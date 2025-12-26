// Лукас Роденбург - вице-директор ГВИК
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Holl"))
			{
				dialog.text = "Fale logo, rapaz, mas seja rápido. Sou um homem ocupado.";
				link.l1 = "Ouvi dizer que você está contratando capitães.";
				link.l1.go = "Holl_start";	
			break;
			}
			dialog.text = "Tem algum trabalho para mim?";
			link.l1 = "Não, desculpe. Estou de saída.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Second_time":
		if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
		{
			if (pchar.questTemp.HWIC.Holl == "BaltazarEsc")
			{
				dialog.text = "Era para você já estar a meio caminho de Sint Maarten agora, kapitein.";
				link.l1 = "Estou me preparando para zarpar, senhor.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "BaltazarCom")
			{
				dialog.text = "Ah, kapitein, aí está você! Não te vi chegando, acabei de terminar de ler a carta do Ridderbrock. Você causou uma bela impressão. Ele te chama de 'guardião dos mercadores e flagelo dos piratas. Um presente de Deus para a Companhia!' O que me diz disso?";
				link.l1 = "Eu prefiro continuar sendo apenas um capitão comum. Um capitão comum, mas rico.";
				link.l1.go = "SantiagoTrip";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "SantiagoTripBegin")
			{
				dialog.text = "Por que você ainda está aqui e não a caminho de Cuba?!";
				link.l1 = "Sim, sim, já estou a caminho, mynheer.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "SantiagoTripFinal")
			{
				sld = characterFromId("Santiago_usurer");
				dialog.text = "Ah, capitão! Admito que já estava começando a me preocupar. Como foi?";
				link.l1 = "Não foi sem dificuldades, mas depois te conto sobre isso. Primeiro, aos negócios. Señor "+GetFullName(sld)+" mandou eu te dizer o seguinte: 'esse homem tem que morrer.' Aí o Geraldi vai considerar o assunto encerrado. Ele também disse que essa decisão é a vontade da família deles.";
				link.l1.go = "SantiagoTrip_8";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "SantiagoTripComplete")
			{
				dialog.text = "Que bom ver você, kapitein! Fico feliz que tenha vindo me procurar.";
				link.l1 = "Bom dia, senhor. Imagino que tenha outro trabalho da Companhia para mim?";
				link.l1.go = "JacobBerg";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "JacobTakeShip")
			{
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED)
				{
					dialog.text = "Eu te mandei atracar o navio. Você é burro ou ignorante demais pra seguir uma ordem direta?";
					link.l1 = "Nem um, nem outro, senhor. Estou a caminho.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Então, você já atracou seu navio. Agora vou lhe emprestar meu xebec. Está pronto para começar essa missão imediatamente? Meu navio está bem equipado e pronto para zarpar, então não há mais nada com que se preocupar.";
					link.l1 = "Sim, claro. Estou pronto, senhor Rodenburg.";
					link.l1.go = "JacobBerg_6";
					DelLandQuestMark(npchar);
				}
			break;
			}
			if (pchar.questTemp.HWIC.Holl == "JacobLongway")
			{
				dialog.text = "Por que você ainda está aqui? Vá falar com Longway agora mesmo.";
				link.l1 = "Desculpe, estou a caminho.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "MirageTake")//а вот теперь начинается дурдом с перебором кораблей
			{
				int iMir = 0;
				int iMef = 0;
				for(i = 0; i < COMPANION_MAX; i++)
				{
				iTemp = GetCompanionIndex(PChar, i);
				if(iTemp > 0)
				{
					sld = GetCharacter(iTemp);
					pchar.questTemp.HWIC.Holl.CompanionIndex = sld.Index;
					if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MIRAGE) iMir = 1;
					if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG) iMef = 1;
				}
				}//установили признак наличия кораблей в эскадре.
				RemoveItems(PChar, "JacobJournal", 1);//удалим журнал ван Берга
				pchar.quest.MirageConvoyOver.over = "yes"; //снять таймер
				if (iMir == 1 && iMef == 0)//потеряли Мейфенг
				{
					dialog.text = "Kapitein... Já estou ciente da sua viagem.";
					link.l1 = "Ah, é mesmo? Então você deve saber que...";
					link.l1.go = "Jacob_lostMef";
					DelLandQuestMark(npchar);
					break;
				}
				if (iMir == 0 && iMef == 1)//потеряли Мираж
				{
					dialog.text = "Kapitein... Já estou ciente da sua viagem.";
					link.l1 = "É mesmo? Então você deve saber que...";
					link.l1.go = "Jacob_lostMir";
					DelLandQuestMark(npchar);
					break;
				}
				if (iMir == 0 && iMef == 0)//а это вообще плохо
				{
					dialog.text = "Kapitein... Já estou ciente da sua viagem.";
					link.l1 = "É mesmo? Então você deve saber que...";
					link.l1.go = "Jacob_failFull";
					DelLandQuestMark(npchar);
					break;
				}
					dialog.text = "Aqui está, Kapitein... Já sei tudo sobre a sua jornada.";
					link.l1 = "É mesmo? Então você deve saber que...";
			link.l1.go = "Jacob_complete";
			DelLandQuestMark(npchar);
			break;
			}
			if (pchar.questTemp.HWIC.Holl == "toAntigua")
			{
				dialog.text = "Vá para Antígua. Agora.";
				link.l1 = "Desculpe, estou a caminho.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "FleetwoodSink" || pchar.questTemp.HWIC.Holl == "FleetwoodCapture")
			{//опять начинаем проверять корабли
				iMir = 0;
				for(i = 0; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if(iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						pchar.questTemp.HWIC.Holl.CompanionIndex = sld.Index;
						if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MIRAGE) iMir = 1;
					}
				}//установили признак наличия Миража в эскадре.
				pchar.quest.ToAntiguaOver.over = "yes"; //снять таймер
				if (iMir == 0)//потеряли Мираж
				{
					dialog.text = "Fui informado da sua chegada, kapitein. Também sei que você perdeu meu Mirage em batalha.";
					link.l1 = "Você está bem informado, senhor Rodenburg. Apesar de todos os meus esforços, não conseguimos salvá-la.";
					link.l1.go = "Fleetwood_fail";
					DelLandQuestMark(npchar);
				}
				else
				{
					dialog.text = "Fui informado da sua chegada, kapitein. Vejo que o Mirage está atracado em segurança. Isso é bom.";
					link.l1 = "Foi tudo conforme suas ordens, senhor. O senhor mandou eu matar o Fleetwood e ele está morto. Mandou eu trazer o Mirage de volta para o porto local e ele está aqui.";
					link.l1.go = "Fleetwood_complete";
					DelLandQuestMark(npchar);
				}
				pchar.quest.Meifeng_fail.over = "yes";
				Group_DeleteGroup("Meifeng_Empty");
				sld = characterFromId("MeifengCap");
				sld.lifeday = 0;//зачистим Мейфенг без китайца
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "Abby_prepare")
			{
				dialog.text = "Ah, aí está você. Que bom te ver. Tenho outra missão para você, como prometido.";
				link.l1 = "Estou ouvindo, senhor.";
				link.l1.go = "Abby";
				DelLandQuestMark(npchar);
				break;
			}
			if (!CheckAttribute(pchar, "questTemp.HWIC.Holl.LucasMoney") && pchar.questTemp.HWIC.Holl == "AbbyAgreeMarried")
			{
				dialog.text = "Ah, que bom te ver, meu rapaz. Você demorou a chegar e eu já estava começando a me preocupar. Conseguiu alguma coisa com a Abigail?";
				link.l1 = "Não só isso, resolvi também seus outros problemas. Encontrei a ilha e o tesouro perdido do senhor Shneur. Salomão está feliz e Abigail vai aceitar seu pedido. Parabéns, mynheer!";
				link.l1.go = "Abby_2";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "NotFindAbbyIsland")
			{
				dialog.text = "Ah, que bom ver você, meu amigo. Conseguiu descobrir algo com a Abigail?";
				link.l1 = "Sim. Conversei com Abigail e com o pai dela. Há um problema, senhor: a fortuna perdida do pai dela. Abigail se sente indigna de você, teme os comentários e cochichos das pessoas se, sem dote algum, ela se casasse com um cavalheiro como você. Espero que compreenda.";
				link.l1.go = "Abby_6";
				DelLandQuestMark(npchar);
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LucasMoney") && pchar.questTemp.HWIC.Holl == "AbbyAgreeMarried")
			{
				dialog.text = "Ah, meu amigo! Espero que tenha trazido boas notícias?";
				link.l1 = "Seu plano deu certo. Abigail vai aceitar. Parabéns, senhor.";
				link.l1.go = "Abby_8";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "MerdokStart")
			{
				dialog.text = "Estava esperando por você. Meu rapaz, você está em grande perigo.";
				link.l1 = "O que você quer dizer?";
				link.l1.go = "Merdok";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "MerdokDie")
			{
				dialog.text = "Meus agentes no cais me disseram que você chegou. Johan van Merden está morto?";
				link.l1 = "Sim. Ele e o comparsa dele se foram. Foi uma luta difícil, mas eu consegui.";
				link.l1.go = "Merdok_4";
				DelLandQuestMark(npchar);
				break;
			}
			dialog.text = "Não temos mais nada para discutir, kapitein.";
			link.l1 = "Entendi, estou indo embora.";
			link.l1.go = "exit";
			break;
		}
		dialog.text = "O que foi? Tempo é dinheiro.";
		link.l1 = "Desculpe, estou indo embora.";
		link.l1.go = "exit";
		break;
		
//------------------------------------------------1 задание--------------------------------------------
		case "Holl_start":
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Bridgetown_tavernkeeper"));
			DelLandQuestMark(characterFromId("Knippel"));
			DelMapQuestMarkCity("Bridgetown");
			DelMapQuestMarkCity("Villemstad");
			DelMapQuestMarkCity("SentJons");
			dialog.text = "Talvez. Quem é você? Fale rápido, tempo é dinheiro.";
			link.l1 = "Eu sou o capitão "+pchar.name+", meu navio e  podem ser úteis para você.";
			link.l1.go = "Holl_start_0";			
		break;
		
		case "Holl_start_0":
			dialog.text = "Hum, uma liga desconhecida a ser testada no cadinho.";
			link.l1 = "É por isso que estou aqui, senhor.";
			link.l1.go = "Holl_start_1";			
		break;
		
		case "Holl_start_1":
			pchar.questTemp.HWIC.Holl.PirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "Muito bem, vamos ver do que você é feito. Certo, Kapitein seja-lá-qual-for-seu-nome, conhece Balthazar Ridderbrock? Não? Que sorte a sua. Gananciosos, rabugentos e esquentados como ele são raros de se ver.\nMas parece que essas qualidades notáveis não eram suficientes para ele, então foi esperto o bastante para ofender um filibusteiro chamado "+GetName(NAMETYPE_ORIG,pchar.questTemp.HWIC.Holl.PirateName,NAME_NOM)+" na taverna local e chamou a guarda no exato momento em que a parte ofendida pôs a mão na espada...";
			link.l1 = "...e enforcaram o pirata com a primeira corda que encontraram?";
			link.l1.go = "Holl_start_2";			
		break;
		
		case "Holl_start_2":
			dialog.text = "Não é tão simples assim. "+GetName(NAMETYPE_ORIG,pchar.questTemp.HWIC.Holl.PirateName,NAME_NOM)+" não é um pirata comum, mas sim um corsário holandês, veterano das duas últimas guerras contra os ingleses. Os moradores daqui gostam bastante dele. Já não posso dizer o mesmo sobre Ridderbrock.";
			link.l1 = "Então nosso corsário ainda está vivo?";
			link.l1.go = "Holl_start_3";			
		break;
		
		case "Holl_start_3":
			dialog.text = "Sim, mas ele está realmente furioso. Por isso o Ridderbrock está morrendo de medo.";
			link.l1 = "Acho que minha sorte está prestes a acabar. Quando vou conhecer o senhor Ridderbrock?";
			link.l1.go = "Holl_start_4";			
		break;
		
		case "Holl_start_4":
			dialog.text = "Imediatamente. O bom povo de Philipsburg está aguardando uma remessa de açúcar, aquela que nosso conhecido em comum, Ridderbrock, prometeu entregar. Não considero esse homem digno nem do couro das próprias botas, mas, enfim, ele trabalha para nós, então vá até o escritório do porto. Encontre Ridderbrock lá e diga que eu ordenei que ele zarpe imediatamente.\nVocê vai segui-lo e... escoltá-lo até Philipsburg em segurança. Não quero "+GetName(NAMETYPE_ORIG,pchar.questTemp.HWIC.Holl.PirateName,NAME_NOM)+"  afundar a reputação da Companhia no fundo do Caribe junto com a carga dele.";
			link.l1 = "Ugh, uma missão de escolta. E quanto ao pagamento por esse... serviço desagradável?";
			link.l1.go = "Holl_start_5";			
		break;
		
		case "Holl_start_5":
			dialog.text = "Kapitein, faça o trabalho primeiro. Balthazar vai te pagar assim que chegar ao destino dele. Em Philipsburg! Não no fundo do mar! Depois, volte para me informar quando terminar. Se for bem-sucedido, poderá contar com meu apoio e o da Companhia. Dispensado.";
			link.l1 = "Até logo, mynheer.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Create_Baltazar");
			pchar.questTemp.HWIC.Holl = "BaltazarEsc";
			NextDiag.TempNode = "Second_time";
			pchar.quest.HWIC_ReturnOfficer.over = "yes";//чтобы офицер не доставал
			pchar.questTemp.HWIC.CanTake.Holl = "true";//признак, что голландка уже бралась
		break;
		
