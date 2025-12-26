// Жак Барбазон в Ле Франсуа
int iBarbazonTotalTemp;
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc, sTemp;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

//--> -----------------------------------------------блок angry-------------------------------------------------
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
					if (npchar.angry.name == "pirate_threat")
                    {
                        if (Dialog.CurrentNode == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                        else Dialog.CurrentNode = "AngryRepeat_1";
                    }
                break;
            }
        }
    }
//<-- -------------------------------------------блок angry------------------------------------------------------

	switch(Dialog.CurrentNode)
	{
	// ----------------------------------- Диалог первый - первая встреча---------------------------------------
		case "First time":
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Você ficou maluco? Queria brincar de açougueiro? Todos os piratas estão furiosos com você, garoto, é melhor cair fora daqui...","Parece que você ficou maluco, garoto. Queria se mostrar um pouco? Sem ofensa, mas aqui não é lugar pra você. Cai fora!");
				link.l1 = RandPhraseSimple("Escuta, eu quero resolver essa situação...","Me ajude a resolver esse problema...");
				link.l1.go = "pirate_town";
				break;
			}
			
			link.l0 = ""+npchar.name+", eu gostaria" + GetSexPhrase("","a") + " de discutir minha segurança no mar. Os rapazes da Irmandade Costeira estão demonstrando interesse demais na minha humilde pessoa. Você poderia dar uma segurada neles?";
			link.l0.go = "pirate_threat";
			
            dialog.text = NPCStringReactionRepeat("Tem alguma coisa pra me dizer? Não? Então cai fora daqui!",
						"Acho que fui bem claro, pare de me irritar.","Apesar de eu já ter deixado tudo claro, você continua me irritando!",
						"Certo, já estou ficando cansado dessa grosseria.","repeat",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Já estou indo embora.",
						"Claro, "+npchar.name+"...",
						"Desculpa, "+npchar.name+"...",
						"Ai...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			
		//----------------------------------Сага - искушение Барбазона---------------------------------------
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "begin")
			{
				link.l1 = "Preciso falar com você, Jacques... Em particular.";
				link.l1.go = "Temptation";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "give_silk" && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 60)
			{
				link.l1 = "Eu venho de Saint Martin, Jacques...";
				link.l1.go = "Temptation_6";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "terrax")
			{
				link.l1 = "E quando é que você vai parar de latir e começar a falar como homem, Jacques? Não esperava me ver?";
				link.l1.go = "terrax";
			}
			
			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
				{
					link.l1 = "Vim falar sobre o seu prisioneiro.";
					link.l1.go = "CapComission1";
					DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
				}
             	
				if (pchar.GenQuest.CaptainComission.PirateShips == "died" || pchar.GenQuest.CaptainComission.PirateShips == "goaway") // лесник. новая проверка. искл. возможность сразу сдать задание,минуя 15 дней.
				{
					link.l1 = "Olá, Jacques, estou aqui por causa da sua missão.";
					link.l1.go = "CapComission3";
				}
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak") && !CheckAttribute(pchar,"GenQuest.CaptainComission.vikupzaplatil")) 
				{ // лесник . второй диалог с проверкой ,если ГГ ещё не принес деньги за выкуп.
					link.l1 = "Vim falar sobre o seu prisioneiro.";
					link.l1.go = "CapComission6";
				}
			}	
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin")
			{
				link.l1 = "Ouvi dizer que você está envolvido em negócios relacionados a prisioneiros...";
				link.l1.go = "Marginpassenger";
			}
		break;
			

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Você ficou maluco? Quis bancar o açougueiro? Todos os piratas estão furiosos com você, garoto, é melhor cair fora daqui...","Parece que você perdeu o juízo, garoto. Queria se exibir um pouco? Sem ofensa, mas você não tem nada pra fazer aqui. Cai fora!");
				link.l1 = RandPhraseSimple("Escuta, eu quero resolver essa situação...","Me ajude a resolver esse problema...");
				link.l1.go = "pirate_town";
				break;
			}
			
			link.l0 = ""+npchar.name+", eu gostaria de discutir minha segurança no mar. Os rapazes da Irmandade Costeira estão demonstrando interesse demais na minha humilde pessoa. Você poderia dar uma segurada neles?";
			link.l0.go = "pirate_threat";
			
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar)+"! O que você quer desta vez?",
						"Esqueceu de me contar alguma coisa? Estou ouvindo.", "Quanto tempo isso vai durar... Se não tem nada pra fazer, então não enche o saco dos outros!",
						"Você me pediu para ser educado. Mas exijo o mesmo de você!","repeat",10,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Não é nada. Só uma visita.",
						"Nada...",
						"Tudo bem...",
						"Você está certo. Me desculpe.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			
			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
			{
				link.l1 = "Vim falar sobre o seu prisioneiro.";
				link.l1.go = "CapComission1";
				DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
			}	
			if (pchar.GenQuest.CaptainComission.PirateShips == "died" || pchar.GenQuest.CaptainComission.PirateShips == "goaway")//  правка лесник,новая проверка ,исключающая тут же сдачу задания
			{
				link.l1 = "Olá, Jacques, é sobre a sua missão.";
				link.l1.go = "CapComission3";
			}
		/*	if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak")) //лишний диалог лесник
			{
				link.l1 = "Vim falar sobre o seu prisioneiro.";
				link.l1.go = "CapComission6";
			}*/
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin")
			{
				link.l1 = "Ouvi dizer que você está envolvido em negócios relacionados a prisioneiros...";
				link.l1.go = "Marginpassenger";
			}
		break;

