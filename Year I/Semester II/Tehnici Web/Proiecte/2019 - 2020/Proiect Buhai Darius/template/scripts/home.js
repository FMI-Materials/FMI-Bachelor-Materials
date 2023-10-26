function init_home(){
    page_type = "home";
    get_products_markup(false);
    get_categories(function () {
        get_products(function () {
            get_bill();
        });
    });
    strip_transition_blockers();
}

init_home();