//----------------------------------------------задание 1а--------------------------------------------	
		case "SantiagoTrip":
			dialog.text = "Sim, Ridderbrock é um pão-duro filho da mãe, até para um holandês. Mas enfim, ele não é mais problema meu. Vamos falar de você, Kapitein Seja-Lá-Qual-For-Seu-Nome. Gosto do seu jeito, então vou te oferecer outro trabalho. Desta vez, eu mesmo vou pagar.";
			link.l1 = "Estou ouvindo, senhor.";
			link.l1.go = "SantiagoTrip_1";			
			AddSimpleRumourCity("Ah, so you are the brave kapitein who escorted that scoundrel Ridderbrock? We heard all about about it... He paid you only five thousand pesos! He's been boasting about it nonstop at the tavern in Philipsburg drunk as a swine. If I were you captain, I drag him out into the street and thrash him.", "Villemstad", 20, 3, "");//слух по 1 заданию
		break;
		
		case "SantiagoTrip_1":
			dialog.text = "Preciso de um homem para um assunto muito importante. Você lidou bem com o caso Ridderbrock, então a Companhia acredita que posso confiar isso a você.";
			link.l1 = "Suponho que devo me sentir honrado. O que foi?";
			link.l1.go = "SantiagoTrip_2";
		break;
		
		case "SantiagoTrip_2":
			sld = characterFromId("Santiago_usurer");
			dialog.text = "Não posso te dar detalhes exatos, mas saiba que isso não é um serviço meu, é da Companhia, então você tem a chance de cair nas nossas graças, o que, garanto, é muito lucrativo.\nNavegue até Santiago, em Cuba, e entregue este pacote ao Don "+GetFullName(sld)+". Ele ocupa um cargo importante no banco do Geraldi e também é meu... nosso sócio de negócios. Você deve entregar este ouro a ele, que vou lhe dar agora mesmo. Confio na sua honestidade, kapitein. Bem, se não for na sua honestidade, então no seu instinto de sobrevivência. A Companhia sempre encontra quem tenta nos roubar.";
			link.l1 = "Você duvida de mim, senhor?";
			link.l1.go = "SantiagoTrip_3";
		break;
		
		case "SantiagoTrip_3":
			if (pchar.BaseNation == ENGLAND || pchar.BaseNation == FRANCE) sTemp = " I am also giving you this short-term Company trade license in order to spare you from any diplomatic entanglements with the Spanish. This will allow you to dock at Spanish colonies for some time.";
			else sTemp = "";
			dialog.text = "No momento, não duvido de você. Acredite, eu nem estaria falando com você sobre isso se fosse diferente. Saiba que gastamos muito tempo preparando esse trabalho, então você tem apenas quinze dias para entregar."+sTemp+"\nMinha mensagem e o pacote precisam ser entregues no prazo. Isso é vital, garoto. Seja rápido, mas tome cuidado, esse trabalho não vai ser fácil.";
			link.l1 = "Mais alguma coisa? Por que está me alertando, senhor Rodenburg?";
			link.l1.go = "SantiagoTrip_4";
		break;
		
		case "SantiagoTrip_4":
			if (pchar.BaseNation == ENGLAND || pchar.BaseNation == FRANCE) GiveNationLicence(HOLLAND, 20);
			dialog.text = "Digamos apenas que tenho minhas suspeitas. Não se preocupe, se você fizer isso tão rápido quanto fez o último trabalho, terá chance de se tornar um agente valioso para os assuntos delicados da Companhia.";
			link.l1 = "Tudo o que preciso fazer é entregar esta carta e o dinheiro ao banqueiro em Santiago em até quinze dias? Parece fácil demais à primeira vista.";
			link.l1.go = "SantiagoTrip_5";
		break;
		
		case "SantiagoTrip_5":
			dialog.text = "Calma aí, garoto... Acho que você ainda não entendeu a seriedade dessa situação. Se você fizer esse trabalho, vou ficar muito grato a você. Agora, se fracassar, vou ficar uma fera. Nesse caso, vou acabar com você. Estamos entendidos, kapitein "+GetFullName(pchar)+"?";
			link.l1 = "Entendi. Dou minha palavra. Vou fazer o possível para te manter de bom humor.";
			link.l1.go = "SantiagoTrip_6";
		break;
		
		case "SantiagoTrip_6":
			dialog.text = "Muito bem. Agora, pegue a carta, esses baús, e lembre-se dos termos e condições. E mais uma coisa: fique longe de confusão em Santiago.";
			link.l1 = "Muito bem.";
			link.l1.go = "SantiagoTrip_7";
		break;
		
		case "SantiagoTrip_7":
			DialogExit();
			GiveItem2Character(pchar, "NPC_Letter");
			ChangeItemDescribe("NPC_Letter", "itmdescr_NPC_Letter4");
			TakeNItems(pchar, "chest", 5); 
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("SantiagoTripOver", 0, 0, 32, false);
			}
			else SetFunctionTimerCondition("SantiagoTripOver", 0, 0, 16, false); //таймер
			AddQuestRecord("Holl_Gambit", "1-43");
			pchar.questTemp.HWIC.Holl = "SantiagoTripBegin";
			AddMapQuestMarkCity("Santiago", true);
			AddLandQuestMark(characterFromId("Santiago_usurer"), "questmarkmain");
		break;
		
		case "SantiagoTrip_8":
			dialog.text = "'Tem que morrer'... assim, do nada. Não esperava por isso. Hm. Você fez bem o seu trabalho, kapitein. Agora me faça um relatório.";
			link.l1 = "Nada demais... foi uma tarefa fácil.";
			link.l1.go = "SantiagoTrip_9";
			link.l2 = "Fui surpreendido e sequestrado por um homem em Santiago. Ele estava muito interessado nos seus negócios com o Geraldi. Consegui escapar, mas precisei matá-lo antes. A única pista que ele deixou foi o nome de um tal Gaston. Não faço ideia do que se tratava.";
			link.l2.go = "SantiagoTrip_10";
			link.l3 = "Fui surpreendido e sequestrado por um homem em Santiago. Ele estava muito interessado nos seus negócios com o Geraldi. Consegui escapar, mas tive que matá-lo antes. Não consegui arrancar nada dele antes de mandá-lo para o inferno.";
			link.l3.go = "SantiagoTrip_11";
		break;
		
		case "SantiagoTrip_9":
			dialog.text = "A gratidão da Companhia não se resume a palavras. Pegue sua recompensa, você a merece.";
			link.l1 = "Trabalhar para a Companhia é bastante lucrativo.";
			link.l1.go = "SantiagoTrip_12";
		break;
		
		case "SantiagoTrip_10":
			dialog.text = "O quê! Sequestro... Espere, porém... Gaston! Entendi... Suponho que sim. Ai, meu rapaz, você acabou envolvido numa situação bem sórdida. Estamos em território desconhecido, então vamos ver como isso se desenrola. Fico feliz que tenha saído vivo.\nVamos falar de coisas mais agradáveis – aceite esta recompensa, você merece.";
			link.l1 = "Trabalhar para a Companhia é bem lucrativo";
			link.l1.go = "SantiagoTrip_12";
		break;
		
		case "SantiagoTrip_11":
			dialog.text = "Que bobagem! Sequestrar você... Mas confesso que tenho algumas suspeitas. Se continuar trabalhando para mim, vai descobrir mais. Você tem sorte, e fico feliz que tenha conseguido.\nVamos falar de coisas mais agradáveis – aceite esta recompensa, você merece.";
			link.l1 = "Trabalhar para a Companhia é bastante lucrativo";
			link.l1.go = "SantiagoTrip_12";
		break;
		
		case "SantiagoTrip_12":
			AddMoneyToCharacter(pchar, 25000);
			dialog.text = "Exatamente, meu rapaz! Você pode se tornar um agente muito bem recompensado da Companhia se continuarmos trabalhando juntos. Agora vá, descanse um pouco da viagem. Você correspondeu às minhas expectativas. Ficarei realmente grato se voltar daqui a uma semana, ainda temos muito trabalho pela frente.";
			link.l1 = "Pode contar comigo, senhor Rodenburg.";
			link.l1.go = "SantiagoTrip_13";
		break;
		
		case "SantiagoTrip_13":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "true";
			AddQuestRecord("Holl_Gambit", "1-46");
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			AddCharacterExpToSkill(pchar, "Leadership", 80);
			AddSimpleRumourCity("My brother at the Company says that Mynheer Rodenburg is quite pleased by your performance, kapitein. Don't lose your chance, Lucas rarely shows such favor.", "Villemstad", 10, 3, "");
			SetTimerFunction("GollandGambit_2_ZadanieStart", 0, 0, 7);
		break;
		