//--> -----------------------------------Сага - Искушение Барбазона---------------------------------------------
		case "Temptation":
			dialog.text = "Você sabe que me incomodar é arriscado? Muito bem, estou ouvindo.";
			link.l1 = "Tenho uma dívida. Uma grande. Logo chega a hora de pagar e não tenho um tostão. Dizem por aí que você tem talento pra bolar planos e sempre sabe onde encontrar um bom prêmio...";
			link.l1.go = "Temptation_1";
		break;
		
		case "Temptation_1":
			dialog.text = "Escuta aqui, garoto! Eu sou Jacques, o Bondoso, só para quem é leal a mim. Para os outros, sou Barbazon, e às vezes o próprio Lúcifer. Como posso saber se posso confiar em você?";
			link.l1 = "Pode tentar. Juro que não vai se arrepender!";
			link.l1.go = "Temptation_2";
		break;
		
		case "Temptation_2":
			dialog.text = "Hm... Suponho que você saiba o que Jacques, o Bondoso, faz com quem tenta enganá-lo, não é? De qualquer forma, não vou te aborrecer com detalhes terríveis. Tenho uma missão simples. Se der conta, todos os seus problemas de dinheiro vão desaparecer.";
			link.l1 = "Não duvide de mim, já estive em muitas brigas e...";
			link.l1.go = "Temptation_3";
		break;
		
		case "Temptation_3":
			dialog.text = "Shut up and listen to me! A few weeks ago, a Dutch patrol caught one of my employees not far from Saint Martin. He was delivering Dutch silk to me. It's very rare; the Dutch bring only small batches here for the needs of the Company's navy.\nSo, I managed to buy six bales of silk, and Simon Morel was supposed to bring them to me on his brigantine, 'Salt Dog', but he ran into a Dutch patrol by accident. Or perhaps not by accident. That's what Morel's navigator said—he told me he was the only one who survived the fight.\nHe also gave me Morel's log, which confirms the story. According to the log, Morel threw the silk overboard during an escape attempt. It's strange, isn't it? Silk is light. They should have thrown their cannons overboard; they didn't stand a chance against the patrol anyway.";
			link.l1 = "Tem alguma coisa muito errada aqui.";
			link.l1.go = "Temptation_4";
		break;
		
		case "Temptation_4":
			dialog.text = "Tudo é possível. Muitos homens valentes trabalham para mim, e bem menos inteligentes. Sem ofensa, heh. Você precisa verificar o local onde Morel descartou a carga. Está em 21 graus 10' Norte e 61 graus 30' Oeste, segundo o diário do capitão.\nOs holandeses enrolam a seda em varas de cortiça, então os fardos ainda devem estar boiando. Devem ser seis fardos. Zarpe imediatamente, o tempo é crucial.";
			link.l1 = "Estou a caminho!";
			link.l1.go = "Temptation_5";
		break;
		
		case "Temptation_5":
			DialogExit();
			SetFunctionTimerCondition("Saga_BarbTemptationOver", 0, 0, 10, false); // таймер
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			pchar.quest.BarbTemptation.win_condition.l1 = "location";
			pchar.quest.BarbTemptation.win_condition.l1.location = "SentMartin";
			pchar.quest.BarbTemptation.function = "Saga_BarbTemptationBarkas";
			pchar.questTemp.Saga.BarbTemptation = "silk";
			AddQuestRecord("BarbTemptation", "2");
		break;
		
		case "Temptation_6":
			dialog.text = "Ótimo! Você encontrou minha seda?";
			link.l1 = "Sim, seis deles, como você disse.";
			link.l1.go = "temptation_wrong";
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 90)
			{
				link.l2 = "Yes. But there were more than you said, nine of them, not six. I brought them all here; your part is to figure out how this could happen.";
				link.l2.go = "temptation_right";
			}
		break;
		
		case "temptation_wrong":
			dialog.text = "Resposta errada. Deveriam ser nove fardos. E se você encontrou seis, então deve ter achado o resto também. Ou seja, ou você é um rato ou só um idiota preguiçoso. Você me deve três fardos de seda, e mais três como... 'compensação moral' por tentar me passar a perna.";
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 120)
			{
				link.l1 = "Que espertinho você é! Vou me lembrar disso. Aqui está sua seda, e vamos esquecer o meu erro.";
				link.l1.go = "temptation_wrong_1";
			}
			link.l2 = "Me disseram que eram seis fardos, nem um a mais. Eu te entreguei tudo o que achei e não dou a mínima pro que você pensa. Não tenho mais seda.";
			link.l2.go = "temptation_wrong_2";
		break;
		
		case "temptation_wrong_1":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 120);
			dialog.text = "Certo. Espero que isso não se repita, porque tenho uma tarefa importante pra você. Quanto dinheiro você quer ganhar?";
			link.l1 = "Dinheiro é sempre bem-vindo, por enquanto cinquenta mil pesos já está ótimo.";
			link.l1.go = "junior";
		break;
		
		case "temptation_wrong_2":
			dialog.text = "Ah, então é assim que você fala agora! Você não vai se safar dessa. Eu já te avisei – nem pense em tentar me enganar! Guardas! Tem um maldito rato na residência!";
			link.l1 = "Merda!";
			link.l1.go = "temptation_wrong_fight";
		break;
		
		case "temptation_wrong_fight":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetWarriorType(npchar);
			ChangeCharacterAddressGroup(npchar, "LeFransua_townhall", "goto", "goto1");
			LAi_SetImmortal(npchar, true);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i = 1; i <= 3; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("BarbGuard_"+i, "citiz_4"+(i+6), "man", "man", 80, PIRATE, 1, true, "quest"));
				FantomMakeCoolFighter(sld, 80, 100, 100, "blade_21", "pistol4", "bullet", 3000);
				ChangeCharacterAddressGroup(sld, "LeFransua_townhall", "reload", "reload1");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "temptation_right":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 80);
			dialog.text = "Bom trabalho. Eu estava te testando por ganância e você passou no meu teste. Deviam ser nove fardos. Um deles é seu. Agora podemos conversar de verdade. Quanto dinheiro você precisa?";
			link.l1 = "Dinheiro é sempre bem-vindo, por enquanto cinquenta mil pesos bastam.";
			link.l1.go = "junior";
		break;
		
		case "junior":
			dialog.text = "Você tem uma chance de ganhar ainda mais. Um certo cavalheiro me pediu para encontrar alguém de confiança como você para uma missão delicada e perigosa. Esse homem é muito rico, e vai te recompensar à altura se não o decepcionar.";
			link.l1 = "Estou pronto.";
			link.l1.go = "junior_1";
		break;
		
		case "junior_1":
			dialog.text = "Certo. Agora escute. Você precisa encontrar o agente dele chamado 'Knave'. Ele é o capitão da polaca 'Marlin', é tudo o que sei sobre ele. Você vai encontrá-lo em Kapsterville. A senha é 'a caçada começou'. Ele vai te dizer o que fazer. Você não me deve nada. Só quero te ajudar. Se tiver sorte, a gente se encontra de novo.";
			link.l1 = "Obrigado pela sua ajuda. Estou a caminho!";
			link.l1.go = "junior_2";
		break;
		
		case "junior_2":
			DialogExit();
			AddQuestRecord("BarbTemptation", "7");
			Saga_SetJuniorInCharles(); // ставим Валета
			pchar.questTemp.Saga.BarbTemptation = "valet";
		break;
		
		case "terrax":
			dialog.text = "O quê?! Eu vou arrancar seu...";
			link.l1 = "You won't, Barbazon. Let's see our cards! I work for Jan Svenson. I have exposed your conspiracy with Jackman. I know everything—what you were planning and what role you played as well. Jackman and his brother are dead; the first killed Blaze Sharp, sealing his own fate, and the second wasn't talkative enough, I'm afraid...";
			link.l1.go = "terrax_1";
		break;
		
		case "terrax_1":
			dialog.text = "Droga! Tyrex nunca vai me perdoar por isso, mas eu ainda...";
			link.l1 = "Não faça nenhuma besteira, Jacques. Eu sabia que essa conversa não seria fácil, então tomei minhas precauções. Dê uma olhada na janela... seu barraco está cercado pelos meus mosqueteiros. Meus homens estão espalhados por toda a sua vila, e tem uma tropa de choque bem na porta. Quer começar um massacre? É só tentar!";
			link.l1.go = "terrax_2";
		break;
		
		case "terrax_2":
			dialog.text = "Maldito seja! O que você quer?";
			link.l1 = "Você não vai acreditar em mim, Barbazon, mas tudo o que eu quero é... paz! Eu quero paz. É por isso que não vou contar para o Tyrex sobre o seu envolvimento nessa conspiração contra ele. Mas só se você fizer o que eu quero...";
			link.l1.go = "terrax_3";
		break;
		
		case "terrax_3":
			dialog.text = "O que você quer de mim? Dinheiro? Quanto?";
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) // Акула жив
			{
				link.l1 = "Ah, não, deixa isso pros seus capangas sem cérebro. Eu preciso de outra coisa. Preciso do seu voto pro Steven Dodson.";
			}
			else
			{
				link.l1 = "Ah, não, deixa isso pros seus capangas sem cérebro. Eu preciso de outra coisa. Preciso do seu voto pro Marcus Tyrex.";
			}
			link.l1.go = "terrax_4";
		break;
		
		case "terrax_4":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "And Steven Dodson is on our side.";
			else sTemp = "";
			dialog.text = "Sério? Deixa eu pensar... e se eu disser não?";
			link.l1 = "Então você vai ficar sozinho. Completamente sozinho. Svenson, Tyrex e Hawk vão se voltar contra você."+sTemp+"Eu só vou mostrar a carta do Patife, o irmão do Jackman, e minha palavra também vai valer. Agora, quanto tempo você acha que vai conseguir sentar confortavelmente depois disso?";
			link.l1.go = "terrax_5";
		break;
		
		case "terrax_5":
			dialog.text = "Falcão? Ele está vivo?!";
			link.l1 = "Ele está. Eu o salvei da armadilha armada pelo Jackman. Então o amigo mais próximo do Jacob vai virar seu inimigo mortal. E eu vou me juntar a eles, lembre-se disso, Barbazon.";
			link.l1.go = "terrax_6";
		break;
		
		case "terrax_6":
			dialog.text = "Jackman não é meu amigo! Maldição! Você me encurralou!";
			link.l1 = "Besteira. Vote no homem de quem falei e nada vai mudar pra você. Já te disse, Jacques, eu quero paz. Eu poderia fazer todos os barões te odiarem, mas não vou... ainda.";
			link.l1.go = "terrax_7";
		break;
		
		case "terrax_7":
			GiveItem2Character(pchar, "splinter_jb"); // дать осколок
			dialog.text = "Certo. Fechado. Dou minha palavra. Aqui, pega o meu fragmento de pedra, você precisa dele, não é?";
			link.l1 = "Exatamente. Fico feliz que chegamos a um acordo, Jacques. E fique com a carta do 'Canalha' como uma lembrança, se quiser. Ou melhor ainda, queime — você não vai querer que a encontrem. Ah, e mais uma coisa...";
			link.l1.go = "terrax_8";
		break;
		
		case "terrax_8":
			RemoveItems(pchar, "letter_chad", 1);
			dialog.text = "Mais o quê?! O que mais você quer de mim?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Barbazon"))
			{
				link.l1 = "Deixe-me te lembrar de uma coisa. Não faz tanto tempo assim, você mandou seu cachorro Ignacio Marco me assassinar. Fui eu quem matou ele. Fui eu quem enterrou seu plano de saquear um galeão espanhol de ouro. Fui eu quem mandou seus amigos direto para a emboscada espanhola perto de Saint Martin. Meu nome é Charlie Prince! Agora acabou, Jacques, e da próxima vez seja mais educado comigo. Acredite, 'garoto', a gente ainda vai se encontrar de novo, e mais de uma vez, eu imagino.";
				link.l1.go = "terrax_8_1";
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Barbazon") && CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
				{
					link.l1 = "Deixe-me te lembrar de uma coisa. Não faz tanto tempo assim que você mandou seu cão Ignacio Marco para me assassinar. Fui eu quem o matou. Fui eu quem enterrou seu plano de saquear um galeão espanhol carregado de ouro. Meu nome é Charlie Prince! Acabou, Jacques, e da próxima vez que nos encontrarmos, seja mais educado comigo. Acredite, 'garoto', a gente ainda vai se ver de novo, e mais de uma vez, imagino. Não se esqueça, tenho todos os barões piratas do meu lado. Adeus, Barbazon...";
					link.l1.go = "terrax_9";
				}
				else
				{
					link.l1 = "Da próxima vez que a gente se encontrar, trate de ser mais educado comigo. Pode acreditar, 'garoto', ainda vamos nos ver de novo, e não vai ser só uma vez, imagino. Não se esqueça, tenho todos os barões piratas do meu lado. Até mais, Barbazon...";
					link.l1.go = "terrax_9";
				}
			}
		break;
		
		case "terrax_8_1":
			dialog.text = "";
			link.l1 = "Não se esqueça, eu tenho todos os barões piratas do meu lado. Adeus, Barbazon...";
			link.l1.go = "terrax_9";
		break;
		
		case "terrax_9":
			DialogExit();
			NextDiag.CurrentNode = "I_know_you_good";
			AddQuestRecord("BarbTemptation", "26");
			if (CheckCharacterItem(pchar, "splinter_mt") && CheckCharacterItem(pchar, "splinter_jb") && CheckCharacterItem(pchar, "splinter_zm")) Saga_GiveCalendar();
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Saga_SGM_"+i);
				LAi_SetCitizenType(sld);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
				sld.lifeday = 0;
			}
			ChangeCharacterComplexReputation(pchar, "fame", 1);
			bDisableFastReload = false;
			LAi_LocationFightDisable(&Locations[FindLocation("LeFransua_town")], false);
		break;

