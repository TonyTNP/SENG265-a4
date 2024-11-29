import sys

from PyQt6.QtWidgets import QApplication, QMainWindow, QWidget
from PyQt6.QtWidgets import QLabel, QLineEdit, QPushButton, QMessageBox
from PyQt6.QtWidgets import QGridLayout, QVBoxLayout, QHBoxLayout
from PyQt6.QtCore import Qt

from controller import Controller, IllegalOperationException

class ListProductGUI(QMainWindow):
    def __init__(self, controller):
        super().__init__()
        self.controller = controller
        self.setWindowTitle("List Product")

        layout1 = QGridLayout()

        label_code = QLabel("Product Code")
        self.text_code = QLineEdit()
        self.text_code.setInputMask('00000000')
        label_description = QLabel("Description")
        self.text_description = QLineEdit()
        label_price = QLabel("Price")
        self.text_price = QLineEdit()

        layout1.addWidget(label_code, 0, 0)
        layout1.addWidget(self.text_code, 0, 1)
        layout1.addWidget(label_description, 1, 0)
        layout1.addWidget(self.text_description, 1, 1)
        layout1.addWidget(label_price, 2, 0)
        layout1.addWidget(self.text_price, 2, 1)

        layout2 = QHBoxLayout()

        self.button_update = QPushButton("Update")
        self.button_delete = QPushButton("Delete")
        self.button_close = QPushButton("Close")
        layout2.addWidget(self.button_update)
        layout2.addWidget(self.button_delete)
        layout2.addWidget(self.button_close)

        layout3 = QVBoxLayout()

        top_widget = QWidget()
        top_widget.setLayout(layout1)
        bottom_widget = QWidget()
        bottom_widget.setLayout(layout2)
        layout3.addWidget(top_widget)
        layout3.addWidget(bottom_widget)
        widget = QWidget()
        widget.setLayout(layout3)

        self.setCentralWidget(widget)

        # define widgets' initial state
        self.text_code.setEnabled(False)
        self.text_description.setEnabled(False)
        self.text_price.setEnabled(False)
        self.button_close.setEnabled(True)

        # connect the button's clicked signal to the slot below
        self.button_close.clicked.connect(self.close_button_clicked)


    def list_product(self, key):
        ''' search and list product '''
        # TODO: call the controller.search_product() method with the key passed from
        # the main window. Then, if a product is found, show its fields in the 
        # QLineEdits, and do not allow the user to edit the text.
        # (We will not work with the Update and Delete buttons in this lab, but you
        # can reuse the ideas from this window in your projects).
        # If no product is found, show a warning message that there is no product
        # with the given code. (Even though that will never happen if your code 
        # is correct. Do you understand why?).

        # Search for the product using the controller
        product = self.controller.search_product(key)

        if product:
            # Populate the fields with product details
            self.text_code.setText(product.code)
            self.text_description.setText(product.description)
            self.text_price.setText(f"{product.price:.2f}")

            # Make fields read-only
            self.text_code.setReadOnly(True)
            self.text_description.setReadOnly(True)
            self.text_price.setReadOnly(True)
        else:
            # Show a warning message if no product is found
            QMessageBox.warning(self, "Product Not Found", f"No product found with code: {key}")


    def close_button_clicked(self):
        ''' close the list product window '''
        self.hide()

    def closeEvent(self, event):
        ''' Handle the window's "X" button to close the window '''
        self.close_button_clicked()


        #Here is the tester for C: 
        # python product_table_gui.py












    def close_button_clicked(self):
        ''' 'close list product window '''
        # TODO: add code here to hide the list product's window when it is close.
        self.hide()



    def closeEvent(self, event):
        ''' Closing the window by using the Window "X" button
         should be similar to close with the Close button '''
        self.close_button_clicked()