//-----------------------------------------------2 задание--------------------------------------------
		case "JacobBerg":
			dialog.text = "Você é esperto, capitão. Exatamente. Bem, vamos discutir os detalhes da próxima missão...";
			link.l1 = "Estou ouvindo.";
			link.l1.go = "JacobBerg_1";			
		break;
		
		case "JacobBerg_1":
			dialog.text = "Tenho uma missão muito séria e importante para você, e espero que siga todas as minhas instruções à risca. Como sabe, a relação entre as Províncias Unidas e a Inglaterra está... longe de ser cordial. Os ingleses estão convencidos de que só eles deveriam governar o mundo. O problema é que nem todos concordam com essa ideia. Onde quer que eles naveguem para fazer negócios, pode apostar que a Companhia Holandesa das Índias Ocidentais já esteve lá antes. Nós, holandeses, temos a maior frota mercante do mundo, e nossos esquadrões militares podem defender os interesses da República tanto aqui quanto no exterior. Os ingleses nos invejam pelo nosso poder comercial e fazem de tudo para sabotar as atividades da Companhia. Agora, há um certo capitão da marinha inglesa chamado Richard Fleetwood. Apesar de ser um oficial comissionado da Commonwealth, ele está atuando como pirata. Ataca e saqueia qualquer navio que ouse navegar sob a bandeira holandesa no Caribe. Ele justifica suas ações como uma resposta ao 'navio fantasma' que afunda mercantes ingleses. Diz que esse 'navio fantasma' é um corsário navegando sob uma carta de corso holandesa. Já ouviu falar do 'navio fantasma', kapitein?";
			link.l1 = "Esse tipo de besteira você escuta em qualquer taverna. Basta pagar um rum para um velho contramestre e vai ouvir qualquer história que quiser...";
			link.l1.go = "JacobBerg_2";
		break;
		
		case "JacobBerg_2":
			dialog.text = "Isso não é delírio de bêbado. Investiguei as ações desse 'navio fantasma'. Descobri que é um navio de madeira e lona, tripulado por homens comuns, uma escuna chamada 'Mirage'. Ela está sob o comando de um homem chamado Jacob van Berg, que a faz passar pela lendária 'Holandês Voador'.";
			link.l1 = "Van Berg? Esse é um sobrenome holandês. Um verdadeiro 'Holandês Voador', hein?";
			link.l1.go = "JacobBerg_3";
		break;
		
		case "JacobBerg_3":
			dialog.text = "Certo. Jacob van Berg é holandês, natural de Leiden. Mas a República já o condenou à forca há muito tempo. Ele é um criminoso foragido, um pirata que age só por interesse próprio. Richard Fleetwood está caçando van Berg. Vamos usar esse fato contra aquele inglês insolente.\nEu preferia não matar Fleetwood de imediato, embora ele já merecesse isso faz tempo. A morte seria pouco para ele. Quero não só matá-lo, mas também destruir seu nome e sua honra. É isso que eu quero. E assim os outros ingleses arrogantes também aprendem a lição.\nVamos falar dos detalhes.";
			link.l1 = "Mynheer, isso está começando a parecer algo pessoal...";
			link.l1.go = "JacobBerg_4";
		break;
		
		case "JacobBerg_4":
			dialog.text = "Isso não é da sua conta. Siga as ordens e será pago. Descobri onde Jacob van Berg se esconde com seu 'Mirage', graças ao meu informante. Ele opera a partir de uma cidade no sul do continente espanhol. Vá até ele e descubra onde ele ancorou seu navio fantasma\nDepois, mate-o, encontre o 'Mirage', tome-o como prêmio e traga-o de volta para cá. Você precisa capturar o 'Mirage', nem pense em afundá-lo.";
			link.l1 = "Parece simples o bastante. Onde devo procurar o van Berg?";
			link.l1.go = "JacobBerg_5";
		break;
		
		case "JacobBerg_5":
			dialog.text = "Todos os detalhes serão passados a você pelo meu agente. O nome dele é Longway, um chinês. Estou lhe cedendo meu navio pessoal, o xebec 'Meifeng', para esta missão. Longway é o capitão dela, mas ele seguirá suas ordens.\nVá até o escritório do porto local e deixe todos os seus navios atracados lá. Volte para mim quando terminar.";
			link.l1 = "Certo, vou falar com o mestre do porto. Não vou te deixar esperando por muito tempo.";
			link.l1.go = "exit";
			pchar.questTemp.HWIC.Holl = "JacobTakeShip";
			AddLandQuestMark(characterFromId("Villemstad_portman"), "questmarkmain");
		break;
		
		case "JacobBerg_6":
			dialog.text = "Longway está te esperando lá fora. Ele vai te mostrar seu novo navio e te passar algumas informações sobre o paradeiro do van Berg. Boa sorte, kapitein, e não me decepcione. Lembre-se de que você deve trazer o 'Meifeng' de volta para mim, então tente não afundá-la enquanto toma o 'Mirage'.";
			link.l1 = "Já estou indo!";
			link.l1.go = "JacobBerg_7";	
		break;
		
		case "JacobBerg_7":
			DialogExit();
			pchar.quest.Create_Longway.win_condition.l1 = "location";
			pchar.quest.Create_Longway.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Create_Longway.function = "Create_Longway";
			pchar.questTemp.HWIC.Holl = "JacobLongway";
			AddQuestRecord("Holl_Gambit", "1-7");
			pchar.questTemp.HWIC.TakeQuestShip = "true";//все ПУ недоступны для стоянки до поры, также корабль нельзя продать
			pchar.questTemp.HWIC.HollEquip = "true";//форма солдат
			DeleteAttribute(pchar, "questTemp.HWIC.CanTake");//иные варианты более невозможны
		break;
		
		//дурдом продолжается
		case "Jacob_lostMir":
			dialog.text = "Seu incompetente. Você falhou na missão de capturar o navio pirata. Todos os meus planos foram arruinados. Estou tirando 'Meifeng' de você. Saia, não precisamos mais de você.";
			link.l1 = "Sinto muito. Adeus, senhor Rodenburg.";
			link.l1.go = "Jacob_RemoveShip";
			pchar.questTemp.HWIC.Holl.ShipType = SHIP_MAYFANG;
		break;
		
		case "Jacob_lostMef":
			dialog.text = "Seu completo idiota. Você perdeu o 'Meifeng'. Isso é inaceitável... Vou tomar o 'Mirage' de você e reter seu pagamento como compensação pela minha perda. Saia, não precisamos mais de você.";
			link.l1 = "Sinto muito. Adeus, senhor Rodenburg.";
			link.l1.go = "Jacob_RemoveShip";
			pchar.questTemp.HWIC.Holl.ShipType = SHIP_MIRAGE;
		break;
		
		case "Jacob_failFull":
			dialog.text = "Meu Deus, você é realmente uma peça rara. Um trapalhão incompetente E um idiota. Você não conseguiu capturar o Mirage e ainda perdeu o Meifeng junto. Cai fora do meu escritório!";
			link.l1 = "Estou indo embora.";
			link.l1.go = "exit";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex("Longway");
			AddDialogExitQuestFunction("LandEnc_OfficerFired");//Лонгвэя из офицеров
			pchar.questTemp.HWIC.Holl = "end";
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Detector = "holl_fail";
		break;
		
		case "Jacob_complete":
			dialog.text = "Well done. Word of your success has already reached my ears. Van Berg is dead and you have captured his ship. Your payment is 50,000 pesos, take it.\nI am retrieving the 'Meifeng' from you. Now it is time for you to take command of the 'Mirage'; she will play an important role in the next stage. Are you ready?";
			link.l1 = "Sim, senhor Rodenburg.";
			link.l1.go = "Fleetwood";
			pchar.questTemp.HWIC.Holl.ShipType = SHIP_MAYFANG;
			AddDialogExitQuestFunction("Jacob_RemoveShip");	
			AddSimpleRumourCity("They say that you are on special assignment for Mynheer Rodenburg himself. Something about sending those English to the bottom of the sea. It seems that you are a man on the rise, kapitein.", "Villemstad", 15, 3, "");
		break;
		
		case "Jacob_RemoveShip":
			DialogExit();
			AddDialogExitQuestFunction("Jacob_RemoveShip");	
			sld = characterFromId("Longway");
			sld.lifeday = 0;
			pchar.questTemp.HWIC.Holl = "end";
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Detector = "holl_fail";
			AddSimpleRumourCity("They say that you have failed Mynheer Rodenburg himself. Good luck, you'll need it.", "Villemstad", 20, 3, "");
		break;
		