//-----------------------------------Поручение капитана - Выкуп-------------------------------------------------
		case "CapComission1":
			dialog.text = "Ha-ha. Acha mesmo que só tenho um prisioneiro aqui? Diga o nome dele.";
			link.l1 = pchar.GenQuest.CaptainComission.SlaveName+". Ele está aqui?";
			link.l1.go = "CapComission2";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
		break;

		case "CapComission2":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.DaysLeft"))
			{
				dialog.text = "Ele era. Eu o vendi para aquele fazendeiro de Barbados – o Coronel Bishop, quando ele esteve aqui há uma semana.";
				link.l1 = "Droga...";
				link.l1.go = "CapComission2_1";
			}
			else
			{
				dialog.text = "Ah, finalmente. Eu já estava pensando em vendê-lo para aquele fazendeiro de Barbados, ele deve chegar em uma semana ou duas... Você trouxe o resgate?";
				link.l1 = "Olha, tem um pequeno problema... Na verdade, eu não tenho tanto dinheiro assim. Mas estou disposto a trabalhar.";
				link.l1.go = "CapComission2_2";
				if(makeint(pchar.money) > 150000)
				{
					link.l2 = "Que bom que você não o vendeu. Aqui estão suas moedas – 150.000 pesos. Onde posso encontrá-lo?";
					link.l2.go = "CapComission2_3";
				}	
			}
		break;
		
		case "CapComission2_1":
			dialog.text = "Você foi lento demais... E por que se importa com ele? Eu só estava negociando com os parentes dele.";
			link.l1 = "Me pediram para vir aqui.";
			link.l1.go = "CapComission2_11";
		break;
		
		case "CapComission2_11":
			dialog.text = "Bem, você está atrasado. Não posso fazer nada.";
			link.l1 = "Escuta, por quanto você vendeu ele, se não for segredo?"; 
			link.l1.go = "CapComission2_12";
		break;
		
		case "CapComission2_12":
			dialog.text = "Ah, não é. Mas não vou te contar... Você só vai rir se eu contar. Ha-ha-ha-ha! Adeus.";
			link.l1 = "Até mais.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "10");
			AddQuestUserData("CaptainComission1", "sName", "Jacques Barbazon");//правка лесник.  в СЖ запись ниже не работает																																				  
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			CaptainComission_GenerateManager();
		break;
		
		case "CapComission2_2":
			if(rand(3) == 1)
			{

				dialog.text = "Bem, "+pchar.name+", sabe, não é assim que funciona. Volte com o dinheiro e você terá seu fracote, ha-ha.";
				link.l1 = "Tá bom. Até mais.";
				link.l1.go = "CapComission2_4";
			}
			else
			{
				dialog.text = "Pois é, pois é... Tenho um assunto pra resolver... Nem sei por onde começar. Preciso afundar um pirata que passou dos limites.";
				link.l1 = "Ele não pode simplesmente ser morto na selva?";
				link.l1.go = "CapComission2_2_1";
			}
		break;

		case "CapComission2_2_1":
			dialog.text = "Não é assim que os negócios funcionam, sabe... Não preciso que ele morra, só quero ensinar pra alguns que não se pega a minha parte do saque. Mas se ele acabar servindo de comida pros tubarões, não vou ficar chateado.";
			link.l1 = "Por que você mesmo não manda seus homens atrás dele?";
			link.l1.go = "CapComission2_2_2";
		break;
		
		case "CapComission2_2_2":
			CaptainComission_GetRandomShore();
			pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			sLoc = XI_ConvertString(pchar.GenQuest.CaptainComission.Island + "Dat"); // belamour gen
			dialog.text = "Hm... Bem, "+GetName(NAMETYPE_ORIG,pchar.GenQuest.CaptainComission.UnknownPirateName,NAME_NOM)+" convenceu alguns piratas de que a parte deles do saque está guardada no nosso esconderijo não muito longe de "+XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore+"Gen")+". Os dois navios deles '"+pchar.GenQuest.CaptainComission.ShipName1+"' e '"+pchar.GenQuest.CaptainComission.ShipName2+"' levantou âncora há pouco tempo e partiu para "+sLoc+". Agora você entende por que não posso confiar esse trabalho aos meus homens?";
			link.l1 = "Sim. Quanto tempo eu tenho?";
			link.l1.go = "CapComission2_2_3";
		break;
		
		case "CapComission2_2_3":
			dialog.text = "12 a 15 dias, não mais. É importante pra mim que eles não cheguem ao esconderijo, senão não faria sentido afundá-los com a carga valiosa. Nesse caso, seria melhor se eles trouxessem ela pra cá...";
			link.l1 = "Certo, estou dentro. Vou tentar pegá-los.";
			link.l1.go = "CapComission2_2_4";
		break;
		
		case "CapComission2_2_4":
			AddQuestRecord("CaptainComission1", "24");
			AddQuestUserData("CaptainComission1", "sName", "Jacques Barbazon");//правка
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));// в СЖ не работает имя . лесник
			AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
			AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
			AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Dat")); // belamour gen
			AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Voc")); // belamour gen
			pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
            pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
            pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips"; 
			SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);
			
			DialogExit();
		break;
		
		case "CapComission2_3":
			dialog.text = "Não se preocupe. Meus homens vão levá-lo até o seu navio. E por que você se importa com ele?";
			link.l1 = "Não. Os parentes dele me pediram para trazê-lo.";
			link.l1.go = "CapComission2_31";
		break;
		
		case "CapComission2_31":
			dialog.text = "Ah, tudo bem. Quase fiquei com pena de ter oferecido tão pouco pelo seu homem. Ha-ha-ha-ha! Até mais.";
			link.l1 = "Até mais.";
			link.l1.go = "CapComission2_32";
		break;
		
		case "CapComission2_32":
			AddQuestRecord("CaptainComission1", "9");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc")); // belamour gen
			addMoneyToCharacter(pchar, -150000);
			pchar.GenQuest.CaptainComission.vikupzaplatil = true; // новая проверка ,если шарль заплатил выкуп за пленника. лесник																																								
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission2_4":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
			{
				AddQuestRecord("CaptainComission1", "31");
				AddQuestUserData("CaptainComission1", "sName", "Jacques Barbazon");		// лесник																												  
				//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM)); в СЖ не работает
			}	
			pchar.GenQuest.CaptainComission.RepeatSpeak = true;		
			DialogExit();
		break;
		
		case "CapComission3":
			dialog.text = "So, , "+GetFullName(pchar)+", você afundou meus camaradas? He-he-he...";
			if(pchar.GenQuest.CaptainComission.PirateShips == "goaway")
			{
				link.l1 = "Não. Não consegui pegá-los. E também não os encontrei no caminho de volta.";
				link.l1.go = "CapComission4";
			}
			if(pchar.GenQuest.CaptainComission.PirateShips == "died")	
			{
				link.l1 = "Fui eu. Mandei eles servirem de comida pros tubarões.";
				link.l1.go = "CapComission5";
			}
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
		break;
		
		case "CapComission4":
			dialog.text = "Droga! Se eu os encontrei ou não, isso já não importa! E qual vai ser a sua próxima sugestão?";
			link.l1 = "Talvez você tenha um trabalho mais fácil pra mim?";
			link.l1.go = "CapComission4_1";
			link.l2 = "Escuta, "+NPChar.name+", abaixe o preço pelo prisioneiro...";
			link.l2.go = "CapComission4_2";
		break;
		
		case "CapComission4_1":
			dialog.text = "Não.";
			link.l1 = "Adeus então...";
			link.l1.go = "CapComission4_3";
		break;
		
		case "CapComission4_2":
			dialog.text = "Baixar o preço?! Acabei de perder meu estoque por causa da sua incompetência! Agora é que eu posso aumentar o preço! Pode levar ele por 200.000 pesos, se quiser, ou pode dar o fora daqui.";
			link.l1 = "Está caro demais... Adeus...";
			link.l1.go = "CapComission4_4";
			if(sti(pchar.money) >= 200000)
			{
				link.l2 = "Droga, pega suas moedas.";
				link.l2.go = "CapComission4_5";
			}	
		break;
		
		case "CapComission4_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "27");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", "Barbazon"); // лесник																			  
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));// в СЖ не работает
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();
		break;
		
		case "CapComission4_4":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "28");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", "Barbazon"); // правка	// лесник																	  
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM)); в сж не работает
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
		break;
		
		case "CapComission4_5":
			dialog.text = "Pode levar esse fracote...";
			link.l1 = "Adeus.";
			link.l1.go = "CapComission4_6";
		break;
		
		case "CapComission4_6":
			addMoneyToCharacter(pchar, -200000);
			AddQuestRecord("CaptainComission1", "29");
			AddQuestUserData("CaptainComission1", "sName", "Barbazon"); // правки имени в сж лесник
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));//в СЖ не работает // belamour gen : это хорошо, но закомментить нужно было)))
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
			DialogExit();	
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission5":
			dialog.text = "Ho-ho! Muito bem! Leve seu fracote e boa sorte.";
			link.l1 = "Obrigado. Adeus.";
			link.l1.go = "CapComission5_1";
		break;
		
		case "CapComission5_1":
			AddQuestRecord("CaptainComission1", "34");
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
	   	/*case "CapComission6":    // ЕСЛИ В ПЕРВЫЙ РАЗ ОТКАЗАЛ В ЗАДАНИИ ,ТО ПУСТЬ БАБКИ ИЩЕТ
		     ИНАЧЕ ПОВТОРНАЯ ДАЧА ЗАДАНИЯ ПРЕВРАЩАЕТ КВЕСТ В КАШУ.. лесник
			dialog.text = "Trouxe o resgate "+GetSexPhrase("","ла")+"? Eu não estava brincando quando disse que o venderia para os fazendeiros.";			
			link.l1 = "Escute, "+NPChar.name+", é o seguinte... Eu não tenho esse tipo de dinheiro. Mas estou disposto"+GetSexPhrase("","а")+" trabalhar.";
			link.l1.go = "CapComission2_2";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "Que bom que você não o vendeu. Aqui estão suas moedas - 150.000 pesos. Onde posso encontrá-lo?"link.l2.go ="CapComission2_3";
			}			
		break;*/
		  case "CapComission6":                        // лесник . пусть шарль бабло ищет,или забить на пленника.
			dialog.text = "Trouxe o dinheiro? Eu não estava brincando sobre vender aquele homem para a plantação.";			
			link.l1 = "Eu não tenho o dinheiro, "+NPChar.name+", mas estou trabalhando nisso.";
			link.l1.go = "exit";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "Que bom que você não o vendeu. Aqui estão suas moedas – 150.000 pesos. Onde posso encontrá-lo?"link.l2.go ="CapComission2_3";
			}			
		break;
																																					 																																													  																																															
