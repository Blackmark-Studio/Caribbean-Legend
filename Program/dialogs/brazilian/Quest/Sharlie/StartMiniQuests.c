void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "O que você quer?";
			link.l1 = "Nada por enquanto.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		//Найти помощника в магазин
		case "Storehelper":
			DelLandQuestMark(npchar);
			dialog.text = "Precisa de alguma coisa, monsieur?";
			link.l1 = "Você é Gralam Lavoie, certo?";
			link.l1.go = "Storehelper_1";
		break;
		
		case "Storehelper_1":
			dialog.text = "Quem está perguntando? Não me incomode enquanto bebo rum, senhor. Não estou com vontade de conversar.";
			link.l1 = "Não vou tomar muito do seu tempo. Fui enviado aqui por um comerciante de Saint-Pierre. Você trabalhou para ele. Ele está procurando por você e...";
			link.l1.go = "Storehelper_2";
		break;
		
		case "Storehelper_2":
			dialog.text = "Ha, ele está me procurando!? Essa é boa, vindo daquele mão de vaca miserável! Ele achou mesmo que eu ia passar a vida inteira trabalhando por uma mixaria dessas? Ele é o maior pão-duro do Caribe! Ralei pra ele cinco anos e nunca vi um tostão a mais do que o mínimo possível! Bah, nem dava pra comprar uma bebida!\nAgora que conte ele mesmo as mercadorias dele, eu me demito. Ninguém em Saint-Pierre vai trabalhar pra esse sovina, disso eu tenho certeza. Ele só pensa em uma coisa – ganhar mais pra si e pagar menos pros outros.";
			link.l1 = "Imagino que você não vai voltar a trabalhar para ele?";
			link.l1.go = "Storehelper_3";
		break;
		
		case "Storehelper_3":
			dialog.text = "Não, que Deus me fulmine se eu estiver mentindo! Vou ficar aqui em Le François esperando algum navio chegar, aí tento embarcar como intendente, se me aceitarem. E se isso não der certo, viro marinheiro comum mesmo. Não suporto nem olhar praquele sanguessuga. Se é pra ser pobre, que seja sendo um homem livre...";
			link.l1 = "Entendi, era só isso que eu precisava saber. Boa sorte, Gralam!";
			link.l1.go = "Storehelper_12";
		break;
		
		case "Storehelper_4":
			DelLandQuestMark(npchar);
			dialog.text = "Senhor, afaste-se. Você está no meu caminho!";
			link.l1 = "Só uma pergunta, monsieur. Você é Gralam Lavoie?";
			link.l1.go = "Storehelper_5";
		break;
		
		case "Storehelper_5":
			dialog.text = "Ha! Sim, sou eu. O que você quer?";
			link.l1 = "Estão procurando por você, um comerciante de St. Pierre. Você já trabalhou para ele, não foi?";
			link.l1.go = "Storehelper_6";
		break;
		
		case "Storehelper_6":
			dialog.text = "Ha-ha! Que piada! E o que Sua Majestade Real quer comigo? Resolveu me pagar os salários atrasados das últimas duas semanas? Ou está com dificuldade de contar seus barris e enganar os clientes ao mesmo tempo, hein? Ha-ha-ha!";
			link.l1 = "Ele me pediu para procurar você e esclarecer por que você não está mais indo trabalhar na loja dele.";
			link.l1.go = "Storehelper_7";
		break;
		
		case "Storehelper_7":
			dialog.text = "Por quê? Porque ele é um verdadeiro pão-duro e um patrão horrível! Agora faço parte da Irmandade da Costa, sou um homem livre, não sou mais escravo de ninguém! Olhe ao redor, estou realmente aproveitando a vida!\nLogo vou zarpar e contar pesos e dobrões tirados dos espanhóis, em vez de caixas de bananas! E quanto àquele mão de vaca – duvido que ele encontre alguém para me substituir. Ninguém em Saint-Pierre é tolo o bastante para trabalhar pra ele, espalhamos a fama dele para todos os aprendizes da ilha, ha-ha!";
			link.l1 = "Entendi. Era só isso que eu precisava saber. Boa sorte, Gralam!";
			link.l1.go = "Storehelper_12";
		break;
		
		case "Storehelper_8":
			DelLandQuestMark(npchar);
			dialog.text = "Como posso ajudar você?";
			link.l1 = "Boa tarde. Gralam Lavoie, presumo?";
			link.l1.go = "Storehelper_9";
		break;
		
		case "Storehelper_9":
			dialog.text = "Sim. O que deseja, monsieur?";
			link.l1 = "Um comerciante de Saint-Pierre está te procurando. Você trabalhava para ele, não era?";
			link.l1.go = "Storehelper_10";
		break;
		
		case "Storehelper_10":
			dialog.text = "Bem, que ele continue procurando. Não devo nada a ele. Ele ainda me deve duas semanas de salário, mas nem vou me dar ao trabalho de cobrar. Tomara que ele engasgue com as próprias moedas.";
			link.l1 = "Hum. Então você o deixou de vez, estou certo?";
			link.l1.go = "Storehelper_11";
		break;
		
		case "Storehelper_11":
			dialog.text = "You got everything right, sirrah. My former employer is a rare specimen of miser, truly Biblical in scale. I'm a Brother of the Coast now and my talents are well esteemed by my new mates. I get twice as much, plus bonuses\nI doubt that our dear friend will find anyone to replace me. His greed is well-known to the people of Saint-Pierre; no one there is foolish enough to work for him.";
			link.l1 = "Entendi. Era só isso que eu precisava saber. Boa sorte, Gralam!";
			link.l1.go = "Storehelper_12";
		break;
		
		case "Storehelper_12":
			DialogExit();
			npchar.lifeday = 0;
			AddQuestRecord("SharlieA", "2");
			pchar.questTemp.Sharlie.Storehelper = "return";
			LAi_CharacterDisableDialog(npchar);
			pchar.quest.StorehelperOver.over = "yes"; //снять таймер
			
			pchar.quest.Sharlie_JungleBandos.win_condition.l1 = "location";
			pchar.quest.Sharlie_JungleBandos.win_condition.l1.location = "Martinique_Jungle_01";
			pchar.quest.Sharlie_JungleBandos.function = "SharlieJungleBandos";
			
			QuestPointerToLoc("lefransua_town", "reload", "gate_back");
			QuestPointerToLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerToLoc("fortfrance_town", "reload", "reload6_back");
			AddLandQuestMark(characterFromId("FortFrance_trader"), "questmarkmain");
			QuestPointerDelLoc("fortfrance_town", "reload", "gate_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload3_back");
			QuestPointerDelLoc("lefransua_exittown", "reload", "reload1_back");
		break;
		
		case "Newstorehelper_1":
			dialog.text = "Olá, monsieur. Não quero parecer atrevido, mas acredito que minha candidatura seria uma ótima escolha para a vaga que está oferecendo.";
			link.l1 = "Boa tarde.   E por que você acha isso?";
			link.l1.go = "Newstorehelper_1_1";
		break;
		
		case "Newstorehelper_2":
			dialog.text = "Saudações, senhor! Permita-me contar um pouco sobre mim.";
			link.l1 = "Pode falar, estou ouvindo.";
			link.l1.go = "Newstorehelper_2_1";
		break;
		
		case "Newstorehelper_3":
			dialog.text = "Saúde para você, caro senhor. Está oferecendo uma vaga de mercador?";
			link.l1 = "Sim, sou eu. O que pode me contar sobre você?";
			link.l1.go = "Newstorehelper_3_1";
		break;
		
		case "Newstorehelper_1_1":
			dialog.text = "Fui imediato sob o comando do próprio Capitão Francis Dubois. Ele ficou bastante satisfeito com minhas habilidades, mas acabei me ferindo em batalha e precisei me afastar para me recuperar. Agora estou bem, completamente recuperado, mas só de pensar nas ondas do mar já me dá enjoo. Não, meu único desejo agora é ficar em terra firme\n(sussurrando) E se você me escolher, eu pago quinhentos pesos e mais vinte e cinco dobrões de ouro.";
			link.l1 = "Entendi. Vou pensar nisso.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Newstorehelper_1_2";
		break;
		
		case "Newstorehelper_2_1":
			dialog.text = "Eu era um mascate, mas precisei fugir de alguns credores e acabei indo para o mar como intendente em um navio mercante. O destino me trouxe até esta vila. Para ser sincero, nunca gostei muito da vida de marinheiro mesmo, então ficarei feliz em aceitar sua proposta\n(sussurrando) E se você me escolher, vou te dar não só quinhentos pesos, mas também este pacote pesado de âmbar.";
			link.l1 = "Entendi. Vou pensar nisso.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Newstorehelper_2_2";
		break;
		
		case "Newstorehelper_3_1":
			dialog.text = "Eu era escriturário em um dos armazéns do porto em Glasgow. Vim para o Caribe em busca de riqueza e consegui juntar dinheiro suficiente para viver minha velhice com dignidade. Mas me cansei das viagens pelo mar e gostaria de levar uma vida tranquila em terra firme\n(sussurrando) E se você me escolher, eu te dou quinhentos pesos mais um bônus de dois mil e quinhentos pesos.";
			link.l1 = "Entendi. Vou pensar nisso.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Newstorehelper_3_2";
		break;
		
		case "Newstorehelper_1_2":
			dialog.text = "Monsieur, faça a escolha certa. E não se esqueça dos dobrões...";
			link.l1 = "Decidi a seu favor. Controle-se. Vamos para Saint-Pierre.";
			link.l1.go = "Newstorehelper_1_3";
			link.l2 = "Ainda não decidi...";
			link.l2.go = "exit";
			NextDiag.TempNode = "Newstorehelper_1_2";
		break;
		
		case "Newstorehelper_2_2":
			dialog.text = "Espero que escolha a mim, monsieur. E o âmbar também é algo bastante valioso e útil...";
			link.l1 = "Decidi a seu favor. Prepare-se. Vamos para Saint-Pierre.";
			link.l1.go = "Newstorehelper_2_3";
			link.l2 = "Ainda não decidi...";
			link.l2.go = "exit";
			NextDiag.TempNode = "Newstorehelper_2_2";
		break;
		
		case "Newstorehelper_3_2":
			dialog.text = "O mercador não vai se decepcionar com o meu trabalho. E não se esqueça do seu bônus.";
			link.l1 = "Decidi a seu favor. Reaja. Vamos para Saint-Pierre.";
			link.l1.go = "Newstorehelper_3_3";
			link.l2 = "Ainda não decidi...";
			link.l2.go = "exit";
			NextDiag.TempNode = "Newstorehelper_3_2";
		break;
		
		case "Newstorehelper_1_3":
			dialog.text = "Deixe só eu juntar minhas coisas! Vou te esperar na entrada da taverna.";
			link.l1 = "...";
			link.l1.go = "Newstorehelper_exit";
			pchar.questTemp.Sharlie.Storehelper.Quality = 0;
		break;
		
		case "Newstorehelper_2_3":
			dialog.text = "Já vou, monsieur! Estarei esperando você na entrada da taverna.";
			link.l1 = "...";
			link.l1.go = "Newstorehelper_exit";
			pchar.questTemp.Sharlie.Storehelper.Quality = 1;
		break;
		
		case "Newstorehelper_3_3":
			dialog.text = "Vou pegar minha velha valise e esperar você na entrada da taverna, senhor!";
			link.l1 = "...";
			link.l1.go = "Newstorehelper_exit";
			pchar.questTemp.Sharlie.Storehelper.Quality = 2;
		break;
		
		case "Newstorehelper_exit":
			DialogExit();
			pchar.questTemp.Sharlie.Storehelper.id = npchar.id;
			DeleteAttribute(npchar, "LifeDay")
			for (i=1; i<=3; i++)
			{
				sld = characterFromId("Newstorehelper_"+i);
				ChangeCharacterAddressGroup(sld, "none", "", "");
			}
			pchar.quest.storehelper4.win_condition.l1 = "location";
			pchar.quest.storehelper4.win_condition.l1.location = "FortFrance_store";
			pchar.quest.storehelper4.function = "NewstorehelperRegard";
			AddQuestRecord("SharlieA", "4");
			pchar.questTemp.Sharlie.Storehelper = "choise";
			pchar.quest.storehelper.over = "yes"; //снять прерывание
			
			AddLandQuestMark(characterFromId("FortFrance_trader"), "questmarkmain");
			
			SetLaunchFrameFormParam("Back to Saint-Pierre...", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("FortFrance_store", "reload", "reload1", "");
			LaunchFrameForm();
		break;
		
		case "Newstorehelper_regard":
			dialog.text = "Então, é aqui que vou trabalhar a partir de agora? Obrigada, monsieur, por me escolher. Aqui estão seus quinhentos pesos e o bônus prometido.";
			link.l1 = "Minha gratidão... Permita-me apresentar-lhe seu empregador.";
			link.l1.go = "Newstorehelper_regard_1";
		break;
		
		case "Newstorehelper_regard_1":
			DialogExit();
			npchar.lifeday = 0;
			switch (sti(pchar.questTemp.Sharlie.Storehelper.Quality))
			{
				case 0:
					AddMoneyToCharacter(pchar, 500);
					TakeNItems(pchar, "gold_dublon", 25);
				break;
				
				case 1:
					AddMoneyToCharacter(pchar, 500);
					TakeNItems(pchar, "jewelry8", 10);
					TakeNItems(pchar, "jewelry7", 1);
				break;
				
				case 2:
					AddMoneyToCharacter(pchar, 3000);
				break;
			}
		break;
		
		//контрабанда рома
		case "Rum_Cap_Over":
			dialog.text = "Monsieur, peço que saia do meu navio imediatamente. Estamos levantando âncora e partindo!";
			link.l1 = "Certo...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rum_Cap_Over";
			chrDisableReloadToLocation = false;
			npchar.DontDeskTalk = true;
			LAi_LocationFightDisable(&Locations[FindLocation("Deck_Near_Ship")], false);
		break;
		
		case "Rum_Cap":
			pchar.quest.Sharlie_rum2.over = "yes"; //снять таймер
			chrDisableReloadToLocation = false; // patch-4
			dialog.text = "E então? Quem é você, afinal?";
			//link.l1.edit = 1;			
			link.l1 = ""+pchar.questTemp.Sharlie.Rum.Pass+"!";
			link.l1.go = "Rum_Cap_1";
		break;
		
		case "Rum_Cap_1":
			dialog.text = "Tome um gole de rum, marinheiro! Ha-ha! Bem-vindo ao meu lugre. Veio atrás da mercadoria?";
			link.l1 = "Sim. Por que mais eu estaria aqui?";
			link.l1.go = "Rum_Cap_2";
			/* if(GetStrSmallRegister(pchar.questTemp.Sharlie.Rum.Pass) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = "Tome um gole de rum, marinheiro! Ha-ha! Bem-vindo ao meu lugre. Veio atrás da mercadoria?";
				link.l1 = "Sim. Por que mais eu estaria aqui?";
				link.l1.go = "Rum_Cap_2";
			}
			else
			{
				dialog.text = "Mas vejam só, que filhinho de mamãe mais verde! Rapazes, esse aqui parece um recruta fresco! Vamos jogá-lo ao mar!";
				link.l1 = "Hup!";
				link.l1.go = "Rum_Cap_getout";
			} */
		break;
		
		case "Rum_Cap_getout":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Deck_Near_Ship")], false);
			setCharacterShipLocation(pchar, "Shore38"));
			setWDMPointXZ("Shore38");
			DoQuestReloadToLocation("Shore38", "goto", "goto1", "Rum_RemoveBarkas");
		break;
		
		case "Rum_Cap_2":
			dialog.text = "Rapazes! Carreguem as caixas no bote!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Rum_CarrierEnter");
		break;
		
		case "Rum_Cap_3":
			dialog.text = "Todas as caixas de rum estão no seu bote. Port Le Francois fica bem ao sul daqui. Apresse-se, está na hora de eu levantar âncora também!";
			link.l1 = "Não vamos perder tempo, senhores! Boa sorte!";
			link.l1.go = "Rum_Cap_4";
		break;
		
		case "Rum_Cap_4":
			dialog.text = "O mesmo pra você, camarada...";
			link.l1 = "...";
			link.l1.go = "Rum_Cap_5";
		break;
		
		case "Rum_Cap_5":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Deck_Near_Ship")], false);
			npchar.DontDeskTalk = true;
			NextDiag.CurrentNode = "Rum_Cap_Over";
			pchar.quest.Sharlie_rum4.win_condition.l1 = "Ship_location";
			pchar.quest.Sharlie_rum4.win_condition.l1.location = "LeFransua_town";
			pchar.quest.Sharlie_rum4.function = "Rum_RemoveRum";
			AddQuestRecord("SharlieB", "4");
			i = FindIsland("Martinique");
			Islands[i].EffectRadius = 3000;
			
			DoQuestFunctionDelay("MessageRum1", 1.0);
			//NewGameTip("Transport the rum to Le Francois. Keep sailing around the island.");
			pchar.questTemp.Rum.Tip2.Reload = "l4";
			
			Weather.Wind.Speed = 16.0;
			pchar.wind.speed = Weather.Wind.Speed;
			fWeatherSpeed = stf(Weather.Wind.Speed);//халява первого выхода
			
			Weather.Wind.Angle = PId2;
			pchar.wind.angle = Weather.Wind.Angle;
			fWeatherAngle = stf(Weather.Wind.Angle);//халява первого выхода
			
			pchar.quest.MessageRum2.win_condition.l1 = "ExitFromLocation";
			pchar.quest.MessageRum2.win_condition.l1.location = pchar.location;
			pchar.quest.MessageRum2.function = "MessageRum2";
		break;
		
		case "Rum_Carrier":
			dialog.text = "Estávamos esperando por você, monsieur. Como foi tudo? Trouxe as caixas?";
			link.l1 = "Foi tudo espetacular. As caixas de rum já estão no bote.";
			link.l1.go = "Rum_Carrier_1";
		break;
		
		case "Rum_Carrier_1":
			dialog.text = "Ótimo. Daqui em diante, deixamos com a gente. Vá para St. Pierre, até a taverna, para receber seu pagamento. Fique atento e tome cuidado na selva à noite.";
			link.l1 = "Tudo de bom, senhores.";
			link.l1.go = "Rum_Carrier_2";
		break;
		
		case "Rum_Carrier_2":
			DialogExit();
			for (i=1; i<=3; i++)
			{
				
				sld = characterFromId("Rum_Carrier2_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			}
			pchar.questTemp.Sharlie.Rum = "regard";
			i = FindLocation("Fortfrance_town");
			setCharacterShipLocation(pchar, GetCityFrom_Sea(locations[i].fastreload));
		    setWDMPointXZ(GetCityFrom_Sea(locations[i].fastreload));
			SetCurrentTime(23, 0);
			Sharlie_removeLocks("");
			// Rebbebion, новые марки до места назначения
			QuestPointerToLoc("lefransua_town", "reload", "gate_back");
			QuestPointerToLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerToLoc("fortfrance_town", "reload", "reload4_back");
			if(CheckAttribute(pchar, "questTemp.Sharlie.Gigolo")) QuestPointerToLocTime("fortfrance_town", "reload", "reload9_back", 23.0, 24.0);
			AddLandQuestMark(characterFromId("FortFrance_tavernkeeper"), "questmarkmain");
		break;
		
		//доставить девочку из борделя
		case "GigoloMan":
			DelLandQuestMark(npchar);
			dialog.text = "Boa tarde, monsieur! Preciso dizer, você não se parece nada com os trastes esfarrapados que costumam rondar nossa colônia. Pelo seu traje, deve ter vindo de longe... Chegou da Europa, foi isso?";
			link.l1 = "Exatamente, monsieur. "+GetFullName(pchar)+", ao seu dispor. O que deseja?";
			link.l1.go = "GigoloMan_1";
		break;
		
		case "GigoloMan_1":
			dialog.text = "Permita-me apresentar - "+GetFullName(npchar)+". Cheguei a este lugar terrível vindo da França há alguns anos. Mas isso não vem ao caso. Tenho um assunto muito delicado para tratar com você\nPor favor, entenda que, se eu não tivesse certeza de que você é um cavalheiro, jamais lhe pediria um favor desses.";
			link.l1 = "Por favor, diga o que deseja, monsieur. Se estiver ao meu alcance, é claro que tentarei ajudar.";
			link.l1.go = "GigoloMan_2";
		break;
		
		case "GigoloMan_2":
			dialog.text = "I am glad to hear that, monsieur de Maure. Now, how to put this delicately...There is a brothel in this town. A new girl appeared there recently; young, pale, blonde, stunningly beautiful! Now, I've been watching her for weeks and... got a very strong desire to spend some time with her in private\nBut my estate and status make it...inconvenient to visit such a place. Imagine the gossip!\nThat is why I am appealing to you. Plainly put, you are a newcomer to our island, people don't know you and they don't care about what you do... yet. You could do me a great favour, monsieur.";
			link.l1 = "Acho que entendi o que você quer dizer.";
			link.l1.go = "GigoloMan_3";
		break;
		
		case "GigoloMan_3":
			dialog.text = "I appreciate your discretion, monsieur. I cannot go to the girl, so the girl must come to me. At my house. I ask you to go to the brothel and make an arrangement with the madame so that she will allow you to organise a 'house call' with the blonde girl for one night.\nAurora will not refuse; she is well known for providing such services, although it always costs a bit more. After that, you shall bring the girl to my house. For payment, I will give you six thousand pesos. Aurora usually takes three thousand or three and a half thousand for one night with the girl at home. You may keep the extra as compensation for your troubles.";
			link.l1 = "Não parece muito complicado. Posso fazer isso.";
			link.l1.go = "GigoloMan_4";
			link.l2 = "Monsieur, levo minha reputação de cavalheiro tão a sério quanto você. Por favor, me perdoe, mas não posso atender ao seu pedido. Preciso recusar. Acho melhor eu ir até a taverna ver se o estalajadeiro tem algum trabalho para mim.";
			link.l2.go = "GigoloMan_exit";
		break;
		
		case "GigoloMan_exit":
			DialogExit();
			LocatorReloadEnterDisable("Fortfrance_town", "reload9_back", false);// бордель open
			LocatorReloadEnterDisable("Fortfrance_town", "reload9", false);// бордель
			LocatorReloadEnterDisable("Fortfrance_town", "reload4_back", false);// таверна
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			chrDisableReloadToLocation = false;
			QuestPointerToLoc("fortfrance_town", "reload", "reload4_back");
			SetCurrentTime(17, 30);
		break;
		
		case "GigoloMan_4":
			dialog.text = "I am damn glad to hear it. Now listen, the girl's name is Lucille. I ask you to deliver her to my place when it's dark, no earlier than eleven p.m., in order to avoid unwanted attention from any gawkers. Knock on the door, and I will open.\nMy house is located to the left of the governor's residence, facing away from it - a two-story mansion with a red roof. You can easily find it, and there's a shop nearby, too. Actually, I am heading to my house now; feel free to follow me to see what it looks like and where it is exactly, so you won't get lost at night.\n Regarding the matter at hand - here, take six thousand pesos. I expect you by the agreed-upon time!";
			link.l1 = "Fechado. Sua loira Lucille vai estar na sua porta hoje à noite.";
			link.l1.go = "GigoloMan_5";
		break;
		
		case "GigoloMan_5":
			DialogExit();
			AddMoneyToCharacter(pchar, 6000);
			AddQuestRecord("SharlieC", "1");
			AddQuestUserData("SharlieC", "sName", GetFullName(npchar));
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "houseSp1", "none", "", "", "", -1);
			LocatorReloadEnterDisable("Fortfrance_town", "houseSp1", true);
			npchar.lifeday = 0;
			pchar.questTemp.Sharlie.Gigolo = "start";
			pchar.questTemp.Sharlie.Gigolo.Rand1 = rand(1);
			pchar.questTemp.Sharlie.Gigolo.Rand2 = rand(1);
			LocatorReloadEnterDisable("Fortfrance_town", "reload9_back", false);// бордель open
			LocatorReloadEnterDisable("Fortfrance_town", "reload91", false);// бордель
			AddLandQuestMark(characterFromId("Fortfrance_hostess"), "questmarkmain");
			QuestPointerToLoc("fortfrance_town", "reload", "reload9_back");
			QuestPointerToLoc("fortfrance_brothel", "reload", "reload3");
			chrDisableReloadToLocation = false;
		break;
		
		case "GigoloGirl":
			if (npchar.quest.meeting == "0")
			{
				DelLandQuestMark(npchar);
				QuestPointerDelLoc("fortfrance_town", "reload", "reload9_back");
				dialog.text = "Bom dia, monsieur. Ora, foi o senhor quem me contratou esta noite? Olha só, devo dizer que sou uma moça de sorte por ter um cavalheiro tão bonito e bem-apessoado, nada parecido com os brutamontes que chegam dos cais fedendo a piche e suor...";
				link.l1 = "Me desculpe, mas não hoje à noite, Lucille. Estou aqui em nome de um bom amigo meu que, por uma série de razões bastante complicadas, não pode sair de casa, então vou levar você até ele. Agora, não fique chateada, ele é um homem gentil e tem muito carinho por você. Acho que, no fim das contas, você vai ficar feliz.";
				link.l1.go = "GigoloGirl_1";
				// belamour legendary edition -->
				link.l2 = "Uhm... Você tem toda razão, querido. Vamos?";
				link.l2.go = "GigoloGirl_1a";
				// <-- legendary edition
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Monsieur, espero que entenda que não posso simplesmente passear com você à noite. Precisa me levar logo à casa do seu amigo ou vou voltar direto para Madame e você vai jogar seu dinheiro fora.";
				link.l1 = "Certo, entendi. Me siga!";
				link.l1.go = "GigoloGirl_2";
			}
		break;
		// belamour legendary edition -->
		case "GigoloGirl_1a":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			chrDisableReloadToLocation = true; //закрыть локацию
			DoQuestReloadToLocation(pchar.location+"_room", "goto", "goto2", "GigoloGirl_Sex");
			ChangeCharacterAddressGroup(npchar, pchar.location+"_room", "goto", "goto1");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Rum"))
			{
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1 = "Hour";
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.start.hour = 6.00;
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.finish.hour = 22.00;
				pchar.quest.Sharlie_CreatShipyardMarker.function = "Sharlie_CreatShipyardMarker";
			}
		break;
		
		case "GigoloGirl_1":
			AddCharacterExpToSkill(pchar, "Fortune", 40);
		// <-- legendary edition
			dialog.text = "Que pena... Gostei de você logo de cara, monsieur. Teria adorado passar a noite com você... quem sabe numa próxima vez. Vamos?";
			link.l1 = "Sim. Venha comigo!";
			link.l1.go = "GigoloGirl_2";
		break;
		
		case "GigoloGirl_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.Sharlie_Gigolo.win_condition.l1 = "locator";
			pchar.quest.Sharlie_Gigolo.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Sharlie_Gigolo.win_condition.l1.locator_group = "reload";
			pchar.quest.Sharlie_Gigolo.win_condition.l1.locator = "houseSp1";
			pchar.quest.Sharlie_Gigolo.function = "Sharlie_GiveGigoloGirl";
			pchar.quest.Sharlie_Gigolo1.win_condition.l1 = "Timer";
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.hour  = sti(GetTime() + 2);
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.Sharlie_Gigolo1.function = "Sharlie_GigoloGirlOver";
			QuestPointerToLoc("fortfrance_town", "reload", "houseSp1");
		break;
		
		case "GigoloGirl_3":
			dialog.text = "Que casa magnífica. É aqui o lugar?";
			link.l1 = "Sim. Entre. Não tenha medo, meu amigo é um bom homem.";
			link.l1.go = "GigoloGirl_4";
		break;
		
		case "GigoloGirl_4":
			dialog.text = "Você me subestima, não tenho medo, monsieur. Sei muito bem me virar. Agora, quem sabe mais tarde você poderia pagar à Madame por uma noite comigo? Prometo que será a melhor noite da sua vida!";
			link.l1 = "Tudo é possível, Lucille. Talvez a gente se encontre de novo. Adeus!";
			link.l1.go = "GigoloGirl_5";
		break;
		
		case "GigoloGirl_5":
			pchar.quest.Sharlie_Gigolo1.over = "yes";
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "houseSp1", "none", "", "", "GigoloGirl_Remove", 5.0);
			QuestPointerDelLoc("fortfrance_town", "reload", "houseSp1");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Rum"))
			{
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1 = "Hour";
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.start.hour = 6.00;
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.finish.hour = 22.00;
				pchar.quest.Sharlie_CreatShipyardMarker.function = "Sharlie_CreatShipyardMarker";
			}
		break;
		
		//пираты с пленным испанцем
		case "CaptivePirate":
			pchar.quest.Captive_CreatePiratesOver.over = "yes";//снять таймер
			pchar.quest.Captive_CreatePiratesOver2.over = "yes";//снять таймер
			// Rebbebion, новые марки до места назначения
			QuestPointerDelLoc("fortfrance_town", "reload", "gate_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_03", "reload", "reload2_back");
			dialog.text = "O que é isso!? Quem é você? O que quer aqui? Anda, cai fora daqui!";
			link.l1 = "Você não é muito educado, rapaz.";
			link.l1.go = "CaptivePirate_1";
		break;
		
		case "CaptivePirate_1":
			dialog.text = "Escuta aqui, moleque, eu não fui criado pra ser educado, assim como nunca aprendi a ler nem escrever, mas abrir tua cabeça com um sabre é tão fácil pra mim quanto uma prostituta cair de costas. E juro pela minha alma que, se você não sair daqui agora, vai sair carregado. Entendeu?";
			link.l1 = "Não, agora quem escuta é você, seu canalha. Seu plano já foi descoberto. Eu preciso desse homem vivo, então largue as armas e fuja. Tem um destacamento de soldados franceses na mata logo atrás de mim. Se correrem rápido o bastante, talvez ainda consigam salvar essas vidas miseráveis de vocês.";
			link.l1.go = "CaptivePirate_3";
			link.l2 = "Tudo bem, tudo bem, calma. Eu já estou indo.";
			link.l2.go = "CaptivePirate_2";
		break;
		
		case "CaptivePirate_2":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			DialogExit();
			n = makeint(MOD_SKILL_ENEMY_RATE/2);
			if (n <= 1) n = 2;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("CaptivePirate_"+i);
				LAi_CharacterDisableDialog(sld);
				LAi_SetImmortal(sld, true);
				sld.lifeday = 0;
			}
			sld = characterFromId("CaptiveSpain");
			LAi_SetImmortal(sld, true);
			sld.lifeday = 0;
			pchar.quest.Sharlie_captive1.over = "yes";
			pchar.quest.Sharlie_captive2.over = "yes";//снять прерывание
			AddQuestRecord("SharlieD", "5");
			CloseQuestHeader("SharlieD");
			DeleteAttribute(pchar, "questTemp.Sharlie.Captive");
			pchar.questTemp.Sharlie = "bankskipermoney";
		break;
		
		case "CaptivePirate_3":
			dialog.text = "O quê? Você está blefando, camarada! Acabem com ele, rapazes, às armas!";
			link.l1 = "Então que recaia sobre sua cabeça, en garde!";
			link.l1.go = "CaptivePirate_4";
		break;
		
		case "CaptivePirate_4":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			int n = makeint(MOD_SKILL_ENEMY_RATE/2);
			if (n <= 1) n = 2;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("CaptivePirate_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Captive_PiratesDead");
			AddDialogExitQuest("MainHeroFightModeOn");	
			sld = characterFromId("CaptiveSpain");
			LAi_SetCitizenType(sld);
			DoQuestFunctionDelay("Ngt_CaptiveEng", 0.5);
		break;
		
		//пленный испанец
		case "CaptiveSpain":
			dialog.text = "Graças a Deus! Ah, você é francês? Merda, você enfrentou aqueles bandidos com estilo. Mas não pense que vou me render assim tão fácil, vou te mostrar como um espanhol luta! Santiago!";
			link.l1 = "Não, espere, por favor!";
			link.l1.go = "CaptiveSpain_1";
		break;
		
		case "CaptiveSpain_1":
			dialog.text = "Prefiro morrer a ser capturado pelos franceses. Peguei um sabre de um dos corpos enquanto você lutava... agora vou te fazer dançar uma quadrilha espanhola!";
			link.l1 = "Vocês espanhóis são teimosos como mulas!";
			link.l1.go = "CaptiveSpain_2";
		break;
		
		case "CaptiveSpain_2":
			DialogExit();
			LAi_SetPlayerType(pchar);
			NextDiag.currentnode = "CaptiveSpain_3";
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "CaptiveSpain_capture");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "CaptiveSpain_3":
			dialog.text = "Maldito... Você venceu. Eu me rendo, maldito francês. Estou à sua mercê.";
			link.l1 = "Guarde sua espada e me deixe falar, seu teimoso castelhano! Não quero que você morra, e também não vou te mandar para a prisão!";
			link.l1.go = "CaptiveSpain_4";
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
		break;
		
		case "CaptiveSpain_4":
			dialog.text = "Então o que você está fazendo? Por que matou os piratas? E onde estão seus soldados?";
			link.l1 = "Não há soldados. Tentei enganar aqueles canalhas, mas como você pode ver ao nosso redor, não funcionou. Estou aqui sozinho, a pedido do seu velho amigo. O nome dele é "+pchar.questTemp.Sharlie.Captive.Name+", ele é um banqueiro em St. Pierre.";
			link.l1.go = "CaptiveSpain_5";
		break;
		
		case "CaptiveSpain_5":
			dialog.text = ""+pchar.questTemp.Sharlie.Captive.Name+"? Eu não conheço ninguém com esse nome...";
			link.l1 = "Eu também não sabia nada sobre você ou seu cativeiro. Fiquei sabendo da sua transferência para um navio inglês por ele. Minha missão é entregar você a ele, e jurei que cumpriria isso! Agora, venha comigo se quiser viver.";
			link.l1.go = "CaptiveSpain_6";
		break;
		
		case "CaptiveSpain_6":
			dialog.text = "Também não tenho escolha... Esse seu banqueiro não pode ser pior do que os ingleses e aquela comida horrível deles...";
			link.l1 = "Finalmente você está tomando uma decisão sensata. Chega de conversa por agora, estamos indo para St. Pierre. Fique perto de mim e não se afaste. Se tentar fugir, eu te pego e te arrebento de novo.";
			link.l1.go = "CaptiveSpain_7";
		break;
		
		case "CaptiveSpain_7":
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "GenQuest.Notsearchbody"); // 170712
			DialogExit();
			AddQuestRecord("SharlieD", "6");
			LAi_group_Register("TempFriends");
			LAi_group_SetRelation("TempFriends", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "TempFriends");
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			SetNationRelation2MainCharacter(FRANCE, RELATION_ENEMY);
			pchar.quest.Sharlie_captive3.win_condition.l1 = "locator";
			pchar.quest.Sharlie_captive3.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Sharlie_captive3.win_condition.l1.locator_group = "reload";
			pchar.quest.Sharlie_captive3.win_condition.l1.locator = "reload8_back";
			pchar.quest.Sharlie_captive3.win_condition.l2 = "Night";
			pchar.quest.Sharlie_captive3.win_condition.l3 = "Alarm";
			pchar.quest.Sharlie_captive3.win_condition.l3.value = 0;
			pchar.quest.Sharlie_captive3.win_condition.l3.operation = "=";
			pchar.quest.Sharlie_captive3.function = "CaptiveSpain_reload";//вход ночью
			pchar.questTemp.Sharlie = "bankskipercaptive";
			SetFunctionLocationCondition("CaptiveSpain_removeGuard", "fortfrance_town", 0);
			SetFunctionLocationCondition("CaptiveSpain_saveTip", "fortfrance_exittown", 0);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_town")], false);
			// Rebbebion, новые марки до места назначения. belamour поправил - были не в ту сторону
			QuestPointerToLoc("shore39", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_03", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerToLoc("fortfrance_town", "reload", "reload8_back");
			AddLandQuestMark(characterFromId("FortFrance_Usurer"), "questmarkmain");
		break;
		
		//горожанин с пропавшей дочерью
		case "Prosper":
			DelLandQuestMark(npchar);
			pchar.quest.Sharlie_RescueDaughter.over = "yes"; //снять прерывание
			dialog.text = "O que deseja, monsieur? Não tenho tempo para conversa, então seja breve.";
			link.l1 = "Você é Prosper Trubal, não é?";
			link.l1.go = "Prosper_1";
		break;
		
		case "Prosper_1":
			dialog.text = "Sim, sou eu. Mas você está em vantagem. Por favor, me diga quem é você e o que diabos quer.";
			link.l1 = "Meu nome é "+GetFullName(pchar)+". Fui enviado até você por "+GetFullName(characterFromId("Fortfrance_portman"))+", o mestre do porto. Ele disse que você precisava de ajuda urgente...";
			link.l1.go = "Prosper_2";
		break;
		
		case "Prosper_2":
			dialog.text = "Meu Deus, sim! Aquele canalha de comandante nem sequer ouviu minha reclamação! Ou é preguiçoso demais ou covarde demais pra ajudar. Você veio mesmo aqui pra me ajudar? Se for isso, não vou deixar de te recompensar!";
			link.l1 = "Sim, Prosper. Conte-me o que aconteceu e o que devo fazer para ajudar. Ouvi dizer que sua filha desapareceu...";
			link.l1.go = "Prosper_3";
		break;
		
		case "Prosper_3":
			dialog.text = "Sim, minha querida filha Celene está desaparecida há dois dias. Ela saiu para passear até o forte, que não fica longe daqui. Mas não voltou, então fui até o forte eu mesma e os soldados me disseram que ela nunca esteve lá!\nMas então, na volta, fui atacada por dois índios selvagens! Eles pularam em cima de mim com porretes e tentaram me espancar.\nMas eu não sou nenhuma florzinha, então dei um soco na cara de um deles, o que me deu tempo suficiente para sacar minha pistola e atirar. Errei o tiro, mas consegui assustá-los. Consegui chegar aos portões da cidade e contei aos guardas sobre o ataque. Eles correram para a mata, mas os selvagens já tinham sumido fazia tempo.\nTenho certeza de que eles são os responsáveis pelo desaparecimento da Celene. Além disso, mais duas pessoas sumiram na última semana – Cesar Blanchet e Gilbert Courcy! Um estava indo para a baía e o outro para Le Francois. Nunca mais voltaram.";
			link.l1 = "Então os índios têm atacado os moradores bem nos portões da cidade? Isso é de uma ousadia inacreditável...";
			link.l1.go = "Prosper_4";
		break;
		
		case "Prosper_4":
			dialog.text = "Enquanto isso, fui sozinho para a selva procurar por ela e encontrei uma caverna ao norte da cidade. Achei aqueles desgraçados escondidos lá dentro. Vi vários índios na entrada, mas alguns deviam estar lá dentro também\nOuvi uma garota gritando... Era a minha Celene, tenho certeza, era a voz dela! Precisei de toda minha força para não entrar correndo naquele instante – as chances não estavam do meu lado e eles teriam me matado. Morto, eu não serviria de nada para ela.";
			link.l1 = "Mas por que diabos eles estão atacando e levando moradores como prisioneiros?";
			link.l1.go = "Prosper_5";
		break;
		
		case "Prosper_5":
			dialog.text = "Eu não sei... Talvez para vendê-los a piratas ou traficantes de escravos? Ou quem sabe vão simplesmente devorá-los vivos, afinal, são selvagens.";
			link.l1 = "Meu Deus do céu, eles são canibais? Achei que isso fosse só história pra assustar criança na Europa...";
			link.l1.go = "Prosper_6";
		break;
		
		case "Prosper_6":
			dialog.text = "Histórias? Bem, alguns homens como você pensaram o mesmo, até que os caribes os assaram na fogueira e comeram... Então, fui direto ao comandante e pedi uma expedição punitiva para salvar minha Celene. Ele recusou! Disse que, quando moças desaparecem, provavelmente fugiram com algum rapaz, não com índios. Sugeriu que eu procurasse por ela nos celeiros da região\nE quanto aos outros dois desaparecidos... disse que um deles era suspeito de contrabando, e o outro provavelmente está bebendo até morrer na taverna do Le François. Resumindo, não consegui nada e decidi agir por conta própria.";
			link.l1 = "O que você pretende fazer?";
			link.l1.go = "Prosper_7";
		break;
		
		case "Prosper_7":
			dialog.text = "Eu vou até lá e mato cada um daqueles malditos vermelhos. Só espero que Celene ainda esteja viva. Como pode ver, comprei uma mosquete — e sei atirar com ela. Paguei caro, mas não me importo nem um pouco\nMinha missão vai ser muito mais fácil se você for comigo. Juntos, podemos acabar com esses selvagens sem grandes problemas, se você cobrir minhas costas enquanto recarrego. Você vai comigo salvar minha filha?";
			link.l1 = "Claro! É uma questão de honra! Não posso simplesmente deixar uma moça morrer pela faca de algum selvagem.";
			link.l1.go = "Prosper_8";
			if (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) == "") {
				link.l1.go = "Prosper_noweapon";
			}
			link.l2 = "Hum. Sabe, acho que as palavras do comandante fazem sentido. Talvez devêssemos seguir o conselho dele primeiro?";
			link.l2.go = "Prosper_exit";
		break;
		
		case "Prosper_noweapon":
			dialog.text = "Monsieur, onde está sua espada?";
			link.l1 = "Parece que eu perdi isso de vista.";
			link.l1.go = "Prosper_noweapon_1";
		break;
		
		case "Prosper_noweapon_1":
			dialog.text = "That will simply not do. I will wait for you until evening; I advise you to grovel at the feet of our governor and beg for his assistance.";
			link.l1 = "Se ajoelhar aos pés dele, é? Bem, como quiser...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Prosper_getweapon";
			SetFunctionTimerConditionParam("RescueDaughter_Over", 0, 0, 0, 22, false);
		break;
		
		case "Prosper_getweapon":
			dialog.text = "E então, monsieur? Conseguiu arranjar uma arma?";
			if (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) == "") {
				link.l1 = "Ainda não, por favor espere só mais um pouco...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Prosper_getweapon";
			} else {
				link.l1 = "Entendi. Estou pronto para te ajudar!";
				link.l1.go = "Prosper_8";
				DeleteQuestCondition("RescueDaughter_Over");
			}
		break;

		case "Prosper_exit":
			dialog.text = "Meu Deus, está fugindo? Não! Cai fora daqui! Covarde!";
			link.l1 = "Ei, ei, calma aí, seu idiota! É melhor eu sair pra ver se algum nobre nas ruas de Saint-Pierre precisa de ajuda.";
			link.l1.go = "Prosper_exit_1";
			pchar.questTemp.Sharlie.GigoloMan.SamPodbezhit = true;
		break;
		
		case "Prosper_exit_1":
			DialogExit();
			npchar.lifeday = 0;
			//AddTimeToCurrent(2,0);
			SetCurrentTime(17,30);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "gate_back", "none", "", "", "", 10.0);
			CloseQuestHeader("SharlieF");
			chrDisableReloadToLocation = true;
			
			//Подбегает дворянин с квестом "девочка по вызову"
			sld = GetCharacter(NPC_GenerateCharacter("GigoloMan", "Guide_2", "man", "man", 25, FRANCE, 5, true, "soldier"));
			SetFantomParamFromRank(sld, 25, true);
			sld.Dialog.Filename = "Quest\Sharlie\StartMiniQuests.c";
			sld.dialog.currentnode = "GigoloMan";
			sld.greeting = "noble_male";
			AddLandQuestMark(sld, "questmarkmain");
			LAi_SetLoginTime(sld, 6.0, 21.0);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Fortfrance_town", "goto", "goto1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Prosper_8":
			dialog.text = "I'm glad there's at least one courageous man in this town. Here, take these three vials. These are health-giving herbs; I bought them from our herbalist. They can be a substantial help to you in battle.";
			link.l1 = "E você?";
			link.l1.go = "Prosper_9";
		break;
		
		case "Prosper_9":
			TakeNItems(pchar, "potion1", 3);
			PlaySound("interface\important_item.wav");
			dialog.text = "Não se preocupe, tenho mais. Está pronto?";
			link.l1 = "Sim, não vamos perder tempo. Em frente!";
			link.l1.go = "Prosper_10";
		break;
		
		case "Prosper_10":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_SetImmortal(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "fortfrance_exittown", "reload", "reload3", "OpenTheDoors", 10.0);
			PChar.quest.RescueDaughter_ProsperGateOutReload.win_condition.l1 = "location";
			PChar.quest.RescueDaughter_ProsperGateOutReload.win_condition.l1.location = "FortFrance_ExitTown";
			PChar.quest.RescueDaughter_ProsperGateOutReload.win_condition = "RescueDaughter_ProsperGateOutReload";
			AddQuestRecord("SharlieF", "3");
			pchar.quest.Sharlie_RescueDaughter1.win_condition.l1 = "location";
			pchar.quest.Sharlie_RescueDaughter1.win_condition.l1.location = "Martinique_jungle_04";
			pchar.quest.Sharlie_RescueDaughter1.function = "RescueDaughter_NearCave";
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1 = "Timer";
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.hour  = sti(GetTime()+2);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.Sharlie_RescueDaughter2.function = "RescueDaughter_CaveOver";
			NextDiag.CurrentNode = "Prosper_11";
			pchar.questTemp.Sharlie.RescueDaughter = "true";
			LocatorReloadEnterDisable("Fortfrance_exittown", "reload2_back", true);//форт
			LocatorReloadEnterDisable("Martinique_Jungle_01", "reload1_back", true);//джунгли
			LocatorReloadEnterDisable("Martinique_Jungle_04", "reload1_back", true);//джунгли
		break;
		
		case "Prosper_11":
			dialog.text = "Estamos quase na posição, "+pchar.name+". Depois desta curva fica a entrada da caverna. Chegue mais perto e eu te conto nosso plano.";
			link.l1 = "Estou todo ouvidos, Prosper.";
			link.l1.go = "Prosper_12";
		break;
		
		case "Prosper_12":
			dialog.text = "Preciso mirar com calma com esse mosquete pesado, mas se você me der cobertura, não vou errar. Se eu tiver que lutar corpo a corpo, esqueça qualquer apoio de fogo, só vou conseguir afastar os outros usando o cano como porrete. Essa luta vai depender da sua habilidade com a espada.";
			link.l1 = "O que você está tentando dizer?";
			link.l1.go = "Prosper_13";
		break;
		
		case "Prosper_13":
			dialog.text = "Tudo o que você precisa fazer é distrair a atenção deles para que eu possa atirar em todos. Não consigo me mover e atirar, então vou ficar parado em um lugar. Tem três canalhas perto da entrada da caverna. Você deve avançar contra eles o mais rápido possível, com a espada em mãos\nAtaque um deles e faça com que te persigam. Afaste-os de mim. Se os três se concentrarem em você, posso derrubá-los feito pássaros enquanto você se defende e desvia. Mas se esses selvagens vierem pra cima de mim, estamos perdidos. Está pronto?";
			link.l1 = "This won't be the first time I've handled a sword; these savages are no threat.";
			link.l1.go = "Prosper_14";
			// belamour legendary edition -->
			link.l2 = "Ha! Não se preocupe comigo. É como caçar em Le Mans! Só não vai me acertar pelas costas sem querer!";
			link.l2.go = "Prosper_14a";
		break;
		
		case "Prosper_14a":
			AddCharacterExpToSkill(pchar, "FencingL", 10);
			AddCharacterExpToSkill(pchar, "FencingS", 10);
			AddCharacterExpToSkill(pchar, "FencingH", 10);
			AddCharacterExpToSkill(pchar, "Pistol", 10);
			dialog.text = "Vá na frente, estou logo atrás de você. Lembre-se: você não pode deixar que eles se aproximem de mim!";
			link.l1 = "Eu lembro, vamos. Em frente!";
			link.l1.go = "Prosper_15";
		break;
		
		case "Prosper_14":
			AddCharacterExpToSkill(pchar, "Leadership", 40);
			// <-- legendary edition
			dialog.text = "Então prepare-se para a ação. Vá na frente, eu vou logo atrás de você. Lembre-se: você não pode deixar que eles cheguem muito perto de mim!";
			link.l1 = "Eu me lembro. Vou fazer tudo o que puder. Em frente!";
			link.l1.go = "Prosper_15";
		break;
		
		case "Prosper_15":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LocatorReloadEnterDisable("Martinique_jungle_04", "reload2_back", false);
			NextDiag.CurrentNode = "Prosper_16";
			NewGameTip("A challenging fight awaits ahead. (F6) for quick save.");
		break;
		
		case "Prosper_16":
			dialog.text = "Muito bem, "+pchar.name+"! Esses pagãos selvagens não vão mais matar ninguém. Agora vamos ao principal - a caverna. Acho que há três ou quatro deles lá dentro, mas não tenho certeza. Agora preste atenção\nEstive lá há dez anos. Há um túnel estreito dentro da caverna. Ele leva a uma pequena gruta, dividida por uma parede com um buraco no meio. Vamos repetir nosso plano de antes. Eu fico perto da entrada e você avança\nProvoque-os, não tente lutar com todos de uma vez, só impeça que eles me ataquem. Fique posicionado no túnel que mencionei, ele é estreito, então só um ou dois deles vão conseguir te enfrentar ao mesmo tempo\nEu atiro neles por cima do seu ombro. Pronto?";
			link.l1 = "Avante! Vamos acabar logo com esse ninho de selvagens!";
			link.l1.go = "Prosper_17";
		break;
		
		case "Prosper_17":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LocatorReloadEnterDisable("Martinique_CaveEntrance", "reload1_back", false);
			AddComplexSelfExpToScill(20, 20, 20, 20);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1 = "location";
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.location = "Martinique_Grot";
			pchar.quest.Sharlie_RescueDaughter2.function = "RescueDaughter_CreateIndiansGrot";
			NextDiag.CurrentNode = "Prosper_18";
		break;
		
		case "Prosper_18":
			dialog.text = "Minha filha está viva! Graças a Deus! Chegamos aqui a tempo. "+pchar.name+". Estou em dívida com você, senhor. Você é um homem corajoso e um excelente lutador!";
			link.l1 = "Fico feliz que tudo tenha terminado bem, Prosper. Foi um trabalho e tanto dar cabo de todos aqueles índios.";
			link.l1.go = "Prosper_19";
		break;
		
		case "Prosper_19":
			DialogExit();
			sld = characterFromId("RD_Selina");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
			AddComplexSelfExpToScill(30, 30, 30, 30);
		break;
		
		case "Prosper_20":
			dialog.text = "Meus mais sinceros agradecimentos mais uma vez, "+pchar.name+"! Agora vamos voltar para a cidade. A vida da minha filha não tem preço, vale mais do que qualquer quantia de dinheiro, mas quero agradecer a você dando o que restou das minhas economias. Assim que chegarmos a Saint-Pierre, vou lhe entregar com prazer. E nem pense em recusar!";
			link.l1 = "Não vou recusar, Prosper. Embora o dinheiro não tenha sido minha motivação para te ajudar.";
			link.l1.go = "Prosper_21";
		break;
		
		case "Prosper_21":
			dialog.text = "Você é um verdadeiro cavaleiro cristão, "+pchar.name+"! Agora não vamos ficar aqui parados. Vamos voltar para casa o quanto antes!";
			link.l1 = "...";
			link.l1.go = "Prosper_22";
		break;
		
		case "Prosper_22":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetImmortal(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("RD_Selina");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			sld = characterFromId("RD_Jilberte");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			pchar.quest.Tutorial_Amulet.over = "yes";
			SetLaunchFrameFormParam("Back to the town...", "Reload_To_Location", 0, 3.0);
			SetLaunchFrameReloadLocationParam("FortFrance_town", "reload", "gate_back", "");
			LaunchFrameForm();
		break;
		
		case "Prosper_23":
			SelectPresentAmulet();
			dialog.text = "Aqui estamos, Charles. Agradeço mais uma vez pela sua ajuda e junto a estas palavras deixo esta modesta quantia em pesos e dobrões de ouro. Sugiro que não gaste os dobrões à toa e os guarde para ocasiões especiais. Sei que não é muito dinheiro pelo serviço que me prestou, mas vem do fundo do meu coração. Além disso, aceite este amuleto, "+pchar.questTemp.SMQ.Text+"";
			link.l1 = "Obrigado! Adeus, Prosper, desejo felicidade a você e à sua querida filha!";
			link.l1.go = "Prosper_24";
		break;
		
		case "Prosper_24":
			LocatorReloadEnterDisable("Fortfrance_exittown", "reload2_back", false);//форт
			LocatorReloadEnterDisable("Martinique_Jungle_01", "reload1_back", false);//джунгли
			LocatorReloadEnterDisable("Martinique_Jungle_04", "reload1_back", false);//джунгли
			AddMoneyToCharacter(pchar, 5000);
			TakeNItems(pchar, "gold_dublon", 15);
			TakeNItems(pchar, pchar.questTemp.SMQ.Amulet, 1);
			Log_Info("You've received 15 doubloons");
			Log_Info("You've received an amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "Ah, um marido como você faria bem a ela. Tudo o que ela faz é ser perseguida pela cidade por um bando de almofadinhas magrelos e sem queixo. Que pena danada que todos eles sumiram de uma vez... já vão tarde. Boa sorte, Charles!";
			link.l1 = "...";
			link.l1.go = "Prosper_25";
		break;
		
		case "Prosper_25":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload10_back", "none", "", "", "", 10.0);
			sld = characterFromId("RD_Selina");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload10_back", "none", "", "", "", 10.0);
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar,"authority", 2);
			AddCharacterExpToSkill(pchar, "Leadership", 120);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 70);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 70);//скрытность
			AddQuestRecord("SharlieF", "7");
			CloseQuestHeader("SharlieF");
			DeleteAttribute(pchar, "questTemp.SMQ");
			pchar.questTemp.Prosper_fmql = "true"; // Addon-2016 Jason, французские миниквесты (ФМК)
			pchar.questTemp.ZsI_Cannibals = true;	//Sinistra Требуется для квеста "Знакомство с индейцами"
			pchar.quest.Sharlie_JungleNative.win_condition.l1 = "location";
			pchar.quest.Sharlie_JungleNative.win_condition.l1.location = "Martinique_jungle_01";
			pchar.quest.Sharlie_JungleNative.function = "SharlieJungleNative";
			SetCurrentTime(17,30);
			//AddTimeToCurrent(2,0);
			//QuestPointerToLoc("fortfrance_town", "reload", "reload4_back");
			sld = characterFromId("RD_Jilberte");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Selina":
			dialog.text = "Ah! Deus me ajude! (chorando) Você... você não faz ideia do horror que está acontecendo aqui! Esses... esses índios nos arrastaram pra cá pra nos matar e comer! Cesar Blanchet estava aqui... Os selvagens o levaram... Fizeram um ritual demoníaco horrível e depois... Senhor, eu nem consigo falar sobre isso! Eu seria o próximo! Eles iam me sacrificar... amanhã!";
			link.l1 = "Calma, Celine. Já acabou. Aqueles desgraçados tiveram o que mereciam e não vão machucar mais ninguém.";
			link.l1.go = "Selina_1";
		break;
		
		case "Selina_1":
			dialog.text = "Gilbert Coursie também está aqui. Ali... ele, ahn... ele ainda não se recuperou. Fale com ele... Depois vamos logo sair daqui!";
			link.l1 = "Pronto, pronto. Está tudo bem, menina. Chega de chorar. Vai ficar tudo certo. Você tem um pai maravilhoso. Ele nunca deixaria ninguém te machucar... Vá lá fora, eu vou ajudar... ahm... o Gilbert a sair daqui e já te encontro depois.";
			link.l1.go = "Selina_2";
		break;
		
		case "Selina_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_2", "", 5.0);
			sld = characterFromId("RD_Prosper");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_1", "", 5.0);
			AddQuestRecord("SharlieF", "5");
			sld = characterFromId("RD_Jilberte");
			LAi_SetStayType(sld);
		break;
		
		case "Selina_3":
			dialog.text = "Deus e a Santa Mãe ouviram minhas preces! Você veio nos salvar?";
			link.l1 = "Você... Seu nome é Celine, não é?";
			link.l1.go = "Selina_4";
		break;
		
		case "Selina_4":
			dialog.text = "Sim... (chorando) Você... você não faz ideia do horror que está acontecendo aqui! Esses... esses índios nos arrastaram pra cá pra nos matar e comer! Cesar Blanchet estava aqui... Eles o levaram... Fizeram um ritual demoníaco e então... Meu Deus, nem consigo falar sobre isso! Eu sou o próximo! Eles iam me sacrificar... amanhã!";
			link.l1 = "Calma, mocinha... Me desculpe, mas trago más notícias. Vim aqui com seu pai. Ele foi morto lá fora por aqueles selvagens de pele vermelha enquanto lutávamos para chegar até você. Ele deu a vida para te salvar.";
			link.l1.go = "Selina_5";
		break;
		
		case "Selina_5":
			dialog.text = "O quê?! Meu pai... Meu Deus! Eu... Eu... (chorando)";
			link.l1 = "Meus pêsames, Celine. Tem mais alguém aqui com você, estou certo?";
			link.l1.go = "Selina_6";
		break;
		
		case "Selina_6":
			dialog.text = "(chorando) Sim... Gilbert Coursie. Ele está lá dentro... Ainda não se recuperou. Vá falar com ele... Depois vamos sair daqui rápido!";
			link.l1 = "Sim, claro. Não podemos perder um minuto parado aqui.";
			link.l1.go = "Selina_7";
		break;
		
		case "Selina_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_2", "", 5.0);
			AddQuestRecord("SharlieF", "6");
			sld = characterFromId("RD_Jilberte");
			LAi_SetStayType(sld);
			AddComplexSelfExpToScill(20, 20, 20, 20);
		break;
		
		case "Selina_8":
			dialog.text = "Meu pai... Meu pobre e querido pai! Ah, monsieur, eu nem sequer lhe agradeci por me salvar...";
			link.l1 = "Selina, só fico aliviado que você e Gilbert conseguiram sair daquela caverna com vida. A morte heroica do seu pai não foi em vão.";
			link.l1.go = "Selina_9";
		break;
		
		case "Selina_9":
			dialog.text = "(chorando) Por favor, monsieur, leve-nos com você até a cidade. Precisamos chamar os soldados para virem buscar o corpo do meu pai, para que ele tenha um enterro cristão digno...";
			link.l1 = "Claro, Celine. Venha comigo!";
			link.l1.go = "Selina_10";
		break;
		
		case "Selina_10":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("RD_Jilberte");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
		case "Selina_11":
			dialog.text = "Obrigada, monsieur, por acompanhar meu pobre pai... Obrigada por me salvar da morte certa. Eu... eu... Aqui, pegue esta bolsa de dobrões. Encontrei em casa, no baú do meu pai. Por favor, nem pense em recusar!";
			link.l1 = "Obrigado, Celine. Fico feliz que conseguimos te salvar. E meus sinceros sentimentos pela perda do seu pai.";
			link.l1.go = "Selina_12";
		break;
		
		case "Selina_12":
			TakeNItems(pchar, "gold_dublon", 15);
			PlaySound("interface\important_item.wav");
			dialog.text = "Você é um homem nobre, monsieur. Jamais vou me esquecer de você. Adeus!";
			link.l1 = "Adeus, Celine.";
			link.l1.go = "Selina_13";
		break;
		
		case "Selina_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload10_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar,"authority", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
			AddQuestRecord("SharlieF", "8");
			CloseQuestHeader("SharlieF");
			pchar.questTemp.ZsI_Cannibals = true;	//Sinistra Требуется для квеста "Знакомство с индейцами"
			
			sld = characterFromId("RD_Jilberte");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Jilberte":
			PlaySound("Voice\English\other\robinzons-08.wav");
			dialog.text = "Meu Deus, será que tudo isso ficou mesmo para trás? Mal posso acreditar... Você salvou a mim e à Celine. Se não fosse por você, o mesmo destino que caiu sobre o pobre Cesar teria aguardado por ela amanhã, e eu teria seguido pelo mesmo caminho em poucos dias.";
			link.l1 = "Esses índios, eles são mesmo canibais?!";
			link.l1.go = "Jilberte_1";
		break;
		
		case "Jilberte_1":
			dialog.text = "Duvida? Se tiver estômago forte, dê uma olhada nas cinzas da fogueira deles. Vai encontrar o pobre velho Cesar lá. Agora ele não passa de uns ossos roídos...";
			link.l1 = "Santíssimo Sacramento... Não, vou passar. Acabei de chegar da Europa e jamais poderia imaginar que coisas tão vis, tão diabólicas ainda acontecem neste mundo.";
			link.l1.go = "Jilberte_2";
		break;
		
		case "Jilberte_2":
			dialog.text = "Muitas coisas estranhas acontecem no Caribe, coisas das quais você só ouvia sussurros no Velho Mundo... Curandeiros indígenas, magia, xamãs e rituais secretos. Fique aqui por mais tempo e verá todo tipo de feitiçaria. Mas me perdoe, ainda não agradeci por ter me salvado – ainda estou em choque\nVocê salvou minha vida e vou demonstrar minha gratidão não só com palavras, mas também com ouro. Escolte Celine e a mim até a cidade. Lá poderei lhe agradecer como merece, monsieur.";
			link.l1 = "Certo. Espere lá fora. Vou dar uma olhada aqui primeiro.";
			link.l1.go = "Jilberte_3";
		break;
		
		case "Jilberte_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_3", "OpenTheDoors", 10.0);
			pchar.quest.Sharlie_RescueDaughter5.win_condition.l1 = "location";
			pchar.quest.Sharlie_RescueDaughter5.win_condition.l1.location = "Martinique_CaveEntrance";
			pchar.quest.Sharlie_RescueDaughter5.function = "RescueDaughter_GoHome";
		break;
		
		case "Jilberte_4":
			dialog.text = "Permita-me expressar mais uma vez minha profunda gratidão por ter me salvado, monsieur! Como prometido, junto à minha gratidão verbal, ofereço também minha gratidão material em forma de pesos de prata e dobrões de ouro.";
			link.l1 = "Fico feliz que tudo tenha acabado bem, Gilbert.";
			link.l1.go = "Jilberte_5";
		break;
		
		case "Jilberte_5":
			AddMoneyToCharacter(pchar, 3000);
			TakeNItems(pchar, "gold_dublon", 20);
			Log_Info("You've received 20 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Você nem imagina o quanto estou feliz com isso! Mais uma vez, obrigado, e permita-me retirar-me, monsieur.";
			link.l1 = "Boa sorte, Gilbert! Aliás, você sabe se tem mais alguém em Saint-Pierre precisando de ajuda?";
			link.l1.go = "Jilberte_6a";
		break;
		
		case "Jilberte_6a":
			dialog.text = "Eu não sei, mas... Você pode perguntar aos cidadãos nas ruas, Monsieur. O povo comum, e até mesmo os mais abastados, dificilmente vão oferecer algo de valor, mas os nobres ricos... talvez tenham algum trabalho para você.";
			link.l1 = "Entendi, Gilbert, obrigado. Até mais!";
			link.l1.go = "Jilberte_6";
		break;
		
		case "Jilberte_6":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.Sharlie.RescueDaughter");
			
			//Подбегает дворянин с квестом "девочка по вызову"
			sld = GetCharacter(NPC_GenerateCharacter("GigoloMan", "Guide_2", "man", "man", 25, FRANCE, 5, true, "soldier"));
			SetFantomParamFromRank(sld, 25, true);
			sld.Dialog.Filename = "Quest\Sharlie\StartMiniQuests.c";
			sld.dialog.currentnode = "GigoloMan";
			sld.greeting = "noble_male";
			AddLandQuestMark(sld, "questmarkmain");
			LAi_SetLoginTime(sld, 6.0, 21.0);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Fortfrance_town", "goto", "goto1");
			sld.talker = 9;
			LAi_SetCitizenType(sld);
		break;
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Escute aqui, eu sou um cidadão respeitador das leis desta cidade. Peço que não ande por aí com a espada à mostra como um bandido.","Senhor, por favor, a lei é clara: homens não podem andar com armas desembainhadas dentro das muralhas da cidade.");
			link.l1 = LinkRandPhrase("Certo.","Muito bem.","Como quiser...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			if (npchar.id == "GigoloMan") NextDiag.TempNode = "GigoloMan";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}

void SelectPresentAmulet()
{
	switch (pchar.HeroParam.HeroType)
	{        
		case "HeroType_1":
			pchar.questTemp.SMQ.Amulet = "indian_7";
			pchar.questTemp.SMQ.Text = "it adds endurance and gives a second wind.";
		break;
		
		case "HeroType_2":
			pchar.questTemp.SMQ.Amulet = "amulet_7";
			pchar.questTemp.SMQ.Text = "it heightens resilience to battle wounds.";
		break;
		
		case "HeroType_3":
			pchar.questTemp.SMQ.Amulet = "indian_4";
			pchar.questTemp.SMQ.Text = "it raises the attack strength of your weapons.";
		break;
		
		case "HeroType_4":
			pchar.questTemp.SMQ.Amulet = "indian_1";
			pchar.questTemp.SMQ.Text = "it makes fire weaponry much more lethal.";
		break;
	}
}
