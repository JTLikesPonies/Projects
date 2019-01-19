
# coding: utf-8

# In[17]:


print('hello world!')


# In[18]:


from time import gmtime as the_time

# In[19]:


print(the_time())


# In[20]:


#Dot notation for objects
this_second = the_time().tm_sec
print(this_second)


# In[21]:


# if statement
if this_second%3 == 0:
    print('Divisible by 3!')
elif this_second%2 == 0:
    print('Divisible by 2!')
else:
    print('Default')


# In[22]:


#Importing whole module instead of just a function
import random
import time

print(time.gmtime())


# In[23]:


# for loops
for i in range(5):
    
    random_num = random.randint(2,7)
    print(random_num)
    time.sleep(random_num)
    
    this_second = the_time().tm_sec
    # String formatting with the % operator
    print('This second: %s' %this_second)
    
    if this_second%3 == 0:
        print('%s is divisible by 3!' %this_second)
        continue;
    elif this_second%2 == 0:
        print('%s is divisible by 2!' %this_second)
    else:
        print('Default')
        
    print('Iteration complete!')

