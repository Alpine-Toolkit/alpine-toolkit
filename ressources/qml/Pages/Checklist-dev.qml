import QtQml 2.2
import QtQuick 2.6
import QtQuick.Window 2.2

import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0

import QtQuick.LocalStorage 2.0

Pane {
    id: checklist_pane

    ListModel {
        id: checklist_model

        // ListElement {
        //     name: "Apple"
        // }
    }

    function open_db() {
        var db = LocalStorage.openDatabaseSync("CheckListDatabase", "1.0", "Check List Database", 1000);
        db.transaction(
            function(transaction) {
                // tx.executeSql('CREATE TABLE IF NOT EXISTS Activity(name TEXT)');
                // tx.executeSql('CREATE TABLE IF NOT EXISTS Category(name TEXT)');
                transaction.executeSql('CREATE TABLE IF NOT EXISTS Item(name TEXT)');
            });
        return db;
    }

    function load_db(db) {
        db = open_db();

        var items = []

        db.transaction(
            function(transaction) {
                var query = transaction.executeSql('SELECT * FROM Item');
                for(var i = 0; i < query.rows.length; i++) {
                    var row = query.item(i);
                    var item = {name: row.name};
                    console.log(item);
                    items.push(item)
                }
            })

        return items;
    }

    function save_db() {
        db = open_db();

        new_items = []
        for(var i = 0; i < checklist_model.count; i++) {
            var item = checklist_model.get(i);
            console.log(item);
            new_item.append(item);
        }

        old_items = load_db(db);

        item_to_add = [];
        item_to_delete = [];
        for (var i = 0; i < new_items.length; i++) {
            for (var j = 0; j < old_items.length; i++) {
        }

        db.transaction(
            function(transaction) {
            });
    }

    Component.onCompleted: { // expected token ,
        db = load_db()

        checklist_model.clear();
        checklist_model.append(element_data);

    }

    Component.onDestruction: {
    }

    Column {
        ToolButton {
            id: add_item_button
            contentItem: Image {
                fillMode: Image.Pad
                horizontalAlignment: Image.AlignHCenter
                verticalAlignment: Image.AlignVCenter
                source: "qrc:/icons/add-black.png"
            }
            onClicked: add_item_popup.open()
        }

        ListView {
            id: list_view
            anchors.fill: parent
            model: checklist_model
            delegate: ItemDelegate {
            width: parent.width
            font.pixelSize: 12
            text: name
            }
        }
    }

    Popup {
        id: add_item_popup
        modal: true
        focus: true
        // Fixme: not centered
        x: (application_window.width - width) / 2
        y: application_window.height / 6
        width: application_window.width * .9
        contentHeight: column.height

        Column {
            id: column
            width: parent.width
            spacing: 5

            Label {
                font.pointSize: 20
                font.bold: true
                text: qsTr("Add Item")
            }

            TextField {
                id: item_name_text_field
                anchors.horizontalCenter: parent.horizontalCenter
                font.pointSize: 32
                placeholderText: "enter name"
            }

            Row {
                spacing: 5
                anchors.right: parent.right

                Button {
                    text: "Cancel"
                    onClicked: calibrate_popup.close()
                    // label.color: "#42a5f5ff"
                    background: null
                }
                Button {
                    text: "Ok"
                    onClicked: {
                        if (item_name_text_field.text) {
                            console.info("define item name", altitude_text_field.text);
                        }
                        calibrate_popup.close()
                    }
                    background: null
                }
            }
        }
    }


    }