//--------------------------------------------Похититель------------------------------------------------------
		case "Marginpassenger":
			dialog.text = "E por que você se importa com o que eu faço? Sabe, é melhor você cair fora...";
			link.l1 = "Tshh, calma aí. Tenho negócios com você. É sobre o seu prisioneiro.";
			link.l1.go = "Marginpassenger_1";
		break;
		
		case "Marginpassenger_1":
			dialog.text = "Ah, tá bom. Quem você quer resgatar?";
			link.l1 = "Espere. Não vim aqui para comprar ninguém, vim oferecer a chance de comprar um prisioneiro. E, bem, você vai ter a oportunidade de cobrar um resgate por ele.";
			link.l1.go = "Marginpassenger_2";
		break;
		
		case "Marginpassenger_2":
			dialog.text = "Hm. E por que você precisa da minha ajuda? Por que não quer pegar o dinheiro diretamente para você?";
			link.l1 = "É bem arriscado pra mim. Posso ter problemas com as autoridades.";
			link.l1.go = "Marginpassenger_3";
		break;
		
		case "Marginpassenger_3":
			dialog.text = "Ha-h... tá bom então. Vamos dar uma olhada. Quem é o seu prisioneiro?";
			link.l1 = "Isto é "+pchar.GenQuest.Marginpassenger.Text+" "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City+"Gen")+".";
			link.l1.go = "Marginpassenger_4";
		break;
		
		case "Marginpassenger_4":
			int iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "Entendo... seria uma troca justa, se você não estiver mentindo. Suponho que posso te pagar por esse homem "+iTemp+" pesos, ou posso te dar uma informação interessante em vez disso. Você escolhe.";
			link.l1 = "É melhor eu pegar os pesos. Já cansei desse negócio...";
			link.l1.go = "Marginpassenger_money";
			link.l2 = "Ha! Conte-me mais. Tenho certeza de que você tem algo interessante para mim.";
			link.l2.go = "Marginpassenger_offer";
		break;
		
		case "Marginpassenger_money":
			dialog.text = "Dinheiro então. Pegue-os. Agora, não é mais seu problema. Entregue o item para venda aqui.";
			link.l1 = "Ele já deve estar perto dos portões da cidade agora. Obrigado! Você realmente me ajudou.";
			link.l1.go = "Marginpassenger_money_1";
		break;
		
		case "Marginpassenger_money_1":
			iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "De nada, traga mais pra mim... Até mais!";
			link.l1 = "Boa sorte...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, iTemp);
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			AddQuestRecord("Marginpassenger", "12");
			AddQuestUserData("Marginpassenger", "sSum", iTemp);
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
		break;
		
		case "Marginpassenger_offer":
			pchar.GenQuest.Marginpassenger.Goods = GetRandomGood(FLAG_GOODS_TYPE_EXPORT, FLAG_GOODS_VALUABLE_WOOD);
			pchar.GenQuest.Marginpassenger.GoodsQty = 200+rand(10)*10;
			switch (hrand(1))
			{
				case 0: //бухта на южном мейне
					SelectSouthshore();
					while (!isLocationFreeForQuests(pchar.GenQuest.Marginpassenger.Shore)) SelectSouthshore();
					dialog.text = "É bom fazer negócios com um homem esperto. Agora escute: em alguns dias "+XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat")+" uma expedição espanhola vai chegar do continente, carregada de mercadorias valiosas. Eles vão esperar por um navio que deve levar a carga. Se você chegar lá dentro de uma semana, vai ter a chance de pegar a carga para você.\nSe eu fosse você, já estaria indo para o meu navio. E traga o prisioneiro aqui.";
					link.l1 = "Obrigado! As mercadorias vão compensar bem pelo meu trabalho. E meu passageiro já deve estar perto dos portões da cidade. Ele será trazido até você.";
					link.l1.go = "Marginpassenger_offer_1";
				break;
				
				case 1: //просто кораблик
					SelectSouthcity();
					pchar.GenQuest.Marginpassenger.ShipName1 = GenerateRandomNameToShip(SPAIN);
					dialog.text = "É bom fazer negócios com um homem esperto. Agora escute: daqui a mais ou menos uma semana, um bergantim espanhol '"+pchar.GenQuest.Marginpassenger.ShipName1+"' carregado com mercadorias valiosas vai zarpar de "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen")+" para "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Gen")+". Se você se apressar, vai pegar isso fácil.\nAinda está aqui? Se eu fosse você, já estaria indo para o meu navio. E traga o prisioneiro aqui.";
					link.l1 = "Valeu! Essas mercadorias vão compensar bem o meu trabalho. E o meu passageiro já deve estar perto dos portões da cidade. Ele será trazido até você.";
					link.l1.go = "Marginpassenger_offer_2";
				break;
			}
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			pchar.GenQuest.Marginpassenger = "final";
		break;
		
		case "Marginpassenger_offer_1":
			DialogExit();
			AddQuestRecord("Marginpassenger", "13");
			AddQuestUserData("Marginpassenger", "sShore", XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat"));//лесник - окончание в СЖ // belamour gen
			AddQuestUserData("Marginpassenger", "sName", "Jacques the Kindman"));
			SetFunctionTimerCondition("Marginpassenger_SouthshoreOver", 0, 0, 7, false);
			pchar.quest.Marginpassenger.win_condition.l1 = "location";
			pchar.quest.Marginpassenger.win_condition.l1.location = pchar.GenQuest.Marginpassenger.Shore;
			pchar.quest.Marginpassenger.function = "Marginpassenger_Southshore";
		break;
		
		case "Marginpassenger_offer_2":
			DialogExit();
			AddQuestRecord("Marginpassenger", "16");
			AddQuestUserData("Marginpassenger", "sName", "Jacques the Kindman"));
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen"));
			AddQuestUserData("Marginpassenger", "sCity1", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Acc")); // лесник - окончание в СЖ
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName1);
			SetFunctionTimerCondition("Marginpassenger_SouthshipInWorld", 0, 0, 5+rand(2), false);
		break;
		
