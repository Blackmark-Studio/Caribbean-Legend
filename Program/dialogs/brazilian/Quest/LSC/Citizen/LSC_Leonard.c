// Леонард Маскетт - пьяница
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iPeso, iDubl;
	string sPeso, sDubl;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Cai fora, camarada! Não fico de papo com canalha que ataca gente inocente.";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			// --> пей до дна
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "find" && CheckAttribute(npchar, "quest.answer_3") && GetNpcQuestPastDayParam(npchar, "quest_date") >= 3 && !CheckAttribute(npchar, "quest.facio"))
			{
				dialog.text = "Amigo, você chegou na hora certa... Quero conversar com você sobre uns negócios... negócios importantes.";
				link.l1 = "Sério? Ora, Leonard... Acho mesmo que você está sóbrio! Que visão rara!";
				link.l1.go = "facio";
				break;
			}
			// <-- пей до дна
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "A-a... hic! Olá, camarada...";
				link.l1 = TimeGreeting()+". Parece que você já teve o suficiente, 'camarada.'";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! Hic! O que você quer?";
				link.l1 = LinkRandPhrase("O que há de novo, Leonard?","Aconteceu alguma novidade na ilha?","Você vai me contar as últimas fofocas?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Quero te fazer algumas perguntas sobre a ilha.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Só queria saber como você está. Tchau!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "É isso aí! Já chega? Não! Nem perto de chegar, h-hic! Sim, Leonard Musket está bêbado e é assim que tem que ser!";
			link.l1 = "Gosta de uma bebida, hein? Sim, meu nome é "+GetFullName(pchar)+". Prazer em... te conhecer.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Se você diz. Estamos todos - hic! - reunidos, então... e agora?";
			link.l1 = "Tudo bem, se você está muito, ahm... ocupado pra conversar... Fica pra outra hora, então!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("O que há de novo por aqui?","Aconteceu algo novo na ilha?","Você vai me contar as últimas fofocas?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Quero te fazer algumas perguntas sobre a ilha.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
		// --> пей до дна
		case "facio":
			dialog.text = "A-haha, vai se ferrar! Sim, camarada, estou - quase - sóbrio. E isso porque tenho uma oportunidade pra nós...";
			link.l1 = "Que tipo de oportunidade? Fale logo, não me faça perder tempo!";
			link.l1.go = "facio_1";
			npchar.quest.facio = "true";
		break;
		
		case "facio_1":
			dialog.text = "Amigo... quer ganhar um dinheiro? Pesos de prata, dobrões de ouro? Eu te conto como. Mas vai ter que dividir comigo – vamos trabalhar juntos.";
			link.l1 = "Sempre topo ganhar dinheiro. Mas tudo depende da sua proposta: o quão lucrativa e o quão... legal... ela é.";
			link.l1.go = "facio_2";
		break;
		
		case "facio_2":
			dialog.text = "The business is not really legal, sure, but it is profitable... and we'll be able to punish a miser for his greed. He won't end up poor; he has too much money.\nBesides, everyone shares with him, so it's his turn to return the favour. Tell me, can you hold your liquor? How much rum are you able to drink before going under table?";
			link.l1 = "Depende. Não costumo beber demais... Você vai finalmente me contar os detalhes?";
			link.l1.go = "facio_3";
		break;
		
		case "facio_3":
			dialog.text = "Certo. Vou ser específico. Tem um desgraçado gordo e feio na ilha, o Giuseppe Fazio. (cospe) Ele explora os Narvais, os Rivados e os locais. Estou de olho nele faz um tempo e descobri uma coisa...\nTem dois baús na cabine dele, no Caroline: um com papéis, outro com ouro e prata. Os dois estão trancados com chaves diferentes. O gordo safado sempre carrega as chaves no bolso.";
			link.l1 = "Então, você pretende roubar o Fazio? Desculpe, camarada, não vou me meter nisso. E agradeça por eu não contar pra ninguém. Procure outro parceiro.";
			link.l1.go = "facio_exit";
			link.l2 = "Ha! Interessante! Continue...";
			link.l2.go = "facio_4";
		break;
		
		case "facio_exit":
			dialog.text = "Que pena, que pena... tem ouro de sobra pra nós dois... Tudo bem, então. Até mais.";
			link.l1 = "Adeus.";
			link.l1.go = "exit";
		break;
		
		case "facio_4":
			dialog.text = "Duas portas levam à cabine dele. Uma delas está sempre trancada, mas a chave que abre o baú de ouro também abre a porta. Eu já vi ele fazer isso. Você só precisa dessa chave para entrar na cabine e pegar o ouro. Mas como conseguir a chave?\nTenho um plano, um plano excelente. Se tudo correr bem, Fazio nunca vai saber o que aconteceu, nem quem culpar. Ele vai achar que foi o misterioso ladrão de rum e joias. O problema é que preciso de um parceiro com cabeça dura pra conseguir fazer isso. Entendeu?";
			link.l1 = "Sim. Continue.";
			link.l1.go = "facio_5";
		break;
		
		case "facio_5":
			dialog.text = "Fazio loves to sit at Sancho's and have a good drink - and he can hold his liquor better than anyone I've ever seen! He knows it, too; he came up with a drinking game: a game where people try to drink him under the table.\nIf you ask him to play this game, I promise you he'll agree. And then comes the fun part.\nYou make a bet with him, go to the tavern, grab a bottle of rum, and drink until one of you kisses the table. If you pass out first then the whole plan is ruined; I won't be able to do it alone.\nThat's why I asked about your head. All you have to do is make sure he drops first. I'll be nearby, waiting. When he's down, I'll take his keys.\nThen we move the fat man to a bed upstairs and sneak into his cabin while he's asleep. I'll return the key right after we loot his chest - he won't even realize he's been robbed 'til he opens the chest, ha-ha!\nOnce we've got the key, you sneak into his cabin and take what you can. I'll stay on guard outside. We split the chest's contents, half-and-half, and go our separate ways. So, are you in?";
			link.l1 = "Um plano ardiloso! Claro, estou dentro.";
			link.l1.go = "facio_6";
			link.l2 = "Não, camarada. Vou deixar passar. Acho que não aguento bebida tão bem assim. Procure outro parceiro, alguém um pouco mais resistente do que eu.";
			link.l2.go = "facio_exit";
		break;
		
		case "facio_6":
			dialog.text = "Fico feliz por ter acertado sobre você. Agora, vá até o Fazio e marque um encontro na taverna hoje à noite, depois das nove. Espero que você derrote aquele porco no próprio jogo dele! Boa sorte, até mais tarde!";
			link.l1 = "Vou fazer o meu melhor... tchau!";
			link.l1.go = "facio_7";
		break;
		
		case "facio_7":
			DialogExit();
			NextDiag.CurrentNode = "facio_wait";
			pchar.questTemp.LSC.Drink = "begin";
			pchar.questTemp.LSC.Drink.Chance = hrand(100); // итог бухалова
			if (CheckAttribute(pchar, "questTemp.CanDrink")) pchar.questTemp.LSC.Drink.Chance = sti(pchar.questTemp.LSC.Drink.Chance)+50;
			SetFunctionTimerCondition("LSC_DrinkOver", 0, 0, 3, false); // 3 дня
			AddQuestRecord("LSC_Drink", "1");
		break;
		
		case "facio_wait":
			dialog.text = "Amigo, estou contando com você. Derrube aquele pão-duro na bebida...";
			link.l1 = "Claro.";
			link.l1.go = "exit";
			NextDiag.TempNode = "facio_wait";
		break;
		
		case "result_0":
			dialog.text = "It's done, the pig is asleep upstairs. I've got the key. You're doing well; you seem to be sober enough!";
			link.l1 = "S-sério? Faz - hic! - tanto tempo que eu não fico tão... tão bêbado assim. Tô meio tonto... Hic! Vamos?";
			link.l1.go = "result_win";
		break;
		
		case "result_1":
			dialog.text = "It's done, that fat pig is asleep upstairs. I have the key. You're doing good; you really managed to over drink that piggy...";
			link.l1 = "Já fiquei, mas faz - hic! - tanto tempo que não bebia tanto assim. Minha cabeça está girando... vamos antes que eu desmaie.";
			link.l1.go = "result_win";
		break;
		
		case "result_2":
			dialog.text = "É, camarada, você não conseguiu beber mais que o grandalhão... Que pena. Bom, pelo menos tentamos...";
			link.l1 = "M-maldição, ele é como um... b-barril sem fundo. Argh, preciso d-descansar... Já chega, v-vaza daqui! Hic!..";
			link.l1.go = "result_fail";
		break;
		
		case "result_win":
			dialog.text = "Sim. Vamos! Me siga até a Caroline! E não se perca, não temos muito tempo!";
			link.l1 = "Sim, v-vamos!";
			link.l1.go = "result_win_1";
		break;
		
		case "result_win_1":
			DialogExit();
			NextDiag.CurrentNode = "result_win_2";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload6", "LostShipsCity_town", "reload", "reload39", "LSC_DrinkGotoCarolina", -1);
			AddQuestRecord("LSC_Drink", "3");
		break;
		
		case "result_win_2":
			pchar.quest.LSC_Drink1.over = "yes"; //снять таймер
			dialog.text = "Aqui. Pegue a chave. O baú que você procura está à esquerda da entrada. Pegue o máximo que conseguir, o mais rápido possível. Não esqueça de trancá-lo de novo! Se eu vir algo, vou bater na porta três vezes. Fuja pela galeria dos fundos.";
			link.l1 = "Tudo bem. Fique atento!";
			link.l1.go = "result_win_3";
		break;
		
		case "result_win_3":
			DialogExit();
			GiveItem2Character(pchar, "key_facioQ");
			NextDiag.CurrentNode = "result_grabbing";
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "reload", "reload25", "LSC_DrinkGotoCarolina_3", -1);
		break;
		
		case "result_grabbing":
			// считаем деньги и дублоны взятые из сундука
			iPeso = sti(pchar.money)-sti(pchar.questTemp.LSC.Drink.Money);
			iDubl = GetCharacterItem(pchar, "gold_dublon")-sti(pchar.questTemp.LSC.Drink.Dublon);
			if (iPeso <= 0) sPeso = "not a single peso";
			else sPeso = ""+FindRussianMoneyString(iPeso)+"";
			if (iDubl <= 0) sDubl = "not a single doubloon";
			else sDubl = ""+iDubl+" doubloons";
			if (iPeso <= 10000 && iDubl <= 10) sTotalTemp = "What a miserable haul... Why'd we even bother? Eh... fine, let's split what we've got.";
			else
			{
				if (iPeso <= 50000 && iDubl <= 100) sTotalTemp = "I thought that there'd be much more... Hardly worth the risk. Eh... fine, let's split what we have got.";
				else
				{
					if (iPeso <= 100000 && iDubl <= 300) sTotalTemp = "Hm. Not bad. But I thought there'd be more. All right, let's split it.";
					else 
					{
						if (iPeso <= 150000 && iDubl <= 500) sTotalTemp = "Excellent! We've done well, partner! This is a lot of coin! Let's split it!";
						else
						{
							sTotalTemp = "Damn me! I never imagined the fat man's stash was so huge. Well done, partner! Let's split the loot!";
						}
					}
				}
			}
			dialog.text = "Finalmente! O que você conseguiu tirar daquele pão-duro? Mostre-me!";
			if (iPeso <= 0 && iDubl <= 0)
			{
				link.l1 = "Não havia nada. Só uns poucos objetos - amuletos e coisas assim.";
				link.l1.go = "grabbing_0";
			}
			else
			{
				link.l1 = "Encontrei "+sPeso+" e "+sDubl+"";
				link.l1.go = "grabbing_1";
			}
		break;
		
		case "grabbing_0":
			dialog.text = "Não! Parece que foi tudo em vão... Talvez aquele desgraçado tenha escondido o tesouro em outro baú. Eh! Tá bom, me dá a chave e eu devolvo. Adeus, camarada... droga...";
			link.l1 = "...";
			link.l1.go = "grabbing_exit";
			AddQuestRecord("LSC_Drink", "6");
		break;
		
		case "grabbing_1":
			dialog.text = sTotalTemp;
			link.l1 = "Vamos compartilhar.";
			link.l1.go = "grabbing_part";
		break;
		
		case "grabbing_part":
			iPeso = makeint((sti(pchar.money)-sti(pchar.questTemp.LSC.Drink.Money))/2);
			iDubl = makeint((GetCharacterItem(pchar, "gold_dublon")-sti(pchar.questTemp.LSC.Drink.Dublon))/2);
			AddMoneyToCharacter(pchar, -iPeso);
			RemoveItems(pchar, "gold_dublon", iDubl);
			Log_Info("You have given "+iDubl+" doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Certo, me dê a chave e eu devolvo. Até mais, camarada.";
			link.l1 = "Boa sorte, amigo.";
			link.l1.go = "grabbing_exit";
			AddSimpleRumourCityTip("Fazio was complaining that someone cleaned out his chest. It seems the mysterious thief did it.", "LostShipsCity", 3, 1, "LSC", "");
			AddSimpleRumourCityTip("Haven't you heard? Fazio was robbed! He was robbed while lying dead drunk after having a game with you.", "LostShipsCity", 3, 1, "LSC", "");
			AddSimpleRumourCityTip("You have a strong head! To drink so much rum and stay on your feet! That's something.", "LostShipsCity", 3, 2, "LSC", "");
			AddQuestRecord("LSC_Drink", "5");
		break;
		
		case "grabbing_exit":
			DialogExit();
			RemoveItems(pchar, "key_facioQ", 1);
			int n = Findlocation("CarolineBank");
			locations[n].private2.QuestClosed = true; // запираем сундук
			LocatorReloadEnterDisable("CarolineBank", "reload1", false); // на галерею
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload38", "FleuronTavern", "goto", "goto2", "OpenTheDoors", 15.0);
			pchar.quest.LSC_Drink4.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink4.win_condition.l1.date.hour  = sti(GetTime()+5);
			pchar.quest.LSC_Drink4.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink4.function = "LSC_DrinkDelete";
		break;
		
		case "result_fail":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "LostShipsCity_town", "goto", "goto05_2", "", 10);
			chrDisableReloadToLocation = false;//открыть локацию
			n = Findlocation("CarolineBank");
			locations[n].private2.QuestClosed = true; // запираем сундук
			pchar.quest.LSC_Drink4.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink4.win_condition.l1.date.hour  = sti(GetTime()+5);
			pchar.quest.LSC_Drink4.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink4.function = "LSC_DrinkDelete";
			AddQuestRecord("LSC_Drink", "4");
		break;
		// <-- пей до дна
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Sério?... hic! Estou ouvindo...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Como você veio parar aqui?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Você está sempre bebendo? E de onde tira dinheiro pra isso?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "O que você pode me contar sobre os moradores daqui?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Você gostaria de sair daqui e ir para o continente espanhol?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Sem perguntas. Perdão...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "É! Sabe, eu não me lembro. É verdade, não lembro mesmo! Faz muito tempo. Eu estava navegando por aí... de algum jeito... enfim, acabei vindo parar aqui. Hic!";
			link.l1 = "Hm... Tudo bem...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Sim, eu bebo. Sou um bêbado... Bebendo... droga, porque não me resta mais nada! Veja, camarada, eu já era. Esta garrafa de rum é a única coisa que eu quero na vida. Então vou continuar bebendo! E dinheiro... he-he, rum não custa quase nada.\nDe qualquer forma, nem preciso pagar por ele. Tem um lugar cheio de rum, mas você precisa nadar pra chegar lá. Por isso só compro rum quando estou bêbado demais pra nadar... hic! Jizjezezejizeze... não, não vou te contar onde nadar, he-he, nem adianta perguntar...";
			link.l1 = "Delicioso.";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "O que posso dizer - hic! - sobre eles? Gente boa pra conversar e beber junto. Giuseppe Fazio é um homem importante, um figurão. Os baús dele estão cheios de ouro... pfuh! Mão de vaca... mas respeita o velho Leonard, paga bebida pra ele na taverna. Às vezes também pede algo em troca, mas é pouca coisa - hic! Heh, sabe quantos dobrões o Fazio tem? Aha-ha-ha! Daria pra passar o resto da vida na melhor taverna do Caribe, sem trabalhar, só bebendo o melhor rum do mundo. Mas ele fica aqui, na ilha. Parece que dinheiro nunca é suficiente pra ele...";
			link.l1 = "Entendi...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
			SaveCurrentNpcQuestDateParam(npchar, "quest_date");
		break;
		
		case "ansewer_4":
			dialog.text = "Sair? Hic! Por quê? Não, não quero ir para o continente, nem para a Europa, nem para nenhuma ilha miserável desse mundo. Tem rum de graça por aí? Não! Não tem... não tem rum de graça - hic! O que significa que não tem nada lá pra mim... Amigo, estou bem aqui. Ei, ei - hic! - pergunta pro pessoal se eles querem sair daqui. Ninguém quer, só dois ou três - hic!";
			link.l1 = "Interessante...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Ei, porco, tira as mãos do meu - hic! - estoque!","Acha que pode roubar o pobre Leonard só porque ele bebe, é? É?! Eu vou te mostrar!","Afaste-se dos meus baús! Quem te mandou, aquele porco gordo do Fazio?!");
			link.l1 = "Seu bêbado desgraçado!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Larga do meu baú, seu criminoso!";
			link.l1 = "Garota tola!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Ei, camarada, guarda essa - hic! - espada. Você vai acabar machucando alguém.","Você não está bêbado... bêbado o suficiente para segurar uma espada. Guarde isso e venha tomar um drinque.","Você parece um verdadeiro idiota balançando essa espada desse jeito. Guarda isso - hic! - guarda logo.");
			link.l1 = LinkRandPhrase("Tudo bem.","Tudo bem.","Idiota... tá bom.");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Olha, você não pode - hic! - não pode ficar balançando sua espada assim. Para com isso.","Você não está bêbado... bêbado o bastante pra segurar uma espada. Guarda isso e vem tomar uma bebida.");
				link.l1 = LinkRandPhrase("Tudo bem.","Certo.","Como você diz...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ei, camarada, guarda essa - hic! - espada. Você vai acabar machucando alguém.","Você parece um verdadeiro idiota balançando essa espada desse jeito. Guarda isso - hic! - guarda logo.");
				link.l1 = RandPhraseSimple("Desculpe.","Estou guardando isso.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
