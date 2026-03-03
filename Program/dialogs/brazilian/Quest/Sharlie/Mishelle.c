// Брат Шарля, Мишель де Монпе, он же Дичозо, он же воплощение Кукулькана, он же главный злодей
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (pchar.questTemp.Sharlie == "takeknife")
			{
				dialog.text = "Bem-vindo, Charles, o Viajante! Ouvi tudo sobre como você derrotou aqueles piratas na costa leste da Martinica. Agora tenho absoluta certeza de que não me enganei sobre você, irmão.";
				link.l1 = "Filhos da puta me pegaram numa armadilha. Mas eles nos subestimaram. Meu navegador, minha tripulação e eu saímos por cima. Embora eu tenha que admitir, meu caro irmão, no começo... as coisas pareciam sombrias.";
				link.l1.go = "trial";//промежуточная стадия
				break;
			}
			if (pchar.questTemp.Sharlie == "gambitstage")
			{
				bool bFMQM = CheckAttribute(pchar,"questTemp.FMQM") && pchar.questTemp.FMQM != "fail" && pchar.questTemp.FMQM != "end";
				bool bFMQN = CheckAttribute(pchar,"questTemp.FMQN") && pchar.questTemp.FMQN != "fail" && pchar.questTemp.FMQN != "end";
				bool bFMQT = CheckAttribute(pchar,"questTemp.FMQT") && pchar.questTemp.FMQT != "fail" && pchar.questTemp.FMQT != "end";
				bool bFMQP = CheckAttribute(pchar,"questTemp.FMQP") && pchar.questTemp.FMQP != "fail" && pchar.questTemp.FMQP != "end";
				bool bFMQG = CheckAttribute(pchar,"questTemp.FMQG") && pchar.questTemp.FMQG != "fail" && pchar.questTemp.FMQG != "end";
				bool bFMQL = CheckAttribute(pchar,"questTemp.FMQL") && pchar.questTemp.FMQL != "fail" && pchar.questTemp.FMQL != "end";
				if(bFMQM || bFMQN || bFMQT || bFMQP || bFMQG || bFMQL)
				{
					if (sti(pchar.rank) < 12)
					{
						dialog.text = "Saudações, irmão! Agradeço seu entusiasmo sincero para me tirar daqui, mas você ainda não está pronto para o próximo passo. Meu plano exige um capitão experiente. Continue explorando o Caribe, conquiste prêmios e aprenda! Quando estiver pronto, seguiremos em frente.";
						link.l1 = "Bom, como quiser, irmão. Quem está aí dentro é você, não eu.";
						link.l1.go = "exit";
					} 
					else 
					{
						dialog.text = "Que bom te ver, irmão. Não se esqueça dos seus compromissos com os outros. Assim que estiver livre, estarei te esperando – tenho ideias para nosso próximo passo!";
						link.l1 = "Entendido, irmão. Vou cuidar dos meus compromissos, mas volto em breve!";
						link.l1.go = "exit";
					}
					break;
				}
				if (sti(pchar.rank) < 12)
				{
					Log_info("Level 12 is required");
					dialog.text = "Charles, o Navegador! Ouvi falar das suas aventuras! Você está quase pronto para a próxima etapa do meu plano. Volte assim que ganhar mais experiência.";
					if (sti(pchar.rank) < 7)
					{
						dialog.text = "Saudações, irmão! Agradeço seu entusiasmo sincero para me tirar daqui, mas você ainda não está pronto para o próximo passo. Meu plano exige um capitão experiente. Continue explorando o Caribe, conquiste prêmios e aprenda! Quando estiver pronto, seguiremos em frente.";
					} 
					else 
					{
						if (sti(pchar.rank) < 10)
						{
							dialog.text = "Que bom te ver, irmão! Ouvi dizer que você está avançando! Mas ainda não está pronto para a próxima etapa do meu plano. Continue fazendo o que tem feito e volte a me procurar quando estiver preparado.";
						}
					}
					link.l1 = "Bem, como quiser, irmão. Quem está sentado aqui é você, não eu.";
					link.l1.go = "exit";
					if(sti(pchar.rank) > 8)
					{
						link.l2 = "Não acho, irmão. Talvez você já tenha se acostumado com essa cela, mas eu não pretendo ficar aqui por muito tempo – nosso pai não vai esperar para sempre. Fale logo.";
						link.l2.go = "gambitA";
					}
					break;
				}
				else
				{
					dialog.text = "Boa tarde, Charles. Ver você me enche de alegria: você está mesmo mudando para melhor.";
					link.l1 = "É mesmo? E como você chegou a essa conclusão?";
					link.l1.go = "gambit";//переход на Гамбит
					break;
				}
			}
			if (!CheckAttribute(npchar, "quest.givelink_saga") && CheckAttribute(pchar, "questTemp.HWIC.Detector"))//признак, что Гамбит пройден или провален
			{
				dialog.text = "Entendo. Vejo que você tem novidades para mim, Charles! Então, o que aconteceu? Espero que não seja nada ruim?";
				link.l1 = "Segui o conselho que você me deu da última vez...";
				link.l1.go = "saga";//переход на Сагу
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Fail1") && CheckAttribute(pchar, "questTemp.HWIC.Fail2") && CheckAttribute(pchar, "questTemp.HWIC.Fail3"))//признак, что Гамбит провален по всем трем вариантам
			{
				dialog.text = "Finalmente, você chegou... Qual é a novidade, meu caro irmão?";
				link.l1 = "Segui o conselho que você me deu da última vez...";
				link.l1.go = "gambit_fale";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "mishelle")//Сага готова к старту
			{
				dialog.text = "Que bom te ver, Charles! Você viu o Chevalier de Poincy? Como foi a sua conversa?";
				link.l1 = "Sim, querido irmão. Já nos encontramos. E tenho duas notícias para você, uma boa e uma ruim. Vou começar pela boa. Resolvi sua dívida com o de Poincy. A má notícia é que ele não vai te soltar até que eu cumpra sua promessa de resolver um assunto com um tal de herege...";
				link.l1.go = "saga_5";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "fail" && !CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince")) // пиратская линейка провалена или пройдена не полностью
			{
				dialog.text = "Como você se saiu em La Vega, irmão?";
				link.l1 = "Nada de que me gabar, de verdade. Tyrex é uma figura e tanto, mas o jeito dele de fazer negócios não combina comigo.";
				link.l1.go = "saga_17e";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "fail" && CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince")) // пиратская линейка провалена или пройдена не полностью, но дальше 4 квеста
			{
				dialog.text = "Como você se saiu em La Vega, irmão? Ouvi alguns boatos e, para ser bem sincero, não gostei nada do que ouvi... Charlie Prince.";
				link.l1 = "Acho que já entendi do que eram esses boatos. Mas isso ficou no passado. Não trabalho mais com o Tyrex, aquele serviço ficou sujo demais pro meu gosto.";
				link.l1.go = "saga_17f";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete") // пиратская линейка пройдена полностью
			{
				dialog.text = "Bem, saudações... Corsário Charlie Prince. Me diga, Charles, como você chegou tão baixo? Eu não consigo acreditar nisso. Meu irmão, que fazia cara de nojo só de eu mencionar saquear um galeão mercante espanhol, agora é um dos piratas mais procurados e perigosos dessa região! Até eu, atolado até o pescoço, fico vermelho toda vez que ouço falar das suas façanhas. Já amaldiçoei o dia em que te mandei para La Vega. Que vergonha! Um nobre francês se juntou aos piratas e virou o pior deles em tão pouco tempo! E agora, irmão? Está procurando uma vaga de barão dos piratas?";
				link.l1 = "Não. Acabei de vez com a pirataria.";
				link.l1.go = "saga_17g";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			
			dialog.text = "O que mais, Charles? Acho que já falamos de tudo. Tempo é dinheiro, meu caro irmão – apresse-se!";
			link.l1 = "Sim, sim, lá vou eu...";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Fortfrance");
		break;
		
		case "Mishelle_prisoner":
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Maltie_officer"));
			QuestPointerDelLoc("FortFrance_Dungeon", "quest", "quest1");
			SetCurrentTime(13, 30);
			dialog.text = "Charles!.. Que bom te ver, irmão! Eu entendo, claro, que pode ser difícil pra você acreditar, mas estou feliz pra caramba que você está aqui...";
			link.l1 = "Ha! Olha só pra ele! Tá feliz! Enquanto você ficava aí todo cheio de si com sua 'Ordem', o Charles era a vergonha da família, um artista de quinta, vivendo às custas de cortesãs, e um 'cavaleiro' de salão, né? Mas agora que foi parar atrás das grades pelos próprios colegas, tá 'feliz da vida' de ver seu irmão inútil!";
			link.l1.go = "Mishelle_prisoner_1";			
		break;
		
		case "Mishelle_prisoner_1":
			dialog.text = "Charles, você...";
			link.l1 = "Eu ainda não terminei! Por que você não mandou nenhuma notícia sua para a França?! Tiraram seu direito de se corresponder?! Nosso pai ficou doente de tanto se preocupar com você! E ele me pediu para descobrir pelo menos alguma coisa sobre o seu paradeiro!..";
			link.l1.go = "Mishelle_prisoner_1a";
		break;
		
		case "Mishelle_prisoner_1a":
			dialog.text = "Charles, como eu poderia contar ao pai o que aconteceu comigo? O que eu escreveria para ele? Não, irmão, por mais difícil que seja, é melhor que nosso pai não saiba de nada por enquanto. E também seria inútil escrever para você – você está sempre mudando de endereço em Paris... Como foi que você me encontrou?..";
			link.l1 = "A pedido do seu pai, fui até Malta. Lá, recebi algumas informações do seu amigo, o Chevalier de La Brignais. Ele me escreveu sobre seus problemas e disse que você provavelmente estava em algum lugar da Martinica. Depois voltei para a França e visitei seu pai. E, depois de tudo isso, vim parar nesse inferno abafado, onde os mosquitos literalmente devoram a gente vivo...";
			link.l1.go = "Mishelle_prisoner_1b";
		break;
		
		case "Mishelle_prisoner_1b":
			dialog.text = "Você contou tudo isso ao pai?";
			link.l1 = "Não. E o Chevalier de La Brignais também não respondeu às cartas dele, temendo as possíveis consequências... Nosso pai ainda não sabe nada sobre o seu paradeiro. Eu decidi te encontrar e descobrir toda a verdade. Só pra você saber, eu vim pra Martinica não por sua causa, mas pelo nosso pobre pai!";
			link.l1.go = "Mishelle_prisoner_2";
		break;
		
		case "Mishelle_prisoner_2":
			dialog.text = "Sério? Charles, desde quando você se importa com a família? Vamos ser sinceros, irmão, todo mundo em Paris sabe quem é seu pai. Você pode até carregar o nome de Maure, mas não quer ver o nome de Monper manchado. Porque, nesse caso, não poderia mais usar sua linhagem pra contar histórias mirabolantes sobre seus feitos heroicos, não é? As portas das melhores casas de Paris se fechariam pra você, e nem deixariam você chegar perto do Louvre. Você acha mesmo que suas cortesãs e amantes, cujos maridos você faz de corno enquanto eles lutam pelo nosso país, vão querer trair seus senhores com o irmão de um criminoso do Estado como eu? Aposto que veio direto da cama de alguma moça casada, acertei? Charles, o que foi essa cara? Peguei num ponto fraco?";
			link.l1 = "Você... Você!..";
			link.l1.go = "Mishelle_prisoner_3";
		break;
		
		case "Mishelle_prisoner_3":
			dialog.text = "Tudo bem, irmão. Já trocamos farpas, chega. Admito que não sou perfeito. Mas você também não é nenhum santo. Charles, agora realmente não é hora de brigar. Nós dois queremos a mesma coisa: salvar a honra e a dignidade da família Monper... seja lá quais forem nossos motivos. Irmão, por uma vez na vida, vamos deixar a rivalidade de lado e buscar a paz. Fechado?";
			link.l1 = "Vamos tentar então... Mas pode me explicar do que estão te acusando?";
			link.l1.go = "Mishelle_prisoner_4";
		break;
		
		case "Mishelle_prisoner_4":
			dialog.text = "Oficialmente, parece que é sobre os gastos do dinheiro da Sociedade. Na verdade, é algo muito mais profundo.";
			link.l1 = "Então, você desviou o dinheiro da sua organização? Ora, ora...";
			link.l1.go = "Mishelle_prisoner_5";
		break;
		
		case "Mishelle_prisoner_5":
			dialog.text = "Eu te disse que essas eram as acusações oficiais. Eu não peguei um único louis d'or. Vou te contar como foi... veja bem, não posso te explicar tudo em detalhes enquanto estou atrás das grades. Não tenho o direito moral de revelar os segredos da nossa Sociedade.";
			link.l1 = "Por favor, tente explicar, meu caro irmão. Eu tenho o direito de saber, não acha?";
			link.l1.go = "Mishelle_prisoner_6";
		break;
		
		case "Mishelle_prisoner_6":
			dialog.text = "Está bem. Recebi dinheiro para uma operação extremamente perigosa e delicada, que tinha como objetivo mudar o equilíbrio político no Caribe. Agi sob ordens diretas de Philippe de Poincy, o governador-geral das colônias francesas. Mas a operação fracassou, apesar de todos os meus esforços.\nDe Poincy ficou furioso quando todos os seus planos ousados desmoronaram. Ele mesmo assinou a ordem para minha prisão e fez questão de que fosse cumprida. Depois veio até aqui e declarou que me acusaria de desfalque e traição contra a Ordem se meus parentes ou eu não devolvêssemos o dinheiro gasto na operação.";
			link.l1 = "Que bela confusão. Onde está esse dinheiro que, pelo que entendi, nossa família tem que pagar pelas suas trapalhadas?";
			link.l1.go = "Mishelle_prisoner_7";
		break;
		
		case "Mishelle_prisoner_7":
			dialog.text = "Foi tudo gasto na preparação da operação. Subornos, organização de expedições, compra de todo tipo de mercadoria e equipamento. Tive despesas bem altas. Como eu disse – não fiquei com uma moeda sequer.";
			link.l1 = "E qual é o valor que estão exigindo?";
			link.l1.go = "Mishelle_prisoner_8";
		break;
		
		case "Mishelle_prisoner_8":
			dialog.text = "Um milhão.";
			link.l1 = "Merde! Você tá brincando, né?!";
			link.l1.go = "Mishelle_prisoner_9";
		break;
		
		case "Mishelle_prisoner_9":
			dialog.text = "Eu pareço alguém de bom humor para piadas? Não, meu caro irmão, essa é a amarga verdade. Vamos ter que entregar um milhão de pesos ao de Poincy.";
			link.l1 = "Mas que droga! Nossa família nunca teve esse tipo de dinheiro! Nem juntando tudo em vinte anos conseguiríamos isso!";
			link.l1.go = "Mishelle_prisoner_10";
		break;
		
		case "Mishelle_prisoner_10":
			dialog.text = "Se eu não estivesse atrás das grades e preso às minhas obrigações com a Sociedade, eu conseguiria em seis meses, um ano no máximo, talvez um ano e meio. Charles, aqui é o Novo Mundo. Tudo é diferente. Um homem motivado e ambicioso pode fazer fortuna por conta própria sem precisar dedicar a vida inteira a isso, como teria que fazer na Europa.";
			link.l1 = "Um milhão em meio ano?! Você ficou louco? Se tem tanta certeza, por que não conta isso ao seu de Poincy? Deixe que ele te solte. Mostre do que é capaz...";
			link.l1.go = "Mishelle_prisoner_11";
		break;
		
		case "Mishelle_prisoner_11":
			dialog.text = "Ah, não fala bobagem, Charles! Não tem chance do Poincy me soltar dessa cela. Se fosse tão fácil assim, eu não teria pedido sua ajuda.";
			link.l1 = "Então sou eu quem tem que arranjar o dinheiro pra comprar sua liberdade?!";
			link.l1.go = "Mishelle_prisoner_12";
		break;
		
		case "Mishelle_prisoner_12":
			dialog.text = "Não é só a minha liberdade. Ou já esqueceu? Vamos voltar à nossa conversa sobre palácios, bailes e sexo com cortesãs da nobreza? Sim, Charles, é você quem tem que fazer isso. Se, é claro, quiser continuar levando essa sua vida fútil em Paris como antes. Você gostaria disso, não é, irmão?";
			link.l1 = "Mas caramba, onde diabos eu vou conseguir isso?! Você conhece alguma floresta antiga por aqui onde crescem luís-d'ouro em vez de folhas?";
			link.l1.go = "Mishelle_prisoner_13";
		break;
		
		case "Mishelle_prisoner_13":
			dialog.text = "O Novo Mundo inteiro é um pomar de árvores de dinheiro, mas as pessoas são preguiçosas demais para levantar a cabeça e estender a mão para os galhos. Não se preocupe, Charles, você vai se sair muito bem. Te conheço desde a infância e jamais teria perdido tempo convencendo nosso pai a te mandar para cá se achasse que você fosse tolo ou preguiçoso.\nApesar dos defeitos que já mencionei, você é corajoso, ambicioso, inteligente, tem a língua afiada e sabe manejar um florete, o que é uma habilidade extremamente importante por aqui...";
			link.l1 = "Muito obrigado. Será que meu querido irmão realmente se dignou a me elogiar? E eu achando que não passava de um artista medíocre, um cortesão...";
			link.l1.go = "Mishelle_prisoner_14";
		break;
		
		case "Mishelle_prisoner_14":
			dialog.text = "Corta essa conversa fiada. Temos um acordo ou não?";
			link.l1 = "Desculpa, irmão. Escapou. Só não estou acostumado a ouvir essas palavras de você. É como uma prostituta de rua pregando sobre salvação da alma.";
			link.l1.go = "Mishelle_prisoner_15";
		break;
		
		case "Mishelle_prisoner_15":
			dialog.text = "Vamos em frente, irmão. Como eu disse, você tem tudo o que precisa para se dar bem aqui. E não está sozinho. Vou te orientar sobre o que fazer e como fazer do jeito certo. Me escute e vamos sair dessa melhor do que nunca. Acredite, você não vai encontrar ninguém com mais experiência do que eu. Está pronto para parar de falar besteira e finalmente ir direto ao ponto?";
			link.l1 = "É, parece que vou ficar por aqui um tempo... Tudo bem. Pode falar, Michel.";
			link.l1.go = "Mishelle_prisoner_16";
		break;
		
		case "Mishelle_prisoner_16":
			dialog.text = "Sim, irmão, você vai ficar aqui por um tempo. Ainda bem que já percebeu isso. Então, se alguma cortesã está esperando por você em Paris, sugiro que esqueça dela. Mas não fique triste, as garotas daqui têm seus próprios encantos.  Só que elas gostam de homens de verdade, fortes e decididos, até um pouco brutos. Então, se quiser conquistar uma moça da colônia, não conte com poesia, conversas sobre pintura ou passeios ao luar. Elas não vão aprovar.";
			link.l1 = "Tá certo, irmão. Você foi atingido por um raio de conversa fiada? Vamos direto ao ponto. Estou disposto a ouvir seus conselhos, mas não suas insinuações maldosas.";
			link.l1.go = "Mishelle_prisoner_17";
		break;
		
		case "Mishelle_prisoner_17":
			dialog.text = "Excelente. Para ter qualquer chance de sucesso, você precisa ter um navio. O Caribe é um arquipélago. Você sabe disso, não é? Aqui, a vida está ligada ao mar. Um homem com seu próprio navio tem um horizonte infinito de possibilidades.";
			link.l1 = "Mas eu não sou marinheiro!";
			link.l1.go = "Mishelle_prisoner_18";
		break;
		
		case "Mishelle_prisoner_18":
			dialog.text = "Então, está na hora de se tornar um. Você não tem outra escolha mesmo. Não pensou em virar escrivão do porto ou se alistar na guarnição, pensou? Não? Então vai ser capitão.";
			link.l1 = "Que reviravolta na minha carreira! E onde é que eu vou arranjar um navio?";
			link.l1.go = "Mishelle_prisoner_19";
		break;
		
		case "Mishelle_prisoner_19":
			dialog.text = "Tem um excelente lugre esperando por você no nosso estaleiro local. Não é grande, mas é um barco muito confortável, perfeito para você dar os primeiros passos no mundo da navegação. Esse lugre foi construído especialmente para mim. Eu dei um sinal de cinco mil pesos pela embarcação com a ajuda dos meus amigos. Vá até o construtor de navios e diga que foi o Michel de Monper que te enviou. Ele vai entender o que você está procurando.";
			link.l1 = "O navio custa só cinco mil? Isso é meio estranho...";
			link.l1.go = "Mishelle_prisoner_20";
		break;
		
		case "Mishelle_prisoner_20":
			dialog.text = "Irmão, está me ouvindo? Cinco mil é só o adiantamento. O preço do lugre fica em torno de vinte mil pesos. Então você vai ter que conseguir o resto do dinheiro sozinho. Além disso, vai precisar de dinheiro para contratar uma tripulação e um navegador.";
			link.l1 = "Ótimo! E como eu vou conseguir isso?";
			link.l1.go = "Mishelle_prisoner_21";
		break;
		
		case "Mishelle_prisoner_21":
			dialog.text = "Não é nenhuma surpresa. Ganhe seu dinheiro. Como mais? Aqui, dinheiro se encontra em cada canto, basta saber onde procurar e não ter medo das dificuldades. Ande pelos estabelecimentos daqui. Converse com o povo local. Com certeza vai encontrar algum tipo de trabalho. Mas tome cuidado, há muito mais vigaristas do que gente honesta. Se você não for uma pessoa honesta, talvez tente roubar algo de valor das casas.";
			link.l1 = "Mas nós somos nobres, certo?";
			link.l1.go = "Mishelle_prisoner_22";
		break;
		
		case "Mishelle_prisoner_22":
			dialog.text = "Títulos não significam nada aqui. Trabalhe, lute, roube como todo mundo. Depois que comprar um barco, contrate uma tripulação. No começo, você não vai conseguir navegar sozinho, então vai precisar de um navegador. Pode conversar sobre tudo isso com o dono da taverna, ele vai te ajudar. E, claro, não se perca. Quando for para o mar, siga direto para Guadalupe...";
			link.l1 = "O que é aquilo? Uma cidade?";
			link.l1.go = "Mishelle_prisoner_23";
		break;
		
		case "Mishelle_prisoner_23":
			dialog.text = "É uma ilha a quase dois dias daqui. Tente conseguir um mapa do arquipélago o quanto antes e decore-o como o 'Pai-Nosso', assim você não vai passar vergonha diante de quem sabe a diferença entre uma cidade e uma ilha. Você vai ter que navegar bastante por essas bandas, então se prepare com antecedência.";
			link.l1 = "Hm. Certo. Então, o que eu faço nessa, ahm... Guadalupe?";
			link.l1.go = "Mishelle_prisoner_24";
		break;
		
		case "Mishelle_prisoner_24":
			dialog.text = "Procure um homem chamado 'Fadey' por lá. Ele tem uma casa perto do cais. Diga que me conhece e peça para ele pagar a dívida — perdeu uma bela quantia para mim num jogo de cartas. O dinheiro que receber vai te ajudar a se reerguer. Use para começar sua vida por aqui.";
			link.l1 = "O que você quer dizer com colocar as coisas em movimento?";
			link.l1.go = "Mishelle_prisoner_25";
		break;
		
		case "Mishelle_prisoner_25":
			dialog.text = "Quero dizer, use esse dinheiro para ganhar ainda mais, e assim por diante. Negociando, por exemplo. Voltaremos a essa conversa depois. Agora você deve cuidar do navio, velejar até Guadalupe, encontrar aquele moscovita gordo e cobrar a dívida dele. Não literalmente, é claro. Fadey é um homem muito respeitado em Guadalupe e amigo pessoal do governador local. Então não faz sentido arrumar confusão. Pelo contrário, tente fazer amizade com ele. Volte para mim assim que tiver o dinheiro. Entendido, irmão?";
			link.l1 = "Entendi. Ah, por quê... O que eu fiz para merecer esse castigo...";
			link.l1.go = "Mishelle_prisoner_26";
		break;
		
		case "Mishelle_prisoner_26":
			dialog.text = "Não se lamente, Charles. Aceite isso como um mal inevitável ou... quem sabe, como uma bênção disfarçada. Mais tarde, você vai agradecer ao destino por sua vida ter tomado esse rumo. Agora, irmão, você finalmente tem a chance de provar que é um homem de verdade. Quem sabe até vire alguém decente...";
			link.l1 = "(INICIAR TUTORIAL)   De novo essa baboseira?";
			link.l1.go = "Mishelle_prisoner_27";
			link.l2 = "(PULAR TUTORIAL) Irmão, não tenho tempo pra isso. Quero pular a parte chata e cair logo no mar aberto. Quanto antes eu tiver um navio, mais cedo você sai desse buraco. Ou prefere ficar aqui mais tempo?";
			link.l2.go = "Mishelle_prisoner_29"; // Addon 2016-1 Jason пиратская линейка 1
		break;
		
		case "Mishelle_prisoner_27":
			dialog.text = "Não, não. Não leve para o lado errado... Tudo bem, Charles, não perca tempo. Você sabe o que fazer. Vou esperar você voltar de Guadalupe como capitão do seu próprio navio, com o dinheiro do Fadey. Boa sorte, irmão. Estou contando com você.";
			link.l1 = "Vou tentar não te decepcionar. Tudo bem, Michel. Até a próxima!";
			link.l1.go = "Mishelle_prisoner_28";
		break;
		
		case "Mishelle_prisoner_28":
			DialogExit();
			pchar.questTemp.Sharlie = "ship";//флаг на старт мини-квестов для сбора денег
			//LocatorReloadEnterDisable("Fortfrance_town", "reload5_back", false);//откроем верфь
			LocatorReloadEnterDisable("Fortfrance_town", "reload4_back", true);// таверна закр
			if(!bHardcoreGame) LocatorReloadEnterDisable("Fortfrance_town", "reload7_back", true);// ЦЕРКОВЬ закр
			LocatorReloadEnterDisable("Fortfrance_town", "reload8_back", true);// ростовщик закр
			LocatorReloadEnterDisable("Fortfrance_town", "reload9_back", true);// бордель закр
			LocatorReloadEnterDisable("Fortfrance_town", "reload91", true);// бордель закр
			LocatorReloadEnterDisable("Fortfrance_town", "reload_jail", true);// тюрьма закр
			bDisableFastReload = false;//open быстрый переход
			SaveCurrentQuestDateParam("questTemp.Sharlie_ship");//запомним дату
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Sharlie", "5");
			//Sharlie_CreateGigoloMan();//мини-квесты на бордель и на джунгли
			AddLandQuestMark(characterFromId("FortFrance_tavernkeeper"), "questmarkmain");
			AddLandQuestMark(characterFromId("FortFrance_trader"), "questmarkmain");
			AddLandQuestMark(characterFromId("FortFrance_PortMan"), "questmarkmain");
			if(CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
			{
				AddLandQuestMark(characterFromId("FortFrance_Mayor"), "questmarkmain");
				QuestPointerToLoc("Fortfrance_town", "reload", "reload3_back");
			}
			QuestPointerToLoc("Fortfrance_town", "reload", "reload6_back");
			/*pchar.quest.CreateGigoloMan.win_condition.l1 = "Hour";
			pchar.quest.CreateGigoloMan.win_condition.l1.start.hour = 17.00;
			pchar.quest.CreateGigoloMan.win_condition.l1.finish.hour = 18.00;
			pchar.quest.CreateGigoloMan.function = "Sharlie_CreateGigoloMan";*/
			/* pchar.quest.SharlieremoveLocks.win_condition.l1 = "HardHour";
			pchar.quest.SharlieremoveLocks.win_condition.l1.hour = 23;
			pchar.quest.SharlieremoveLocks.win_condition.l2 = "location";
			pchar.quest.SharlieremoveLocks.win_condition.l2.location = "FortFrance_Town";
			pchar.quest.SharlieremoveLocks.function = "Sharlie_removeLocks"; */
			//устанавливаем прерывание на джунгли
			pchar.quest.Jungle_jew.win_condition.l1 = "location";
			pchar.quest.Jungle_jew.win_condition.l1.location = "Martinique_jungle_01";
			pchar.quest.Jungle_jew.function = "Junglejew_CreateIndians";
			
			ref location = &Locations[FindLocation(pchar.location)];
			location.first_meeting = true;
			npchar.greeting = "mishelle_3";
			// на гида
			if (GetCharacterIndex("Guide") != -1)
			{
				pchar.quest.Guide_next.win_condition.l1 = "location";
				pchar.quest.Guide_next.win_condition.l1.location = "Fortfrance_town";
				pchar.quest.Guide_next.win_condition = "Guide_next";
			}
		break;
		
		case "Mishelle_prisoner_29": // Addon 2016-1 Jason пиратская линейка 1
			dialog.text = "Heh! Essa 'parte chata' pode salvar sua vida um dia... Enfim. Tem um jeito fácil de conseguir o dinheiro agora mesmo.\nVá até a igreja local e fale com o Abade Benoit. Ele é um velho amigo do nosso pai. Conte a ele sobre a situação, caia de joelhos e implore para que ele te empreste moedas suficientes para comprar um navio.";
			link.l1 = "(PULAR TUTORIAL) Agora sim! Indo falar com o abade.";
			link.l1.go = "Mishelle_prisoner_31";
			link.l2 = "(INICIAR TUTORIAL) Quer que eu comece aumentando ainda mais suas dívidas? Você me acha um idiota, irmão? Dá pra ver que você não pode me ajudar em nada com isso. Então tudo sobra pra mim, é isso.";
			link.l2.go = "Mishelle_prisoner_30";
		break;
		
		case "Mishelle_prisoner_30":
			dialog.text = "Uau! Parece que eu não estava enganado sobre você, irmão. Mal posso esperar pelo seu retorno de Guadalupe como capitão do seu próprio navio, com o dinheiro do Fadey. Boa sorte!";
			link.l1 = "Até mais. Aproveite por aqui.";
			link.l1.go = "Mishelle_prisoner_28";
		break;
		
		case "Mishelle_prisoner_31":
			DialogExit();
			AddLandQuestMark(characterFromId("Benua"), "questmarkmain");
			pchar.questTemp.Sharlie = "ship_fast"; // ускоренный старт
			pchar.questTemp.Sharlie.FastStart = "true";
			LocatorReloadEnterDisable("Fortfrance_town", "reload5_back", false);//откроем верфь
			SaveCurrentQuestDateParam("questTemp.Sharlie_ship");//запомним дату
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Sharlie", "5-1");
			location = &Locations[FindLocation(pchar.location)];
			location.first_meeting = true;
			npchar.greeting = "mishelle_3";
			// на гида
			if (GetCharacterIndex("Guide") != -1)
			{
				pchar.quest.Guide_next.win_condition.l1 = "location";
				pchar.quest.Guide_next.win_condition.l1.location = "Fortfrance_town";
				pchar.quest.Guide_next.win_condition = "Guide_next";
			}
			//DeleteAttribute(pchar, "GenQuest.CannotWait");
			Sharlie_removeLocks("");
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "First time";
		break;
		
		case "trial":
			DelLandQuestMark(npchar);
			dialog.text = "Está tentando dizer que ficou assustado? Não se preocupe, irmão. Está tudo certo. Eu também não me senti nenhum herói na minha primeira batalha no mar. Que bobagem. Em um mês ou dois, esses encontros vão parecer coisa do dia a dia... Já visitou o Fadey?";
			link.l1 = "Eu consegui... Mas com esse tipo de sucesso... Por que eu me dei ao trabalho?";
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "Hm. Por que isso?";
			link.l1 = "Porque ele está numa situação difícil. Foi roubado recentemente e agora está cheio de problemas financeiros. Em vez de dinheiro, ele me ofereceu uma adaga da coleção dele. Disse que é valiosa, que vale até mais do que toda a dívida. Então, aceitei...";
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			dialog.text = "Fadey? Quebrado? Com problemas de dinheiro? Ha-ha-ha! Você me fez rir, meu caro irmão! Aquele maldito moscovita te sacou na hora, viu que você era novato e... ah, aquele desgraçado! Mostra aí a adaga que o velho te deu em troca da dívida dele.";
			if (CheckCharacterItem(pchar, "knife_01"))
			{
				link.l1 = "Aqui está...";
				link.l1.go = "trial_3";
				PlaySound("interface\important_item.wav");
			}
			else
			{
				link.l1 = "Não estou com ela agora. A olho nu, parece só uma adaga comum. O Fadey me disse que ela foi encantada por um xamã indígena e se chama Garra do Chefe.";
				link.l1.go = "trial_4";
			}
		break;
		
		case "trial_3":
			PlaySound("interface\important_item.wav");
			dialog.text = "Hm. Bem, vejamos... Deus vai julgar esse urso gorducho. Uma sucata dessas, Charles, você compraria em qualquer loja por aqui. Ele te passou a perna, aproveitando sua falta de experiência... Aqui, pega esse pedaço de aço de volta. Guarda como lembrança. Pode pendurar acima da sua cama na cabine.";
			link.l1 = "Filho da puta! Ah, que se dane... Vou voltar pra Guadalupe e dar um sacode nesse desgraçado seboso!";
			link.l1.go = "trial_5";
		break;
		
		case "trial_4":
			dialog.text = "Enfeitiçado por um xamã? Garra do Chefe? Sim... tudo certo. Deus vai julgar aquele urso gorducho. Uma porcaria dessas, Charles, você poderia comprar em qualquer loja da esquina. Ele te passou a perna, aproveitando sua falta de experiência... Tentou me contar umas histórias de fadas e eu logo coloquei ele no lugar dele. Então pode pendurar essa garra na sua cabine, acima da cama, como lembrança... Se ainda não jogou fora, é claro.";
			link.l1 = "Filho da puta! Ah, que se dane... Vou voltar pra Guadalupe e dar um sacode nesse desgraçado seboso!";
			link.l1.go = "trial_5";
		break;
		
		case "trial_5":
			dialog.text = "Calma, meu caro irmão, relaxe. Não precisa disso, a menos que queira passar alguns meses numa cela da prisão de Basse-Terre. Esqueceu o que te falei? Aquele urso pomposo é amigo do Claude François de Lyon, o governador da Guadalupe. Assim que eu sair daqui, vou conversar com ele... de coração aberto. Ele não vai a lugar nenhum.";
			link.l1 = "Certo. É melhor você resolver isso com ele... Pelo visto, vou ficar sem o dinheiro inicial prometido?";
			link.l1.go = "trial_6";
		break;
		
		case "trial_6":
			dialog.text = "Parece que sim, Charles. Mas mantenha a cabeça erguida. Quem tem um navio e juízo não se perde no Caribe. E você tem os dois, não é?";
			link.l1 = "O que você está insinuando? Eu fiz besteira com essa adaga, então o que eu deveria...";
			link.l1.go = "trial_7";
		break;
		
		case "trial_7":
			dialog.text = "Calma, meu caro irmão! Por que esse nervosismo todo de repente? Fique tranquilo, assim você vive mais. Não estou insinuando nada. Nem pensei nisso!";
			link.l1 = "Desculpa, Michel. É que eu estou um pouco... bem, tenta me entender também!";
			link.l1.go = "trial_8";
		break;
		
		case "trial_8":
			dialog.text = "Eu entendo. E eu realmente quero te ajudar! Então preste atenção. Você precisa ganhar um pouco de experiência e juntar pelo menos um pouco de dinheiro antes de se meter em coisas mais sérias. Se jogar em aventuras sem a preparação necessária é pedir pra morrer. Não quero que esse lugar acabe com você tão cedo.";
			link.l1 = "Muito inspirador. Que tipo de aventuras você está contando, Michel? Por algum motivo, me perdi nas suas divagações.";
			link.l1.go = "trial_9";
		break;
		
		case "trial_9":
			dialog.text = "Irmão, deixa eu te lembrar que eu, ou melhor dizendo, nós, devemos um milhão de pesos ao de Poincy. Você realmente acha que pode ganhar isso de forma honesta? Claro, dá pra negociar essa quantia, é possível se a sorte sorrir pra você, mas negociar no Caribe está longe de ser um negócio tranquilo também.\nA aventura vai te encontrar, querendo ou não— a questão é: você vai estar pronto quando chegar a hora? É melhor atacar primeiro. Si vis pacem, para bellum, Charles...";
			link.l1 = "De novo com essas palavras difíceis? Fale simples, por favor...";
			link.l1.go = "trial_10";
		break;
		
		case "trial_10":
			dialog.text = "É latim, meu caro irmão. Eu disse: 'Se queres paz, prepara-te para a guerra.' Leve essa frase como uma mentalidade de liderança voltada para a ação. Pode anotar no seu diário de bordo e reler toda manhã depois da oração. Ainda há muito que você precisa aprender e muito a compreender...";
			link.l1 = "Certo, já chega. Cansei dos seus tratados científicos. Vamos direto ao ponto.";
			link.l1.go = "trial_11";
		break;
		
		case "trial_11":
			dialog.text = "I am being specific, you just don't understand yet. Fine. First, you need to get familiar with the archipelago and get used to your new life as captain of a ship. You will have to work hard to ensure your well-being and a wage for your crew. There are many ways to make coin.\nTaking freights and passengers on board are the simplest. Merchants in stores may give you freight contracts and passengers will approach you on the streets themselves. You should also consider checking harbour offices; having a lugger or any fast ship will allow you to earn good money as a courier.\nHarbour masters will provide you with very profitable freight contracts once you acquire a bigger ship. Talk with people, don't boast about your lineage, be friendly and things will go just fine. Visit colony governors, they often offer well-paid work.\nYou may try trading but in that case you should hire a decent purser. Be careful at sea, avoid Spanish military squadrons and warships. If you meet a lone Spanish trader or an unprotected convoy, you may try to capture them.";
			link.l1 = "O quê?! Michel, perdi a audição? Você está sugerindo que eu vire pirata? Você, orgulho da Sociedade, servo de Deus e da Trindade, propõe esse tipo de vida para mim?";
			link.l1.go = "trial_12";
		break;
		
		case "trial_12":
			dialog.text = "Oh, Charles... Eu aconselho você a deixar de lado essa sua frescura de uma vez por todas, aqui ninguém valoriza isso. E quanto à Ordem... não seja ingênuo, irmão. Talvez na Europa o Louvre e o Escorial estejam em alguma espécie de paz, mas aqui é guerra. Qualquer corsário espanhol não vai hesitar em saquear seu navio e enforcar você e sua tripulação no mastro.\nPor isso, ninguém vai te culpar por atacar um navio mercante de uma nação inimiga, pode acreditar. E com uma carta de corso, ainda vai ter apoio oficial das autoridades...";
			link.l1 = "Estou começando a entender seus princípios de vida. Assim como entendo os métodos pelos quais você aparentemente conseguiria 'ganhar' um milhão em meio ano.";
			link.l1.go = "trial_13";
		break;
		
		case "trial_13":
			dialog.text = "E você vai ter que usar esses métodos, Charles. Afinal, isso é apoiado pelas autoridades, seja abertamente ou por debaixo dos panos. Mesmo que você se dedique ao comércio, um dia vai ser obrigado a enfrentar piratas ou invasores espanhóis, porque para eles, você é o prêmio.\nÉ do seu interesse esquecer as ideias que tinha sobre a vida. Confie em mim, irmão, dá pra fazer muita coisa não só sem perder a dignidade, mas também ganhando o favor das autoridades e o carinho do povo.";
			link.l1 = "Você nunca deixa de me surpreender, Michel. Agora está me dizendo para virar pirata. O que vem depois?";
			link.l1.go = "trial_14";
		break;
		
		case "trial_14":
			dialog.text = "Não dramatize demais, Charles. É bem simples: caçar ou ser caçado. Essa é toda a filosofia. Eu prefiro a primeira opção, e gostaria que você seguisse meu exemplo. E não estou dizendo para você virar pirata, mas sim agir militarmente contra uma nação hostil, e só quando houver um bom motivo para isso.";
			link.l1 = "Um benefício, quer dizer?";
			link.l1.go = "trial_15";
		break;
		
		// Rebbebion, небольшое изменение диалога
		case "trial_15":
			dialog.text = "Viu, você entende sim, irmão. Mas chega de conversa. Hora de se provar. Só venha me procurar quando estiver pronto de verdade. Ganhe um bom dinheiro, consiga um navio melhor, conheça o arquipélago e aprimore suas habilidades.\nMas fique atento: se passar os próximos meses em tavernas e bordéis sem aprender nada que preste... nem pense em voltar. Estamos entendidos, Charles?";
			link.l1 = "Não se preocupe. Não vim aqui para me divertir... O que vem depois disso?";
			link.l1.go = "trial_16";
		break;
		
		case "trial_16":
			dialog.text = "Depois eu vou te contar o que fazer depois disso. Já bolei um plano. Você tem um futuro promissor pela frente, Charles, se seguir meus conselhos e recomendações direitinho.";
			link.l1 = "Eu prefiro meu passado modesto a um futuro tão brilhante e grandioso...";
			link.l1.go = "trial_17";
		break;
		
		case "trial_17":
			dialog.text = "Confie em mim, irmão, você ainda vai rir do seu passado inútil e agradecer ao destino por ter te livrado dele. Seja otimista e pense positivo. Você vai adorar essa vida. Vai ver.\nAh, mais uma coisa: faça uma visita ao nosso amigo em comum, o Fadey, e peça pra ele te arrumar um trabalho. O urso tem bons contatos, tenho certeza de que vai encontrar algo pra você. Não demore ou pode perder uma oportunidade. E, por favor, não me decepcione.";
			link.l1 = "Mais lições de moral... Meu Deus, quando isso vai acabar? Tá bom, Michel... Posso ir agora?";
			link.l1.go = "trial_18";
		break;
		
		case "trial_18":
			dialog.text = "Espere. Mais alguns conselhos táticos. Se você se indispor com alguma nação e virar foragido, procure a igreja local e fale com o Abade Benoit. Diga a ele que fui eu quem te enviou. Ele tem contatos tanto entre os papistas quanto entre os calvinistas, e já me ajudou muito com esse tipo de situação mais de uma vez. Mas saiba que isso não é nem fácil nem barato, então tente evitar arranjar inimigos.  Espere, mais uma coisa! Somos nobres, mas é tolice ter aversão a trabalhar com as próprias mãos, especialmente aqui. Você pode fabricar muitos itens úteis, desde que tenha as ferramentas e componentes necessários... Me diga, irmão, como você carrega alguma das suas pistolas?";
			link.l1 = "Hm. Como sempre, uma bala e um pouco de pólvora.";
			link.l1.go = "trial_19";
		break;
		
		case "trial_19":
			dialog.text = "Ha! Eu não esperava ouvir nada diferente.";
			link.l1 = "Você conhece outro jeito, querido irmão?";
			link.l1.go = "trial_20";
		break;
		
		case "trial_20":
			dialog.text = "Claro. Mas poucos fazem isso, por pura ignorância ou simples preguiça. Se você dedicar algumas horas do seu tempo, pode preparar cartuchos de papel com pólvora e balas. Usando esses cartuchos, o tempo de recarga da arma cai pela metade. Impressionado?";
			link.l1 = "Hm. Suponho que sim. É interessante.";
			link.l1.go = "trial_21";
		break;
		
		case "trial_21":
			pchar.alchemy.known = 1;
			AddQuestRecordInfo("Recipe", "cartridge");
			SetAlchemyRecipeKnown("cartridge");
			dialog.text = "Pegue estas instruções para fabricar cartuchos de papel, estude quando tiver um tempo livre e não seja preguiçoso a ponto de não usar o que aprendeu\Espere aí, irmão. Não se esqueça de passar para ver nosso querido governador.";
			link.l1 = "Tem alguma ocasião?";
			link.l1.go = "trial_22";
		break;
		
		// Rebbebion, намёк на "Травлю крысы"
		case "trial_22":
			dialog.text = "Sempre é bom manter contato com os governadores, especialmente quando eles mantêm seus parentes presos em suas ilhas.";
			link.l1 = "Me fale sobre ele.";
			link.l1.go = "trial_23";
		break;
		
		case "trial_23":
			dialog.text = "Nem todo mundo consegue manter o trono da Martinica. Os interesses da Ordem, da Coroa, dos piratas... e um nobre não deve esquecer dos próprios interesses. Se Parquet não fosse tão relaxado e suscetível à tentação, talvez até fizesse Poincy levá-lo a sério.";
			link.l1 = "E de que utilidade eu poderia ser para ele?";
			link.l1.go = "trial_24";
		break;
		
		case "trial_24":
			dialog.text = "Os oficiais sempre têm trabalho para capitães livres. Mas pagam pouco, e só quando se trata de interesses públicos, nunca pessoais. De qualquer forma, não há jeito melhor no Caribe de manter a honra e melhorar as relações com a Coroa do que trabalhando para os governadores. Aproveite a oportunidade, ainda mais agora que Parquet está enfrentando alguns problemas. Que tipo de problemas?";
			link.l1 = "Que tipo de problema?";
			link.l1.go = "trial_25";
		break;
		
		case "trial_25":
			dialog.text = "Me desculpe, irmão. Os interesses da Ordem estão em jogo. Só posso dizer que não somos os únicos procurando maneiras rápidas de enriquecer.";
			link.l1 = "Você está sendo enigmático de novo... Bem, eu passo aqui quando tiver tempo.";
			link.l1.go = "trial_26";
		break;
		
		case "trial_26":
			dialog.text = "Vá agora. Boa sorte, irmão!";
			link.l1 = "Obrigado... Até logo, Michel.";
			link.l1.go = "trial_27";
		break;
		
		case "trial_27":
			DialogExit();
			NextDiag.TempNode = "First time";
			AddDialogExitQuestFunction("Sharlie_Mishelle_OpenWorld");
		break;
		
		case "gambitA":
			dialog.text = "Então faça do seu jeito. Eu acredito em você, irmão. Quando olho pra você agora, simplesmente sei que está mudando para melhor.";
			link.l1 = "É mesmo? Como assim?";
			link.l1.go = "gambit";
		break;
		
		case "gambit":
			dialog.text = "Eu posso ver, meu caro irmão. Consigo ver seu jeito de andar e a expressão no seu rosto. Finalmente, a máscara daquele jovem convencido, que quase me enlouqueceu, desapareceu de você. Sua nova vida claramente já te fez bem.";
			if (sti(pchar.money) >= 1000000)
			{
				link.l1 = "Não sei, irmão, se suas palavras são elogio ou ofensa. Mas vou ser sincero: não me interessa o que você pensa de mim aí de dentro. Já consegui o milhão necessário para quitar sua dívida, então logo você estará livre. Onde posso encontrar o de Poincy?";
				link.l1.go = "gambit_1_1";
			}
			else
			{
				link.l1 = "Não sei dizer, irmão, se suas palavras são elogio ou ofensa. Mas vou ser sincero: não me interessa o que você pensa de mim daí. Tenho um mar, não um monte, de assuntos para resolver, e não tenho tempo para ficar aqui trocando palavras com você. Tem algo importante a dizer? Se não, vou seguir meu caminho...";
				link.l1.go = "gambit_1";
			}
			DelLandQuestMark(npchar);
			DeleteQuestCondition("Sharlie_GambitStage_level_9");
			DeleteQuestCondition("Sharlie_GambitStage_level_12");
			// уберем маркеры, если ФМК не стали проходить
			DelMapQuestMarkCity("Baster");
			DelMapQuestMarkCity("Fortfrance");
			DelMapQuestMarkCity("Charles");
			DelMapQuestMarkCity("Tortuga");
			DelMapQuestMarkCity("Portpax");
			
			if(CharacterIsAlive("FMQG_pass_1"))
			{
				sld = CharacterFromID("FMQG_pass_1");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CharacterIsAlive("FMQM_carpenter"))
			{
				sld = CharacterFromID("FMQM_carpenter");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CharacterIsAlive("FMQN_seafox_1"))
			{
				sld = CharacterFromID("FMQN_seafox_1");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CharacterIsAlive("FMQT_girl"))
			{
				sld = CharacterFromID("FMQT_girl");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CheckAttribute(pchar, "questTemp.FMQP") && pchar.questTemp.FMQP == "begin") 
			{
				DeleteAttribute(pchar, "questTemp.FMQP");
				sld = CharacterFromID("PortPax_waitress");
				DelLandQuestMark(sld);
			}
			if(CharacterIsAlive("FMQG_cureer"))
			{
				sld = CharacterFromID("FMQG_cureer");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CharacterIsAlive("Guide_y"))
			{
				sld = CharacterFromID("Guide_y");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
		break;
		
		case "gambit_1_1":
			dialog.text = "You've managed to put together a million? Well done, Charles, simply impeccable! But unfortunately, Philippe de Poincy is no longer at his residence; he has departed on Society business, off on a secret expedition. So you'll have to wait a little before visiting him.";
			link.l1 = "Dane-se você e seus esquemas secretos! Achei que já teria acabado com tudo isso e voltado pra casa, e agora...";
			link.l1.go = "gambit_1_2";
		break;
		
		case "gambit_1_2":
			dialog.text = "E agora você abriu a chance de ganhar muito mais dinheiro, e não só isso. Irmão, o fato de você ter juntado a quantia exigida pelo velho raposa é impressionante, mas eu não ficaria tão confiante nem tão tranquilo... De Poincy é um sujeito escorregadio, e demonstrou um interesse enorme pela sua modesta pessoa, e...";
			link.l1 = "E agora você está com medo de que um milhão não seja suficiente pra ele?! Ou tem alguma coisa que você não contou da última vez?";
			link.l1.go = "gambit_1_3";
		break;
		
		case "gambit_1_3":
			dialog.text = "Não tenho medo de nada, mas preciso te alertar que Poincy não é um homem simples. Enquanto ele estiver ausente, você tem a chance de conquistar algum prestígio, para que possa falar com ele de igual para igual, e não como um servo diante de um senhor. Por isso, insisto que siga o meu plano, que vou te explicar agora.";
			link.l1 = "Certo. Não adianta chorar pelo leite derramado. Vou me esconder nesse fim de mundo por mais um tempo. De Poincy não vai ficar navegando por aí pra sempre. Me conta logo qual é o seu plano.";
			link.l1.go = "gambit_2";
		break;
		
		case "gambit_1":
			dialog.text = "Oh! Uma resposta admirável. Fico feliz, Charles, que você tenha se tornado um homem. No entanto, não seja tão duro com seu irmão. Aliás, tenho algo para lhe contar. Estava ansioso para nosso reencontro e já elaborei um plano para o que você fará a seguir.";
			link.l1 = "Ótimo. Então me conte tudo.";
			link.l1.go = "gambit_2";
		break;
		
		case "gambit_2":
			dialog.text = "Veja. Claro, o dinheiro tem um papel importante no Caribe, como em qualquer outro lugar, mas ele não resolve tudo. Um homem de sucesso precisa não só de uma bolsa cheia, mas também de contatos amplos e variados — e não com qualquer um, mas com pessoas que realmente importam neste mundo.\nNão importa a nacionalidade ou o status delas. Contatos abrem portas que o dinheiro sozinho não consegue abrir. A combinação de 'dinheiro mais contatos' dá ao homem a coisa mais valiosa do mundo: poder.\nVocê deveria pensar em construir esse tipo de relação, e não vai conseguir isso só fazendo fretes, negociando, praticando pirataria de ocasião ou mesmo ganhando o favor de governadores.";
			link.l1 = "O que você propõe?";
			link.l1.go = "gambit_3";
		break;
		
		case "gambit_3":
			dialog.text = "There are not that many powerful organisations in the Caribbean. One of them is the Dutch West India Company. You can join them. Their headquarters are in Willemstad on Curaçao. The Company often hires third-party captains and offers special long-term contracts to the most useful of them.\nIf you are lucky, you may make a decent career there. I heard that they are experiencing serious trouble now – some English privateer has taken up arms against the Company and is constantly sinking their ships. They can't do anything about him; he is a navy officer, making him too tough for them.\nThey say that he is somehow connected to British military intelligence, and they are very serious people. So, perhaps, taking the side of this captain will be even more profitable for you, but the problem is – I don't know his name, I only know that Antigua is his operational base.\nYou may sail there and ask around. I also heard about some strange organisation which also takes part in this English-Dutch conflict, but I don't know which side they are on. All I know is that the trail leads to Barbados, to Bridgetown...";
			link.l1 = "Então você sugere que eu me aliste com os holandeses, ou que procure um capitão duvidoso ou uma 'organização' ainda mais suspeita?";
			link.l1.go = "gambit_4";
		break;
		
		case "gambit_4":
			dialog.text = "A escolha é sua. De qualquer forma, você não vai ter outro jeito de se aproximar tão rápido das pessoas que decidem o destino dos outros no Caribe e detêm poder de verdade. Espero que você não esteja achando que dois ou três favores para o governador vão te colocar direto na Marinha Real.";
			link.l1 = "Sabe, meu caro irmão. Nunca tive grandes esperanças de seguir carreira militar na marinha francesa. Deus me livre acabar como você, preso numa cela por causa de uma missão fracassada... Tudo bem, entendi. Acho que vou conseguir encontrar o Quartel-General da Companhia Holandesa sem muita dificuldade, mas não faço a menor ideia de como procurar o resto dos envolvidos";
			link.l1.go = "gambit_5";			
		break;
		
		case "gambit_5":
			dialog.text = "Sobre o corsário inglês, você pode perguntar em St. John's, Antígua. Alguém com certeza vai poder te informar. Diga que está procurando trabalho com a frota inglesa. Quanto à 'terceira força', pode conversar com o pessoal de Bridgetown sobre isso. Alguém lá deve ter ligação com essa organização.";
			link.l1 = "O trabalho deles vai ser pelo menos recompensado? A Companhia, esse corsário... Ou vai ser tudo só por causa de 'conexões'?";
			link.l1.go = "gambit_6";			
		break;
		
		case "gambit_6":
			dialog.text = "Charles, você me surpreende. A Companhia Holandesa das Índias Ocidentais lida com somas que até um rei invejaria. O corsário de quem te falei saqueou tantos navios holandeses que já deve estar transbordando de riqueza. E o pessoal daquela 'organização' não tem só muito dinheiro. Eles têm uma verdadeira fortuna.   Trabalhar para eles sempre garante uma bela fatia do bolo. Gente assim joga sempre alto. E se você for esperto, pode jogar seu próprio jogo e ganhar ainda mais.";
			link.l1 = "Certo. Vou pensar nisso e decidir qual é a melhor opção para mim. Tem mais alguma orientação?";
			link.l1.go = "gambit_7";
		break;
		
		case "gambit_7":
			dialog.text = "Sim. Você deveria aprender a usar instrumentos de navegação. Infelizmente, muitos navegadores só conseguem se orientar pela bússola e pelas estrelas, mas não sabem calcular suas coordenadas. E isso é fundamental.\nEntão. Use uma bússola para estimar a latitude. É um instrumento raro e você não vai encontrá-lo à venda, mas pode fabricar um usando dois itens comuns – uma bússola e um astrolábio. Aqui, pegue as instruções.\nCalcular a longitude é um pouco mais complicado. Você vai precisar de um cronômetro certificado. Dá para fazer um a partir de um cronômetro comum de navio, ajustando-o com uma ampulheta. O problema é que esse instrumento só funciona bem por um mês, depois começa a ficar impreciso por causa dos erros.\nUm cronômetro sempre precisa ser reajustado. Ampulhetas podem ser compradas no escritório da Companhia Holandesa das Índias Ocidentais. Também comprei cronômetros lá. Aqui, leve estas instruções.";
			link.l1 = "Obrigado. Vou começar a estudar agora mesmo.";
			link.l1.go = "gambit_8";
		break;
		
		case "gambit_8":
			AddQuestRecordInfo("Recipe", "bussol");
			SetAlchemyRecipeKnown("bussol");
			AddQuestRecordInfo("Recipe", "clock2");
			SetAlchemyRecipeKnown("clock2");
			dialog.text = "Tente conseguir todas essas ferramentas o quanto antes. Todos os capitães experientes e respeitados navegam por latitude e longitude. Você será visto como um novato na arte da navegação até entender o que esses números significam.\nBem, volte para se gabar assim que tiver sucesso nos assuntos que discutimos recentemente. Boa sorte, Charles!";
			link.l1 = "Obrigado, meu querido irmão. Sinto que isso vai ser muito útil!";
			link.l1.go = "gambit_9";
		break;
		
		case "gambit_9":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			pchar.questTemp.Sharlie = "gambit";//флаг на Голландский Гамбит
			pchar.questTemp.HWIC.CanTake = "true"; //Голландский Гамбит доступен для взятия
			AddQuestRecord("Sharlie", "20");
			npchar.greeting = "mishelle_3";
			AddMapQuestMarkCity("Bridgetown", false);
			AddMapQuestMarkCity("Villemstad", false);
			AddMapQuestMarkCity("SentJons", false);
			AddLandQuestMark(characterFromId("Bridgetown_tavernkeeper"), "questmarkmain");
			AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
			// Rebbebion, убираем марки
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Fortfrance");
		break;
		
		case "gambit_fale":
			dialog.text = "E do que você tem para se gabar?";
			link.l1 = "Nada por enquanto. Já encontrei as três organizações e tentei trabalhar com elas, mas, como um charuto, tudo se desfez em fumaça logo no começo. É como se o destino estivesse jogando contra mim...";
			link.l1.go = "gambit_fale_1";			
		break;
		
		case "gambit_fale_1":
			dialog.text = "Então os boatos eram verdade mesmo... Meu caro irmão, o destino não está contra você. Isso se chama mente preguiçosa e mãos desastradas. Você me decepcionou. Volte para a França, não há mais nada para você fazer aqui.";
			link.l1 = "Mas como...";
			link.l1.go = "gambit_fale_2";			
		break;
		
		case "gambit_fale_2":
			dialog.text = "Isso não é mais da sua conta. Eu mesmo vou resolver isso. Tenho outras pessoas mais capazes de me ajudar a resolver meu problema. Tinha medo que confiar em você me prendesse aqui até o fim dos meus dias. Enfim. Vai embora, volta para as suas cortesãs.";
			link.l1 = "Tá bom, vai pro inferno...";
			link.l1.go = "gambit_fale_3";
		break;
		
		case "gambit_fale_3":
			DialogExit();
			NextDiag.CurrentNode = "gambit_fale_4";
			npchar.lifeday = 30;
		break;
		
		case "gambit_fale_4":
			dialog.text = "Não tenho nada para conversar com você. Vá.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "gambit_fale_4";
		break;
		
		case "saga":
			switch(pchar.questTemp.HWIC.Detector)
			{
				case "holl_win": sTemp = "I've entered service with the Dutch West India Company and become a special tasks agent and close friend of the vice administrator of the Company, Lucas Rodenburg. I managed to carry out several serious missions, in particular, I liquidated the actual English privateer. In addition, I've now got my own personal home on Antigua and my pockets are chinking with money."; break;
				
				case "holl_fail": sTemp = "I've entered service with the Dutch West India Company, however matters have gone modestly, I've failed an important task, and was compelled to a dishonorable discharge with nothing."; break;
				
				case "eng_win": sTemp = "I've found the actual English privateer, Richard Fleetwood, and carried out several important tasks in the name of the English navy, in particular, I liquidated the pirate 'ghost ship' and did away with Lucas Rodenburg himself, vice administrator of the Company. In addition, I've now got my own personal home on Antigua and my pockets are chinking with money."; break;
				
				case "eng_win_half": sTemp = "I've found the actual English privateer, Richard Fleetwood, and carried out several important tasks in the name of the English navy, in particular, I liquidated the pirate 'ghost ship'. Of course, Fleetwood departed to England and my service with him is over, but still..."; break;
				
				case "eng_fail": sTemp = "I've entered service with the English privateer from Antigua, however matters have gone modestly, I've failed an important task, and was compelled to a dishonorable discharge with nothing."; break;
				
				case "self_win": sTemp = "I've discovered the 'secret organization' on Barbados, started rolling some game of my own, and achieved quite a bit: I did away with that English privateer, Richard Fleetwood, put Lucas Rodenburg, the vice administrator of the Company, behind bars, become a close friend of governor Matthias Beck and the company's director Peter Stuyvesant. In addition, I've now got my own personal home on Antigua and my pockets are chinking with money."; break;
				
				case "self_fail": sTemp = "I've discovered the 'secret organization' on Barbados, started rolling some game of my own, however it all went down in dust at the moment of truth..."; break;
			}
			dialog.text = "E então? Vamos lá, meu caro irmão, não enrola. Qual é a boa notícia? Chegaram aos meus ouvidos rumores sobre o seu entusiasmo e diligência, mas quero ouvir tudo de você.";
			link.l1 = sTemp;
			link.l1.go = "saga_1";
		break;
		
		case "saga_1":
			if (pchar.questTemp.HWIC.Detector == "holl_win" || pchar.questTemp.HWIC.Detector == "eng_win" || pchar.questTemp.HWIC.Detector == "self_win")
			{
				dialog.text = "Excelente! Muito bem, Charles! Eu não duvidei de você nem por um instante! Você vai longe, meu caro irmão... Se mantendo ocupado assim e fazendo amizade com gente tão importante—bom, eu não esperava por isso. Parabéns!";
			}
			else
			{
				dialog.text = "Não fique chateado, Charles. Se não deu certo, não há nada que você possa fazer. Vamos usar outros meios para conseguir os resultados de que precisamos.";
			}
			link.l1 = "O que faremos agora, Michel? Já é hora de visitar o Chevalier de Poincy? Acho que estou pronto para conversar com ele.";
			link.l1.go = "saga_2";	
		break;
		
		case "saga_2":
			dialog.text = "Você já conseguiu juntar a quantia exigida de um milhão de pesos?";
			if (sti(pchar.money) >= 1000000)
			{
				link.l1 = "Sim, atualmente possuo a quantia necessária.";
				link.l1.go = "saga_3_1";
			}
			else
			{
				link.l1 = "Não, ainda não tenho tanto dinheiro assim.";
				link.l1.go = "saga_3_2";
			}
		break;
		
		case "saga_3_1":
			dialog.text = "Excelente! Então não vou ficar muito mais tempo nessa masmorra... Siga para Capsterville, que fica em Saint Christopher, e peça uma audiência com de Poincy. Ele deve estar no palácio do governador, onde reside. Depois disso, avalie conforme a situação e lembre-se: Poincy é esperto, muito esperto... Tenho um pressentimento ruim de que essa história toda não vai se resolver tão fácil assim. Vá, irmão, e tome cuidado!";
			link.l1 = "Vou lembrar dos seus conselhos, Michel. Fique tranquilo, eu também não nasci ontem. Lá vou eu falar com o velho raposa. Até mais!";
			link.l1.go = "saga_4";			
		break;
		
		case "saga_3_2":
			dialog.text = "Não adianta tentar falar com de Poincy agora. Ele nem vai deixar você entrar. Junte o dinheiro, meu irmão, você já tem experiência suficiente, então não deve ser tão difícil. Navegue para Capsterville, em Saint Christopher, assim que conseguir a quantia. O Chevalier deve estar no palácio do governador. Peça uma audiência e eles vão deixar você entrar. Depois, tire suas próprias conclusões e tome cuidado: de Poincy é astuto, muito astuto... Algo me diz que essa história não vai terminar tão simples assim.";
			link.l1 = "Vou levar suas precauções em conta, Michel. Fique tranquilo, também não nasci ontem. Assim que juntar o dinheiro, vou direto falar com o velho raposa. Até mais!";
			link.l1.go = "saga_4";			
		break;
		
		case "saga_4":
			DialogExit();
			AddMapQuestMarkCity("Charles", false);
			AddLandQuestMark(characterFromId("Puancie"), "questmarkmain");
			npchar.quest.givelink_saga = "true";
			NextDiag.TempNode = "First time";
			pchar.questTemp.Sharlie = "saga";//флаг на Пиратскую Сагу
		break;
		
		case "saga_5":
			dialog.text = "Sacré bleu! Era exatamente isso que eu temia. Poincy está no seu encalço faz tempo, Charles. Por isso ele anda tão interessado em você! Você já fez seu nome no Caribe, e agora ele resolveu te usar para cumprir tarefas que deram errado...";
			link.l1 = "Tenho a impressão, Michel, de que você sabia muito bem e só não quis me avisar antes. Está tudo dando certo demais... Primeiro o dinheiro, agora o seu trabalho... Isso não acontece por acaso.";
			link.l1.go = "saga_6";
		break;
		
		case "saga_6":
			dialog.text = "Charles, não procure por mensagens secretas onde elas não existem. Se ao menos você tivesse dado o dinheiro ao Poincy no primeiro dia em que chegou... Bem, quero dizer, se você tivesse esse dinheiro. O Chevalier não teria pedido mais nada a você. Mas agora que ele se interessou por você, viu como você se adaptou rápido aqui e tudo o que conseguiu conquistar, decidiu aproveitar os seus talentos.";
			link.l1 = "Certo... porque seus talentos já não o satisfazem mais, não é? Merda! Tudo bem. Vejo que cheguei a um beco sem saída aqui. Quem é esse herege? Como posso encontrá-lo?";
			link.l1.go = "saga_7";
		break;
		
		case "saga_7":
			dialog.text = "Não precisa procurá-lo! Ele nunca sai de Tortuga e permanece sob a proteção do bastião que construiu e das hordas de huguenotes leais que servem como soldados em sua guarnição. Por isso, todo soldado é fiel a ele. Poincy se referia a François Levasseur, o governador de Tortuga.\nOs espanhóis ainda não conseguiram tirá-lo de lá, e de Poincy realmente acreditou que eu conseguiria fazer isso sozinho, sem nenhum apoio da marinha, apenas porque iniciar uma guerra civil seria um erro político grave devido à proximidade da guarnição de Santo Domingo.\nO velho canalha está preocupado demais com sua carreira impecável e a aposentadoria que se aproxima para arriscar tudo assim. Mesmo assim, Levasseur foi longe demais e agora representa um perigo para a coroa.\nDe Poincy, que nomeou Levasseur para o cargo atual, considera esse temido huguenote um inimigo pessoal e está ansioso para substituí-lo pelo Cavaleiro Maltês de Fontenay, meu superior imediato sob cujo comando cheguei aqui vindo de Malta.";
			link.l1 = "Glorioso! Primeiro, faça um milhão, depois assassine o governador de Tortuga. Qual será minha próxima missão? Organizar uma conspiração no Escorial? Droga! Não me surpreende que você tenha estragado aquilo. Derrubar o governador não é como roubar mercadores espanhóis. Espero que você pelo menos tivesse algum plano quando jurou tirar as castanhas do fogo?";
			link.l1.go = "saga_8";
		break;
		
		case "saga_8":
			dialog.text = "Para ser totalmente sincero, eu não tinha nenhum plano, já que de qualquer forma pretendia deixar o serviço e voltar para a mansão da família se minha aposta arriscada desse certo. Pessoalmente, não estou nem aí para os problemas do de Poincy.\nCom certeza, ele teria ficado muito mais maleável assim que visse o ouro dos índios... Bem, por enquanto ele tem todas as cartas na mão contra nós. Acho que vou ficar por aqui enquanto Levasseur for o governador de Tortuga.";
			link.l1 = "E por que os malteses, liderados por de Fontenay, com os olhos na cadeira de governador, não invadiriam eles mesmos Tortuga?";
			link.l1.go = "saga_9";
		break;
		
		case "saga_9":
			dialog.text = "Imagine só. A Ordem declarar guerra a Luís? Não seja ridículo! Um escândalo desses está fora de cogitação. Só um particular pode tomar Tortuga. Um pirata, ou um aventureiro católico como você.\nDepois, ele pode entregar a ilha ao novo governador que de Poincy vai mandar. Um ato desses vai parecer ótimo aos olhos dos grandes políticos.";
			link.l1 = "Então, faz algum sentido negociar com piratas?";
			link.l1.go = "saga_10";
		break;
		
		case "saga_10":
			dialog.text = "O problema é que Levasseur tem autoridade sobre muitos piratas da Irmandade e até além. Ele permite que eles se escondam atrás das baterias de Tortuga e vendam livremente o que saqueiam, ficando com uma parte do butim.\nEle costumava dividir com de Poincy, mas não faz mais isso. Os navios piratas vão proteger Tortuga e sua guarnição, o que torna ainda mais difícil tomar o forte de assalto.";
			link.l1 = "Você acha que essa questão está perdida?";
			link.l1.go = "saga_11";
		break;
		
		case "saga_11":
			dialog.text = "There is always a solution, little brother. It is just not always visible on the surface. Not all pirates are sympathetic to the Huguenots of Tortuga. I know at least two influential pirates who consider Levasseur a traitor and scum. I am talking about Steven Dodson, also known as the Shark, and the legendary baron of Mosquito Bay, Jan Svenson.\nI don't know where to find the Shark; I've heard rumours that something happened and he had to leave his base at Isla Tesoro. But you can always find Svenson in Blueweld. He is a significant figure there.";
			link.l1 = "Você acha que esse... Svenson vai me ajudar?";
			link.l1.go = "saga_12";
		break;
		
		case "saga_12":
			dialog.text = "Ele vai, se você ajudar. As coisas não estão indo muito bem para ele no momento, e o homem está precisando de gente leal e talentosa. Primeiro, você vai ter que mostrar o seu valor antes de conseguir uma conversa séria com ele. Quando chegar lá, vai encontrar um jeito de fazer isso. Daqui, é difícil te aconselhar.\nImagino que você já decidiu seguir em frente, Charles, já que continua fazendo perguntas?";
			link.l1 = "Veja, Michel, acabei de entregar um monte do meu próprio prata para o de Poincy. Juntei isso com muito suor, sangue e lágrimas! Não tenho certeza se você teria arriscado nem um único louis d'or por mim se estivesse no meu lugar.";
			link.l1.go = "saga_13";
		break;
		
		case "saga_13":
			dialog.text = "Charles...";
			link.l1 = "Não me interrompa! Seria uma tolice voltar para o pai de mãos vazias. O problema ainda não está resolvido, você está atrás das grades e corre o risco de ser condenado por traição à Sociedade. Poincy não hesitaria em manchar o nome Monper se eu não cumprir o 'pedido' dele. Dava para ver isso na cara dele. Então, vou partir para Blueweld para tentar encontrar um jeito de me aproximar do Svenson. Enquanto isso, pense bem no que mais você 'esqueceu' de me contar. Por exemplo, é a primeira vez que ouço falar desse ouro indígena que você deveria ter levado para o de Poincy.";
			link.l1.go = "saga_14";
		break;
		
		case "saga_14":
			dialog.text = "There are things that are better left hidden. You are right, I didn't tell you everything I know. Perhaps, one day I will tell you more, but not before you deal with Levasseur; it would be useless knowledge for now.\nI have no doubt that your touching concern for me is motivated only by your wish to save the honour of our family. By saving me, you are saving yourself first and foremost, and secondly, your chance to visit the finest houses in Paris. Am I wrong?";
			link.l1 = "Receio que já não seja mais assim, irmão. Você estava certo. Esses meses que passei no Caribe mudaram cada fibra do meu ser e toda a minha visão de mundo. E tenho certeza de que foi para melhor. Já não preciso mais daqueles salões parisienses e um dia vou conseguir seguir em frente sem o nome Monper. De Maure não é nada pior...";
			link.l1.go = "saga_15";
		break;
		
		case "saga_15":
			dialog.text = "...";
			link.l1 = "E agora, o que realmente me dói é saber que a sua desgraça vai manchar o nome do nosso velho pai. Ele não faz ideia da situação real ou do que está acontecendo aqui. Além disso, como você mesmo disse, é preciso recuperar o patrimônio da família que está em ruínas. E o milhão pago pela sua liberdade esvaziou consideravelmente meus cofres, então certamente vou precisar reabastecê-los.";
			link.l1.go = "saga_16";
		break;
		
		case "saga_16":
			dialog.text = "Você aprendeu muito bem todas as lições da vida, Charles. Fico realmente feliz por você. E também estou contente que você aceitou o pedido de de Poincy em vez de voltar para a França. Espero que tudo dê certo para você e que consiga realizar o que eu mesmo não consegui.";
			link.l1 = "Receio que não tenho escolha. Desde o meu primeiro dia no Caribe, venho fazendo tudo sozinho. Até logo, Michel. Acho que nosso próximo encontro já vai trazer a ordem para sua libertação.";
			link.l1.go = "saga_17a";

		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		case "saga_17a":
            dialog.text = "Espere um pouco! Antes de procurar o Jan Svenson, não deixe de visitar o Marcus Tyrex – ele é o Guardião do Código. Ele comanda La Vega, em Hispaniola. Entre os piratas, sua autoridade não tem limites, e os espanhóis morrem de medo dele.";
			link.l1 = "Será que ele poderia me ajudar com o nosso assunto?";
			link.l1.go = "saga_17b";
		break;
		
		case "saga_17b":
            dialog.text = "Doubt it. I can't really tell which side he's on; most likely, he stands only for himself. You will need the Shark and Svenson anyway, but at this moment, Tyrex is the most powerful pirate out here. They elected him as the Code Keeper for a reason. You shouldn't ignore such an important figure. It could prove useful to get to know the pirates better before you meet Svenson. You may even make a name for yourself among them...";
			link.l1 = "E lá vamos nós de novo com essa conversa de pirata. Não tem jeito de escapar disso, né? Muito bem. Vou fazer uma visita a ele.";
			link.l1.go = "saga_17c";
		break;
		
		case "saga_17c":
            dialog.text = "Ser pirata e fazer negócios com eles são duas coisas completamente diferentes, irmão. Espero que você perceba a diferença. Vá até La Vega e peça um trabalho ao Tyrex. Se vocês dois não se derem bem, esqueça-o e volte para mim.";
			link.l1 = "Muito bem, Michel. Até logo!..";
			link.l1.go = "saga_17d";
		break;
		
		case "saga_17d":
            DialogExit();
			AddQuestRecord("Sharlie", "22");
			npchar.greeting = "mishelle_3";
			pchar.questTemp.Mtraxx = "to_lavega";
			pchar.questTemp.Saga = "pirate_line";
			AddLandQuestMark(characterFromId("Terrax"), "questmarkmain");
			AddMapQuestMarkCity("LaVega", false);
		break;
		
		case "saga_17e":
            dialog.text = "Pelo menos você tentou. Teve a chance de 'conhecer' um barão pirata famoso. Deixa pra lá. Vá até Jan Svenson, ele está em Blueweld. Tente fazer dele seu aliado, ou nossos negócios com Levasseur vão acabar em banho de sangue.";
			link.l1 = "Certo. Estou a caminho.";
			link.l1.go = "saga_17";
			pchar.questTemp.Mtraxx = "fail_end";
		break;
		
		case "saga_17f":
            dialog.text = "Que bom que você parou, irmão. Já te disse uma vez: ser pirata é uma coisa, fazer negócios com eles é outra bem diferente. E você se perdeu no caminho. Espero que não cometa o mesmo erro com o Tubarão e o Svenson. Faça o trabalho, mas mantenha distância deles. Você é um nobre francês, afinal, então esteja acima deles. Agora vá até Jan Svenson, ele está em Blueweld. Tente fazer dele um aliado, ou nossos negócios com Levasseur vão acabar em banho de sangue.";
			link.l1 = "Certo. Estou a caminho.";
			link.l1.go = "saga_17";
			pchar.questTemp.Mtraxx = "fail_end";
		break;
		
		case "saga_17g":
            dialog.text = "Fico muito feliz em ouvir isso, se estiver dizendo a verdade. Mas será que posso mesmo confiar na palavra de um pirata que queima cidades, mesmo que sejam espanholas, e mata civis, inclusive mulheres?";
			// belamour legendary edition -->
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Choice"))
			{
				if(pchar.questTemp.Mtraxx.Retribution.Choice == "good")
				{
			link.l1 = "Pare... Eu realmente sinto muito pelo que fiz enquanto estava com Tyrex. Eu vi o inferno com meus próprios olhos, irmão... Não, acabou! Estou fora da pirataria e não há chance de eu voltar para La Vega. Vou fazer o que for preciso para recuperar meu bom nome.";
			link.l1.go = "saga_17gx";
				}
				if(pchar.questTemp.Mtraxx.Retribution.Choice == "bad")
				{
					link.l1 = "Acredite se quiser. Quem está atrás das grades é você, não eu.";
					link.l1.go = "saga_17gxa";
				}
			}
			else //заглушка
			{
				link.l1 = "Pare com isso... Eu realmente me arrependo das abominações que cometi enquanto trabalhava com Tyrex. Eu vi o inferno com meus próprios olhos, irmão! .. Não, meus dias de pirata acabaram! Não estou mais em La Vega. Vou fazer de tudo para recuperar meu bom nome.";
				link.l1.go = "saga_17gx";
			}
		break;
		
		case "saga_17gxa":
            dialog.text = "Ah, meu irmão... Não provoque a ira de Deus... Espero que isso não se repita com Svenson e Shark. Faça o que for preciso, mas mantenha distância e lembre-se de que tipo de gente eles são. Não é digno de um nobre francês se igualar a eles. Seja melhor do que isso. Agora vá até Jan Swenson em Blueweld e tente encontrar uma forma de se aproximar do velho corsário. Sem ele, não será possível resolver a questão com Levasseur sem derramamento de sangue.";
			link.l1 = "Certo. Não vou demorar.";
			link.l1.go = "saga_17";
			pchar.questTemp.Mtraxx = "full_complete_end";
		break;

		case "saga_17gx":
            dialog.text = "Você vai ter que se esforçar muito, irmão. Lembra do que te falei uma vez? Ser pirata é uma coisa, fazer negócios com eles é outra bem diferente. Você... Deixa pra lá, só espero que não cometa o mesmo erro com o Tubarão e o Svenson. Faça o que precisa, mas mantenha distância deles. Você é um nobre francês, afinal, então esteja acima deles. Agora vá até Jan Svenson, ele está em Blueweld. Tente fazê-lo seu aliado, ou nossos negócios com Levasseur vão acabar em banho de sangue.";
			link.l1 = "Certo. Estou indo.";
			link.l1.go = "saga_17";
			pchar.questTemp.Mtraxx = "full_complete_end";
		break;
		
		case "saga_17":
			DialogExit();
			AddQuestRecord("Sharlie", "22_1");
			pchar.questTemp.Saga = "blueveld";
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", true); // закрыть кабинет Свенсона
			npchar.greeting = "mishelle_3";
			if(CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince"))
			{
				DeleteAttribute(pchar, "questTemp.Mtraxx.CharleePrince");
				SetFunctionTimerCondition("DelCharleePrince", 1, 0, 0, false);
			}
			AddMapQuestMarkCity("SantaCatalina", false);
			AddLandQuestMark(characterFromId("SantaCatalina_tavernkeeper"), "questmarkmain");
			AddLandQuestMark(characterFromId("JS_girl"), "questmarkmain");
		break;
		
		case "Base_fight":
			dialog.text = "Agora não é hora para conversa, irmão! O inimigo está no nosso refúgio!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Base_fight";
		break;
		
		case "Base_afterfight":
			sTemp = "";
			// belamour legendary edition фикс проверки мундира с мушкетом
			if(IsUniformEquip()) sTemp = "I see you've become a captain of the navy... I didn't see that coming to be honest. I truly congratulate you!";
			dialog.text = "Você chegou na hora certa, meu querido irmão! Estou tão feliz em te ver! Esses malditos castelhanos já tomaram conta de Saint-Pierre completamente. Achei que estávamos perdidos, de verdade! "+sTemp+"";
			link.l1 = "Ainda não estamos fora de perigo, a cidade está limpa mas os canalhas se entrincheiraram no forte e há um enorme esquadrão liderado por um navio de guerra. Mas trago uma notícia realmente maravilhosa: Michel, você está livre!";
			link.l1.go = "Base_afterfight_1";
		break;
		
		case "Base_afterfight_1":
			dialog.text = "Não acredito no que estou ouvindo! Será possível? Liberdade?!";
			link.l1 = "Levasseur está morto, Tortuga agora é comandada pelo seu antigo chefe, e o velho raposa Poincy retirou todas as acusações contra você. De agora em diante, nada ameaça o nosso bom nome.";
			link.l1.go = "Base_afterfight_2";
		break;
		
		case "Base_afterfight_2":
			dialog.text = "Eu duvidei até o último instante... Você me surpreendeu, Charles, e conseguiu onde eu sofri um fracasso angustiante.";
			link.l1 = "Audaces fortuna juvat, irmão... Como pode ver, agora também sei latim. Onde está a chave da sua cela?";
			link.l1.go = "Base_afterfight_3";
		break;
		
		case "Base_afterfight_3":
			dialog.text = "A chave da minha cela deve estar na mesa do oficial de serviço. Procure por lá. Talvez tenha caído no chão e escorregado para algum lugar...";
			link.l1 = "Vou procurá-los e já volto!";
			link.l1.go = "Base_afterfight_4";			
		break;
		
		case "Base_afterfight_4":
			DialogExit();
			pchar.questTemp.Sharlie.DefendSP.SeekKey = true;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Base_afterfight_6":
			dialog.text = "Enfim - liberdade! Esperei tanto por este momento!";
			link.l1 = "Você não faz ideia de quanto tempo eu esperei por isso também! Michel, conseguimos reunir alguns homens para reagir?";
			link.l1.go = "Base_afterfight_7";			
		break;
		
		case "Base_afterfight_7":
			dialog.text = "O que você tem em mente, Charles?";
			link.l1 = "A ameaça representada pelos espanhóis ainda não desapareceu. Quero expulsá-los do forte e depois unir forças para atacar o esquadrão por terra e mar! Usando os canhões do bastião, vou conseguir enfrentar o navio de guerra!";
			link.l1.go = "Base_afterfight_8";			
		break;
		
		case "Base_afterfight_8":
			dialog.text = "Temos gente. Muitos cavaleiros foram proteger o palácio do governador. Com certeza vamos encontrar alguém na cidade... Vou reunir todos que eu conseguir. Te vejo além dos portões da cidade!";
			link.l1 = "...";
			link.l1.go = "Base_afterfight_9";			
		break;
		
		case "Base_afterfight_9":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetCheckMinHP(npchar, 10, true, ""); // скрытое бессмертие
			LAi_SetHP(npchar, 500, 500);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 30.0);
			pchar.quest.DefendSP_base2.win_condition.l1 = "location";
			pchar.quest.DefendSP_base2.win_condition.l1.location = "FortFrance_Town";
			pchar.quest.DefendSP_base2.function = "DefendSP_CloseTown";
			AddQuestRecord("Sharlie", "36");
		break;
		
		case "Fort_attack":
			dialog.text = "Aqui está, irmão, nosso exército. Todo mundo que consegui reunir. Não somos muitos, mas vamos lutar pela nossa pátria! Vamos expulsar esses malditos invasores do forte! O elemento surpresa está do nosso lado – eles não esperam nosso ataque. Avante!";
			link.l1 = "Dulce et decorum est pro patria mori! Avante!";
			link.l1.go = "Fort_attack_1";
		break;
		
		case "Fort_attack_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			for (i=1; i<=7; i++)
			{
				sld = CharacterFromID("DefendSP_frafort_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload2_back", false);
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload1_back", true);
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload3", true);
			pchar.quest.DefendSP_fort2.win_condition.l1 = "location";
			pchar.quest.DefendSP_fort2.win_condition.l1.location = "FortFrance_fort";
			pchar.quest.DefendSP_fort2.function = "DefendSP_FortBattle";
			locations[FindLocation("FortFrance_fort")].QuestCapture = true;
		break;
		
		case "Fort_attack_2":
			dialog.text = "Está feito, irmão! O forte é nosso!";
			link.l1 = "É uma pena que tenha sofrido tanto na batalha contra o esquadrão espanhol... mas ainda está bem capaz de liderar uma luta.";
			link.l1.go = "Fort_attack_3";			
		break;
		
		case "Fort_attack_3":
			dialog.text = "Vou fazer a minha parte. Vamos carregar os canhões e dar um golpe pesado no inimigo! Mas só depois de vermos o seu esquadrão se aproximando, senão o navio de guerra vai nos reduzir a pó num instante.";
			link.l1 = "Reúna o pessoal, Michel! Estou indo direto para a praia!";
			link.l1.go = "Fort_attack_4";			
		break;
		
		case "Fort_attack_4":
			dialog.text = "Charles, lembre-se: a parte mais perigosa do esquadrão é o navio de linha! Tente derrubá-lo primeiro. Nós também vamos concentrar o fogo nele com o que restou da bateria do forte.";
			link.l1 = "Certo, irmão. Talvez eu devesse capturá-la.";
			link.l1.go = "Fort_attack_5";			
		break;
		
		case "Fort_attack_5":
			dialog.text = "Pelo que vejo, não sou eu quem deveria estar te ensinando. Agora, vamos parar de perder tempo!";
			link.l1 = "...";
			link.l1.go = "Fort_attack_6";			
		break;
		
		case "Fort_attack_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1);
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload1_back", false);
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload3", false);
			LocatorReloadEnterDisable("Shore38", "boat", false); // выпустить в море
			// закрываем городские заведения
			for (i=3; i<=10; i++)
			{
				LocatorReloadEnterDisable("FortFrance_town", "reload"+i+"_back", true);
			}
			LocatorReloadEnterDisable("FortFrance_town", "reload91", true);
			LocatorReloadEnterDisable("FortFrance_town", "reload_jail", true);
			pchar.quest.DefendSP_fort3.win_condition.l1 = "location";
			pchar.quest.DefendSP_fort3.win_condition.l1.location = "shore38";
			pchar.quest.DefendSP_fort3.function = "DefendSP_BeforeSeaBattle";
			pchar.quest.DefendSP_sea1.win_condition.l1 = "location";
			pchar.quest.DefendSP_sea1.win_condition.l1.location = "Martinique";
			pchar.quest.DefendSP_sea1.function = "DefendSP_SeaBattle";
			AddQuestRecord("Sharlie", "37");
		break;
		
		case "Victory":
			dialog.text = "Glória vitoriosa! Parabéns pela vitória, irmão! Você foi magnífico! Os espanhóis foram completamente destruídos!";
			link.l1 = "Espero que isso os faça pensar duas vezes antes de atacar colônias francesas.";
			link.l1.go = "Victory_1";			
		break;
		
		case "Victory_1":
			dialog.text = "Agora me diga, Charles: quanto vale sua vida passada... comparada a esta?";
			link.l1 = "Nem me lembre...";
			link.l1.go = "Victory_2";			
		break;
		
		case "Victory_2":
			dialog.text = "Você se lembra do que eu te disse quando nos encontramos aqui pela primeira vez? 'Você vai adorar essa vida', foi isso! Sim, e um enorme obrigado a você, irmão, pela sua ajuda. Sem você, eu provavelmente nunca teria conseguido escapar daquele maldito esconderijo subterrâneo.";
			link.l1 = "Não foi nada, Michel. Você é meu irmão, afinal de contas, e eu tinha obrigação de te ajudar.";
			link.l1.go = "Victory_3";			
		break;
		
		case "Victory_3":
			dialog.text = "Just look at you, brother, I am impressed: so much strength in your eyes, confidence in your movements, stature in your posture... where did that wretched artist and court jester go? Indeed! You have surpassed my boldest expectations; truth be told, I never thought that you would become... this.\nIt even... frightens me a little. Because you will stop at nothing to achieve your goal. You are good, too good...";
			link.l1 = "Por algum motivo, estou tendo dificuldade para te entender de novo. Você está chateado comigo outra vez?";
			link.l1.go = "Victory_4";			
		break;
		
		case "Victory_4":
			dialog.text = "Não! Do que você está falando?... De jeito nenhum! Eu só estava deixando a empolgação escapar.";
			link.l1 = "Certo. Então, o que vai fazer agora, irmão? Vai continuar servindo à Sociedade? Ou vai voltar para o nosso patrimônio? Ah, e quase me esqueci: você prometeu me contar uma coisa.";
			link.l1.go = "Victory_5";			
		break;
		
		case "Victory_5":
			dialog.text = "Sobre o quê exatamente?";
			link.l1 = "Sobre o seu serviço para o de Poincy. Sobre um ouro indígena que você deveria ter trazido para ele. Sobre tudo o que te levou à prisão. Tem muita coisa que você ainda não conseguiu me contar, Michel, me deixando praticamente no escuro. Então...";
			link.l1.go = "Victory_6";			
		break;
		
		case "Victory_6":
			dialog.text = "Brother, I remember exactly what I said. I will tell you everything. But not in the middle of a burning city!\nWe both have plenty to do now. You need to settle your squadron, repair it, and get the ships ready again. The governor and I will organise and calm the locals.\nWe will discuss everything tomorrow morning over a glass of good French wine. Trust me, brother, I have a big plan. A truly big one. But not now. Visit Abbot Benoit tomorrow at nine a.m. I will spend the night at his place; he is an old friend of mine.";
			link.l1 = "Certo, Michel. Então está combinado. Vou esperar pela nossa conversa amanhã.";
			link.l1.go = "Victory_7";			
		break;
		
		case "Victory_6A":
			dialog.text = "Диалог 28.";
			link.l1 = "Está certo, Michel. Então ficou combinado. Vou esperar ansioso pela nossa conversa amanhã.";
			link.l1.go = "Victory_7";
		break;
		
		case "Victory_7":
			dialog.text = "Não precisa se despedir, Charles!";
			link.l1 = "...";
			link.l1.go = "Victory_8";			
		break;
		
		case "Victory_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "DefendSP_OpenExit", -1);
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			AddQuestRecord("Sharlie", "39");
			pchar.quest.DefendSP_final.win_condition.l1 = "Timer";
			pchar.quest.DefendSP_final.win_condition.l1.date.hour  = 9;
			pchar.quest.DefendSP_final.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.DefendSP_final.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.DefendSP_final.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.DefendSP_final.function = "DefendSP_finaltalk";
			// раздача экспы
			ChangeCharacterNationReputation(pchar, FRANCE, 30);
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeCharacterComplexReputation(pchar, "fame", 15);
			ChangeOfficersLoyality("good_all", 10);
			AddComplexSeaExpToScill(500, 500, 500, 500, 500, 500, 0);
			AddComplexSelfExpToScill(300, 300, 300, 300);
			AddCharacterExpToSkill(pchar, "Leadership", 2000);
			AddCharacterExpToSkill(pchar, "Fortune", 1000);
			AddSimpleRumour("All those residing in the French colony owe you, Captain. Defending Saint-Pierre from the vile attack of the Spanish is quite a feat!", FRANCE, 30, 15);
			AddSimpleRumour("It's an honor for me to speak with the brave Captain that has beaten a bunch of Spanish invaders hollow!", FRANCE, 30, 15);
			AddSimpleRumour("The French colonists may sleep in peace, while brave naval officers such as you are at the King's service!", FRANCE, 30, 15);
			AddSimpleRumourCity("We are all forever indebted to you, Captain! You have saved our colony from devastation!", "FortFrance", 30, 15, "");
			AddSimpleRumourCity("You are a brave and astute naval officer. All those residing in Saint-Pierre are praying for you, know that!", "FortFrance", 30, 15, "");
			AddSimpleRumourCity("You are the pride and joy of our nation and the hero of Saint-Pierre. We will never forget that!", "FortFrance", 30, 15, "");
			npchar.greeting = "mishelle_0";
		break;
		
		case "kukulkan":
			PlaySound("Voice\English\sharlie\mishelle-04.wav");
			dialog.text = "Então nos encontramos de novo, "+pchar.name+". Apesar dos meus avisos, você ainda assim continuou me procurando, e sua busca te levou para muito, muito longe...";
			link.l1 = "Michel?... Por alguma razão, não estou surpreso. Miguel Dichoso voltou a Tayasal atrás de mais um monte de tesouros? Hm-hm-hm. Sim, eu estava mesmo querendo encontrar você, meu caro irmão. Estava morrendo de vontade de encarar esses seus olhos sem vergonha. E ainda por cima, sua tentativa de me matar no túmulo do cemitério foi a cereja do bolo. Mas antes, me diga: como devo te chamar? Michel de Monper ou Miguel Dichoso?";
			link.l1.go = "kukulkan_1";			
		break;
		
		case "kukulkan_1":
			dialog.text = "Esses nomes já não têm mais importância, "+pchar.name+". Tudo isso ficou no passado, que em breve vai desaparecer até mesmo dos registros da história. Agora é o momento da verdade, para o qual venho me aproximando lentamente há um longo quarto de século, desde que pisei em terra firme pela primeira vez...";
			link.l1 = "O quê?!! Isso... isso não pode ser!!!";
			link.l1.go = "kukulkan_2";			
		break;
		
		case "kukulkan_2":
			dialog.text = "Sim, "+pchar.name+". Vejo pela sua expressão que você entende quem eu sou, mas não consegue acreditar. Sou aquele que você desejou encontrar nestes últimos meses. Aquele com quem o representante do seu Deus, o Inquisidor de Santiago, te abençoou para a batalha.";
			link.l1 = "Kukulcan?!";
			link.l1.go = "kukulkan_change";			
		break;
		
		case "kukulkan_change":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Kanek");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.7);
		break;
		
		case "kukulkan_3":
			dialog.text = "Concordo. "+pchar.name+", é difícil de acreditar. A vida é mais complicada e mais surpreendente do que qualquer conto de fadas...";
			link.l1 = "Eu estava pronto para tudo, mas... meu irmão!";
			link.l1.go = "kukulkan_4";			
		break;
		
		case "kukulkan_4":
			dialog.text = "Irmão? Só pelo sangue do nosso pai. Temos mães diferentes, "+pchar.name+"Saiba que minha mãe era filha de Kanek, chamada Shochikezhal. Ela foi raptada por corsários franceses sob o comando do famoso Nicolas Gotier, depois que saiu de Tayasal de forma imprudente. Eles decidiram escravizá-la. Entre eles estava um homem chamado Serge Benoit. Envergonhado pelo ato de seu capitão, ele o abandonou, tornou-se monge e agora você o conhece como Abade Benoit. Henri de Monper, nosso pai, era oficial da marinha naquela época. Ele comprou Shochikezhal e a levou para a França, onde ela me deu à luz. Mais ou menos na mesma época, você também nasceu, "+pchar.name+". Sua mãe morreu no parto, e nosso pai declarou que sua esposa legítima havia dado à luz gêmeos.\nShochikezhal, minha mãe, tornou-se nossa ama de leite. Você foi alimentado com o leite de uma índia do povo Itza, "+pchar.name+"! Depois, sua avó materna decidiu cuidar da sua educação, e você passou a usar o nome da sua mãe - de Maure.";
			link.l1 = "Como você descobriu tudo isso?!";
			link.l1.go = "kukulkan_5";			
		break;
		
		case "kukulkan_5":
			dialog.text = "Você não acha, irmão, que eu sei mais do que a maioria das pessoas? Além disso, nosso pai já me contou muita coisa e estou por dentro de muita coisa... É como dizem, vou levando na base da improvisação.";
			link.l1 = "Agora tudo faz sentido... E o que aconteceu com sua mãe? Por que nunca a vi?";
			link.l1.go = "kukulkan_6";			
		break;
		
		case "kukulkan_6":
			dialog.text = "Ela morreu salvando minha vida. Pouco mais de um ano após o meu nascimento, quase morri de uma doença. Minha mãe, filha de um sacerdote Itza, realizou para mim uma cerimônia secreta de cura maia. Eu me recuperei, mas essa cerimônia trouxe alguns... efeitos colaterais destrutivos na forma de trovões, relâmpagos e um furacão tropical. Shochikezhal foi denunciada, acusada de feitiçaria e queimada na fogueira pela Inquisição...";
			link.l1 = "E você melhorou...";
			link.l1.go = "kukulkan_7";			
		break;
		
		case "kukulkan_7":
			dialog.text = "Além de me curar, esse ritual também me concedeu outras habilidades, além de abrir uma conexão com o mundo dos deuses. E o resto você já sabe. Como já disse, vou levar a luz do conhecimento e da experiência da raça branca para o passado e transmiti-la ao povo Maia. A história será reescrita e vocês, brancos, não dominarão este mundo. Eu vou garantir isso.";
			link.l1 = "Então toda a sua vida, estudando na melhor academia naval, servindo no exército e na Ordem de Malta, foi basicamente só um acúmulo de experiência militar?";
			link.l1.go = "kukulkan_8";			
		break;
		
		case "kukulkan_8":
			dialog.text = "Exatamente. Quando percebi que já sabia o suficiente, dei um jeito de ser enviado para o Caribe. Consegui convencer o Chevalier de Poincy a montar uma base na Martinica. Depois disso, precisei encontrar um caminho até Tayasal. Não foi nada simples para mim, já que este corpo mortal tem seus limites e os portais no Caribe não estavam funcionando direito.";
			link.l1 = "E você se tornou Miguel Dichoso...";
			link.l1.go = "kukulkan_9";			
		break;
		
		case "kukulkan_9":
			dialog.text = "Dear brother, I earned this nickname on the battlefields of Europe. I also met Ramón de Mendoza y Riba there. Do you think that life is made of chances? No, not at all; every chance is an unknown regularity. Much had been done for the sake of my return to Tayasal. I had to live two lives: Michel de Monper and Miguel Dichoso. I also had to make sure people believed them to be different men. I had to turn pirate, just like you, in service to de Poincy in order to gain his trust, favour, and money. I had to murder Blaze Sharp, one of the leaders of the pirates, as a favour for Ramón de Mendoza, in order to get soldiers for the expedition. I had to tempt both de Poincy and de Mendoza with tales of Tayasal's treasures. I received seven hundred and fifty thousand pieces of silver from de Poincy's treasury and sold the Spanish military frigate to the pirate Dodson. And then the expedition happened. I returned to Tayasal only to suffer failure...";
			link.l1 = "Eu entendo... Enquanto você era apenas um garoto de cinco anos correndo atrás de borboletas nas terras do nosso pai, Kanek, o grande sacerdote, assustado pela invasão de Tayasal por Dom Alonso de Maldonado, escondeu com todo cuidado a máscara de Kukulcán, tão essencial para viajar ao passado... perdão, quero dizer, a SUA máscara.";
			link.l1.go = "kukulkan_10";			
		break;
		
		case "kukulkan_10":
			dialog.text = "Sim, Kanek acabou se enganando ali. Ele realizou o ritual mais difícil, um ritual que nem os antigos ousaram fazer. Escondeu a máscara na ilha deserta recém-formada e conseguiu perder a chave de Ksocheatem – o chamado Guardião da Verdade. Eu precisava agir com inteligência. O ritual impedia que qualquer navio carregando itens protegidos do tesouro de Taysal deixasse o Caribe, fazendo com que essas embarcações fossem lançadas nas praias de Ksocheatem. Eu pretendia usar isso a meu favor. Levei tesouros suficientes para agradar Mendoza. Também peguei um item especial protegido pelo ritual. Um navio com esse item a bordo estaria condenado a ser levado direto para Ksocheatem, direto para minha máscara. Então fui para o mar e fiz questão de que Mendoza soubesse de mim.";
			link.l1 = " Então, você saiu de Tayasal sozinho?";
			link.l1.go = "kukulkan_11";			
		break;
		
		case "kukulkan_11":
			dialog.text = "You mean without Mendoza's soldiers? Certainly. All the Spaniards were slain here, in Tayasal. The Itzas brought the treasures to the shore themselves, and I told Mendoza that the soldiers had been ambushed by the Miskito people. He believed me, since he was only interested in gold, not in people. I had planned to set up the ship with the treasures under the cannons of the 'Gryffondor', but it all went much better: the baron decided to send the treasures to Spain under my watch. That was the best possible outcome; I only had to wait until the ship crossed the invisible border of the Caribbean. However, it turned out that the captain had different orders. I found out that a special boarding unit was supposed to mutiny as soon as we reached the Atlantic Ocean, killing the crew and all the officers. The captain had orders to return the Indian gold to Mendoza afterwards. Such a fine specimen of the white race, isn't he, brother? I had to risk it; I didn't know when the mutiny was supposed to happen. But it all went according to plan: the storm hit us as soon as the 'Santa Quiteria' reached the eastern side of the island of Trinidad and Tobago. The frigate was swept back into the Caribbean towards Ksocheatem. I then suffered the greatest failure of my life—a wave washed me off the ship, and I found myself at Le Marin Cove on Martinique a couple of days later. Fishermen found me and took me to Le François. But de Poincy's men captured me while I was coming back to life at Cesar Craig's place. The 'Gryffondor' didn't find the 'Santa Quiteria' at the place I had specified. Chevalier de Poincy became furious as soon as he learned that the Indian gold was gone, together with the money taken from the Order's treasury and his own savings. He had me arrested. He couldn't kill me, though—he didn't want to. He wanted gold. Gold! That is the only thing your people want and care about! You will do anything to get it... I was in a terrible position: I had no mask on me, and I was left rotting in a cell without a single coin in my pockets. That was when I summoned you. Yes, yes, dear brother, you were supposed to free me, so I could do what I was born to do. And you did extraordinary work. It seems that the Itza milk you suckled did you some good.";
			link.l1 = "O que me interessa é saber no que você estava apostando quando fugiu de Saint-Pierre, então? Qual era o seu plano?";
			link.l1.go = "kukulkan_12";			
		break;
		
		case "kukulkan_12":
			PlaySound("Voice\English\sharlie\mishelle-05.wav");
			dialog.text = "Você sempre foi o meu plano, irmão. Kukulcan consegue ler o coração das pessoas. A carta que deixei para você na casa do Abade era para te fazer agir. Eu estava certo sobre você. Estive acompanhando seu progresso desde que conheceu o Inquisidor de Santiago. Você fez tudo por mim. Criou o Guardião da Verdade. Eliminou os concorrentes. Encontrou Ksocheatem.\nEu estava lá, te seguindo. Embora eu não esperasse que você conseguisse entrar em Tayasal. Você superou todas as minhas expectativas. E com a sua ajuda, vou cumprir o que nasci para fazer. O motivo pelo qual vim ao mundo em carne mortal.";
			link.l1 = "Há só um pequeno detalhe na sua lógica, meu caro irmão. Você não tem sua máscara e não é nada sem ela. Eu é que estou com ela. E não estou nem um pouco disposto a te entregar. Prefiro destruí-la do que deixá-la cair nas suas mãos.";
			if (CheckCharacterItem(pchar, "mask_true")) link.l1.go = "kukulkan_13";	
			else link.l1.go = "kukulkan_14";			
		break;
		
		case "kukulkan_13":
			dialog.text = "Você não pode mudar o que está predestinado pelo destino. Não vou permitir que você danifique meu artefato. Eu posso sentir... Ele está com você. E você está aqui, no meu templo, sob todo o meu poder! Você nunca vai sair daqui. Chegou a hora da sua prova final, querido irmão, para ver do que você é capaz em uma batalha contra Kukulcán!";
			link.l1 = "Acho que seu corpo mortal ainda pode sangrar!";
			link.l1.go = "kukulkan_fight";		
		break;
		
		case "kukulkan_14":
			dialog.text = "Ha! Sinto pena de você, Charles. Isso é realmente triste. Mas você merece a chance de lutar contra um Deus. Mesmo que seja inútil. Eu te conto depois, se sobreviver ao primeiro ato.";
			link.l1 = "Acho que seu corpo mortal ainda pode sangrar!";
			link.l1.go = "kukulkan_fight";			
		break;
		
		case "kukulkan_fight":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "item", "button04");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocator(npchar, "quest", "defend1", "", -1);
			sld = characterFromId("Kanek");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "quest", "defend2", "", -1);
			DoQuestFunctionDelay("Tieyasal_TempleFightGuard", 3.0);
		break;
		
		case "kukulkan_twice": // развилка финалов - есть настоящая маска или нет
			if (CheckCharacterItem(pchar, "mask_true"))
			{
				dialog.text = "";
				link.l1 = "Parece que seus poderes estão te abandonando, grande Kukulcan... Você pode ser forte, mas seu corpo ainda é mortal!";
				link.l1.go = "kukulkan_win";
			}
			else
			{
				dialog.text = "Acho que já tivemos diversão suficiente. Você é realmente um mestre da espada e um grande lutador, ouso dizer até o maior guerreiro do seu tempo, mas desta vez foi você quem perdeu."+pchar.name+"...";
				link.l1 = "Estamos só...";
				link.l1.go = "kukulkan_fail";
			}
		break;
		
		case "kukulkan_fail":
			DialogExit();
			SetMusic("music_teleport");
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "attack_force_1", "Tieyasal_KukulkanKick", 1.0);
			LaunchBlast(npchar);
			PlaySound("Sea Battles\udar_metal_003.wav");
		break;
		
		case "kukulkan_fail_1":
			dialog.text = "Basta, querido irmão. Você não pode resistir ao poder de Kukulcan quando ele está unido ao seu artefato! Eu permiti que você vivesse até agora só para ver do que realmente era capaz.";
			link.l1 = "Merda... Aquele último golpe... Mas de que artefato você está falando? A máscara? Ela está comigo!";
			link.l1.go = "kukulkan_fail_2";
		break;
		
		case "kukulkan_fail_2":
			dialog.text = "Pobre, pobre Capitão "+GetFullName(pchar)+"... You have come this far, survived all dangers, slain many of the strongest enemies only to be defeated in the end!.. The jade mask you found inside the metal box near the wrecks of the 'Santa Quiteria' on Ksocheatem is a fake! It is merely an ancient mask from Taysal's treasury. It is NOT THE MASK OF KUKULCAN!.\nI personally took it from here after my failed expedition; it is guarded by the ancient ritual. This mask was the reason why the storm carried the Santa Quiteria away to Ksocheatem. It also had a second purpose. It was meant to deceive anyone who came there seeking my TRUE artefact.";
			link.l1 = "Mas... Onde estava a máscara verdadeira então?! Procurei por toda Ksocheatem!..";
			link.l1.go = "kukulkan_fail_3";
		break;
		
		case "kukulkan_fail_3":
			dialog.text = "Você não fez isso, "+pchar.name+". Meu artefato estava do outro lado da ilha em relação ao 'Santa Quiteria', em um santuário protegido por uma guarda rigorosa. O caminho até lá passa por cavernas subterrâneas. É difícil de encontrar e nada óbvio para o olhar ingênuo de um mortal. Lá está! Olhe bem para ele, olhe uma última vez...";
			link.l1 = "Não pode ser!";
			link.l1.go = "kukulkan_fail_4";
		break;
		
		case "kukulkan_fail_4":
			dialog.text = "Você sobreviveu e venceu muitas batalhas, irmão. Mas desta vez, você perdeu, "+pchar.name+"...";
			link.l1 = "E o que agora?";
			link.l1.go = "kukulkan_fail_5";
		break;
		
		case "kukulkan_fail_5":
			dialog.text = "Vou viajar diretamente para o século dez, sete séculos atrás. Isso será suficiente para que a civilização maia alcance uma supremacia militar e científica inabalável sobre a raça branca.";
			link.l1 = "E o que vai acontecer com o nosso mundo? Ele vai desaparecer?";
			link.l1.go = "kukulkan_fail_6";
		break;
		
		case "kukulkan_fail_6":
			dialog.text = "Não. Vai mudar. Talvez haja um lugar para você, mas você não vai se lembrar de nada do que aconteceu neste mundo. Alguns que nasceram aqui nunca nascerão lá, e o contrário também é verdade. Os mortos voltarão à vida e os vivos morrerão, de um jeito ou de outro, todos vão renascer. Suum cuique, a cada um o seu, "+pchar.name+".\nNão tenha medo, irmãozinho. Você nunca vai perceber o que aconteceu e vai aceitar a nova realidade naturalmente. Só eu, Kukulcan, vou guardar as lembranças... Mas chega! Kanek já preparou tudo para o ritual.\nVocê vai me acompanhar, "+GetFullName(pchar)+", e você vai testemunhar os momentos finais da existência desta realidade que você tanto quis preservar.";
			link.l1 = "...";
			link.l1.go = "kukulkan_fail_7";
		break;
		
		case "kukulkan_fail_7":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Tieyasal_Fail_ReloadTown", 2.0);
		break;
		
		case "kukulkan_fail_8":
			dialog.text = "As portas do tempo se abriram! Alegrem-se, meus filhos, pois estão tão perto da grandeza! Vamos criar um novo mundo, um mundo onde não haverá lugar para os invasores pálidos!\nAdeus, "+pchar.name+", e esteja pronto para aceitar seu novo destino, seja ele qual for. Suum cuique!";
			link.l1 = "...";
			link.l1.go = "kukulkan_fail_9";
		break;
		
		case "kukulkan_fail_9":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "kukulkan", "", -1);
			DoQuestCheckDelay("Tieyasal_Fail_TeleportStart", 4.0);
		break;
		
		case "kukulkan_win":
			dialog.text = "Esta batalha ainda não acabou, mortal. Você está claramente exausto, e meus reforços estão a caminho! Você vai me entregar meu artefato. Ou isso, ou eu o tirarei do seu cadáver – para mim, tanto faz...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tieyasal_PrepareToWinBattle");
		break;
		
		case "kukulkan_win_1":
			dialog.text = "Urakan! Eu ordeno que você mate este homem imediatamente!";
			link.l1 = "...";
			link.l1.go = "kukulkan_win_2";
		break;
		
		case "kukulkan_win_2":
			dialog.text = "Urakan! Você não me ouviu? Repito: ordeno que você e seus guerreiros capturem e matem esse homem!";
			link.l1 = "...";
			link.l1.go = "kukulkan_win_3";
		break;
		
		case "kukulkan_win_3":
			dialog.text = "Urakan! Que diabos? Kanek! Repita minha ordem para o seu maldito filho!!!";
			link.l1 = "...";
			link.l1.go = "kukulkan_win_4";
		break;
		
		case "kukulkan_win_4":
			DialogExit();
			sld = characterFromId("Kanek");
			sld.dialog.currentnode = "kanek_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "kukulkan_win_5":
			dialog.text = "Você traiu seu povo, Urakan! Você se acovardou diante de transformações tão grandiosas! Guerreiros, ordeno que capturem e executem não só este homem que se diz meu irmão, mas também Urakan, o traidor!";
			link.l1 = "Guerreiros, em nome de Cavil e Hurakan, ordeno que fiquem onde estão, se valorizam suas vidas! Nenhum de vocês sobreviveria a uma luta contra Cavil! Que os próprios deuses decidam quem entre eles é o mais forte na Terra!";
			link.l1.go = "kukulkan_win_6";
		break;
		
		case "kukulkan_win_6":
			DialogExit();
			LAi_SetActorType(PChar);
			LAi_ActorTurnToCharacter(PChar, characterFromID("Mishelle"));
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Mishelle");
			sld.dialog.currentnode = "kukulkan_win_7";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.8);
		break;
		
		case "kukulkan_win_7":
			dialog.text = "";
			link.l1 = "Esse dia só fica melhor e melhor. Você não esperava que as coisas fossem acabar assim, não é, irmão? Os deuses que decidam por si mesmos quem entre eles é realmente o mais forte. E todos vão receber o que merecem, Michel. Suum cuique! A cada um o seu...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tieyasal_WinBattleStart");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
