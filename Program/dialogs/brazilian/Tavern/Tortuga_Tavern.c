// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Todos os boatos sobre "+GetCityName(npchar.city)+" ao seu dispor. O que gostaria de saber?","Estávamos justamente falando sobre isso. Você deve ter esquecido...","Esta é a terceira vez hoje que você levanta essa questão...","Você está repetindo a mesma coisa como um papagaio...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sabe, "+NPChar.name+", talvez da próxima vez.","Certo, por algum motivo eu esqueci...","Sim, é mesmo a terceira vez...","É...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatTortuga") // работорговец
            {
                link.l1 = "Escuta, onde posso encontrar François Gontier? Ele já deveria ter chegado em Tortuga.";
                link.l1.go = "Tortuga_ratT_1";
            }
			// суп из черепахи
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tortuga" && !CheckAttribute(pchar, "questTemp.Tonzag.TerrapinBlock"))
			{
				link.l1 = "Estou procurando por Henri Thibaut. Onde posso encontrá-lo?";
				link.l1.go = "terrapin";
			}
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tortuga1" && !CheckAttribute(pchar, "questTemp.Tonzag.TerrapinBlock"))
			{
				link.l1 = "Estou procurando por Henri Thibaut. Onde posso encontrá-lo?";
				link.l1.go = "terrapin_2";
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "tortuga")
			{
				link.l1 = "Me diga, um galeão chamado 'Santa Margarita' parou na sua colônia recentemente? Talvez como prêmio de corso?";
                link.l1.go = "guardoftruth";
			}
			// Addon 2016-1 Jason Пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Jeweller"))
			{
				link.l1 = "Olha, camarada, estou procurando pelo Gaspard Parmentier. Onde posso encontrá-lo?";
                link.l1.go = "mtraxx_jew";
			}
			// Rebbebion, "Путеводная звезда"
			if (CheckAttribute(pchar, "questTemp.PZ.TortugaCitizensAsk") && !CheckAttribute(npchar, "quest.PZ.Ask.Block"))
			{
				link.l1 = "Pode me dar uma ajudinha, amigo? Estou procurando um homem chamado Joep van der Vink. Você conhece ele?";
				link.l1.go = "PZ_1";
			}
        break;
        
		case "Tortuga_ratT_1":
			dialog.text = "Francois Gontier? Quem é ele? Não conheço ninguém com esse nome.";
			link.l1 = "Ele é o capitão da corveta '"+pchar.questTemp.Slavetrader.ShipName+"'.";
			link.l1.go = "Tortuga_ratT_2";
        break;
		
		case "Tortuga_ratT_2":
			dialog.text = "Eu não faço a menor ideia. E posso garantir que nenhum navio com esse nome atracou no nosso porto.";
			link.l1 = "Certo então, você viu algum forasteiro pela cidade ultimamente?";
			link.l1.go = "Tortuga_ratT_3";
        break;
		
		case "Tortuga_ratT_3":
			dialog.text = "Boa pergunta! Aqui é uma cidade portuária, não uma vila. Estranhos passam por aqui todos os dias. Mas ouvi falar de cinco sujeitos esquisitos, eles andam sempre juntos e nunca largam as armas.\nA patrulha até perguntou sobre eles, mas não conseguiu nada. Mas tenho certeza de que eles não chegaram aqui em uma corveta, ninguém viu um navio desses por perto, entendeu?";
			link.l1 = "Hm... Tudo bem então, entendi. Obrigado, "+npchar.name+".";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_8");
			pchar.questTemp.Slavetrader = "wait1";//затычка
        break;
		
		// суп из черепахи
		case "terrapin":
			DelMapQuestMarkCity("SentJons");
			dialog.text = "Monsieur Thibaut é um homem famoso em Tortuga. A mansão dele fica perto da autoridade portuária. Ao sair da taverna, siga direto em direção ao porto. Quando chegar ao arco que leva ao porto, vire à esquerda no cruzamento e siga até o final da rua, onde você vai encontrar um prédio de pedra de dois andares com telhado vermelho. Essa é a mansão do Monsieur Thibaut.";
			link.l1 = "Obrigado! Vou lá visitar ele...";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			DialogExit();
			pchar.questTemp.Terrapin = "house";
			sld = characterFromId("Tibo");
			ChangeCharacterAddressGroup(sld, "Tortuga_houseS2", "barmen", "stay");
			LAi_SetOwnerType(sld);
		break;
		
		case "terrapin_2":
			dialog.text = "Monsieur Thibaut está muito requisitado hoje, até um mensageiro do governador acabou de aparecer por aqui. Ele também estava interessado. É tão difícil assim encontrá-lo? Faz tempo que ele aluga um quarto comigo no segundo andar, mesmo tendo uma mansão inteira para morar. Não sei pra que ele precisa disso, mas entra muito mais do que sai. E só aparece lá à noite.";
			link.l1 = "Talvez ele esteja aqui agora.";
			link.l1.go = "terrapin_3";
		break;
		
		case "terrapin_3":
			if (stf(environment.time) < 20.0 && stf(environment.time) > 8.0)
			{
				dialog.text = "Não. Ele disse que só voltaria às oito da noite. Você pode tentar procurá-lo na mansão dele, mas duvido que o encontre lá. Eu vi ele navegando num lugre de patrulha no mar.";
				link.l1 = "Obrigado! Vou passar lá para vê-lo mais tarde.";
				link.l1.go = "terrapin_4";
			}
			else
			{
				dialog.text = "Sim. Se quiser, pode subir.";
				link.l1 = "Obrigado! Vou lá visitar ele...";
				link.l1.go = "terrapin_4";
			}
		break;
		
		case "terrapin_4":
			DialogExit();
			pchar.questTemp.Terrapin = "tavern";
			sld = characterFromId("Tibo");
			sld.dialog.currentnode = "tibo_9";
			LAi_SetLoginTime(sld, 20.0, 8.0);
			ChangeCharacterAddressGroup(sld, "Tortuga_tavern_upstairs", "goto", "goto1");
			LocatorReloadEnterDisable("Tortuga_tavern", "reload2_back", false); // откроем комнату
			LAi_LocationFightDisable(&Locations[FindLocation("Tortuga_tavern_upstairs")], true);//запретить драться
			LAi_SetStayType(sld);
			// Addon 2016-1 Jason Пиратская линейка
			if (GetCharacterIndex("Mary") != -1)
			{
				sld = characterFromId("Mary");
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && !IsOfficer(sld))
				{
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
			}
			if (GetCharacterIndex("Helena") != -1)
			{
				sld = characterFromId("Helena");
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && !IsOfficer(sld))
				{
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Não faço ideia do nome do navio, era 'Santa Margarita' ou 'Puta Castelhana', mas trouxeram uma galé espanhola capturada. E foi um saveiro que pegou, acredita? Isso sim é navegar de verdade, porra! Gaius Marchais, o capitão, está se gabando há dois dias na taverna – primeira viagem dele e já volta com um prêmio desses!\nPois é, um feito heroico mesmo, abordar uma galé cheia de ratos de igreja sem um soldado pra proteger. Parece que esses papistas filhos da puta esqueceram o que dizem sobre quem ajuda a si mesmo...";
			link.l1 = "Sim, Deus ajuda quem cedo madruga, isso é mesmo um ditado huguenote. Como faço pra ver esse capitão sortudo? Ele está aqui, em Tortuga?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Ah, sei lá. Faz tempo que não vejo ele na minha taverna. Assim que ficou sóbrio, comprou um navio novinho com o dinheiro do prêmio e saiu correndo pelo convés feito um louco. Não faço ideia de onde o Marchais está agora. Talvez em Tortuga, talvez no mar.";
			link.l1 = "Certo. Bem, obrigado pela história, camarada!";
			link.l1.go = "guardoftruth_2";			
		break;
		
		case "guardoftruth_2":
			dialog.text = "Sempre que precisar, Monsieur. Estou sempre feliz em ajudar o nosso querido Capitão "+pchar.name+", salvador de St. Pierre! Passe aqui mais tarde!";
			link.l1 = "...";
			link.l1.go = "exit";	
			AddQuestRecord("Guardoftruth", "8");
			pchar.questTemp.Guardoftruth = "tortuga1";
		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		case "mtraxx_jew":
            dialog.text = "Parece que o Gaspard está ficando cada vez mais popular entre os seus. A casa dele fica perto do muro. Saia da taverna e vire à esquerda em direção ao porto, mas não vá até lá, vire à esquerda de novo, siga em frente e depois vire à direita. É uma casa de dois andares.";
			link.l1 = "Obrigado!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekJewellerHouse");
		break;
		
		case "PZ_1":
			dialog.text = "Nunca ouvi falar dele.";
			link.l1 = "Talvez ele use outro nome. Quem sabe você já ouviu falar dele como o capitão do brigue 'Banten'?";
			link.l1.go = "PZ_2";
		break;
		
		case "PZ_2":
			dialog.text = "Também nunca ouvi falar desse brigue.";
			link.l1 = "Ouvi dizer que ele esteve aqui recentemente. Talvez um pouco de prata ajude a refrescar sua memória?";
			link.l1.go = "PZ_3";
		break;
		
		case "PZ_3":
			npchar.quest.PZ.Ask.Block = true;
			
			dialog.text = "Bem, pergunte a si mesmo onde ouviu isso. Mas não me importo em aceitar sua prata.";
			link.l1 = "Sem prata desta vez, então. Adeus.";
			link.l1.go = "Exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
