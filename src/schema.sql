CREATE DATABASE datapulse;
USE datapulse;

CREATE TABLE IF NOT EXISTS tdc_UserAccounts
(
user_id INTEGER NOT NULL,
username VARCHAR(255) NOT NULL,
email VARCHAR(255) NOT NULL,
password VARCHAR(25) NOT NULL,
first_name VARCHAR(255) NULL,
last_name VARCHAR(255) NULL,
phone_number INTEGER NOT NULL,
created_at  DATETIME DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
last_login  DATETIME DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
PRIMARY KEY (user_id)
)ENGINE=InnoDB
COMMENT="stores the customer account information";

CREATE TABLE IF NOT EXISTS tdc_Address
(
address_id INTEGER NOT NULL,
user_id INTEGER NOT NULL,
address VARCHAR(255) NOT NULL,
street VARCHAR(255) NULL,
city VARCHAR (100) NULL,
state VARCHAR(100) NULL,
postal_code INTEGER NULL,
country VARCHAR(100) NULL,
PRIMARY KEY (address_id),
FOREIGN KEY (user_id) REFERENCES tdc_UserAccounts(user_id)
)ENGINE=InnoDB
COMMENT="contains the customers' billing and shipping addresses to facilitate checkout.";

CREATE TABLE IF NOT EXISTS tdc_ProductCategory 
(
product_category_id INTEGER NOT  NULL,
product_category_name VARCHAR(255) NOT NULL,
PRIMARY KEY (product_category_id)
)ENGINE=InnoDB
COMMENT=" lists the products categories available for purchase";

CREATE TABLE IF NOT EXISTS tdc_Products
(
product_id INTEGER NOT NULL,
product_category_id INTEGER NOT  NULL,
product_name VARCHAR(255) NOT NULL,
product_desc LONGTEXT NOT NULL,
price DECIMAL(10,2) NOT NULL,
stock_quantity INTEGER NOT NULL,
image_url VARCHAR(500) NOT NULL,
created_at DATETIME DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
PRIMARY KEY (product_id),
FOREIGN KEY (product_category_id) REFERENCES tdc_ProductCategory(product_category_id)
)ENGINE=InnoDB
COMMENT=" lists the products available for purchase";

CREATE TABLE IF NOT EXISTS tdc_ShoppingCart
(
cart_id INT NOT NULL,
user_id INTEGER NOT NULL,
created_at DATETIME DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
PRIMARY KEY (cart_id),
FOREIGN KEY (user_id) REFERENCES tdc_UserAccounts(user_id)
)ENGINE=InnoDB
COMMENT=" ties a specific user to a collection of products they have added to their cart";

CREATE TABLE IF NOT EXISTS tdc_CartItems
(
cart_item_id INTEGER NOT NULL,
cart_id INT NOT NULL,
product_id INTEGER NOT NULL,
quantity INTEGER NOT NULL,
PRIMARY KEY (cart_item_id),
FOREIGN KEY (cart_id) REFERENCES tdc_ShoppingCart(cart_id)
)ENGINE=InnoDB
COMMENT="stores the products that a user has added to their cart";

CREATE TABLE IF NOT EXISTS tdc_Orders
(
order_id INTEGER NOT NULL,
user_id INTEGER NOT NULL,
payment_method VARCHAR(255) NOT NULL,
shipping_address_id INTEGER NOT NULL,
billing_address_id INTEGER NOT NULL,
order_status VARCHAR(255) NOT NULL,
order_date DATETIME DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
total_cost DECIMAL(10,2),
PRIMARY KEY (order_id),
FOREIGN KEY (user_id) REFERENCES tdc_UserAccounts(user_id),
FOREIGN KEY (shipping_address_id) REFERENCES tdc_Address(address_id),
FOREIGN KEY (billing_address_id) REFERENCES tdc_Address(address_id)
)ENGINE=InnoDB
COMMENT="The orders table holds information on completed transactions";

CREATE TABLE IF NOT EXISTS tdc_OrderItems
(
order_item_id INTEGER NOT NULL,
order_id INTEGER NOT NULL,
product_id INTEGER NOT NULL,
quantity INTEGER NOT NULL,
price_at_purchase DECIMAL(10,2),
PRIMARY KEY (order_item_id),
FOREIGN KEY (order_id) REFERENCES tdc_Orders(order_id),
FOREIGN KEY (product_id) REFERENCES tdc_Products(product_id)
)ENGINE=InnoDB
COMMENT="records the products included in each order";

SHOW TABLES;

--- DROP DATABASE datapulse;
