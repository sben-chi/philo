int main()
{
	int t;
	int t2;

	pthread_create(&t, NULL, f, NULL);
	pthread_create(&t2, NULL, f, NULL);
	          
}