//----------------------------------------------3 задание-------------------------------------------------
		
		case "Fleetwood":
			AddMoneyToCharacter(pchar, 50000);
			dialog.text = "Now we deal with Fleetwood. You are going to lure him out using the 'ghost ship' Mirage that he has been hunting so enthusiastically. Set a trap near Dominica; the Mirage will serve as bait.\nFirst, you will let Fleetwood know that the Mirage was seen not far from Dominica. Our brave Englishman will drop everything he's doing and rush straight to Dominica in search of his prey. Don't speak to Fleetwood directly or you won't survive the encounter. Find the drugstore in St. John's. The apothecary, John Murdock, is an old friend of mine.\nTell him that you are acting under my command and he will help you find some local ears to fill with juicy lies about the 'ghost ship' attacking English merchants near Dominica.";
			link.l1 = "Posso fazer isso. O objetivo é emboscar o Fleetwood em Dominica, certo?";
			link.l1.go = "Fleetwood_1";
		break;
		
		case "Fleetwood_1":
			dialog.text = "Exatamente. Longway e 'Meifeng' vão esperar por você perto de Dominica. Vocês dois podem dar conta desse inglês facilmente. Aborde o navio dele e revistem a cabine. Quero o diário de bordo dele. Pago um extra por isso.\nMas sua prioridade principal é matar aquele desgraçado do Fleetwood, então, se abordar não for possível, mande ele para o fundo do mar. Acima de tudo, você deve preservar a 'Mirage' a qualquer custo. Ela tem um papel crucial na próxima etapa do plano.";
			link.l1 = "Entendido.";
			link.l1.go = "Fleetwood_2";
		break;
		
		case "Fleetwood_2":
			dialog.text = "Um conselho, kapitein. Não ancore em St. John's. Desembarque em alguma das baías da ilha e vá até a cidade pela selva, senão John não vai falar com você. Se chamar muita atenção, ele vai fingir que não te conhece. E cuidado no mar – o 'Mirage' é famoso entre as colônias inglesas, então evite os navios de guerra e assentamentos deles se não quiser ser caçado por uma matilha de lobos do mar. É só isso. Que Deus te acompanhe.";
			link.l1 = "Afirmativo.";
			link.l1.go = "Fleetwood_3";
		break;
		
		case "Fleetwood_3":
			DialogExit();	
			pchar.questTemp.HWIC.Holl = "toAntigua";
			AddQuestRecord("Holl_Gambit", "1-15");
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			SetFunctionTimerCondition("ToAntiguaOver", 0, 0, 60, false); //таймер 2 месяца
			AddMapQuestMarkShore("Shore1", false);
			AddMapQuestMarkShore("Shore2", false);
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		case "Fleetwood_complete":
			if (pchar.questTemp.HWIC.Holl == "FleetwoodSink")//Флитвуд утоп с журналом
			{
				dialog.text = "Você voltou, kapitein... Você trouxe o diário de bordo do Richard Fleetwood?";
				link.l1 = "Infelizmente, não. Não tive a chance de subir a bordo do navio dele antes que ele o afundasse.";
				link.l1.go = "Fleetwood_complete_1";
				break;
			}
			if (!CheckCharacterItem(pchar, "FleetwoodJournal"))
			{
				dialog.text = "Você voltou, kapitein... Você trouxe o diário de bordo do Richard Fleetwood?";
				link.l1 = "Infelizmente, não consegui. Consegui embarcar na Valkyrie e matei o homem em combate corpo a corpo, mas não encontrei o diário dele. Um dos homens dele incendiou o paiol e tivemos apenas alguns segundos para escapar com vida.";
				link.l1.go = "Fleetwood_complete_1";
				break;
			}
			dialog.text = "Você voltou, kapitein... Você trouxe o diário de bordo do Richard Fleetwood?";
			link.l1 = "Consegui. Aqui está. Consegui abordar o Valkyrie, embora tenha sido por um triz. O desgraçado explodiu o paiol do próprio navio e mandou tudo pelos ares. Escapamos por pouco com vida.";
			link.l1.go = "Fleetwood_complete_2";
		break;
		
		case "Fleetwood_complete_1":
			AddMoneyToCharacter(pchar, 100000);
			dialog.text = "Que pena, isso teria respondido a muitas perguntas que temos. Mas agora não importa mais. Você matou aquele maldito inglês insolente, e isso é o que mais importa. Aqui está sua recompensa - 100.000 pesos. Vou ficar com o 'Mirage', vamos devolver esse navio para a Inglaterra.";
			link.l1 = "Mas que diabo?! Ela é um belo navio, eu queria ficar com ela!";
			link.l1.go = "Fleetwood_complete_3";
		break;
		
		case "Fleetwood_complete_2":
			AddMoneyToCharacter(pchar, 150000);
			RemoveItems(PChar, "FleetwoodJournal", 1);
			dialog.text = "Excellent! You are a very capable man. If all our captains were like you, the Dutch Republic would be first among the greatest maritime nations in history. Here is your reward - 100,000 pesos, and 50,000 pesos extra for the logbook. I am taking the 'Mirage' from you; we are going to return this ship to England.";
			link.l1 = "Que diabo?! Ela é um belo navio, eu queria ficar com ela!";
			link.l1.go = "Fleetwood_complete_3";
		break;
		
		case "Fleetwood_complete_3":
			dialog.text = "Meu rapaz, você é um excelente soldado, mas confie em mim e na minha experiência em assuntos de política. Lembra do que falei sobre Fleetwood? Vou afundar o nome e a reputação dele como uma pedra de moinho lançada ao fundo do mar. E esses nobres arrogantes de Port Royal vão ter que engolir e se engasgar.\nVamos transformar Richard Fleetwood no capitão do 'navio fantasma' Mirage, um lobisomem jogando Inglaterra e Holanda uma contra a outra, saqueando, pilhando e assassinando cidadãos pacíficos de ambos os lados só para enriquecer! Que farsa! Já preparei provas e testemunhas, mas o 'Mirage' será o grande ato do meu espetáculo perfeito.";
			link.l1 = "Então, que se dane. Você vai sacrificar meu navio excelente pelo seu plano!?";
			link.l1.go = "Fleetwood_complete_4";
			AddDialogExitQuestFunction("Lucas_ExangeShip");
		break;
		
		case "Fleetwood_complete_4":
			dialog.text = "Controle sua língua, rapaz, isto é guerra. Às vezes precisamos sacrificar não só homens, mas também navios e cidades ricas para alcançar nossos objetivos políticos. Toda guerra traz perdas... Falando em perdas, tenho más notícias para você.\nEnquanto você esteve fora, Willemstad foi atacada por corsários ingleses. O forte conseguiu expulsá-los, mas não antes de eles entrarem no porto com navios incendiários.\nSeu navio estava ancorado e foi queimado até a linha d'água. Foi uma perda total.";
			link.l1 = "Mynheer, você só pode estar de sacanagem comigo agora. Maldição! O que diabos eu faço agora?!";
			link.l1.go = "Fleetwood_complete_5";			
		break;
		
		case "Fleetwood_complete_5":
			dialog.text = "Don't be so upset, kapitein, I also have good news. To salve your indignation, I am giving you my Beautiful Wind, the xebec 'Meifeng'. You are free to use the ship in any way you wish, within reason. Additionally, meet me tomorrow at the governor's residence; you have been nominated for a state award with the gratitude of the Dutch Republic and the West India Company. Don't leave town until you receive it, kapitein.";
			link.l1 = "Isso realmente ameniza um pouco minhas perdas. Fico honrado. A propósito, senhor, para onde foi o Longway?";
			link.l1.go = "Fleetwood_complete_6";
		break;
		
		case "Fleetwood_complete_6":
			dialog.text = "Longway desapareceu de repente logo depois que eu mandei ele navegar para Dominica. Suspeito que agentes ingleses possam ter ido atrás dele... ou talvez não. Estou investigando.";
			link.l1 = "Entendo. A ajuda dele em Dominica teria sido muito bem-vinda. Fleetwood e sua 'Valkyrie' formavam uma dupla assustadora. Espero que Longway ainda esteja vivo... Tot ziens, mynheer!";
			link.l1.go = "Fleetwood_complete_7";
			pchar.questTemp.HWIC.Holl = "Award";
			AddQuestRecord("Holl_Gambit", "1-24");
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", true);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", true);
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", true);
		break;
		
		case "Fleetwood_complete_7":
			DialogExit();
			AddDialogExitQuestFunction("GollandGambit_AwardFromLucas_1");
			AddSimpleRumour("Tell me captain, was that damned English dog Fleetwood was really responsible for plundering English 'and' Dutch merchants? Really? Such an artful dodger! It is good that you have eliminated this bastard. You are a real hero, captain!", HOLLAND, 10, 3);
		break;
		
		case "Fleetwood_fail":
			dialog.text = "Você não é só um palhaço comum, você é o circo inteiro. Estávamos tão perto do ato final e você estragou tudo... Vou te pagar 30.000 pesos pela eliminação do Fleetwood. Não tenho mais missões para você e nosso acordo está encerrado. Agora suma daqui.";
			link.l1 = "Como quiser.";
			link.l1.go = "Fleetwood_fail_1";			
		break;
		
		case "Fleetwood_fail_1":
			AddMoneyToCharacter(pchar, 30000);
			dialog.text = "Tenho más notícias para você.\nEnquanto você estava fora, Willemstad foi atacada por corsários ingleses. O forte conseguiu expulsá-los, mas não antes de eles entrarem no porto com navios incendiários.\nSeu navio estava ancorado e foi queimado até a linha d'água. Foi uma perda total.";
			link.l1 = "Então acho que vou me ferrar sozinho mesmo! Valeu por nada!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//можно пользоваться ПУ
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			CloseQuestHeader("Holl_Gambit");
			pchar.questTemp.HWIC.Holl = "end";
			pchar.questTemp.HWIC.Detector = "holl_fail";
			AddSimpleRumour("Tell me, captain, is it true that you have sunk this damned English dog Fleetwood? Really? It is good that you have eliminated this bastard. You did well, captain!", HOLLAND, 15, 3);
		break;
		
		case "LucasAward":
			dialog.text = "Kapitein "+GetFullName(pchar)+"! Por eliminar Richard Fleetwood, um perigoso criminoso do Estado, por desmascarar a traiçoeira conspiração inglesa contra a República, por bravura e coragem, você recebe mil dobrões de ouro em nome da República Holandesa!\nVocê também receberá este valioso instrumento de navegação – o sonho de qualquer oficial naval.";
			link.l1 = "Estou feliz em servir à República!";
			link.l1.go = "LucasAward_1";			
		break;
		
		case "LucasAward_1":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			LAi_SetActorType(sld);
			sld.Dialog.Filename = "Quest\HollandGambit\OtherNPC.c";
			sld.dialog.currentnode = "Bek_7";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			GiveItem2Character(pchar, "bussol");
		break;
		
		case "LucasAward_2":
			dialog.text = "Parabéns mais uma vez, meu amigo. E, por favor, venha me visitar daqui a uma semana. Precisamos de você para tratar de um assunto extremamente delicado.";
			link.l1 = "Entendido, senhor Rodenburg. Voltarei em uma semana.";
			link.l1.go = "LucasAward_3";			
		break;
		
		case "LucasAward_3"://наведем порядок
			LAi_SetActorType(pchar);
			DialogExit();
			AddQuestRecord("Holl_Gambit", "1-25");
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			LAi_ActorGoToLocator(sld, "goto", "goto6", "BekSitDown", -1);
			for (i=1; i<=3; i++)
			{
				sld = characterFromId("LucasGuard_"+i);
				sld.lifeday = 0;//подчистим солдат
			}
			sld = characterFromId("Lucas");
			LAi_ActorGoToLocator(sld, "reload", "reload1", "LucasReturnInCabinet", -1);
			bDisableFastReload = true;
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", false);
			SetTimerFunction("GollandGambit_4_ZadanieStart", 0, 0, 7);
			AddSimpleRumourCity("They say that you were given a state award by Matias Beck himself! The Republic should be proud to have people like you, kapetein!", "Villemstad", 20, 4, "");
		break;
		
