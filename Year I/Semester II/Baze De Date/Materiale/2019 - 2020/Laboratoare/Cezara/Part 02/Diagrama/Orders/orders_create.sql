drop table employee_pay_tbl;
drop table orders_tbl;
drop table products_tbl;
drop table customer_tbl;
drop table employee_tbl;

CREATE TABLE EMPLOYEE_TBL 
(
EMP_ID              VARCHAR(9)       NOT NULL,
LAST_NAME           VARCHAR(15)      NOT NULL,
FIRST_NAME          VARCHAR(15)      NOT NULL,
MIDDLE_NAME         VARCHAR(15),
ADDRESS             VARCHAR(30)      NOT NULL,
CITY                VARCHAR(15)      NOT NULL,
STATE               CHAR(2)           NOT NULL,
ZIP                 NUMBER(5)         NOT NULL,
PHONE               CHAR(10),
CONSTRAINT EMP_PK PRIMARY KEY (EMP_ID)
);


CREATE TABLE EMPLOYEE_PAY_TBL 
(
EMP_ID              VARCHAR(9)        NOT NULL    primary key,
POSITION            VARCHAR(15)       NOT NULL,
DATE_HIRE           DATE,
PAY_RATE            NUMBER(4,2),
DATE_LAST_RAISE     DATE,
SALARY              NUMBER(8,2),
BONUS               NUMBER(6,2),
CONSTRAINT EMP_FK FOREIGN KEY  (EMP_ID) REFERENCES EMPLOYEE_TBL (EMP_ID)
);


CREATE TABLE CUSTOMER_TBL 
(
CUST_ID             VARCHAR(10)    NOT NULL       primary key,
CUST_NAME           VARCHAR(30)    NOT NULL,
CUST_ADDRESS        VARCHAR(20)    NOT NULL,
CUST_CITY           VARCHAR(15)    NOT NULL,
CUST_STATE          CHAR(2)         NOT NULL,
CUST_ZIP            NUMBER(5)       NOT NULL,
CUST_PHONE          NUMBER(10),
CUST_FAX            NUMBER(10)
);


CREATE TABLE PRODUCTS_TBL 
(
PROD_ID        VARCHAR2(10)    NOT NULL       primary key,
PROD_DESC      VARCHAR2(40)    NOT NULL,
COST           NUMBER(6,2)     NOT NULL
);

CREATE TABLE ORDERS_TBL 
(
ORD_NUM             VARCHAR2(10)    NOT NULL     primary key,
CUST_ID             VARCHAR2(10)    NOT NULL references customer_tbl(cust_id),
PROD_ID             VARCHAR2(10)    NOT NULL references products_tbl(prod_id),
QTY                 NUMBER(6)     NOT NULL,
ORD_DATE            DATE,
SALES_REP           VARCHAR2(9)  references EMPLOYEE_TBL (EMP_ID) 
);

