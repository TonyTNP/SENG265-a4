import sys
from PyQt6.QtCore import Qt, QAbstractTableModel

from controller import Controller
from product import Product


class ProductTableModel(QAbstractTableModel):
    def __init__(self, controller):
        super().__init__()
        self.controller = controller
        self._data = []
        self.refresh_data()

    def refresh_data(self):
        self._data = []
        # TODO: Bring your full refresh_data() code from the previous exercise.
        # Fetch the list of products from the controller
        products = self.controller.list_products()

        # Transform the product list into a 2D list (rows and columns)
        self._data = [[product.code, product.description, product.price] for product in products]

        # Emit the layoutChanged signal to notify the QTableView of model changes
        self.layoutChanged.emit()






        # emitting the layoutChanged signal to alert the QTableView of model changes
        self.layoutChanged.emit()

    def reset(self):
        self._data = []
        # emitting the layoutChanged signal to alert the QTableView of model changes
        self.layoutChanged.emit()

    def data(self, index, role):
        value = self._data[index.row()][index.column()]

        if role == Qt.ItemDataRole.DisplayRole:
            # Perform per-type checks and render accordingly.
            if isinstance(value, float):
                # Render float to 2 dp
                return "%.2f" % value
            if isinstance(value, str):
                # Render strings with quotes
                return '%s' % value
            # Default (anything not captured above: e.g. int)
            return value

        if role == Qt.ItemDataRole.TextAlignmentRole:
            if isinstance(value, int) or isinstance(value, float):
                # Align right, vertical middle.
                return Qt.AlignmentFlag.AlignVCenter + Qt.AlignmentFlag.AlignRight

    def rowCount(self, index):
        # The length of the outer list.
        return len(self._data)

    def columnCount(self, index):
        # The following takes the first sub-list, and returns
        # the length (only works if all rows are an equal length)
        if self._data:
            return len(self._data[0])
        else:
            return 0

    def headerData(self, section, orientation, role=Qt.ItemDataRole.DisplayRole):
        headers = ['Code', 'Description', 'Price']
        if orientation == Qt.Orientation.Horizontal and role == Qt.ItemDataRole.DisplayRole:
            return '%s' % headers[section]
        return super().headerData(section, orientation, role)