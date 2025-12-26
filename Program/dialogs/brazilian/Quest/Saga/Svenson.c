// Ян Свенсон - пиратский барон Западного Мэйна
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp, sStr;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Svenson")) {
				if (pchar.questTemp.HelenDrinking.Result == "won") {
					dialog.text = "Ah, Charles. Obrigado por ter vindo. Só queria agradecer por passar um tempo com a Helen. A garota precisava se recuperar, e ouvi dizer que vocês se divertiram bastante, ha-ha! Droga, até fiquei com inveja!";
					link.l1 = "Você não está chateada? Por causa do barril e... de todo o resto?";
					link.l1.go = "after_drinking";
				} else {
					dialog.text = "Ah, Charles. Obrigado por ter vindo. Só queria agradecer por passar um tempo com a Helen. A garota precisava se recuperar, e ouvi dizer que você também se divertiu, ha-ha! Boa sorte pra você em Cartagena!";
					link.l1 = "Sim, também fico feliz que tudo tenha corrido bem ontem. Até a próxima, Jan.";
					link.l1.go = "exit";
				}
				
				DeleteAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Svenson");
				break;
			}
		
			if(CheckAttribute(pchar, "questTemp.Saga"))
			{
				if (CheckAttribute(pchar, "questTemp.Saga_Late")) // отсекание при провале по времени
				{
					dialog.text = "Oh, meu amigo "+pchar.name+"! Prazer em vê-lo! O que posso fazer por você?";
					link.l1 = "Só passei aqui para ver como você está.";
					link.l1.go = "exit";
					if(CheckAttribute(npchar, "quest.trade_bakaut")) // торговля бакаутом
					{
						if (GetDataDay() == 14 || GetDataDay() == 28)
						{
							link.l2 = "Jan, eu gostaria de comprar madeira de ferro.";
							link.l2.go = "trade_bakaut";
						}
					}
					break;
				}
				if(pchar.questTemp.Saga == "svenson")
				{
					dialog.text = "Como posso ajudá-lo, senhor?";
					link.l1 = "Gostaria de pedir sua ajuda, Diabo da Floresta.";
					link.l1.go = "saga";
					break;
				}
				if(pchar.questTemp.Saga == "svenson1")
				{
					dialog.text = "Aha, meu amigo "+pchar.name+"! Quais são as novidades?";
					link.l1 = "Consegui descobrir muitas coisas interessantes com o Carrasco.";
					link.l1.go = "saga_11";
					break;
				}
				if(pchar.questTemp.Saga == "svenson2")
				{
					dialog.text = "Então, "+pchar.name+", você falou com a Gladys?";
					link.l1 = "Sim, eu vi. Jan, dá uma olhada aqui... Consegue me dizer algo sobre esse pedaço de pergaminho aqui?";
					link.l1.go = "saga_17";
					break;
				}
				if(pchar.questTemp.Saga == "helena1" || pchar.questTemp.Saga == "helena2" || pchar.questTemp.Saga == "svenson_wait")
				{
					dialog.text = "Ainda não tenho novidades para te contar, "+pchar.name+". Mas estou trabalhando em uma solução para o nosso problema. Volte mais tarde.";
					link.l1 = "Certo, Jan. Até mais tarde.";
					link.l1.go = "exit";
					break;
				}
				if(pchar.questTemp.Saga == "baronsquests") // старт трех квестов баронов
				{
					// первая проверка времени. Свенсон очень недоволен растяпством ГГ. Счищаем Элен, к Свенсону доступ закроем
					if (CheckAttribute(pchar, "questTemp.Saga.Late"))
					{
						dialog.text = ""+pchar.name+", você me decepcionou completamente. Eu esperava que fosse um homem sério, mas pelo visto, você não passa de um garoto tolo. Onde esteve esse tempo todo, hein? Os ingleses tomaram a Isla Tesoro enquanto você estava sabe-se lá fazendo o quê!\nTodos os meus planos foram por água abaixo! Para ser sincero, eu quase tinha esquecido que você existia e não quero ser lembrado disso. Cai fora!";
						link.l1 = "Não acredito nisso!";
						link.l1.go = "saga_l1";
					}
					else
					{
						dialog.text = "Aí está você, "+pchar.name+". Estive pensando um pouco sobre a nossa situação. Não diria que é exatamente um plano, mas...";
						link.l1 = "Estou ouvindo, Jan.";
						link.l1.go = "saga_25";
					}
					break;
				}
				if(pchar.questTemp.Saga == "baronsquests_1") // идут три квеста баронов
				{
					dialog.text = "Como estão as coisas? Posso te ajudar com alguma coisa?";
					if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "after_marlow")
					{
						link.l3 = "Conversei com o Pastor Negro. Infelizmente, o resultado da nossa conversa me fez voltar direto pra você em busca de conselho, estou sem saída.";
						link.l3.go = "shark_hunt_2";
					}
					if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "LSC" && !CheckAttribute(pchar, "questTemp.Saga.BaronReturn"))
					{
						link.l3 = "Encontrei o Dios e tivemos uma conversa agradável. Ele me contou várias coisas interessantes, mas infelizmente não chegamos ao que realmente importa.";
						link.l3.go = "shark_hunt_7";
					}
					if (CheckAttribute(pchar, "questTemp.Saga.BaronReturn") && pchar.questTemp.Saga.BaronReturn == "third_teleport")
					{
						link.l3 = "Oh, Jan. Tenho tanta coisa pra te contar que levaria a noite inteira pra dizer tudo, então vou ser breve.";
						link.l3.go = "return_LSC";
					}
					if (CheckAttribute(pchar, "questTemp.Saga.BaronReturn") && pchar.questTemp.Saga.BaronReturn == "shamane" && !CheckAttribute(npchar, "quest.shamane"))
					{
						link.l3 = "Eu trouxe Nathaniel Hawk da Ilha da Justiça. Ele está no meu navio agora.";
						link.l3.go = "nathaniel";
					}
					if (CheckAttribute(pchar, "questTemp.Saga.BaronReturn") && pchar.questTemp.Saga.BaronReturn == "treatment")
					{
						link.l3 = "Deixei Nathaniel Hawk na aldeia Miskito para ser tratado por um xamã chamado Olho de Cobra. Ele prometeu restaurar a saúde do Nathan.";
						link.l3.go = "nathaniel_2";
					}
					link.l4 = "Não tenho muito o que te contar agora. Só passei para ver como você está.";
					link.l4.go = "exit";
					break;
				}
				if(pchar.questTemp.Saga == "fail_centurion") // провал - потоплен Центурион
				{
					dialog.text = "Quais são as novidades, "+pchar.name+"? Como vão as coisas?";
					link.l1 = "Ah, não podia estar pior. Fiz tanto esforço... Rastreiei o Jackman, jogamos fora as bainhas, e afoguei ele como um idiota, junto com tudo que podia estar na cabine dele. Agora não tenho nada pra limpar o nome do Shark ou jogar a culpa no Barbazon. Acho que não tem mais jeito, Jan.";
					link.l1.go = "saga_f_1";
					break;
				}
				if(pchar.questTemp.Saga == "calendar") // квесты баронов завершены
				{
					// вторая проверка времени. Отбираем Элен, со Свенсоном нейтральные отношения - ну не выщло и не вышло, хоть попытались. Данни и Натана - в Марун-Таун
					if (CheckAttribute(pchar, "questTemp.Saga.Late"))
					{
						dialog.text = "Ouvi falar dos seus feitos heroicos! Dannie me contou o resumo. Aliás, agora somos amigos. E o Nathan mudou completamente! Toda aquela tristeza sumiu quando ele viu o 'Centurion'.\nMas tenho más notícias pra você, "+pchar.name+". Perdemos tanto tempo que os direitos à herança do testamento de Sharp já se foram há muito, e Isla Tesoro virou uma base militar inglesa. Não há mais nada que eu possa fazer para te ajudar com Levasseur."link.l1 ="Estou completamente sem palavras... Passamos por tantos problemas à toa. Será que realmente não há nada que possamos fazer?";
						link.l1.go = "saga_l2";
					}
					else
					{
						dialog.text = "Ouvi tudo sobre suas façanhas! A Dannie me contou tudo. Ah, já fizemos as pazes, aliás. Você nem reconheceria o Nathan. Assim que ele viu o 'Centurion', deixou todo o mau humor pra trás, como se fosse um pesadelo...";
						link.l1 = "O Nathan está bem de novo? Fico feliz em saber disso!";
						link.l1.go = "saga_26";
					}
					break;
				}
				if(pchar.questTemp.Saga == "mine") // рудник взят
				{
					dialog.text = "Aqui está, "+pchar.name+"! Agora eu tenho algo para te contar.";
					link.l1 = "Olá, Jan. Estou radiante! Qual é a novidade? Espero que seja algo bom?";
					link.l1.go = "saga_32";
					break;
				}
				if(pchar.questTemp.Saga == "mine_1") // рудник взят совместно
				{
					dialog.text = "Aqui está, "+pchar.name+"! Descansou um pouco? Posso concluir que está pronto mais uma vez para grandes aventuras?";
					link.l1 = "Olá, Jan. Sim, estou pronto.";
					link.l1.go = "saga_32a";
					break;
				}
				if(pchar.questTemp.Saga == "late_l3") // провал по времени у адвоката
				{
					dialog.text = "Quais são as novidades, "+pchar.name+"? Como vão as coisas?";
					link.l1 = "Ah. As coisas estão realmente péssimas.  Lutei com todas as minhas forças, mas acabei perdendo do mesmo jeito. Como você deve lembrar, o testamento do Sharp tinha um prazo. Pois é, esse prazo acabou e Isla Tesoro agora é uma base militar inglesa. Não tem mais jeito, Jan.";
					link.l1.go = "saga_l3";
					break;
				}
				if(pchar.questTemp.Saga == "bakaut") // пришёл от адвоката за деньгами
				{
					dialog.text = "Saudações, "+pchar.name+"! Boas notícias: a reunião do Conselho aconteceu e os Irmãos da Costa escolheram um novo líder.";
					link.l1 = "Boa tarde, Jan. Fico feliz por você.";
					link.l1.go = "saga_44";
					break;
				}
				if(pchar.questTemp.Saga == "sellbakaut" && GetSquadronGoods(pchar, GOOD_SANDAL) >= 1) // отдает бакаут
				{
					dialog.text = "Bem, "+pchar.name+"?   Você conseguiu falar com Mulligan?";
					link.l1 = "Fui eu. Foi ele quem roubou seu pau-ferro.";
					link.l1.go = "saga_55";
					break;
				}
				if(CheckAttribute(npchar, "quest.bakaut") && GetNpcQuestPastDayParam(npchar, "bakaut_date") >= 1) // за деньгами за бакаут
				{
					dialog.text = "Pontual como sempre, "+pchar.name+". Eu vendi a madeira de ferro que você me trouxe.";
					link.l1 = "Excelente. Quanto dinheiro você conseguiu?";
					link.l1.go = "saga_57";
					break;
				}
				if(CheckAttribute(npchar, "quest.bakaut_sum")) // сам продал бакаут
				{
					dialog.text = "Bem, "+pchar.name+"?   Você conseguiu encontrar o Molligan?";
					link.l1 = "Fui eu. Ele foi quem roubou seu pau-ferro. Por acaso, também encontrei o comprador dele. Era um comandante militar holandês. Eu vendi a mercadoria para ele.";
					link.l1.go = "saga_59";
					link.l2 = "Eu tentei. Forcei ele a me mostrar o porão de carga... acabamos brigando e... agora não existe mais Molligan. Mas não tem nada pra ver lá dentro além de ébano e mogno.";
					link.l2.go = "saga_59_1";
					break;
				}
				if(CheckAttribute(npchar, "quest.jessika")) // информация о Джессике
				{
					dialog.text = TimeGreeting()+", "+pchar.name+". O que há de novo?";
					link.l1 = "Jan, eu queria conversar com você sobre uma coisa. Estive investigando o passado da mãe da Helen, a Beatrice, e acabei esbarrando em alguém que você conhece muito bem. Pelo que me contaram...";
					link.l1.go = "saga_62";
					break;
				}
				if(pchar.questTemp.Saga == "lastpages") 
				{
					dialog.text = TimeGreeting()+", "+pchar.name+". Como estão as coisas? Pelo seu rosto, posso te dar os parabéns? ";
					link.l1 = "Sim. Finalmente consegui resolver essa confusão. Helen recebeu todos os direitos sobre a Isla Tesoro. Nunca mais ninguém vai ousar invadir o santuário dos Irmãos da Costa!";
					link.l1.go = "saga_82";
					break;
				}
				if (pchar.questTemp.Saga == "end") sTemp = "Oh, my friend "+pchar.name+"! Pleased to see you! What brings you here?";
				else sTemp = "Anything else, "+pchar.name+"?";
				dialog.text = sTemp;
				link.l1 = "Não, Jan. Nada por enquanto.";
				link.l1.go = "exit";
				if(CheckAttribute(npchar, "quest.trade_bakaut")) // торговля бакаутом
				{
					if (GetDataDay() == 14 || GetDataDay() == 28)
					{
						link.l2 = "Jan, eu gostaria de comprar um pouco do seu pau-ferro.";
						link.l2.go = "trade_bakaut";
					}
				}
				NextDiag.TempNode = "First time";
			}
			else
			{
				// заглушка Элен
				if(startHeroType == 4)
				{
					dialog.text = "Helen, olá, minha querida. Que novidades você tem? Queria me dizer algo?";
					link.l1 = "Oi, Jan! Só passei aqui pra te ver, só isso.";
					link.l1.go = "exit";
					NextDiag.TempNode = "First time";
					break;
				}
				dialog.text = "Posso te ajudar com alguma coisa?";
				link.l1 = "Não, estou bem.";
				link.l1.go = "exit";
				NextDiag.TempNode = "First time";
			}
		break;
		
		case "saga":
			dialog.text = "Eu te conheço, droga! Você é o capitão corajoso que salvou a Rumba e enfrentou de frente os canhões da corveta inglesa! Que alegria te ver! A Helen é como uma filha para mim. De hoje em diante, te devo para sempre. Pode me chamar de Jan ou Svenson, como preferir. O que posso fazer por você?";
			link.l1 = "Eu preciso eliminar Levasseur, o governador de Tortuga. Sei que chegar até ele na ilha não vai ser fácil, então vim até você pedir um conselho.";
			link.l1.go = "saga_1";
		break;
		
		case "saga_1":
			dialog.text = "Minha nossa, onde você estava há alguns anos! Eu mesmo planejava fazer a mesma coisa. Ele estragou todo o nosso jogo com os franceses. Mas naquela época tudo era diferente. Blaze estava vivo, Shark tinha alguma autoridade, e Nathan mandava em tudo em Maroon Town... Agora tudo mudou e, Deus sabe, não foi pra melhor. Você sabe alguma coisa sobre nós, sobre a Irmandade?";
			link.l1 = "Acabei de chegar aqui, então não sei quase nada. Só sei que você e o Jackman são membros do Conselho.";
			link.l1.go = "saga_2";
		break;
		
		case "saga_2":
			dialog.text = "Ah, eu não suporto esse Jackman! Desde que ele chegou, nossos problemas começaram. Vou considerar seu pedido. No momento, nada me ocorre.";
			link.l1 = "Tenho algo interessante sobre o Jackman.";
			link.l1.go = "saga_3";
		break;
		
		case "saga_3":
			dialog.text = "Hum. O que é isso?";
			link.l1 = "Jackman está procurando por Gladys Chandler e sua filha. Depois de conversar com Higgins, comecei a achar que ele está atrás da Rumba. Parece que Gladys não é a mãe biológica da Helen, e seu sobrenome era Chandler antes de se casar com Sean McArthur.";
			link.l1.go = "saga_4";
		break;
		
		case "saga_4":
			dialog.text = "Droga! Isso é uma péssima notícia. Jackman está mais forte do que nunca agora. Além disso, tenho um pressentimento ruim de que ele não está agindo sozinho. Tem uma sombra bem sinistra por trás dele. Se ele realmente precisa da Helen, então a garota está mesmo precisando de um protetor. Receio que eu já esteja um pouco velho demais pra isso...";
			link.l1 = "Isso não é tudo. Jackman também está procurando por alguém chamado Henry, o Carrasco, ex-contra-mestre do 'Neptune', da tripulação do Capitão Butcher.";
			link.l1.go = "saga_5";
		break;
		
		case "saga_5":
			dialog.text = "Caramba! Minhas piores suspeitas se confirmaram! Esse Açougueiro e seu 'Neptune' já mantiveram todo o arquipélago em pânico. Naquela época não existia Irmandade, cada um por si. Esse homem fez muito mal, e alguém querido por mim morreu por causa dele.\nNunca cheguei a conhecê-lo. O 'Neptune' foi afundado por uma fragata inglesa, e o Açougueiro foi executado em St. John's. Já foi tarde! Embora muitos admirassem sua sorte e coragem insana.\nO próprio Jackman era seu braço direito e imediato no 'Neptune'. Surpreso? Ex-criminosos viraram heróis da Nação, tudo graças ao Cromwell! Para onde foi a boa e velha Inglaterra?\nPrecisamos encontrar Henry, o Carrasco, antes que os homens de Jackman o façam. Talvez ele tenha a chave desse mistério, se ainda estiver vivo.";
			link.l1 = "Aposto que seria mais fácil achar uma agulha no palheiro. Você pelo menos tem alguma pista?";
			link.l1.go = "saga_6";
		break;
		
		case "saga_6":
			dialog.text = "Conheci o Henry quando ele ainda era garoto. Filho de uma prostituta de Cartagena, meio espanhol, embora sempre tenha escondido isso. A mãe dele era um furacão! Não posso dizer que era bonita, mas poucas dançavam flamenco como ela. O bordel inteiro parava para ver as apresentações da Chica Gonzales nua com seus castanholas. Pobre moça. Pegou uma doença terrível e se apagou como uma vela. Foi nessa época que convenci Henry a ir para Providence, onde logo fez fama e entrou para a tripulação de Thomas Beltrope, grande amigo de Nicolas Sharp. Esses dois eram os últimos cães da Rainha Elizabeth e sempre agiam juntos. Belos tempos! Thomas voltou para a Inglaterra quando o parceiro morreu. Levou a tripulação com ele, mas Henry ficou no Caribe. Navegou sob vários capitães até aparecer o Açougueiro. Aliás, ele ganhou esse apelido por causa de um sabre que nunca largava.";
			link.l1 = "E o que essa informação nos diz?";
			link.l1.go = "saga_7";
		break;
		
		case "saga_7":
			dialog.text = "Se o Carrasco decidiu se esconder dos piratas, o melhor lugar para ele seria uma cidade espanhola. Principalmente em sua casa em Cartagena, onde tem amigos e parentes. Henrique sempre foi bem religioso, então é improvável que ele vá a uma igreja de outro santo. Provavelmente ainda usa o mesmo nome que tinha desde criança, Enrique.";
			link.l1 = "É... Não tem muita opção, mas pelo menos é melhor do que nada.";
			link.l1.go = "saga_8";
		break;
		
		case "saga_8":
			dialog.text = "Tente encontrá-lo, Charles! Poucos sabem das raízes espanholas de Henry, então temos uma pequena vantagem aqui. Vou pensar em como convencer Rumba a entrar para sua tripulação. A garota tem coragem, nunca serviu sob o comando de ninguém além do pai.\nMas ela não tem navio nem tripulação, e precisa ganhar a vida. Claro, continuarei ajudando Gladys, como sempre fiz, mas não vou conseguir manter Helen em Blueweld por muito tempo. E uma oficial assim vai ser muito útil para você. Sean ensinou tudo o que sabia a ela e a criou como se fosse um menino.\nEu ficaria mais tranquilo se ela estivesse sob o comando de um capitão como você.";
			link.l1 = "Rumba mostrou ser bastante valiosa. Preciso de mais gente como ela na minha tripulação. Então, se conseguir convencê-la, vou nomeá-la oficial. Mas antes quero entender quem ela realmente é e por que Jackman precisa dela. Temo que, ao contrário de Donovan, ele não esteja interessado nos encantos dela. Vou tentar encontrar o Hangman, mas não posso prometer nada.";
			link.l1.go = "saga_9";
		break;
		
		case "saga_9":
			dialog.text = "Well, splendid. Take this licence from the Dutch West India Company for three months. Write your name there; it may very well come in handy in your search. In the meantime, I'll think about what you have said concerning Levasseur and Tortuga.";
			link.l1 = "Muito obrigado! Este documento vai ser muito útil pra mim. Nesse caso, estou de partida para Cartagena, então.";
			link.l1.go = "saga_10";
		break;
		
		case "saga_10":
			DialogExit();
			GiveNationLicence(HOLLAND, 90);
			AddQuestRecord("Saga", "14");
			pchar.questTemp.Saga = "cartahena";//идем в Картахену
			pchar.quest.Saga_Gonsales.win_condition.l1 = "location";
			pchar.quest.Saga_Gonsales.win_condition.l1.location = "Cartahena_town";
			pchar.quest.Saga_Gonsales.function = "Saga_CreateGonsalesB";
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", false);//открыть спальню Элен
			LocatorReloadEnterDisable("FortOrange_town", "reload6", true); // закрыть резиденцию Джекмана
			npchar.greeting = "svenson_3";
			
			AddQuestRecord("HelenDrinking", "1");
			pchar.questTemp.HelenDrinking.CanDrink = true;
			SetFunctionTimerConditionParam("HelenDrinking_NoVisit", 0, 0, 1, 24 - GetHour(), false);
			
			pchar.questTemp.Saga.HelenRelation = 0;
		break;
		
		case "saga_11":
			dialog.text = "O Henry morreu?  Espera, foi você quem matou ele?";
			link.l1 = "Não me olhe com esses olhos arregalados! Eu não tive nada a ver com isso. Ele morreu pelas próprias mãos, pela consciência podre e pelo medo do Jackman. O velho pirata já tinha problemas no coração e não lhe restava muito tempo de vida. Aqui está o que consegui descobrir...";
			link.l1.go = "saga_12";
		break;
		
		case "saga_12":
			dialog.text = "Por favor, me conte!";
			link.l1 = "Vinte anos atrás, Henry deveria entregar um baú de ouro em nome do Capitão Butcher para a mãe adotiva de sua filha biológica. Não resta dúvida de que essa mãe adotiva era a Sra. McArthur. Naquela época, ela usava o sobrenome Chandler e morava em Belize. Mas as circunstâncias mantiveram o Carrasco em St. John's por mais um mês inteiro, e quando ele finalmente chegou a Belize, a cidade estava em ruínas após um ataque dos espanhóis, e tia Gladys e Sean já tinham partido sob sua proteção.";
			link.l1.go = "saga_13";
		break;
		
		case "saga_13":
			dialog.text = "";
			link.l1 = "Eles fizeram a Helen passar por filha biológica deles e a criaram como se fosse deles de verdade. Henry perdeu o rastro deles e ficou na moita, sabendo da vingança do Jackman e vivendo com medo nesses últimos vinte anos. Acontece que Jackman está procurando a filha do capitão dele. Mas por quê, eu não sei.";
			link.l1.go = "saga_14";
		break;
		
		case "saga_14":
			dialog.text = "Talvez ele esteja cumprindo ordens de alguém...";
			link.l1 = "Duvido. Quem poderia dar ordens a ele? O Açougueiro está morto. A morte dele foi confirmada por documentos oficiais. Dezenas, talvez centenas, de pessoas viram ele morrer.";
			link.l1.go = "saga_15";
		break;
		
		case "saga_15":
			dialog.text = "Talvez isso não seja sobre quem é o pai da Helen. Talvez tudo isso tenha a ver com a mãe biológica dela. Já posso imaginar quem ela era, mas tenho medo de admitir. Mas a Gladys! Como ela conseguiu guardar esse segredo por tantos anos, sem contar nem para o próprio marido! Sean McArthur com certeza teria me contado. Nunca tivemos segredos um com o outro.";
			link.l1 = "Vou ter uma conversa franca com a Gladys. Acho que tenho um jeito de fazê-la falar. Até a próxima, Jan!";
			link.l1.go = "saga_16";
		break;
		
		case "saga_16":
			DialogExit();
			pchar.questTemp.Saga = "gladis1";
			sld = characterFromId("Gladis");
			sld.dialog.currentnode = "Gladis_history";
			AddQuestRecord("Saga", "21");
		break;
		
		case "saga_17":
			dialog.text = "Onde você conseguiu isso!?";
			link.l1 = "Gladys me deu isso. Ela disse que era a 'herança da mãe da Helen'. Ela não sabe o nome dela. Algo me diz que isso não é só um pedaço qualquer de papel velho.";
			link.l1.go = "saga_18";
		break;
		
		case "saga_18":
			dialog.text = "Lembra quando eu te disse que tinha um palpite sobre quem era a verdadeira mãe da Helen? Agora tenho certeza. O nome dela era Beatrice Sharp. Ela era filha biológica do meu mestre e amigo Nicholas Sharp, irmã reconhecida do fundador da nossa Irmandade, Blaze Sharp, e coproprietária da Isla Tesoro. É esse pedaço do mapa que o Jackman está procurando.";
			link.l1 = "Olha só! Mas por que ele precisaria de metade de um mapa da ilha?";
			link.l1.go = "saga_19";
		break;
		
		case "saga_19":
			dialog.text = "A ilha foi descoberta por Nicolas Sharp. Ele a nomeou de Isla Tesoro, fez o mapa e reivindicou a posse dela através da Providence Island Company, onde tinha bons contatos.\nNicolas escreveu em seu testamento que a ilha só poderia ser herdada por quem apresentasse as duas partes do mapa. Ele fez isso para evitar disputas. Antes de morrer tragicamente nas mãos dos espanhóis, entregou as partes para Beatrice e seu enteado Blaze.";
			link.l1 = "Mas que diabo! Que estranho.";
			link.l1.go = "saga_20";
		break;
		
		case "saga_20":
			dialog.text = "Você está certo. Não foi a melhor ideia. E um tabelião astuto acrescentou que a ilha passaria para a coroa inglesa se ninguém apresentasse as duas partes do mapa dentro de um ano após a morte dos herdeiros.\nNinguém previu isso naquela época. E agora estamos pagando o preço pela nossa estupidez. Beatrice morreu há vinte anos. Todos esses anos se passaram e ainda não fazemos ideia de onde está o túmulo dela, junto com a parte do mapa dela. Blaze Sharp foi assassinado há pouco tempo. A parte dele também sumiu.\nSe ninguém apresentar o mapa completo de Isla Tesoro às autoridades dentro de um ano, então Sharptown será reivindicada pela Inglaterra. Eles vão mandar um governador com uma guarnição para lá e a Irmandade estará acabada.";
			link.l1 = "O que você sugere que façamos?";
			link.l1.go = "saga_21";
		break;
		
		case "saga_21":
			dialog.text = "Não podemos deixar isso acontecer. Preciso de você, Charles, preciso que impeça que isso aconteça. Só poderei ajudá-lo a eliminar Levasseur depois que tomarmos o controle da Isla Tesoro e elegermos Shark Dodson como o novo líder da Irmandade. Ele é o mais digno entre nós. Estou lhe oferecendo uma aliança.\nAh, e a propósito, conversei com Helen. Ela concordou em se juntar à sua tripulação.";
			link.l1 = "Você não me deixa escolha, Jan. Não posso voltar para a França sem restaurar a honra da minha família. E para isso, preciso tirar Levasseur do caminho, com ou sem a sua ajuda. Não quero mortes desnecessárias, e espero que você consiga tomar Tortuga sem derramar muito sangue. Embora eu deva admitir que gostaria de entender por conta própria o passado nebuloso que envolve a herança dos Sharps.";
			link.l1.go = "saga_22";
		break;
		
		case "saga_22":
			dialog.text = "Que bom ouvir um pouco de bom senso! Vamos encontrar a melhor maneira de tomar Tortuga. Isso eu te prometo. Então, vamos?";
			link.l1 = "Vamos lá! Eu volto daqui a pouco. Por enquanto, pense por onde começar a resolver o problema.";
			link.l1.go = "saga_23";
		break;
		
		case "saga_23":
			dialog.text = "Volte daqui a dois ou três dias. Acho que até lá meu plano já terá dado certo. E não se esqueça de levar a Helen com você no navio. A pobre garota está definhando longe do mar. Ela será uma assistente leal e você poderá confiar nela sem hesitar.";
			link.l1 = "Tudo bem, Jan. Vou buscá-la agora mesmo.";
			link.l1.go = "saga_24";
		break;
		
		case "saga_24":
			DialogExit();
			pchar.questTemp.Saga = "helena1";
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", true);//закрыть выходы из города
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", true);//закрыть спальню Элен
			AddQuestRecord("Saga", "23");
		break;
		
		case "saga_25":
			dialog.text = "First, you need to find the Shark. He wanted to get rid of Levasseur himself, and I assure you he has some bright ideas. Of course, we could also persuade Marcus to accept the leadership. He is the keeper of the Codex, after all. But I doubt he would be of any help; he has intentionally limited any contact with Levasseur and Tortuga. A man of principles.   I have no idea where Steven and his men are hiding, but his frigate, 'Fortune', was seen at Puerto Principe. Perhaps Zachary Marlow, also known as the Black Pastor, can point us to where we should look for the Shark. Second, we have to gain the support of the other barons to elect Dodson. And in order to do that, we need to collect their Indian shards – the votes. The new leader must have all five of them. That is what the Code tells us to do in the case that the previous leader has died.   Ridiculous! It is time to change the laws, but only the new leader can do that. We already have my vote. I believe that the Black Pastor doesn't give a damn whose arse is planted in Sharptown. I hope Jackman didn't talk to him first. We also have to persuade both Tyrex and Jacques Barbazon, who hate each other. But it is all irrelevant until we find out what has happened to the Shark. Third, one day we will have to kill Jackman and replace him with someone else. He won't negotiate with us.   Too bad Hawk is dead! People trusted him, and we could use his word. We won't find a better baron for Maroon Town. It is possible that Jackman has something to do with Blaze's murder, so he is also the clue to finding the second part of the map. Jacob trusts no one and most likely keeps the part of the map in his cabin on the 'Centurion'.   Hawk's family used to own the frigate, but Jackman claimed it, just like Hawk's barony. If we find the second part of the map in Jackman's possession, it would be a great argument for Steven's election. Especially for Marcus Tyrex, the Code keeper, and his over-scrupulousness in terms of honour. We will return to Helen her rights over Isla Tesoro as soon as we acquire both parts of the map.   We must be careful, though; Jackman won't stay idle and just watch you searching.";
			link.l1 = "Bem... Estou prestes a fazer uma visita ao Pastor Negro. Me fale sobre ele.";
			link.l1.go = "shark_hunt";
			pchar.questTemp.Saga = "baronsquests_1";
		break;
		
		case "shark_hunt":
			dialog.text = "Hell if I know what's on his mind. Sometimes he looks like a complete freak, but nevertheless, I believe it's just clever acting. Besides, his men are ready to fight the devil himself in honour of their beloved Pastor.\nThey've established some sort of Protestant sect, not far from the Spanish Inquisition, on Cuba. So don't even start talking about theological matters there; they won't approve of them.";
			link.l1 = "Vou levar isso em consideração...";
			link.l1.go = "shark_hunt_0";
		break;
		
		case "shark_hunt_0":
			dialog.text = "E, "+pchar.name+": não perca nem um minuto do seu tempo. Sério. Lembra da cláusula no testamento que diz que, se os herdeiros não reivindicarem a ilha em um ano, então Isla Tesoro vai para a coroa inglesa, certo? Pois é, o tempo não está a nosso favor agora. Da última vez que nos vimos, faltavam só uns onze meses até o prazo acabar.";
			link.l1 = "Eu me lembro, Jan.  Você tem razão, tempo é dinheiro. Vou cuidar disso!";
			link.l1.go = "shark_hunt_1";
		break;
		
		case "shark_hunt_1":
			DialogExit();
			AddQuestRecord("SharkHunt", "1");
			pchar.questTemp.Saga.SharkHunt = "begin";
			pchar.GenQuest.LigaAttack = "true"; // киллеры Лиги активированы
		break;
		
		case "shark_hunt_2":
			dialog.text = "Hm... O que o Zachary te contou?";
			link.l1 = "Antes de desaparecer, o Shark veio visitá-lo e deixou sua fragata com o Zachary como garantia em troca de uma escuna com um pouco de comida, depois partiu navegando para noroeste, em direção a Cuba.";
			link.l1.go = "shark_hunt_3";
		break;
		
		case "shark_hunt_3":
			dialog.text = "Isso realmente é estranho. Continue.";
			link.l1 = "Um mês depois, Dodson não voltou, e o Pastor, conforme os termos do acordo, ficou com a fragata para si e a vendeu por um bom preço para um tal de Paterson. Quanto aos nossos assuntos, Zachary comentou que o Shark pode ter fugido para uma lendária Ilha da Justiça, que dizem ficar em algum lugar não muito longe a noroeste de Cuba.";
			link.l1.go = "shark_hunt_4";
		break;
		
		case "shark_hunt_4":
			dialog.text = "Já ouvi falar da Ilha da Justiça. Dizem que existe uma ilha onde brancos e negros vivem juntos em paz, como iguais. Bobagem espalhada por sonhadores de todo tipo. Mas é possível que exista algum tipo de base de contrabandistas ao noroeste. Suas barcas costumavam ser vistas no mar aberto com frequência, uns dez anos atrás. Eles traziam todo tipo de mercadoria para Cuba em troca de comida.";
			link.l1 = "Tesouros por comida? O Pastor também me falou sobre os bucaneiros que transportam carne. É praticamente uma contradição ambulante.";
			link.l1.go = "shark_hunt_5";
		break;
		
		case "shark_hunt_5":
			dialog.text = "These rumours must have a source; those smugglers' or buccaneers' barques were sailing to that region for some reason. I remember the Shark told me stories about his youth—he was some sort of slave at a strange structure made of shipwrecks in the middle of the sea.   Perhaps that is our place? No clue. Anyway, the Pastor has a point—something is out there, either a secret base or an island where the Shark could have gone. Listen, sail to Santo Domingo and find a scientist named Jose Dios.   He is a Spanish cartographer. I once saved him from some filthy scoundrels; I respect educated people. He will help you, just tell him my name. Go to Hispaniola, find Dios and speak to him.   He knows our region's geography perfectly, and if he cannot help you—no one will.";
			link.l1 = "Está certo, Jan. Parece um bom plano. Lá vou eu!";
			link.l1.go = "shark_hunt_6";
		break;
		
		case "shark_hunt_6":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "dios";
			AddQuestRecord("SharkHunt", "3");
		break;
		
		case "shark_hunt_7":
			dialog.text = "Que pena. Eu tinha esperança de que o Jose nos ajudasse.";
			link.l1 = "Eu também contava com isso, mas enfim. Bem, não vamos ficar nos lamentando. Vou pensar mais um pouco sobre esse assunto. Sim, Jan, me diga, como o Hawk morreu?";
			link.l1.go = "baron_return";
		break;
		
		case "baron_return":
			dialog.text = "Ninguém testemunhou a morte dele, assim como ninguém viu o corpo. Ele simplesmente sumiu há alguns meses. Desde então, foi igual ao caso do Shark, nem sinal dele. Mas diferente do Steven, o Nathan não tinha motivo pra se esconder. Por isso todo mundo achou que ele tinha morrido na selva. Se não fosse por isso, não teriam concordado em eleger o Jackman no lugar dele.";
			link.l1 = "O que diabos o Hawk estava fazendo na selva?";
			link.l1.go = "baron_return_1";
		break;
		
		case "baron_return_1":
			dialog.text = "Foi culpa minha, sou um velho tolo! Convenci ele a lidar com os bandidos recém-chegados. Não faço ideia de quem são ou quem é o líder deles. Normalmente eu não ligaria, mas começaram a sequestrar os miskitos aliados. O chefe de guerra deles, Kumvana, ameaçou declarar o Caminho da Guerra e pediu minha ajuda. Não tive escolha a não ser intervir.\nHawk desembarcou com um pequeno grupo na Costa dos Mosquitos, caiu numa emboscada brilhantemente armada e foi derrotado. Parecia que ele e seus homens eram esperados ali. O corpo de Hawk não foi encontrado junto aos outros na selva.";
			link.l1 = "Tem todo tipo de confusão acontecendo bem debaixo do seu nariz! Nenhum dos homens do Hawk tentou lidar com os bandidos?";
			link.l1.go = "baron_return_2";
		break;
		
		case "baron_return_2":
			dialog.text = "Jackman foi o primeiro a agir. Ele se ofereceu para resolver a questão no conselho dos Irmãos e tomou a decisão. Os Miskitos pararam de desaparecer, mas os bandidos continuaram lá, mantendo um perfil relativamente discreto.\nJackman disse que eles não estavam mantendo nenhum dos agressores como refém, então não havia motivo para os Irmãos declararem guerra contra eles. Hawk foi quem atacou primeiro, então, segundo nossas leis, os bandidos tinham direito de se defender. Todos concordaram. Todos, menos...";
			link.l1 = "Todo mundo, menos quem?";
			link.l1.go = "baron_return_3";
		break;
		
		case "baron_return_3":
			dialog.text = "Nathan tinha uma esposa. O nome dela era Danielle Hawk e ela era uma mulher de fibra! Duvido que ela tenha superado a perda do capitão, sem falar que desde o começo ela desconfiava de algo e tentou convencer Hawk a desistir. Lembro que eles tiveram uma briga feia por causa disso, mas para eles isso não era nada fora do comum.";
			link.l1 = "E onde está Danielle agora?";
			link.l1.go = "baron_return_4";
		break;
		
		case "baron_return_4":
			dialog.text = "Quem sabe! Jackman garantiu que ela deixasse Maroon Town. Ela não me faz visitas. Nunca nos demos bem, ela ficou ainda mais rancorosa com o passar dos anos, e agora deve me odiar de verdade, porque provavelmente acha que sou o responsável pelas desgraças dela. Talvez esteja procurando o Hawk por conta própria, mas o que uma mulher pode fazer sozinha, mesmo que use calças e carregue um sabre! Aliás, ela domina o sabre. Não recomendo testar se cruzar com ela. E também não adianta conversar com os bandidos. Eles montaram um acampamento impressionante por lá e estão armados até os dentes. Parece que são ex-militares e entendem do assunto. Não deixam ninguém entrar no território deles. Dizem que os espanhóis extraíam ouro ali. Mas o ouro acabou e eles abandonaram a mina. Não faço ideia do que aqueles desgraçados estão aprontando por lá.";
			link.l1 = "Bem, já que ninguém viu o corpo do Hawk, ainda resta esperança de encontrá-lo vivo. Deus sabe, talvez até consigamos trazê-lo de volta para o baronato.";
			link.l1.go = "baron_return_5";
		break;
		
		case "baron_return_5":
			dialog.text = "É, pois é. Aqui, pegue esta carta. Quando encontrar Steve Dodson, entregue a ele imediatamente. O conteúdo desta carta vai garantir a sua segurança. Só por precaução.";
			link.l1 = "Obrigado, Jan. Vou cuidar disso, pode deixar!";
			link.l1.go = "baron_return_6";
		break;
		
		case "baron_return_6":
			DialogExit();
			GiveItem2Character(pchar, "letter_svenson");
			AddQuestRecord("BaronReturn", "1");
			pchar.questTemp.Saga.BaronReturn = "begin";
			pchar.quest.Saga_DannyMeeting.win_condition.l1 = "location";
			pchar.quest.Saga_DannyMeeting.win_condition.l1.location = "SantaCatalina_town";
			pchar.quest.Saga_DannyMeeting.function = "Saga_DannyMeeting";
		break;
		
		case "return_LSC":
			dialog.text = "Ué, por que essa cara triste? Está cansado? Que tal um copo de rum para você?";
			link.l1 = "Eu não me importaria...";
			link.l1.go = "return_LSC_1";
		break;
		
		case "return_LSC_1":
			LAi_AlcoholSetDrunk(pchar, 51, 5600);
			dialog.text = "Aqui, tome um copo. Agora fale.";
			link.l1 = "(bebendo) Ah, isso sim é melhor... Bem, Jan, você e o Pastor Negro estavam certos. A Ilha da Justiça existe mesmo. Eu estive lá.";
			link.l1.go = "return_LSC_2";
		break;
		
		case "return_LSC_2":
			dialog.text = "Eu te disse que era pra ter uma base de contrabando ali!";
			link.l1 = "Na verdade, não existe base nenhuma. E os boatos pelo Caribe não mentiram. Negros e brancos realmente vivem juntos por lá, não exatamente em paz, mas mais como cão e gato. E a ilha em si é formada por uma infinidade de destroços de navios.";
			link.l1.go = "return_LSC_3";
		break;
		
		case "return_LSC_3":
			dialog.text = "Não acredito! José Dios vai ficar muito interessado em ouvir sua história, tenho certeza disso. Aliás, passe lá para visitá-lo um dia.";
			link.l1 = "Vou visitá-lo mais tarde. Agora não é o melhor momento para isso. Tenho assuntos mais urgentes para resolver no momento. Encontrei Nathaniel Hawk na ilha.";
			link.l1.go = "return_LSC_4";
		break;
		
		case "return_LSC_4":
			dialog.text = "Você encontrou o Nathan? Isso é incrível! Como ele está?";
			link.l1 = "Bem... Ele está doente, vive bêbado e profundamente deprimido.";
			link.l1.go = "return_LSC_5";
		break;
		
		case "return_LSC_5":
			dialog.text = "Maldição, isso é desanimador. Onde ele está? No seu navio?";
			link.l1 = "Não, ele está no próprio navio. Na ilha.";
			link.l1.go = "return_LSC_6";
		break;
		
		case "return_LSC_6":
			dialog.text = "O quê, você não trouxe ele aqui? Por quê?";
			link.l1 = "Porque não havia nada que pudesse detê-lo. Cheguei à ilha sem um navio.";
			link.l1.go = "return_LSC_7";
		break;
		
		case "return_LSC_7":
			dialog.text = "Maldição, "+pchar.name+", mal tomou um copo de rum e já está falando bobagem como se tivesse bebido até cair. O que foi, atravessou o Caribe a nado? Ou amarrou tartarugas nos pés?";
			link.l1 = "Não, eu não nadei. Jan, eu cheguei à Ilha direto pela selva do continente, igualzinho ao Nathan, por causa de um ídolo indígena mágico. Já contei essa história pra tanta gente que já cansei de provar que não enlouqueci, então só digo uma coisa: acredita em mim, tá bom!?";
			link.l1.go = "return_LSC_8";
		break;
		
		case "return_LSC_8":
			dialog.text = "Ídolo indígena?";
			link.l1 = "Existem pelo menos três ídolos no Caribe conhecidos como as estátuas de Kukulcan: um perto da aldeia Miskito de West Main, outro no fundo das águas rasas perto da Ilha da Justiça, e mais um na aldeia Carib de Dominica. Esses ídolos, com a ajuda da magia indígena, são capazes de transportar pessoas instantaneamente através do tempo e do espaço.";
			link.l1.go = "return_LSC_9";
		break;
		
		case "return_LSC_9":
			dialog.text = "";
			link.l1 = "Eu passei pelas três estátuas em círculo e acabei exatamente onde comecei minha jornada na aldeia Miskito. Se não acredita em mim, posso chamar a Danielle. Ela viu tudo com os próprios olhos!";
			link.l1.go = "return_LSC_10";
		break;
		
		case "return_LSC_10":
			dialog.text = "Danielle? A esposa do Hawk? Ela estava com você?";
			link.l1 = "Em parte, sim. Ela mesma me encontrou em Blueweld e me levou até a aldeia Miskito, a um xamã que me enviou para a estátua mágica. Agora ela está servindo como uma das minhas oficiais, temporariamente, é claro.";
			link.l1.go = "return_LSC_11";
		break;
		
		case "return_LSC_11":
			dialog.text = "Estou absolutamente pasmo, "+pchar.name+"! É como dizem os ingleses. Você nasceu em berço de ouro. É um sortudo do caramba! Tudo bem, vou acreditar em você, embora seja difícil. Mas o problema com o Nathan continua, ele precisa de ajuda.";
			link.l1 = "É isso que vou fazer. Estou preparando uma expedição para a Ilha da Justiça. Agora tenho tudo o que preciso: as coordenadas da ilha e as instruções de navegação.";
			link.l1.go = "return_LSC_12";
		break;
		
		case "return_LSC_12":
			dialog.text = "Fantástico. Posso fazer algo para te ajudar?";
			link.l1 = "Não, obrigado. Mas deixei de fora um pequeno detalhe. Além do Nathan, também encontrei o Shark Dodson na ilha.";
			link.l1.go = "return_LSC_13";
		break;
		
		case "return_LSC_13":
			dialog.text = "Então, ele foi mesmo pra lá! Bem, "+pchar.name+", você fez um excelente trabalho. Como está o Dodson por lá? Você falou com ele, claro, não foi?";
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie"))
			{
				link.l1 = "Não só conversei com ele, como também viramos amigos. Foi ele quem me deu as instruções de navegação que vou precisar para voltar à Ilha. O Steven concordou em trocar a cabine do seu navio de guerra pela residência de Sharptown.";
				link.l1.go = "return_LSC_14";
			}
			else
			{
				link.l1 = "Conversamos, sim, mas no fim não adiantou de nada. Steven foi morto enquanto eu estava na ilha, quando uma conspiração organizada pelo seu contramestre, Chad Kapper, foi colocada em prática.";
				link.l1.go = "return_LSC_17";
			}
		break;
		
		case "return_LSC_14":
			dialog.text = "Hah! E como foi que o Tubarão conseguiu virar capitão de um navio de guerra?";
			link.l1 = "O navio está preso numa 'calmaria' sem fim há mais de meio século. Ele está encalhado com a tripulação na Ilha. Por isso ele não aparece no Caribe há tanto tempo. De qualquer forma, logo vou trazê-lo aqui e ele mesmo vai te contar sobre as aventuras dele.";
			link.l1.go = "return_LSC_15";
		break;
		
		case "return_LSC_15":
			dialog.text = "Mal posso esperar por isso! Agora as coisas estão começando a melhorar. Acabamos de ficar mais fortes, "+pchar.name+". Quando você pretende voltar para a ilha?";
			link.l1 = "Agora mesmo. Só passei aqui um minuto para te contar as novidades, enquanto a Danielle está preparando tudo para a expedição. Ela está louca para ver o Nathan dela. E sabe de uma coisa, Jan? Ela nem é tão insuportável assim.";
			link.l1.go = "return_LSC_16";
		break;
		
		case "return_LSC_16":
			dialog.text = "É?  Bom, talvez eu não estivesse totalmente certo sobre ela. Tudo bem, "+pchar.name+", não vou mais te segurar. Vá, e que a sorte esteja com você! Estarei esperando pelo seu retorno.";
			link.l1 = "Até mais, Jan.";
			link.l1.go = "return_LSC_19";
		break;
		
		case "return_LSC_17":
			dialog.text = "Chad Kapper? Droga, eu conhecia esse sujeito. Ele matou o Steven? Aquele desgraçado...";
			link.l1 = "Kapper está morto. Mas não podemos trazer Steven de volta, então precisamos pensar em uma forma de continuar organizando nossa política.";
			link.l1.go = "return_LSC_18";
		break;
		
		case "return_LSC_18":
			dialog.text = "Hah! Que pena... O que há pra pensar? Só precisamos convencer o Tyrex a liderar a Irmandade. Além disso, depois do Blaze, o Tyrex, como guardião do Código, é o mais respeitado entre nós. Mas primeiro precisamos trazer o Hawk de volta, pelo menos pra termos uma carta na manga. Quando você parte pra Ilha?";
			link.l1 = "Agora mesmo. Só passei aqui por um minuto pra te contar as novidades, enquanto a Danielle está se preparando pra expedição. Ela está morrendo de vontade de ver o Nathan dela. E sabe de uma coisa, Jan, ela nem é tão insuportável assim.";
			link.l1.go = "return_LSC_16";
		break;
		
		case "return_LSC_19":
			DialogExit();
			pchar.questTemp.Saga.BaronReturn = "return_LSC";
			// LSC ждёт своего героя!
			i = FindIsland("LostShipsCity");
			Islands[i].visible = true;
			Islands[i].reload_enable = true;
			pchar.quest.return_LSC.win_condition.l1 = "location";
			pchar.quest.return_LSC.win_condition.l1.location = "LostShipsCity";
			pchar.quest.return_LSC.function = "LSC_ReturnCheckShips"; // проверка типов кораблей
			pchar.quest.return_LSC_attack.win_condition.l1 = "location";
			pchar.quest.return_LSC_attack.win_condition.l1.location = "Beliz";
			pchar.quest.return_LSC_attack.function = "LSC_ReturnJackmanAttack"; // атака наймитов Джекмана
			pchar.quest.return_LSC_main.win_condition.l1 = "Ship_location";
			pchar.quest.return_LSC_main.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.return_LSC_main.function = "LSC_ReturnMain"; // основная функция возвращения
		break;
		
		case "nathaniel":
			dialog.text = "Como ele está? Você disse que ele não estava se sentindo bem.";
			link.l1 = "Sim, é exatamente isso. Vou levá-lo comigo para ser tratado na aldeia Miskito pelo Olho de Cobra, o xamã.";
			link.l1.go = "nathaniel_1";
		break;
		
		case "nathaniel_1":
			dialog.text = "Então não há tempo a perder! Depressa, "+pchar.name+"! Assim que você entregar o Nathan ao seu xamã, volte direto para mim.";
			link.l1 = "Certo, Jan. Parece um bom plano.";
			link.l1.go = "exit";
			npchar.quest.shamane = "true";
		break;
		
		case "nathaniel_2":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) // Акула жив
			{
				if (CheckAttribute(npchar, "quest.shark")) //и на месте
				{
					dialog.text = "Muito bem. Steven já passou aqui para me ver. Agora finalmente podemos continuar discutindo nossos planos.";
					link.l1 = "Estou todo ouvidos, Jan.";
					link.l1.go = "barbazon";
				}
				else
				{
					dialog.text = "Isso é ótimo, claro, mas por que o Dodson ainda não veio me ver? O quê, você deixou ele na ilha?";
					link.l1 = "Hm... Eu estava com pressa para levar o Nathan até Olho de Cobra...";
					link.l1.go = "nathaniel_wait";
				}
			}
			else
			{
				dialog.text = "Muito bem. Meu coração dói pelo Shark. Mas é a vida, então Tyrex vai assumir o lugar dele. Bem, agora finalmente podemos continuar discutindo nossos planos.";
				link.l1 = "Estou todo ouvidos, Jan.";
				link.l1.go = "barbazon";
			}
		break;
		
		case "nathaniel_wait":
			dialog.text = "... e você esqueceu de levar o Tubarão? Não acredito nisso."+pchar.name+"! Leve o Steven para Blueweld agora! Está me ouvindo? Vai!";
			link.l1 = "Calma, Jan. Eu vou cuidar de tudo.";
			link.l1.go = "exit";
			NextDiag.TempNode = "nathaniel_wait_1";
		break;
		
		case "nathaniel_wait_1":
			if (CheckAttribute(npchar, "quest.shark"))
			{
				dialog.text = "Steven passou aqui para me ver. Agora finalmente podemos continuar discutindo nossos planos.";
				link.l1 = "Estou todo ouvidos, Jan.";
				link.l1.go = "barbazon";
			}
			else
			{
				dialog.text = "Oh, "+pchar.name+"... Me parece que você anda bebendo rum demais ultimamente. Veja bem, isso nunca acaba bem. Primeiro suas mãos começam a tremer, depois você começa a perder a memória, e então recebe a marca negra...";
				link.l1 = "Entendi, Jan. Vou buscar o Steven agora mesmo!";
				link.l1.go = "exit";
				NextDiag.TempNode = "nathaniel_wait_1";
			}
		break;
		
		case "barbazon":
			dialog.text = "The Black Pastor has been very clear, he is only interested in that theological book. I've sent my men to search for it; perhaps someone will find it. Marcus Tyrex is not an issue, we'll have no problems persuading him. Jackman left Maroon Town soon after you paid him a visit. He sailed somewhere on the 'Centurion', the Hawks' frigate.\nThere is only Barbazon left - he is also known as Jacques the Kindman. We must find a way to make him cooperate with us. I am not sure how to accomplish that so far. But one thing is obvious - you should visit him.";
			link.l1 = "Me fale sobre Barbazon."; // Addon 2016-1 Jason пиратская линейка патч 17/1
			link.l1.go = "barbazon_1";
		break;
		
		case "barbazon_1":
			dialog.text = "Tipo reservado. Finge ser pobre, mas provavelmente é o homem mais rico do Caribe. Ele controla todo o contrabando no Leste. Se não fosse o Marcus enfrentando ele, já teria dominado todo o tráfico de contrabando nas Ilhas de Barlavento. Tyrex é como uma pedra na garganta dele.\nVivem brigando no conselho, mas Barbazon não tem coragem de declarar guerra aberta. Talvez ele tenha sido mesmo um pirata de Dunquerque, como diz, mas agora me lembra muito mais um agiota.";
			link.l1 = "Como diabos ele foi eleito barão?";
			link.l1.go = "barbazon_2";
		break;
		
		case "barbazon_2":
			dialog.text = "Gold, my friend, rules everything and everywhere; whoever has the gold makes the rules. Besides, Barbazon is really good at coming up with all kinds of profitable and illegal operations. He doesn't take part in them himself, but he always takes a share. So he is constantly surrounded by a lot of brave thugs, who are mostly weak in the head. They would all just die of hunger or end up on the scaffold without him.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
			{
				link.l1 = "Ele me lembra o Marcus... Jan, o negócio é o seguinte... Eu não faço ideia de como chegar no Barbazon. Tem um problema que você não sabe.";
				link.l1.go = "barbazon_5";
			}
			else
			{
				link.l1 = "Como faço para chegar a Barbazon?";
				link.l1.go = "barbazon_3";
			}
		break;
		
		case "barbazon_3":
			dialog.text = "Simplesmente finja ser um desses imbecis que precisam de uma dica para conseguir um bom trabalho. Nem pense em tentar passar a perna nele para ficar com a parte dele. O generoso Barbazon não perdoa.";
			link.l1 = "Isso nem precisa dizer. Não estou me envolvendo com ele por interesse próprio. De qualquer forma, está na hora de fazer uma visita a ele.";
			link.l1.go = "barbazon_4";
		break;
		
		case "barbazon_4":
			DialogExit();
			AddQuestRecord("BarbTemptation", "1");
			pchar.questTemp.Saga.BarbTemptation = "begin";
			pchar.questTemp.Saga.BaronReturn = "barbazon";
			NextDiag.CurrentNode = "First time";
			// тут вычищаем квестовый мусор от LSC
			if (CheckCharacterItem(pchar, "letter_chad")) RemoveItems(pchar, "letter_chad", 1);
			if (CheckCharacterItem(pchar, "letter_chad_1")) RemoveItems(pchar, "letter_chad_1", 1);
		break;
		
		// Addon 2016-1 Jason пиратская линейка патч 17/1
		case "barbazon_5":
			dialog.text = "Sério? Pode falar.";
			link.l1 = "Já ouviu falar de Charlie Prince?"; 
			link.l1.go = "barbazon_6";
		break;
		
		case "barbazon_6":
			dialog.text = "Sim, ouvi os boatos. Esse cara trabalhava para o Marcus Tyrex até pouco tempo atrás. Fez muita coisa em pouco tempo, ficou famoso saqueando Cartagena. E daí?";
			link.l1 = "Esse cara sou eu. Eu sou Charlie Prince. Era. Entende agora?"; 
			link.l1.go = "barbazon_7";
		break;
		
		case "barbazon_7":
			dialog.text = "Mas que diabos! Você é o Charlie Prince? Que reviravolta! "+pchar.name+", estou impressionado! Agora entendi de onde vem essa sua força... Mas o que Barbazon tem a ver com isso?";
			link.l1 = "Que tal o Príncipe fazer uma visita ao Barbazon, Jan?.."; 
			link.l1.go = "barbazon_8";
		break;
		
		case "barbazon_8":
			dialog.text = "Hm... Entendi. Você já lidou com ele antes?";
			link.l1 = "Não exatamente. Um dos capangas dele, chamado Ignacio Marco, tentou acabar comigo por ordem direta do Barbazon. Era parte da guerrinha deles."; 
			link.l1.go = "barbazon_9";
		break;
		
		case "barbazon_9":
			dialog.text = "Ele viu o seu rosto? Você se apresentou para ele?";
			link.l1 = "Não."; 
			link.l1.go = "barbazon_10";
		break;
		
		case "barbazon_10":
			dialog.text = "Então não vejo problema aqui. Também ouvi falar do corsário Charlie Prince, mas não sabia que era você até você me contar.";
			link.l1 = "Você acha que o Barbazon não vai me enxergar?"; 
			link.l1.go = "barbazon_11";
		break;
		
		case "barbazon_11":
			dialog.text = "Como ele poderia, se nunca viu o seu rosto? Tudo o que fez foi mandar se livrar de um dos empregados do Marcus.";
			link.l1 = "Hum... Talvez você tenha razão sobre isso."; 
			link.l1.go = "barbazon_12";
		break;
		
		case "barbazon_12":
			dialog.text = "No way we are getting through this without Barbazon. Go see him, but be careful. Run if he recognises you; we will think of another way to approach him in that case.";
			link.l1 = "Certo. Já devia estar indo. Estava ansioso para conhecer o desgraçado."; 
			link.l1.go = "barbazon_13";
		break;
		
		case "barbazon_13":
			dialog.text = "Não se faça de bobo e nem tente mexer com o Jacques. Ele nunca perdoa. Aja como um idiota ansioso pra ganhar dinheiro fácil.";
			link.l1 = "Parece que esse é meu papel favorito... Adeus, Jan!"; 
			link.l1.go = "barbazon_4";
		break;
		
		case "saga_26":
			dialog.text = "Sim. O xamã indígena fez tudo o que pôde, o Hawk está como novo. Ele já deve estar em Maroon Town com o Dannie, então, se quiser, vá lá dar um alô. Eles vão ficar muito felizes em te ver.";
			link.l1 = "Com certeza vou passar lá para ver como eles estão... Jan, consegui encontrar a segunda parte do mapa do Sharp! Estava na cabine do Jackman. Agora não vamos ter problema nenhum para provar os direitos da Helen sobre Isla Tesoro.";
			link.l1.go = "saga_27";
		break;
		
		case "saga_27":
			dialog.text = "Ótimo, mostre-me isso.\nEstávamos certos, Jacob foi quem matou Blaze. Agora a mancha no nome do Shark precisa ser removida de uma vez por todas. Quanto às provas, é uma questão mais delicada. E só deve ser tratada depois de muita reflexão.";
			link.l1 = "Outra coisa, Jan. Dá uma olhada nesse bilhete. Ele também estava entre as coisas do Jackman.";
			link.l1.go = "saga_28";
		break;
		
		case "saga_28":
			RemoveItems(pchar, "letter_parol", 1); // удалить записку
			dialog.text = "Vamos dar uma olhada... Ah, então é por isso que os bandidos ouviram o Jackman e pararam de sequestrar os Miskitos! Não poderia ter sido diferente! Aquele canalha planejou tudo e estava vários passos à frente.";
			link.l1 = "Sim, e eu também entendo por que os homens do Hawk foram massacrados. Mas tem duas coisas que eu não entendo: primeiro, o que os comparsas do Jackman estão fazendo na mina, e segundo, por que você está reagindo com tanta calma ao fato de que toda essa confusão está acontecendo no seu território?";
			link.l1.go = "saga_29";
		break;
		
		case "saga_29":
			dialog.text = "Estou envergonhado... Você tem razão. Jackman realmente passou dos limites. E os capangas dele não têm nada que fazer no meu território. Acho que chegou a hora de lembrar ao Caribe com quem eles estão lidando.";
			link.l1 = "O que você está pensando, Jan?";
			link.l1.go = "saga_30";
		break;
		
		case "saga_30":
			dialog.text = "Reviver o passado... Pretendo organizar uma expedição punitiva e eliminar todos os bandidos das minas. Agora temos provas de que são homens de Jackman, e estou obrigado a limpar meus territórios dessa escória.\n"+pchar.name+", você fez um excelente trabalho. Agora é hora de eu seguir em frente. Descanse um pouco por enquanto. Vá visitar os Falcões. Volte em dez dias!";
			link.l1 = "Certo, Jan.  Pode deixar. Vou voltar exatamente no tempo que você falou!";
			link.l1.go = "saga_31";
			link.l2 = "Ha! Eu também quero participar dessa cruzada. Por que você decidiu me colocar de folga?";
			link.l2.go = "saga_31_1";
		break;
		
		case "saga_31_1":
			dialog.text = "Me perdoe, meu caro. Só achei que talvez tivesse chegado a hora de eu trabalhar um pouco e você descansar. Mas se esse é o seu desejo, ficarei mais do que feliz! Vamos enfrentar a tempestade juntos! E tudo o que encontrarmos na mina será dividido igualmente entre nossas tripulações, como está escrito nas leis da Irmandade.";
			link.l1 = "Fechado, Jan! Quando partimos?";
			link.l1.go = "saga_31_2";
		break;
		
		case "saga_31_2":
			dialog.text = "Venha com seu pessoal para a Costa dos Mosquitos em três dias. Até lá, já terei reunido meu grupo e estarei esperando por você. Não se atrase!";
			link.l1 = "Está certo, Diabo da Floresta. Mal posso esperar para lutar ao seu lado, ombro a ombro! Até logo!";
			link.l1.go = "saga_31";
			npchar.quest.mine_tw = "true";
		break;
		
		case "saga_31": 
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto1");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			if (CheckAttribute(npchar, "quest.mine_tw"))
			{
				pchar.quest.Saga_MinePrepareAttack.win_condition.l1 = "location";
				pchar.quest.Saga_MinePrepareAttack.win_condition.l1.location = "Shore53";
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2 = "Timer";
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2.date.hour  = sti(GetTime());
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2.date.day   = GetAddingDataDay(0, 0, 3);
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2.date.month = GetAddingDataMonth(0, 0, 3);
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2.date.year  = GetAddingDataYear(0, 0, 3);
				pchar.quest.Saga_MinePrepareAttack.function = "Saga_MineBanditsPrepareAttack";
				SetFunctionTimerCondition("Saga_MineBanditsAttackOver", 0, 0, 4, false); // таймер
			}
			else SetFunctionTimerCondition("Saga_MineBanditsDestroyed", 0, 0, 10, false); // таймер
			sld = characterFromId("Nathaniel");
			sld.model = "Hawk_2";
			Characters_RefreshModel(sld); // наверно не нужно
			sld.greeting = "nathaniel_2";
			sld.dialog.currentnode = "marun_town";
			ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "sit", "sit1");
			LAi_SetHuberType(sld);
			LocatorReloadEnterDisable("FortOrange_town", "reload6", false); // открыть резиденцию Хоука
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "marun_town";
			sld.greeting = "danny_2";
			ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "goto", "goto1");
			LAi_SetStayType(sld);
		break;
		
		case "saga_32a":
			dialog.text = "Excelente. Descobri algo sobre o misterioso dono da mina, Lawrence Beltrope.";
			link.l1 = "Então, quem é essa moça?";
			link.l1.go = "saga_35";
		break;
		
		case "saga_32":
			dialog.text = "Eu arranquei a informação dos capangas do Jackman na mina. Eles até que deram trabalho, mas meus homens também não nasceram ontem. Além disso, conseguimos baixar a guarda deles depois de falar a senha do bilhete que você encontrou. Invadimos a mina e demos a eles uma despedida inesquecível.";
			link.l1 = "Você tomou a mina? Impressionante!";
			link.l1.go = "saga_33";
		break;
		
		case "saga_33":
			dialog.text = "Que isso sirva de lição pra quem acha que o Diabo da Floresta está ficando enferrujado. Eu realmente fiquei à toa demais nesses últimos anos, e olha no que deu? Jackman estava tramando seu plano maligno bem debaixo do meu nariz!";
			link.l1 = "O que você viu naquela mina? Me conte sobre isso!";
			link.l1.go = "saga_34";
		break;
		
		case "saga_34":
			dialog.text = "A mina foi realmente abandonada pelos espanhóis, mas Lawrence Beltrope, de Port Royal, comprou-a por uma ninharia e continuou a explorá-la em segredo. Pelo visto, os espanhóis desistiram do veio cedo demais, porque, embora nós mesmos não tenhamos encontrado ouro, achamos vários escravizados que juram que havia ouro ali até bem recentemente.";
			link.l1 = "Lawrence Beltrope? Nunca ouvi falar dele. Quem é?";
			link.l1.go = "saga_35";
		break;
		
		case "saga_35":
			dialog.text = "Ele é um nativo daqui, filho de Thomas Beltrope, que foi irmão de juramento de Nicholas Sharp e corsário da Companhia da Ilha da Providência. Eu conheci muito bem o Thomas. Há um ano, Lawrence voltou ao Caribe. Descobri que Jackman estava trabalhando para ele. Guarde isso na cabeça e fique atento!";
			link.l1 = "Então o misterioso 'chefe' do Jackman, mencionado naquela carta, é Lawrence Beltrope... Certo, vou guardar esse nome.";
			link.l1.go = "saga_36";
		break;
		
		case "saga_36":
			dialog.text = "Mais uma coisa. Lembro de algo estranho. Blaze certa vez mencionou uma mina de ouro espanhola abandonada e disse que ia investir o ouro dela em Sharptown. Mas o mapa da mina sumiu depois que a irmã dele fugiu com o Capitão Butcher. Talvez ele estivesse falando da nossa mina?\nEnfim, faz tanto tempo que não muda muita coisa... Você e eu precisamos lidar com o Conselho. Já conseguiu todos os cinco fragmentos?";
			link.l1 = "Sim. Esses quatro: Nathaniel, Tyrex, Marlow e Barbazon. Todos eles deram seu consentimento.";
			link.l1.go = "saga_37";
		break;
		
		case "saga_37":
			RemoveItems(pchar, "splinter_nh", 1);
			RemoveItems(pchar, "splinter_mt", 1);
			RemoveItems(pchar, "splinter_jb", 1);
			RemoveItems(pchar, "splinter_zm", 1);
			sTemp = "Shark";
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Tyrex";
			dialog.text = "Ótimo. Tenho certeza de que não haverá nenhum problema para eleger "+sTemp+" como líder da Irmandade da Costa. Vou começar a organizar uma reunião do Conselho imediatamente.";
			link.l1 = "Então, Jan, podemos considerar que todos os problemas estão sob controle por enquanto? Nathaniel está em Maroon Town, Jackman está morto, e os Irmãos agora têm um novo líder... Talvez seja hora de voltarmos ao começo, ou seja, tomar Tortuga?";
			link.l1.go = "saga_38";
		break;
		
		case "saga_38":
			dialog.text = "Eu me lembro, "+pchar.name+", mas precisamos esperar um pouco. Além disso, o tempo para resolver a herança do Sharp está acabando, e esse assunto, como você sabe, precisa ser tratado com urgência.";
			link.l1 = "O que há de errado com a herança? Eu já tenho as duas partes do mapa. Tudo o que precisamos fazer é apresentá-las e pronto...";
			link.l1.go = "saga_39";
		break;
		
		case "saga_39":
			dialog.text = ""+pchar.name+", eu te garanto que hoje em dia não se distribuem ilhas assim tão facilmente. Nem mesmo para os herdeiros legítimos, com cada cláusula do testamento cumprida. As autoridades inglesas querem muito essa ilha, disso eu sei bem.\nNão acredito que o Coronel Doyle vá ficar de braços cruzados enquanto tomamos a ilha que ele já considera propriedade inglesa. Além disso, nós dois devemos agir discretamente.";
			link.l1 = "E o que você sugere?";
			link.l1.go = "saga_40";
		break;
		
		case "saga_40":
			dialog.text = "Vá até Port Royal e procure um homem chamado Albert Loxley por lá. Ele é o melhor advogado de todo o Caribe. Ficou bem experiente em assuntos escusos de todo tipo, então aceita qualquer trabalho se pagarem uma fortuna. Tem um apetite de rei, mas vale cada centavo.";
			link.l1 = "Você acha que o testamento do Sharp pode ter algumas armadilhas?";
			link.l1.go = "saga_41";
		break;
		
		case "saga_41":
			dialog.text = "Não é que eu ache, eu tenho certeza disso. Já precisou tratar de negócios com funcionários públicos? Saiba que, se eles querem algo de você, vão arrancar sua alma, apontar cada vírgula fora do lugar, interpretar tudo do jeito que lhes convém e te deixar mais pelado que um gatinho cego.\nÉ por isso que existem advogados. Eles enfrentam os funcionários com as mesmas armas – a enrolação, a papelada e as artimanhas. Por isso, você deveria procurar o Loxley e contratá-lo para defender nossos interesses enquanto eu cuido das eleições.";
			link.l1 = "Certo. Estou indo para Port Royal. Quanto tempo vai levar para o Conselho se reunir e realizar a eleição?";
			link.l1.go = "saga_42";
		break;
		
		case "saga_42":
			dialog.text = "Dez dias. Então não se preocupe em me procurar em Blueweld antes disso.";
			link.l1 = "Entendi. Bem, Jan, nesse caso, até daqui a pouco!";
			link.l1.go = "saga_43";
		break;
		
		case "saga_43":
			DialogExit();
			AddQuestRecord("Testament", "1");
			pchar.questTemp.Saga = "loxly"; // обновляем флаг
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", true); // закрыть кабинет Свенсона
			SetFunctionTimerCondition("Saga_GoldForLoxly", 0, 0, 10, false); // таймер
		break;
		
		case "saga_44":
			sTemp = "Steven Dodson";
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus Tyrex";
			dialog.text = ""+sTemp+" envia suas mais calorosas saudações. Ele ficará sempre feliz em recebê-lo em sua residência na Isla Tesoro. Não deixe de visitá-lo, caso tenha oportunidade.";
			link.l1 = "Para ter certeza "+sTemp+" não vai sair da sua nova residência, você e eu, Jan, temos um pouco de trabalho pela frente.";
			link.l1.go = "saga_45";
		break;
		
		case "saga_45":
			sTemp = "four hundred and fifty";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) sTemp = "one thousand";
			dialog.text = "Imagino que você já visitou Loxley...";
			link.l1 = "Sim, já consegui. Ele aceitou pegar nosso caso, mas exigiu uma fortuna em ouro pelos serviços. "+sTemp+" dobrões adiantados. Adiantados! E ainda teremos que pagar mais a ele, dependendo de como for a prova dos direitos da Helen. O valor pode dobrar ou triplicar, como ele disse.";
			link.l1.go = "saga_46";
		break;
		
		case "saga_46":
			dialog.text = "Ha! Bem, eu não esperava menos de um velho raposa como ele. Consegue farejar uma presa a quilômetros de distância, igual a uma hiena. Claro, estamos falando de uma ilha inteira aqui. Seria ridículo pensar que o Albert não pediria algumas centenas. Então, o valor total deve ficar em torno de mil e quinhentas moedas de ouro...";
			link.l1 = "Jan, isso é uma fortuna!";
			link.l1.go = "saga_47";
		break;
		
		case "saga_47":
			dialog.text = "Eu sei onde você quer chegar. Concordo que você não é nenhum idiota pagando tudo isso do próprio bolso. Mas, infelizmente, no momento não tenho essa quantia de ouro guardada. Eu até tinha planejado para esse tipo de gasto, mas a intervenção de um canalha acabou com tudo.";
			link.l1 = "Do que você está falando?";
			link.l1.go = "saga_48";
		break;
		
		case "saga_48":
			dialog.text = "Escute. Talvez você já saiba que nosso assentamento é só meio legalizado. Os ingleses mantêm uma guarnição aqui e nós fornecemos mogno para eles por um bom preço. Mas existe um tipo de madeira muito pesada e resistente – o Lignum Vitae, que você deve conhecer como pau-ferro.\nÉ raro e difícil de trabalhar, mesmo com aço temperado. Dizem que, há muito tempo, os maias-itza faziam seus temíveis porretes com ela. Você não encontra pau-ferro no mercado aberto e, contrabandeado, vale seu peso em prata.\nOs homens do Doyle às vezes aparecem e compram todo o lote que conseguimos processar por uma mixaria. Mas eu sempre dou um jeito de guardar um pouco para mim.";
			link.l1 = "Já ouvi falar dessa árvore. Dizem que balas de mosquete afundam na sua madeira oleosa como piche! Ela é tão resistente que dá até pra fazer engrenagens de aço com ela.";
			link.l1.go = "saga_49";
		break;
		
		case "saga_49":
			dialog.text = "Estão exagerando um pouco sobre as engrenagens, mas o resto está certinho. Então, prevendo os gastos, preparei um grande lote de pau-ferro, mas algum desgraçado esvaziou meu armazém há uns dias. É alguém do nosso meio, disso eu tenho certeza. Tenho uma suspeita, mas não posso afirmar com certeza.";
			link.l1 = "Ratos devem ser esmagados! Quem você suspeita?";
			link.l1.go = "saga_50";
		break;
		
		case "saga_50":
			dialog.text = "Paul Molligan. His East Indian 'Oyster' sailed to Barbados yesterday. I didn't have the chance to check her holds. But he wouldn't bring the ironwood to Bridgetown anyway; Lord Willoughby has serious customs officers there, and ironwood is a raw material of strategic importance for the English navy.\nIf he really has my ironwood, then he will sell it before arriving at Bridgetown. If only you could intercept Molligan and inspect his holds!..";
			link.l1 = "Você disse que ele partiu para Bridgetown ontem? Ainda não está tudo perdido. Vou tentar alcançá-lo.";
			link.l1.go = "saga_51";
		break;
		
		case "saga_51":
			dialog.text = "Você já sabe o que fazer se o Molligan for o traidor. Mas tente descobrir primeiro o nome do cliente dele. Assim, você pode entregar a carga diretamente ao cliente ou devolvê-la para mim.\nLeve também a 'Ostra' para Blueweld, é um belo navio, quero ficar com ele e adaptá-lo para o meu uso. Você também pode pegar o que quiser como prêmio... E caso Molligan não seja o culpado... não, tenho certeza de que ele é o rato que roubou meu pau-ferro.";
			link.l1 = "Vou aproveitar bem o meu tempo!";
			link.l1.go = "saga_52";
		break;
		
		case "saga_52":
			dialog.text = "Se você vender a madeira de ferro por conta própria, separe mil e quinhentos dobrões de ouro para o Loxley e dividimos o resto igualmente. Posso confiar em você nisso, não posso?";
			link.l1 = "Claro. Eu não sou um rato.";
			link.l1.go = "saga_53";
		break;
		
		case "saga_53":
			dialog.text = "Não tenho dúvidas. Boa sorte, "+pchar.name+"! Espero que desta vez a sorte esteja do seu lado.";
			link.l1 = "Obrigado. Até mais!";
			link.l1.go = "saga_54";
		break;
		
		case "saga_54":
			DialogExit();
			pchar.questTemp.Saga = "molligan"; // обновляем флаг
			AddQuestRecord("Testament", "3");
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			Saga_CreateMolliganInWorld(); // ставим корабль Моллигана на карту
		break;
		
		case "saga_55":
			npchar.quest.bakaut = GetSquadronGoods(pchar, GOOD_SANDAL);
			dialog.text = "Eu sabia. Quanto ele tinha no porão?";
			link.l1 = "Eu encontrei "+FindRussianQtyString(sti(npchar.quest.bakaut))+" no 'Ostra'.";
			link.l1.go = "saga_56";
		break;
		
		case "saga_56":
			iTemp = sti(npchar.quest.bakaut);
			if (iTemp > 100)
			{
				dialog.text = "Uau! Nunca tive tanto assim no meu depósito. Olha só quem conseguiu pôr as mãos numa fortuna. Obrigado, "+pchar.name+", você nunca me decepciona. Vou vender a mercadoria agora mesmo, já temos um comprador. Amanhã terei o dinheiro para você.";
				link.l1 = "Tudo bem. Não vou mais te atrapalhar então. Até amanhã.";
				link.l1.go = "saga_oust";
				break;
			}
			if (iTemp >= 90 && iTemp < 101)
			{
				dialog.text = "Já chega pra mim. Rato miserável! Obrigado, "+pchar.name+", você nunca me decepciona. Vou vender a mercadoria agora mesmo, já temos um comprador. Amanhã terei o dinheiro para você.";
				link.l1 = "Tudo bem. Não vou te atrapalhar mais então. Até amanhã.";
				link.l1.go = "saga_oust";
				break;
			}
			if (iTemp >= 70 && iTemp < 90)
			{
				dialog.text = "Provavelmente ele já conseguiu vender parte da carga para alguém, porque deveria ter mais. Mas não é nada grave, recuperamos quase tudo. Obrigado, "+pchar.name+", vou vender a mercadoria agora mesmo, já temos um comprador. Amanhã terei o dinheiro para você.";
				link.l1 = "Tudo bem. Não vou te atrapalhar mais então. Até amanhã.";
				link.l1.go = "saga_oust";
				break;
			}
			if (iTemp >= 50 && iTemp < 70)
			{
				dialog.text = "Maldição, aquele desgraçado já conseguiu vender uma boa parte da carga... Ah, que pena. Fazer o quê. Vou vender o que sobrou, já tenho comprador. Amanhã mesmo estarei com o dinheiro.";
				link.l1 = "Certo. Não vou te atrapalhar mais então. Até amanhã.";
				link.l1.go = "saga_oust";
				break;
			}
			if (iTemp >= 20 && iTemp < 50)
			{
				dialog.text = "Maldição, isso é lamentável! Aquele desgraçado já conseguiu vender mais da metade da carga... Ah, que pena. Fazer o quê. Vou vender o que sobrou, já arrumei um comprador. Amanhã mesmo vou ter o dinheiro.";
				link.l1 = "Tudo bem. Não vou mais te atrapalhar então. Até amanhã.";
				link.l1.go = "saga_oust";
				break;
			}
			dialog.text = "Rapaz, eu tô mesmo sem sorte. Ele já vendeu quase tudo... Toma, fica com essa madeira de ferro pra você, "+pchar.name+", faça o que quiser com isso. Você é minha única esperança de ganhar algum dinheiro agora.";
			link.l1 = "Entendi. Tá bom, eu mesmo vou procurar. Não é a primeira vez... Tchau, Jan.";
			link.l1.go = "saga_oust";
		break;
		
		case "saga_oust":
			if (CheckAttribute(npchar, "quest.bakaut"))
			{
				if (sti(npchar.quest.bakaut) < 20) DeleteAttribute(npchar, "quest.bakaut");
				else 
				{
					SaveCurrentNpcQuestDateParam(npchar, "bakaut_date");
					RemoveCharacterGoods(pchar, GOOD_SANDAL, sti(npchar.quest.bakaut));
				}
				pchar.questTemp.Saga = "removebakaut";
			}
			int iUst = 0;
			for(i = 0; i < COMPANION_MAX; i++)
			{
				iTemp = GetCompanionIndex(PChar, i);
				if(iTemp > 0)
				{
					sld = GetCharacter(iTemp);
					if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_EASTINDIAMAN && sld.ship.name == "Oyster") iUst = 1;
				}
			} // есть ли у нас Устрица
			dialog.text = "Espere! Você capturou a 'Ostra'?";
			if (iUst == 1)
			{
				link.l1 = "Sim. Ela está no porto agora mesmo. Eu a ancorei para você, exatamente como pediu.";
				link.l1.go = "saga_oust_yes";
			}
			else
			{	
				link.l1 = "Não. O navio ficou tão danificado durante a batalha que precisei afundá-lo.";
				link.l1.go = "saga_oust_no";
			}
		break;
		
		case "saga_oust_no":
			dialog.text = "Que pena. Mas é assim mesmo. Até mais, "+pchar.name+"!";
			link.l1 = "Tchau, Jan.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "saga_oust_yes":
			dialog.text = "Impressionante! Vou equipar essa belezinha do jeito que ela merece. E depois você sempre pode pegá-la emprestada por um tempo, como combinamos. Acho que em cerca de dois meses ela estará pronta.";
			link.l1 = "Certo. Um navio desses pode ser bem útil de vez em quando... Até mais, Jan!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Saga_RemoveOuster");
			npchar.quest.ouster = "true";
			SaveCurrentNpcQuestDateParam(npchar, "ouster_date"); // через 2 месяца
			NextDiag.TempNode = "First time";
		break;
		
		case "saga_57":
			int idlt;
			iTemp = sti(npchar.quest.bakaut)*30; // Ян за 1 шт бакаута даёт 30 дублонов
			if (iTemp > 1600)
			{
				idlt = makeint(iTemp-1500)/2; // доля Бонса :)
				dialog.text = "Recebi "+iTemp+" moedas por isso. Mil e quinhentas vão para o advogado, mais a sua parte dos dobrões - "+idlt+". Aqui está.";
				link.l1 = "Excelente! Agora posso partir para Loxley sem problemas.";
				link.l1.go = "saga_58";
				TakeNItems(pchar, "gold_dublon", 1500+idlt);
				break;
			}
			if (iTemp > 1450 && iTemp <= 1600)
			{
				dialog.text = "Recebi mil e quinhentos dobrões por isso. Dá só para pagar o advogado. Aqui está.";
				link.l1 = "Fantástico. Agora posso partir para Loxley.";
				link.l1.go = "saga_58";
				TakeNItems(pchar, "gold_dublon", 1500);
				break;
			}
			dialog.text = "Recebi "+iTemp+" doblões por isso. Aqui está. O resto você vai ter que cavar sozinho.";
			link.l1 = "Bem, se é sozinho, então vai ser sozinho. Certo, estou a caminho para ver o Loxley.";
			link.l1.go = "saga_58";
			TakeNItems(pchar, "gold_dublon", iTemp);
		break;
		
		case "saga_58":
			DialogExit();
			PlaySound("interface\important_item.wav");
			DeleteAttribute(npchar, "quest.bakaut");
		break;
		
		case "saga_59":
			dialog.text = "E então? Que interessante. E quanto o holandês está disposto a pagar por isso?";
			link.l1 = "Quarenta dobrões cada um.";
			link.l1.go = "saga_60";
		break;
		
		case "saga_60":
			dialog.text = "Opa! Meus compradores pagam menos...";
			link.l1 = "No geral, tenho dois mil em ouro para Loxley e "+sti(npchar.quest.bakaut_sum)*2+" dobrões além disso.";
			link.l1.go = "saga_61";
		break;
		
		case "saga_61":
			dialog.text = "Muito bem. Então vamos dividir igualmente.";
			if (PCharDublonsTotal() > 0)
			{
				npchar.quest.bakaut_pay = func_min(sti(npchar.quest.bakaut_sum), PCharDublonsTotal()); // дублоны в кармане
				link.l1 = "Aqui está. Eu trouxe "+FindRussianQtyString(sti(npchar.quest.bakaut_pay))+".";
				link.l1.go = "bakaut_pay";
			}
			else
			{
				link.l1 = "Deixei os dobrões no navio. Vou até lá rapidinho e já volto.";
				link.l1.go = "exit";
				NextDiag.TempNode = "bakaut_pay_wait";
			}
		break;
		
		case "saga_61_1":
			dialog.text = "Muito bem. Quanto você trouxe?";
			if (PCharDublonsTotal() > 0)
			{
				npchar.quest.bakaut_pay = func_min(sti(npchar.quest.bakaut_sum), PCharDublonsTotal()); // дублоны в кармане
				link.l1 = "Aqui está. Eu tenho "+FindRussianQtyString(sti(npchar.quest.bakaut_pay))+".";
				link.l1.go = "bakaut_pay";
			}
			else
			{
				link.l1 = "O que está acontecendo com a minha memória! Está na hora de parar de brincar com esse rum. Mais uma vez, deixei os dobrões no meu baú. Vou lá rapidinho pegar e já trago.";
				link.l1.go = "exit";
				NextDiag.TempNode = "bakaut_pay_wait";
			}
		break;
		
		case "bakaut_pay": // оплата
			if (sti(npchar.quest.bakaut_sum) < sti(npchar.quest.bakaut_pay)) // полная сумма
			{
				npchar.quest.bakaut_pay = sti(npchar.quest.bakaut_sum);
				iTemp = 0;
			}
			else iTemp = sti(npchar.quest.bakaut_sum)-sti(npchar.quest.bakaut_pay);
			npchar.quest.bakaut_sum = iTemp; // запоминаем остаток
			RemoveDublonsFromPCharTotal(sti(npchar.quest.bakaut_pay));
			Log_Info("You have given "+sti(npchar.quest.bakaut_pay)+" doubloons");
			PlaySound("interface\important_item.wav");
			if (iTemp == 0)
			{
				dialog.text = "Bom trabalho, "+pchar.name+"! Mais uma vez percebo que é bom ter você por perto.";
				link.l1 = "Eu tento, Jan...";
				link.l1.go = "bakaut_done";
			}
			else
			{
				dialog.text = "Ótimo. Vai trazer o resto "+FindRussianQtyString(sti(npchar.quest.bakaut_sum))+" dobrões depois?";
				link.l1 = "Sim. Eu simplesmente não consegui carregar uma pilha tão grande de ouro de uma só vez.";
				link.l1.go = "exit";
				NextDiag.TempNode = "bakaut_pay_wait";
			}
		break;
		
		case "bakaut_pay_wait":
			dialog.text = "Então, "+pchar.name+", como andam meus doblões?";
			link.l1 = "Posso te dar mais um pouco de ouro.";
			link.l1.go = "saga_61_1";
		break;
		
		case "bakaut_done": // рассчитались
			dialog.text = "Tenho uma proposta para você. Já que conseguiu encontrar um comprador que paga bem, posso te vender um pouco de madeira de ferro. Eu costumava receber trinta doblões por peça. Se quiser, pode comprar de mim por esse preço. Prefiro vender para você do que para outra pessoa.";
			link.l1 = "Quanto de pau-ferro você pode vender?";
			link.l1.go = "bakaut_done_1";
		break;
		
		case "bakaut_done_1":
			dialog.text = "Eu evito acumular grandes lotes. O caso do Molligan foi uma exceção. As autoridades não vão gostar de saber de um mercado negro local. Então, é o seguinte: vou separar 25 peças de pau-ferro para você nos dias 14 e 24 de cada mês.\nSe quiser comprar, traga setecentos e cinquenta dobrões e leve o lote inteiro. Se não aparecer nesse dia, vendo para outro cliente. Assim, você consegue 50 peças por mês. Fechado?";
			link.l1 = "Fechado, Jan! Vamos nessa. Agora, está na hora de eu ir...";
			link.l1.go = "saga_oust";
			DeleteAttribute(npchar, "quest.bakaut_sum");
			npchar.quest.trade_bakaut = "true"; // генератор купли-продажи бакаута
			AddQuestRecordInfo("Unique_Goods", "1");
		break;
		
		case "saga_59_1": // укрысил у Яна - нет генератора на бакаут, потерял больше
			dialog.text = "Ah, então ou não era ele, ou ele já vendeu a madeira de ferro antes... Que pena. Bem, agora você é minha única esperança de conseguir o dinheiro para o advogado.";
			link.l1 = "Eu estou disposto a assumir essa responsabilidade. Não é a primeira vez que faço isso.";
			link.l1.go = "exit";
			// Ян расстроен и забыл про Устрицу - так что и Устрицы тоже не будет
			DeleteAttribute(npchar, "quest.bakaut_sum");
		break;
		
		case "saga_62":
			dialog.text = "É mesmo? Que interessante. Pode perguntar. Sobre quem você quer saber?";
			link.l1 = "Sobre uma garota. O nome dela era... Jessica Rose.";
			link.l1.go = "saga_63";
		break;
		
		case "saga_63":
			dialog.text = "Hum. O novo líder da nossa Irmandade te falou sobre ela?";
			link.l1 = "Ele também. Mas eu soube dela pelo Baker, o velho carrasco de St. John's. O mesmo homem que executou o Capitão Butcher.";
			link.l1.go = "saga_64";
		break;
		
		case "saga_64":
			dialog.text = "Certo. Hm. Bem, já faz mais de vinte anos desde a última vez que vi a Jessica. O que você sabe sobre ela?";
			link.l1 = "Bem, eu sei como ela acabou com o Capitão Butcher e como eles piratearam juntos. Sei que ele a deixou por Beatrice. Depois, ela se vingou dele por isso com a ajuda de um tal Joshua Leadbeater, também conhecido como a Máscara...";
			link.l1.go = "saga_65";
		break;
		
		case "saga_65":
			dialog.text = "";
			link.l1 = "Eu também sei que você, Jan, me perdoe a franqueza, tinha interesse na Jessica. É por isso que vim até você. Jessica é uma peça importante na minha investigação. Foi ela quem matou Beatrice Sharp, por ciúmes, pelo que entendi.";
			link.l1.go = "saga_66";
		break;
		
		case "saga_66":
			dialog.text = "Well, you know a great deal. Yes, I really had been courting Jess, but it was no surprise; all pirates of Isla Tesoro were divided into two different groups back then: those who wanted to fuck Beatrice and those who wanted Jessica.\nI remember her well... She was beautiful, very beautiful!..";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("Video_Jess");
			NextDiag.TempNode = "saga_66a";
		break;
		
		case "saga_66a":
			dialog.text = "Ela era especial... Também é bem provável que a Jess tenha matado a Beatrice. Depois que o Butcher a expulsou do 'Neptune', ela provavelmente não pensou em mais nada além de se vingar dele e da Beatrice. Aliás, você sabe como o Butcher se livrou da Jessica?";
			link.l1 = "Não. Ou ele simplesmente a deixou em Barbados ou a colocou para resgate.";
			link.l1.go = "saga_67";
		break;
		
		case "saga_67":
			dialog.text = "O segundo. Ele a humilhou de um jeito inacreditável. Trancou ela na cabine, levou para Barbados, começou a negociar com o pai dela, Oliver Rose, e no fim vendeu ela por um monte de dobrões... depois de tudo que ela fez por ele.";
			link.l1 = "Hum. Achei que o Açougueiro tinha defendido a honra dela quando os piratas tomaram o 'Neptune' do Joshua Leadbeater...";
			link.l1.go = "saga_68";
		break;
		
		case "saga_68":
			dialog.text = "Isso também é verdade. Mas ela também o recompensou generosamente. Jessica salvou a vida miserável daquele canalha várias vezes, tirando-o das enrascadas que ele mesmo arranjava com suas farras e seu temperamento explosivo. Na verdade, foi só graças a ela que ele alcançou a glória de um pirata próspero.";
			link.l1 = "É, é, o talismã vermelho dele. Ouvi falar disso. Dizem que assim que o Açougueiro chutou a Jess, a sorte dele também foi embora...";
			link.l1.go = "saga_69";
		break;
		
		case "saga_69":
			dialog.text = "But of course. Without Jessica, he had become just another common sea raider, even though a recklessly brave one. But Jessica wasn't there for him; she was the one who helped him plan all his risky operations, and he could always count on her blade.\nSure, Beatrice wasn't a good girl either, but she couldn't match Jess. Bea's charms were completely different... She made the mistake of crossing Butcher.";
			link.l1 = "Já ouvi isso em algum lugar antes...";
			link.l1.go = "saga_70";
		break;
		
		case "saga_70":
			dialog.text = "All pirates thought so, including Blaze Sharp, her brother. He couldn't stand Butcher... But let's get back to Jessica. I didn't even dare think of her while she was on the 'Neptune'; she would never have left her beloved captain. But when Butcher got rid of her in such a mean way...\nI arrived in Barbados and became friends with her. It wasn't easy for her; she loved the sea and dangerous adventures. That dull colonial life was killing her. Besides, she had become a very infamous person in the Caribbean while serving on the 'Neptune', and the folk of Bridgetown had reasons to consider her Butcher's partner in crime...";
			link.l1 = "Mas eles não conseguiram provar nada...";
			link.l1.go = "saga_71";
		break;
		
		case "saga_71":
			dialog.text = "No. But no one wanted to have anything to do with her either. She was considered cursed, despite her status in Bridgetown. I suppose I was the only man who spent more than half an hour with Jessica there.\nI offered her the chance to come with me to the West Main and start a new life there. The life she had always wanted - the sea, ships, voyages, adventures. I had already set up a large operation in Blueweld by then and I was able to offer her a hundred times more than that scoundrel Butcher. But Jess was badly hurt. She hadn't forgiven Butcher for his betrayal and the way he treated her afterwards. And I believe she still had feelings for him even then... Despite all my efforts, I could not make her forget the past; she was obsessed with thoughts of revenge.";
			link.l1 = "Sim, não invejo ela. Pobre garota...";
			link.l1.go = "saga_72";
		break;
		
		case "saga_72":
			dialog.text = "Eu sentia o mesmo por ela. Mais tarde, ela passou a se interessar por cultos e rituais indígenas antigos. Isso aconteceu depois que um feiticeiro indígena foi capturado e trazido das profundezas da selva de Yucatán para a plantação local. Jessica o comprou e lhe deu uma casa em sua propriedade.   Ela passava muito tempo com o feiticeiro, dizendo que era tudo por conta do seu interesse histórico nos rituais mágicos dos índios. O povo de Bridgetown ficou preocupado, especialmente o pastor local. Na verdade, ele era um dos poucos que era gentil com Jessica.   O padre conversava bastante com ela, insistindo para que se livrasse do feiticeiro, alertando sobre perigos e sobre a inquisição, mas tentar assustar Jessica era inútil. Numa noite, alguns desconhecidos invadiram a casa do feiticeiro e o assassinaram.   Na mesma noite, dois homens atacaram Jessica em seu próprio quarto, mas as coisas não saíram como eles esperavam—ninguém em Bridgetown sabia o quanto Jess era habilidosa com sua espada de lâmina flamejante. Ela literalmente os despedaçou.";
			link.l1 = "É, claro... aquela megera imprudente!";
			link.l1.go = "saga_73";
		break;
		
		case "saga_73":
			dialog.text = "Depois disso, toda a cidade passou a temê-la. E então apareceu a Máscara. Eles se encontraram bem rápido.";
			link.l1 = "Segundo os registros, a Máscara é Joshua Leadbeater, o antigo capitão do 'Neptune'...";
			link.l1.go = "saga_74";
		break;
		
		case "saga_74":
			dialog.text = "Eu só fiquei sabendo disso muito tempo depois. Uma semana após a chegada da Máscara, Jess pegou suas coisas, se despediu de mim e partiu em uma fragata militar rumo a águas desconhecidas. Ela nunca voltou... assim como Beatrice nunca retornou à Isla Tesoro.\nLogo depois que enforcaram o Carniceiro em St. John's, ele foi entregue lá pelo próprio Máscara. Mas sobreviveu ao Carniceiro por apenas um dia.";
			link.l1 = "Sim... Nosso Steven Dodson mostrou classe...";
			link.l1.go = "saga_75";
		break;
		
		case "saga_75":
			dialog.text = "Yes, that's what I was told. He avenged Beatrice... And that's how Jessica's story ends; she passed away somewhere on an uninhabited island in a skirmish with Butcher's pirates. Nobody knows where this place is. Butcher is dead, and so are Jackman and Hangman.";
			link.l1 = "É aí que você se engana, Jan. O Butcher está vivo.";
			link.l1.go = "saga_76";
		break;
		
		case "saga_76":
			dialog.text = " O quê!? Não pode ser! Ele foi enforcado!";
			link.l1 = "Leia o depoimento de Raymond Baker. É melhor do que qualquer história.";
			link.l1.go = "saga_77";
		break;
		
		case "saga_77":
			PlaySound("interface\important_item.wav");
			dialog.text = "Mostre-me isso...(lendo) Hm. Incrível! Então a execução dele foi encenada!";
			link.l1 = "Esperto, né? Mas isso não é tudo. Você conhece o Açougueiro. Só não sabe quem ele é agora.";
			link.l1.go = "saga_78";
		break;
		
		case "saga_78":
			dialog.text = "É mesmo? E quem é ele?";
			link.l1 = "Lawrence Beltrope, de Port Royal. O dono da mina, aquela sombra misteriosa por trás do Jackman. Descobri isso pelo Baker, e o Baker soube pelo Máscara.";
			link.l1.go = "saga_79";
		break;
		
		case "saga_79":
			dialog.text = "Caramba! Então foi ele quem armou tudo isso? Certo... Vamos atrás do Açougueiro também. Vou pensar em como derrubar esse maldito. Mas não vai ser fácil, ele está sempre sob a proteção das autoridades inglesas.";
			link.l1 = "A hora dele vai chegar, Jan. Em breve, ele vai se encontrar com o contramestre e o imediato. Certo, obrigado pela história. Agora preciso ir.";
			link.l1.go = "saga_80";
		break;
		
		case "saga_80":
			dialog.text = "Para onde você está indo agora?";
			link.l1 = "Para alguma ilha. Acho que é o mesmo lugar onde Jess e Beatrice morreram e onde a Máscara atacou o Açougueiro-Beltrope. Preciso de provas de que Helen pertence à família Sharp e espero encontrá-las lá.";
			link.l1.go = "saga_81";
		break;
		
		case "saga_81":
			dialog.text = "Certo. Então, "+pchar.name+" , boa sorte pra você. Me conte tudo quando voltar.";
			link.l1 = "Pode deixar. Até mais, Jan!";
			link.l1.go = "saga_81a";
		break;
		
		case "saga_81a":
			DialogExit();
			LAi_SetHuberType(npchar);
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(npchar, "quest.jessika");
			npchar.quest.jessika_peace = "true"; // атрибут на мирное разрешение после боя
		break;
		
		case "saga_82":
			dialog.text = "Mandou bem, "+pchar.name+". Você realizou o impossível. Todos nós, barões da Irmandade da Costa, lhe devemos uma.";
			link.l1 = "Sim, o caminho para a vitória foi estreito. Se ao menos eu soubesse antes que teria que aguentar tanto...";
			link.l1.go = "saga_83";
		break;
		
		case "saga_83":
			dialog.text = "Como está a Helen? O que ela pretende fazer?";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				link.l1 = "Ela está ficando no meu navio comigo. Ela não é mais uma oficial comum. O controle da ilha vai ser dado ao líder da Irmandade, e tudo que ela vai receber é uma renda. Foi a própria Helen quem decidiu isso.";
				link.l1.go = "saga_84";
			}
			else
			{
				link.l1 = "Ela partiu para Isla Tesoro para assumir o baronato por conta própria.";
				link.l1.go = "saga_85";
			}
		break;
		
		case "saga_84":
			dialog.text = "Bem, "+pchar.name+"... Parabéns! Muitos homens sonharam em estar no seu lugar. Fico feliz que Helen tenha escolhido um homem que realmente a merece. Não poderia haver candidato melhor do que você para ser o companheiro da vida dela.";
			link.l1 = "Obrigado, Jan! Agora gostaria de voltar à nossa conversa sobre Tortuga e Levasseur.";
			link.l1.go = "saga_86";
			if (CheckAttribute(pchar, "questTemp.PZ_DialogSvensonBlock"))
			{
				link.l1 = "Obrigado, Jan!";
				link.l1.go = "saga_87";
			}
		break;
		
		case "saga_85":
			dialog.text = "Maravilha. Ela merece isso. Acho que o novo chefe da Irmandade vai ajudá-la a cuidar dos seus assuntos. Ela é uma jovem talentosa e inteligente, aprende rápido e pode dominar qualquer coisa. Obrigado, "+pchar.name+"! Helen é como uma filha para mim e fico radiante que um futuro tão maravilhoso tenha se aberto para ela.";
			link.l1 = "De nada, Jan... Mas enfim, gostaria de voltar à nossa conversa sobre Tortuga e Levasseur.";
			link.l1.go = "saga_86";
			if (CheckAttribute(pchar, "questTemp.PZ_DialogSvensonBlock"))
			{
				link.l1 = "De nada, Jan.";
				link.l1.go = "saga_87";
			}
		break;
		
		case "saga_86":
			sTemp = "Shark Dodson";
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus Tyrex";
			dialog.text = "Enquanto você estava fora, "+sTemp+"  já conversamos sobre isso e chegamos a um acordo sobre o destino de Levasseur. Navegue até Isla Tesoro e fale com nosso novo chefe, ele vai te contar os detalhes do nosso plano e te ajudar no que puder.";
			link.l1 = "Finalmente posso sentir o cheiro da pólvora! Sem tempo a perder, estou indo para Isla Tesoro!";
			link.l1.go = "saga_87";
		break;
		
		case "saga_87":
			dialog.text = ""+pchar.name+", espere um pouco. Tenho alguns presentes para você, em agradecimento pela sua ajuda com a Helen e os Irmãos. O primeiro é o amuleto encantado do Sarraceno, vindo do Extremo Oriente. Seus encantos fortalecem a disciplina a bordo, posso garantir pessoalmente. Aqui está.";
			link.l1 = "Obrigado!";
			link.l1.go = "saga_88";
		break;
		
		case "saga_88":
			GiveItem2Character(pchar, "talisman4");
			Log_Info("You've received the 'Janissary' amulet.");
			PlaySound("interface\important_item.wav");
			dialog.text = "A segunda é apenas uma lembrança de aventuras passadas. Convenci o Conselho a abandonar essa tradição ridícula de jogar fragmentos de pedra ao vento. Eles não servem mais para nada. Vou te dar. Quem sabe você encontre alguma utilidade para eles.";
			link.l1 = "Um uso para os fragmentos? Hm. Não sei... mas como lembrança, fico muito agradecido!";
			link.l1.go = "saga_89";
		break;
		
		case "saga_89":
			GiveItem2Character(pchar, "splinter_js"); 
			GiveItem2Character(pchar, "splinter_nh"); 
			GiveItem2Character(pchar, "splinter_mt"); 
			GiveItem2Character(pchar, "splinter_zm"); 
			GiveItem2Character(pchar, "splinter_jb"); 
			Log_Info("You've received five ornamental pattern fragments");
			dialog.text = "Bem, não se esqueça do seu amigo, "+pchar.name+". Passe lá em casa quando ancorar em Blueweld. Vamos sentar e tomar um rum. Sempre fico feliz em te ver.";
			link.l1 = "Com certeza, Jan. Agora temos algo para lembrar, não é? Ha-ha! Bem, eu já vou indo.";
			link.l1.go = "saga_90";
		break;
		
		case "saga_90":
			dialog.text = "Boa sorte, "+pchar.name+"!";
			link.l1 = "Até logo...";
			link.l1.go = "saga_91";
		break;
		
		case "saga_91":
			DialogExit();
			pchar.questTemp.Saga = "end";
			if (CheckAttribute(pchar, "questTemp.PZ_DialogSvensonBlock")) AddQuestRecord("Saga", "26_1");
			else 
			{
				AddQuestRecord("Saga", "26");
				pchar.questTemp.Terrapin = "islatesoro";
			}
			CloseQuestHeader("Saga");
			ChangeCharacterComplexReputation(pchar, "fame", 5);
		break;
		
	// --> провалы Саги
		case "saga_f_1":
			dialog.text = "É... Parece mesmo que nosso plano foi por água abaixo. Agora não vamos conseguir colocar quem queríamos como chefe da Irmandade. Jackman está morto, isso até que não é ruim. Mas, infelizmente, meu plano não vai dar certo agora. Vamos ter que eleger o chefe da Irmandade do jeito tradicional, e Deus sabe que rumo isso vai tomar...";
			link.l1 = "Que pena. Uma grande pena. E parece que a Helen vai ficar sem a herança dela.";
			link.l1.go = "saga_f_2";
		break;
		
		case "saga_f_2":
			dialog.text = "Sim, "+pchar.name+". E eu gostaria mesmo de te ajudar a tomar Tortuga, de verdade, mas agora nem sei como. Provavelmente não há nada que eu possa fazer para ajudar. Parece que você vai ter que contar apenas com sua própria força e sua habilidade de lutar.";
			link.l1 = "Parece que não resta outra opção... Tudo bem, Jan, vou pensar no que fazer agora. Até mais...";
			link.l1.go = "saga_f_3";
		break;
		
		case "saga_f_3":
			dialog.text = "Passe aqui, "+pchar.name+". Sempre fico feliz em te ver.";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.Saga = "end";
			CloseQuestHeader("Saga");
			CloseQuestHeader("Testament");
		break;
		
		case "saga_l1": // проход первый - отбираем Элен и закрываем вход к Свенсону
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", true); // закрыть кабинет Свенсона
			pchar.questTemp.Saga = "end";
			CloseQuestHeader("Saga");
			// Элен - к разговору
			sld = characterFromId("Helena");
			sld.quest.talk = "late_l1";
			pchar.quest.Saga_Late_1.win_condition.l1 = "Location_Type";
			pchar.quest.Saga_Late_1.win_condition.l1.location_type = "town";
			pchar.quest.Saga_Late_1.function = "Saga_HelenaTalk";
			pchar.questTemp.Saga.Jackman = "true";
			Saga_ChangesIslatesoro(); // вызов перестановки на Исла-Тесоро
		break;
		
		case "saga_l2": // проход второй - отбираем Элен, Натана и Данни в Марун-Таун, чистим квестовый лут
			dialog.text = "Mas, infelizmente, agora já é tarde demais para fazer qualquer coisa. Isla Tesoro foi oficialmente transferida para a autoridade da coroa inglesa. Já tem uma guarnição instalada lá. Isso é um golpe duro para a Irmandade, do qual, receio, não vamos conseguir nos recuperar.";
			link.l1 = "Que terrível... Ah, eu devia ter agido mais rápido. Aí, veja, tudo teria dado certo. Tá bom, Jan, vou pensar no que fazer agora. Até mais...";
			link.l1.go = "saga_l2_1";
		break;
		
		case "saga_l2_1":
			dialog.text = "Passe aqui, "+pchar.name+". Sempre fico feliz em te ver.";
			link.l1 = "...";
			link.l1.go = "saga_l2_2";
		break;
		
		case "saga_l2_2":
			DialogExit();
			pchar.questTemp.Saga = "end";
			CloseQuestHeader("Saga");
			RemoveItems(pchar, "splinter_nh", 1);
			RemoveItems(pchar, "splinter_mt", 1);
			RemoveItems(pchar, "splinter_jb", 1);
			RemoveItems(pchar, "splinter_zm", 1);
			RemoveItems(pchar, "letter_parol", 1);
			RemoveItems(pchar, "map_sharp_full", 1);
			sld = characterFromId("Nathaniel");
			sld.model = "Hawk_2";
			Characters_RefreshModel(sld); // наверно не нужно
			sld.greeting = "nathaniel_2";
			sld.dialog.currentnode = "marun_town";
			ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "sit", "sit1");
			LAi_SetHuberType(sld);
			LocatorReloadEnterDisable("FortOrange_town", "reload6", false); // открыть резиденцию Хоука
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "marun_town";
			sld.greeting = "danny_2";
			ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "goto", "goto1");
			LAi_SetStayType(sld);
			// Элен - к разговору
			sld = characterFromId("Helena");
			sld.quest.talk = "late_l2";
			pchar.quest.Saga_Late_2.win_condition.l1 = "Location_Type";
			pchar.quest.Saga_Late_2.win_condition.l1.location_type = "town";
			pchar.quest.Saga_Late_2.function = "Saga_HelenaTalk";
			Saga_ChangesIslatesoro(); // вызов перестановки на Исла-Тесоро
			pchar.questTemp.Saga_Late = true; // второй атрибут, отсекающий диалоги, на всякий пожарный
		break;
		
		case "saga_l3":
			dialog.text = "Sim... Nós realmente acabamos de sofrer uma derrota dura. E o pior é que estávamos literalmente a um passo da vitória. Caramba! Como isso pôde acontecer, hein, "+pchar.name+"? Você se esforçou tanto, fez tanto, e... que azar miserável!";
			link.l1 = "Eu sou o idiota responsável por isso. Eu devia ter sido mais rápido. E por minha culpa, a Helen vai perder a herança dela. E o plano de Tortuga nunca vai se realizar.";
			link.l1.go = "saga_f_2";
			pchar.questTemp.Saga_Late = true; // второй атрибут, отсекающий диалоги, на всякий пожарный
		break;
	// <-- провалы Саги
		
	//-----------------------------------генератор торговли бакаутом--------------------------------------------
		case "trade_bakaut":
			if (CheckAttribute(pchar, "questTemp.UpgradeBakaut"))
			{
				dialog.text = "Certo, não me importo. Tenho 125 unidades no meu armazém. O preço, como você lembra, é 3.150 por peça.";
				if (PCharDublonsTotal() >= 3150)
				{
					link.l1 = "Certo, combinado. Aqui está. São 3150 doblões.";
					link.l1.go = "trade_bakaut_1";
				}
				else
				{
					link.l1 = "Que azar dos grandes. Deixei meu dinheiro no meu navio. Já volto com ele em um instante.";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Certo, não me importo. Tenho vinte e cinco unidades no meu armazém. O preço, como você lembra, é trinta doblões por peça.";
				if (PCharDublonsTotal() >= 750)
				{
					link.l1 = "Certo, combinado. Aqui está. São setecentos e cinquenta doblões.";
					link.l1.go = "trade_bakaut_1";
				}
				else
				{
					link.l1 = "Que azar dos grandes. Deixei meu dinheiro no navio. Já volto com ele em um instante.";
					link.l1.go = "exit";
				}
			}
			if(sti(pchar.questTemp.SvensonBakaut) >= 1 && !CheckAttribute(pchar, "questTemp.SvensonBakautBlock")) // увеличить объём поставок бакаута
			{
				link.l4 = "Jan, seria possível aumentar o tamanho dos carregamentos de pau-ferro?";
				link.l4.go = "UpgradeBakaut";
			}
			if(sti(pchar.questTemp.SvensonBakaut) >= 1 && CheckAttribute(pchar, "questTemp.SvensonBakautPotom") && PCharDublonsTotal() >= 3000) // увеличить объём поставок бакаута, если в первый раз не принесли
			{
				link.l4 = "Jan, consegui juntar três mil moedas de ouro. Aqui, você pode entregar este presente aos nossos parasitas. Imagino que hoje eles vão ter um dia feliz.";
				link.l4.go = "UpgradeBakaut_Agreed";
			}
		break;
		
		case "trade_bakaut_1":
			RemoveDublonsFromPCharTotal(750);
			Log_Info("You have given 750 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Admirável. Vou mandar meus homens levarem a madeira de ferro até o seu navio.";
			link.l1 = "Obrigado!";
			link.l1.go = "trade_bakaut_2";
		break;
		
		case "trade_bakaut_2":
			dialog.text = "Se quiser comprar mais, volte em duas semanas. Até lá, terei preparado outro lote.";
			link.l1 = "Até mais, Jan. Nos vemos na próxima!";
			link.l1.go = "exit";
			AddCharacterGoods(pchar, GOOD_SANDAL, 25);
			DeleteAttribute(npchar, "quest.trade_bakaut");
			SetFunctionTimerCondition("Bakaut_SvensonAttrReturn", 0, 0, 1, false); // таймер
			AddCharacterExpToSkill(pchar, "Commerce", 100);
		break;
		
		case "UpgradeBakaut": //
			if (startHeroType == 1) sStr = "old friend";
			if (startHeroType == 2) sStr = "old friend";
			if (startHeroType == 3) sStr = "old friend";
			if (startHeroType == 4) sStr = "Helen";
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 80)
			{
				dialog.text = "Que bom que você está gostando do pau-ferro, "+sStr+". Aumentar os embarques não é problema, mas tem um porém, como você deve imaginar. Com volumes maiores, deixamos rastros que podem chamar atenção indesejada, especialmente das autoridades inglesas. Mas se conseguirmos aliados de confiança, ouvidos atentos e gente dentro da residência para nos manter nas sombras, tudo pode ser resolvido. Só que não vai sair barato – três mil dobrões para contornar o tesouro da cidade e as exigências da Inglaterra. Aí sim, posso te fornecer cinco vezes mais. O que me diz?";
				link.l1 = "Três mil dobrões? Jan, isso é um roubo à luz do dia! Não dava pra resolver com menos despesas? Talvez exista um jeito de resolver isso sem gastar tanto assim?";
				link.l1.go = "UpgradeBakaut_1";
				Notification_Skill(true, 80, SKILL_COMMERCE);
			}
			else
			{
				dialog.text = "Boa ideia, mas devo dizer que, para negociar volumes assim, você precisa de um pouco mais de experiência e habilidade. Se apressar só traz mais risco do que vantagem. Vamos fazer assim: ganhe mais experiência e, quando estiver pronto para lotes maiores, volte aqui. Aí conversamos direito sobre tudo.";
				link.l1 = "Hmm... Tudo bem. Vamos voltar a essa conversa depois.";
				link.l1.go = "exit";
				Notification_Skill(false, 80, SKILL_COMMERCE);
			}
		break;
		
		case "UpgradeBakaut_1":
			dialog.text = "Ai de mim, "+pchar.name+", esse é o preço da paz hoje em dia – o apetite desses senhores de perucas e uniformes só aumenta a cada dia. Nada os atrai mais do que dobrões tilintando em seus cofres. Garanto a você um desconto de quinze por cento em todos os próximos carregamentos, se isso te consola.";
			link.l1 = "Malditos! Pedir uma quantia dessas! Com tanta ganância, deveriam estar comprando tesouros de reis, não negociando silêncio! Jan, talvez devêssemos... mostrar a eles quem é que manda de verdade nesse arquipélago, hein?";
			link.l1.go = "UpgradeBakaut_2";
		break;
		
		case "UpgradeBakaut_2":
			if (startHeroType == 1) sStr = "my friend";
			if (startHeroType == 2) sStr = "my friend";
			if (startHeroType == 3) sStr = "my friend";
			if (startHeroType == 4) sStr = "Helen";
			dialog.text = "Ha! Que espírito você tem, "+sStr+"! Mas enfrentar toda a Inglaterra não me interessa agora, e já não sou tão jovem quanto antes. Vamos apenas pagar esses sanguessugas e deixá-los quietos – temos nossos próprios assuntos para resolver. Junte a quantia necessária e nosso caminho ficará livre, sem perguntas desnecessárias!";
			if (PCharDublonsTotal() >= 3000)
			{
				link.l1 = "Está bem, Jan, você me convenceu. Que seja, já que não há outro jeito. Aqui estão seus três mil doblões. Só lembre-se: não pretendo sustentar esses mãos-de-vaca para sempre.";
				link.l1.go = "UpgradeBakaut_Agreed";
			}
			link.l2 = "Que o diabo os leve, Jan! Você acha mesmo que não tem outro jeito? Tá bom. Eu vou encontrar esses dobrões. Mas agora eu não tenho esse dinheiro todo.";
			link.l2.go = "UpgradeBakaut_4";
			link.l3 = "Droga, Jan, você realmente quer que eu alimente esses oficiais e suas madames mimadas? Eles ficam sentados, não fazem nada e só sabem pedir dinheiro! Não, não gosto disso! Não vou encher os bolsos deles com o meu suor e sangue! Vamos voltar aos termos anteriores. Isso já basta pra mim.";
			link.l3.go = "UpgradeBakaut_3";
		break;
		
		case "UpgradeBakaut_Agreed":
			dialog.text = "Agora sim! Com a sua contribuição, nosso negócio vai prosperar, e aqueles mãos de vaca vão receber o que merecem – e nem vão ousar olhar para o lado do pau-ferro. Te garanto, logo vamos recuperar todo o investimento cem vezes mais.";
			link.l1 = "Espero que sim, Jan, espero que sim.";
			link.l1.go = "UpgradeBakaut_Agreed_1";
			RemoveDublonsFromPCharTotal(3000);
			AddQuestRecordInfo("Unique_Goods", "1_1");
			pchar.questTemp.UpgradeBakaut = true;
			pchar.questTemp.SvensonBakautBlock = true;
			DeleteAttribute(pchar, "questTemp.SvensonBakautPotom");
		break;
		
		case "UpgradeBakaut_Agreed_1":
			dialog.text = "Os negócios vão seguir como devem, não precisa se preocupar. Agora, quanto aos nossos próximos acordos: vou deixar 125 toras de pau-ferro separadas para você, como antes, nos dias 14 e 28 de cada mês. Pode levar todo o lote por 3.150 dobrões.";
			link.l1 = "Eu gosto muito mais dessas conversas! Cento e vinte e cinco toras, então? Excelente, Jan. Bem, até logo, vou esperar pela entrega!";
			link.l1.go = "exit";
		break;
		
		case "UpgradeBakaut_3":
			if (startHeroType == 1) sStr = "old friend";
			if (startHeroType == 2) sStr = "old friend";
			if (startHeroType == 3) sStr = "old friend";
			if (startHeroType == 4) sStr = "Helen";
			dialog.text = "Como quiser, "+sStr+". E não se exalte tanto. É assim que o mundo funciona.";
			link.l1 = "Sim, Jan, eu sei como este mundo funciona. Mas isso não significa que eu tenha que aceitar. Certo, preciso ir.";
			link.l1.go = "exit";
			pchar.questTemp.SvensonBakautBlock = true;
		break;
		
		case "UpgradeBakaut_4":
			dialog.text = "Vou esperar até você conseguir o dinheiro. Sei que vai dar um jeito. Assim que estiver pronto, estarei te esperando com o dinheiro e seguiremos em frente.";
			link.l1 = "Certo.";
			link.l1.go = "exit";
			pchar.questTemp.SvensonBakautBlock = true;
			pchar.questTemp.SvensonBakautPotom = true;
		break;
		// <-- генератор бакаута
		
	//----------------------------------- штурм рудника --------------------------------------------
		case "mine_attack":
			dialog.text = "Que bom te ver, "+pchar.name+". Meu pessoal está pronto. Vamos para a selva?";
			link.l1 = "Sim, Jan. Meu grupo está pronto para a batalha.";
			link.l1.go = "mine_attack_1";
		break;
		
		case "mine_attack_1":
			dialog.text = "Vamos então. A mina fica no meio da selva, bem ao longo desta trilha. Mantenha-se à direita na bifurcação. Em frente!";
			link.l1 = "Avante!";
			link.l1.go = "mine_attack_2";
		break;
		
		case "mine_attack_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Svensons_off_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			for (i=1; i<=12; i++)
			{
				sld = characterFromId("Svensons_sold_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("shore53", "boat", true);
			LocatorReloadEnterDisable("mine_03", "reload3_back", true);
			LocatorReloadEnterDisable("mine_02", "reload3_back", true);
			pchar.quest.Saga_MineAttack_01.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_01.win_condition.l1.location = "Mine_02";
			pchar.quest.Saga_MineAttack_01.function = "Saga_PrepareMineAttackTail";
		break;
		
		case "mine_attack_3":
			dialog.text = "Então, "+pchar.name+", chegou a hora de discutirmos como vamos prosseguir com essa operação. Já enviei vários índios Miskito adiante para inspecionar a área e elaborei um plano de ação com base nas observações deles.";
			link.l1 = "Me conte tudo!";
			link.l1.go = "mine_attack_4";
		break;
		
		case "mine_attack_4":
			dialog.text = "A cova representa a mina sob as montanhas na selva. Há um acampamento perto da entrada da mina. Algumas casas e uma paliçada. Um caminho leva até a paliçada. Veja, ele leva a um pequeno espaço aberto na selva, não muito longe daqui. É lá que fica a entrada principal da cova.\nEla representa um muro de pedra alto entre duas colinas íngremes, impedindo qualquer um de entrar sorrateiramente. Os portões são guardados por seis homens. Não é grande coisa, mas eles também instalaram dois canhões ali. Esse é o maior problema.\nDuas rajadas de metralha poderiam derrubar metade do nosso grupo, o que seria um desastre, então atacar de frente está fora de questão...";
			link.l1 = "Ha! Mas temos uma carta na manga — sabemos a senha que vai nos deixar entrar...";
			link.l1.go = "mine_attack_5";
		break;
		
		case "mine_attack_5":
			dialog.text = "Isso mesmo. Vamos usar isso a nosso favor, mas por enquanto deixe-me te contar todo o meu plano até o final.";
			link.l1 = "Certo, Jan. Estou ouvindo.";
			link.l1.go = "mine_attack_6";
		break;
		
		case "mine_attack_6":
			dialog.text = "Existe outra entrada para o poço – por aquele caminho na selva. Ele contorna as colinas que protegem a mina e leva a uma clareira pequena e estreita, que pode ser usada para entrar. Mas os bandidos ergueram uma cerca alta e colocaram guardas ali. A cerca tem pequenos portões, mas eles estão barricados do outro lado.\nAgora preste atenção no que vamos fazer. Vamos eliminar os que guardam a segunda entrada da mina. Parte do nosso grupo vai ficar lá e arranjar um tronco para usar como aríete.\nNós vamos voltar para a entrada principal e eliminar as equipes dos canhões. A senha que temos vai nos ajudar duas vezes. Depois, atacaremos a mina pelos dois lados. Eu vou liderar a primeira unidade de ataque e você vai comandar a segunda.";
			link.l1 = "Bem, faz sentido. Vamos obrigá-los a lutar em duas frentes. Avante!";
			link.l1.go = "mine_attack_7";
		break;
		
		case "mine_attack_7":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.quest.mine01 = "true";
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationDisableOfficersGen("mine_01", true);//офицеров не пускать
			pchar.quest.Saga_MineAttack_02.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_02.win_condition.l1.location = "Mine_04";
			pchar.quest.Saga_MineAttack_02.function = "Saga_PrepareMineAttackTail";
		break;
		
		case "mine_attack_8":
			dialog.text = "Right, here we are... This is the path to the bandits' fence. Now we need to decide how to deal with them. If we send the whole squad, it will be too suspicious and they'll raise the alarm.\nWe should send a small group of three, no more; this group will be able to get close enough without arousing suspicion and attack by surprise. I can't lead the group, my face is too well known around here.\nSo it's up to you, "+pchar.name+", because you are the only one I can trust to command without risking the whole operation. I will give you Gregory and a musketeer to assist...";
			link.l1 = "Quantos guardas estão na cerca de piquete?";
			link.l1.go = "mine_attack_9";
		break;
		
		case "mine_attack_9":
			dialog.text = "Quatro. Dois mosqueteiros e dois soldados.";
			link.l1 = "Vamos pegá-los...";
			link.l1.go = "mine_attack_10";
		break;
		
		case "mine_attack_10":
			dialog.text = "Te conhecendo, não duvido nem por um segundo. Chegue até eles e diga que foi o Jackman quem te mandou. Passe a senha. E então, quando todos estiverem tranquilos... aja conforme a situação.";
			link.l1 = "Certo. Vamos mantê-los atentos.";
			link.l1.go = "mine_attack_11";
		break;
		
		case "mine_attack_11":
			dialog.text = "Boa sorte, "+pchar.name+"!";
			link.l1 = "...";
			link.l1.go = "mine_attack_12";
		break;
		
		case "mine_attack_12":
			DialogExit();
			LAi_SetStayTypeNoGroup(npchar);
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Svensons_off_"+i);
				LAi_SetStayTypeNoGroup(sld);
				if (i == 2)
				{
					LAi_SetActorType(sld);
					LAi_ActorFollowEverywhere(sld, "", -1);
				}
			}
			for (i=1; i<=12; i++)
			{
				sld = characterFromId("Svensons_sold_"+i);
				LAi_SetStayTypeNoGroup(sld);
				if (i == 12)
				{
					LAi_SetActorType(sld);
					LAi_ActorFollowEverywhere(sld, "", -1);
				}
			}
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("Ourmine_sold_"+i);
				LAi_SetStayTypeNoGroup(sld);
				LAi_CharacterDisableDialog(sld);//запрет диалога
			}
			chrDisableReloadToLocation = false;//открыть локацию
			DeleteAttribute(npchar, "quest.mine01");
			npchar.quest.mine02 = "true";
			pchar.questTemp.Saga.MineAttack = "true";
			pchar.quest.Saga_MineAttack_03.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_03.win_condition.l1.location = "Mine_01";
			pchar.quest.Saga_MineAttack_03.function = "Saga_MineAttackTail";
		break;
		
		case "mine_attack_13":
			dialog.text = "Mandou bem, "+pchar.name+"! Você saiu por cima, como sempre. Agora, meus rapazes vão se preparar para soltar uma tempestade deste lado da mina e vamos limpar a entrada principal.";
			link.l1 = "Então eu vou ter que ir falar com os guardas de novo?";
			if (GetCharacterIndex("Svensons_off_2") != -1 && GetCharacterIndex("Svensons_sold_12") != -1) link.l1.go = "mine_attack_14";
			else link.l1.go = "mine_attack_14a";
		break;
		
		case "mine_attack_14a":
			dialog.text = "Sim, "+pchar.name+", mais uma vez. Eu adoraria ir pessoalmente, mas com certeza me reconheceriam e toda a operação iria por água abaixo. Vai ser mais perigoso, pois há mais inimigos, e não se esqueça das armas.";
			link.l1 = "Vou levar meus oficiais comigo.";
			link.l1.go = "mine_attack_14_1";
		break;
		
		case "mine_attack_14":
			dialog.text = "Sim, "+pchar.name+", mais uma vez. Eu adoraria ir pessoalmente, mas com certeza me reconheceriam e toda a operação iria por água abaixo. Vai ser mais perigoso, pois há mais inimigos, e não se esqueça das armas. Quem você vai levar com você para ajudar? Seus oficiais ou Gregory e o mosqueteiro, como da última vez?";
			link.l1 = "Vou levar meus oficiais.";
			link.l1.go = "mine_attack_14_1";
			link.l2 = "Vou levar o Gregory e o mosqueteiro.";
			link.l2.go = "mine_attack_14_2";
		break;
		
		case "mine_attack_14_1":
			dialog.text = "Certo. Os seus próprios homens são o seu melhor apoio. Agora vamos voltar para a entrada principal. Você lembra o caminho?";
			link.l1 = "Claro. Voltamos pelo caminho por onde viemos, depois mantemos à esquerda, e então seguimos pela trilha ao redor do morro.";
			link.l1.go = "mine_attack_15";
			pchar.questTemp.Saga.MineAttack = "officer";
		break;
		
		case "mine_attack_14_2":
			dialog.text = "Certo. Você conseguiu da primeira vez, então repetir não deve ser difícil. Agora vamos voltar para a entrada principal. Você lembra o caminho?";
			link.l1 = "Claro. Voltamos pelo caminho por onde viemos, depois mantemos à esquerda e seguimos pela trilha ao redor do morro.";
			link.l1.go = "mine_attack_15";
			pchar.questTemp.Saga.MineAttack = "soldiers";
		break;
		
		case "mine_attack_15":
			dialog.text = "Sem tempo a perder. Vamos em frente!";
			link.l1 = "Em frente!";
			link.l1.go = "mine_attack_16";
		break;
		
		case "mine_attack_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			for (i=1; i<=2; i++)
			{
				if (GetCharacterIndex("Svensons_off_"+i) != -1)
				{
					sld = characterFromId("Svensons_off_"+i);
					LAi_SetActorType(sld);
					LAi_ActorFollowEverywhere(sld, "", -1);
				}
			}
			for (i=1; i<=12; i++)
			{
				sld = characterFromId("Svensons_sold_"+i);
				LAi_SetActorType(sld);
				if (pchar.questTemp.Saga.MineAttack == "soldiers" && i == 12) LAi_ActorFollowEverywhere(sld, "", -1);
				else LAi_ActorRunToLocation(sld, "reload", "reload3_back", "mine_01", "goto", "goto"+i, "", 5);
			}
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("Ourmine_sold_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationDisableOfficersGen("mine_01", false);//офицеров пускать
			if (pchar.questTemp.Saga.MineAttack == "soldiers") LAi_LocationDisableOfficersGen("mine_exit", true);//офицеров не пускать
			LocatorReloadEnterDisable("mine_03", "reload3_back", false);
			LocatorReloadEnterDisable("mine_02", "reload3_back", false);
			DeleteAttribute(npchar, "quest.mine02");
			npchar.quest.mine03 = "true";
			pchar.quest.Saga_MineAttack_05.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_05.win_condition.l1.location = "Mine_02";
			pchar.quest.Saga_MineAttack_05.function = "Saga_PrepareMineAttackTail";
		break;
		
		case "mine_attack_17":
			dialog.text = "Certo, "+pchar.name+", ouça estas instruções finais. Os demônios que guardam os portões são duros na queda, então não vai ser fácil pra você. Seu objetivo principal é matar os artilheiros que ficam perto dos portões, porque não vamos conseguir te ajudar se eles ainda estiverem vivos.\nAssim que os dois estiverem mortos e não houver mais risco de uma saraivada de tiros, todos nós vamos entrar e acabar com eles em segundos. Entendeu, "+pchar.name+"? Não tente bancar o herói, mate os artilheiros e deixe o resto conosco.";
			link.l1 = "Tá bom, Jan. Vou tentar fazer tudo como combinamos. E se algo der errado, improviso na hora.";
			link.l1.go = "mine_attack_18";
		break;
		
		case "mine_attack_18":
			dialog.text = "Parece bom. Que Deus esteja com você!";
			link.l1 = "Obrigado...";
			link.l1.go = "mine_attack_19";
		break;
		
		case "mine_attack_19":
			DialogExit();
			LAi_SetStayTypeNoGroup(npchar);
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			for (i=1; i<=2; i++)
			{
				if (GetCharacterIndex("Svensons_off_"+i) != -1)
				{
					sld = characterFromId("Svensons_off_"+i);
					if (pchar.questTemp.Saga.MineAttack == "soldiers" && i == 2)
					{
						LAi_SetActorType(sld);
						LAi_ActorFollowEverywhere(sld, "", -1);
					}
					else LAi_SetStayTypeNoGroup(sld);
				}
			}
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("Ourmine_sold_"+i);
				LAi_SetStayTypeNoGroup(sld);
			}
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationDisableOfficersGen("mine_01", false);//офицеров пускать
			DeleteAttribute(npchar, "quest.mine03");
			pchar.quest.Saga_MineAttack_06.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_06.win_condition.l1.location = "Mine_exit";
			pchar.quest.Saga_MineAttack_06.function = "Saga_MineAttackTail";
		break;
		
		case "mine_attack_20":
			dialog.text = "Ufa! Derrubamos aqueles filhos da mãe... Eram uns desgraçados bem atrevidos. Dá pra ver que esses mercenários já serviram nas tropas regulares. Fizemos um barulho danado aqui, acho que podem ter ouvido. Não temos um minuto a perder! "+pchar.name+", chegou a hora de atacarmos a mina.\nVou voltar para o meu grupo na segunda entrada – eles já devem ter encontrado e preparado um tronco para arrombar a cerca. Você e seus homens vão entrar pelos portões centrais. Esperem por nós por meia hora, não ataquem imediatamente...";
			link.l1 = "Jan, se eles ouviram os tiros na mina, não temos nem meia hora. Esses bandidos podem montar uma linha de defesa ou vir direto para os portões centrais e atacar meu grupo com tudo o que têm...";
			link.l1.go = "mine_attack_21";
		break;
		
		case "mine_attack_21":
			dialog.text = "Merda! Isso é bem possível. O que você sugere que a gente faça?";
			link.l1 = "Hum... Ha! Tive uma ideia! Canhões! Olhe ao redor. Não tem só bala de canhão, mas também bombas! Agora esses bandidos estão perdidos! Por que não pensei nisso antes?!";
			link.l1.go = "mine_attack_22";
		break;
		
		case "mine_attack_22":
			dialog.text = "O que você acha que devemos fazer?";
			link.l1 = "Vamos levar só um canhão. Com apenas um, vamos conseguir nos mover muito mais rápido e com eficiência. Vamos rolar ele para dentro, além dos portões, até a mina e posicioná-lo lá. Se eles atacarem, vão levar um baita estouro, e se ficarem na defensiva, a gente bombardeia o acampamento deles. Você pode me dizer exatamente onde fica o acampamento atrás dos portões?";
			link.l1.go = "mine_attack_23";
		break;
		
		case "mine_attack_23":
			dialog.text = "O acampamento fica numa área baixa perto de uma montanha. Tem uma trilha logo depois dos portões que desce e contorna o morro. O acampamento está logo atrás desse morro.";
			link.l1 = "Excelente! Vamos nos posicionar no topo da trilha e lançar algumas bombas por cima da colina direto no ninho deles! Ah, eles vão ficar pulando pra todo lado!";
			link.l1.go = "mine_attack_24";
		break;
		
		case "mine_attack_24":
			dialog.text = "Droga, "+pchar.name+", muito bem! Avante a toda velocidade! Vou deixar o Randolf sob seu comando, ele é meu melhor artilheiro. Faça dele seu artilheiro e ele não vai te decepcionar. Agora vou para minha unidade.";
			link.l1 = "Certo. Vou bombardear as posições deles sem piedade por meia hora até você arrombar os portões.";
			link.l1.go = "mine_attack_25";
		break;
		
		case "mine_attack_25":
			dialog.text = "Vou tentar chegar a tempo. Te vejo no acampamento!";
			link.l1 = "Fechado... Esquadrão! Ouçam meu comando! Preparem-se para mover o canhão para uma nova posição! Levem pólvora, bombas e balins com vocês! Para a mina pelos portões. Avante, marchar!";
			link.l1.go = "mine_attack_26";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "none", "", "", "", 5);
			if (GetCharacterIndex("Svensons_off_2") != -1)
			{
				sld = characterFromId("Svensons_off_2");
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "", 5);
			}
		break;
		
		case "mine_attack_26":
			DialogExit();
			int n = Findlocation("mine_exit");
			DeleteAttribute(&locations[n], "mine_bandits");
			LocatorReloadEnterDisable("mine_exit", "reload1_back", false);
			pchar.quest.Saga_MineAttack_07.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_07.win_condition.l1.location = "Mine";
			pchar.quest.Saga_MineAttack_07.function = "Saga_MineGunAttack";
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("mine_exit", "reload2_back", true);
			LAi_LocationDisableOfficersGen("mine_exit", false); // офицеров пускать
			n = Findlocation("mine");
			locations[n].models.always.Gun = "mortair";
			Locations[n].models.always.Gun.locator.group = "goto";
			Locations[n].models.always.Gun.locator.name = "fire"; // орудие - к бою!
			Locations[n].hidden_sound = true;
		break;
		
		case "mine_attack_27":
			dialog.text = "Ufa, não chegamos tarde demais? "+pchar.name+"?";
			link.l1 = "Jan, pelo amor de Deus! O que te atrasou tanto? Meu grupo acabou de levar uma baita surra!";
			link.l1.go = "mine_attack_28";
		break;
		
		case "mine_attack_28":
			dialog.text = "Aquela maldita cerca de madeira era mesmo resistente. Quebramos ela à força... Ouvimos seu barulho e a confusão. Parece que você limpou bem esse lugar! Está pegando fogo até o chão!";
			link.l1 = "As façanhas do Randolf... Queria que você tivesse visto quantos canalhas enterramos antes de finalmente partir para o combate corpo a corpo!";
			link.l1.go = "mine_attack_29";
		break;
		
		case "mine_attack_29":
			dialog.text = "Caramba! Tiro meu chapéu para você, "+pchar.name+". Muito bem! Agora, sobre as perdas... você sempre as terá quando estiver em guerra.";
			link.l1 = "Agora o que precisamos fazer é limpar a própria mina. É possível que alguns sobreviventes estejam escondidos lá dentro.";
			link.l1.go = "mine_attack_30";
		break;
		
		case "mine_attack_30":
			dialog.text = "Vamos, só nós dois. Vamos ver o que está acontecendo lá.";
			link.l1 = "Parece um bom plano!";
			link.l1.go = "mine_attack_31";
		break;
		
		case "mine_attack_31":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetCheckMinHP(npchar, 10, true, "");
			TakeNItems(npchar, "potion2", 8); 
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4", "Mine_mines", "reload", "reload1", "", -1);
			LAi_LocationDisableOfficersGen("Mine_mines", true);//офицеров не пускать
			pchar.quest.Saga_MineAttack_08.win_condition.l1 = "locator";
			pchar.quest.Saga_MineAttack_08.win_condition.l1.location = "mine";
			pchar.quest.Saga_MineAttack_08.win_condition.l1.locator_group = "reload";
			pchar.quest.Saga_MineAttack_08.win_condition.l1.locator = "reload4";
			pchar.quest.Saga_MineAttack_08.function = "Saga_MineAttackMines";
		break;
		
		case "mine_attack_32a":
			dialog.text = "Ainda não revistamos toda a mina! Te garanto que ainda tem mais desses canalhas escondidos aqui!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "mine_attack_32a";
		break;
		
		case "mine_attack_32":
			dialog.text = "Acho que não sobrou mais nenhum canalha...";
			link.l1 = "Jan, eu achei que a gente só vinha aqui pra entender a situação...";
			link.l1.go = "mine_attack_33";
		break;
		
		case "mine_attack_33":
			dialog.text = "Ha-ha, bom, eu não te disse que seria uma exploração especial, uma exploração sangrenta... Faz tempo que não tinha um aquecimento desses! Agora todos podem ter certeza de que nenhum canalha escapou desta mina!";
			link.l1 = "E então, o que vamos fazer agora, Jan?";
			link.l1.go = "mine_attack_34";
		break;
		
		case "mine_attack_34":
			dialog.text = "O que você quer dizer com 'o que vamos fazer agora'? Vamos procurar ouro e prata. Duvido que Jackman tenha mantido essa fortaleza aqui só por tédio. Ele deixou uma guarnição inteira de prontidão. Viu os escravizados na mina? Descubra onde eles estão guardando o minério.";
			link.l1 = "Tudo bem. Então você vai interrogar os escravos e eu vou subir para vasculhar todas as casas do acampamento, talvez eu encontre alguma coisa.";
			link.l1.go = "mine_attack_35";
		break;
		
		case "mine_attack_35":
			dialog.text = "Te peguei! Hora de agir!";
			link.l1 = "...";
			link.l1.go = "mine_attack_36";
		break;
		
		case "mine_attack_36":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_SetImmortal(npchar, true);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("mine", "reload1", true);
			LocatorReloadEnterDisable("mine", "reload6", true);//закрыть выходы с рудника
			pchar.quest.Saga_Mine_letter.win_condition.l1 = "item";
			pchar.quest.Saga_Mine_letter.win_condition.l1.item = "letter_mine";
			pchar.quest.Saga_Mine_letter.function = "Saga_FindMineLetter";
			NextDiag.CurrentNode = "mine_attack_36a";
		break;
		
		case "mine_attack_36a":
			dialog.text = "Vai, camarada. E revira essas cabanas miseráveis de cabeça pra baixo!";
			link.l1 = "Estou a caminho!";
			link.l1.go = "exit";
			NextDiag.TempNode = "mine_attack_36a";
		break;
		
		case "mine_attack_37":
			dialog.text = "Ha-ha! "+pchar.name+", que bom que você se ofereceu para vir comigo destruir essa mina! É mais uma prova clara de que você nasceu com muita sorte.";
			link.l1 = "Você encontrou ouro?";
			link.l1.go = "mine_attack_38";
		break;
		
		case "mine_attack_38":
			dialog.text = "Sim, droga! Não era ouro, mas prata, e uma boa pilha dela. Se chegássemos um dia depois, eles já teriam levado tudo do acampamento. Por isso tinha tanto bandido aqui – eram o grupo de escolta.\nGraças a você, chegamos a tempo. Sem você, eu ainda estaria juntando gente. Parabéns, parceiro!";
			link.l1 = "Ha! Entendi... Quanto prata nós temos?";
			link.l1.go = "mine_attack_39";
		break;
		
		case "mine_attack_39":
			dialog.text = "Temos cerca de quatro mil unidades. Vamos dividir em duas partes – metade pra mim, metade pra você, como combinamos.";
			link.l1 = "Incrível! Podemos ganhar uma boa grana com essa mercadoria!";
			link.l1.go = "mine_attack_40";
		break;
		
		case "mine_attack_40":
			dialog.text = "Com certeza... Achou alguma coisa de valor?";
			link.l1 = "Não. Não tem nem um doblão nessas pocilgas. Mas encontrei uns papéis. Li e descobri que o dono dessa mina é um tal de Lawrence Beltrope, de Port Royal.";
			link.l1.go = "mine_attack_41";
		break;
		
		case "mine_attack_41":
			dialog.text = "Ah, é mesmo? Deixe-me ver esses documentos...";
			link.l1 = "Aqui está.";
			link.l1.go = "mine_attack_42";
		break;
		
		case "mine_attack_42":
			RemoveItems(pchar, "letter_mine", 1);
			dialog.text = "(lendo)... Certo... Beltrope? Conheço esse sobrenome de algum lugar. Ah, sim! Thomas Beltrope! Que interessante... Tudo bem, vou investigar isso quando voltar para Blueweld. Vou ficar com esses documentos, se não se importar?";
			link.l1 = "De jeito nenhum. Não preciso deles pra nada.";
			link.l1.go = "mine_attack_43";
		break;
		
		case "mine_attack_43":
			dialog.text = "Ótimo. Agora vem a melhor parte: vou transportar a prata para os navios. Os miskitos vão nos ajudar com isso. Vamos preparar uma carroça... Enquanto isso, pode ir descansar, "+pchar.name+". Você merece isso mais do que qualquer um!";
			link.l1 = "Obrigado, Jan. Vamos acampar naquela colina, o cheiro de cinzas aqui está insuportável. Sim, e precisamos apagar o fogo nessas cabanas. Vai saber, talvez um dia elas ainda nos sirvam para alguma coisa...";
			link.l1.go = "mine_attack_44";
		break;
		
		case "mine_attack_44":
			dialog.text = "Está pensando em tomar posse da mina? Ha-ha! Eu já considerei essa ideia, mas saquear é uma coisa, tomar como propriedade é outra. Amigo, ela já tem dono. Podemos arranjar problemas com as autoridades inglesas.\nAlém disso, os escravos com quem conversei me disseram que todas as veias daqui já estão praticamente esgotadas – grandes quantidades de prata já foram tiradas daqui várias vezes. Receio que esta mina já deu o que tinha que dar.";
			link.l1 = "Hm... Vamos ver. Talvez nem tudo esteja perdido. Certo, eu realmente preciso descansar um pouco. Até mais tarde, Jan";
			link.l1.go = "mine_attack_45";
		break;
		
		case "mine_attack_45":
			dialog.text = "Vá em frente. E não se preocupe com nada. Nós cuidaremos do resto.";
			link.l1 = "...";
			link.l1.go = "mine_attack_46";
		break;
		
		case "mine_attack_46":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "rld", "attack1", "Saga_MineWaitTime", -1);
			n = Findlocation("mine");
			DeleteAttribute(&locations[n], "hidden_sound");
			DeleteAttribute(&locations[n], "hidden_fire");
			n = Findlocation("mine_exit");
			DeleteAttribute(&locations[n], "models.always.Gun1");
		break;
		
		case "mine_attack_47":
			dialog.text = "Descansou bem, "+pchar.name+"?";
			link.l1 = "Não foi ruim... Mas, sinceramente, eu daria tudo pra achar uma taverna, tomar um gole e dormir numa cama limpa.";
			link.l1.go = "mine_attack_48";
		break;
		
		case "mine_attack_48":
			dialog.text = "Os índios já trouxeram a prata até a praia e estão carregando-a no seu navio sob a supervisão dos meus oficiais. Você já pode voltar. Seu desejo por rum, uma taverna e uma cama logo será realizado. E gostaria que você passasse na minha casa daqui a cinco dias, ainda temos muita coisa para resolver.";
			link.l1 = "Beleza, Jan. Te vejo em Blueweld em cinco dias! Boa sorte!";
			link.l1.go = "mine_attack_49";
		break;
		
		case "mine_attack_49":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4", "none", "", "", "", 15.0);
			LocatorReloadEnterDisable("shore53", "boat", false);
			LocatorReloadEnterDisable("mine", "reload1", false);
			LocatorReloadEnterDisable("mine", "reload6", false);
			LocatorReloadEnterDisable("mine_01", "reload3_back", false);
			LocatorReloadEnterDisable("mine_exit", "reload2_back", false); //открыть выходы с рудника
			LAi_LocationDisableOfficersGen("mine_mines", false); // офицеров пускать
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			SetFunctionTimerCondition("Saga_ReturnFromMine", 0, 0, 5, false); // таймер
			pchar.questTemp.Saga.Mines = "true"; // после Саги рудник будет разрабатываться
			ChangeCharacterComplexReputation(pchar, "fame", 2);
			DoQuestReloadToLocation("Shore53", "goto", "goto6", "");
		break;
		// <-- штурм рудника
		
		case "helensleep":
			dialog.text = "";
			link.l1 = "Jan, não grite comigo. Vamos resolver isso como pessoas sensatas – lembre-se, temos negócios a tratar!";
			link.l1.go = "helensleep_1";
		break;
		
		case "helensleep_1":
			dialog.text = "Vou soltar meus cães em cima de você agora mesmo, seu verme! Esqueça o Levasseur e suma daqui!";
			link.l1 = "Jan! Me escuta...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenSleep_SvensonThrowOut");
		break;
		
		case "after_drinking":
			dialog.text = "Que barril? Quanto à Helen, pode deixar que eu dou um bom puxão de orelha nela... Brincadeira, Charles, só brincadeira! Eu entendo como é, e quanto à Joanna – tomara que essa história faça ela refletir um pouco – ela anda especialmente irritada ultimamente, sabe... Bem, é a vida. De qualquer forma, boa sorte pra você em Cartagena!";
			link.l1 = "Até a próxima, Jan.";
			link.l1.go = "exit";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