//--------------------------------------------------4 задание----------------------------------------------
		
		case "Abby":
			dialog.text = "Vou lhe contar uma história. Isso vai ajudar você a entender como sua próxima tarefa é delicada. Alguns meses atrás, um fluyt navegando sob bandeira inglesa a caminho de Willemstad foi atacado pelo falecido Jacob van Berg. Ele tomou o navio e o afundou não muito longe de uma ilha que não consta em nenhum dos nossos mapas. Apenas dois passageiros do fluyt sobreviveram. Um judeu chamado Solomon Shneur e sua filha Abigail. Todos os outros passageiros morreram, incluindo o restante da família deles. Nossos dois judeus chegaram à ilha flutuando em destroços\nSolomon ainda conseguiu arrastar consigo um baú cheio do ouro da família. Muito previdente da parte dele. Outro personagem da nossa história, Richard Fleetwood, navegava por perto e ouviu sons de luta. Ele chegou tarde demais para pegar van Berg, e o 'Mirage' fugiu. Fleetwood decidiu então verificar a ilha em busca de sobreviventes\nEle salvou Solomon e Abigail de uma morte certa naquela ilha deserta. Infelizmente para o velho judeu, Solomon não tem olhar de marinheiro. Ele confundiu o 'Valkerie' de Richard com o 'Mirage' de Jacob e — apavorado, achando que o pirata voltava para terminar o serviço — escondeu seu ouro em algum lugar da ilha. Por isso, ele e a filha chegaram aqui sem um tostão, deixados por Fleetwood na Lagoa Blanca, perto de Willemstad, o destino original deles.\nSolomon me contou essa história. A República Holandesa apoia a livre prática religiosa. Como parte dessa política, a Companhia apoia a comunidade judaica daqui. Por isso, garanti que eles tivessem um teto, comida e roupas. Visitei a casa deles muitas vezes. Abigail é uma... jovem notável. Sincera e confiável\nNão vou mentir para você, capitão, eu a quero e pretendo fazê-la minha esposa. Ela também me ama, mas algo se colocou entre nós.";
			link.l1 = "O pai dela não ficou muito animado com um genro goi?";
			link.l1.go = "Abby_0";			
		break;
		
		case "Abby_0":
			dialog.text = "Ha! Old Solomon would be in seventh heaven if I married Abigail, uncircumcised son-in-law or not. As a matter of fact, he urges her to accept my proposal. No, no, this is something that goes beyond Jew and Gentile. I ask you, my boy, to solve this problem for me. Talk to Abigail and find out what is wrong\nYou are a stranger; she might tell you things she would never reveal to familiar people because of her charming modesty. Shneur's house is located to the right of the company's office, if you stand with your back to it. I know that you are a smooth talker\nBut remember one thing: Richard Fleetwood was the true captain of the 'ghost ship'... Keep it in mind while talking to Abigail.";
			link.l1 = "Ha! Claro que me lembro disso, senhor Rodenburg. Afinal, não é um fato oficialmente reconhecido? Não vou perder tempo então, vou visitar sua amada imediatamente.";
			link.l1.go = "Abby_1";			
		break;
		
		case "Abby_1":
			LocatorReloadEnterDisable("Villemstad_town", "houseSP2", false);//откроем дом Аби
			DialogExit();
			pchar.questTemp.HWIC.Holl = "AbbyInHouse";
			AddQuestRecord("Holl_Gambit", "1-26");
			AddLandQuestMark(characterFromId("Abigile"), "questmarkmain");
		break;
		
		case "Abby_2":
			dialog.text = "Você realmente encontrou a ilha onde Salomão escondeu seu ouro? Isso é incrível! Eu já estava começando a achar que você consegue dar conta de qualquer coisa... Achou mais alguma coisa no esconderijo?";
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.ScullnotReturn"))
			{
				link.l1 = "Não, nada mais. Só dinheiro.";
				link.l1.go = "Abby_3";
			}
			else
			{
				link.l1 = "Havia um item interessante – um crânio de jade. Eu o entreguei ao Solomon, e ele disse que era uma herança de família. Ele também comentou que você estava planejando comprá-lo dele...";
				link.l1.go = "Abby_4";
			}
		break;
		
		case "Abby_3":
			pchar.questTemp.HWIC.Holl.LucasItem = "obereg_11";
			dialog.text = "Hm. Tudo bem então. Mas é realmente estranho. Enfim... Eu lhe devo uma, senhor, e nunca vou esquecer isso. Preparei uma recompensa para você – 50.000 pesos e este amuleto. Agora são seus.";
			link.l1 = "Obrigado, senhor Rodenburg!";
			link.l1.go = "Abby_5";
		break;
		
		case "Abby_4":
			pchar.questTemp.HWIC.Holl.LucasItem = "totem_04";
			dialog.text = "Excelente! Sim, vou comprar esse artefato do Solomon, ele não precisa disso e tenho um comprador muito generoso esperando por ele. Preparei uma recompensa para você – 50.000 pesos e este amuleto. Agora são seus.";
			link.l1 = "Obrigado, senhor Rodenburg!";
			link.l1.go = "Abby_5";
		break;
		
		case "Abby_5":
			dialog.text = "Não tenho nenhum trabalho à altura de um kapitein como você no momento. Mas não fique longe de Curaçao por muito tempo, logo vou precisar dos seus serviços de novo.";
			link.l1 = "Entendi, senhor. Adeus!";
			link.l1.go = "exit";
			GiveItem2Character(pchar, pchar.questTemp.HWIC.Holl.LucasItem);
			AddMoneyToCharacter(pchar, 50000);
			pchar.questTemp.HWIC.Holl = "Merdok_wait";
			AddQuestRecord("Holl_Gambit", "1-34");
			DelMapQuestMarkCity("Villemstad");
			SetTimerFunction("GollandGambit_5_ZadanieStart", 0, 0, 10);
			AddSimpleRumourCity("Have you heard the latest news? Mynheer Rodenburg is going to marry Abigail Shneur, the beautiful daughter of the old crazy Jew Solomon. What can I say, she is a lucky girl. God willing, she'll be baptized a true Christian before the wedding!", "Villemstad", 20, 3, "");
		break;
		
		case "Abby_6":
			dialog.text = "Ha, e é só isso? Francamente absurdo... típico de uma mulher. Ouça, meu rapaz, esse problema pode ser resolvido facilmente. Eu sei quanto dinheiro havia no esconderijo do Salomão: 200.000 pesos. Estou disposto a dar essa quantia pela minha felicidade e da Abigail. Eu te dou o dinheiro e você sai de Curaçao por uma ou duas semanas. Depois, você volta para o Salomão e entrega o dinheiro a ele. Finja que encontrou o esconderijo. O lobo fica satisfeito e a ovelha sai ilesa. Aqui, pegue a quantia necessária";
			link.l1 = "Um bom plano, simples. Vamos nessa.";
			link.l1.go = "Abby_7";
		break;
		
		case "Abby_7":
			dialog.text = "Saia para o mar aberto e volte para mim em dez dias. Vá fazer algo útil. Procure pela Manga Rosa, produza alguns materiais, ou qualquer outra coisa.";
			link.l1 = "O que o senhor mandar, Mynheer Rodenburg.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 200000);
			pchar.questTemp.HWIC.Holl = "GiveLucasMoney";
			SaveCurrentQuestDateParam("questTemp.HWIC.Holl.LucasMoney");
			pchar.questTemp.HWIC.Holl.LucasMoney = "true";
			AddQuestRecord("Holl_Gambit", "1-35");
		break;
		
		case "Abby_8":
			pchar.questTemp.HWIC.Holl.LucasItem = "obereg_11";
			dialog.text = "Excelente! Mais uma vez, você fez o trabalho perfeitamente. Estou em dívida com você, mynheer, e nunca vou esquecer isso. Preparei uma recompensa para você – 50.000 pesos e este amuleto. Agora são seus.";
			link.l1 = "Obrigado, senhor Rodenburg!";
			link.l1.go = "Abby_5";
		break;
		
