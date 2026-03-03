// шаман команчей Змеиный Глаз
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "calendar")
			{
				dialog.text = "Saudações, meu amigo pálido.";
				link.l2 = "Fico feliz em te ver também, meu irmão de pele vermelha. Tenho um assunto importante para você de novo.";
				link.l2.go = "calendar";
				break;
			}
			dialog.text = "Saudações, meu amigo pálido.";
			link.l1 = "Também estou feliz em te ver, Olho de Cobra.";
			link.l1.go = "exit";
			if (CheckAttribute(npchar, "quest.amulet") && CheckCharacterItem(pchar, pchar.questTemp.Saga.BaronReturn.Indian) && CheckCharacterItem(pchar, pchar.questTemp.Saga.BaronReturn.Amulet) && CheckCharacterItem(pchar, pchar.questTemp.Saga.BaronReturn.Obereg))
			{
				link.l2 = "Trouxe os amuletos que você pediu. Vamos negociar.";
				link.l2.go = "SnakeEye_potion";
			}
			if (CheckAttribute(pchar, "questTemp.LSC")) // был в LSC
			{
				if (CheckAttribute(npchar, "quest.LSC_hello") && CheckCharacterItem(pchar, "buben"))
				{
					link.l2 = "Encontrei seu pandeiro, Olho de Cobra. Dá uma olhada.";
					link.l2.go = "LSC_buben";
				}
				if (CheckAttribute(npchar, "quest.LSC_tube") && CheckCharacterItem(pchar, "smoking_tube"))
				{
					link.l2 = "Encontrei um cachimbo indígena interessante, Olho de Cobra. Dê uma olhada.";
					link.l2.go = "LSC_tube";
				}
				if (!CheckAttribute(npchar, "quest.LSC_hello"))
				{
					link.l2 = "Olá, xamã. Usei a estátua e vivi uma experiência incrível. Você estava absolutamente certo. Encontrei o cemitério de navios, o capitão branco e até o porão de carga com os mantimentos!";
					link.l2.go = "LSC_hello";
				}
				if (CheckAttribute(npchar, "quest.LSC_hello") && pchar.questTemp.Saga.BaronReturn == "shamane")
				{
					link.l3 = "Olho de Cobra, preciso da sua ajuda.";
					link.l3.go = "Saga_nathaniel";
				}
			}		
			NextDiag.TempNode = "First time";
		break;
		
	//---------------------------------------- первая встреча------------------------------------------------
		case "SnakeEye":
			dialog.text = "Saudações, meu amigo pálido.";
			link.l1 = "Olá, xamã. Por que você acha que sou seu amigo?";
			link.l1.go = "SnakeEye_1";
		break;
		
		case "SnakeEye_1":
			dialog.text = "Eu sei muita coisa, mas nem sempre sei exatamente o quê. Você veio aqui com um propósito. O destino te trouxe até aqui, e eu estou aqui para te ajudar.";
			link.l1 = "Bom saber! De fato, estou aqui para contar com sua ajuda, meu amigo de pele vermelha. Vou ser direto: o que você quis dizer ao contar para a esposa do Hawk sobre Kukulcan?";
			link.l1.go = "SnakeEye_2";
		break;
		
		case "SnakeEye_2":
			dialog.text = "Até peixe morto vai embora com a correnteza. E um homem vivo é levado pelo destino de objetivo em objetivo. O objetivo do capitão acorrentado, perseguido por homens cruéis na selva, era a estátua de Kukulcan. Se ele se sacrificasse, poderia estar bem longe daqui.";
			link.l1 = "Eu não entendi nada. Para que serve a estátua do seu deus, e como o Hawk conseguiu ir tão longe a pé que ninguém consegue encontrá-lo até agora?";
			link.l1.go = "SnakeEye_3";
		break;
		
		case "SnakeEye_3":
			dialog.text = "Se Kukulcan engoliu o Hawk, então pode cuspir ele em qualquer lugar. Talvez até em outro mundo. Kukulcan já me engoliu três vezes. E cada vez, fui parar em um lugar diferente. Há muito tempo, cheguei aqui e decidi não arriscar mais. Não entrei mais na boca de Kukulcan, e não sei onde ele cospe suas vítimas.";
			link.l1 = "Meu Deus, isso foge completamente ao meu entendimento! Você está me dizendo que o ídolo de pedra pode teleportar pessoas para longe?";
			link.l1.go = "SnakeEye_4";
		break;
		
		case "SnakeEye_4":
			dialog.text = "Não só isso. Kukulcan governa não só o espaço, mas também o tempo. Ou talvez até mais do que isso. Contei ao capitão acorrentado sobre a estátua de ouro que devora pessoas. Talvez ele tenha decidido arriscar quando viu que os perseguidores estavam perto...";
			link.l1 = "Espera, a estátua é de pedra. E você está falando de uma de ouro...";
			link.l1.go = "SnakeEye_5";
		break;
		
		case "SnakeEye_5":
			dialog.text = "À meia-noite, o ídolo ganha vida e se transforma em ouro. Nesse momento, o espírito de Kukulcan habita nele. Cuidado ao se aproximar, ou você pode ver o nascer do sol de outro lugar. Até as estrelas podem mudar de lugar no céu. Você pode encontrar quem ainda não nasceu, ou presenciar o nascimento de quem morreu há muito tempo, ou de quem jamais existiu.";
			link.l1 = "O que... mais enigmas e charadas... Você me intriga, Olho de Cobra. Você disse que sobreviveu a três encontros com Kukulcan, o deus em quem você acredita. Então por que eu não deveria tentar a sorte com o ídolo de um deus em quem eu não acredito?";
			link.l1.go = "SnakeEye_6";
		break;
		
		case "SnakeEye_6":
			dialog.text = "Pena. Pena que você não acredita. Talvez o próprio Kukulcan tenha te chamado e feito você deixar a terra dos seus ancestrais. Mas você ainda não o escuta. Tudo acontece por um bom motivo. Se decidir arriscar, saiba que só sobrevivi todas as vezes porque tinha poções Comanche maravilhosas.";
			link.l1 = "Comanche? Isso é outra tribo?";
			link.l1.go = "SnakeEye_7";
		break;
		
		case "SnakeEye_7":
			dialog.text = "That is what enemies call my people, whom I will never see again. The potion restores strength and endurance, and also heals and saves you from strong poisons. You need several flasks, but I have only three left.\nThere were four flasks, but I lost one in a strange place; it looks like a cemetery of white men's ships. That is where I began my journey in this world. Perhaps Kukulcan spat the captain out there. If so, I do not envy him.";
			link.l1 = "O que é este lugar? O cemitério de navios?";
			link.l1.go = "SnakeEye_8";
		break;
		
		case "SnakeEye_8":
			dialog.text = "Strange place... It should not exist, yet it does. People who kill because of skin colour live there. They keep their supplies inside a big ship where Kukulcan spat me out. I did not go into its hold, which they protect from thieves; they aren't trusting neighbours. If you get there - find another exit, don't go into the hold or there will be trouble.\nWhite Boy will help you find another statue if he still lives. Give him this white bead. He likes them.";
			link.l1 = "Hum. Minha cabeça já está girando e isso só fica cada vez mais interessante. Continue, meu irmão pele-vermelha.";
			link.l1.go = "SnakeEye_9";
		break;
		
		case "SnakeEye_9":
			Log_Info("You have received a white pearl");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "jewelry52");
			dialog.text = "Se você encontrar o capitão vivo, ele pode estar muito doente. Não tive tempo de lhe dar a poção. Procure meu tamborim lá. Ganhei do meu avô. Tem muitas coisas na bolsa que perdi, mas só preciso do tamborim. É difícil falar com os espíritos sem ele.";
			link.l1 = "Bem, esse lugar parece muito interessante! Tomara que o Hawk tenha sido teleportado pra lá... Você vai me dar sua poção?";
			link.l1.go = "SnakeEye_10";
		break;
		
		case "SnakeEye_10":
			dialog.text = "Eu vou te dar. Mas você precisa me dar três amuletos locais em troca: "+XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Indian)+", "+XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Amulet)+" e "+XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Obereg)+". Um frasco para cada amuleto. Assim é justo. Volte quando tiver todos os amuletos. Então faremos a troca. Não pense que sou ganancioso. Ou talvez você mude de ideia enquanto procura pelos amuletos.";
			link.l1 = "Eu não vou pensar isso. Espere por mim, Olho de Cobra, eu volto logo.";
			link.l1.go = "SnakeEye_11";
		break;
		
		case "SnakeEye_11":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			npchar.quest.amulet = "true";
			AddQuestRecord("BaronReturn", "3");
			AddQuestUserData("BaronReturn", "sItem1", XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Indian));
			AddQuestUserData("BaronReturn", "sItem2", XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Amulet));
			AddQuestUserData("BaronReturn", "sItem3", XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Obereg));
			sld = characterFromId("Danielle");
			sld.quest.talk = "SnakeEye";
			pchar.quest.BaronReturn_out.win_condition.l1 = "ExitFromLocation";
			pchar.quest.BaronReturn_out.win_condition.l1.location = pchar.location;
			pchar.quest.BaronReturn_out.function = "Saga_DannyTalk";
			pchar.questTemp.HelenDrinking.GiveAmulets = true;
			
			//if (GetCharacterIndex("Longway") != -1 && CheckPassengerInCharacter(pchar, "Longway") && CheckAttribute(pchar, "questTemp.PZ_Etap4_Start"))
			if (GetCharacterIndex("Longway") != -1 && CheckPassengerInCharacter(pchar, "Longway"))	// Временно так
			{
				// Квест "Путеводная звезда", начало 4 этапа
				PChar.quest.PZ_Etap4_Start.win_condition.l1 = "location";
				PChar.quest.PZ_Etap4_Start.win_condition.l1.location = "Shore9";
				PChar.quest.PZ_Etap4_Start.win_condition = "PZ_Etap4_Start";
				locations[FindLocation("Shore9")].DisableEncounters = true;
			}
		break;
		
		// даёт зелья - идем на телепортацию
		case "SnakeEye_potion":
			dialog.text = "Muito bem, meu amigo. Você trouxe os amuletos para poder ir até Kukulcan?";
			link.l1 = "Sim. Estou pronto para embarcar na mesma jornada que Nathaniel, o capitão acorrentado, fez um dia.";
			link.l1.go = "SnakeEye_potion_1";
		break;
		
		case "SnakeEye_potion_1":
			RemoveItems(pchar, pchar.questTemp.Saga.BaronReturn.Indian, 1);
			RemoveItems(pchar, pchar.questTemp.Saga.BaronReturn.Amulet, 1);
			RemoveItems(pchar, pchar.questTemp.Saga.BaronReturn.Obereg, 1);
			TakeNItems(pchar, "Ultimate_potion", 3);
			Log_Info("You have given amulets");
			Log_Info("You have received three versatile potions");
			PlaySound("interface\important_item.wav");
			dialog.text = "Pegue estas poções. Lembre-se, você deve beber uma imediatamente depois que Kukulcan te cuspir, senão vai morrer ou ficar gravemente doente. E lembre-se também de não ir ao porão onde os rostos-pálidos guardam seus suprimentos. Existe outra forma de sair do navio. Na verdade, existem duas formas. Encontre a mulher de vermelho na primeira noite, isso é muito importante. É tudo o que posso te dizer.";
			link.l1 = "Vou me lembrar disso, irmão.";
			link.l1.go = "SnakeEye_potion_2";
		break;
		
		case "SnakeEye_potion_2":
			dialog.text = "Então vá. Toque em Kukulcan à meia-noite e ele vai te devorar. Vou chamar os espíritos para te guiar.";
			link.l1 = "Obrigada, Olho de Cobra. Não se preocupe comigo, tudo vai ficar bem. Nós vamos nos encontrar de novo!";
			link.l1.go = "SnakeEye_potion_3";
		break;
		
		case "SnakeEye_potion_3":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			pchar.questTemp.Saga.BaronReturn = "first_teleport";
			pchar.questTemp.Dolly = true; // телепорты работают!
			LAi_LocationDisableOfficersGen("Pearl_jungle_03", true); // не пускать офицеров в локу телепорта
			DeleteAttribute(npchar, "quest.amulet");
			AddQuestRecord("BaronReturn", "4");
			sld = characterFromId("Danielle");
			sld.quest.talk = "teleport";
			pchar.quest.BaronReturn_out1.win_condition.l1 = "ExitFromLocation";
			pchar.quest.BaronReturn_out1.win_condition.l1.location = pchar.location;
			pchar.quest.BaronReturn_out1.function = "Saga_DannyTalk";
			QuestPointerToLoc("Pearl_Jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("Pearl_Jungle_03", "camera", "dolly");
		break;
		
		// пришёл из LSC
		case "LSC_hello":
			dialog.text = "Fico feliz em te ver, meu amigo. Como você conseguiu voltar do cemitério de navios?";
			link.l1 = "Eu encontrei a estátua de Kukulcan lá, exatamente como você me disse. O garoto branco me ajudou – Ole Christiansen. A estátua estava afundada no mar, mas consegui alcançá-la. Ela me teleportou para uma aldeia indígena na Dominica.";
			link.l1.go = "LSC_hello_1";
			npchar.quest.LSC_hello = "true";
		break;
		
		case "LSC_hello_1":
			dialog.text = "Monkitekuvri te encontrou lá?";
			link.l1 = "Hm. Monkitekuvri? Quem é esse?";
			link.l1.go = "LSC_hello_2";
		break;
		
		case "LSC_hello_2":
			dialog.text = "Ele é o chefe da aldeia.";
			link.l1 = "Eu não perguntei o nome dele. Talvez fosse Monkitekuvri, talvez não.";
			link.l1.go = "LSC_hello_3";
		break;
		
		case "LSC_hello_3":
			dialog.text = "Ele estava usando um cocar pomposo feito de penas de pássaro na cabeça?";
			link.l1 = "Sim, ele tinha. Muitas penas... Parece que ele depenou todos os papagaios da floresta.";
			link.l1.go = "LSC_hello_4";
		break;
		
		case "LSC_hello_4":
			dialog.text = "Ele se chama Monkitekuvri. Essas não são penas de papagaio, mas sim de águia. Esse cocar é meu. Eu dei para Monkitekuvri quando Kukulcan me cuspiu de volta. Depois me levaram para outra estátua...";
			link.l1 = "Veja só! Eles também me 'sacrificaram' para Kukulcan! E eu vim parar aqui, perto da primeira estátua.";
			link.l1.go = "LSC_hello_5";
		break;
		
		case "LSC_hello_5":
			dialog.text = "Sim, meu amigo pálido. Minha jornada também terminou aqui.";
			link.l1 = "Os ídolos se teletransportam em círculo... Mas qual é o sentido disso? Tem alguma ideia, Olho de Cobra?";
			link.l1.go = "LSC_hello_6";
		break;
		
		case "LSC_hello_6":
			dialog.text = "Acho que as estátuas não estão funcionando direito. No momento, elas só mudam as pessoas de lugar, mas deveriam levá-las para um só lugar. Tem algo errado com elas.";
			link.l1 = "O que te faz pensar assim?";
			link.l1.go = "LSC_hello_7";
		break;
		
		case "LSC_hello_7":
			dialog.text = "Porque teletransportar em círculo não faz sentido. Kukulcan precisa reunir todas as vítimas em um só lugar, não ficar movendo elas de um lado para o outro.";
			link.l1 = "E onde seria esse lugar?";
			link.l1.go = "LSC_hello_8";
		break;
		
		case "LSC_hello_8":
			dialog.text = "Esse é um grande segredo, irmão branco, até mesmo para mim.";
			link.l1 = "Entendi. Tudo bem, que se danem os ídolos. Não chego mais perto deles. Já encontrei o capitão acorrentado, não preciso mais passar pelos portais.";
			link.l1.go = "LSC_hello_9";
			AddQuestRecord("BaronReturn", "12");
		break;
		
		case "LSC_hello_9":
			dialog.text = "Quando você esteve no cemitério de navios. Você encontrou meu pandeiro lá?";
			if (CheckCharacterItem(pchar, "buben"))
			{
				link.l1 = "Acho que sim. Dá uma olhada.";
				link.l1.go = "LSC_buben";
			}
			else
			{
				link.l1 = "Não. Infelizmente, ainda não encontrei. Mas eu sei onde fica a ilha e posso chegar lá. Vou procurar pelo seu pandeiro.";
				link.l1.go = "LSC_hello_10";
			}
		break;
		
		case "LSC_hello_10":
			dialog.text = "Procure por ele, meu amigo pálido. Eu te peço, por favor. Sem meu pandeiro, não consigo ouvir bem os espíritos.";
			link.l1 = "Está certo, Olho de Cobra. Até mais!";
			link.l1.go = "exit";
		break;
		
		case "LSC_buben":
			RemoveItems(pchar, "buben", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Esse é o meu tamborim. Obrigado, meu amigo pálido. Posso retribuir. Ofereço a você esta arma, que o seu povo ainda vai demorar muito para ter. Esta arma é a arma dos rostos-pálidos do meu tempo.";
			link.l1 = "Interessante! Mostre para mim, meu amigo pele-vermelha...";
			link.l1.go = "LSC_buben_1";
		break;
		
		case "LSC_buben_1":
			GiveItem2Character(pchar, "pistol7");
			Log_Info("You have received a Colt revolver");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "shotgun_cartridge", 3);
			TakeNItems(pchar, "GunCap_colt", 3);
			dialog.text = "Pegue. Só restam três cargas, o resto eu já usei. Mas talvez você consiga aprender a fazer mais cargas para ele. Perdi algumas dezenas de peças para cargas no cemitério de navios, você pode encontrá-las lá.";
			link.l1 = "Opa! Isso é uma pistola! Nunca vi nada assim antes... que máquina curiosa. Tem um mecanismo giratório... cinco tiros! Interessante!";
			link.l1.go = "LSC_buben_2";
		break;
		
		case "LSC_buben_2":
			dialog.text = "Isso se chama revólver Colt. Não existe outra pistola como essa na sua época. É fácil de usar, basta armar o cão e puxar o gatilho. Atira muito bem.";
			link.l1 = "Obrigado! Obrigado, Olho de Cobra! Isso vai ser uma bela surpresa para meus inimigos... Pena que só tem três cargas...";
			link.l1.go = "LSC_buben_3";
		break;
		
		case "LSC_buben_3":
			dialog.text = "Tente aprender a fazer cargas para um revólver Colt. Assim você será um grande guerreiro do seu tempo. Ah, meu irmão pálido, esqueci de pedir para você procurar meu cachimbo no cemitério de navios. Era um cachimbo muito bonito.";
			if (CheckCharacterItem(pchar, "smoking_tube"))
			{
				link.l1 = "Ha! E eu estava me perguntando de quem poderia ser esse cachimbo pintado. Dá uma olhada.";
				link.l1.go = "LSC_tube";
			}
			else
			{
				link.l1 = "Certo. Vou procurar seu cachimbo também. Até mais!";
				link.l1.go = "exit";
			}
			npchar.quest.LSC_tube = "true";
		break;
		
		case "LSC_tube":
			RemoveItems(pchar, "smoking_tube", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Este é o meu cachimbo, irmão. Fico feliz que você o tenha encontrado. E posso lhe dar outro presente por isso. Este é um livro engenhoso dos rostos-pálidos do meu tempo. Não consigo entendê-lo. Tente encontrar um homem inteligente que possa ler e compreender este livro.";
			link.l1 = "Obrigado, Olho de Cobra. Acho que conheço alguém que vai se interessar por isso.";
			link.l1.go = "LSC_tube_1";
		break;
		
		case "LSC_tube_1":
			GiveItem2Character(pchar, "chemistry");
			Log_Info("You have received a Lavoisier's chemistry textbook");
			PlaySound("interface\important_item.wav");
			dialog.text = "Entregue a ele, irmão branco. Este livro guarda grandes segredos da sabedoria dos rostos-pálidos.";
			link.l1 = "Ótimo. Até mais, Olho de Cobra!";
			link.l1.go = "exit";
		break;
		
		// лечение Натаниэля
		case "Saga_nathaniel":
			dialog.text = "Estou ouvindo você, irmão de rosto pálido.";
			link.l1 = "Eu trouxe o capitão acorrentado, que eu procurava no cemitério de navios, comigo. Ele está muito doente. Eu sei que só você pode curá-lo...";
			link.l1.go = "Saga_nathaniel_1";
		break;
		
		case "Saga_nathaniel_1":
			dialog.text = "Kukulcan consumiu a saúde dele. Acho que posso ajudá-lo a se curar. Mas vai levar pelo menos uma lua cheia. Kukulcan devorou o capitão há muito tempo, e a doença se espalhou fundo dentro dele.";
			link.l1 = "Por favor, cure ele, xamã! Eu trago o que você precisar!";
			link.l1.go = "Saga_nathaniel_2";
		break;
		
		case "Saga_nathaniel_2":
			dialog.text = "Eu vou tentar, irmão branco. Você não precisa me trazer nada. Eu tenho tudo. O tempo fortalece a doença, mas um capitão acorrentado vai estar saudável de novo em uma lua.";
			link.l1 = "Obrigado, meu irmão de pele vermelha. Mais uma vez, você salvou minha vida.";
			link.l1.go = "Saga_nathaniel_3";
		break;
		
		case "Saga_nathaniel_3":
			dialog.text = "Deixe o capitão acorrentado na minha cabana, irmão branco, e siga sem preocupação. Leve a esposa dele também, ninguém verá meus rituais.";
			link.l1 = "Certo, Olho de Cobra. Vou levar a Danielle comigo. Até mais!";
			link.l1.go = "Saga_nathaniel_4";
		break;
		
		case "Saga_nathaniel_4":
			DialogExit();
			pchar.questTemp.Saga.BaronReturn = "treatment";
			sld = characterFromId("Nathaniel");
			RemovePassenger(Pchar, sld);
			LAi_SetStayType(sld);
			sld.location = "none";
			pchar.quest.Saga_NatanTreatment1.win_condition.l1 = "ExitFromLocation";
			pchar.quest.Saga_NatanTreatment1.win_condition.l1.location = pchar.location;
			pchar.quest.Saga_NatanTreatment1.function = "Saga_NatanTreatment";
		break;
		
		case "calendar":
			dialog.text = "Estou ouvindo, meu amigo.";
			link.l1 = "Lembra da nossa conversa sobre as estátuas de Kukulcan? Você disse que 'elas deveriam levar as pessoas a um lugar especial'.";
			link.l1.go = "calendar_1";
		break;
		
		case "calendar_1":
			dialog.text = "Eu me lembro, capitão branco.";
			link.l1 = "Eu sei para onde aquelas estátuas devem ter levado as pessoas que foram devoradas por Kukulcan.";
			link.l1.go = "calendar_2";
		break;
		
		case "calendar_2":
			dialog.text = "Onde?";
			link.l1 = "Para a antiga cidade maia de Tayasal. Ela fica no coração das selvas de Main.";
			link.l1.go = "calendar_3";
		break;
		
		case "calendar_3":
			dialog.text = "Muito interessante. Como você sabe disso?";
			link.l1 = "É uma longa história, Olho de Cobra. Eu entendo como você veio parar aqui também. Você ainda nem nasceu, não é?";
			link.l1.go = "calendar_4";
		break;
		
		case "calendar_4":
			dialog.text = "Nem meu pai nasceu no seu tempo. Mas eu vivo no seu tempo, e isso é um grande mistério.";
			link.l1 = "Na verdade, isso tem explicação. Um sacerdote Itza chamado Kanek, que vive em Tayasal, invocou Kukulcan para nascer como mortal neste mundo e absorver a sabedoria da raça branca. Ele também criou um buraco no tempo que trouxe alguns homens do futuro para o nosso tempo...";
			link.l1.go = "calendar_5";
		break;
		
		case "calendar_5":
			dialog.text = "Deixar Kukulcan absorver a sabedoria das pessoas do futuro?";
			link.l1 = "Sim. E Kukulcan planeja voltar ao passado para entregar o conhecimento ao povo maia que morreu há muito tempo. A história será mudada, e os maias vão dominar a América e talvez até mais...";
			link.l1.go = "calendar_6";
		break;
		
		case "calendar_6":
			dialog.text = "";
			link.l1 = "Mas algo aconteceu com os portais e eles começaram a teleportar as pessoas em círculos, em vez de levá-las para Tayasal. E é por isso que estou aqui, preciso do seu conselho, Olho de Cobra.";
			link.l1.go = "calendar_7";
		break;
		
		case "calendar_7":
			dialog.text = "Por que eu, capitão branco?";
			link.l1 = "Porque você foi devorado por Kukulcan. E porque a estátua de Kukulcan perto da sua aldeia tem uma marca estranha neste mapa, que está fortemente ligada aos rituais de Kanek.";
			link.l1.go = "calendar_8";
		break;
		
		case "calendar_8":
			dialog.text = "Pode me mostrar esse mapa?";
			link.l1 = "Aqui, dê uma olhada...";
			link.l1.go = "calendar_9";
		break;
		
		case "calendar_9":
			RemoveItems(pchar, "skinmap", 1);
			dialog.text = "(olhando) Este sinal redondo, certo? E o que isso significa?";
			link.l1 = "Eu não sei, xamã. Só sei que uma das três estátuas de Kukulcán tem essa marca. E a estátua com a marca é a sua. Concluo que a sua estátua é especial. Alguma ideia?";
			link.l1.go = "calendar_10";
		break;
		
		case "calendar_10":
			dialog.text = "Me dê até amanhã de manhã, irmão branco. Deixe comigo esse mapa de couro. Preciso consultar os espíritos. Volte amanhã.";
			link.l1 = "Certo, irmão pele-vermelha. Estarei aqui amanhã. Obrigado por me ajudar.";
			link.l1.go = "calendar_11";
		break;
		
		case "calendar_11":
			DialogExit();
			SetFunctionTimerCondition("Tieyasal_CalendarThink", 0, 0, 1, false);
			pchar.questTemp.Tieyasal = "calendar_think";
			NextDiag.CurrentNode = "calendar_wait";
		break;
		
		case "calendar_wait":
			dialog.text = "Volte depois, irmão branco. Não me incomode agora.";
			link.l1 = "Claro, xamã...";
			link.l1.go = "exit";
			NextDiag.TempNode = "calendar_wait";
		break;
		
		case "calendar_12":
			dialog.text = "Tenho algo para te contar, irmão branco.";
			link.l1 = "Você encontrou alguma coisa? Ou tem algum palpite?";
			link.l1.go = "calendar_13";
		break;
		
		case "calendar_13":
			dialog.text = "Os espíritos dos ancestrais me deram uma visão e eu fui até Kukulcan com o mapa. Procurei e encontrei. Deve ser isso que você está procurando, irmão branco.";
			link.l1 = "O que você encontrou?";
			link.l1.go = "calendar_14";
		break;
		
		case "calendar_14":
			dialog.text = "A estátua de Kukulcan tem duas presilhas de ferro e uma cavidade. A cavidade é redonda e lisa. Ela está voltada para o objeto redondo e plano do seu mapa de couro.";
			link.l1 = "O que foi?";
			link.l1.go = "calendar_15";
		break;
		
		case "calendar_15":
			dialog.text = "Eu não sei. Só sei que é redondo, achatado, mais ou menos do tamanho de uma pequena abóbora e talvez tão grosso quanto um dedo. Você pode ir ver o encaixe e as presilhas por si mesmo. A presilha precisa segurá-lo.";
			link.l1 = "Você faz alguma ideia? Ou tem algum palpite do que pode ser?";
			link.l1.go = "calendar_16";
		break;
		
		case "calendar_16":
			dialog.text = "A pedra carrega vestígios de fogo. Eu sei o que aconteceu com ela. O fogo do céu a atingiu.";
			link.l1 = "Relâmpago? Foi atingido por um relâmpago?";
			link.l1.go = "calendar_17";
		break;
		
		case "calendar_17":
			dialog.text = "Tenho certeza disso. Perguntei aos Miskitos sobre esse ídolo. Um guerreiro disse que, há muito tempo, algumas coisas bonitas e pintadas foram vistas na estátua. Muito parecidas com pedras. Ele me contou que eram pedras vermelhas muito bonitas. Um homem branco da vila dos brancos as comprou.";
			link.l1 = "Hum. Pelo que entendi, parece que um raio atingiu esse tal 'algo' redondo, quebrou em pedaços, e depois esses pedaços foram vendidos para algum homem branco?";
			link.l1.go = "calendar_18";
		break;
		
		case "calendar_18":
			dialog.text = "Parece que sim.";
			link.l1 = "E quem era aquele homem branco? O seu guerreiro te contou?";
			link.l1.go = "calendar_19";
		break;
		
		case "calendar_19":
			dialog.text = "Ele me contou. Ele era um grande amigo dos Miskito e mora na vila de Blueweld. O nome dele é Forest Devil. Eu o conheço, você deve conhecê-lo também.";
			link.l1 = "Jan Svenson? Espere um instante... pedras pintadas de vermelho, é isso? Parece que acabei de ter muita sorte. Veja só, xamã, olhe para estas pedras vermelhas que eu tenho! O Diabo da Floresta me deu elas.";
			link.l1.go = "calendar_20";
		break;
		
		case "calendar_20":
			Log_Info("You have given ornamental pattern fragments");
			RemoveItems(pchar, "splinter_js", 1);
			RemoveItems(pchar, "splinter_nh", 1);
			RemoveItems(pchar, "splinter_mt", 1);
			RemoveItems(pchar, "splinter_zm", 1);
			RemoveItems(pchar, "splinter_jb", 1);
			dialog.text = "Devem ser eles. Cinco pedras. Dá uma olhada, irmão branco. Se você colocar assim... (juntando-as)";
			link.l1 = "...";
			link.l1.go = "calendar_21";
		break;
		
		case "calendar_21":
			dialog.text = "... então temos um objeto redondo. Olhe! Eles combinam. Antes era um só objeto.";
			link.l1 = "Droga! E essas coisas ficaram no meu bolso por tanto tempo... Escuta, xamã, se eu colocar os fragmentos no encaixe...";
			link.l1.go = "calendar_22";
		break;
		
		case "calendar_22":
			dialog.text = "Kukulcan vai cuspir a vítima na velha cidade indígena, como você disse.";
			link.l1 = "Seria ótimo! Eu preciso chegar lá! Você acha que o ornamento ainda vai funcionar mesmo estando quebrado em pedaços?";
			link.l1.go = "calendar_23";
		break;
		
		case "calendar_23":
			dialog.text = "Acho que precisamos juntar eles e então colocar o ornamento no encaixe.";
			link.l1 = "Juntar eles? Mas como podemos reuni-los de novo?";
			link.l1.go = "calendar_24";
		break;
		
		case "calendar_24":
			dialog.text = "Deixe isso comigo e com os espíritos dos ancestrais, irmão branco. Não são pedras comuns. É um item milagroso. Volte em três noites, irmão branco. Vou invocar os espíritos, a sabedoria e a habilidade dos vivos, e tentarei unir os fragmentos.";
			link.l1 = "Incrível... Como eu poderia te agradecer, Olho de Cobra?";
			link.l1.go = "calendar_25";
		break;
		
		case "calendar_25":
			dialog.text = "Me agradeça depois, irmão branco. Vá agora. Volte em três noites.";
			link.l1 = "Certo. Espero que você consiga...";
			link.l1.go = "calendar_26";
		break;
		
		case "calendar_26":
			DialogExit();
			SetFunctionTimerCondition("Tieyasal_CalendarDone", 0, 0, 3, false);
			NextDiag.CurrentNode = "calendar_wait";
		break;
		
		case "calendar_28":
			dialog.text = "Posso te fazer feliz, irmão branco.";
			link.l1 = "Você conseguiu reunir os fragmentos?";
			link.l1.go = "calendar_29";
		break;
		
		case "calendar_29":
			dialog.text = "Sim. Não foi fácil e ainda ficaram marcas no calendário, mas agora está tudo concluído.";
			link.l1 = "Calendário? Por que você chama assim?";
			link.l1.go = "calendar_30";
		break;
		
		case "calendar_30":
			dialog.text = "Porque esse objeto redondo é um calendário. Eu o estudei com atenção. Ele marca o tempo. Os índios da cidade antiga contam noites, luas, anos e eras.";
			link.l1 = "Incrível... Mas, considerando do que os sacerdotes maias são capazes, a criação deste calendário nem parece tão extraordinária assim.";
			link.l1.go = "calendar_31";
		break;
		
		case "calendar_31":
			GiveItem2Character(pchar, "calendar_maya");
			sld = ItemsFromID("calendar_maya");
			sld.shown = "0";
			Log_Info("You have received a Maya calendar");
			dialog.text = "Pegue, capitão branco. Coloque isso no nicho da estátua. Talvez assim ela o cuspa para fora na cidade dos índios.";
			link.l1 = "Como posso te agradecer, Olho de Cobra?";
			link.l1.go = "calendar_32";
		break;
		
		case "calendar_32":
			dialog.text = "Diga 'Obrigado'. Os deuses guiam você no seu caminho, mesmo que você não perceba. Os brancos chamam isso de destino. Kukulcan te chamou, os deuses te guiam. Agora vá. Faça o que precisa ser feito e deixe que bons espíritos te conduzam.";
			link.l1 = "Obrigado, Olho de Cobra! Nunca vou te esquecer.";
			link.l1.go = "calendar_33";
		break;
		
		case "calendar_33":
			TakeNItems(pchar, "Ultimate_potion", 4);
			Log_Info("You have received four versatile potions");
			PlaySound("interface\important_item.wav");
			dialog.text = "Espere. Quase esquecemos o mais importante. Kukulcan devora homens e consome suas vidas. Preparei poções para você. Poções Comanche. Vou entregá-las a você. Fiz quatro frascos, assim você pode levar três companheiros leais e corajosos com você.";
			link.l1 = "Você fez tanto por mim, meu irmão de sangue...";
			link.l1.go = "calendar_34";
		break;
		
		case "calendar_34":
			dialog.text = "Irmão não é apenas uma palavra para os índios da tribo Comanche. Quando você voltar da cidade de Kukulcan, visite nossa aldeia. Vamos preparar bastante saraiaka. Vou ficar feliz em te ver.";
			link.l1 = "Claro, meu irmão de pele vermelha! Com certeza vou te visitar!";
			link.l1.go = "calendar_35";
		break;
		
		case "calendar_35":
			DialogExit();
			pchar.questTemp.Tieyasal = "calendar_place";
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Tieyasal", "17");
			sld = ItemsFromID("skinmap");
			sld.price = 100; // кожаную карту можно выкладывать 270912 
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
