import sys

from PyQt6.QtCore import Qt
from PyQt6.QtWidgets import QApplication, QMainWindow, QVBoxLayout
from PyQt6.QtWidgets import QPushButton, QPlainTextEdit, QWidget

from controller import Controller
from product import Product

class ProductListGUI(QMainWindow):

    def __init__(self):
        super().__init__()
        self.controller = Controller()
        self.setWindowTitle("Products")
        self.setMinimumSize(600, 400)

        self.text_box = QPlainTextEdit()

        refresh_button = QPushButton("Refresh Products")
        refresh_button.clicked.connect(self.refresh_button_clicked)
        clear_button = QPushButton("Clear Text")
        clear_button.clicked.connect(self.clear_button_clicked)

        layout = QVBoxLayout()
        layout.addWidget(self.text_box)
        layout.addWidget(refresh_button)
        layout.addWidget(clear_button)

        widget = QWidget()
        widget.setLayout(layout)
        self.setCentralWidget(widget)
        self.refresh_button_clicked()

    def refresh_button_clicked(self):
        # TODO: Call the controller.list_products().
        # With the results, list all the products in the QPlainTextEdit,
        # showing code, description and price.

        # Clear the existing text
        self.text_box.clear()

        # Get the list of products from the controller
        products = self.controller.list_products()

        # Iterate over the products and display them in the text box
        for product in products:
            product_details = f"Code: {product.code}, Description: {product.description}, Price: ${product.price:.2f}"
            self.text_box.appendPlainText(product_details)



    def clear_button_clicked(self):
        # TODO: clear the text from the QPlainTextEdit

        # Clearing the text from the QPlainTextEdit
        self.text_box.clear()



def main():
    app = QApplication(sys.argv)
    window = ProductListGUI()
    window.show()
    app.exec()

if __name__ == '__main__':
    main()

    #Here is the tester: 
    # python product_list_gui.py

