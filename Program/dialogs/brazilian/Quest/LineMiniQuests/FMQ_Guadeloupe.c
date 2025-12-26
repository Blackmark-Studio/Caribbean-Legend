// Addon-2016 Jason, французские миниквесты (ФМК) Гваделупа
void ProcessDialogEvent()
{
	ref sld, NPChar;
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
			dialog.text = "Um bug óbvio. Avise os desenvolvedores sobre isso.";
			link.l1 = "Ah, eu vou.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// квестодатель
		case "citizen":
			DelMapQuestMarkCity("Baster");
			LAi_SetImmortal(npchar, false);
			LAi_RemoveLoginTime(npchar);
			dialog.text = "Saudações, capitão! Tenho uma proposta de negócio que você vai achar muito interessante.";
			link.l1 = "Continue, monsieur.";
			link.l1.go = "citizen_1";
			DelLandQuestMark(npchar);
		break;
		
		case "citizen_1":
			dialog.text = "Quero contratar seu navio para um serviço de transporte de Guadalupe até o continente espanhol.";
			link.l1 = "Você quer ir até lá como passageiro?";
			link.l1.go = "citizen_2";
			link.l2 = "Mar do Caribe espanhol? Tô fora. Não somos exatamente amigos dos espanhóis. Sugiro que procure outro trouxa.";
			link.l2.go = "citizen_no";
		break;
		
		case "citizen_no":
			dialog.text = "Como quiser, capitão, embora não seja uma viagem arriscada. Até logo.";
			link.l1 = "Adeus.";
			link.l1.go = "citizen_exit";
		break;
		
		case "citizen_no_1":
			dialog.text = "Como quiser, capitão. Adeus!";
			link.l1 = "Adeus.";
			link.l1.go = "citizen_exit";
		break;
		
		case "citizen_exit":
			DialogExit();
			chrDisableReloadToLocation = false;
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
		break;
		
		case "citizen_2":
			dialog.text = "Não é bem assim, monsieur. Um passageiro é alguém dependente da vontade do capitão. Quero contratar você, sua tripulação e seu navio para levar a mim e a dois amigos meus até o Panamá.";
			link.l1 = "Para o Panamá? Como? Você quer dar a volta no continente inteiro?";
			link.l1.go = "citizen_3";
		break;
		
		case "citizen_3":
			dialog.text = "Ha-ha-ha! Good joke, captain. Of course not. All you have to do is deliver us to Mosquito Bay, which is not far from Portobello. We'll make our way to Panama on our own; it won't be our first journey through the jungle.";
			link.l1 = "E o pagamento?";
			link.l1.go = "citizen_4";
		break;
		
		case "citizen_4":
			dialog.text = "Dois baús de dobrões. Trezentas moedas. Você recebe um adiantado assim que estivermos a bordo. O segundo baú será seu assim que chegarmos ao nosso destino.";
			link.l1 = "Uma recompensa generosa por um trabalho tão fácil. Qual é a pegadinha, meu caro?";
			link.l1.go = "citizen_5";
		break;
		
		case "citizen_5":
			dialog.text = "Capitão, tempo é dinheiro, meus amigos e eu não temos tempo a perder. Temos que zarpar daqui hoje à noite e precisamos chegar lá em dez dias. Esta será nossa segunda viagem. Então, você está dentro?";
			link.l1 = "Fechado!";
			link.l1.go = "citizen_6";
			link.l2 = "Me desculpe, monsieur, mas sua proposta me parece suspeita demais. Procure outro tolo.";
			link.l2.go = "citizen_no_1";
		break;
		
		case "citizen_6":
			dialog.text = "Excelente. Meus amigos estão na selva agora, vou avisá-los sobre o nosso acordo. Você nos encontra na Praia Capster hoje à noite, às dez horas. Não se atrase, Capitão!";
			link.l1 = "Tá bom. Praia Capster, hoje à noite, às dez horas.";
			link.l1.go = "citizen_7";
		break;
		
		case "citizen_7":
			dialog.text = "Um minuto, capitão, nem sequer nos apresentamos. Meu nome é Bertrand Pinette. E você é...";
			link.l1 = ""+GetFullName(pchar)+". Capitão "+GetFullName(pchar)+". Até logo, Monsieur Pinette.";
			link.l1.go = "citizen_8";
		break;
		
		case "citizen_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "", "", "", "OpenTheDoors", 20.0);
			npchar.location = "None";
			AddQuestRecord("FMQ_Guadeloupe", "1");
			pchar.quest.FMQG_Capster.win_condition.l1 = "Hour";
			pchar.quest.FMQG_Capster.win_condition.l1.start.hour = 22.00;
			pchar.quest.FMQG_Capster.win_condition.l1.finish.hour = 23.99;
			pchar.quest.FMQG_Capster.win_condition.l2 = "Ship_location";
			pchar.quest.FMQG_Capster.win_condition.l2.location = "Shore29";
			pchar.quest.FMQG_Capster.win_condition.l3 = "location";
			pchar.quest.FMQG_Capster.win_condition.l3.location = "Shore29";
			pchar.quest.FMQG_Capster.function = "FMQG_CapsterBeach";
			SetFunctionTimerCondition("FMQG_StartLate", 0, 0, 1, false);
			pchar.questTemp.FMQG = "begin";
			pchar.GenQuest.SmugglersBlock = "baster_tavern";
		break;
		
		case "citizen_9":
			DelLandQuestMark(npchar);
			dialog.text = "Capitão "+GetFullName(pchar)+", aí está você. Podemos ir?";
			link.l1 = "Sim. Bem-vindo a bordo.";
			link.l1.go = "citizen_10";
		break;
		
		case "citizen_10":
			dialog.text = "Muito bem. Aceite seu adiantamento – um baú cheio de dobrões. E lembre-se – você tem apenas dez dias para nos levar ao nosso destino. Nem um dia a mais!";
			link.l1 = "Eu lembro dos termos. Não se preocupe, vamos chegar a tempo. Sentem-se.";
			link.l1.go = "citizen_11";
		break;
		
		case "citizen_11":
			DialogExit();
			GiveItem2Character(pchar, "chest");
			log_info("You have received a chest full of doubloons");
			PlaySound("interface\important_item.wav");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "officers", "sea_1", "none", "", "", "FMQG_OnBoard", 20.0);
			for (i=2; i<=3; i++)
			{
				sld = characterFromId("FMQG_pass_"+i);
				LAi_ActorRunToLocation(sld, "officers", "sea_"+i, "none", "", "", "", 10.0);
			}
			pchar.quest.FMQG_SailStart.win_condition.l1 = "location";
			pchar.quest.FMQG_SailStart.win_condition.l1.location = "Guadeloupe";
			pchar.quest.FMQG_SailStart.function = "FMQG_SailingStart";
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("FMQG_SailingLate", 0, 0, 20, false);
				SetFunctionTimerCondition("FMQG_MutiniActivate", 0, 0, 40, false);
			}
			else
			{
				SetFunctionTimerCondition("FMQG_SailingLate", 0, 0, 10, false);
				SetFunctionTimerCondition("FMQG_MutiniActivate", 0, 0, 20, false);
			}
			pchar.questTemp.FMQG = "sail";
			DeleteAttribute(pchar, "GenQuest.SmugglersBlock");
		break;
		
		case "citizen_12":
			dialog.text = "Então, Capitão, você cumpriu completamente a sua parte do acordo. Agora é a minha vez. Aceite este baú junto com a nossa mais sincera gratidão.";
			link.l1 = "Foi um prazer fazer negócios com você, monsieur.";
			link.l1.go = "citizen_13";
		break;
		
		case "citizen_13":
			GiveItem2Character(pchar, "chest");
			log_info("You have received a chest full of doubloons");
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Sailing", 200);//навигация
			AddCharacterExpToSkill(pchar, "Leadership", 200);//авторитет
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			dialog.text = "Da mesma forma. Adeus, Capitão "+GetFullName(pchar)+".";
			link.l1 = "Adeus!";
			link.l1.go = "citizen_14";
		break;
		
		case "citizen_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 20.0);
			for (i=2; i<=3; i++)
			{
				sld = characterFromId("FMQG_pass_"+i);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
				sld.lifeday = 0;
			}
			AddQuestRecord("FMQ_Guadeloupe", "6");
			CloseQuestHeader("FMQ_Guadeloupe");
			pchar.questTemp.FMQG = "pause";
			pchar.quest.FMQG_Continue.win_condition.l1 = "Ship_location";
			pchar.quest.FMQG_Continue.win_condition.l1.location = "Baster_town";
			pchar.quest.FMQG_Continue.win_condition.l2 = "location";
			pchar.quest.FMQG_Continue.win_condition.l2.location = "Baster_town";
			pchar.quest.FMQG_Continue.function = "FMQG_BasterContinue";
			/* pchar.quest.FMQG_Block1.win_condition.l1 = "Rank";
			pchar.quest.FMQG_Block1.win_condition.l1.value = 13;
			pchar.quest.FMQG_Block1.win_condition.l1.operation = ">=";
			pchar.quest.FMQG_Block1.function = "FMQG_Block"; */
			//SetFunctionTimerCondition("FMQG_Block", 0, 0, 90, false);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);	// лесник - открыть оружие снова.
			AddMapQuestMarkCity("baster", false);
		break;
		
		case "citizen_12a":
			dialog.text = "So, Captain, here we are. You have fulfilled only half of your part of the bargain, so I will do the same. Keep your advance as full pay. I hope you won't object; it was your fault, after all.";
			link.l1 = "Não posso dizer que gosto disso, mas admito que você está certo. Vamos nos separar agora.";
			link.l1.go = "citizen_13a";
		break;
		
		case "citizen_13a":
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
			dialog.text = "De qualquer forma, obrigado pelo serviço, capitão "+GetFullName(pchar)+". Adeus!";
			link.l1 = "Adeus.";
			link.l1.go = "citizen_14";
		break;
		
		case "citizen_15":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("bridgetown");
			dialog.text = "Oh! Que encontro! "+TimeGreeting()+", "+GetFullName(pchar)+"! Mas como?";
			link.l1 = TimeGreeting()+", Monsieur Pinette. Não foi fácil te encontrar.";
			link.l1.go = "citizen_16";
		break;
		
		case "citizen_16":
			sld = characterFromId("Baster_usurer");
			dialog.text = "E qual é o motivo, capitão?";
			link.l1 = "Meu bom senhor, há um homem chamado "+GetFullName(sld)+" e ele está muito ansioso para te ver. Imagino que você saiba o motivo.";
			link.l1.go = "citizen_17";
		break;
		
		case "citizen_17":
			sld = characterFromId("Baster_usurer");
			dialog.text = "Claro que sim, mas você, meu caro Capitão, também deve saber que não estou nada ansiosa para ver o monsieur "+GetFullName(sld)+" de jeito nenhum. Você é o caçador de recompensas dele? Eu realmente não entendo.";
			link.l1 = "Infelizmente, é isso que sou no momento, e não estou nada feliz com isso. Cometi um erro, e agora, monsieur "+GetFullName(sld)+", maldito seja, me colocou diante de uma escolha. Ou é o seu glorioso retorno à Guadalupe, ou é a minha cabeça como cúmplice nessa sua tentativa de libertar o don Carlos de Milyar. Isso me machucaria, você sabe.";
			link.l1.go = "citizen_18";
		break;
		
		case "citizen_18":
			sld = characterFromId("Baster_usurer");
			dialog.text = "Ah, aquele desgraçado! Isso é uma maneira realmente cruel de chantagear as pessoas!.. Então, Capitão, o que vai ser, vai tomar uma decisão ou vai deixar alguém assim te chantagear?";
			link.l1 = "E o que você acha? Eu acredito que você vai comigo para Basse-Terre.";
			link.l1.go = "citizen_19";
			link.l2 = "Eu tenho escolha aqui?";
			link.l2.go = "citizen_25";
		break;
		
		case "citizen_19":
			dialog.text = "Ah, sinto muito em te decepcionar, Capitão. Não tenho a menor intenção de embarcar no seu belo navio. Você não vai conseguir nada à força aqui, o lugar está cercado de guardas e eu vou gritar por socorro se você mostrar qualquer sinal de violência. Claro, pode até tentar me esfaquear, mas nosso bom amigo não vai ganhar moeda nenhuma de um cadáver gelado. Então, o mais sensato que você pode fazer agora é me deixar em paz. Eu vou deixar você sair sem nenhum arranhão.";
			link.l1 = "Você realmente acha que eu vou simplesmente sair andando depois de tudo o que aconteceu? Você me arrastou pra essa confusão, seu desgraçado, agora chegou a hora de pagar!";
			link.l1.go = "citizen_20";
			link.l2 = "Você tem razão, acho eu. Gosto da ideia de te esfaquear, mas não faz sentido. Nem pense que isso acabou. Agora vou para Basse-Terre contar ao nosso bom amigo onde você está. E então ele vai mandar homens mascarados atrás de você.";
			link.l2.go = "citizen_21";
		break;
		
		case "citizen_20":
			dialog.text = "A-ah! Soldados! Socorro!!!";
			link.l1 = "...";
			link.l1.go = "citizen_fight";
		break;
		
		case "citizen_21":
			dialog.text = "Mas é claro. Diga ao seu chefe para manter os homens mascarados dele sob controle – estou ficando muito popular ultimamente. Até logo, Capitão.";
			link.l1 = "...";
			link.l1.go = "citizen_22";
		break;
		
		case "citizen_22":
			DialogExit();
			LAi_SetActorType(npchar);
			AddQuestRecord("FMQ_Guadeloupe", "19");
			pchar.quest.FMQG_Mayak.win_condition.l1 = "location";
			pchar.quest.FMQG_Mayak.win_condition.l1.location = "Mayak2";
			pchar.quest.FMQG_Mayak.function = "FMQG_Lighthouse";
		break;
		
		case "citizen_23":
			DelLandQuestMark(npchar);
			dialog.text = "Espere! Eu me rendo! Eu me rendo!";
			link.l1 = "Certo então! Agora largue sua arma e marche para o navio!";
			link.l1.go = "citizen_24";
		break;
		
		case "citizen_24":
			DialogExit();
			chrDisableReloadToLocation = false;
			RemoveAllCharacterItems(npchar, true);
			DoQuestReloadToLocation("Mayak2", "goto", "goto1", "FMQG_OnLighthouse");
		break;
		
		case "citizen_25":
			dialog.text = "Sempre há uma escolha, capitão. Pelo que entendi, você não estaria me caçando se não fosse pelas ameaças daquele banqueiro?";
			link.l1 = "Exatamente.";
			link.l1.go = "citizen_26";
		break;
		
		case "citizen_26":
			dialog.text = "Ótimo. Então vou providenciar um jeito seguro de calar a boca dele. Vamos escrever uma carta para você entregar ao seu patrão. Diga a ele que, se algum dia resolver abrir o bico, o governador de Guadalupe vai saber quem foi o homem que planejou e financiou o sumiço do Courage – uma escuna de correio encarregada de transportar um grande lote de diamantes.";
			link.l1 = "Hum. Acho que estou começando a entender, Monsieur Pinette.";
			link.l1.go = "citizen_27";
		break;
		
		case "citizen_27":
			dialog.text = "Fico feliz que você seja tão esperto, Capitão. De Lion vai pessoalmente pregar a cabeça do avarento ardiloso nos portões da cidade se descobrir a verdade por trás do desaparecimento do Courage. Nesta carta que estou prestes a escrever, você encontrará provas que vão acalmar o chantagista. Me dê um minuto para pegar minha pena.";
			link.l1 = "Certo...";
			link.l1.go = "citizen_28";
		break;
		
		case "citizen_28":
			LAi_Fade("", "");
			GiveItem2Character(pchar, "letter_baker");
			ChangeItemDescribe("letter_baker", "itmdescr_letter_pinett");
			dialog.text = "(escrevendo) Aqui, pegue. Tem duas cartas parecidas nesse pacote. Entregue uma para o banqueiro, deixe ele se divertir. Fique com a outra e mantenha ela escondida.";
			link.l1 = " Essa informação é confiável?";
			link.l1.go = "citizen_29";
		break;
		
		case "citizen_29":
			sld = characterFromId("Baster_usurer");
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity("Baster", false);
			dialog.text = "Eu juro, você me ajudou e agora eu vou te ajudar. Fique tranquilo, o chantagista vai te deixar em paz assim que ler este testamento. Ah, sim... Mais uma coisa, capitão. Já que resolvemos isso de forma pacífica... Eu tenho um esconderijo, e vou te contar onde fica se você prometer não se meter mais nos meus negócios daqui pra frente. De qualquer jeito, nunca mais vão me deixar pisar em Guadalupe.";
			link.l1 = "Se a carta funcionar como esperado, então pode ter certeza, eu te prometo isso.";
			link.l1.go = "citizen_30";
		break;
		
		case "citizen_30":
			dialog.text = "Está combinado então. Procure entre as pedras dentro da caverna de Guadalupe. Que isso sirva como uma modesta compensação pelo seu trabalho. Boa sorte, capitão.";
			link.l1 = "O mesmo para você, Monsieur Pinette.";
			link.l1.go = "citizen_31";
		break;
		
		case "citizen_31":
			DialogExit();
			pchar.questTemp.FMQG = "letter";
			AddQuestRecord("FMQ_Guadeloupe", "24");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 1;
		break;
		
		case "citizen_fight":
			chrDisableReloadToLocation = true;
			LAi_group_Delete("EnemyFight");
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");
			DoQuestFunctionDelay("FMQG_PlantationGuards", 3.0);
			pchar.questTemp.FMQG = "fail";
			AddQuestRecord("FMQ_Guadeloupe", "18");
			CloseQuestHeader("FMQ_Guadeloupe");
		break;
		
		// вестовой к ростовщику
		case "cureer":
			DelMapQuestMarkCity("baster");
			LAi_SetImmortal(npchar, false);
			DelLandQuestMark(npchar);
			npchar.lifeday = 0;
			dialog.text = "Saudações, monsieur! Você é o capitão "+GetFullName(pchar)+", certo?";
			link.l1 = "Certo. O que posso fazer por você?";
			link.l1.go = "cureer_1";
		break;
		
		case "cureer_1":
			sld = characterFromId("BasTer_usurer");
			dialog.text = "Monsieur "+GetFullName(pchar)+", o dono do banco de Basse-Terre está pedindo que você o visite o quanto antes. Ele me mandou verificar o escritório do porto todos os dias para garantir que sua chegada não passe despercebida.";
			link.l1 = "Interessante, e por que ele estaria tão ansioso para me ver?";
			link.l1.go = "cureer_2";
		break;
		
		case "cureer_2":
			dialog.text = "Monsieur "+GetFullName(sld)+" vou te contar pessoalmente o motivo. Espero que você não recuse o convite dele.";
			link.l1 = "Hm... Tudo bem. Esses banqueiros são gente poderosa e nunca perdem tempo com peixe pequeno. Vou falar com o homem assim que possível.";
			link.l1.go = "cureer_3";
		break;
		
		case "cureer_3":
			dialog.text = "Obrigado, Capitão. Adeus!";
			link.l1 = "Adeus.";
			link.l1.go = "cureer_4";
		break;
		
		case "cureer_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Baster_town", "reload1_back", true);
			LocatorReloadEnterDisable("Baster_town", "reload2_back", true);
			LocatorReloadEnterDisable("Baster_town", "gate_back", true);//закрыть выходы из города
			pchar.questTemp.FMQG = "continue";
			pchar.quest.FMQG_Block.over = "yes";
			pchar.quest.FMQG_Block1.over = "yes";
			AddLandQuestMark(characterFromId("Baster_usurer"), "questmarkmain");
		break;
		
		// Жан Дено
		case "Juan":
			dialog.text = "Argh! Seu canalha! Não tem como isso ser um encontro ao acaso...";
			link.l1 = "É verdade isso, Jean... perdão, quero dizer Juan. Eu te encontrei. Agora, poderia se dirigir até meu porão de carga? Desabafe um pouco e depois conversamos.";
			link.l1.go = "Juan_1";			
		break;
		
		case "Juan_1":
			DialogExit();
			Lai_SetPlayerType(pchar);
			DeleteAttribute(npchar, "DontRansackCaptain");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			pchar.questTemp.FMQG.Prisoner = GetFullName(npchar);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			AddQuestRecord("FMQ_Guadeloupe", "14");
			pchar.questTemp.FMQG = "juan_capture";
			DoQuestCheckDelay("LAi_ReloadBoarding", 3.5);
		break;
		
		case "Juan_2":
			dialog.text = "";
			link.l1 = "Eu cumpri minha parte do acordo. Agora é a sua vez. Faça o que prometeu, e lembre-se das consequências de mentir.";
			link.l1.go = "Juan_3";
		break;
		
		case "Juan_3":
			dialog.text = "Você vai encontrar o Bertrand Pinette em Barbados, na principal plantação, para ser mais exato. Ele estava planejando continuar suas operações por lá. O capataz da plantação é amigo dele.";
			link.l1 = "Que tipo de operações?";
			link.l1.go = "Juan_4";
		break;
		
		case "Juan_4":
			dialog.text = "O mesmo que fazia em Guadalupe. Comércio meio legal, contrabando, escravos. Acho que ele quer negociar escravos e açúcar, por que mais teria se mudado para uma plantação?";
			link.l1 = "Entendi. Ele tem algum protetor entre as autoridades inglesas?";
			link.l1.go = "Juan_5";
		break;
		
		case "Juan_5":
			dialog.text = "Acho que sim. Ele é uma figura curiosa. Sempre tem amigos em todo lugar.";
			link.l1 = "Mais alguma coisa?";
			link.l1.go = "Juan_6";
		break;
		
		case "Juan_6":
			dialog.text = "Como assim? Astuto e esperto, sempre sabe das coisas, sempre tem uma carta na manga. Não tive muito tempo pra saber mais sobre ele.";
			link.l1 = "Entendi. Tudo bem, tenho que navegar até Bridgetown. Você está livre, don Juan. Nem pense em avisar o Pinette. Se eu não encontrá-lo lá, vai ser o seu pescoço na reta de novo.";
			link.l1.go = "Juan_7";
		break;
		
		case "Juan_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			pchar.questTemp.FMQG = "headhunter_pinett";
			AddQuestRecord("FMQ_Guadeloupe", "17");
			// Пинетта - в Бриджтаун
			sld = characterFromId("FMQG_pass_1");
			ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation_F2", "goto", "goto1");
			sld.Dialog.currentnode = "citizen_15";
			LAi_SetStayType(sld);
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity("bridgetown", false);
		break;
		
		case "killer":
			dialog.text = "Me desculpe, amigo. Nada pessoal. Você sabe demais, esse é o seu problema.";
			link.l1 = "...";
			link.l1.go = "killer_1";
		break;
		
		case "killer_1":
			DialogExit();
			AddLandQuestMark(characterFromId("Baster_usurer"), "questmarkmain");
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // правки релиза								  
			LAi_group_Delete("EnemyFight");
			int n = 2;
			if (MOD_SKILL_ENEMY_RATE > 6) n = 3;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("FMQG_killer_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FMQG_KillersDestroy");
			LAi_SetFightMode(pchar, true);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
