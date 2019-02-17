from selenium import webdriver
import time
import timeit
def order(k):
    driver=webdriver.Chrome('./chromedriver')
    driver.get(k['product_url'])
    driver.find_element_by_xpath('//*[@id="buyTools"]/div[1]/div/label[3]').click()
    driver.find_element_by_xpath('//*[@id="buyTools"]/div[2]/button[1]').click()
    time.sleep(2)
    driver.find_element_by_xpath('//*[@id="PDP"]/div/div[3]/div/div/div/div/div/div/div/div/div/div[3]/button[1]').click()
    driver.find_element_by_xpath('//*[@id="cartForm"]/button[1]').click()
    time.sleep(3)
    driver.find_element_by_xpath('//*[@id="Shipping_FirstName"]').send_keys(k['name'])
    driver.find_element_by_xpath('//*[@id="Shipping_LastName"]').send_keys(k['lastname'])
    driver.find_element_by_xpath('//*[@id="Shipping_PostCode"]').send_keys(k['postalcode'])
    driver.find_element_by_xpath('//*[@id="Shipping_Address1"]').send_keys(k['add'])
    driver.find_element_by_xpath('//*[@id="Shipping_phonenumber"]').send_keys(k['phone'])
    driver.find_element_by_xpath('//*[@id="Shipping_Address3"]').send_keys(k['munic'])
    driver.find_element_by_xpath('//*[@id="shipping_Email"]').send_keys(k['email'])
    time.sleep(2)
    driver.find_element_by_xpath('//*[@id="gdprSection"]/div[1]/label[1]/span').click()
    driver.find_element_by_xpath('//*[@id="shippingSubmit"]').click()
 
keys = {"product_url":"https://www.nike.com/ca/t/odyssey-react-flyknit-2-graphic-running-shoe-27Ws8c",
        "name": "Zeeshaan", "lastname":"Manji","postalcode":"V5H0E8","add":"6588 Nelson Ave","phone":"7788967869","munic":"burnaby","email":"info@a.com"}
start = timeit.timeit()
order(keys)
end = timeit.timeit()
elapsed=end-start
print(elapsed, "Total Time to Run the Bots")
