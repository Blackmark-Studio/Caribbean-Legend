// BOAL новый диалог офицера и компаньона 21/06/06
void ProcessDialogEvent()
{
	ref NPChar, d;
	aref Link, Diag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);
	
	ref    	sld, rItm, rItem;
	string 	attr, attrLoc, sGun, sBullet, attrL, sAttr;
	int    	iTemp, iTax, iFortValue, i;
	aref 	rType;
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	if (findsubstr(sAttr, "SetMusketBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetMusketBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetMusketBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
        case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = RandPhraseSimple("Heh, capitão, metade da guarnição está atrás de você neste momento. Com certeza não é a melhor hora para entrar na sua tripulação!","E lutar para chegar até o navio? Não, Capitão, deixa pra outra hora...");
				link.l1 = RandPhraseSimple("Como quiser...","Na verdade, eu não ia te contratar."); 
				link.l1.go = "exit";
				break;
			}
			Diag.TempNode = "OnceAgain";
			dialog.text = "Precisa de um oficial, capitão?";
			if (FindFreeRandomOfficer() > 0)
			{
    			Link.l1 = "Um oficial? E no que você é bom?";
    			Link.l1.go = "Node_2";
			}
			Link.l2 = "Não, já tenho um conjunto completo.";
			Link.l2.go = "Exit";			
		break;
		
		case "CitizenNotBlade":
			dialog.text = "Capitão, o que está fazendo? Guarde sua arma antes que cause um grande problema!";
			link.l1 = LinkRandPhrase("Certo.","Certo.","Não se preocupe, estou guardando isso...");
			link.l1.go = "exit";
		break;
		
		case "hired":
			Diag.TempNode = "Hired";
			// только наняли -->
			if (IsCompanion(NPChar))
			{
				Dialog.text = "Hoje, finalmente vamos zarpar!";
				link.l2 = "É... ainda bem.";
				link.l2.go = "Exit";
				break;
			}
			if (Npchar.location.group == "sit" && !isShipInside(pchar.location))
			{
				dialog.text = "Vou só terminar minha bebida, capitão, e depois vou para o navio. Não se preocupe – estarei lá a tempo.";
				Link.l1 = "Certo. Se você se atrasar, vai esfregar o convés!";
				Link.l1.go = "Exit";
				break;
			}
			// только наняли <--
   			dialog.text = "O que você quer, capitão?";
			// эпилог -->
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && !CheckAttribute(npchar, "quest.SharlieEpilog_FarewellOfficers") && npchar.id == "Folke")
			{
				dialog.text = "Não gosto desse tempo, capitão. Notei os primeiros sinais de tempestade.";
				Link.l1 = ""+npchar.name+", preciso conversar com você. Vou direto ao ponto: estou partindo para a Europa por tempo indeterminado. Deixar você aqui esperando meu retorno seria tolice, mas também não posso levar todos comigo. Estou indo como passageiro, em outro navio.";
				Link.l1.go = "SharlieEpilog_Folke_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && !CheckAttribute(npchar, "quest.SharlieEpilog_FarewellOfficers") && npchar.id == "Duran")
			{
				dialog.text = "(boceja) Que tédio...";
				Link.l1 = "Faz tempo que você não se diverte, né, "+npchar.name+"?";
				Link.l1.go = "SharlieEpilog_Duran_1";
				break;
			}
			// эпилог <--
			// диалог компаньона на корабле.
			if (CheckAttribute(NPChar, "IsCompanionClone"))
			{
				Link.l2 = "Preciso te dar várias ordens.";
				Link.l2.go = "Companion_Tasks";
				break;
			}
			
			// на Тайясаль
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l66 = ""+npchar.name+", estou indo para a antiga cidade indígena de Tayasal. Vai ser uma jornada perigosa e fora do comum – através de um ídolo de teletransporte. Você vem comigo?";
				if(npchar.id == "Folke")
				{
					Link.l66 = ""+npchar.name+", tenho um pedido sério pra você – é coisa grande, perigosa de verdade, mas pode render uma fortuna. Preciso de alguém de confiança pra uma missão numa antiga cidade indígena. Vai encarar?";
				}
				if(npchar.id == "Duran")
				{
					Link.l66 = "Claude, uma vez você reclamou que mercenários são mal pagos.";
				}
				Link.l66.go = "tieyasal";
			}
			
			if (isOfficer(Npchar)) // проверка для кампуса, где слотовые офы
			{
				Link.l2 = "Agora ouça minha ordem!";
				Link.l2.go = "stay_follow";
			}

           		// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l8 = "Me dê um relatório completo sobre o navio, "+GetStrSmallRegister(XI_ConvertString("tesoureiro"))+".";
			    Link.l8.go = "QMASTER_1";
			        
			    // Warship. Автозакупка товара
			    if(!CheckAttribute(PChar, "TransferGoods.Enable"))
			    {
				    Link.l11 = "Quero que você compre mercadorias enquanto estivermos na colônia.";
				    Link.l11.go = "TransferGoodsEnable";
			    }
			    else
			    {
				    Link.l11 = "Sabe, não precisamos mais comprar mercadorias nas colônias.";
				    Link.l11.go = "TransferGoodsDisable";
			    }
			}
			
			if (pchar.location != "My_Campus") // patch-5
			{
			Link.l4 = "Oficial, seus serviços não são mais necessários.";
			Link.l4.go = "AsYouWish";
			}
			
			
			// по тек локации определим можно ли тут приказать  -->
			if(IsEntity(&loadedLocation))
			{
				if(CheckAttribute(loadedLocation, "fastreload"))
				{
					iTemp = FindColony(loadedLocation.fastreload);
					if(iTemp != -1)
					{
						sld = GetColonyByIndex(iTemp);
						if(sti(sld.HeroOwn) == true && !CheckAttribute(sld, "OfficerIdx"))
						{
							NPChar.ColonyIdx = iTemp;
							Link.l7 = "Eu te nomeio delegado desta cidade!";
							Link.l7.go = "Gover_Hire";
						}
					}
				}
			}
			
			Link.l9 = "Nada. Fique à vontade!";
			Link.l9.go = "Exit";
		break;
		
		// Тайясаль
		case "tieyasal":
			if(npchar.id == "Folke")
			{
				dialog.text = "Maldição, Capitão! Achei que você ia se livrar de mim na primeira oportunidade, mas você me surpreendeu, como sempre. Claro que estou com você, e obrigado por dar a este idiota a verdadeira vida de lobo do mar!";
				Link.l1 = "Muito bem, "+npchar.name+"!";
				Link.l1.go = "folke_tieyasal";
				break;
			}
			if(npchar.id == "Duran")
			{
				dialog.text = "Hã? Eu realmente disse isso?";
				Link.l1 = "Você ouviu. Eu prestei atenção no que disse naquela hora, e agora estou pronto para corrigir essa injustiça.";
				Link.l1.go = "Duran_tieyasal";
				break;
			}
			dialog.text = LinkRandPhrase("Desculpe, capitão, mas não foi pra isso que eu me alistei. Não pense que sou covarde, mas não estou disposto a encarar a morte certa. Ainda não estou cansado de viver – pelo menos por enquanto. Pode me dispensar se quiser.","Capitão, me desculpe, mas - não. O mar, abordagens, cidades inimigas - tudo isso está ótimo, mas não quero me meter com essa feitiçaria indígena. Se minha resposta te incomoda, pode cancelar nosso contrato.","Você quer o impossível, capitão, e sabe disso. Ninguém vai voltar vivo, nem você, então vou recusar. Se considerar minha recusa uma violação dos termos do contrato, pode cancelá-lo.");
			link.l1 = LinkRandPhrase("Eu não te culpo, oficial. Eu entendo perfeitamente.","Uma pena, mas eu entendo você. Por isso te avisei antes.","Eu estava contando com você... Mas entendo a sua posição, oficial.");
			link.l1.go = "tieyasal_1";
		break;
		
		case "Duran_tieyasal":
			dialog.text = "Hein! Vai aumentar meu pagamento, então?";
			Link.l1 = "De jeito nenhum! Estou indo para uma antiga cidade indígena. O trabalho é suicida, mas vai ter ouro lá...";
			Link.l1.go = "Duran_tieyasal_2";
		break;
		
		case "Duran_tieyasal_2":
			dialog.text = "Não estou interessado em ouro. Seria uma honra te ajudar, Capitão, assim como você já me ajudou. Quando partimos?";
			Link.l1 = "Muito bem dito, Claude! Prepare-se totalmente – não vai demorar agora.";
			Link.l1.go = "Duran_tieyasal_3";
		break;
		
		case "Duran_tieyasal_3":
			DialogExit();
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "folke_tieyasal":
			Achievment_Set("ach_CL_108");
			DialogExit();
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "tieyasal_1":
			DialogExit();
			npchar.quest.Tieyasal = "true";
		break;
		
		case "TransferGoodsEnable":
			if(sti(PChar.Ship.Type) == SHIP_NOTUSED)
	        {
				dialog.text = "Capitão, que mercadorias? Primeiro precisamos encontrar um navio!";
				Link.l1 = "Sim, você está certo.";
				Link.l1.go = "Exit";
				Diag.TempNode = "Hired";
				break;
	        }
	        	
			PChar.TransferGoods.Enable = true;
		//	PChar.TransferGoods.TreasurerID = NPChar.id;
			Dialog.text = "Vai ser feito, "+GetSexPhrase("senhor","senhorita")+" capitão!";
			Link.l1 = "À vontade.";
			Link.l1.go = "TransferGoodsEnable_2";
        break;
        	
		case "TransferGoodsEnable_2":
			Diag.CurrentNode = "Hired";
			DialogExit();
			LaunchTransferGoodsScreen(); // Интерфейс автозакупки товаров
		break;
		
		case "TransferGoodsDisable":
			DeleteAttribute(PChar, "TransferGoods.Enable");
			Dialog.text = "Vai ser feito, "+GetSexPhrase("senhor","senhorita")+" capitão!";
			Link.l1 = "À vontade.";
			Link.l1.go = "exit";
			Diag.TempNode = "Hired";
		break;
        
		case "ShowParam_exit":
			Diag.CurrentNode = "OnceAgain";
			NPChar.quest.meeting = true;
			DialogExit();
			
			PChar.SystemInfo.OnlyShowCharacter = true;
            LaunchCharacter(NPChar);
		break;
		
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();			
		break;

		case "exit_hire":
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
			if(CheckAttribute(pchar,"systeminfo.tutorial.Fighter") && Npchar.quest.officertype == "fighter")
			{
				DeleteAttribute(pchar,"systeminfo.tutorial.Fighter");
				LaunchTutorial("Fighter", 1);
			}
		break;

		case "exit_fire":
			//navy -->
			if (CheckAttribute(NPChar, "PGGAi"))
			{
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();			
				break;
			}
			//navy <--
			Diag.TempNode = "Fired";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");

			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;

			DialogExit();			
		break;
		
		// boal 29.05.04 офицер хочет свалить -->
        case "WantToGo":
			if (npchar.id == "Duran" && !CheckAttribute(pchar, "questTemp.SKD_SobytieKlodDuran"))
			{
				SetTimerCondition("SKD_DuranTavern", 0, 0, 30, false);
				pchar.questTemp.SKD_SobytieKlodDuran = true;
			}
			chrDisableReloadToLocation = false;
			Diag.TempNode = "Hired";
			dialog.text = LinkRandPhrase(LinkRandPhrase("Captain, you know, I... Well, I'd like to ask you to relieve me. It's time for me to settle down, get married, and have some children. I still have no home of my own; when I grow old, there will be no one to bring me a glass of water.","Captain, please, let me resign. For all these years I've been wandering all around the world, and I still haven't really seen anything. I just want to live a new life, drop anchor and see the world from a different perspective.","Captain, the naval service is surely a fine thing, there's good profit and adventure, but the time has come for me to think about myself. You know, cast anchor in a quiet harbour, buy a home, have children. Please, let me go."),LinkRandPhrase("Captain, you know, I am truly sorry, but I am fed up with all these duties, watches and discipline. You see, I just want to live a free life, at least for a while, but I realise that you will not be waiting for me, so... Could you discharge me?","Captain, you know... There is a small vessel I can afford, so... I think it's probably time for me to start my own business. Please, could you let me go?","Captain, I was just offered a position at the port. Actually, I've been longing to cast anchor and settle down to married life for quite some time already. Please, allow me to go. I really can't miss such an opportunity."),LinkRandPhrase("Captain, I'm really seasick. The doctors keep telling me it's an idiosyncrasy. Please, for God's sake, let me go, or I'll just jump overboard at some point.","Captain, I think it's time for me to settle down and find myself a quieter place. You know, I'm afraid. Afraid of stray bullets, afraid of dying during a boarding. I pray to the Lord to keep me alive, and when I close my eyes, I see all the innocent souls I've killed. They are begging me to spare them... Please, show some compassion, and let me go.","Captain, my old wounds are aching, and this recent contusion reminds me of itself every single day. Soon you will dismiss me, and who will hire me after that? Please let me go, I'll patch myself up and find a quieter place."));
			Link.l1 = RandPhraseSimple(LinkRandPhrase("Todos acabam indo embora. Tudo bem, você está livre para ir.","Eu entendo seu ponto de vista. Mais cedo ou mais tarde, tudo chega ao fim. Bem, vá então... e não guarde rancor se algum dia te ofendi.","De novo isso? Você escolheu deliberadamente o momento mais inconveniente possível para me deixar, não foi? Tanto faz. Adeus."),LinkRandPhrase("É difícil acreditar no que você está me dizendo... Tudo bem, arrume suas coisas e vá.","Você? Eu não esperava por isso... Depois de tanto tempo lutando lado a lado... Bem, não vou te impedir. Boa sorte.","Você parece sério. Bem, desejo-lhe sorte, e saiba que vou sentir sua falta."));				
			Link.l1.go = "WantToGo_free";
			if (sti(Pchar.money) >= sti(NPChar.rank)*250)
			{
				Link.l2 = LinkRandPhrase("Entendo... Então é assim que é, hein? E eu estava contando com você... Bem, se você já tomou sua decisão, então vamos nos separar. Leve "+sti(NPChar.rank)*250+" pesos pelo seu serviço leal. E não guarde rancor se algum dia te ofendi.","Bem, não guardo rancor nem fico remoendo o passado. Se é isso que você decidiu, então vá. E leve "+sti(NPChar.rank)*250+" pesos para recomeçar, vai ser muito útil.","Entendo... Bem, mais cedo ou mais tarde isso ia acontecer. Vou te dar "+sti(NPChar.rank)*250+" pesos para você acertar sua vida. E cuide da sua saúde também, a vida na marinha é cheia de dificuldades..."); 
				Link.l2.go = "Im_kind_A2_1";
			}
			Link.l3 = LinkRandPhrase("Então é isso que você diz... Você não percebe que, indo embora agora, está simplesmente me apunhalando pelas costas? Eu não posso deixar você ir agora, nem pense nisso.","Isso sim é novidade! Sabe, as pessoas deveriam me avisar dessas coisas com antecedência! Então esqueça sua vida pessoal por um tempo. Quando chegar a hora, eu aviso quando você pode se aposentar.","Sem demissões. Tenho todos sob controle. Não posso liberar todo mundo só por vontade própria. Sirva, enquanto decido se você merece uma folga.");	
			Link.l3.go = "WantToGo_Stay";
		break;
		
		case "Im_kind_A2_1":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*250)));
			ChangeOfficersLoyality("good_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			dialog.text = "Obrigado, capitão! Que generosidade inesperada... Sabe, ainda tenho algumas coisas suas, talvez queira recuperá-las?";
			Link.l1 = "Talvez... Encontrar uma boa lâmina não seja tão fácil hoje em dia.";
			Link.l1.go = "Get_out_А2_chang";
			Link.l2 = "Ah, não se preocupe. Fique com elas como lembrança do seu serviço.";
			Link.l2.go = "WantToGo_free";
		break;
		
		case "WantToGo_Stay":
			dialog.text = RandPhraseSimple("Mas como assim, capitão? Até os escravizados acabam sendo mandados para terra firme. E eu não sou escravo, então posso decidir meu próprio destino!","Capitão, servi você fielmente todo esse tempo. Não mereço o direito de decidir meu próprio destino?");
			Link.l1 = LinkRandPhrase("I see that I cannot keep you as it stands. Alright, how about some financial support? That will never hurt; you can use the money to build yourself a cosy home in a quiet harbour or take care of your health.","Alright, let's put it this way. What sum could possibly make you reconsider your decision?","You're right. But what about a one-time monetary allowance, would that change your mind?");
			Link.l1.go = "WantToGo_Stay_2";
			Link.l2 = PCharRepPhrase(RandPhraseSimple("Ah, não, meu amigo, aí você se engana... Enquanto você perdia tempo nas tavernas atrás de saias e copos, podia decidir por si mesmo, mas no momento em que pisou no meu navio, entregou seu destino nas minhas mãos.","Hmm. Agora, isso sim é uma afirmação séria. Pelo visto, você esqueceu como eu te encontrei, numa taverna fedorenta, sem um tostão no bolso. Não pode nem ver uma moeda de ouro, que já transforma em rum na mesma hora. 'Decida meu destino...' Pfff! Que piada!"),LinkRandPhrase("Enquanto estiver ao meu serviço, sou eu quem toma as decisões. Agora, por favor, volte às suas tarefas antes que me irrite ainda mais!","Hum. Agora, isso é uma declaração séria. Mas você ainda não trabalhou o suficiente para compensar todo o dinheiro que recebeu adiantado. Então, sua atitude pode ser considerada uma tentativa de extorsão, certo?","Ah, entendi... O que dizem mesmo os regulamentos do navio? Aqui, parágrafo dois: 'Quem tentar sair sem permissão será deixado numa praia deserta com um saco de pólvora, um cantil de água, uma pistola e uma única bala.' E então, o que acha dessa ideia?"));	
			Link.l2.go = "WantToGo_Stay_force";
		break;
		
	case "WantToGo_Stay_2":
		dialog.text = LinkRandPhrase("Bem, essa já é outra história. "+sti(NPChar.rank)*500+" pesos na hora, e eu fico com você.","Bem, talvez por "+sti(NPChar.rank)*500+" pesos eu poderia ficar, suponho.","Bem, se você coloca dessa forma, por "+sti(NPChar.rank)*500+" pesos, eu poderia continuar meu serviço.");
		if (sti(Pchar.money) >= sti(NPChar.rank)*500)
		{
			Link.l1 = RandPhraseSimple("Certo, combinado.","Certo. Mas você podia ter pedido menos.","Vejo que você tem um belo apetite! Mas eu te fiz uma promessa, não foi? E vou cumprir minha palavra.");	
			Link.l1.go = "WantToGo_Stay_ForMoney";
		}
		Link.l2 = LinkRandPhrase("Isso é demais. Eu poderia contratar dois oficiais por esse preço. Talvez seja mais simples simplesmente deixar você ir.","Bem, você certamente tem uma opinião elevada de si mesmo. Tudo bem, vou deixar você ir. Mas vai ver por si só, quando estiver livre, que sua vida não vai ser tão tranquila quanto esperava.","Eu não vou pagar tudo isso. Pode ir, mas nem pense em voltar. Eu não perdoo traição.");				
		Link.l2.go = "WantToGo_free";
	break;
	
	case "WantToGo_Stay_force":
		Npchar.loyality = makeint(Npchar.loyality) - 2;
		dialog.text = "Certo, se você coloca dessa forma, eu fico. Mas saiba que, ao fazer isso, estou indo contra a minha própria vontade.";
		Link.l1 = LinkRandPhrase("Muito bem. Volte às suas tarefas, e continuaremos essa conversa depois.","Volte para o navio. E da próxima vez, pense duas vezes antes de pedir aposentadoria.","De fato. Dever é dever, e você não deveria se entregar às suas fantasias tão cedo.");
		Link.l1.go = "exit";
	break;
	
	case "WantToGo_Stay_ForMoney":
		Diag.TempNode = "Hired";
		NPChar.greeting = "Gr_Officer";
		if(NPChar.id == "Duran") NPChar.greeting = "Duran_officer";
		ChangeCharacterComplexReputation(pchar,"authority", 0.2);
		AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
		Npchar.loyality = makeint(Npchar.loyality) + 1;    
		Diag.CurrentNode = Diag.TempNode;
		NPChar.quest.meeting = true;
		DialogExit();
		NPChar.location = "none";
		LAi_SetOfficerType(NPChar);
	break;
	
	case "WantToGo_free":
		//navy -->
		if (CheckAttribute(NPChar, "PGGAi"))
		{	
			pchar.questTemp.FiringOfficerIDX = NPChar.index;
			AddDialogExitQuestFunction("PGG_FireOfficer");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();	
			break;
		}
		//navy <--
		Diag.TempNode = "WantToGo_free_Yet";
		Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
		AddDialogExitQuestFunction("LandEnc_OfficerFired");
		Diag.CurrentNode = Diag.TempNode;
		NPChar.quest.meeting = true;
		DialogExit();
	break;
	
	case "WantToGo_free_Yet":
		Diag.TempNode = "WantToGo_free_Yet";
		dialog.text = LinkRandPhrase("Eu não acredito! Obrigado, Capitão, isso tira um peso enorme das minhas costas.","Obrigada, capitão, por não tentar me impedir. Sabe, eu realmente quero experimentar outras coisas na vida.","Heh, agora vou ter que me acostumar com minha liberdade recém-conquistada. Só agora comecei a perceber o quanto eu estava de saco cheio daquele serviço na frota.");	
		Link.l1 = RandPhraseSimple("Bem, boa sorte pra você.","Você está livre agora. Seu serviço terminou.");
		Link.l1.go = "exit";
	break;
	// boal 29.05.04 офицер хочет свалить <--
		
	// пассажир возмущен игроком и сваливает -->
	case "WantToRemove":
		if (npchar.id == "Duran" && !CheckAttribute(pchar, "questTemp.SKD_SobytieKlodDuran"))
		{
			SetTimerCondition("SKD_DuranTavern", 0, 0, 30, false);
			pchar.questTemp.SKD_SobytieKlodDuran = true;
		}
        chrDisableReloadToLocation = false;
		if (Npchar.alignment == "good")
		{
			dialog.text = RandPhraseSimple(LinkRandPhrase("Capitão, eu não quero ir contra minha consciência e participar de banditismo.","Capitão, não quero mais participar dos seus tumultos. Sou um oficial, não um carniceiro.","Capitão, o seu jeito bandido de fazer negócios torna impossível a minha permanência na sua tripulação."),LinkRandPhrase("Capitão, devo admitir que trabalhar com você foi um erro decepcionante. Não estou disposto a sacrificar minha reputação por dinheiro nenhum.","Capitão, você reuniu no seu navio todos os mais vis criminosos do Novo Mundo. É repugnante para um homem decente sequer olhar para eles. Não quero mais continuar servindo com uma tripulação dessas.","Capitão, você contratou uma tripulação cheia de canalhas, não tem um homem decente pra conversar. Eu detesto esse tipo de serviço."))+" Adeus.";
			Link.l1 = "O quê?! Isto é um navio militar, não um colégio de boas maneiras! Então pode ir para o inferno!";
			Link.l1.go = "exit_fire_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l2 = "Eu sabia que você logo iria embora... esse serviço não é para você. Mas não me acuse de nada. Aqui está "+sti(NPChar.rank)*500+" pesos, vão ser úteis enquanto você procura um trabalho do seu agrado.";
				Link.l2.go = "Im_kind_A2";
			}
			Link.l3 = LinkRandPhrase("Ah, então é essa a música que você está cantando agora. E quanto à sua parte de cada golpe, ela queima nas suas mãos? Ou está pensando em se aposentar num mosteiro para rezar pelo perdão dos seus pecados? Reze por nós também, então! Ha-ha-ha-ha-ha!","Hum. Agora, isso é uma declaração séria. E onde estava sua consciência inocente enquanto a gente assaltava mercadores juntos? Como vai limpar essa culpa? Ou vai nos delatar, pra gente acabar na forca em boa companhia?","Ah, muito bem! Pelo visto, você esqueceu como eu te encontrei, numa taverna fedorenta sem um tostão no bolso. Só pra constar, como oficial, você não vale nem um vintém de latão. Você não vale nada!");
			Link.l3.go = "WantToGo_stop";
		}
		else
		{
            dialog.text = RandPhraseSimple(LinkRandPhrase("Capitão, eu realmente não gosto dos seus joguinhos de nobre e não vou abandonar meus hábitos só para te agradar. Adeus.","Capitão, não posso mais continuar ao seu serviço. Já perdi tempo demais. Se eu fosse apenas um corsário, já teria feito uma fortuna. Estou indo embora.","Capitão, seus homens me dão nojo. Não há um só homem decente entre eles, só uns almofadinhas, nenhum digno de dividir uma bebida comigo. Estou indo embora."),LinkRandPhrase("Capitão, sou um oficial veterano, e seu navio parece mais uma barcaça de carga. Não gosto desse tipo de serviço. Adeus.","Capitão, sua tripulação inteira é cheia de frescura, não tem um só homem com quem beber ou conversar. Tenho verdadeira aversão a esse tipo de serviço. Adeus.","Capitão, eu achava que servia sob as ordens de um verdadeiro corsário, mas tudo o que fazemos é caridade! Não quero continuar perdendo meu tempo. Estou fora."));
			Link.l1 = RandPhraseSimple("Entendo. Com essa sua atitude, isso ia acontecer mais cedo ou mais tarde. Tudo bem, não vou te segurar.","Sua declaração não foi nenhuma surpresa. Para ser sincero, já estou insatisfeito com sua atitude faz tempo.")+" Boa sorte.";
			Link.l1.go = "exit_fire_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l2 = "Eu sabia que você logo iria embora... esse serviço não é pra você. Mas não me acuse de nada. Aqui estão "+sti(NPChar.rank)*500+" pesos, eles vão ser úteis enquanto você procura um novo emprego.";
				Link.l2.go = "Im_kind_A2";
			}
			Link.l3 = RandPhraseSimple("Hum. Agora, isso é uma declaração séria. Mas você ainda não trabalhou o suficiente para compensar todo o dinheiro que recebeu adiantado. Então, sua atitude pode ser considerada uma tentativa de extorsão, certo?","Ah, entendi... O que dizem os regulamentos do navio? Aqui, parágrafo dois: 'Quem tentar partir sem permissão será deixado numa praia deserta com um saco de pólvora, um cantil de água, uma pistola e uma única bala.' E então, o que acha disso?");
			Link.l3.go = "WantToGo_stop";
		}
		break;
		
		case "WantToGo_stop":
			if (Npchar.alignment == "good")
			{
				dialog.text = LinkRandPhrase("Nem pense em me insultar! Trabalho por dinheiro, mas ainda tenho o direito de escolher um serviço que me agrade!","Sou um homem livre! E tenho o direito de aceitar um novo trabalho sempre que quiser!","Eu não sou um escravo para trabalhar por comida, então minha consciência está limpa! Mas não vou mais participar de roubos!");
				Link.l1 = "Na verdade, você está enganado... Enquanto bebia na taverna, podia escolher qualquer trabalho que quisesse... Mas assim que pisou no meu navio, sua única saída passou a ser uma bala de canhão estourando seu pescoço... E com a língua arrancada, pra não sair falando nada no outro mundo...";
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "WantToGo_stop_stay";
				}
				else
				{
					Link.l1.go = "WantToGo_stop_fight";	
				}
				Link.l2 = "Tá bom. Pode ir... Mas Deus me livre de te encontrar em alto-mar. Juro que você vai se arrepender do momento em que decidiu não ficar ao meu lado.";
				Link.l2.go = "exit_fire_5";
			}
			else
			{
				dialog.text = LinkRandPhrase("Nem tente me intimidar! Eu trabalho por dinheiro, mas ainda tenho o direito de escolher um serviço que me agrade!","Sou um homem livre! E tenho o direito de aceitar um novo trabalho quando eu quiser!","Eu não sou seu escravo! E não vou continuar levando uma vida miserável nesse seu velho barco!");
				Link.l1 = "Bem, na verdade, você está enganado... Enquanto estava bebendo na taverna, podia escolher qualquer trabalho que quisesse... Mas assim que pisou no meu navio, sua única saída passou a ser uma bala de canhão estourando seu pescoço... E com a língua arrancada, pra não sair contando nada no outro mundo...";
				// belamour legendary edition можно запугать офицера -->
				//if (makeint(Pchar.Rank) > makeint(NPchar.Rank) || CheckCharacterPerk(pchar, "IronWill"))
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "WantToGo_stop_stay";
				}
				else
				{
					Link.l1.go = "WantToGo_stop_fight";	
				}
				Link.l2 = "Certo. Pode ir... Mas que Deus te proteja se me encontrar em alto-mar. Juro que você vai se arrepender do momento em que decidiu não ficar ao meu lado.";
				Link.l2.go = "exit_fire_5";
			}
		break;
		
		case "WantToGo_stop_stay":
			dialog.text = RandPhraseSimple("Se você coloca dessa forma, eu fico, simplesmente não tenho outra escolha. Mas lembre-se de que não estou fazendo isso por vontade própria...","Certo, se você coloca dessa forma, eu fico. Mas saiba que, ao fazer isso, estou indo contra a minha própria vontade.");
			Link.l1 = RandPhraseSimple("Tudo bem... Sirva até eu decidir te dispensar.","Isso é bom. Continue servindo... Eu decido quando vou te liberar.");
			Link.l1.go = "WantToGo_Munity"; //этот линк ведет к бегству
		break;
		
		case "WantToGo_stop_fight":
			dialog.text = NPCharRepPhrase(NPChar,"Você nunca vai me obrigar a mudar de ideia! Você não tem o direito de me manter como escravo! Eu vou embora, fique longe ou você vai se arrepender.","Você acha que pode assustar um oficial veterano?! Já estive cara a cara com a morte mais de uma vez. E se é assim, prefiro morrer em uma batalha justa do que durante um saque sangrento!");
			Link.l1 = NPCharRepPhrase(NPChar,"Bem... cada um escolhe o próprio destino. Espero que tenha rezado antes de vir até mim.","Se eu soubesse que isso ia acontecer quando te peguei na taverna, teria deixado você balançar na forca. E ainda dá tempo de providenciar isso...");
			Link.l1.go = "WantToGo_stop_fight_1";
			Link.l2 = NPCharRepPhrase(NPChar,"Bem, você pode ir embora se precisa tanto da sua liberdade. Mas não vou te dar nenhuma recomendação.","Certo. Pode ir... Mas que Deus te proteja se me encontrar em alto-mar. Juro que você vai se arrepender do momento em que decidiu não ficar ao meu lado.");
			Link.l2.go = "exit_fire_5";	
		break;
		
		case "WantToGo_stop_fight_1":
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			dialog.text = NPCharRepPhrase(NPChar,"Pare de me intimidar de uma vez! Qual dos seus capangas teria coragem de me enfrentar? Se eu fosse o capitão, eles já estariam nadando em dinheiro! E depois de toda a sua generosidade, você ainda teme que sua tripulação fique do meu lado?!","Pare com isso, você não vai me assustar! Adeus.");
			Link.l1 = NPCharRepPhrase(NPChar,"Não, camarada, você não vai viver o bastante pra chegar à forca. Esse luxo não é pra você...","Calma aí, camarada, ainda não estamos quites. Você me deve uma.");
			Link.l1.go = "Get_out_fight";
		break;	
		///////////////////////////////////////////////////////////////////////////////////
		case "WantToGo_Munity":	//zagolski. отыгрыш бегство офицера
			Diag.TempNode = "Hired";
			// belamour legendary edition в ближайшее время не подойдет от страха
			/* if(CheckCharacterPerk(pchar, "IronWill"))
			{
				Npchar.loyality = makeint(Npchar.loyality) + 3 + hrand(sti(GetSummonSkillFromNameToOld(pchar,SKILL_FORTUNE)+GetSummonSkillFromNameToOld(pchar,SKILL_LEADERSHIP)));
				log_info(GetFullName(Npchar)+" increased his loyalty");
				log_testinfo("Loyalty has become: " + Npchar.loyality + " of " + MAX_LOYALITY);
			}
			else
			{ */
				if (!CheckAttribute(pchar, "questTemp.MutinyOfficerIDX"))
				{
					pchar.questTemp.MutinyOfficerIDX = npchar.index;
					npchar.quest.Mutiny = true; // mitrokosta доп защита от багов
					SetFunctionTimerCondition("mOfficer_fc", 0, 0, 1, false);
				}
			//}
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.location = "none";
			LAi_SetOfficerType(NPChar);
			DialogExit();
		break;
		////////////////////////////////////////////////////////////////////
		// пассажир возмущен игроком и сваливает <--
		
		case "Node_2":
			dialog.text = NPCharRepPhrase(Npchar,RandSwear()+"Eu sou o melhor "+XI_ConvertString(Npchar.quest.officertype)+" nessas águas. "+Npchar.quest.officertype_2+"E estou pronto para lhe fazer um favor e servir sob seu comando.","Bem, dizem que eu não sou ruim "+XI_ConvertString(Npchar.quest.officertype)+". "+Npchar.quest.officertype_2+"Você pode me levar no seu navio, capitão, e ver com seus próprios olhos.");
			Link.l1 = "E quanto você quer?";
			Link.l1.go = "price";
			Link.l2 = "E que tipo de especialista é você?";
			Link.l2.go = "ShowParam_exit";
			Link.l3 = "Infelizmente, eu já tenho um "+XI_ConvertString(Npchar.quest.officertype)+".";
			Link.l3.go = "Exit";
		break;

		case "OnceAgain":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = RandPhraseSimple("Heh, capitão, metade da guarnição está atrás de você neste momento. Com certeza não é a melhor hora para entrar na sua tripulação!","E lutar até o navio? Não, capitão, deixa pra outra hora...");
				link.l1 = RandPhraseSimple("Como quiser...","Na verdade, eu não ia te contratar."); 
				link.l1.go = "exit";
				break;
			}
			Diag.TempNode = "OnceAgain";
			dialog.text = " Mudou de ideia, capitão? Resolveu que um novo "+XI_ConvertString(Npchar.quest.officertype)+" não faria mal?";
			// boal -->
			if (FindFreeRandomOfficer() > 0)
			{
                Link.l1 = "Algo assim. Quanto você quer?";
                Link.l1.go = "price";
			}
			Link.l2 = "E do que você é capaz?";
			Link.l2.go = "ShowParam_exit";
			// boal <--
			Link.l3 = "Tenho um jogo completo. Até mais.";
			Link.l3.go = "exit";
		break;

		case "price":
			dialog.text = "Acho que podemos concordar em "+Npchar.quest.OfficerPrice+" pesos.";
			if(Npchar.rank >= 15)
			{
				dialog.text = "Acho que podemos concordar em "+(makeint(Npchar.quest.OfficerPrice)/ 100+30)+" dobrões.";
			}	
			Link.l1 = "Isso não é um pouco demais?";
			Link.l1.go = "trade";
			Link.l2 = "Concordo. Considere-se parte da tripulação.";
			Link.l2.go = "hire";
			Link.l3 = "Você não vale esse dinheiro.";
			Link.l3.go = "exit";
		break;

		case "trade":
			if (GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE) >= Rand(12) && (sti(Npchar.quest.OfficerPrice) - GetCharacterSkillToOld(Pchar, "commerce")*100) >= sti(Npchar.quest.OfficerLowPrice))// bug fix
			{
				Npchar.quest.OfficerPrice = makeint(makeint(Npchar.quest.OfficerPrice) - GetCharacterSkillToOld(Pchar, "commerce")*100); // пусть будет коммерция перса голой
				dialog.text = "Certo... Suponho que eu poderia concordar até mesmo com "+Npchar.quest.OfficerPrice+" pesos. O que me diz?";
				if(Npchar.rank >= 15)
				{
					dialog.text = "Acho que eu poderia concordar até mesmo com "+(makeint(Npchar.quest.OfficerPrice)/ 100+30)+" dobrões. O que me diz?";
				}
				Link.l1 = "Agora sim. Você está dentro.";
				Link.l1.go = "hire";				
				Link.l2 = "Ainda acho que é um pouco demais. Tchau.";
				Link.l2.go = "exit";
			}
			else
			{
				dialog.text = "Me desculpe, capitão, mas eu valho exatamente o que pedi. Se for demais pra você, então procure outra pessoa.";
				Link.l1 = "Certo, eu concordo. Vou te levar.";
				Link.l1.go = "hire";				
				Link.l2 = "É isso que eu vou fazer. Adeus.";
				Link.l2.go = "exit";
			}
		break;

		case "hire":
			dialog.text = "Vejo que está sem dinheiro, capitão! Sinto muito, mas não trabalho fiado.";
			Link.l1 = "Ah, diabo!";
			Link.l1.go = "Exit";
			if(Npchar.rank < 15 && makeint(Pchar.money) >= makeint(Npchar.quest.OfficerPrice))
			{
				AddMoneyToCharacter(Pchar, -(makeint(Npchar.quest.OfficerPrice)));
				Diag.TempNode = "OnboardSoon";
				dialog.text = "Obrigado, capitão. Você não vai se arrepender da sua escolha.";
				Link.l1 = "Espero que sim.";
				Link.l1.go = "Exit_hire";								
			}
			if(Npchar.rank >= 15 && PCharDublonsTotal() >= makeint((makeint(Npchar.quest.OfficerPrice) / 100 + 30)))
			{
				RemoveDublonsFromPCharTotal(makeint((makeint(Npchar.quest.OfficerPrice) / 100 + 30)));
				Diag.TempNode = "OnboardSoon";
				dialog.text = "Obrigado, capitão. Você não vai se arrepender da sua escolha.";
				Link.l1 = "Espero que sim.";
				Link.l1.go = "Exit_hire";								
			}
		break;

		case "OnboardSoon":			
			Diag.TempNode = "OnboardSoon";
			dialog.text = "Vou só terminar minha bebida, capitão, e depois vou para o navio. Não se preocupe, estarei lá a tempo.";
			Link.l1 = "Certo. Se você se atrasar, vou te fazer esfregar o convés!";
			Link.l1.go = "Exit";											
		break;
        
		case "QMASTER_1":
			if(sti(PChar.Ship.Type) == SHIP_NOTUSED)
			{
				dialog.text = "Capitão, mas você não tem navio!";
				Link.l1 = "Obrigado por me lembrar...";
				Link.l1.go = "Exit";
				Diag.TempNode = "Hired";
				break;
			}
			// Rebbebion, добавил фикс отображения знака процента
			dialog.text = "Máxima atividade de ratos durante a viagem "+FloatToString(50.0 /(2.0+GetSummonSkillFromNameToOld(PChar,SKILL_REPAIR)+GetSummonSkillFromNameToOld(PChar,SKILL_SNEAK)),1)+"%% do valor total da carga. Por "+GetCrewQuantity(PChar)+" marinheiros nós vamos precisar "+makeint((GetCrewQuantity(PChar)+6)/ 10)+" comida por dia. Isso não inclui os escravizados em transporte.";
			Link.l1 = "Obrigado.";
			Link.l1.go = "Exit";
			Diag.TempNode = "Hired";
		break;
        
        // boal 05.09.03 offecer need to go to abordage -->
        case "stay_follow":
            dialog.text = "Quais são suas ordens?";
            Link.l1 = "Fique aqui!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Me siga e não fique para trás!";
            Link.l2.go = "Boal_Follow";
            // boal 05.09.03 offecer need to go to abordage <--
			if (npchar.id == "OffMushketer")
			{
				Link.l3 = "Quero que você mantenha uma certa distância do alvo.";
				Link.l3.go = "TargetDistance";
			}
			
			if(CheckAttribute(NPChar, "equip.gun"))
			{
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l4 = "Precisamos trocar o tipo de munição da sua arma de fogo.";
					Link.l4.go = "SetGunBullets";
				}	
			}
			if(CheckAttribute(NPChar, "equip.musket"))
			{
				if(CheckAttribute(NPChar, "chr_ai.musket.bulletNum") && sti(NPChar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l5 = "Precisamos trocar o tipo de munição do seu mosquete.";
					Link.l5.go = "SetMusketBullets";
				}
					Link.l6 = "Precisamos trocar sua arma principal para o combate.";
					Link.l6.go = "SetPriorityMode";
			}
		break;

		case "SetGunBullets":
			Dialog.Text = "Selecione o tipo de munição:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetItemName(rItem);
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			Diag.CurrentNode = Diag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetItemName(rItem)+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;
		
		case "SetMusketBullets":
			Dialog.Text = "Selecione o tipo de munição:";
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.musket.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetItemName(rItem);
				Link.(attrL).go = "SetMusketBullets1_" + i;
			}
		break;	

		case "SetMusketBullets2":
			i = sti(NPChar.SetMusketBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, MUSKET_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, MUSKET_ITEM_TYPE);
			Diag.CurrentNode = Diag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetItemName(rItem)+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetMusketBullets");
			DialogExit();
		break;
		
		case "SetPriorityMode":
			Dialog.Text = "No início da luta você usará:";
			Link.l1 = "Blade";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "Mosquete";
			Link.l2.go = "MusketPriorityMode";
		break;
		
		case "BladePriorityMode":
            SetPriorityMode(NPChar, 1);
			DialogExit();
		break;
		
		case "MusketPriorityMode":
			SetPriorityMode(NPChar, 2);
			DialogExit();
		break;
		
		case "TargetDistance":
			dialog.text = "Que distância exatamente, capitão? Especifique em passos, mas não mais que 20.";
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";			
		break;
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = "Capitão, você está bem?";
				link.l1 = "Desculpe, foi meu erro...";
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Vou ficar aqui sem me mexer. É isso que você quer de mim, capitão?";
				link.l1 = "Sim. É exatamente isso que se espera de você.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "Acho que já te disse que não consigo ficar a mais de 20 passos do alvo.";
				link.l1 = "Certo, mantenha uma distância de 20 metros.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = "Entendido e levado em consideração.";
			link.l1 = "Certo.";
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;

		case "AsYouWish":
			// проверка на море -->
			if (bSeaActive)
			{
				attr = Sea_FindNearColony();
				if (attr == "none")
				{
					dialog.text = "Capitão, embora eu realmente não entenda seu raciocínio, podemos conversar sobre isso em terra? Ou você já decidiu simplesmente me jogar ao mar?";
					Link.l1 = "Hum... Não, não foi isso que eu quis dizer. Fique aqui até chegarmos ao porto.";
					Link.l1.go = "Exit";	
					break;	
				}
			}
			// проверка на море <--
			if (makeint(PChar.reputation.nobility) >= 41 && makeint(NPChar.reputation) < 41) //герой против злодея
			{
				dialog.text = RandPhraseSimple(LinkRandPhrase("Isso sim é novidade!","Por quê, em nome do céu?","Qual é o motivo?!"),RandPhraseSimple("Capitão, você ficou louco? Falar uma coisa dessas do nada!","Mas que diabos! E o que foi que eu fiz pra te desagradar?"));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("Decidi impor ordem à tripulação. E não aprovo o seu envolvimento com os colegas","Seus benefícios não foram tão bons quanto discutido na contratação. Então,","Marginais e canalhas na minha tripulação não vão ficar! Então,"),LinkRandPhrase("Chegou ao meu conhecimento que você está roubando rum, incentivando secretamente minha tripulação a beber demais e, assim, diminuindo o moral deles. Portanto,","Estou farto dos seus modos de bandido e não vou mais tolerar isso. Então,","Você passa o tempo todo na cabine central jogando cartas ou dados, distraindo os outros oficiais de suas funções. Isso não pode continuar assim para sempre. Então,"))+" junte suas coisas e saia do navio.";
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "Get_out_A1_peace";
				}
				else
				{
					Link.l1.go = "Get_out_A1_strife";
				}
				break;	
			}
			if (makeint(PChar.reputation.nobility) >= 41 && makeint(NPChar.reputation) >= 41) // герой против героя
			{
				dialog.text = RandPhraseSimple(RandPhraseSimple("Posso saber o motivo de tal decisão?","Obviamente, uma decisão dessas é bem fundamentada."),RandPhraseSimple("Explique-se, Capitão","Isso é bem inesperado. Mas ainda assim gostaria de saber o motivo."));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("Estou completamente insatisfeito com a sua atitude em relação às suas obrigações.","Infelizmente, você não se saiu bem como oficial e provavelmente nunca vai se sair...","Você é um bom oficial e seu serviço foi justo, mas agora nossos caminhos se separaram. Não me pergunte por quê."),LinkRandPhrase("Eu te avisei que essa sua paixão pelo rum ia te arruinar. Como posso confiar num homem numa briga se ele nem consegue guardar a espada na bainha?","Você é um péssimo marinheiro e oficial... Acho que vai passar mais tempo em terra do que no mar.","Não estou satisfeito com suas qualificações, mas agora finalmente encontrei um substituto adequado."));
				Link.l1.go = "Get_out_A2";
				break;	
			}
			if (makeint(PChar.reputation.nobility) < 41 && makeint(NPChar.reputation) >= 41) // злодей против героя 
			{		
				dialog.text = RandPhraseSimple(RandPhraseSimple("Hmm... Posso saber o motivo?","Isso é uma afirmação séria. Posso saber com o que exatamente você está insatisfeito?"),RandPhraseSimple("Explique-se, capitão.","Obviamente, uma afirmação dessas é bem fundamentada?"));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("Estou completamente insatisfeito com suas qualificações, portanto","Infelizmente, você não se mostrou um oficial decente. Então,","Estou farto dos seus modos nobres. Não vou tolerar isso para sempre, então"),LinkRandPhrase("Chegou ao meu conhecimento que você está incitando a tripulação à desobediência. Não haverá tumultos no meu navio! E não me agradeça por não ter te jogado ao mar antes. Então","Seus princípios nobres lhe dão crédito, mas vão contra a vida sem leis de um corsário livre. Então","Não gosto da sua atitude em relação às suas obrigações. Então"))+" junte suas coisas e saia do navio.";
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "Get_out_A3_peace";
				}
				else
				{
					Link.l1.go = "Get_out_A3_strife";
				}	
				break;
	
			}
			if (makeint(PChar.reputation.nobility) < 41 && makeint(NPChar.reputation) < 41) // злодей против злодея
			{	
				dialog.text = RandPhraseSimple(LinkRandPhrase("Capitão, eu realmente não esperava por isso! Talvez você possa me explicar o que está acontecendo?","Capitão, o que está te preocupando?!","O que quer dizer com isso, Capitão?!"),RandPhraseSimple("Mas que diabos, capitão?! Ontem estava tudo certo, e agora estamos nessa, o que aconteceu?","Mas que diabos! Talvez queira se explicar?"));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("Você é um completo preguiçoso e um inútil, até um grumete em um barco de carga faria melhor. Já sofri demais por sua causa. Então","Já faz um tempo que penso em te dispensar, e agora finalmente encontrei alguém à altura para te substituir. Então","Fiquei sabendo que você está roubando rum, incentivando secretamente minha tripulação a beber demais e, com isso, prejudicando o moral deles. Portanto"),LinkRandPhrase("Quando te contratei, você se gabou de ser o melhor oficial de toda a frota, mas no fim das contas não passa de um preguiçoso, então","Eu te avisei que esse seu vício em bebida ia acabar mal. Por que eu deveria manter um bêbado inútil no meu navio? Então","Em vez de trabalhar, você vive sumindo por aí, ou jogando cartas ou dados. Espero que não tenha achado que isso ia durar pra sempre? Então"))+" arrume suas coisas e saia do navio.";
				Link.l1.go = "Get_out_A4";
				break;
			}
		break;
	
		case "Get_out_A1_peace":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Então é assim que você fala agora! Tudo bem, como quiser. Mas fique sabendo: eu não volto pra você, nem que esteja morrendo de fome!","Francamente, também não faço questão dos seus joguinhos de nobre. Então, adeus...","Ah, vai pro inferno! Fique com seus puxa-sacos. 'Herói', é?!"),LinkRandPhrase("Na verdade, eu nunca gostei de te servir... Você tem uma barca de carga aí, não um navio de verdade. Parece mais uma escola de boas maneiras...","Sabe, estou de saco cheio da sua tripulação, todos eles cheios de frescura, só um bando de moleques, não tem um homem de verdade aí...","Certo, capitão, como quiser. Mas Deus sabe, eu tenho feito meu trabalho direitinho..."));
			Link.l1 = "Espere. No momento, não posso deixar o navio sem um oficial. Mas voltaremos a essa conversa depois.";
			Link.l1.go = "exit_bad";
			Link.l2 = "Então vá em paz.";
			Link.l2.go = "Exit_Fire_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "Não se irrite. Preparei uma indenização para você - "+sti(NPChar.rank)*500+" pesos. Espero que isso resolva todas as questões.";
				Link.l3.go = "Get_out_А1_ForMoney";
			}
		break;

		case "Get_out_A1_strife":
			dialog.text = LinkRandPhrase("Com licença! Como assim 'sair do navio'?! Eu não arrisquei meu pescoço sob fogo de canhão pra você me mandar embora quando bem entender!","Ha! 'Sair do navio'! Você realmente acha que vou deixar você me descartar como um gatinho?!","Calma, capitão, gente séria não resolve as coisas assim. Não vou ser tratado como um novato.");
			Link.l1 = "Certo, você pode ficar por enquanto – mas só até eu encontrar um substituto decente.";
			Link.l1.go = "exit_bad";
			Link.l2 = "Eu repito, seu serviço acabou. Pode arrumar suas coisas.";
			Link.l2.go = "Get_out_A1_strife_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "Não se irrite. Eu preparei "+sti(NPChar.rank)*500+" pesos para você. Espero que isso resolva todas as questões.";
				Link.l3.go = "Get_out_А1_ForMoney";
			}
		break;

		case "Get_out_A1_strife_1":
			dialog.text = RandPhraseSimple("Na verdade, não estou morrendo de vontade de ficar aqui. Mas também não vou embora sem uma compensação!","Agora, com certeza não vou ficar nesse seu velho barco, mas antes você vai me compensar!")+" "+sti(NPChar.rank)*1000+" pesos, e nunca mais vamos nos ver.";
			Link.l1 = "Me exaltei um pouco... Por favor, aceite minhas desculpas e volte às suas tarefas.";
			Link.l1.go = "exit_bad1";
			Link.l2 = "Que dinheiro é esse de que você está falando, se sempre recebeu a sua parte justa? Isso pra mim parece chantagem!";
			Link.l2.go = "Get_out_А1_strife_battle";
			if (sti(Pchar.money) >= sti(NPChar.rank)*1000)
			{
				Link.l3 = "Certo. Devolva o equipamento, e então você terá o que pediu.";
				Link.l3.go = "Get_out_А1_chang";
			}
		break;

		case "Get_out_А1_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			dialog.text = "Agora isso já é outra história. Adeus!";
			Link.l1 = "Espero mesmo que nossos caminhos nunca mais se cruzem.";
			Link.l1.go = "Exit_Fire_1";
		break;

		case "Get_out_А1_strife_battle":
			dialog.text = LinkRandPhrase("Considere isso uma compensação por danos morais. Não vou tolerar esse tipo de tratamento, e quem ousar me tratar assim vai se arrepender!","Isso não é extorsão, e sim uma compensação por esse desperdício idiota do meu tempo! E eu vou conseguir, custe o que custar!","Perdi tempo demais servindo sob o comando de um covarde como você. Eu poderia ter feito uma fortuna saqueando navios mercantes. Então só quero compensar o lucro que deixei de ganhar.");
			if (sti(Pchar.money) >= sti(NPChar.rank)*1000)
			{
				Link.l1 = "Certo. Aqui está o seu dinheiro... Agora suma daqui!";
				Link.l1.go = "Get_out_А1_ForMoney_angry";
			}
			Link.l2 = "Parece que você está esquecendo quem é! Não vou permitir que idiotas como você gritem comigo!";
			Link.l2.go = "Get_out_А1_strife_death";
		break;

		case "Get_out_А1_strife_death":
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			OfficersReaction("good");
			dialog.text = "Vai lá, capitão! Mostre-se!";
			Link.l1 = "Deus sabe, eu não queria isso!";
			Link.l1.go = "Get_out_fight";
		break;
	
		case "Get_out_А1_ForMoney_angry":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			OfficersReaction("bad");
			dialog.text = "Agora isso já é outra história. Adeus!";
			Link.l1 = "Espero mesmo que nossos caminhos nunca mais se cruzem.";
			Link.l1.go = "Exit_Fire_1";
		break;

		case "Get_out_A2":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Então está decidido, capitão. Adeus, e não guarde rancor...","Uma pena, capitão. Mas Deus sabe, eu tentei. Adeus.","Bem, capitão, você realmente não é fácil de agradar! Tudo bem, boa sorte pra você."),LinkRandPhrase("Uma pena, capitão. Sabe, gostei de trabalhar para você.","É, acontece... Mas não guardo rancor. Adeus.","Você está sendo injusto comigo, capitão. Ainda assim, respeito sua decisão. Adeus."));
			Link.l1 = "Espera, mudei de ideia. Vamos deixar essa conversa pra depois.";
			Link.l1.go = "exit_good";
			Link.l2 = "Não fique chateado. Boa sorte pra você...";
			Link.l2.go = "exit_fire_2";
			Link.l3 = "Espere... Eu te equipei direitinho. Devolva, não vou sair equipando uma multidão...";
			Link.l3.go = "Return_items_A2";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l4 = "Espere... Não quero deixar você sair de mãos vazias. Aqui, pegue "+sti(NPChar.rank)*500+" pesos. Vai ser útil enquanto você procura um novo emprego.";
			}
			Link.l4.go = "Im_kind_A2";
		break;

		case "Return_items_A2":
			ChangeOfficersLoyality("bad_all", 1);
			dialog.text = "Ah, claro, pode levar tudo de volta...";
			Link.l1 = "Eu sei que você me entende, não é...";
			Link.l1.go = "Get_out_А2_chang";
		break;

		case "Im_kind_A2":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeOfficersLoyality("good_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			dialog.text = "Obrigado, capitão! Que generosidade inesperada... Sabe, ainda tenho algumas coisas suas, talvez queira recuperá-las?";
			Link.l1 = "Talvez... Encontrar uma boa lâmina não seja tão fácil hoje em dia...";
			Link.l1.go = "Get_out_А2_chang";
			Link.l2 = "Ah, não se preocupe. Fique com eles como lembrança do seu serviço.";
			Link.l2.go = "exit_fire_2";
		break;

		case "Get_out_A3_peace":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Certo, como quiser. Mas fique sabendo: não vou voltar pra você, nem que eu esteja morrendo de fome!","Capitão, esse seu jeito de bandido de fazer negócios também me enoja. Mais cedo ou mais tarde, isso ia acontecer mesmo. E não precisa inventar desculpas.","Fique com seus assassinos, então. Um homem decente não teria nem coragem de aparecer na sala de oficiais do seu navio. Que bordel você tem aqui, Deus me perdoe!"),LinkRandPhrase("Francamente, eu também não gostei de servir sob seu comando. Você contratou uma tripulação cheia de canalhas, não tem um homem decente com quem conversar.","É, se você continuar tratando sua tripulação desse jeito, logo vai acabar sozinho e nem vai precisar inventar desculpas.","A nossa inimizade é mútua, e isso me conforta. Adeus."));
			Link.l1 = "Espere. Agora não é o melhor momento para sua aposentadoria. Mas todos os direitos estão mantidos.";
			Link.l1.go = "exit_bad";
			Link.l2 = "Vai, vai. Eu fico bem sem as suas lições.";
			Link.l2.go = "exit_fire_3";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "Espere. Eu vou te dar "+sti(NPChar.rank)*500+" pesos. Não quero que você acabe largado na sarjeta, para eu não ficar me sentindo culpado por isso.";
				Link.l3.go = "Get_out_А3_ForMoney";
			}
		break;

		case "Get_out_А3_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			ChangeOfficersLoyality("good_all", 1);
			dialog.text = LinkRandPhrase("Bem, obrigado. Adeus...","Obrigado pela compreensão. Boa sorte.","Agora terminamos. Boa sorte...");
			Link.l1 = "Eu sei que você me entende, não é.";
			Link.l1.go = "exit_fire_3";
		break;
	
		case "Get_out_A3_strife":
			dialog.text = LinkRandPhrase("Mas capitão, nesse caso eu fico encalhado. Você está mesmo disposto a me mandar do navio direto para a paróquia?","Você está sendo injusto comigo, capitão. Mas não guardarei rancor se receber uma compensação justa.","E essa é a sua gratidão por todas as minhas feridas de batalha? Bem, acho que não posso ficar sem uma compensação em dinheiro.");
			Link.l1 = "Certo, mudei de ideia. Você pode ficar, mas voltaremos a conversar sobre isso.";
			Link.l1.go = "exit_bad";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l2 = "Ah, não se preocupe com isso. Aqui - "+sti(NPChar.rank)*500+" pesos. Isso vai compensar pelo tempo que você passou no meu navio.";
				Link.l2.go = "Get_out_А3_ForMoney";
				Link.l3 = "Eu vou te dar o dinheiro. Mesmo assim, você ficou bem equipado graças a mim, então acho justo que me devolva as coisas.";
				Link.l3.go = "Return_items_A3";
			}
			Link.l4 = "Ah, é mesmo? E a sua parte, que você vem recebendo direitinho?! Eu sabia que isso ia acabar em reclamação e pedido de bônus.";
			Link.l4.go = "Get_out_A3_strife_1";
		break;

		case "Return_items_A3":
			dialog.text = "Eu sabia que você diria isso, mas só vai receber seu equipamento de volta quando eu receber "+sti(NPChar.rank)*1000+" pesos. Caso contrário, só vai conseguir isso por cima do meu cadáver!";
			Link.l1 = "Certo, pegue seu dinheiro, então.";
			Link.l1.go = "Get_out_А3_chang";
			Link.l2 = "Você está maluco ou o quê?! Exigir uma quantia dessas por algo que te foi dado de graça?! Agora vejo que sua ganância claramente venceu sua falsa boa vontade.";
			Link.l2.go = "Get_out_A3_strife_1";
		break;

		case "Get_out_A3_strife_1":
			dialog.text = "Não ouse me insultar! Talvez eu não seja o melhor da Marinha, mas ainda sou um oficial de combate. E vou ser respeitado, até mesmo por um grosseiro como você!";
			Link.l1 = "Se ainda não entendeu, vou repetir mais uma vez: pare de implorar, você não vai conseguir nada de mim.";
			Link.l1.go = "Get_out_А3_strife_death";
		break;

		case "Get_out_А3_strife_death":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			OfficersReaction("bad");
			dialog.text = "Bem, ainda vou ter minha satisfação!";
			Link.l1 = "Ah, então isso é um desafio, não é? Como quiser então...";
			Link.l1.go = "Get_out_fight";
		break;

		case "Get_out_A4":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Que sorte a minha! Dediquei meu coração e alma ao serviço, só para ser mandado embora sem nem uma pensão!","Que azar, hein?! Mal fui contratado e já fui mandado embora quase na mesma hora. Nem sei mais pra qual santo acendo vela hoje em dia...","Puxa vida! Ser demitido pela terceira vez só este ano, e sempre numa segunda-feira. Talvez eu devesse evitar aparecer na frente do capitão quando estou de ressaca."),LinkRandPhrase("Bem, como quiser. Reze para que nunca mais nos encontremos.","Como quiser. Mas lembre-se de que nunca vai encontrar um oficial melhor.","Está bem, capitão, como quiser. Mas Deus sabe, eu tenho feito meu trabalho direitinho..."));
			Link.l1 = "Espere. Agora não é o melhor momento para você se aposentar. Mas todos os seus direitos estão garantidos.";
			Link.l1.go = "exit_good";
			Link.l2 = RandPhraseSimple("Vá embora agora. E agradeça a Deus que estou de bom humor hoje.","Cai fora agora. Você é tão bom oficial quanto merda serve pra fazer bala.");
			Link.l2.go = "exit_fire_4";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "Espere. Eu vou te dar "+sti(NPChar.rank)*500+" pesos. Não quero que você acabe morrendo na sarjeta, senão vou me sentir culpado por isso.";
				Link.l3.go = "Get_out_А4_ForMoney";
			}
			Link.l4 = "Espere... Eu te equipei bem, devolva minhas coisas.";
			Link.l4.go = "Return_items_A4";
		break;

		case "Get_out_А4_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			ChangeOfficersLoyality("good_all", 1);
			dialog.text = LinkRandPhrase("Oh, obrigada, capitão! Isso é realmente muito gentil da sua parte...","Obrigado pela compreensão. Boa sorte.","Agora terminamos. Boa sorte...");
			Link.l1 = "Boa sorte. Espero que você não gaste tudo na primeira taverna.";
			Link.l1.go = "exit_fire_4";
		break;

		case "Return_items_A4":
			if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
			{
				dialog.text = LinkRandPhrase("E agora você está levando meu equipamento! Ah, quer saber? Vou pescar, juro...","Vejo que você decidiu me deixar completamente sem nada. Fazer o quê. Agora só me resta um caminho, para o parvis...","Oh, muito obrigado! Agora você resolveu me roubar. Ah, que destino cruel... Pegue então, pegue! O que eu posso fazer mesmo...");
				Link.l1 = "Cai fora agora. Você é tão bom oficial quanto merda serve pra fazer bala.";
				Link.l1.go = "Get_out_А4_chang_1";
			}
			else	
			{
				dialog.text = RandPhraseSimple("Como quiser, capitão, mas antes, por favor, seja gentil e me entregue "+sti(NPChar.rank)*1000+" pesos. Que isso sirva como compensação pelo dano moral.","Certo. Mas ainda quero receber "+sti(NPChar.rank)*1000+" pesos como compensação pelo meu trabalho duro e fiel.");
				if (sti(Pchar.money) >= sti(NPChar.rank)*1000)
				{
					Link.l1 = "Que canalha! Tudo bem, aqui está o seu dinheiro.";
					Link.l1.go = "Get_out_А4_chang";
				}
				Link.l2 = "Você está maluco?! Como ousa pedir tanto dinheiro por algo que eu mesma te dei!";
				Link.l2.go = "Get_out_A4_strife";
				Link.l3 = "Ah-ha! Eu estava brincando! Como eu poderia expulsar um velho amigo, ainda mais com esse chapéu furado!";
				Link.l3.go = "exit_bad1";
			}
		break;

		case "Get_out_A4_strife":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			ChangeOfficersLoyality("bad_all", 1);
			dialog.text = "Então, você não vai receber nada! Não dou um passo sequer até ouvir o tilintar do meu dinheiro!";
			Link.l1 = RandPhraseSimple("Logo você vai ouvir o tilintar da minha lâmina!","Então você vai sair daqui carregado, de pés pra frente!");
			Link.l1.go = "Get_out_fight";
		break;

		case "Get_out_fight":
			CheckForReleaseOfficer(GetCharacterIndex(Npchar.id));
			RemovePassenger(Pchar, Npchar);
			LAi_CharacterDisableDialog(NPChar);
			LAi_SetWarriorType(Npchar);
			LAi_group_MoveCharacter(Npchar, "TmpEnemy");
			LAi_group_SetHearRadius("TmpEnemy", 100.0);
			LAi_group_FightGroupsEx("TmpEnemy", LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
			if (PChar.location == Get_My_Cabin() || findsubstr(PChar.location, "_tavern" , 0) != -1 || findsubstr(PChar.location, "_store" , 0) != -1)
            {
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				LAi_group_SetCheck("TmpEnemy", "CannotFightCurLocation");
				LAi_group_SetCheck("TmpEnemy", "MainHeroFightModeOff");
            }
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

	    case "Get_out_А1_chang": // интерфейс обмена
			Diag.TempNode = "Fired_1";
			LAi_CharacterDisableDialog(NPChar);
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;	
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А2_chang": // интерфейс обмена
			Diag.TempNode = "Fired_2";
			LAi_CharacterDisableDialog(NPChar);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А3_chang": // интерфейс обмена
			Diag.TempNode = "Fired_3";
			LAi_CharacterDisableDialog(NPChar);
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А4_chang_1": // интерфейс обмена
			Diag.TempNode = "Fired_4";
			LAi_CharacterDisableDialog(NPChar);
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;	
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А4_chang": // интерфейс обмена
			Diag.TempNode = "Fired_4";
			LAi_CharacterDisableDialog(NPChar);
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;	
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

	    case "exit_bad":
			Npchar.loyality = makeint(Npchar.loyality) - 3;
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_bad1":
			Npchar.loyality = makeint(Npchar.loyality) - 2;
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			Diag.CurrentNode = Diag.TempNode;			
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_good":
			Npchar.loyality = makeint(Npchar.loyality) - 1;
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_fire_1":	//navy -->			
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--		
			Diag.TempNode = "Fired_1";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_2":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");	
				DialogExit();
				break;
			}	//navy <--	
			Diag.TempNode = "Fired_2";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_3":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--	
			Diag.TempNode = "Fired_3";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_4":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");	
				DialogExit();
				break;
			}	//navy <--		
			Diag.TempNode = "Fired_4";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_5":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--	
			Diag.TempNode = "Fired_1";
			OfficersReaction("good");
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "Fired_1":
			Diag.TempNode = "Fired_1";      
			dialog.text = "E agora?! Já falamos sobre tudo! Nunca mais vou pôr os pés no seu navio.";
			Link.l1 = RandPhraseSimple("Cai fora agora. Não vai fazer falta mesmo, no fim das contas.","Está bem, vá então. Não vou te segurar.");	
			Link.l1.go = "Exit";
		break;

		case "Fired_2":
			Diag.TempNode = "Fired_2"; 
			dialog.text = "Mais alguma coisa, capitão? Achei que já tínhamos conversado sobre tudo...";
			Link.l1 = "Não, nada. Só queria me despedir...";	 
			Link.l1.go = "Exit";
		break;

		case "Fired_3":
			Diag.TempNode = "Fired_3"; 
			dialog.text = "Capitão, já discutimos tudo e deixamos claro o que queremos. Não vai dizer que mudou de ideia, vai?";
			Link.l1 = "Certo, vai lá, então. No fim das contas, não é grande coisa perder você.";	 
			Link.l1.go = "Exit";
		break;

		case "Fired_4":
			Diag.TempNode = "Fired_4"; 
			dialog.text = "Capitão, que outras perguntas poderiam haver? Só para você saber, estou profundamente ofendido e não tenho vontade nenhuma de voltar...";
			Link.l1 = "Certo, vai, então. Não que eu precisasse tanto de você assim.";	 
			Link.l1.go = "Exit";
		break;
		
		// boal 05.09.03 offecer need to go to abordage -->
	    case "Boal_Stay":
            //SetCharacterTask_Stay(Characters[Npchar.index]); // it's a mistic but here doesn't work :(
            //Log_SetStringToLog(Npchar.id +" "+Npchar.index);
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
		    Diag.TempNode = "Hired";
		    dialog.text = "Sim, senhor, Capitão!";
		    Link.l1 = "À vontade.";
		    Link.l1.go = "Exit";
		    Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
	    break;
		
	    case "Boal_Follow":
		    SetCharacterTask_FollowCharacter(Npchar, PChar); // it works here!!!
		    Diag.TempNode = "Hired";
		    dialog.text = "Sim, senhor, Capitão!";
		    Link.l1 = "À vontade.";
		    Link.l1.go = "Exit";
	    break;
        // boal 05.09.03 offecer need to go to abordage <--

		//////////////////////////////    офицер-наместник -->
		case "Gover_Hire":
            dialog.Text = "Capitão! Seria uma honra!";
            Link.l1 = "Mantenha a ordem e faça a cidade prosperar, e de vez em quando eu voltarei para recolher as tarifas.";
			Link.l1.go = "Exit_Gover_Hire";
            Link.l2 = "Mudei de ideia.";
            Link.l2.go = "Exit";
            Diag.TempNode = "Hired";
        break;

        case "Exit_Gover_Hire":
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
            attr = sld.id + "_townhall";

            // снимем пассажира -->
			CheckForReleaseOfficer(sti(NPChar.index));
			RemovePassenger(pchar, NPChar);
			// снимем пассажира <--
		    sld.OfficerIdx = sti(NPChar.index);
			ChangeCharacterAddressGroup(NPChar, attr, "sit", "sit1");
			LAi_SetHuberTypeNoGroup(NPChar);
            SaveCurrentNpcQuestDateParam(NPChar, "StartTaxDate");
            SaveCurrentNpcQuestDateParam(NPChar, "GoverTalkDate");
            LAi_LoginInCaptureTown(NPChar, true);
			//  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
            AddQuestRecordInfo("Gen_CityCapture", "t3_1");
			AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + sld.id));
			AddQuestUserData("Gen_CityCapture", "sName", GetFullName(NPChar));
			//  СЖ <--
			Diag.CurrentNode = "Gover_Main";
            DialogExit();
        break;

        case "Gover_Main":
            iTemp = GetNpcQuestPastDayParam(NPChar, "GoverTalkDate");
            if (iTemp > 0)
            {
				dialog.Text = "Quais são suas ordens? Da última vez que você me visitou "+FindRussianDaysString(iTemp)+" atrás.";
			}
			else
			{
			    dialog.Text = "Quais são suas ordens?";
			}

            Link.l1 = "Quanto dinheiro de imposto você já "+NPCharSexPhrase(NPChar,"coletado","coletado")+" neste ponto?";
        	Link.l1.go = "Gover_Tax";
            Link.l8 = "Você é necessário no navio, estou te dispensando do serviço na cidade.";
            Link.l8.go = "Gover_Fire";
			Link.l9 = "Tudo de bom.";
            Link.l9.go = "Exit";
            Diag.TempNode = "Gover_Main";
            SaveCurrentNpcQuestDateParam(NPChar, "GoverTalkDate");
        break;

        case "Gover_Tax":
            iTemp = GetNpcQuestPastDayParam(NPChar, "StartTaxDate");
            iTax  = makeint((GetCharacterSkillSimple(NPChar, SKILL_COMMERCE) + GetCharacterSkillSimple(NPChar, SKILL_LEADERSHIP)) / 2);
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
			if (CheckAttribute(sld, "FortValue"))
			{
			    iFortValue = sti(sld.FortValue);
			}
			else
			{
			    iFortValue = 20;
			}
			NPChar.Gover_Tax_Sum = iFortValue*iTax*iTemp;
			dialog.Text = "Minhas habilidades me permitem coletar "+FindRussianMoneyString(iFortValue*iTax)+" Por dia. Acabou "+FindRussianDaysString(iTemp)+" Eu "+NPCharSexPhrase(NPChar,"coletado","coletado")+" "+FindRussianMoneyString(sti(NPChar.Gover_Tax_Sum))+".";
			if (sti(NPChar.Gover_Tax_Sum) > 0)
			{
			    Link.l1 = "Quero pegar todo o dinheiro de impostos arrecadado.";
            	Link.l1.go = "Gover_Tax_Get";
			}
			Link.l2 = "Obrigado pelo serviço!";
            Link.l2.go = "Exit";
        break;

        case "Gover_Tax_Get":
            SaveCurrentNpcQuestDateParam(NPChar, "StartTaxDate");
            AddMoneyToCharacter(Pchar, sti(NPChar.Gover_Tax_Sum));

			Diag.CurrentNode = "Gover_Main";
            DialogExit();
        break;

        case "Gover_Fire":
            dialog.Text = "Ótimo! Não sou nenhum novato em terra firme, viu.";
            Link.l8 = "Isso é bom.";
            Link.l8.go = "exit_hire";
            Diag.TempNode = "Hired";
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
            DeleteAttribute(sld, "OfficerIdx");
            //  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
            AddQuestRecordInfo("Gen_CityCapture", "t3_2");
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + sld.id));
			AddQuestUserData("Gen_CityCapture", "sName", GetFullName(NPChar));
			//  СЖ <--
        break;
        //////////////////////////////    офицер-наместник <--

		//Указания для компаньона 19.02.08 -->
		case "Companion_Tasks":
			dialog.Text = "Estou ouvindo você.";
			Link.l1 = "Isso é sobre abordagens.";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "Isto é sobre o seu navio.";
			Link.l2.go = "Companion_TaskChange";
			if(bBettaTestMode) // Только при бета-тесте
			{
			    Link.l3 = "Quero que você deixe meu esquadrão por um tempo e vá buscar sua sorte sozinho.";
			    Link.l3.go = "CompanionTravel";
			}
			Link.l8 = "Nada até agora.";
			Link.l8.go = "exit";
		break;
		
		case "Companion_TaskBoarding":
			dialog.Text = "Então, qual é o seu desejo?";
			Link.l1 = "Não aborde navios inimigos. Cuide de você e da tripulação.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "Quero que você aborde navios inimigos.";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;
		
		case "Companion_TaskChange":
			dialog.Text = "Então, qual é o seu desejo?";
			Link.l1 = "Eu preferiria que você não trocasse seu navio por outro depois de embarcar. Ele é valioso demais.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "Quando você embarca em navios inimigos, pode ficar com eles para você, se valerem a pena.";
			Link.l2.go = "Companion_TaskChangeYes";
		break;
		
		case "Companion_TaskBoardingNo":
			dialog.Text = "Sim, senhor, Capitão.";
			Link.l1 = "À vontade.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;
		
		case "Companion_TaskBoardingYes":
			dialog.Text = "Vai ser feito, Capitão.";
			Link.l1 = "À vontade.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;
		
		case "Companion_TaskChangeNo":
			dialog.Text = "Sim, senhor, Capitão.";
			Link.l1 = "À vontade.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;
		
		case "Companion_TaskChangeYes":
			dialog.Text = "Vai ser feito, Capitão.";
			Link.l1 = "À vontade.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
		//<--
	
		// Самостоятельное плавание компаньона -->
		case "CompanionTravel":
			if(GetAttrValue(PChar, "CompanionTravel") == 3) // Если уже троих отпустил
			{
				dialog.Text = "Capitão, não vou deixar seu esquadrão, porque você já dispensou três navios.";
					Link.l1 = "Sim, talvez você esteja certo.";
					Link.l1.go = "exit";
				break;
			}
		
			dialog.Text = "Sem problema, capitão. Em qual cidade vamos nos encontrar?";
			for(iTemp=0; iTemp<MAX_COLONIES; iTemp++)
			{
				sld = &colonies[iTemp];
				attr = sld.ID;
				if(sld.nation == "none" || sld.nation == PIRATE || attr == "Panama" || attr == "FortOrange") continue;
				attrLoc = "l" + iTemp;
				Link.(attrLoc) = "In the " + XI_ConvertString("Colony" + attr + "Dat");
				Link.(attrLoc).go = "CompanionTravelToColony_" + attr;
			}
				Link.l99 = "Mudei de ideia.";
				Link.l99.go = "exit";
		break;
			
		case "CompanionTravel_EnemyColony":
			dialog.Text = "Capitão, mas eu não posso esperar por você na colônia, que é hostil a nós!";
				Link.l1 = "Sabe, esquece todas essas viagens...";
				Link.l1.go = "exit";
		break;
			
		case "CompanionTravel_NoCrew":
			dialog.Text = "Capitão, quase não temos marinheiros na tripulação! Que viagem é essa de que você está falando?!";
				Link.l1 = "É isso mesmo, estamos realmente com poucos marinheiros...";
				Link.l1.go = "exit";
		break;
			
		case "CompanionTravel_NoFood":
			dialog.Text = "Capitão, não tenho provisões suficientes a bordo para uma viagem dessas.";
				Link.l1 = "É, você tem razão. A viagem pode esperar...";
				Link.l1.go = "exit";
		break;
			
		case "CompanionTravel_NoHP":
			dialog.Text = "Capitão, mas meu navio está em péssimas condições. Seria imprudente zarpar sozinho nessas circunstâncias!";
				Link.l1 = "Sim, você está certo. Seu navio precisa de reparos.";
				Link.l1.go = "exit";
		break;
		
		case "CompanionTravel_PrepareStart":
			dialog.Text = "Entendi. Até "+XI_ConvertString("Colony"+characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID+"Gen")+" ir "+sti(characters[sti(NPChar.realcompanionidx)].CompanionTravel.Days)+" dias, o que devo fazer quando chegar?";
				Link.l1 = "Fique ancorado no porto da colônia por um mês.";
				Link.l1.go = "CompanionTravel_PrepareStart_2";
				Link.l2 = "Sabe, já pensei nisso. Fique comigo...";
				Link.l2.go = "exit";
		break;
		
		case "CompanionTravel_PrepareStart_2":
			dialog.Text = "Entendi, capitão. Partirei imediatamente.";
				Link.l1 = "Sim, por favor, faça isso.";
				Link.l1.go = "CompanionTravel_Start";
		break;
			
		case "CompanionTravel_Start":
			Diag.CurrentNode = "CompanionTravel_LastNode";
			NPChar.quest.meeting = true;
			CompanionTravel_SetTraveller(NPChar);
			DialogExit();
		break;
			
		case "CompanionTravel_LastNode":
			Dialog.text = RandPhraseSimple("Hoje, vou zarpar novamente...","Não se esqueça do nosso encontro em "+XI_ConvertString("Colony"+characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID+"Dat")+".");
				link.l2 = "...";
				link.l2.go = "Exit";
				Diag.TempNode = "CompanionTravel_LastNode";
		break;
			
		case "CompanionTravel_ToSquadron":
			if(GetCompanionQuantity(PChar) < COMPANION_MAX)
			{
				dialog.text = "Eu também gostaria disso. De agora em diante, meu navio está novamente sob seu comando, capitão.";
					Link.l1 = "Certo.";
					Link.l1.go = "exit";
					Diag.TempNode = "hired";
					CompanionTravel_DeleteSpecialShipAttributes(NPChar);
					Group_DeleteAtEnd(NPChar.CompanionTravel.GroupID); // Потрем группу
					SetCompanionIndex(PChar, -1, sti(NPChar.index));
					PChar.CompanionTravel = sti(PChar.CompanionTravel) - 1; // Этого компаньона взяли обратно в эскадру
					DeleteAttribute(NPChar, "CompanionTravel");
			}
			else
			{
				dialog.text = "Capitão, você já tem cinco navios no seu esquadrão – o que vai fazer com um sexto? Olha, acho melhor eu esperar aqui no meu navio. Esses seus novos companheiros não me parecem confiáveis. Os navios deles logo vão afundar, e você vai acabar voltando pra me buscar.";
					Link.l1 = "Olha só, você é esperto, hein? Devia ser almirante, não só capitão!";
					Link.l1.go = "exit";
					Diag.TempNode = "CompanionTravel_ToSquadron_2";
					NPChar.DeckDialogNode = "CompanionTravel_ToSquadron_2"; // ставим снова эту ноду
			}
		break;
			
		case "CompanionTravel_ToSquadron_2":
			dialog.text = "Oh, capitão, você voltou, como eu disse. Então, tem uma vaga no seu esquadrão agora?";
			if(GetCompanionQuantity(PChar) < COMPANION_MAX)
			{
				Link.l1 = "Sim, "+NPChar.name+", tem sim. Bem-vindo ao esquadrão.";
				Link.l1.go = "exit";
				Diag.TempNode = "hired";
				CompanionTravel_DeleteSpecialShipAttributes(NPChar);
				Group_DeleteAtEnd(NPChar.CompanionTravel.GroupID);
				SetCompanionIndex(PChar, -1, sti(NPChar.index));
				PChar.CompanionTravel = sti(PChar.CompanionTravel) - 1; // Этого компаньона взяли обратно в эскадру
				DeleteAttribute(NPChar, "CompanionTravel");
			}
			else
			{
				Link.l1 = "Ainda não, infelizmente.";
				Link.l1.go = "exit";
				Diag.TempNode = "CompanionTravel_ToSquadron_2";
				NPChar.DeckDialogNode = "CompanionTravel_ToSquadron_2";
			}
		break;
		// <-- Самостоятельное плавание компаньона
		
		case "tonzag_after_boarding":
			dialog.text = "Capitão, a situação está crítica! O inimigo nos mantém sob controle firme, e temo que não vão nos soltar até estarmos mortos! Nosso povo está em apuros de verdade agora, e a maioria das equipes dos canhões já foi derrubada!";
			link.l1 = "Eu vou ajudá-los. Assuma o comando e tire a gente daqui!";
			link.l1.go = "tonzag_after_boarding_1";
			DelLandQuestMark(npchar);
		break;
		
		case "tonzag_after_boarding_1":
			dialog.text = "Sim, senhor!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_GoToGunDeck");
		break;
		
		case "tonzag_after_victory":
			dialog.text = "Vitória, Capitão! O grupo de desembarque foi destruído, o inimigo decidiu recuar e seguir para o sul. O estado do navio é aceitável. Tripulação sobrevivente: "+GetCrewQuantity(pchar)+" pessoas. Relatório concluído!";
			link.l1 = "Obrigado! Rum para todos, e reforcem a vigilância até chegarmos ao porto!";
			link.l1.go = "tonzag_after_victory_1";
		break;
		
		case "tonzag_after_victory_1":
			dialog.text = "Viva! Sim, senhor!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_AlonsoBoardingDialog");
		break;
		
		// --> Эпилог
		case "SharlieEpilog_Folke_1": // Фульк
			dialog.text = "Então… chegou a hora de dizer adeus?";
			link.l1 = "Parece que sim. E, confesso, pensei que essa decisão seria mais fácil para mim.";
			link.l1.go = "SharlieEpilog_Folke_2";
		break;
		
		case "SharlieEpilog_Folke_2":
			dialog.text = "Então… obrigado por tudo, capitão. Vi muitos capitães, mas juro que você é o melhor de todos. Foi uma honra servir sob a sua bandeira.";
			link.l1 = "Você foi um oficial leal, "+npchar.name+". Obrigado pelo seu serviço. Espero que o destino ainda nos una… e não em lados opostos das barricadas.";
			link.l1.go = "SharlieEpilog_Folke_nothing";
			link.l2 = "Fico feliz de ouvir isso, amigo. É bom ouvir. Vou providenciar para que você receba sua carta de alforria com um salário. Obrigado pelos anos de serviço e pela sua lealdade. E sabe… acho que já é hora de você se tornar um capitão. Pense nisso.";
			link.l2.go = "SharlieEpilog_Folke_salary";
			link.l3 = "E obrigado a você também, parceiro. Você é um oficial excelente e habilidoso. Em sinal de agradecimento pela sua lealdade, vou providenciar para que receba três salários ao se despedir. E, "+npchar.name+", se eu descobrir que você acabou de novo nas masmorras por causa de dívidas… juro que deixo tudo, volto, te tiro de lá – e pessoalmente te deixo numa ilha deserta.";
			link.l3.go = "SharlieEpilog_Folke_salary_X3";
		break;
		
		case "SharlieEpilog_Folke_nothing":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Folke_exit");
		break;
		
		case "SharlieEpilog_Folke_salary":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Folke_exit");
			AddMoneyToCharacter(pchar, - sti(npchar.quest.OfficerPrice));
		break;
		
		case "SharlieEpilog_Folke_salary_X3":
			dialog.text = "Ha-ha, não, capitão, não piso mais na casa dos agiotas. Mas virar capitão é uma ideia interessante. Pra ser honesto, já pensei nisso mais de uma vez. Talvez eu realmente faça isso.";
			link.l1 = "E tem mais: quero fazer uma despedida na taverna. Espero que você apareça. Vai ser uma ótima chance de recrutar nossos homens para sua tripulação.";
			link.l1.go = "SharlieEpilog_Folke_salary_X3_2";
			AddMoneyToCharacter(pchar, -sti(npchar.quest.OfficerPrice) * 3);
		break;
		
		case "SharlieEpilog_Folke_salary_X3_2":
			dialog.text = "Eu certamente vou, capitão.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Folke_salary_X3_3";
		break;
		
		case "SharlieEpilog_Folke_salary_X3_3":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Folke_exit");
		break;
		
		case "SharlieEpilog_Duran_1":
			dialog.text = "Siiim, faz tempo mesmo – e isso é dizer pouco. Foi tanto tempo que nem lembro como se faz mais, haha.";
			link.l1 = "Então, talvez você goste do que eu tenho pra dizer. Veja bem, vou zarpar para o Velho Mundo. Não vejo meu pai há muito tempo, ele está preocupado – e pra ser sincero, eu também tô. Mas vou como passageiro. Num navio de outra pessoa.";
			link.l1.go = "SharlieEpilog_Duran_2";
		break;

		case "SharlieEpilog_Duran_2":
			dialog.text = "Como passageiro? Ora bolas.";
			link.l1 = "Quero ver se continuo nessa vida. Vai saber, talvez a sorte me abandone antes de eu estar preparado.";
			link.l1.go = "SharlieEpilog_Duran_3";
		break;

		case "SharlieEpilog_Duran_3":
			dialog.text = "Ah é? Hahaha. Não acredito que você vai largar o mar. Pode apostar – um verdadeiro lobo do mar em terra ou morre de tédio, ou se enforca de tristeza.";
			link.l1 = "É por isso que vou como passageiro – pra descobrir se posso viver assim quando chegar a hora. Mas o principal não é isso: eu não posso levar vocês comigo – e não posso fazer ninguém esperar. Eu mesmo não sei quando volto. Tenho certeza que meu pai quer que eu fique e cuide dos negócios da família.";
			link.l1.go = "SharlieEpilog_Duran_4";
		break;

		case "SharlieEpilog_Duran_4":
			dialog.text = "Quer dizer que agora cada um por si? Bem… cedo ou tarde isso ia acontecer de qualquer jeito. Só que eu não gosto de despedidas, então não espere lágrimas ou abraços de mim.";
			link.l1 = "Obrigado pelo serviço. Tenho certeza de que você vai se dar bem, mas tente não perder a cabeça antes de nos encontrarmos de novo.";
			link.l1.go = "SharlieEpilog_Duran_nothing";
			link.l2 = "Então ouça meu conselho – fique longe da sua velha profissão. Ela não lhe trará nada de bom. Aqui, pega um pouco de prata – vai te ajudar no começo. Não recomendaria você ir para soldado, mas entrar na guarda pessoal de algum capitão – é uma boa opção. Pense nisso.";
			link.l2.go = "SharlieEpilog_Duran_salary";
			link.l3 = "No lugar das lágrimas, vai ter prata. Haha, vejo seus olhos brilhando. Aqui, segura. Três meses de pagamento – dá pra beber com todos os piratas em Le François por uma semana. Ou, pra falar simples, dá pra viver por uns seis meses. Espero que você encontre o que fazer e como ganhar a vida.";
			link.l3.go = "SharlieEpilog_Duran_salary_X3";
		break;
		
		case "SharlieEpilog_Duran_nothing":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Duran_exit");
		break;
		
		case "SharlieEpilog_Duran_salary":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Duran_exit");
			AddMoneyToCharacter(pchar, - sti(npchar.quest.OfficerPrice));
		break;
		
		case "SharlieEpilog_Duran_salary_X3":
			dialog.text = "Já decidi. Vou virar buscador de tesouros. Tem algo nisso…";
			link.l1 = "Haha! Ótima escolha! E mais uma coisa: pretendo me divertir legal uma última vez. Então, se quiser se juntar – aparece na taverna.";
			link.l1.go = "SharlieEpilog_Duran_salary_X3_2";
			AddMoneyToCharacter(pchar, -sti(npchar.quest.OfficerPrice) * 3);
		break;
		
		case "SharlieEpilog_Duran_salary_X3_2":
			dialog.text = "Tá de brincadeira, capitão? Haha! Isso eu não perco por nada!";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Duran_salary_X3_3";
		break;
		
		case "SharlieEpilog_Duran_salary_X3_3":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Duran_exit");
		break;
		
		
		// <-- Эпилог
	}
}
