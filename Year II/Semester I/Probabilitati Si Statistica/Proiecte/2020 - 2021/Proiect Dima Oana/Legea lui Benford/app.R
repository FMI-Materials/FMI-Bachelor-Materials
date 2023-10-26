#####################################
  #Dima Oana & Badescu George Gr. 241
  #Proiect Probabilitati si statistica 
  #Februarie 2021
  #Legea lui Benford 
#######################################

library(shiny)
library(ggplot2)

ui <- fluidPage(

  navbarPage("Benford App",
             #experiment 1
             tabPanel("Experimentul YoutTube",
                      h3("Legea lui Benford"),
                      uiOutput('formula'),
                      h4("Experimentul YouTube (Date de referinta Canada 2019)"),
                      textOutput("text1"),
                      textOutput("text2"),
                      
  sidebarLayout(      
    sidebarPanel(
      
      selectInput("tip", "Alege tipul de date:", 
                  choices=c('date oficiale', 'date neoficiale')),
      #input conditional pentru datele oficiale
      conditionalPanel(condition = "input.tip == 'date oficiale' ",
                       
      #sunt mai multe coloane care respecta legea   choices=c('views', 'likes', 'comment_count')              
      radioButtons("coloana", "Alege domeniul", 
                   choiceNames = c('Vizualizari','Like-uri','Comentarii'),
                   choiceValues = c('views', 'likes', 'comment_count') 
                   )
      #sfarsit conditie
      ),
      sliderInput("n", "Marime de referinta", min = 0, max =20000, value = 7000),
      
      hr(),
      helpText("Sursa date:"),
      tags$a(href="https://www.kaggle.com/datasnaek/youtube-new?select=CAvideos.csv", "Kaggle.com-Trending YouTube Video Statistics (2019)")
    ),
    
    #afisare grafic / tabel cu date
    mainPanel(
      #creare tab-uri
      tabsetPanel(
      tabPanel("Grafic", plotOutput("date")), 
      tabPanel("Vizualizare date tabel", DT::dataTableOutput("mytable") )
      )
    )
    
  )
             ),
  tabPanel("Unde nu functioneaza?",
           h3("Analiza vanzarilor din supermarket (2019)"),
           textOutput("text3"),
           textOutput("text4"),
           
           
           fluidRow(
             column(4,
                    h4("Rating"),
                    helpText("Cauza: limitare interval"),
                    plotOutput("grafic1")
                    
             ),
             column(4, 
                    h4("Cantitate"),
                    helpText("Cauza: nu creste exponential"),
                    plotOutput("grafic2")
                  
             ),
             column(4,
                    h4("ID Factura"),
                    helpText("Cauza: numere unice"),
                    plotOutput("grafic3")
                    
             )
           )
           ),
  helpText("Proiect realizat de Dima Oana & Badescu Gabi (241)")
  )
  
)

#################################################################################
#
# Server function
#
server <- function(session,input,output) {
  #zona de text
  output$text1<-renderText({
    "Este cunoscut faptul ca numarul vizualizarilor
    video-urilor de pe YouTube respecta ipotezele de examinare a datelor de catre lege:
    sa fie numere generate aleator, predispuse cresterii exponentiale, nerestrictionate de maxime sau minime, iar 
    calculele sa aiba loc pe esantioane mari de date.
    "
  })
  output$text2<-renderText({
    "
    Se poate observa cum de la primele 1500 de vizualizari procentele se aproprie
    de respectarea legii. Tabelul cu date neoficiale contine date modificate manual, neconforme cu 
    realitatea care demonstreaza faptul ca Legea lui Benford poate sa semnaleze in anumite cazuri frauda.
    
    "
  })
  output$text3<-renderText({
    "
    Setul de date reprezinta vanzarile unei companii de 
    supermarketuri din Myanmar care a inregistrat timp de 3 luni,
    date din fiecare oras din tara. 
    "
  })
  output$text4<-renderText({
    "
    Se poate observa ca Legea lui Benford nu este aplicabila pe anumite tipuri de date.
    "
  })
  output$formula <- renderUI({
    withMathJax(
      #afisare formula legea lui Benford
      helpText('$$P(d)=lg (d+1) -lg(d)=lg(\\frac{d+1}{d})=lg(1+\\frac {1}{d}), d\\in\\{1..9\\}$$')
    )
  })
  #functie care genereaza graficul legii lui Benford pentru un set de date
  Benford<- function(rate, linii_coloana)
  {
    #extrag prima cifra
    primaCifra<-function(x) as.numeric(substr(gsub('[0.]', '', x), 1, 1))
    #vector de frecventa pt cifrele de la 1 la 9
    frecv<-c(0,0,0,0,0,0,0,0,0)
    for (i in 1:linii_coloana)
    {
      cifra<-primaCifra(rate[i])
      frecv[cifra]<-frecv[cifra]+1#calculez frecventa
    }
    total<-sum(frecv)#o sa ma folosesc de nr total de aparitii in calc procentului
    #vector care retine procentul pentru fiecare cifra
    procent<-c(0,0,0,0,0,0,0,0,0)
    for (i in 1:9)
    {
      procent[i]<-frecv[i]/total #calculez procentul 
      #de cate ori apare cifra i/ nr total de aparitie al cifrelor
    }
    benford<-c(0,0,0,0,0,0,0,0,0)
    for (i in 1:9)
    {
      benford[i]<-log10(1+ 1/i)#calculez valorile standard ale lui Benford 
    }
    #formez un data frame din care o sa generez graficul
    frame3<-data.frame(
      numere=c("1","2", "3", "4", "5", "6", "7", "8", "9"),
      ben=benford,
      procente=procent
    )
    #generare grafic
    ggplot(data = frame3, aes(x = numere, group=1))+ geom_bar(aes(y = procente), stat = "identity", color=NA, fill="lightblue") + geom_line(aes(y = ben), stat = "identity", color="red") 
    
  }

  #grafice
  output$date <- renderPlot({
    
    #citire din fisierul dat ca input din dropdown
    nume_csv<-paste(input$tip, ".csv", sep="")
    data1<-(read.csv(nume_csv, header=TRUE))
    
    #afisare tabel cu date
    tabel<- data.frame(
      ID=data1$video_id,
      Canal=data1$channel_title,
      Vizualizari=data1$views,
      Likeuri=data1$likes,
      Comentarii=data1$comment_count
      
    )
    output$mytable = DT::renderDataTable({tabel})
    #incheiere afisare tabel cu date
    
    #extrag numele coloanei acolo unde al doilea dropdown a fost activ
    nume_coloana<-input$coloana
    if (nume_coloana == 'likes')
      rate<-data1$likes
    else if (nume_coloana == 'comment_count')
      rate<-data1$comment_count
    else 
      rate<-data1$views
    
    #aplic legea lui Benford pt n date de Slidebar
    
    #lucrez doar pe coloana Views
    linii_coloana<-input$n
    
    Benford(rate, linii_coloana)

   
  })
  data2<-(read.csv('Sales.csv', header=TRUE))
  output$grafic1 <- renderPlot({ 
    rate<-data2$Rating
    Benford(rate, length(rate))
    
    })
  output$grafic2 <- renderPlot({
    rate<-data2$Quantity
    Benford(rate, length(rate))
  })
  output$grafic3 <- renderPlot({
    rate<-data2$Invoice.ID
    Benford(rate, length(rate))
  })
  
}
shinyApp(ui = ui, server = server)