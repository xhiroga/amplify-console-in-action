pdf = amplify-console-in-action.pdf

$(pdf):
	docker-compose run --rm review && open $(pdf)

clean:
	rm $(pdf)
