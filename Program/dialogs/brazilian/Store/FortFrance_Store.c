// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Pode falar, o que você quer?","Estávamos justamente falando sobre isso. Você deve ter esquecido...","Já é a terceira vez hoje que você vem com alguma pergunta...","Olha, aqui é uma loja. As pessoas vêm comprar coisas. Não me atrapalhe!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sabe, "+NPChar.name+", talvez na próxima vez.","Certo, por algum motivo eu esqueci...","Sim, é mesmo a terceira vez...","Hm, eu não vou...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			/* //--> Бремя гасконца
			if (!CheckAttribute(npchar, "quest.storehelper") && pchar.questTemp.Sharlie == "ship")
			{
				Link.l1 = "Escute, monsieur, estou procurando um trabalho. Não um emprego fixo ou carregar carga, mas algo mais como fazer alguns serviços, por assim dizer. Por acaso precisa de alguma ajuda?";
				Link.l1.go = "Sharlie_storehelper";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "return")
			{
				Link.l1 = "Terminei sua tarefa. Encontrei Gralam Lavoie.";
				Link.l1.go = "Sharlie_storehelper_2";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "choise")
			{
				Link.l1 = "Conheça seu novo assistente, monsieur.";
				Link.l1.go = "Sharlie_storehelper_11";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "final")
			{
				Link.l1 = "Sou eu de novo, monsieur. Vim buscar minha recompensa.";
				Link.l1.go = "Sharlie_storehelper_13";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
			{
				link.l1 = "Dê uma olhada nesses brincos, monsieur. Encontrei-os no corpo de um bandido que foi morto na selva. É claramente obra de um joalheiro de talento, que tenho certeza não é daqui. Você pode me dizer algo sobre esses brincos?";
                link.l1.go = "Sharlie_junglejew";
			}
			//<-- Бремя гасконца */
		break;
		
		//--> Бремя гасконца
		case "Sharlie_storehelper":
			if (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) == "") 
			{
				dialog.text = "Com licença, senhor, mas onde está sua espada? Não é seguro sair da cidade sem uma lâmina. Nunca se sabe o que pode acontecer na selva!";
				link.l1 = "Droga, eu esqueci completamente! Levaram tudo embora!";
				link.l1.go = "Store_noweapon";
				break;
			}
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("Fortfrance_town", "reload", "reload6_back");
			dialog.text = "A job? Hm. I suppose I've got a job you might want. My assistant is missing; he used to work in my warehouse. He has been missing for a week already and this is damn annoying, because I am forced to do his duties and I don't have time.\nPlease, find this idiot and find out why the hell he abandoned his work. Or even better – bring him back to me. I'll pay you a thousand pieces of eight.";
			link.l1 = "Certo, estou dentro. Me diga o nome dele e descreva como ele é. Você faz ideia de onde posso procurá-lo?";
			link.l1.go = "Sharlie_storehelper_1";
			link.l2 = "Procurar um homem sabe-se lá onde por uma mixaria dessas? Só pode estar brincando!";
			link.l2.go = "Sharlie_storehelper_exit";
			npchar.quest.storehelper = "true";
		break;
		
		case "Sharlie_storehelper_exit":
			AddTimeToCurrent(2,0);
			LocatorReloadEnterDisable("Fortfrance_town", "reload10_back", false);// пу откр
			dialog.text = "Ei, monsieur. Quem está procurando trabalho, você ou eu? Se não quiser, não vou te forçar. Tenha um bom dia.";
			link.l1 = "Hm... Think I'll go check the port authority; perhaps they'll offer something more substantial there.";
			link.l1.go = "exit";
		break;
		
		case "Sharlie_storehelper_1":
			dialog.text = "Meu nome é Gralam Lavois. Aparência? Uns trinta e cinco anos, barba e bigode, casaco marrom comprido, camisa branca. Ah, e ele sempre usa aquele chapéu de abas levantadas ridículo, finge ser um almirante com uma âncora enfiada no traseiro. Ele não está em St. Pierre, já procurei pela cidade toda. Deve estar na selva ou em Les Francois, escondido com os piratas que rondam por lá. Por outro lado, é provável que esteja no assentamento pirata de Le Francois, que fica na parte leste da nossa ilha. Talvez esteja conversando com os piratas de lá, ou passando o tempo na taverna, ou discutindo com o comerciante local na loja. Como chegar a Le Francois? Saia pelos portões da cidade para a selva, no cruzamento, pegue o caminho da esquerda, depois siga pela estrada até virar à direita, então pegue a passagem à esquerda entre as pedras, e você vai encontrar Le Francois. Acho difícil você se perder.";
			link.l1 = "Certo. Vou começar a procurar. Assim que aparecer alguma coisa, aviso você na hora.";
			link.l1.go = "exit";
			AddQuestRecord("SharlieA", "1");
			pchar.questTemp.Sharlie.Storehelper = "true";
			pchar.questTemp.Sharlie.Storehelper.Chance = rand(2);
			AddDialogExitQuestFunction("Sharlie_CreateStorehelper");
			// Rebbebion, новые марки до места назначения
			QuestPointerToLoc("fortfrance_town", "reload", "gate_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload3_back");
			QuestPointerToLoc("lefransua_exittown", "reload", "reload1_back");
		break;
		
		case "Sharlie_storehelper_2":
			DelLandQuestMark(npchar);
			// Rebbebion, новые марки до места назначения
			QuestPointerDelLoc("lefransua_town", "reload", "gate_back");
			QuestPointerDelLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerDelLoc("fortfrance_town", "reload", "reload6_back");
			dialog.text = "Ah é? E onde ele está?";
			link.l1 = "Encontrei ele em Le Francois. Ele não vai mais trabalhar para você. E também tinha algumas coisas bem ácidas a dizer sobre você... Quer ouvir o que foi?";
			link.l1.go = "Sharlie_storehelper_3";
		break;
		
		case "Sharlie_storehelper_3":
			dialog.text = "Não. Poupe-me dos detalhes... Que pena! O que vou fazer agora sem um assistente?";
			link.l1 = "Contrate outra pessoa. Ou será que o problema é mesmo tão grande quanto o Gralam disse?";
			link.l1.go = "Sharlie_storehelper_4";
		break;
		
		case "Sharlie_storehelper_4":
			dialog.text = "Que azar dos grandes, de fato. E o que aquele vagabundo disse?";
			link.l1 = "Bem, para começar, ele claramente não está perdendo tempo, he-he. Ele disse que ninguém em todo Saint Pierre aceitaria trabalhar para você porque... você não paga o suficiente aos seus funcionários. Ah, e mais uma coisa, "+npchar.name+", você deve mil pesos, como prometido.";
			link.l1.go = "Sharlie_storehelper_5";
		break;
		
		case "Sharlie_storehelper_5":
			AddMoneyToCharacter(pchar, 1000);
			dialog.text = "Por favor, pegue seu dinheiro. Ha! Nunca é o bastante! Claro, ninguém quer trabalhar pra mim. Aquele desgraçado fez de tudo pra espalhar boatos imundos. O que eu posso fazer? Não posso fazer tudo sozinho!\nNão consigo dormir até contar cada peça da carga, porque aqueles malditos trabalhadores sempre roubam alguma coisa. Depois da última carga, estou com cinco barris de rum a menos. Tenho certeza de que os trabalhadores 'acidentalmente' levaram eles...";
			link.l1 = "Olha, não sei o que te aconselhar. Tudo bem, tudo de bom. Já está na hora de eu ir.";
			link.l1.go = "Sharlie_storehelper_6";
		break;
		
		case "Sharlie_storehelper_6":
			dialog.text = "Espere! Acho que você pode me ajudar. Se conseguiu encontrar aquele desgraçado, então talvez consiga também...";
			link.l1 = "E o que eu poderia fazer, me pergunto, se ninguém nesta cidade acredita em você? Sou novo aqui e...";
			link.l1.go = "Sharlie_storehelper_7";
		break;
		
		case "Sharlie_storehelper_7":
			dialog.text = "Deixe-me terminar, senhor. Você já esteve em Le Francois. Gostaria que fosse lá novamente e tentasse encontrar um funcionário para mim. Talvez Gralam não tenha destruído completamente minha reputação naquele antro de piratas\nO trabalho é simples – contar a carga e supervisionar os trabalhadores do porto para evitar furtos. Às vezes, fazer o meu trabalho aqui no meu lugar enquanto eu estiver fora, claro que por uma taxa extra\nDiga a eles que ofereço um quarto na loja para morar e quinhentas peças de oito por semana. Monsieur, estou planejando expandir meus negócios e as coisas finalmente estão indo bem, preciso de um assistente!\nAliás, é melhor pedir ajuda ao dono da taverna local, Cesare Craig, para encontrar um trabalhador. Aquele canalha com certeza vai te ajudar, embora não de graça, a encontrar alguém interessado em trabalhar para mim.";
			link.l1 = "Hm. Posso tentar, mas não tenho certeza... Quanto você vai me pagar por esse serviço?";
			link.l1.go = "Sharlie_storehelper_8";
		break;
		
		case "Sharlie_storehelper_8":
			dialog.text = "Isso vai depender de quem você conseguir contratar. Quanto melhor ele for, mais eu vou te pagar pelo esforço. Justo, não é?";
			link.l1 = "Você não acha que está me obrigando a agir no escuro? Como vou saber como você avalia um trabalhador? Você pode rotular qualquer um como ruim ou...";
			link.l1.go = "Sharlie_storehelper_9";
		break;
		
		case "Sharlie_storehelper_9":
			dialog.text = "Monsieur! Pode até ser justo me chamar de um pouco pão-duro, mas ninguém pode me acusar de desonesto! Se eu digo que vou pagar pelo seu esforço dependendo do resultado, é porque falo sério. Tente ver pelo meu lado também. Você pode acabar me trazendo algum cigano preguiçoso que, além de não fazer nada, ainda pode me roubar durante a noite!";
			link.l1 = "Tudo bem. Eu concordo. Vou confiar na sua palavra, "+npchar.name+". Vou ter certeza de não trazer nenhum cigano de volta.";
			link.l1.go = "Sharlie_storehelper_10";
		break;
		
		case "Sharlie_storehelper_10":
			DialogExit();
			SetLaunchFrameFormParam("Back to Le Francois...", "Reload_To_Location", 0, 3.0);
			SetLaunchFrameReloadLocationParam("LeFransua_tavern", "reload", "reload1", "SharlieA_TeleportLF");
			LaunchFrameForm();
		break;
		
		case "Sharlie_storehelper_11":
			dialog.text = "Você encontrou um trabalhador para mim? Maravilha. Deixe-me conversar com ele, volte em uma hora para receber sua recompensa.";
			link.l1 = "Tudo bem. Eu volto em uma hora.";
			link.l1.go = "Sharlie_storehelper_12";
			DelLandQuestMark(npchar);
		break;
		
		case "Sharlie_storehelper_12":
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.questTemp.Sharlie.Storehelper = "final";
			DialogExit();
			SetLaunchFrameFormParam("One hour passed...", "", 0, 5);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0); //крутим время
			RecalculateJumpTable();
			AddQuestRecord("SharlieA", "5");
			AddLandQuestMark(npchar, "questmarkmain");
		break;
		
		case "Sharlie_storehelper_13":
			switch (sti(pchar.questTemp.Sharlie.Storehelper.Quality))
			{
				case 0:
					AddMoneyToCharacter(pchar, 3000);
					dialog.text = "Estou bastante satisfeito com o trabalhador que você encontrou para mim, embora ele fale mais do que faz, mas não se preocupe, vou dar um jeito nesse falatório com o tempo. Sua recompensa são três mil peças de oito. Aqui está.";
					link.l1 = "Muito obrigado! Diga-me, Monsieur, você sabe se há mais alguém na cidade que precise de ajuda com algum assunto importante?";
					link.l1.go = "Sharlie_storehelper_14a";
				break;
				
				case 1:
					AddMoneyToCharacter(pchar, 5000);
					dialog.text = "Você conseguiu encontrar um trabalhador realmente valioso! Ele é até melhor do que aquele canalha do Gralam. Estou muito, muito satisfeito, senhor. Aqui, pegue sua recompensa – cinco mil peças de oito.";
					link.l1 = "Obrigado! Diga-me, Monsieur, você sabe se há mais alguém na cidade que precise de ajuda com algum assunto importante?";
					link.l1.go = "Sharlie_storehelper_14a";
				break;
				
				case 2:
					AddMoneyToCharacter(pchar, 4000);
					dialog.text = "Você encontrou um bom trabalhador. E embora ele ainda não saiba todos os segredos do ofício, tenho certeza de que vai aprender rápido, sem grandes dificuldades. Estou satisfeito com você, senhor. Aqui, receba sua recompensa – quatro mil peças de oito.";
					link.l1 = "Obrigado! Diga-me, Monsieur, você sabe se há mais alguém na cidade que precise de ajuda com algum assunto importante?";
					link.l1.go = "Sharlie_storehelper_14a";
				break;
			}
		break;
		
		case "Sharlie_storehelper_14a":
			LocatorReloadEnterDisable("Fortfrance_town", "reload10_back", false);// пу откр
			dialog.text = "Hmm... Just recently, I saw the port master, clearly upset, heading to the port authority. Check with him; who knows what might have happened.";
			link.l1 = "Vou fazer exatamente isso. Obrigado, Monsieur.";
			link.l1.go = "Sharlie_storehelper_14";
			DelLandQuestMark(npchar);
		break;
		
		case "Sharlie_storehelper_14":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Sharlie.Storehelper");
			CloseQuestHeader("SharlieA");
			
			QuestPointerDelLoc("lefransua_town", "reload", "gate_back");
			QuestPointerDelLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerDelLoc("fortfrance_town", "reload", "reload6_back");
			
			QuestPointerToLoc("fortfrance_town", "reload", "reload10_back");
		break;
		
		case "Sharlie_junglejew":
			dialog.text = "Bem, o que eu posso dizer, brincos magníficos. Posso te oferecer... vejamos... quatro mil peças de oito por eles. Duvido que alguém te ofereça mais. Negócio fechado?";
			link.l1 = "Fechado! São seus.";
			link.l1.go = "Sharlie_junglejew_1";
			link.l2 = "Não. Acho que vou ficar com essas joias para mim.";
			link.l2.go = "exit";
			npchar.quest.junglejew = "true";
		break;
		
		case "Sharlie_junglejew_1":
			DialogExit();
			PlaySound("interface\important_item.wav");
			Log_Info("You've given the earrings");
			RemoveItems(pchar, "jewelry25", 1);
			AddMoneyToCharacter(pchar, 4000);
			AddQuestRecord("SharlieE", "4");
			CloseQuestHeader("SharlieE");
			DeleteAttribute(pchar, "questTemp.Sharlie.Junglejew");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
			{
				DelLandQuestMark(characterFromId("FortFrance_Mayor"));
			}
		break;
		
		case "Store_noweapon":
			dialog.text = "Isso não vai servir. Sugiro que procure nosso governador e peça a ajuda dele.";
			link.l1 = "Obrigado pelo conselho. É exatamente isso que pretendo fazer.";
			link.l1.go = "exit";
		break;
		//<-- Бремя гасконца
	}
	UnloadSegment(NPChar.FileDialog2);
}