//-------------------------------------------5 задание-------------------------------------------------
		case "Merdok":
			dialog.text = "Sim, exatamente isso. Meu amigo, às vezes é difícil saber quem é seu amigo e quem é seu inimigo. Às vezes você nem percebe quando seu parceiro mais próximo se torna seu inimigo. Nosso conhecido em comum de St John's, John Murdock – também chamado de Johan van Merden – é um ex-agente da Companhia que se vendeu para a Marinha Inglesa.\nA última missão dele é eliminar um dos maiores talentos da Companhia... você.";
			link.l1 = "Fico lisonjeado. Ainda bem que você me contou, senão eu nunca teria imaginado isso.";
			link.l1.go = "Merdok_1";
		break;
		
		case "Merdok_1":
			dialog.text = "Exatamente, kapitein. Ele é um sujeito astuto. Encontre esse desgraçado e mate-o antes que ele ataque. Navegue até Antígua e procure uma entrada secreta para a farmácia dele. Há uma escotilha em frente à igreja que leva a um túnel secreto. Use-a.";
			link.l1 = "Eu cuido disso.";
			link.l1.go = "Merdok_2";
		break;
		
		case "Merdok_2":
			dialog.text = "Mais uma coisa, kapitein. Quando Johan estiver morto, revire o corpo dele, a casa e o porão. Ele tem um arquivo—um livro-caixa grosso onde escreveu algumas anotações comprometedoras enquanto trabalhava para a Companhia. Se nossos inimigos encontrarem essas informações, todos nós estaremos perdidos.\nEncontre esse maldito arquivo e traga para mim, que eu pago um extra por isso. Agora vá. Boa sorte, Kapitein "+pchar.name+", e tente voltar inteiro. A República precisa de você!";
			link.l1 = "Eu lhe prometo, senhor, que voltarei inteiro. Isso certamente é do meu maior interesse!";
			link.l1.go = "Merdok_3";
		break;
		
		case "Merdok_3":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "KillMerdok";
			AddQuestRecord("Holl_Gambit", "1-42");
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", false);
			bDisableFastReload = false;
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload2", false);//откроем проход в подземелье из дома
			LocatorReloadEnterDisable("SentJons_TownCave", "reload1_back", false);//откроем проход в дом из подземелья
			LocatorReloadEnterDisable("SentJons_town", "HouseF3", true);//аптеку закроем
			pchar.quest.Merdok_inCave.win_condition.l1 = "location";
			pchar.quest.Merdok_inCave.win_condition.l1.location = "SentJons_TownCave";
			pchar.quest.Merdok_inCave.function = "MerdokInUndergroundCave";
			LAi_LocationDisableOfficersGen("SentJons_TownCave", true);//офицеров в шахту не пускать
			DelMapQuestMarkCity("Villemstad");
			AddMapQuestMarkCity("SentJons", false);
		break;
		
		case "Merdok_4":
			dialog.text = "Excelente, capitão! Fico feliz, de verdade. Você encontrou o arquivo dele?";
			if (CheckCharacterItem(pchar, "MerdokArchive"))//архив
			{
				link.l1 = "Sim, aqui está. Não havia outros documentos no corpo do químico ou nos baús dele.";
				link.l1.go = "Merdok_book";
			}
			link.l2 = "Não. Procurei em todo lugar, mas não encontrei nada.";
			link.l2.go = "Merdok_5";
			DeleteAttribute("SentJons_TownCave", "box2");//если не нашли шифр - уже и не найдем
		break;
		
		case "Merdok_5":
			dialog.text = "É realmente uma pena, mas tudo bem. Tenho certeza de que Johan não teve tempo de entregar isso aos ingleses, senão já estaríamos com a corda no pescoço... É provável que ele tenha escondido em algum esconderijo secreto... que fique lá para sempre! Parabéns, kapitein, pelo sucesso da nossa missão!";
			link.l1 = "Gratidão!";
			link.l1.go = "Merdok_6";
			
			SetTimerCondition("PZ_LigaInJungle", 0, 0, 7, false);	// проверку не прошёл, значит нападёт Лига через неделю, после чего начнётся таймер на 30 дней 1 этапа
		break;
		
		case "Merdok_book":
			dialog.text = "Excelente! Agora está seguro onde deveria estar. Você provou mais uma vez que é o melhor... Me dê o livro... Há uma recompensa pelo arquivo – este belo mosquete. Ele me serviu com grande distinção, e agora é seu!";
			link.l1 = "";
			if (CheckAttribute(pchar, "questTemp.PZ_RodenburgUkradenaStranitsa"))
			{
				link.l1.go = "Merdok_book_2";
			}
			else
			{
				link.l1.go = "Merdok_book_6";
			}
			RemoveItems(PChar, "MerdokArchive", 1);
		break;
		
		case "Merdok_book_2":
			dialog.text = "Qual é o seu jogo, capitão? Faltam várias páginas — páginas que são muito importantes para mim. Achou que eu não perceberia, para usá-las contra mim? Ou estava esperando tirar algum proveito disso? Receio ter que te decepcionar nos dois casos.";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				Notification_Perk(true, "Trustworthy");
				link.l1 = "(Confiável) Me desculpe. Meu único erro foi não ter conferido o arquivo eu mesmo antes.";
				link.l1.go = "VD_Merdok_book_3";
				SetTimerCondition("PZ_Etap1_Start", 0, 0, 30, false);	// 1 этап стартует через 30 дней
			}
			else
			{
				Notification_Perk(false, "Trustworthy");
				link.l1 = "Eu realmente arrancaria as páginas e depois entregaria o arquivo com uma cara de quem não liga?";
				link.l1.go = "Merdok_book_3";
				SetTimerCondition("PZ_LigaInJungle", 0, 0, 7, false);	// проверку не прошёл, значит нападёт Лига через неделю, после чего начнётся таймер на 30 дней 1 этапа
			}
			LAi_Fade("", "");
		break;
		
		case "Merdok_book_3":
			dialog.text = "A ganância, a estupidez e a ousadia às vezes levam as pessoas aos atos mais insanos, Capitão.";
			link.l1 = "Nenhuma dessas três coisas me motivou, pode acreditar.";
			link.l1.go = "Merdok_book_4";
		break;
		
		case "Merdok_book_4":
			dialog.text = "Então você está dizendo que van Merden tirou aquelas páginas e as escondeu em outro lugar?";
			link.l1 = "Exatamente. Posso voltar e procurá-los—revirar toda a farmácia, ou até mesmo toda St. John's—se você achar necessário.";
			link.l1.go = "Merdok_book_5";
		break;
		
		case "Merdok_book_5":
			dialog.text = "Não precisa, senhor. O que importa está aqui de qualquer jeito, e sem as páginas que faltam, o resto não me ameaça.";
			link.l1 = "";
			link.l1.go = "Merdok_book_6";
		break;
		
		case "VD_Merdok_book_3":
			dialog.text = "Então, é falta de cuidado ou curiosidade, e não desonestidade ou algum plano secreto? Você acha que já estava assim quando encontrou?";
			link.l1 = "Provavelmente, senhor Rodenburg. Talvez van Merden tenha arrancado essas páginas antes. ";
			link.l1.go = "VD_Merdok_book_4";
		break;
		
		case "VD_Merdok_book_4":
			dialog.text = "Talvez seja melhor assim. Sem essas páginas, o resto do arquivo não representa ameaça para mim – especialmente em mãos ignorantes.";
			link.l1 = "";
			if (IsCharacterPerkOn(pchar, "Trustworthy")) link.l1.go = "Merdok_book_6";
			else link.l1 = "Merdok_6";
		break;
		
		case "Merdok_book_6":
			dialog.text = "Há uma recompensa pelo arquivo - este belo mosquete. Ele me serviu com grande distinção, e agora é seu!";
			link.l1 = "Obrigado!";
			link.l1.go = "Merdok_6";
			GiveItem2Character(PChar, "mushket2");
		break;
		
		case "Merdok_6":
			dialog.text = "Fizemos um ótimo trabalho, você e eu, kapitein. Não é exagero dizer que nada disso teria acontecido sem você. Se continuar servindo à República, vai alcançar alturas incríveis na sua carreira, talvez até seja nobilitado.";
			link.l1 = "Acho que isso é um adeus, senhor Rodenburg.";
			link.l1.go = "Merdok_7";
		break;
		
		case "Merdok_7":
			dialog.text = "É um adeus, "+pchar.name+". Já realizei tudo o que queria aqui, então partirei para casa, em Amsterdã, daqui a uma semana. Minha nova esposa Abigail e meu sogro Solomon irão comigo. Peter Stuyvesant já encontrou um novo vice-diretor para a Companhia, então fale com ele se precisar de algo\nPelo seu serviço, lhe dou a Meifeng. Agora ela é sua, kapitein, você merece.";
			link.l1 = "Obrigado, senhor Rodenburg. Já me apeguei bastante à Meifeng e já comecei a considerá-la como minha.";
			link.l1.go = "Merdok_8";
		break;
		
		case "Merdok_8":
			dialog.text = "E agora preciso pedir que você me deixe, meu rapaz. Tenho muitas coisas para resolver antes de zarparmos... Venha me visitar em Amsterdã algum dia! Vamos tomar um drinque e relembrar os bons tempos...";
			link.l1 = "Sim, senhor. Espero que todos estejam felizes e prósperos nessa nova vida! Adeus!";
			link.l1.go = "Merdok_9";
			// belamour legendary edition -->
			link.l2 = "Pois bem, senhor. Espero que todos estejam felizes e prósperos nessa nova vida!\n(entre dentes cerrados) ... Espero que a gente nunca mais se veja, seu arrogante de uma figa. Só espere até descobrir as delícias de ser casado com uma 'recatada' judia insuportável.";
			link.l2.go = "Merdok_9a";
		break;
		
		case "Merdok_9a":
			AddCharacterExpToSkill(pchar, "FencingL", 60);
			AddCharacterExpToSkill(pchar, "FencingS", 60);
			AddCharacterExpToSkill(pchar, "FencingH", 60);
			AddCharacterExpToSkill(pchar, "Pistol", 60);
			DialogExit();
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//можно пользоваться ПУ
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Holl = "end";
			AddQuestRecord("Holl_Gambit", "1-41");
			CloseQuestHeader("Holl_Gambit");
			sld = characterFromId("Abigile");//уберем Аби
			sld.lifeday = 0;
			sld = characterFromId("Solomon");//уберем Соломона
			sld.lifeday = 0;
			pchar.quest.Lucas_quit.win_condition.l1 = "Timer";
			pchar.quest.Lucas_quit.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Lucas_quit.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 7);
			pchar.quest.Lucas_quit.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 7);
			pchar.quest.Lucas_quit.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 7);
			pchar.quest.Lucas_quit.function = "LucasQuit";//прерывание на Лукаса
			pchar.questTemp.HWIC.Detector = "holl_win";
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			sld.Dialog.Filename = "Common_Mayor.c";//patch-8
			sld.dialog.currentnode = "First time";
			sld.quest.meeting = "1";
			DelMapQuestMarkCity("Villemstad");
			AddMapQuestMarkCity("FortFrance", false);
			AddLandQuestMark(characterFromId("Mishelle"), "questmarkmain");
			AddSimpleRumourCity("Mynheer Rodenburg has sailed to Amsterdam with his young wife and father-in-law. Are you the new vice-director?", "Villemstad", 30, 3, "");
			AddSimpleRumour("They say, kapitein, that you are well regarded by the governor-general. Mynheer Rodenburg supposedly appointed you as his successor in the Company, is that so?", HOLLAND, 30, 3);
		break;
		
		case "Merdok_9":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			// <-- legendary edition
			DialogExit();
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//можно пользоваться ПУ
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Holl = "end";
			AddQuestRecord("Holl_Gambit", "1-41");
			CloseQuestHeader("Holl_Gambit");
			sld = characterFromId("Abigile");//уберем Аби
			sld.lifeday = 0;
			sld = characterFromId("Solomon");//уберем Соломона
			sld.lifeday = 0;
			pchar.quest.Lucas_quit.win_condition.l1 = "Timer";
			pchar.quest.Lucas_quit.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Lucas_quit.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 7);
			pchar.quest.Lucas_quit.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 7);
			pchar.quest.Lucas_quit.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 7);
			pchar.quest.Lucas_quit.function = "LucasQuit";//прерывание на Лукаса
			pchar.questTemp.HWIC.Detector = "holl_win";
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			sld.Dialog.Filename = "Common_Mayor.c";//patch-8
			sld.dialog.currentnode = "First time";
			sld.quest.meeting = "1";
			DelMapQuestMarkCity("Villemstad");
			AddMapQuestMarkCity("FortFrance", false);
			AddLandQuestMark(characterFromId("Mishelle"), "questmarkmain");
			AddSimpleRumourCity("Mynheer Rodenburg has sailed to Amsterdam with his young wife and father-in-law. Are you the new vice-director?", "Villemstad", 30, 3, "");
			AddSimpleRumour("They say, kapitein, that you are well regarded by the governor-general. Mynheer Rodenburg supposedly appointed you as his successor in the Company, is that so?", HOLLAND, 30, 3);
		break;
		
