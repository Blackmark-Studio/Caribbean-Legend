// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Que perguntas você tem?","Como posso ajudar você, "+GetAddress_Form(NPChar)+"?"),"Você tentou me fazer uma pergunta há pouco tempo, "+GetAddress_Form(NPChar)+"...","No decorrer deste dia inteiro, esta é a terceira vez que você levanta alguma questão...","Mais perguntas, imagino?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia...","Não tenho nada para conversar no momento."),"Ah, onde foi parar minha memória...","Sim, realmente é a terceira vez...","Não, que perguntas?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			/* //--> Jason, Бремя гасконца
			if (!CheckAttribute(npchar, "quest.Rum") && CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.questTemp.Sharlie == "ship" && makeint(environment.time) > 5.0 && makeint(environment.time) < 19.0)
			{
				link.l1 = "Monsieur, estou procurando trabalho. Você tem algum serviço?";
                link.l1.go = "Sharlie_rum";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Rum") && pchar.questTemp.Sharlie.Rum == "regard")
			{
				link.l1 = "Cumpri sua tarefa. O bote com o rum foi entregue na Baía de Le François e passado para o seu pessoal.";
                link.l1.go = "Sharlie_rum_5";
			}	
			//<-- Бремя гасконца */
			
			//Jason, Португалец
			if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "ToMartinique" && !CheckAttribute(npchar, "quest.Portugal"))
			{
				link.l1 = "Preciso alugar um dos seus quartos por dois ou três dias. Tenho um homem a bordo que está ferido. Ele precisa descansar e se recuperar.";
				link.l1.go = "Portugal";
			}
			if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "MartiniqueGovernorEnd")
			{
				link.l1 = "Me diga, o amigo para quem aluguei um quarto — ele já foi embora? Ele prometeu me esperar, mas o quarto está vazio.";
				link.l1.go = "Portugal_2";
			}
			//Португалец
			// Jason Долго и счастливо
			if (!CheckAttribute(npchar, "quest.LongHappy") && CheckAttribute(PChar, "questTemp.LongHappy.MarryRum") && LongHappy_CheckTavernGoods())
			{
				link.l1 = "Vou organizar uma festa para meus homens. Suponho que você já saiba disso?";
				link.l1.go = "LH_tavern_SP";
			}
			if (CheckAttribute(npchar, "quest.LongHappy.Nomoney") && LongHappy_CheckTavernGoods() && sti(Pchar.money) >= 100000+sti(pchar.questTemp.LongHappy.MarryMoney))
			{
				link.l1 = "Trouxe tudo o que precisamos para a nossa comemoração.";
				link.l1.go = "LH_tavern_SP_3";
			}
		break;
		
		//--> Jason, Бремя гасконца
		case "Sharlie_rum":
			DelLandQuestMark(npchar);
			dialog.text = "Uma tarefa? Hm... Você parece ter um pouco de juízo, garoto. Talvez eu tenha algo pra você\nEsse trabalho pode parecer fácil, mas exige responsabilidade e inteligência. Não posso confiar nesses idiotas pra cuidar dos negócios, eles iam estragar tudo mesmo...";
			link.l1 = "Escuta, você pode me dizer exatamente o que quer que eu faça? Eu juro, não vou te decepcionar, ou pelo menos vou dar o meu melhor.";
			link.l1.go = "Sharlie_rum_1";
		break;
		
		case "Sharlie_rum_1":
			switch(rand(4))
			{
				case 0:
					pchar.questTemp.Sharlie.Rum.Pass = "Old Thomas has grown tired of waiting for the beer";
				break;
				case 1:
					pchar.questTemp.Sharlie.Rum.Pass = "The boards and the oakum will be here in the morning";
				break;
				case 2:
					pchar.questTemp.Sharlie.Rum.Pass = "Don't wait for the south wind";
				break;
				case 3:
					pchar.questTemp.Sharlie.Rum.Pass = "The bay is ready for disembarkation";
				break;
				case 4:
					pchar.questTemp.Sharlie.Rum.Pass = "The camels are going north";
				break;
			}
			dialog.text = "Ótimo. Preciso de alguém para entregar várias caixas de rum jamaicano de primeira à minha taverna. É o seguinte: as tarifas de importação estão acabando com meu lucro e meus melhores clientes estão sedentos, então precisamos agir com inteligência para evitar os fiscais da alfândega. O lugre 'Ghost' vai chegar perto da Martinica esta noite\nEles vão lançar âncora não muito longe da Baía Lamanten. Você precisa encontrar esse navio e embarcar. Vou providenciar um bote e cinco marinheiros, eles vão seguir suas ordens\nQuando estiver a bordo, um homem vai se aproximar de você. Você terá que dizer uma senha para ele: '"+pchar.questTemp.Sharlie.Rum.Pass+"'\nA resposta será 'Por que não tomar um rum, marinheiro?'. Você só terá uma chance, então anote e não erre, senão o acordo está desfeito. Por isso não posso confiar isso àqueles idiotas que vão navegar com você. Repita a senha.";
			link.l1 = "'"+pchar.questTemp.Sharlie.Rum.Pass+"'.";
			link.l1.go = "Sharlie_rum_2";
		break;
		
		case "Sharlie_rum_2":
			dialog.text = "Ótimo. Repita isso para si mesmo mais algumas vezes, ou melhor ainda, anote em algum lugar. Depois que você disser a senha ao capitão do lugre, as caixas de rum serão carregadas no bote, que você precisará levar até a baía do assentamento pirata Le Francois – lá você será bem recebido.\nEssa é toda a tarefa. Você pode ir da Baía de Le Francois até Saint Pierre a pé – o bote ficará na baía. Vou pagar cinco mil peças de oito assim que terminar.";
			link.l1 = "Contrabando parece tanto emocionante quanto lucrativo. Vou fazer como você disse. Onde está o bote?";
			link.l1.go = "Sharlie_rum_3";
			link.l2 = "Então, você está sugerindo que eu me envolva com contrabando? Hm... Olha, não posso arriscar meu nome. Me desculpe, vamos fingir que não ouvi nada.";
			link.l2.go = "Sharlie_rum_exit";
		break;
		
		case "Sharlie_rum_exit":
			dialog.text = "Como quiser, monsieur. Não tenho nenhum outro trabalho.";
			link.l1 = "Entendi. Então, tudo de bom, "+npchar.name+".";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Sharlie.Rum");
			SetCurrentTime(23, 0);
			Sharlie_removeLocks("");
		break;
		
		case "Sharlie_rum_3":
			dialog.text = "O bote estará no cais às sete da noite. A tripulação do bote é experiente, então você deve chegar ao lugre rapidamente. Tudo não deve levar mais de quatro horas – tenho certeza de que estará de volta a Saint Pierre até às onze da noite. Pegue esta luneta, é uma porcaria mas é melhor do que nada. A Praia Lamanten fica na parte norte da ilha, então ao sair do porto, siga direto para o norte. Boa sorte!";
			link.l1 = "Beleza, entendi. Até logo, "+npchar.name+"!";
			link.l1.go = "Sharlie_rum_4";
		break;
		
		case "Sharlie_rum_4":
			DialogExit();
			AddQuestRecord("SharlieB", "1");
			AddQuestUserData("SharlieB", "sPassword", pchar.questTemp.Sharlie.Rum.Pass);
			GiveItem2Character(pchar, "spyglass1"); 
			Log_Info("You've received a spyglass");
			PlaySound("interface\important_item.wav");
			if(CheckAttribute(pchar, "questTemp.Sharlie.FastStart"))
			{
				GiveItem2Character(pchar, "map_martiniqua");
				Log_Info("You have received a map of Martinique");
				RefreshEquippedMaps(GetMainCharacter());
			}
			/* pchar.quest.Sharlie_rum.win_condition.l1 = "location";
			pchar.quest.Sharlie_rum.win_condition.l1.location = "Fortfrance_town"; */
			//pchar.quest.Sharlie_rum.win_condition.l1.locator_group = "rld";
			//pchar.quest.Sharlie_rum.win_condition.l1.locator = "loc0";
			pchar.quest.Sharlie_rum.win_condition.l1 = "HardHour";
			pchar.quest.Sharlie_rum.win_condition.l1.hour = 19.00;
			pchar.quest.Sharlie_rum.function = "Rum_CreateBarkas";
			SetFunctionTimerCondition("Rum_CreateBarkasOver", 0, 0, 1, false);
			pchar.questTemp.Sharlie.Rum = "true";
			npchar.quest.Rum = "true";
			NewGameTip("Open your inventory (F1) and equip the spyglass.");
			pchar.quest.NgtBarkas.win_condition.l1 = "location";
			pchar.quest.NgtBarkas.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.NgtBarkas.win_condition.l2 = "HardHour";
			pchar.quest.NgtBarkas.win_condition.l2.hour = 19.00;
			pchar.quest.NgtBarkas.function = "NgtBarkas";
			AddTimeToCurrent(1,30);
			QuestPointerDelLoc("fortfrance_town", "reload", "reload4_back");
			QuestPointerToLoc("fortfrance_town", "reload", "reload1_back");
		break;
		
		case "Sharlie_rum_5":
			dialog.text = "Maravilha! Eu sabia que podia contar com você. Foi difícil?";
			link.l1 = "Bem, isso depende de como você define difícil...";
			link.l1.go = "Sharlie_rum_6";
		break;
		
		case "Sharlie_rum_6":
			dialog.text = "Bem, aqui está sua recompensa: cinco mil pesos. Pode ficar com a luneta. E também, mais um presentinho—por favor, aceite estas três garrafas de rum. Depois que provar, vai entender por que há tanta procura por ele.";
			link.l1 = "Obrigado! Foi um prazer trabalhar com você! Até logo!";
			link.l1.go = "Sharlie_rum_7";
		break;
		
		case "Sharlie_rum_7":
			DialogExit();
			AddMoneyToCharacter(pchar, 5000);
			TakeNItems(pchar, "potionrum", 3);
			AddQuestRecord("SharlieB", "5");
			CloseQuestHeader("SharlieB");
			DeleteAttribute(pchar, "questTemp.Sharlie.Rum");
			// Rebbebion, новые марки до места назначения
			QuestPointerDelLoc("lefransua_town", "reload", "gate_back");
			QuestPointerDelLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerDelLoc("fortfrance_town", "reload", "reload4_back");
			DelLandQuestMark(npchar);
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Gigolo"))
			{
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1 = "Hour";
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.start.hour = 6.00;
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.finish.hour = 22.00;
				pchar.quest.Sharlie_CreatShipyardMarker.function = "Sharlie_CreatShipyardMarker";
			}
		break;
		//<-- Бремя гасконца
		
		//Португалец
		case "Portugal":
			dialog.text = "Sem problema, tenho um quarto. Por 50 pesos, ele é seu por três dias.";
			if (sti(pchar.money) >= 50)
			{
				link.l1 = "Aqui está.";
				link.l1.go = "Portugal_1";
			}
			else
			{
				link.l1 = "Vou buscar o dinheiro com o tesoureiro e já volto.";
				link.l1.go = "exit";
			}
		break;
		
		case "Portugal_1":
			ref sld;
			DialogExit();
			AddMoneyToCharacter(pchar, -50);
			npchar.quest.Portugal = "true";
			LocatorReloadEnterDisable("Fortfrance_tavern", "reload2_back", false);
			pchar.quest.Portugal_Ill3.over = "yes";
			LocatorReloadEnterDisable("Fortfrance_town", "reload1_back", true);
			LocatorReloadEnterDisable("Fortfrance_town", "reload2_back", true);
			LocatorReloadEnterDisable("Fortfrance_town", "gate_back", true);//закрыть выходы из города
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern_upstairs", "goto", "goto3");
			sld = characterFromId("PortugalDoctor");
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern_upstairs", "goto", "goto1");
			pchar.quest.Portugal_tavernroom.win_condition.l1 = "location";
			pchar.quest.Portugal_tavernroom.win_condition.l1.location = "FortFrance_tavern_upstairs";
			pchar.quest.Portugal_tavernroom.function = "PortugalInTavernRoom";
		break;
		
		case "Portugal_2":
			dialog.text = "Eu não diria que ele se levantou e saiu da sala sozinho, monsieur. Algumas pessoas passaram por aqui ontem. Um deles era um homem alto, magro, de um olho só – claramente um bandido pela aparência, e também tinha um sujeito que falava com a língua presa, parecia um castelhano. Fiquei até surpreso, mas aquele gago me lançou um olhar... igualzinho ao que se dá pra um piolho antes de esmagar. E aí perguntaram do seu amigo... e eu contei. O que mais eu poderia fazer?";
			link.l1 = "Eu sei, "+npchar.name+", você não é nenhum herói, isso mesmo. O que mais você viu? Para onde eles foram?";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			dialog.text = "Isso é tudo... espera, não! Calma, o homem de um olho só falou algo sobre uma carroça. Acho que eles pegaram uma carroça e arrastaram seu amigo até o outro lado da ilha. É só isso, monsieur, eu juro... Eu até chamaria a guarda, mas aquele gago disse que eu tinha uma esposa linda antes de ir embora... Entende? Se descobrirem que contei tudo isso pra você, eles vão...";
			if (pchar.money >= 1000)
			{
				link.l1 = "Não se preocupe, eles não vão ouvir nada de mim além de balas. Você realmente me ajudou, obrigado. Aqui, pegue 1000 pesos como recompensa.";
				link.l1.go = "Portugal_4";
			}
			link.l2 = "Não é grande coisa, mas obrigado mesmo assim. Da próxima vez, chame a guarda e não seja tão covarde.";
			link.l2.go = "Portugal_5";
		break;
		
		case "Portugal_4":
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "Obrigada, monsieur. Posso garantir que seu amigo já está quase recuperado. Ele pelo menos já estava andando sozinho. E aquele outro, o holandês quieto, entrou vindo de fora bem naquela hora, viu toda aquela bagunça e saiu correndo de novo, simplesmente sumiu depois.";
			link.l1 = "Eu diria que ele já partiu no primeiro navio que conseguiu encontrar. Obrigado pela informação, está na hora de eu ir.";
			link.l1.go = "Portugal_6";
		break;
		
		case "Portugal_5":
			dialog.text = "Nem todo homem pode ser um herói com a espada desembainhada, capitão.";
			link.l1 = "Bem... essa é a escolha do homem.";
			link.l1.go = "Portugal_6";
		break;
		
		case "Portugal_6":
			DialogExit();
			sld = characterFromId("Avendel");
			sld.dialog.currentnode = "Avendel_seapatrol_9";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		//Португалец
		
		// Jason Долго и счастливо
		case "LH_tavern_SP":
			npchar.quest.LongHappy = "true";
			dialog.text = "Sim, sua assistente passou por aqui, mas eu disse a ela e vou repetir pra você – estou acostumada com multidões de marinheiros bêbados, mas sei como são suas festas. O que sobrar vai parecer Antuérpia depois que os tercios espanhóis passaram por lá. Vou ficar feliz se as paredes ainda estiverem de pé. Então, se quiser mesmo fazer a multidão brigar, vou precisar de um adiantamento não reembolsável além do que você já trouxe. Caso haja consequências, por assim dizer.";
			link.l1 = "Seu danado! Já bebi com marujos por muitos anos, já estive em todo tipo de... estabelecimento, e sei que com o dinheiro que trouxe, poderíamos reconstruir sua taverna do zero! Está querendo se aproveitar da situação, não é? Muito bem, tenho um casamento para ir e não estou com paciência para essas miudezas – quanto você quer?";
			link.l1.go = "LH_tavern_SP_1";
		break;
		
		case "LH_tavern_SP_1":
			dialog.text = "Mais 100.000 peças de oito devem ser suficientes e não se preocupe – vou cuidar de tudo da melhor forma possível. Seus rapazes vão lembrar dessa festa por muito tempo, pode apostar!";
			if (sti(Pchar.money) >= 100000+sti(pchar.questTemp.LongHappy.MarryMoney))
			{
				link.l1 = "Você realmente precisa se esforçar — é uma ocasião especial, entendeu? E olha, depois da celebração, não venha reclamar comigo, mesmo que sua taverna pegue fogo.";
				link.l1.go = "LH_tavern_SP_4";
			}
			else
			{
				link.l1 = "Já estou me sentindo como se estivesse organizando um casamento real! Espere, já volto.";
				link.l1.go = "LH_tavern_SP_2";
			}
		break;
		
		case "LH_tavern_SP_2":
			DialogExit();
			npchar.quest.LongHappy.Nomoney = "true";
		break;
		
		case "LH_tavern_SP_3":
			dialog.text = "Seus rapazes vão lembrar dessa festa por muito tempo, pode apostar!";
			link.l1 = "Você tem que se esforçar de verdade – é uma ocasião especial, entendeu. E não venha chorar pra mim se meus rapazes, sem querer, botarem fogo na sua taverna.";
			link.l1.go = "LH_tavern_SP_4";
		break;
		
		case "LH_tavern_SP_4":
			DialogExit();
			RemoveCharacterGoods(pchar, GOOD_RUM, sti(pchar.questTemp.LongHappy.MarryRum));
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.LongHappy.MarryMoney));
			AddMoneyToCharacter(pchar, -100000);
			DeleteAttribute(npchar, "quest.LongHappy.Nomoney");
			pchar.questTemp.LongHappy.DrinkReady = "true";
			pchar.questTemp.LongHappy.MarrySP = "true";
			DeleteAttribute(pchar, "questTemp.LongHappy.MarryMoney");
			DeleteAttribute(pchar, "questTemp.LongHappy.MarryRum");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