//---------------------------------------попытка залезть в сундуки --------------------------------------------
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Roubo!!! Isso é inaceitável! Prepare-se, "+GetSexPhrase("garoto","garota")+"...","Ei, que diabos você está fazendo aí?! Achou que podia me roubar? Acabou pra você... ","Espera, que diabos? Tira as mãos de mim! Então você é um ladrão! Chegou sua hora, desgraçado...");
			link.l1 = LinkRandPhrase("Merda!","Caramba!!","Maldição!!");
			link.l1.go = "PL_Q3_fight";
		break;
					
// ----------------------------------------------блок нод angry--------------------------------------------------
		case "AngryRepeat_1":
            dialog.text = "Cai fora daqui!";
			link.l1 = "Opa...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Não me venha com suas conversas baratas. Da próxima vez, você não vai gostar do resultado...";
        			link.l1 = "Entendi.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = RandPhraseSimple("Acabou, sem conversa.","Não quero mais falar com você, então é melhor não me incomodar.");
			link.l1 = RandPhraseSimple("Como quiser...","Tá bom, então...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Espero que você mostre mais respeito e pare de ser grosseiro?";
        			link.l1 = "Pode ter certeza, Jacques, eu vou.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("LeFransua_town","reload","reload6");
		break;
		
		case "pirate_town":
            dialog.text = "Resolver o problema? Você faz ideia do que fez? Enfim, traga-me um milhão de pesos e eu convenço os rapazes a esquecerem suas 'façanhas'. Se não gostou da ideia, pode ir para o inferno.";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "Certo, estou pronto para pagar.";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "Entendi. Estou indo embora.";
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;//закрыть переход
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;
		
		case "pirate_town_pay":
            dialog.text = "Ótimo! Considere-se limpo de novo. Mas espero que você não faça esse tipo de coisa nojenta de novo.";
			link.l1 = "Não vou. Muito caro pra mim. Adeus...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
		
		case "pirate_threat":
			if (GetNpcQuestPastDayWOInit(NPChar, "ThreatTalk") == 0)
			{
				dialog.text = NPCStringReactionRepeat("Já falamos sobre isso hoje.",
													  "Fui pouco claro?",
													  "Sua insistência já está passando dos limites.",
													  "Já estou de saco cheio. Cai fora!",
													  "repeat", 3, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Então, deixamos pra outra vez...",
												   "Claro, "+npchar.name+"...",
												   "Desculpa, "+npchar.name+"...",
												   "Ai...", npchar, Dialog.CurrentNode);
				link.l1.go = "exit";
				break;
			}
			if (iGPThreat != 0)
			{
				iBarbazonTotalTemp = 10 * iGPThreatRate;
				dialog.text = "Ha! A galera da nossa irmandade tá pegando no seu pé, né, " + GetSexPhrase("camarada", "amiga") + "? Claro que posso conter eles por um tempo. Mas você vai ter que desembolsar uma boa grana. " + FindRussianDublonString(iBarbazonTotalTemp) + " na mesa e temos um acordo.";
				if (PCharDublonsTotal() > iBarbazonTotalTemp)
				{
					if (iGPThreat < 5) link.l0 = "Claro, aqui está o seu dinheiro.";
					else link.l0 = "Parece que não tenho escolha. Aqui está o seu dinheiro.";
					link.l0.go = "pirate_threat_pay";
				}
				link.l1 = "Acho melhor voltar outra hora...";
				link.l1.go = "exit";
			}
			else
			{
				SaveCurrentNpcQuestDateParam(NPChar, "ThreatTalk");
				if (NextDiag.TempNode != "I_know_you_good")
					dialog.text = "Você ficou maluco" + GetSexPhrase("", "a") + "? Nossos caras fogem de você como o diabo foge da cruz. Some daqui e para de encher!";
				else
					dialog.text = "Do que você tá falando, " + GetSexPhrase("camarada", "amiga") + "? Você é uma dor de cabeça — até os cachorros sentem isso. Ninguém quer se meter contigo.";
				link.l1 = "Entendi...";
				link.l1.go = "exit";
			}
		break;
		
		case "pirate_threat_pay":
            iGPThreatRate = 0;
            iGPThreat = 0;
            SaveCurrentNpcQuestDateParam(NPChar, "ThreatTalk");
			RemoveDublonsFromPCharTotal(iBarbazonTotalTemp);
            DialogExit();
            PiratesDecreaseNotif("");
		break;
	}
}

void SelectSouthshore()
{
	switch (rand(6))
	{
		case 0: pchar.GenQuest.Marginpassenger.Shore = "shore37"; break;
		case 1: pchar.GenQuest.Marginpassenger.Shore = "shore47"; break;
		case 2: pchar.GenQuest.Marginpassenger.Shore = "shore48"; break;
		case 3: pchar.GenQuest.Marginpassenger.Shore = "shore25"; break;
		case 4: pchar.GenQuest.Marginpassenger.Shore = "shore21"; break;
		case 5: pchar.GenQuest.Marginpassenger.Shore = "shore20"; break;
		case 6: pchar.GenQuest.Marginpassenger.Shore = "shore19"; break;
	}
}

void SelectSouthcity()
{
	switch (hrand(2))
	{
		case 0: 
			pchar.GenQuest.Marginpassenger.Southcity = "Maracaibo";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Havana"; 
		break;
		
		case 1:
			pchar.GenQuest.Marginpassenger.Southcity = "Cartahena";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santiago"; 
		break;
		
		case 2:
			pchar.GenQuest.Marginpassenger.Southcity = "Portobello";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santodomingo"; 
		break;
	}
}