//----------------------------------------------за Англию------------------------------------------------------
		case "Lucas_abordage":
			dialog.text = "Deus do céu! Cão do Fleetwood! Pode até vencer hoje, mas Lucas Rodenburg não entregará sua vida facilmente.";
			link.l1 = "Eu não acho que não. Você vai entregar sua vida pra mim de graça, seu holandês miserável.";
			link.l1.go = "Lucas_abordage_1";
		break;
		
		case "Lucas_abordage_1":
			PlaySound("Voice\English\hambit\Lucas Rodenburg-04.wav");
			dialog.text = "Das profundezas do inferno eu vou cagar na sua boca! Acabei de incendiar o porão de carga e o fogo logo vai alcançar o paiol de pólvora! Nossos navios estão presos lado a lado, então não há esperança de fuga! Você vai queimar ou servir de comida para os tubarões!";
			link.l1 = "Droga! Recuem, homens, precisamos bater em retirada!";
			link.l1.go = "Lucas_abordage_2";
			// belamour legendary edition -->
			link.l2 = "Eu não vou sair até sua alma deixar seu corpo. Fique parado, isso vai doer.";
			link.l2.go = "Lucas_abordage_2a";
		break;
		
		case "Lucas_abordage_2a":
			AddCharacterExpToSkill(pchar, "FencingL", 60);
			AddCharacterExpToSkill(pchar, "FencingS", 60);
			AddCharacterExpToSkill(pchar, "FencingH", 60);
			AddCharacterExpToSkill(pchar, "Pistol", 60);
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("PrepareToBoom1"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.GenQuest.Detonation = true; // patch-4
		break;
		
		case "Lucas_abordage_2":
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			// <-- legendary edition
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("PrepareToBoom1"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.GenQuest.Detonation = true; // patch-4
		break;
		
//----------------------------------------------против всех--------------------------------------------------
		case "LucasPrisoner":
			dialog.text = "Por que você está aqui, seu desgraçado? Veio me ridicularizar? Talvez finalmente me conte qual é o seu papel nessa história. Foi você quem capturou o brigantim, não foi? Era esse o seu plano desde o começo?";
			link.l1 = "Estou aqui para entregar uma mensagem, Lucas Rodenburg. Saudações de John Merdock, o homem que você traiu. Você era minha missão, e eu a cumpri. Até logo, por enquanto.";
			link.l1.go = "LucasPrisoner_1";
		break;
		
		case "LucasPrisoner_1":
			PlaySound("Voice\English\hambit\Lucas Rodenburg-04.wav");
			dialog.text = "Johan? Haha! Então era esse o homem por trás de tudo isso! Aquele velho canalha! Mas o jogo ainda não acabou. Jacob van Berg está vindo atrás de você, e você não vai escapar! Você e seu navio estão perdidos, seu miserável vagabundo do mar!";
			link.l1 = "Guarde suas palavras para o tribunal do carrasco, Rodenburg.";
			link.l1.go = "LucasPrisoner_2";
		break;
		
		case "LucasPrisoner_2":
			DialogExit();
			pchar.questTemp.jailCanMove = true; //разрешить пройти мимо стражи
			LAi_SetPlayerType(pchar);
			pchar.quest.Login_Joakim.win_condition.l1 = "location";
			pchar.quest.Login_Joakim.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Login_Joakim.function = "Create_Joakim";
			pchar.questTemp.HWIC.Self = "JoakimMeeting";
			SetFunctionTimerCondition("LucasQuit", 0, 0, 7, false);
		break;
	}
}
