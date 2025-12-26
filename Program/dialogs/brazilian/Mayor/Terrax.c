// Маркус Тиракс, барон Ла Веги
int iTerraxTotalTemp;
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc, sTemp;
	int i;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

// ------------------------------------------блок angry-----------------------------------------------
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
// ------------------------------------------блок angry-----------------------------------------------

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
			// Addon 2016-1 Jason пиратская линейка патч 17/1
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && !CheckAttribute(npchar, "quest.mtraxx_complete")) 
			{
				if (pchar.questTemp.Mtraxx == "full_complete_end" || pchar.questTemp.Mtraxx == "full_complete")
				{
					dialog.text = "Ah, Príncipe, até que enfim você apareceu. Pelo menos um de vocês se deu ao trabalho de vir! O serviço está esperando e todos vocês sumiram! Onde diabos está todo mundo?";
					link.l1 = "Não faço ideia... Marcus, chega pra mim. Já deu. Homens mortos me visitam nos sonhos e o próprio Lúcifer está no meu encalço. Sangue demais foi derramado ultimamente.";
					link.l1.go = "mtraxx_113";
					break;
				}
			}
			// Jason НСО
			// если Сага завалена, то у Маркуса ноды в двух местах и оплата вперед
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "Tem algum 'serviço' pra mim?";
				link.l1 = "Saudações, Marcus. Sim, tenho um 'negócio'. Lucrativo e prático.";
				link.l1.go = "patria_x";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Condotier.NeedMoney") && pchar.questTemp.Patria == "epizode_12_pirates" && sti(pchar.money) >= 100000)
			{
				dialog.text = "Trouxe o dinheiro?";
				link.l1 = "Fui eu.";
				link.l1.go = "patria_x8";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "Esse é o nosso cliente! O serviço está feito, seu Barão está sentado numa masmorra bem guardada. Talvez queira dar uma olhada, hein, hein?!";
				link.l1 = "Vou ter tempo de sobra pra isso, ha-ha. Ele está sendo bem tratado?";
				link.l1.go = "patria_10";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "Charles, que diabos?!";
				link.l1 = "Marcus, tudo deu errado. Não consegui nem vir, nem te avisar...";
				link.l1.go = "patria_x33";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "Aí está o nosso marionetista!";
				link.l1 = "Ha-ha! O espetáculo foi perfeito!";
				link.l1.go = "patria_x29";
				break;
			}
			
			link.l0 = ""+npchar.name+", eu gostaria" + GetSexPhrase("","a") + " de discutir minha segurança no mar. Os rapazes da Irmandade Costeira estão demonstrando interesse demais na minha humilde pessoa. Você poderia dar uma segurada neles?";
			link.l0.go = "pirate_threat";
			
            dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("Tem algo pra me dizer? Não? Então me deixa em paz!","Ha, "+pchar.name+"! Tem algum assunto comigo? Não? Então não me incomode.")+"","Eu achei que tinha sido claro... Mandei você sair, mas continua me enchendo o saco!","Certo, já estou ficando cansado dessa grosseria.","repeat",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Já estou indo embora.","Claro, Marcus...","Desculpa, Marcus...","Opa...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Você ficou maluco? Queria brincar de açougueiro? Todos os piratas estão furiosos com você, garoto, é melhor cair fora daqui...","Parece que você ficou maluco, garoto. Queria se mostrar um pouco? Sem ofensa, mas aqui não é lugar pra você. Cai fora!");
				link.l1 = RandPhraseSimple("Escuta, eu quero resolver essa situação...","Me ajude a resolver esse problema...");
				link.l1.go = "pirate_town";
				break;
			}
			// Сага - завершаем искушение барбазона
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "terrax")
			{
				// Addon 2016-1 Jason пиратская линейка патч 17/1
				if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
				{
					link.l1 = "Marcus, será que um dia você vai parar de ficar bravo comigo? Eu salvei o seu amigo Vincent, que saqueou Cartagena com a gente, e também salvei a sua pele! Ou o Bernard nem te contou?";
					link.l1.go = "Temptation_13";
				}
				else
				{
					link.l1 = "Por que você é tão grosso, Marcus? O Bernard não falou nada sobre mim?";
					link.l1.go = "Temptation";
				}
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "to_lavega")
			{
				link.l2 = "Estou procurando trabalho... Tem algo lucrativo em mente?";
				link.l2.go = "Mtraxx";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkTrade") && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "Tenho um pouco de seda para vender.";
				link.l2.go = "Mtraxx_silktrade";
			}
			if (pchar.questTemp.Mtraxx == "silk_14")
			{
				link.l1 = "Encontrei um comprador para você. É um construtor de navios de Port Royal. Ele precisa de seda naval para a produção dele e pode comprar lotes de cem rolos todo mês, pagando 5 doblões por rolo. Os homens dele vão buscar a mercadoria do dia 10 ao 15, à noite, no Cabo Negril. A senha é 'Um mercador de Lyon.' O Careca Geffrey já entregou o primeiro lote na Jamaica.";
				link.l1.go = "mtraxx_13";
			}
			if (pchar.questTemp.Mtraxx == "silk_15")
			{
				link.l1 = "I've found you a buyer. He's a shipbuilder from Port Royal. He needs ship silk for his production and will be able to buy batches of one hundred rolls every month for 5 doubloons a roll. His men will receive the goods from the 10th to the 15th, at night, at Negril Cape. The password is 'A merchant of Lyons'. It took me more than two months to find such a buyer; Geffrey must have already sold the silk to smugglers. I am sorry, Marcus.";
				link.l1.go = "mtraxx_15";
			}
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Você ficou maluco? Quis bancar o açougueiro? Todos os piratas estão furiosos com você, garoto, é melhor cair fora daqui...","Parece que você virou um cachorro louco, garoto. Queria se mostrar um pouco? Sem ofensa, mas aqui não tem lugar pra você. Cai fora!");
				link.l1 = RandPhraseSimple("Escuta, eu quero resolver essa situação...","Me ajude a resolver esse problema, por favor...");
				link.l1.go = "pirate_town";
				break;
			}
			// Jason НСО
			if(!CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "Charles, que diabos?!";
				link.l1 = "Marcus, tudo deu errado. Não consegui nem vir, nem te avisar...";
				link.l1.go = "patria_33";
				break;
			}
			if(!CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "Bom te ver, amigo!";
				link.l1 = "Também estou feliz em te ver. Obrigado pelo espetáculo incrível!";
				link.l1.go = "patria_29";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "Bom te ver, garoto! O que você quer?";
				link.l1 = "Tenho uma proposta pra você. Combina com um pirata, sabe!";
				link.l1.go = "patria";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "Esse é o nosso cliente! O serviço está feito, seu Barão está sentado numa masmorra bem guardada. Talvez queira dar uma olhada, hein?!";
				link.l1 = "Vou ter bastante tempo pra isso, ha-ha. Ele está sendo bem tratado?";
				link.l1.go = "patria_10";
				break;
			}
			// если Сага завалена, то у Маркуса ноды в двух местах и оплата вперед
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "Tem algum serviço pra mim?";
				link.l1 = "Saudações, Marcus. Sim, um assunto. Lucrativo e pirata.";
				link.l1.go = "patria_x";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Condotier.NeedMoney") && pchar.questTemp.Patria == "epizode_12_pirates" && sti(pchar.money) >= 100000)
			{
				dialog.text = "Trouxe o dinheiro?";
				link.l1 = "Fui eu.";
				link.l1.go = "patria_x8";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "Esse é o nosso cliente! O serviço está feito, seu Barão está sentado numa masmorra bem guardada. Talvez queira dar uma olhada, hein, hein?!";
				link.l1 = "Vou ter tempo de sobra pra isso, ha-ha. Ele está sendo bem tratado?";
				link.l1.go = "patria_10";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "Charles, que diabos?!";
				link.l1 = "Marcus, tudo deu errado. Não consegui nem vir, nem te avisar...";
				link.l1.go = "patria_x33";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "Aí está o nosso marionetista!";
				link.l1 = "Ha-ha! O espetáculo foi perfeito!";
				link.l1.go = "patria_x29";
				break;
			}
			// Тени прошлого
			if(CheckAttribute(pchar, "questTemp.Saga.Shadows") && pchar.questTemp.Saga.Shadows == "islatesoro" && npchar.location == "Pirates_townhall")
			{
				dialog.text = "Bom te ver, garoto! Em que posso te ajudar?";
				link.l1 = "Marcus, preciso falar com você. Não sei se vai gostar, mas preciso da sua ajuda do mesmo jeito.";
				link.l1.go = "shadows";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "islatesoro" && npchar.location == "Pirates_townhall")
			{
				dialog.text = "Ha, então você apareceu, "+pchar.name+". Estava esperando a sua chegada. O Diabo da Floresta me deixou intrigado com o seu problema sobre Tortuga...";
				link.l1 = "Ele me disse que você encontrou uma solução. Estou certo?";
				link.l1.go = "terrapin";
				break;
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkTrade") && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "Tenho seda para vender.";
				link.l2.go = "Mtraxx_silktrade";
			}
			
			link.l0 = ""+npchar.name+", eu gostaria" + GetSexPhrase("","a") + " de discutir minha segurança no mar. Os rapazes da Irmandade Costeira estão demonstrando interesse demais na minha humilde pessoa. Você poderia dar uma segurada neles?";
			link.l0.go = "pirate_threat";
			
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar)+", que bom te ver! O que você quer desta vez?","O que você quer?","De novo? Não incomode as pessoas se não tem nada pra fazer!","Você é um "+GetSexPhrase("bom corsário","boa garota")+", então você pode viver por enquanto. Mas não quero mais falar com você.","repeat",10,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Só queria te ver.","Nada.","Tá bom, Marcus, me desculpa.","Maldição, me desculpe mesmo, Marcus!",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Roubo! Isso é inaceitável! Prepare-se para morrer, rato...","Ei, o que você tá fazendo aí?! Achou que podia me roubar? Acabou pra você...","Espera aí, mas que diabos?! Então você é um ladrão! Chegou o seu fim, desgraçado...");
			link.l1 = LinkRandPhrase("Merda!","Caramba!","Ah, droga!");
			link.l1.go = "PL_Q3_fight";
		break;
					
		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(""+GetSexPhrase("Vá embora","Cai fora")+" daqui!","Saia da minha casa!");
			link.l1 = "Opa...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Não me distraia do meu trabalho com essa conversa inútil. Da próxima vez, não vai acabar tão bem pra você...";
        			link.l1 = "Entendi, Marcus.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = RandPhraseSimple("Estou cansado de você.","Não quero conversar com você, então é melhor ficar longe de mim.");
			link.l1 = RandPhraseSimple("Bem...","Tá, então tá...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Espero que você não venha mais me incomodar com suas conversas vazias, ou vou ter que te matar. Digo logo, não seria algo que eu faria com prazer.";
        			link.l1 = "Pode ter certeza disso, Marcus, eu não vou...";
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
            DoReloadCharacterToLocation("Lavega_town","reload","reload6");
		break;
		// <<<<<<<<<<<<============= блок нод angry =============================
		
//--> -----------------------------Сага - Искушение Барбазона завершающие этапы---------------------------
		case "Temptation":
			dialog.text = "Ha! O herói de Turks? Desculpe pela recepção dura, garoto. O Bernard já me contou sobre sua participação impressionante e mencionou algo sobre uma armadilha pra mim. Quero ouvir os detalhes...";
			link.l1 = "Era mesmo uma armadilha. Eles estavam caçando você, não o Bernard. Ele só serviu de isca.";
			link.l1.go = "Temptation_1";
		break;
		
		case "Temptation_1":
			dialog.text = "";
			link.l1 = "O plano era simples. Você devia salvar seu amigo e ser o primeiro a subir a bordo do 'Separator'. E bem nesse momento, eles abririam fogo contra o navio e o destruiriam em mil pedaços. A escuna estava carregada de pólvora como o inferno está de enxofre.";
			link.l1.go = "Temptation_2";
		break;
		
		case "Temptation_2":
			dialog.text = "Droga! De quem foi a ideia daquela loucura?! E como diabos eu ia descobrir onde estavam escondendo o Bernard?!";
			link.l1 = "Os autores desse plano foram Jackman e seu irmão David. Um mensageiro teria avisado você que o 'Separator' estava esperando sua ajuda na baía sul de Turks. Eles me escolheram como esse mensageiro, e aí foi o erro deles.";
			link.l1.go = "Temptation_3";
		break;
		
		case "Temptation_3":
			dialog.text = "Eu não entendo! Qual é o seu papel nisso tudo?";
			link.l1 = "Faz tempo que estou de olho naquele desgraçado do Jackman. Trabalho com o Jan Svenson, caso não saiba. Eu e o Diabo da Floresta decidimos desmascará-lo. O Jan tem certeza de que ele é o responsável pela morte do Blaze, e que o Steven foi acusado à toa.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end") link.l1.go = "Temptation_14";
			else link.l1.go = "Temptation_4"; //патч 17/1
		break;
		
		case "Temptation_4":
			dialog.text = "Heh! Mas um dente de tubarão com as iniciais dele foi encontrado no corpo do Blaze – S.D. – todo mundo sabe que isso pertence ao Steven...";
			link.l1 = "Foi tudo uma armação. Jackman jogava alto. Ele se livrou de Nathaniel Hawk e tomou o lugar dele em Maroon Town, depois matou Sharp e incriminou Shark pelo crime. Tenho provas suficientes das sujeiras dele. Encontrei tudo no baú de Jacob. Foi lá que achei a segunda parte do mapa de Sharp e o fragmento de Hawk.";
			link.l1.go = "Temptation_5";
		break;
		
		case "Temptation_5":
			dialog.text = "Maldição! Então o Steven é inocente? E por que o Jacob fez tudo isso?";
			link.l1 = "Ele esperava se tornar o chefe da Irmandade e previa algo relacionado à Isla Tesoro. Como não conseguiu o apoio seu e do Svenson, decidiu se livrar de vocês dois. Você era o primeiro da lista. Jan, por ser o mais perigoso, era o segundo.";
			link.l1.go = "Temptation_6";
		break;
		
		case "Temptation_6":
			dialog.text = "Onde está aquele desgraçado?! Vou acabar com ele!";
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) // Акула жив
			{
				link.l1 = "Jackman e o irmão dele estão mortos, assim como o resto dos caçadores dele. Eu mesmo cuidei disso. Esse desgraçado não vai machucar mais ninguém. Marcus, você votaria no Steven Dodson? Esse é um favor pessoal meu.";
				link.l1.go = "Temptation_7";
			}
			else
			{
				link.l1 = "Jackman e o irmão dele estão mortos, assim como o resto dos caçadores. Eu mesmo cuidei deles. Esse desgraçado não vai machucar mais ninguém. Infelizmente, o Steven foi morto...";
				link.l1.go = "Temptation_10";
			}
		break;
		
		case "Temptation_7":
			dialog.text = "Claro, eu vou votar! Sempre achei o Tubarão o mais digno de nós depois do Blaze. E quase acreditei na culpa dele. Todos nós acreditamos! Aqui, pegue meu fragmento.";
			link.l1 = "Muito bem! Agora você pode respirar aliviado.";
			link.l1.go = "Temptation_8";
		break;
		
		case "Temptation_8":
			GiveItem2Character(pchar, "splinter_mt"); // дать осколок
			dialog.text = "É verdade... Pelo que entendi, você representa os interesses do Tubarão?";
			link.l1 = "Sim. Jan Svenson e eu. Tudo bem, Marcus, até mais!";
			link.l1.go = "Temptation_9";
		break;
		
		case "Temptation_10":
			dialog.text = "Morto?! Como? Também foi coisa do Jackman?";
			link.l1 = "Não. Foi o próprio contramestre dele, Chad Kapper era o nome dele. Ele já teve o que merecia... Marcus, Svenson acha que você é o mais digno para ser o novo líder da Irmandade. Os outros barões vão apoiar essa decisão. Você aceita isso?";
			link.l1.go = "Temptation_11";
		break;
		
		case "Temptation_11":
			dialog.text = "Heh! Não precisa pedir duas vezes. É uma grande honra ser o Chefe da Irmandade! Nem pense que vou discordar.";
			link.l1 = "Ótimo. Fico feliz que você tenha aceitado isso.";
			link.l1.go = "Temptation_12";
		break;
		
		case "Temptation_12":
			GiveItem2Character(pchar, "splinter_mt"); // дать осколок
			dialog.text = "Aqui, pegue meu fragmento. Entregue para o Svenson. Imagino que ele esteja no comando?";
			link.l1 = "Sim, ele está. Tudo bem, Marcus, até mais!";
			link.l1.go = "Temptation_9";
		break;
		
		case "Temptation_9":
			dialog.text = "Sim, e quero te agradecer por ter salvado meu amigo Bernard. Aqui, pegue esta bolsa cheia de ouro.";
			link.l1 = "Obrigado! Adeus!";
			link.l1.go = "Temptation_exit";
		break;
		
		case "Temptation_exit":
			DialogExit();
			TakeNItems(pchar, "gold_dublon", 300);
			Log_Info("You have received 300 doubloons");
			PlaySound("interface\important_item.wav");
			NextDiag.CurrentNode = "I_know_you_good";
			AddQuestRecord("BarbTemptation", "25");
			if (CheckCharacterItem(pchar, "splinter_mt") && CheckCharacterItem(pchar, "splinter_jb") && CheckCharacterItem(pchar, "splinter_zm")) Saga_GiveCalendar();
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		// Addon 2016-1 Jason пиратская линейка патч 17/1
		case "Temptation_13":
			dialog.text = "É, ele me contou sobre a chegada triunfante do Charlie Prince em Turks... Salvou minha pele, é isso? Como? O Bernard falou algo sobre uma armadilha...";
			link.l1 = "Yes, it was a trap. You were the target; Bernard was just the bait...";
			link.l1.go = "Temptation_1";
		break;
		
		case "Temptation_14":
			dialog.text = "Ha-ha-ha, trabalhando para o Diabo da Floresta, hein Príncipe? E aí, ganha mais dinheiro com ele do que ganhava comigo? Fala a verdade!";
			link.l1 = "Marcus, vamos deixar o passado pra trás de uma vez. Agora temos um objetivo em comum, e ele é mais importante do que saquear comboios. Droga! É a coisa mais importante agora! O futuro da Irmandade está em jogo!";
			link.l1.go = "Temptation_15";
		break;
		
		case "Temptation_15":
			dialog.text = "Tá bom, príncipe, entendi! Você é um corsário livre afinal, trabalhar pro Diabo da Floresta foi sua escolha, e você fez bem... O Steven então... Você disse que ele foi difamado, não foi?";
			link.l1 = "Isso mesmo.";
			link.l1.go = "Temptation_4";
		break;
		
		// Тени прошлого
		case "shadows":
			dialog.text = "Claro, vou fazer o possível para te ajudar! Pode falar.";
			link.l1 = "Dá uma olhada, Marcus... Aqui está um dente de tubarão. O que pode me dizer sobre ele?";
			link.l1.go = "shadows_1";
		break;
		
		case "shadows_1":
			RemoveItems(pchar, "shark_teeth", 1);
			dialog.text = "Ha! Esse é o dente de um tubarão-branco morto pelo Steven Dodson, que queria impressionar uma garota. Desde então, todo mundo chama ele de Tubarão. Poucos conseguiriam fazer isso debaixo d'água só com um sabre simples. Mas ele era jovem e inconsequente, e a Beatrice Sharp era a mulher mais bonita do Caribe... Então, como foi que você conseguiu isso?";
			link.l1 = "Foi me dado pelo antigo carrasco de Saint John's. Este dente foi usado para matar um homem. O nome dele era... Joshua Leadbeater.";
			link.l1.go = "shadows_2";
		break;
		
		case "shadows_2":
			dialog.text = "That is an old story. Steven killed that man. He was shocked by Beatrice's death and thought that Leadbeater was the only living person responsible for it. But later he found some papers on Joshua's corpse, studied them, and repented his deed.\nThe Mask wasn't to blame for Beatrice's death; he only needed Butcher. Butcher's jealous ex-girlfriend Jessica had set all this up.";
			link.l1 = "Você leu aqueles papéis?";
			link.l1.go = "shadows_3";
		break;
		
		case "shadows_3":
			dialog.text = "Por que eu faria isso? Claro que não. Não tinha interesse neles. Mas posso te contar por que a Máscara estava atrás do Açougueiro, se você tiver um tempo. O Steven Bêbado me contou essa história várias vezes.";
			link.l1 = "Tenho tempo. Confie em mim, meu interesse tem um motivo. Eu até poderia escrever essa história.";
			link.l1.go = "shadows_4";
		break;
		
		case "shadows_4":
			dialog.text = "Eu sei que você nunca perde tempo à toa. Então escute. Joshua Leadbeater era um capitão da marinha inglesa, e o lendário 'Neptune' estava sob seu comando...";
			link.l1 = "...";
			link.l1.go = "shadows_5";
		break;
		
		case "shadows_5":
			DialogExit();
			SetLaunchFrameFormParam("One hour later", "Saga_FinalLedbitterStory", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
		break;
		
		case "shadows_6":
			AddQuestRecordInfo("Mask", "1");
			dialog.text = "... mas Leadbeater sobreviveu e foi resgatado por um navio que passava. A ferida o desfigurou, e desde então ele usa uma máscara. Com o tempo, as pessoas começaram a chamá-lo de Máscara. Vingar-se do homem que o marcou para sempre virou seu único propósito.";
			link.l1 = "Entendo... Anotei tudo. Acho que preciso reler e comparar com as informações que já tenho. Realmente, é uma história triste. Você já viu a Jessica?";
			link.l1.go = "shadows_7";
		break;
		
		case "shadows_7":
			dialog.text = "Sure! She accompanied Butcher on all his voyages until he left her for Beatrice. Jess couldn't forgive him for that. People called her the Butcher's talisman, because he always had luck while she was there with him.\nBelieve it or not, but as soon as he got rid of her in Barbados, his business went bad, the booty became poor, and the 'Neptune' became a frequent guest at the shipyard of Isla Tesoro. But that can be explained by the fact that Butcher had been spending most of his time with Beatrice in the cabin rather than on the quarterdeck.\nBeatrice was not like Jessica; she wasn't addicted to adventure and war, although Nicholas taught her fencing and sailing. Yes, she was fond of sea romances, but she didn't have enough steel in her. Butcher's 'Neptune' wasn't the right place for her. In the end, it killed her.";
			link.l1 = "E o que dizer da Jessica?";
			link.l1.go = "shadows_8";
		break;
		
		case "shadows_8":
			dialog.text = "Oh, she was something, alright... Every sailor on the 'Neptune' obeyed her orders, and not just because she was the captain's girlfriend. Jess was a master of fencing and sailing; Butcher's efforts weren't wasted. She was tough and reckless, and she was so beautiful. A lot of men wanted to share a bed with her, but she wanted only Butcher. Bothering her was really risky; many felt the consequences on their own skin, quite literally, and for the most persistent, her fencing lessons turned out to be the last of their lives. Jess owned a very special sword, the only one of its kind in the Caribbean. I have no clue where she got it. A flame-bladed sword. The blade couldn't be grabbed by hand, and even the slightest touch left a terrible wound. Jess was an adventurer not by birth, but by vocation. By the way, if you want to know more about her, you can talk to an acquaintance of yours. He can tell you much more about her than I can.";
			link.l1 = "Sério? E quem é esse homem?";
			link.l1.go = "shadows_9";
		break;
		
		case "shadows_9":
			dialog.text = "Jan Svenson. O Diabo da Floresta nunca admitiria, mas ele tinha planos para a Jessica. Naquela época, ele já tinha tomado Western Main para si e sua fama era de dar inveja, então a tigresa combinava com ele.\nDepois que o Açougueiro se livrou da Jess, Jan começou a visitar Barbados com uma frequência suspeita, fazendo a guarnição tremer de medo, isso sim. Como você sabe, Jessica era filha de um fazendeiro de Bridgetown.\nNo fim das contas, suas intenções eram bem conhecidas em certos círculos, mas ninguém ousava falar sobre isso. Hoje em dia Jan pode até ficar sentado em Blueweld, mas naquela época qualquer palavra errada dirigida a ele podia acabar mal.\nNo final, não deu certo entre eles. Jess não conseguiu conviver com a dor causada pela traição do Açougueiro, e se vingou um ano depois com a ajuda da Máscara. Essa vingança terminou terrivelmente para todos: para o Açougueiro, para a Beatrice, para a Máscara e para ela mesma. Todos morreram.";
			link.l1 = "Não. O Açougueiro ainda está vivo.";
			link.l1.go = "shadows_10";
		break;
		
		case "shadows_10":
			dialog.text = "O quê?! Eu ouvi direito?! Ele está vivo?!";
			link.l1 = "Sim. O Capitão Butcher não foi enforcado. Bem, na verdade foi, mas graças ao Jacob Jackman e ao Henry Carrasco, que assustaram o carrasco, ele sobreviveu. O enforcamento foi só uma encenação. Eu tenho provas.";
			link.l1.go = "shadows_11";
		break;
		
		case "shadows_11":
			dialog.text = "Incrível! E onde ele está agora?";
			link.l1 = "Ele é conhecido como Lawrence Beltrop e mora em Port Royal. Mas parece que ele continua o mesmo e ainda é perigoso. Jackman, que já causou muitos problemas entre os Irmãos, estava seguindo as ordens dele.";
			link.l1.go = "shadows_12";
		break;
		
		case "shadows_12":
			dialog.text = "Droga! O imediato finalmente encontrou seu capitão! Depois de tantos anos... Beltrop, você disse... espera! Agora entendi por que havia aquele protocolo de interrogatório estranho nos papéis do Blaze... Parece que o Blaze descobriu algo interessante sobre o Açougueiro-Beltrop...";
			link.l1 = "Do que você está falando?";
			link.l1.go = "shadows_13";
		break;
		
		case "shadows_13":
			dialog.text = "Quando assumi esta residência, reservei um tempo para examinar os papéis do Blaze. Encontrei um protocolo de interrogatório sobre alguém chamado Samuel Brooks. Havia muitos detalhes sobre as aventuras de Thomas Beltrope, um pirata famoso e o amigo mais próximo de Nicolas Sharp. Ao que parece, ele é o pai do Butcher.";
			link.l1 = "Interessante. Parece que os filhos de Beltrop e Sharp continuaram o trabalho dos pais...";
			link.l1.go = "shadows_14";
		break;
		
		case "shadows_14":
			dialog.text = "Parece que sim... Me diga, amigo, por que esse interesse todo pelo passado de gente que já morreu faz tempo? Do que se trata isso afinal?";
			link.l1 = "Preciso de documentos que provem que Ellen McArthur é filha de Beatrice Sharp e neta de Nicolas Sharp, e que ela tem todo o direito de usar esse sobrenome. Não me importa se o sobrenome dela pode ser Beltrop.";
			link.l1.go = "shadows_15";
		break;
		
		case "shadows_15":
			dialog.text = "Não encontrei nada sobre Ellen McArthur nos arquivos do Blaze. É estranho que Beatrice não tenha contado ao Blaze sobre o nascimento da sobrinha dele. Não é do feitio dela.";
			link.l1 = "Escuta, será que tem mais alguma coisa nos papéis do Sharp sobre essa história? Preciso de todos os detalhes que conseguir!";
			link.l1.go = "shadows_16";
		break;
		
		case "shadows_16":
			dialog.text = "Hm... Maybe. According to Blaze's notes, he was trying to find the island where his sister died. There are copies of archive papers concerning Leadbeater's punitive expedition. Nothing interesting, except for a few latitude numbers.\nThis parallel crosses the Caribbean Sea in its northern part. But there is no sign of longitude. Obviously, Blaze's search failed; you can't even imagine how many small islands are at that latitude.";
			link.l1 = "E qual é a latitude?";
			link.l1.go = "shadows_17";
		break;
		
		case "shadows_17":
			dialog.text = "Vamos ver... Aqui: 21° 32' Norte. Não sei como isso pode te ajudar.";
			link.l1 = "Pode sim. Muito obrigado, Marcus, pela sua sinceridade. Até mais!";
			link.l1.go = "shadows_18";
		break;
		
		case "shadows_18":
			DialogExit();
			pchar.questTemp.Saga.Shadows = "jessika";
			AddQuestRecord("Shadows", "6");
			LAi_SetHuberType(npchar);
			NextDiag.CurrentNode = "I_know_you_good";
			sld = characterFromId("Svenson");
			sld.quest.jessika = "true";
			// рифы доступны для посещения
			i = FindIsland("RockIsland");
			Islands[i].visible = true;
			Islands[i].reload_enable = true;
			// для любителей самостоятельно добавлять локаторы
			LAi_LocationDisableOfficersGen("Shore67", true);//офицеров не пускать
			// и сразу прерывание
			pchar.quest.Saga_Jess_Island.win_condition.l1 = "location";
			pchar.quest.Saga_Jess_Island.win_condition.l1.location = "Shore67";
			pchar.quest.Saga_Jess_Island.function = "Saga_JessikaIsland"; 
			// активируем квест хронометра Алекса
			pchar.questTemp.AlexClock = "terrax"; // 280912
		break;		
		
		// суп из черепахи
		case "terrapin":
			dialog.text = "Bem, posso fazer algo por você. Como sabe, a segurança de Tortuga não é garantida apenas pelo Forte La Roche, mas também por um esquadrão pirata que patrulha constantemente as praias da ilha. O porto de Tortuga está seguro, esses caras sabem o que fazem e têm navios poderosos. Levasseur já vem atraindo esses capitães há muito tempo.\nEles são capazes de enfrentar até mesmo um esquadrão de linha e serão adversários de peso. Então, sendo o guardião do Código e também o líder da Irmandade da Costa, posso fazer com que esses cães de guarda deixem as praias de Tortuga.";
			link.l1 = "E só isso?";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			dialog.text = "Já não basta? De qualquer forma, não posso te ajudar mais. Você precisa destruir o forte, mas pelo menos não vai precisar enfrentar aqueles navios de guarda. Acredite, eles são mais perigosos que o forte, então minha ajuda vai facilitar as coisas.";
			link.l1 = "Bem, se eu tenho que atacar de qualquer jeito, a saída do esquadrão pirata vai ajudar muito. Valeu, Marcus! Quando posso atacar Tortuga?";
			link.l1.go = "terrapin_2";
		break;
		
		case "terrapin_2":
			dialog.text = "Quando quiser. Os navios de escolta partirão ao meu sinal.";
			link.l1 = "Certo. Agora preciso ir me preparar.";
			link.l1.go = "terrapin_3";
		break;
		
		case "terrapin_3":
			DialogExit();
			// Левассера - к барьеру!
			sld = characterFromId("Tortuga_Mayor");
			LAi_LoginInCaptureTown(sld, true);
			pchar.questTemp.Sharlie.Hardcore_Tortuga = "true";
			pchar.questTemp.Terrapin = "hardcore";
			pchar.questTemp.Sharlie.DelTerGuard = "true"; // убираем пиратскую эскадру
		break;
		
		case "pirate_town":
            dialog.text = "Resolver o problema? Você faz ideia do que acabou de fazer? Enfim, traga um milhão de pesos e eu convenço os rapazes a esquecerem o que você fez. Se não gostou da ideia, pode ir pro inferno.";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "Certo, estou pronto para pagar.";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "Adeus...";
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
            dialog.text = "Ótimo! Considere-se limpo de novo. Mas espero que não faça mais essas coisas nojentas.";
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
		
		// Addon 2016-1 Jason ------------------------- пиратская линейка --------------------------
		case "Mtraxx":
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				dialog.text = "Primeiro arrume um navio, depois venha pedir trabalho. Marujo de terra firme não tem vez aqui. Cai fora!";
				link.l1 = "Hum... Entendi.";
				link.l1.go = "exit";
				break;
			}
			if(ChangeCharacterHunterScore(Pchar, "spahunter", 0) > 10)
			{
				dialog.text = "Você está completamente fora de si? Metade do mundo espanhol está atrás de você. Vai acabar causando mais problema do que ajudando. Resolva seus próprios enroscos, depois venha pedir. Era só isso que eu queria dizer! Agora suma daqui!";
				link.l1 = "Hum... Entendi.";
				link.l1.go = "exit";
				break;
			}
            dialog.text = "Procurando por um pouco de ação, hein? Ha-ha! Ótimo... Mas já vou avisando, garoto, comigo você não vai ter sossego. Se tem medo de cheiro de pólvora ou não consegue derramar sangue, a porta está logo ali. Não suporto covardes. E não vai durar muito comigo se for dedo-duro ou rato que gosta de roubar a parte do parceiro no saque. Então, o que me diz? Vai encarar?";
			link.l1 = "Estou dentro, Marcus. Não tenho medo de lutar e não existe canalha que possa me chamar de covarde ou traidor.";
			link.l1.go = "Mtraxx_1";
			link.l2 = "Opa, isso é demais pra mim! Me desculpe, Marcus, mas é melhor eu ir embora...";
			link.l2.go = "Mtraxx_exit";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("LaVega");
		break;
		
		case "Mtraxx_exit":
            DialogExit();
			pchar.questTemp.Mtraxx = "fail";
		break;
		
		case "mtraxx_wait":
            dialog.text = "O quê, você ainda está aqui?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkTrade") && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "Tenho um pouco de seda para vender.";
				link.l2.go = "Mtraxx_silktrade";
				link.l1 = "Já estou indo embora.";
				link.l1.go = "exit";
				break;
			}
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		case "Mtraxx_1":
            dialog.text = "Ha-ha, muito bem, meu pequeno pirata corajoso, vamos falar de negócios então. Minha fonte em Santo Domingo me contou sobre um capitão espanhol tão rico em âmbar azul que está distribuindo para as prostitutas. Já ouviu falar de âmbar azul?";
			link.l1 = "Eu tenho. Uma pedra rara e valiosa.";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "Exatamente. Mesmo aqui, banqueiros e joalheiros pagam bem por isso, e na velha Europa você consegue dez vezes mais. Âmbar não é uma pedra rara no Caribe, mas a variedade azul é uma raridade. E agora aparece um espertalhão castelhano se gabando de que tem mais âmbar azul do que todos os banqueiros de Cuba e Hispaniola juntos têm de âmbar amarelo.";
			link.l1 = " Dá pra confiar nas histórias de um espanhol bêbado? Achou três dobrões e já tá contando pra todo mundo que encontrou El Dorado ";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "Eu não teria feito isso, mas ele realmente estava dando âmbar azul para prostitutas. Deve ter um fundo de verdade nas suas bravatas. Vá até Santo Domingo e investigue. Se encontrar o depósito de âmbar azul, melhor ainda. Faça isso e posso garantir uma recompensa e respeito em La Vega.";
			link.l1 = "E se a sua informação não valer nada?";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
            dialog.text = "Então prove para mim que o castelhano é um mentiroso.";
			link.l1 = "Muito bem. Quem é sua fonte em Santo Domingo?";
			link.l1.go = "mtraxx_5";
		break;
		
		case "mtraxx_5":
			// belamour legendary edition даем флаг и лизензию ГВИК если отсутствует -->
			bOk = IsCharacterPerkOn(pchar,"FlagSpa") || IsCharacterPerkOn(pchar,"FlagHol");
			if(CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 60 && bOk) sTemp = ".";
			else 
			{
				if(bOk) 
				{
					if(!CheckCharacterItem(pchar, "HolTradeLicence") || GetDaysContinueNationLicence(HOLLAND) < 60) 
					{
						sTemp = ". Wait a minute, take a trading license for 60 days."; 
						GiveNationLicence(HOLLAND, 60);
					}
				}
				else // нет флага
				{
					if(!CheckCharacterItem(pchar, "HolTradeLicence")) 
					{
						sTemp = ". Wait a minute, take a 60-day trade license and a Spanish flag to land in Santo Domingo. From now on, I recommend getting your own, it will help to fool the simpleton in the trading pelvis. This one will be returned to me.";
						GiveNationLicence(HOLLAND, 60);
						STH_SetJokerFlag(SPAIN, true);
						log_info("You have received spanish flag");
						pchar.questTemp.GiveMeSpaFlag = true;
					}
					else // есть лицензия
					{	
						if(GetDaysContinueNationLicence(HOLLAND) < 60) 
						{
							sTemp = ". Wait, how are you going to trade without having the right flag?! Here you go, a 60-day trading license, longer than yours. As well as the Spanish flag for landing in Santo Domingo. From now on, I recommend getting your own, it will help to fool the simpleton in the trading pelvis. This one will be returned to me.";
							GiveNationLicence(HOLLAND, 60);
							STH_SetJokerFlag(SPAIN, true);
							log_info("You have received spanish flag");
							pchar.questTemp.GiveMeSpaFlag = true;
						}
						else 
						{
							sTemp = ". Wait, how are you going to trade without having the right flag?! Here, take the Spanish flag for the Santo Domingo landings. From now on, I recommend getting your own, it will help to fool the simpleton in the trading pelvis. This one will be returned to me.";
							STH_SetJokerFlag(SPAIN, true);
							log_info("You have received spanish flag");
							pchar.questTemp.GiveMeSpaFlag = true;
						}
					}
				}
			}
			// <-- legendary edition
            dialog.text = "Você precisa de uma garota de bordel chamada Gabriela Chapado. Diga meu nome e a senha - 'Colar de Âmbar'. Ela vai te passar os detalhes. E não perca tempo - a informação ainda está quente, mas em um ou dois dias pode ficar desatualizada"+sTemp;
			link.l1 = "Entendi, Marcus. Estou indo para Santo Domingo.";
			link.l1.go = "mtraxx_6";
		break;
		
		case "mtraxx_6":
            DialogExit();
			pchar.questTemp.Mtraxx = "jewelry_1";
			pchar.questTemp.Mtraxx.AffairOfHonor = "true"; // конфликт с делом чести
			pchar.questTemp.ZA.Block = true;			// конфликт с квестом "Заносчивый аристократ"
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_1", "1");
			Mtraxx_JewelryBegin();
			AddMapQuestMarkCity("SantoDomingo", false);
		break;
		
		case "mtraxx_7":
			i = GetCharacterItem(pchar, "jewelry7");
            dialog.text = "Já fui informado da sua chegada. Me entregue seu relatório!";
			link.l1 = "Eu resolvi o problema daquele amante de âmbar azul, embora não tenha sido fácil. Consegui encontrar os depósitos dele e saqueá-los. Eu trouxe para você "+FindRussianQtyString(i)+" pedaços de âmbar azul.";
			link.l1.go = "mtraxx_8";
			DelLandQuestMark(characterFromId("Terrax"));
			DelMapQuestMarkCity("LaVega");
		break;
		
		case "mtraxx_8":
			if (sti(pchar.questTemp.Mtraxx.JewQty) > GetCharacterItem(pchar, "jewelry7"))
			{
				PlaySound("interface\important_item.wav");
				Log_Info("You have given "+FindRussianQtyString(GetCharacterItem(pchar, "jewelry7"))+" pieces of blue amber");
				RemoveItems(pchar, "jewelry7", GetCharacterItem(pchar, "jewelry7"));
				dialog.text = "Pois bem, pois bem... Filho, lembra do meu aviso sobre os perigos de ser um rato? O que você me disse naquela hora? Que nenhum cachorro pode te culpar por isso? Você acha que eu sou idiota, moleque? Eu sei muito bem que você saqueou "+FindRussianQtyString(sti(pchar.questTemp.Mtraxx.JewQty))+" pedaços de âmbar azul na Costa dos Mosquitos. Agora corre, ratinho, corre, e reza pra que a gente nunca mais se encontre!";
				link.l1 = "Maldição!";
				link.l1.go = "AngryExitAgainWithOut";
				pchar.questTemp.Mtraxx = "fail";
				npchar.Dialog.currentnode = "First time";
				CloseQuestHeader("Roger_1");
				// belamour legendary edition забрать флаг обратно
				if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
				{
					DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
					STH_SetJokerFlag(SPAIN, false); 
					log_info("You have given spanish flag");
				}
			}
			else
			{
				PlaySound("interface\important_item.wav");
				Log_Info("You have given "+FindRussianQtyString(GetCharacterItem(pchar, "jewelry7"))+" pieces of blue amber");
				RemoveItems(pchar, "jewelry7", sti(pchar.questTemp.Mtraxx.JewQty));
				dialog.text = "Mandou bem, garoto! Mostrou do que é capaz: resolveu um problema difícil e trouxe tudo o que saqueou. Bom trabalho! Fico feliz de não ter me enganado sobre você.";
				link.l1 = "E o meu quinhão, Marcus?";
				link.l1.go = "mtraxx_9";
			}
		break;
		
		case "mtraxx_9":
			i = sti(pchar.questTemp.Mtraxx.JewQty)/2;
			PlaySound("interface\important_item.wav");
			Log_Info("You have received "+FindRussianQtyString(i)+" pieces of blue amber");
			TakeNItems(pchar, "jewelry7", i);
			// belamour legendary edition забрать флаг обратно
			if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
			{
				DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
				STH_SetJokerFlag(SPAIN, false); 
				log_info("You have given spanish flag");
			}
            dialog.text = "Falou como um verdadeiro pirata, ha-ha-ha! Metade do saque é sua. Pegue.";
			link.l1 = "Valeu, capitão. Tem mais alguma coisa pra mim?";
			link.l1.go = "mtraxx_10";
			DeleteAttribute(pchar, "questTemp.Mtraxx.JewQty");
			CloseQuestHeader("Roger_1");
			Achievment_Set("ach_57");
		break;
		
		case "mtraxx_10":
            dialog.text = "I always have tasks for capable lads. There is a delicate matter I want you to deal with. There is a ship stationed in Capsterville, called the 'Snake', under the command of Geffrey Brooke, also known as Bald Geffrey. He works for me. An excellent fighter, knows everything about guns and blades, yet a complete idiot in every other aspect of life. But let's not be too hard on Baldy, no one is perfect, ha-ha! So. This tough guy attacked a Dutch convoy north of Saint Martin and captured a bark filled with sacks of wheat. Thing is, he managed to find hidden ship silk among the sacks. A really big cargo. This merchandise is extremely valuable and rare; the Dutch bring it from Europe solely for their military needs. This silk is used for special sails which increase a ship's speed and ability to sail by the wind. It is almost impossible to buy, selling it is not a problem but it is hard to find the right price. These goddamn traders always reduce the price! I am aware that there are people in the Caribbean who are ready to give a good price in doubloons to buy this silk, and your goal is to find such people. What? Any fool can plunder caravans, but trade is only for people with at least a sign of brains' existence in their skull. I am planning to sell ship silk on a monthly basis, so your goal is to find a regular buyer who will pay at least 4 golden doubloons for a roll. You have two months to do that, I cannot keep Bald Geffrey in Capsterville forever. That's all. Set sail to Capsterville and talk to Geffrey before he sells the cargo to smugglers for a penny. I've already told you that he is a bit 'simple'.";
			link.l1 = "Hm... Entendi. Já estou indo.";
			link.l1.go = "mtraxx_11";
		break;
		
		case "mtraxx_11":
            DialogExit();
			pchar.questTemp.Mtraxx = "silk_1";
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_2", "1");
			Mtraxx_SilkBegin();
		break;
		
		case "mtraxx_12":
            dialog.text = "Ha! Olha só quem chegou, o capitão valente "+GetFullName(pchar)+"! E o comprador?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkLate"))
			{
				link.l1 = "I've found you a buyer. He's a shipbuilder from Port Royal. He needs ship silk for his production and will be able to buy batches of one hundred rolls every month for 5 doubloons a roll. His men will collect the goods from the 10th to the 15th, at night, at Negril Cape. The password is 'A merchant of Lyons'. It took me more than two months to find such a buyer; Geffrey must have already sold the silk to smugglers. I'm sorry, Marcus.";
				link.l1.go = "mtraxx_15";
			}
			else
			{
				link.l1 = "Encontrei um comprador pra você. É um construtor naval de Port Royal. Ele precisa de seda de navio pra produção dele e pode comprar lotes de cem rolos todo mês por 5 dobrões cada. Os homens dele vão receber a mercadoria do dia 10 ao 15, à noite, no Cabo Negril. A senha é 'Um mercador de Lyon'. O Careca Geffrey já entregou o primeiro lote na Jamaica.";
				link.l1.go = "mtraxx_13";
			}
		break;
		
		case "mtraxx_13":
            dialog.text = "Isso é ótimo, meu amigo! Muito bem feito. É difícil encontrar um homem que saiba usar tanto as mãos quanto a cabeça. Volte em 20 dias para receber sua recompensa. Até lá, o Careca Geffrey já terá trazido o dinheiro da primeira transação."; // правки прогона 3
			link.l1 = "Muito bem, Marcus. Até logo. Espero que tenha outro trabalho pra mim.";
			link.l1.go = "mtraxx_14";
		break;
		
		case "mtraxx_14":
            dialog.text = "Vou sim. Até mais.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkLate"))
			{
				SetFunctionTimerCondition("Mtraxx_SilkPay", 0, 0, 30, false);
				//SetFunctionTimerCondition("Mtraxx_SilkPayLate", 0, 0, 40, false);
				AddQuestRecord("Roger_2", "23");
			}
			else
			{
				SetFunctionTimerCondition("Mtraxx_SilkPay", 0, 0, 20, false); // правки прогона 3
				//SetFunctionTimerCondition("Mtraxx_SilkPayLate", 0, 0, 30, false);
				AddQuestRecord("Roger_2", "24");
			}
		break;
		
		case "mtraxx_15":
			pchar.quest.Mtraxx_SilkTimeLateAll.over = "yes";
            dialog.text = "Uma pena, mas ainda assim foi um grande sucesso. Você fez um bom trabalho! Não vai receber sua parte do lote do Geffrey, mas ainda merece uma recompensa. Me procure daqui a um mês, até lá já terei vendido o primeiro lote para o seu comprador, então conversamos.";
			link.l1 = "Muito bem, Marcus. Até logo. Espero que tenha outro trabalho pra mim.";
			link.l1.go = "mtraxx_14";
		break;
		
		case "mtraxx_16":
			//pchar.quest.Mtraxx_SilkPayLate.over = "yes";
            dialog.text = "Aí está você, "+pchar.name+". Vamos falar sobre sua recompensa.";
			link.l1 = "Eu gosto de conversas assim, ha-ha-ha! Pode falar, estou ouvindo.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkLate")) link.l1.go = "mtraxx_19";
			else link.l1.go = "mtraxx_17";
		break;
		
		case "mtraxx_17":
            dialog.text = "O Careca do Geffrey vendeu para o seu comprador o primeiro lote de 105 rolos de seda naval. Eu esperava vender por 4 dobrões cada rolo, então acho justo te dar a diferença. Essa é a minha decisão. Sua parte é de 105 dobrões mais um bônus – um dobrão por rolo. Isso dá 210 dobrões no total. Aqui, pegue.";
			link.l1 = "Obrigado, Marcus!";
			link.l1.go = "mtraxx_18";
		break;
		
		case "mtraxx_18":
			TakeNItems(pchar, "gold_dublon", 210);
			PlaySound("interface\important_item.wav");
            dialog.text = "Mais uma coisa. Você pode tirar um lucro extra com isso.";
			link.l1 = "Interessante... Continue.";
			link.l1.go = "mtraxx_19";
		break;
		
		case "mtraxx_19":
            dialog.text = "Seu comprador quer mais de 100 rolos de seda entregues nos próximos dois meses. Se você tiver, traga de 20 a 100 rolos por 5 dobrões cada. A oferta vale por dois meses.";
			link.l1 = "Tá bom! Eu trago mais se eu tiver.";
			link.l1.go = "mtraxx_20";
			pchar.questTemp.Mtraxx.SilkTrade = "true";
			SetFunctionTimerCondition("Mtraxx_SilkTradeOver", 0, 0, 60, false);
		break;
		
		// торговля шелком
		case "mtraxx_silktrade":
			iTotalTemp = GetSquadronGoods(pchar, GOOD_SHIPSILK);
            dialog.text = "Quanto você tem?";
			link.l1 = ""+FindRussianQtyString(iTotalTemp)+".";
			if (iTotalTemp > 100) link.l1.go = "mtraxx_silktrade_2";
			else link.l1.go = "mtraxx_silktrade_1";
		break;
		
		case "mtraxx_silktrade_1":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, iTotalTemp);
			TakeNItems(pchar, "gold_dublon", iTotalTemp*5);
            dialog.text = "Muito bem. Pegue o ouro - 5 dobrões por jogada, como combinamos.";
			link.l1 = "Obrigado!";
			link.l1.go = "mtraxx_silktrade_3";
		break;
		
		case "mtraxx_silktrade_2":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 100);
			TakeNItems(pchar, "gold_dublon", 500);
            dialog.text = "Vou levar cem rolos. Pegue o ouro - 5 dobrões por rolo, como combinamos.";
			link.l1 = "Gratidão!";
			link.l1.go = "mtraxx_silktrade_3";
		break;
		
		case "mtraxx_silktrade_3":
            DialogExit();
			npchar.dialog.currentnode = "First time";
			DeleteAttribute(pchar, "questTemp.Mtraxx.SilkTrade");
		break;
		
		case "mtraxx_20":
            dialog.text = "Vamos falar de algo mais urgente, quer lidar com alguma coisa perigosa?";
			link.l1 = "Claro! Meus homens e eu estamos prontos para zarpar imediatamente.";
			link.l1.go = "mtraxx_24";
		break;
		
		case "mtraxx_22":
            dialog.text = "Pelo amor de Deus, "+pchar.name+", onde diabos você esteve? Lembra quando eu mandei você vir falar comigo? Eu tinha um trabalho pra você e agora foi pro lixo, graças ao seu ótimo senso de oportunidade. Você me deixou realmente irritado, garoto. Cai fora, não trabalho com gente em quem não posso confiar.";
			link.l1 = "Merda...";
			link.l1.go = "mtraxx_23";
		break;
		
		case "mtraxx_23":
			DialogExit();
            npchar.dialog.currentnode = "First time";
			CloseQuestHeader("Roger_2");
			pchar.questTemp.Mtraxx = "fail";
		break;
		
		case "mtraxx_24":
			// belamour legendary edition даем флаг и лизензию ГВИК если отсутствует -->
			bOk = IsCharacterPerkOn(pchar,"FlagSpa") || IsCharacterPerkOn(pchar,"FlagHol");
			if(CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 40 && bOk) sTemp = ".";
			else 
			{
				if(bOk) 
				{
					if(!CheckCharacterItem(pchar, "HolTradeLicence") || GetDaysContinueNationLicence(HOLLAND) < 40) 
					{
						sTemp = ", as well as a trade license for 40 days."; 
						GiveNationLicence(HOLLAND, 40);
					}
				}
				else // нет флага
				{
					if(!CheckCharacterItem(pchar, "HolTradeLicence")) 
					{
						sTemp = ", as well as a trade license for 40 days. Besides, how are you going to fool the bungler in the fort?! You will let me down one day with such sloppiness... Here you go... You will return it back upon arrival. The new generation, pah...";
						GiveNationLicence(HOLLAND, 40);
						STH_SetJokerFlag(SPAIN, true);
						log_info("You have received spanish flag");
						pchar.questTemp.GiveMeSpaFlag = true;
					}
					else // есть лицензия
					{	
						if(GetDaysContinueNationLicence(HOLLAND) < 40) 
						{
							sTemp = ". Tell me, how are you going to fool the bungler in the fort?! Your paper won't help you without the right flag. I feel that you will let me down one day with such sloppiness... Here, a trading license for 40 days, more than yours. As well as the Spanish flag for landing in Maracaibo. You will return it upon arrival. The new generation, pah...";
							GiveNationLicence(HOLLAND, 40);
							STH_SetJokerFlag(SPAIN, true);
							log_info("You have received spanish flag");
							pchar.questTemp.GiveMeSpaFlag = true;
						}
						else 
						{
							sTemp = ". Tell me, how are you going to fool the bungler in the fort?! Your paper won't help you without the right flag. I feel that you will let me down one day with such sloppiness... Here you go... You will return it back upon arrival. The new generation, pah...";
							STH_SetJokerFlag(SPAIN, true);
							log_info("You have received spanish flag");
							pchar.questTemp.GiveMeSpaFlag = true;
						}
					}
				}
			}
			// <-- legendary edition
            dialog.text = "Then listen closely. Two months ago I had an appointment with a captain by the name of Jean Picard, also known as Jean the Handsome. He didn't show up to the meeting and since I was going to discuss serious matters with him, I did some investigation regarding his whereabouts. Turned out our good brave privateer and his brigantine had managed to engage in a fight with a Spanish heavy galleon under command of don Eduardo de Losad and he is a tough son of a bitch. As a result, Jean and what's left of his crew was taken to Maracaibo and sold to a local plantation. This is where he is, busy with honest labor, at the moment.\nYour tasks are: firstsly - investigate the details of his misfortunes, secondly - get him out from plantation alive and bring him here; I really need details of his story. I am assigning a captain of a barquentine called 'Moray' to assist you in this. Captain's name is Paul Chant also known as Pelly the Cutlass. Remember Geffrey? He is almost as dumb as him, but good at fighting too.\nHe will be waiting for you at cape Ragget Point, on Barbados. Find him and his 'Moray' and sail to Maracaibo. Cutlass will follow your orders without asking stupid questions. Actually, he won't be asking questions at all. Just do your job and come back here, I'll be waiting for you. Here is ten thousand pesos for future expenses"+sTemp+". Any questions?";
			link.l1 = "Não. Tudo certo. Indo para Barbados.";
			link.l1.go = "mtraxx_25";
		break;
		
		case "mtraxx_25":
			AddMoneyToCharacter(pchar, 10000);
            dialog.text = "Então, te desejo sorte. Seja rápido, não faça Cutlass e o pobre Jean esperar.";
			link.l1 = "Claro, chefe! Já estou indo.";
			link.l1.go = "mtraxx_26";
		break;
		
		case "mtraxx_26":
            DialogExit();
			CloseQuestHeader("Roger_2");
			npchar.dialog.currentnode = "mtraxx_wait";
			// belamour legendary edition по пути могут заскочить к Московиту, если рабов нет
			pchar.questTemp.Mtraxx.GiveMeSlaves = "Baster";
			AddQuestRecord("Roger_3", "1");
			AddLandQuestMark(characterFromId("Fadey"), "questmarkmain");
			AddMapQuestMarkCity("baster", false);
			Mtraxx_PlantBegin();
		break;
		
		case "mtraxx_27":
			pchar.quest.Mtraxx_PlantGoHomeOver.over = "yes"; 
            dialog.text = "Bem-vindo de volta, meu bravo corsário, ha-ha! Derrubou um esquadrão espanhol? Picard já me contou. Muito bem feito!";
			link.l1 = "É, meus rapazes deram uma boa surra neles quando estávamos fugindo de Maracaibo.";
			link.l1.go = "mtraxx_28";
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup3"))
			{
				dialog.text = "Bem-vindo de volta, meu bravo corsário, ha-ha! Picard já me contou. Muito bem!";
				link.l1 = "...";
				link.l1.go = "mtraxx_28";
			}
		break;
		
		case "mtraxx_28":
            dialog.text = "Eu vejo nos seus olhos que está esperando sua recompensa. Justo. Jean vai te pagar, afinal, era a vida dele que tentávamos salvar ali. Manda a conta pra ele, mas depois – o garoto não tem tripulação nem navio. Ele é esperto, igual a você, então essa situação dele não vai durar muito.";
			link.l1 = "Hm... Bem... Vou esperar o momento certo. Tem algum trabalho pra mim, Marcus? Nada que envolva salvar ou procurar alguém?";
			link.l1.go = "mtraxx_29";
		break;
		
		case "mtraxx_29":
            dialog.text = "Cansado de ser a vela mais brilhante? Tenho que te decepcionar: já tenho brutamontes sem cérebro como o Cutlass, então vou usar seus talentos de acordo. Tenho um trabalho pra você daqui a um mês. Por enquanto, vá até Isla Tesoro e procure Pasquale Lavoisier, ele é um comerciante de Sharptown.\nEle pediu que mandassem um pirata durão pra ele o quanto antes pra um negócio sério – provavelmente exatamente o que você quer: menos conversa, mais ação. Você tem uma semana pra se apresentar a ele, então não perca tempo ou vai perder essa missão. E seja educado, não tente enganá-lo, esse homem é respeitado entre os Irmãos. Agora vá, e me procure daqui a um mês. Não se atrase!";
			link.l1 = "Tá bom, Marcus. Até mais!";
			link.l1.go = "mtraxx_30";
		break;
		
		case "mtraxx_30":
            DialogExit();
			// belamour legendary edition забрать флаг обратно
			if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
			{
				DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
				STH_SetJokerFlag(SPAIN, false); 
				log_info("You have given spanish flag");
			}
			CloseQuestHeader("Roger_3");
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_4", "1");
			pchar.questTemp.Mtraxx = "pasq_start";
			Mtraxx_PasqualeBegin();
			SetFunctionTimerCondition("Mtraxx_PlantFithTaskTimer", 0, 0, 35, false);
			SaveCurrentNpcQuestDateParam(npchar, "task_date");
		break;
		
		case "mtraxx_31":
            dialog.text = "Opa! Um morto voltou! A gente já tinha te enterrado, garoto! Mas pelo visto você ainda está vivo";
			link.l1 = "Como você pode ver, Marcus...";
			link.l1.go = "mtraxx_32";
		break;
		
		case "mtraxx_32":
            dialog.text = "Então por que demorou tanto pra chegar de Maracaibo até Hispaniola? Você está fora da minha organização agora, garoto. Fico realmente feliz em ver que está vivo, mas aqui não tem mais trabalho pra você.";
			link.l1 = "Eh!.. Que pena...";
			link.l1.go = "mtraxx_33";
		break;
		
		case "mtraxx_33":
            DialogExit();
            npchar.dialog.currentnode = "First time";
			pchar.questTemp.Mtraxx = "fail";
		break;
		
		case "mtraxx_34x":
            DialogExit();
            npchar.dialog.currentnode = "mtraxx_34";
		break;
		
		case "mtraxx_34":
			/*if (GetNpcQuestPastDayParam(npchar, "task_date") >= 35 && !bImCasual) // опоздал
			{
				dialog.text = "Maldição "+pchar.name+", onde você esteve?! Eu mandei você me procurar em um mês! Isso aqui não é o exército, mas um mínimo de disciplina é o esperado! Cai fora, não vou mais trabalhar com você!";
				link.l1 = "Como quiser...";
				link.l1.go = "mtraxx_33";
				break;
			}*/
			if (GetNpcQuestPastDayParam(npchar, "task_date") < 28) // рано пришёл
			{
				dialog.text = ""+pchar.name+", eu te disse 'me procure daqui a um mês.' Não tenho tempo pra você agora.";
				link.l1 = "Tudo bem...";
				link.l1.go = "mtraxx_34x";
				break;
			}
			if (pchar.questTemp.Mtraxx == "pasq_angry")
			{
				dialog.text = "Um agente do Lavoisier me contou que você passou a perna nele com aquela madeira preta. Eu te avisei para não ser um rato e tratar o Pasquale com justiça. Você quebrou as duas regras. Você é esperto, garoto, mas isso é inaceitável. Cai fora daqui e esquece o caminho pra este lugar.";
				link.l1 = "Merda...";
				link.l1.go = "AngryExitAgainWithOut";
				pchar.questTemp.Mtraxx = "fail";
				npchar.dialog.currentnode = "First time";
				CloseQuestHeader("Roger_4");
				break;
			}
			if (pchar.questTemp.Mtraxx == "pasq_fail")
			{
				dialog.text = "Um agente do Lavoisier me contou que você passou a perna nele com a madeira negra – não entregou o lote inteiro. Se fosse um Cutlass ou Bald sem cérebro, talvez eu acreditasse que não pegaram tudo mesmo, mas alguém esperto como você... Resolveu enganar o Pasquale? Eu te avisei: 'não engane ele'! Não confio mais em você, e também não faço mais negócios contigo. Cai fora daqui e esquece o caminho pra este lugar!";
				link.l1 = "Esse seu Lavoisier é um rato também!";
				link.l1.go = "AngryExitAgainWithOut";
				pchar.questTemp.Mtraxx = "fail";
				npchar.dialog.currentnode = "First time";
				CloseQuestHeader("Roger_4");
				break;
			}
			if (pchar.questTemp.Mtraxx == "pasq_late" || pchar.questTemp.Mtraxx == "pasq_sink" || pchar.questTemp.Mtraxx == "pasq_esc")
			{
				pchar.questTemp.Mtraxx.CharleePrince = "true"; // атрибут - ГГ известный пират // правки прогона 3
				dialog.text = "Ha! Charlie Prince, um capitão valente! Esse é o seu novo nome em La Vega, caso não soubesse. E aí, gostou de bancar o brutamontes? Não? A sorte te virou as costas dessa vez? É assim que vivem meus agentes sem cérebro, como o Cutlass: hoje ele se esbalda num bordel, torrando tudo o que ganhou, e na semana seguinte aparece na minha porta pedindo uns milhares pra pagar a tripulação de idiotas igual a ele. Enfim. Vamos falar de negócios?";
				link.l1 = "Claro!";
				link.l1.go = "mtraxx_36";
				break;
			}
            dialog.text = "Ha! Charlie Prince, um capitão corajoso! Ha-ha! Um agente do Lavoisier me contou que você se saiu bem. Fico feliz que tenha conseguido mostrar um pouco de respeito ao nosso agiota.";
			link.l1 = "Não faria mal se ele fosse um pouco mais generoso...";
			link.l1.go = "mtraxx_35";
		break;
		
		case "mtraxx_35":
			pchar.questTemp.Mtraxx.Pasquale.Continue = "true"; // правки прогона 3
            dialog.text = "Lembra do que eu disse sobre brutamontes sem cérebro e compradores de mercadoria roubada? Isso mesmo. Nunca aceite um trabalho desses no futuro. Deixe isso para o Cutlass e gente como ele. Enfim. Vamos falar de negócios?";
			link.l1 = "Claro!";
			link.l1.go = "mtraxx_36";
		break;
		
		case "mtraxx_36":
            dialog.text = "Ótimo! Jean Picard está vindo pra cá, ele vai te contar mais. Você e Jean vão trabalhar juntos nessa missão. Além disso, é a chance dele pagar a dívida que tem com você... Olha ele aí!";
			link.l1 = "...";
			link.l1.go = "mtraxx_37";
		break;
		
		case "mtraxx_37":
            DialogExit();
            npchar.dialog.currentnode = "mtraxx_38";
			chrDisableReloadToLocation = true;
			// преобразуем Пикара
			sld = characterFromId("Mrt_Rocur");
			sld.model = "Jan_Pikar";
		
			SetCharacterPerk(sld, "GunProfessional");
			RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
			GiveItem2Character(sld, "blade_17");
			EquipCharacterbyItem(sld, "blade_17");
			GiveItem2Character(sld, "pistol6");
			EquipCharacterbyItem(sld, "pistol6");
			TakeNItems(sld, "bullet", 40);
			TakeNItems(sld, "gunpowder", 40);
			LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
			GiveItem2Character(sld, "cirass7");
			EquipCharacterbyItem(sld, "cirass7");
			sld.dialog.currentnode = "rocur_29";
			sld.greeting = "Rocur_03";
			Characters_RefreshModel(sld);
			LAi_SetCheckMinHP(sld, 10, true, "");
			TakeNItems(sld, "potion2", 7);
			TakeNItems(sld, "potion3", 7);
			TakeNItems(sld, "potion4", 7);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "mtraxx_38":
            dialog.text = "My man will join your raid. Name's Luka Bayard, mostly known as Luke Leprechaun. He and his men are buccaneers—hunters who have spent most of their lives in the forests of Hispaniola. So they are masters at trekking through the jungle; add your fighters to theirs and consider Merida yours. You'll take a third of the loot. The rest goes to Jean. Jean, you'll pay your debt to this brave captain from your share, then bring what's left to me. We'll settle things between us then. Questions? Splendid! Leprechaun will be waiting for you in our harbour. Good luck, corsairs, ha-ha!";
			link.l1 = "...";
			link.l1.go = "mtraxx_39";
		break;
		
		case "mtraxx_39":
            DialogExit();
			CloseQuestHeader("Roger_4");
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_5", "1");
			pchar.questTemp.Mtraxx = "merida_start";
			Mtraxx_MeridaBegin();
			LAi_SetHuberType(npchar);
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "Mtraxx_MeridaAddPicar", 5.0);
			pchar.GenQuest.HunterLongPause = true;
		break;
		
		case "mtraxx_40":
            dialog.text = "Bem-vindo de volta, meu bravo canalha! Já chegou até nós a notícia do seu ataque.";
			link.l1 = "Não posso dizer que gosto de ouvir isso. Certas coisas é melhor deixar no desconhecido...";
			link.l1.go = "mtraxx_41";
		break;
		
		case "mtraxx_41":
            dialog.text = "Confie em mim, nunca são, meu amigo. Tanto faz. O Picard já pagou a dívida dele com você?";
			link.l1 = "Sim.";
			link.l1.go = "mtraxx_42";
		break;
		
		case "mtraxx_42":
            dialog.text = "Muito bem. O Luke Leprechaun te causou uma boa impressão?";
			link.l1 = "Ele fez isso.";
			link.l1.go = "mtraxx_43";
		break;
		
		case "mtraxx_43":
            dialog.text = "Perfeito então. Todo mundo está feliz, todo mundo recebeu o seu.";
			link.l1 = "Tem algum trabalho pra mim, Marcus?";
			link.l1.go = "mtraxx_44";
			// belamour legendary edition отказ после событий Мериды
			link.l2 = "Sabe, Marcus, eu pensei bem e esse trabalho não é pra mim. Me desculpe, mas já tomei minha decisão.";
			link.l2.go = "mtraxx_44a";
		break;
		
		case "mtraxx_44":
            dialog.text = "Ainda não tenho nenhum trabalho de verdade. Mas tenho um favor pessoal pra pedir. Se interessa?";
			link.l1 = "Claro, chefe. Que favor?";
			link.l1.go = "mtraxx_45";
		break;
		
		case "mtraxx_45":
            dialog.text = "Há uma pinassa, 'Kittie', perto das margens de La Vega. Ela está lá há dias, esperando uma escolta para Bridgetown. Não vou deixar ela navegar sozinha até lá, por motivos óbvios. Você seria gentil o bastante para acompanhá-la? Terei um trabalho de verdade para você quando voltar. E, claro, dinheiro para te pagar por essa escolta.";
			link.l1 = "Fechado.";
			link.l1.go = "mtraxx_46";
		break;
		
		case "mtraxx_46":
            dialog.text = "Boa! Mandou bem na navegação.";
			link.l1 = "Valeu!";
			link.l1.go = "mtraxx_47";
		break;
		
		case "mtraxx_47":
            DialogExit();
			sld = characterFromId("Mrt_Rocur");
			RemovePassenger(pchar, sld);
			sld = characterFromId("Lepricon");
			RemovePassenger(pchar, sld);
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "none", "", "");
			CloseQuestHeader("Roger_5");
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_6", "1");
			pchar.questTemp.Mtraxx = "ignasio_start";
			sld = characterFromId("Mtr_KittyCap");
			DeleteAttribute(sld, "DontDeskTalk");
			LocatorReloadEnterDisable("LaVega_port", "boat", false);
		break;
		// belamour legendary edition -->
		case "mtraxx_44a":
            dialog.text = "O quê?! Eu te tirei das ruas, enchi seus bolsos de âmbar e pedras preciosas! É assim que você me retribui?";
			link.l1 = "Merida me mostrou que eu não sou implacável o bastante para este trabalho. Não tão implacável quanto você e seus homens. Não seja cruel.";
			link.l1.go = "mtraxx_45a";
		break;
		
		case "mtraxx_45a":
            dialog.text = "Fraco! Então, cai fora! Vai carregar carga ou, melhor ainda, vai beber até morrer como o resto dos fracassados!";
			link.l1 = "...";
			link.l1.go = "mtraxx_46a";
		break;
		
		case "mtraxx_46a":
            DialogExit();
			sld = characterFromId("Mrt_Rocur");
			RemovePassenger(pchar, sld);
			sld = characterFromId("Lepricon");
			RemovePassenger(pchar, sld);
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "none", "", "");
			CloseQuestHeader("Roger_5");
			npchar.dialog.currentnode = "First time";
			Group_DelCharacter("Mtr_Kitty", "Mtr_KittyCap");
			sld = characterFromId("Mtr_KittyCap");
			sld.lifeday = 0;
			LocatorReloadEnterDisable("LaVega_port", "boat", false);
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.questTemp.Mtraxx = "fail";
			if(CheckAttribute(pchar, "GenQuest.HunterLongPause")) DeleteAttribute(pchar, "GenQuest.HunterLongPause");
			DoQuestReloadToLocation("LaVega_town", "reload", "reload6", ""); // выставим за дверь
		break;
		// <--- legendary edition
		case "mtraxx_48":
			AddMoneyToCharacter(pchar, 10000);
            dialog.text = "Ah, aí está você... Estava te esperando. Aqui estão 10.000 pelo escolta da 'Kittie'.";
			link.l1 = "Obrigado... Tenho algo para discutir com você, Marcus.";
			link.l1.go = "mtraxx_49";
		break;
		
		case "mtraxx_49":
            dialog.text = "É mesmo?! Ha-ha! Atira!..";
			link.l1 = "Lembra como Jean Picard foi escravizado? Primeiro, ele saqueou uma caravana holandesa com um corsário britânico, e depois fizeram o mesmo com ele num galeão espanhol pesado.";
			link.l1.go = "mtraxx_50";
		break;
		
		case "mtraxx_50":
            dialog.text = "Lembre-se. E daí?";
			link.l1 = "Fui abordado em Bridgetown por Ignacio Marco. O mesmo corsário português que serve à Inglaterra. Ele me ofereceu a chance de saquear uma caravana holandesa perto das costas de uma ilha desabitada entre Curaçao e Trinidad.";
			link.l1.go = "mtraxx_51";
		break;
		
		case "mtraxx_51":
            dialog.text = "Então, então... Você concordou?";
			link.l1 = "Eu fiz. Primeiro, era um bom negócio. Segundo, lembrei da história do Picard e decidi investigar...";
			link.l1.go = "mtraxx_52";
		break;
		
		case "mtraxx_52":
            dialog.text = "Eu aposto que sim.";
			link.l1 = "É. Tinha uma caravana, fizemos o serviço direitinho, sem deixar rastros. Depois dividimos o saque em terra firme, mas antes mandei discretamente um vigia com luneta subir no morro. Valeu a pena, porque logo depois apareceu um esquadrão espanhol, liderado por um galeão pesado.";
			link.l1.go = "mtraxx_53";
		break;
		
		case "mtraxx_53":
            dialog.text = "Seu parceiro certamente fugiu, então os espanhóis vieram atrás de você?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.LosadaSink")) 
			{
				link.l1 = "Exatamente. Eles nem deram atenção pra ele. Azar o deles: lutamos tanto contra os espanhóis que eles nunca vão esquecer. Aqueles castelhanos eram bons de briga, mas conseguimos derrubar o esquadrão inteiro.";
				link.l1.go = "mtraxx_53x";
			}
			else
			{
				link.l1 = "Exatamente. Eles nem deram atenção pra ele. Apesar de eu ter conseguido escapar, graças ao meu vigia...";
				link.l1.go = "mtraxx_53y";
			}
		break;
		
		case "mtraxx_53x":
			DeleteAttribute(pchar, "questTemp.Mtraxx.LosadaSink");
            dialog.text = "Heh! Derrubar um esquadrão do Eduardo de Losad! Você é um Demônio do Mar, Príncipe! Aposto que os espanhóis já mandaram caçadores atrás da sua cabeça.";
			link.l1 = "Pior pra eles... Mesmo assim, temos que lidar com essa escória, Ignacio. Se é que me entende.";
			link.l1.go = "mtraxx_54";
		break;
		
		case "mtraxx_53y":
            dialog.text = "Heh! Só posso imaginar o caos que foi quando os castelhanos perceberam que você escapou deles! Mandou bem!";
			link.l1 = "O problema é deles, não meu. Mesmo assim, temos que lidar com essa escória, Ignacio. Se é que você me entende.";
			link.l1.go = "mtraxx_54";
		break;
		
		case "mtraxx_54":
            dialog.text = "Deixa comigo. Precisamos descobrir mais sobre esse Ignacio Marco. Ele pode estar a serviço de alguém. Esse 'interesse' dele nos meus homens é suspeito. Que navio ele comanda?";
			link.l1 = "Uma polaca, a 'Torero'. Um navio único, deve ser um projeto original.";
			link.l1.go = "mtraxx_55";
		break;
		
		case "mtraxx_55":
            dialog.text = "Ótimo, vai ser mais fácil rastrear ela então... Entendi. E pra você, Príncipe, tenho um trabalho. Pronto pra isso?";
			link.l1 = RandSwear()+"Claro, chefe!";
			link.l1.go = "mtraxx_56";
		break;
		
		case "mtraxx_56":
            dialog.text = "Então escute. Há algum tempo tivemos um pirata curioso na nossa região. O nome dele é Wulfric Iogansen, também conhecido como Lobo Vermelho. Um sujeito bem peculiar. Ele veio do norte da Europa faz alguns anos. Esse viking não pagava a taxa de proteção do Levasseur, não fazia amizades e vivia na dele. Era muito reservado, ninguém nunca saiu vivo da tripulação dele. Diziam que ele mesmo arrancava a língua de quem falava demais nas tavernas sobre as pilhagens... Diferente da maioria de nós, Wulfric nunca gastava dinheiro com prostitutas ou bebida. Nunca vendeu o saque por mixaria. Não confiava em banqueiros e nunca trocou de navio. Tinha uma bela corveta, a 'Freyja', e uma tripulação fiel que ele pagava bem pelo serviço e pelo silêncio. Acho que ele planejava juntar o máximo de ouro possível e depois voltar pra Europa pra viver como um rei. Não deu certo pra ele, graças aos caçadores espanhóis. Esse homem causou enormes prejuízos à Espanha, então expedições punitivas caçaram ele nas águas de Hispaniola, afundaram a 'Freyja' e mataram toda a tripulação junto com o Lobo. Cercado em águas rasas por navios espanhóis, o Lobo Vermelho encontrou a morte. O negócio é o seguinte: todo mundo em La Vega sabia dos tesouros do Lobo e até acharam a 'Freyja' afundada, mas nem os mergulhadores locais nem os índios acharam tesouro nenhum. Ele não era burro e deve ter escondido uma fortuna em algum lugar que só ele e a tripulação sabiam, mas não dá pra perguntar pra eles... por motivos óbvios. Agora vem a parte interessante: eu tenho o diário de bordo dele, intacto, que estava escondido num baú trancado no navio. Não tem pistas óbvias do tesouro, mas talvez você encontre alguma coisa nas entrelinhas. Leia o diário, descubra onde o viking escondeu os tesouros depois de dois anos roubando no Caribe, e encontre-os. Se conseguir – dois terços são seus. Vai encarar?";
			link.l1 = "Hm... parece que estamos procurando uma agulha no palheiro. Cadê o registro?";
			link.l1.go = "mtraxx_57";
		break;
		
		case "mtraxx_57":
            dialog.text = "Aqui, pega. Boa sorte!";
			link.l1 = "Valeu, vou precisar mesmo...";
			link.l1.go = "mtraxx_58";
		break;
		
		case "mtraxx_58":
            DialogExit();
			CloseQuestHeader("Roger_6");
			npchar.dialog.currentnode = "mtraxx_wait";
			GiveItem2Character(pchar, "wolfreeks_book");
			AddQuestRecord("Roger_7", "1");
			pchar.questTemp.Mtraxx = "wolfreek_start";
			pchar.questTemp.Mtraxx.Logbook.CanRead = "true";
			pchar.questTemp.Mtraxx.Logbook.Page1 = "true";
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true;
		break;
		
		case "mtraxx_59":
            dialog.text = "Ah, aí está o nosso capitão corajoso. E o tesouro do Lobo Vermelho?";
			link.l1 = "Estou trabalhando nisso. Preciso da sua ajuda com isso.";
			link.l1.go = "mtraxx_60";
		break;
		
		case "mtraxx_60":
            dialog.text = "Estou ouvindo.";
			link.l1 = "Há uma palavra desconhecida escrita várias vezes no diário de Wulfric, 'Gord'. Preciso saber o que significa para avançar na minha investigação.";
			link.l1.go = "mtraxx_61";
		break;
		
		case "mtraxx_61":
            dialog.text = "Hm... Gord, você diz... Nunca ouvi falar disso também. Muito bem, volte daqui a uma semana: vou consultar algumas cabeças espertas que trabalham como intendentes nos navios. Pelo menos eles sabem contar e ler. Talvez nos deem alguma ideia.";
			link.l1 = "Certo, Marcus. Então até daqui a uma semana.";
			link.l1.go = "mtraxx_62";
		break;
		
		case "mtraxx_62":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			SetFunctionTimerCondition("Mtraxx_WolfreekTimer", 0, 0, 7, false);
		break;
		
		case "mtraxx_63":
            dialog.text = "Tenho uma resposta pra você. Um espertinho me explicou. Um gord é um assentamento fortificado de um jarl livre.";
			link.l1 = "Um jarl livre? Quem é esse?";
			link.l1.go = "mtraxx_64";
		break;
		
		case "mtraxx_64":
            dialog.text = "Um tipo de almirante pirata dos vikings. Por exemplo, eu sou um jarl livre e La Vega é meu gord. Parece que o Lobo Vermelho gostava da história dos antepassados dele, ha-ha! Essas informações te ajudaram?";
			link.l1 = "Ainda não sei. Preciso comparar as anotações primeiro. Então Gord significa assentamento... Obrigado, Marcus!";
			link.l1.go = "mtraxx_65";
		break;
		
		case "mtraxx_65":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			Mtraxx_WolfreekReadLogbookFourth();
		break;
		
		case "mtraxx_66":
            dialog.text = "E aí? Essa sua cara de satisfeito me diz que você conseguiu.";
			link.l1 = "É. O tesouro do Lobo Vermelho foi encontrado! Mas não foi nada fácil.";
			link.l1.go = "mtraxx_67";
		break;
		
		case "mtraxx_67":
            dialog.text = "Quanto o nosso Viking escondeu?";
			link.l1 = "750.000 pesos e 900 dobrões.";
			link.l1.go = "mtraxx_68";
		break;
		
		case "mtraxx_68":
            dialog.text = "Ho-ho! Mandou bem, Príncipe. E a minha parte?";
			if (sti(pchar.money) >= 250000 && PCharDublonsTotal() >= 300) // belamour legendary edition
			{
				link.l1 = "Aqui, pega isso. Como combinado: 250.000 pesos e 300 dobrões.";
				link.l1.go = "mtraxx_69";
			}
			else
			{
				link.l1 = "Todos os pesos e dobrões estão na minha cabine. Me dê um momento para trazê-los aqui!";
				link.l1.go = "mtraxx_68_1";
			}
		break;
		
		case "mtraxx_68_1":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_68_2";
		break;
		
		case "mtraxx_68_2":
            dialog.text = "Trouxe a minha parte?";
			if (sti(pchar.money) >= 250000 && PCharDublonsTotal() >= 300) // belamour legendary edition
			{
				link.l1 = "Aqui, pegue isto. Como combinado: 250.000 pesos e 300 dobrões.";
				link.l1.go = "mtraxx_69";
			}
			else
			{
				link.l1 = "Sim, sim, estou a caminho!";
				link.l1.go = "mtraxx_68_1";
			}
		break;
		
		case "mtraxx_69":
			AddMoneyToCharacter(pchar, -250000);
			RemoveDublonsFromPCharTotal(300); // belamour legendary edition
			PlaySound("interface\important_item.wav");
            dialog.text = "Muito bom. Você mandou bem de novo. Parabéns!";
			link.l1 = "Marcus, descobriu alguma coisa sobre Ignacio Marco?";
			link.l1.go = "mtraxx_70";
			// mitrokosta возможность отстройки исламоны
			pchar.questTemp.IslaMona = "start";
		break;
		
		case "mtraxx_70":
            dialog.text = "Sim, mas preciso verificar primeiro...";
			link.l1 = "O quê?";
			link.l1.go = "mtraxx_71";
		break;
		
		case "mtraxx_71":
            dialog.text = "Tenho uma suspeita de que o Marco está ligado a alguém... E preciso que você descubra quem. Navegue até Martinica. Deixe seu navio em Saint Pierre e siga até Le Francois pela selva. Disseram que nosso homem foi visto por lá. Não fale com os piratas da região, apenas observe e fique de olho. Quando encontrá-lo, siga-o e veja para onde ele vai ou com quem se encontra. Não ataque ele nem o navio dele, porque se fizer isso vai estragar um plano que estou preparando agora! Estou avisando! Siga e observe, depois volte para mim quando souber o suficiente. Sei que você está louco para estrangular esse desgraçado, mas mantenha a cabeça fria. Agora vá. Você tem três semanas. Boa sorte.";
			link.l1 = "Já estou indo, chefe.";
			link.l1.go = "mtraxx_72";
		break;
		
		case "mtraxx_72":
            DialogExit();
			CloseQuestHeader("Roger_7");
			RemoveItems(pchar, "wolfreeks_book", 1);
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_8", "1");
			pchar.questTemp.Mtraxx = "corrida_start";
			pchar.quest.mtraxx_corrida_martinique.win_condition.l1 = "location";
			pchar.quest.mtraxx_corrida_martinique.win_condition.l1.location = "Martinique";
			pchar.quest.mtraxx_corrida_martinique.function = "Mtraxx_CorridaStart";
			pchar.quest.mtraxx_pasq_continue.win_condition.l1 = "location";
			pchar.quest.mtraxx_pasq_continue.win_condition.l1.location = "LaVega_exittown";
			pchar.quest.mtraxx_pasq_continue.function = "Mtraxx_PasqualeJan";
			bDisableFastReload = true;
			//SaveCurrentNpcQuestDateParam(npchar, "task_date");
		break;
			
		case "mtraxx_73":
			/*if (GetNpcQuestPastDayParam(npchar, "task_date") >= 22) // опоздал
			{
				dialog.text = "Droga, Príncipe! Você poderia ter conseguido sua vingança e uma bela grana se não fosse tão lento! Não esperava isso de você, mas como é um bom garoto, vou te perdoar. Você vai ter a chance de recuperar sua reputação comigo daqui a um mês. Estou reunindo todo mundo para um ataque!\nVenha até mim daqui a um mês com um navio só, mas poderoso. Luke, Cutlass, Geffrey e Jean também vão participar. Não se atrase, nem um dia!";
				link.l1 = "Entendi, Marcus. Não vai acontecer de novo!";
				link.l1.go = "mtraxx_73x";
				break;
			}*/
			dialog.text = "Chegou na hora certa! Faça seu relatório, agora.";
			link.l1 = "I've tracked my obligor to Le Francois. His polacre was part of a squadron consisting of a corvette and a frigate. Marco himself paid a visit to Barbaszon; they had a meeting at his place for two hours, and other visitors were sent away by his guards. Then he left the house with two gloomy fellows: one was red-haired and bearded, wearing a reiter cuirass; the other had a moustache and wore heavy trench armour. They all went to the port and sailed away before I reached Saint Pierre.";
			link.l1.go = "mtraxx_74";
		break;
		
		/*case "mtraxx_73x":
            DialogExit();
            npchar.dialog.currentnode = "First time";
			pchar.questTemp.Mtraxx = "wait_month";
			AddQuestRecord("Roger_8", "5");
			SetFunctionTimerCondition("Mtraxx_CartahenaTavernPrepare", 0, 0, 1, false); // belamour legendary edition увеличим таймер 
			SetFunctionTimerCondition("Mtraxx_CartahenaPrepare", 0, 0, 1, false);
			SetFunctionTimerCondition("Mtraxx_CartahenaLate", 0, 0, 92, false);
		break;*/
		
		case "mtraxx_74":
            dialog.text = "Está certo. Agora entendi tudo. Aqueles dois desgraçados que você viu trabalham ou para o Barbazon ou para o Jackman. São quase como meus Bald e Cutlass, mas lutam melhor. O ruivo se chama Prowler, é capitão do 'Cuttlefish', uma corveta, e o sujeito de bigode é o Ghoul, que comanda a 'Merciless', uma fragata. Quanto ao nosso amigo Ignacio – ele trabalha não só para os ingleses e para o espanhol dom Losad, mas também para o Barbazon. Por isso ele tentou armar pra você e pro Picard.";
			link.l1 = "Por quê?";
			link.l1.go = "mtraxx_75";
		break;
		
		case "mtraxx_75":
            dialog.text = "Ordem do Barbazon. Você não sabia, mas o Jacques nunca perde uma chance de estragar meu dia. Ele nunca se oporia a mim abertamente, por motivos óbvios, então me atravessa pelas costas. Ele sabia que Picard e você são meus homens. Mandar o mercenário dele atrás de você é bem a cara dele, e não mandou nenhum idiota, como você mesmo viu.";
			link.l1 = "Vou fazer uma visita ao Barbazon assim que resolver o caso do Marco...";
			link.l1.go = "mtraxx_76";
		break;
		
		case "mtraxx_76":
            dialog.text = "Tira essa merda da sua cabeça! Você não tem chance contra o Barbazon em um confronto direto. Ele vai acabar com você sem esforço. Vamos pagar na mesma moeda — atacando os comparsas dele. Pronto pra isso? Vai ser um serviço sujo.";
			link.l1 = "Parece o tipo de negócio que eu gosto!";
			link.l1.go = "mtraxx_77";
		break;
		
		case "mtraxx_77":
            dialog.text = "Ignacio Marco, Prowler, Goul e outro dos homens do Barbazon chamado Joker Jim têm um plano para capturar um dos navios espanhóis da Frota Dourada. Toda a operação foi arquitetada pelo próprio Barbazon, e consegui descobrir os detalhes através dos meus espiões. Um galeão pesado da Frota Dourada ficou em Havana no estaleiro, enquanto o resto do esquadrão partiu para a Espanha. O galeão foi consertado e logo seguirá para a Europa, junto com mais dois navios. O esquadrão vai zarpar de Cuba para o nordeste, mas não sei a rota exata.   Fui informado de que os navios espanhóis pretendem navegar até Santo Domingo, depois costeando Porto Rico e indo direto para o oceano. Barbazon também sabe disso. No entanto, como Hispaniola pode ser contornada não só pelo sul, mas também pelo norte, mudando a rota e saindo para o oceano pelos lados de Turks ou Isla-Tesoro sem passar por Santo Domingo, Jacques resolveu não arriscar e mandou a raposa astuta do Ignacio para Cuba.   A tarefa do Marco é conseguir o cronograma de partida do galeão espanhol que vai sair de Cuba e deve alcançar o resto da Frota depois. Ele tem contatos entre os espanhóis, então isso não deve ser problema para ele. O resto do bando do Barbazon está esperando o Marco em Saint Martin, que é o lugar ideal para começar a caçada a esse prêmio. Como Marco e os holandeses não se dão bem, ele não vai poder entrar nas águas de Saint Martin, então vai ter que mandar um recado para os comparsas de longe...";
			link.l1 = "Acho que já sei o que devo fazer aqui...";
			link.l1.go = "mtraxx_78";
		break;
		
		case "mtraxx_78":
            dialog.text = "Me parece que você é bem esperto, mas ainda não terminei. Eu atrapalhei esse plano com a ajuda da Gabriela Chapada. Você a conhece. Juntos, avisamos aos espanhóis que a emboscada dos piratas seria armada não muito longe de Porto Rico. Então o galeão não vai passar por aquela área, mas eles mandaram secretamente um esquadrão de caçadores de piratas pra lá. Você tem algumas tarefas. A primeira é encontrar e capturar o 'Torero'. Imagino que você saiba o que fazer com o capitão dele.";
			link.l1 = "Naturalmente...";
			link.l1.go = "mtraxx_79";
		break;
		
		case "mtraxx_79":
            dialog.text = "Em segundo lugar, você vai precisar descobrir a verdadeira rota do galeão espanhol de ouro. O Marco deve ter o itinerário dele. Pegue isso e me envie.";
			link.l1 = "Como?";
			link.l1.go = "mtraxx_80";
		break;
		
		case "mtraxx_80":
			GiveItem2Character(pchar, "Dove"); 
            dialog.text = "Pelo ar. Pegue uma gaiola... Este é o Spyke, um pombo-correio nascido e criado aqui em La Vega. Ele sempre vai encontrar o caminho de volta pra cá, até mesmo vindo de Trinidad. Assim que conseguir o cronograma, escreva um bilhete, prenda na perna dele e solte-o. O Spyke vai voar até mim em poucas horas. Cuide bem dele, Príncipe!";
			link.l1 = "Claro, chefe!";
			link.l1.go = "mtraxx_81";
		break;
		
		case "mtraxx_81":
            dialog.text = "Terceiro, navegue até Saint Martin no 'Torero'. Só nele, entendeu? Se não, eles vão desconfiar muito rápido. Mande um sinal para eles seguirem para Porto Rico, onde os espanhóis estão esperando. Os códigos de sinal deles devem estar nos papéis do Marco. Ou você pode aprender direto com ele.";
			link.l1 = "Entendi. Mandar os homens do Barbazon para os espanhóis foi um lance esperto, ha-ha!";
			link.l1.go = "mtraxx_82";
		break;
		
		case "mtraxx_82":
            dialog.text = "Exatamente! Vou atacá-lo pelas sombras. Do mesmo jeito que ele fez. E mais uma coisa: assim que você mandar o sinal, zarpe imediatamente para interceptar a galera espanhola e sua escolta. Não haverá tempo a perder.";
			link.l1 = "Em uma polaca? Contra um galeão pesado e mais dois navios, e com certeza nenhum escuna? Eles vão me destruir!";
			link.l1.go = "mtraxx_83";
		break;
		
		case "mtraxx_83":
            dialog.text = "Pare de chorar como uma garotinha! Por que acha que vai me mandar o Spyke? Você não vai ficar sem reforços. Só não deixe a caravana escapar, não deixe eles chegarem ao oceano. Entendeu?";
			link.l1 = "Sim, chefe.";
			link.l1.go = "mtraxx_84";
		break;
		
		case "mtraxx_84":
            dialog.text = "Sua recompensa vai ser uma bela pilha de ouro, além da polaca do Marco. Dizem que é um navio do caralho. Alguma dúvida? Entendeu sua missão?";
			link.l1 = "Eu não sou o Cutlass, eu sei o que fazer. Onde devo interceptar o 'Torero'?";
			link.l1.go = "mtraxx_85";
		break;
		
		case "mtraxx_85":
            dialog.text = "Enquanto estamos aqui conversando, o navio está navegando rápido direto de Cuba para Philipsburg. Deve estar perto de Tortuga agora, ou um pouco a leste dela. Então levante âncora e siga para Saint Martin, intercepte o 'Torero' não muito longe da ilha, só não deixe os homens do Barbazon verem a briga, senão meu plano vai por água abaixo.";
			link.l1 = "Já vou!";
			// belamour legendary edition испанский флаг к выдаче -->
			if(IsCharacterPerkOn(pchar,"FlagSpa")) link.l1.go = "mtraxx_86";
			else link.l1.go = "mtraxx_85f";
		break;
		
		case "mtraxx_85f":
			STH_SetJokerFlag(SPAIN, true);
			log_info("You have received a spanish flag");
			pchar.questTemp.GiveMeSpaFlag = true;
            dialog.text = "Que diabos? Eu te daria uma paulada com um atiçador de lareira, Príncipe. Não achei que teria que explicar coisas tão básicas. Segure firme a bandeira espanhola, ou vai estragar tudo antes mesmo de começar. Me devolva isso. Agora suma daqui!";
			link.l1 = "Já estou no mar, chefe";
			link.l1.go = "mtraxx_86";
		break;
		// <-- legendary edition
		case "mtraxx_86":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			AddQuestRecord("Roger_8", "6");
			pchar.questTemp.Mtraxx = "corrida_marko";
			/*pchar.quest.mtraxx_corrida_landtimer.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.hour  = sti(GetTime()+1);
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.mtraxx_corrida_landtimer.function = "Mtraxx_CorridaLandTimer";
			pchar.quest.mtraxx_corrida_checktime.win_condition.l1 = "location";
			pchar.quest.mtraxx_corrida_checktime.win_condition.l1.location = "Hispaniola1";
			pchar.quest.mtraxx_corrida_checktime.function = "Mtraxx_CorridaCheckTime";*/
			pchar.quest.mtraxx_corrida_torero.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.hour  = sti(GetTime()+12);
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtraxx_corrida_torero.function = "Mtraxx_CorridaToreroOnMap";
			SetFunctionTimerCondition("Mtraxx_CorridaTimeFindTorero", 0, 0, 7, false); // время на перехват Тореро, снимать при потоплении или захвате
		break;
		
		case "mtraxx_87":
            dialog.text = "Então, Príncipe, você estraga tudo, né?";
			link.l1 = "Eu consegui. Essa missão foi um desafio muito maior do que eu esperava. Pode me dar um sermão furioso e me mostrar a porta.";
			link.l1.go = "mtraxx_88";
		break;
		
		case "mtraxx_88": // belamour legendary edition увеличиваем срок
            dialog.text = "Vamos lá, deixa disso. Acontece. Você é um bom corsário e todos nós falhamos de vez em quando. Pena que não pegamos aquele ouro... mas se não foi em um lugar, vai ser em outro, ha-ha! Você vai ter a chance de recuperar sua reputação: venha me procurar em três semanas, e de preferência com um navio mais forte, mas só um - vamos ser um verdadeiro esquadrão. Estou reunindo todo mundo para um ataque!\nVenha me procurar em três semanas com um único navio, mas poderoso. Luke, Cutlass, Geffrey e Jean também vão participar. Não se atrase!";
			link.l1 = "Não vou, chefe!";
			link.l1.go = "mtraxx_89";
		break;
		
		case "mtraxx_89":
            DialogExit();
			// belamour legendary edition забрать флаг обратно
			if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
			{
				DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
				STH_SetJokerFlag(SPAIN, false); 
				log_info("You have given a spanish flag");
			}
			npchar.dialog.currentnode = "First time";
			pchar.questTemp.Mtraxx = "wait_month";
			AddQuestRecord("Roger_8", "22");
			SetFunctionTimerCondition("Mtraxx_CartahenaTavernPrepare", 0, 0, 1, false); // belamour legendary edition увеличим таймер 
			SetFunctionTimerCondition("Mtraxx_CartahenaPrepare", 0, 0, 1, false);
			//SetFunctionTimerCondition("Mtraxx_CartahenaLate", 0, 0, 92, false);
			if (CheckCharacterItem(pchar, "Dove")) RemoveItems(pchar, "Dove", 1);
		break;
		
		case "mtraxx_board":
            dialog.text = "Ho-ho, olha só quem apareceu, garoto! Não esperava me ver aqui, né? Ha-ha-ha! No fim das contas, achamos a caravana espanhola...";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Gold")) // был абордаж
			{
				link.l1 = "Sim, chefe, conseguimos, embora não tenha sido fácil.";
				link.l1.go = "mtraxx_board_1";
			}
			else
			{
				link.l1 = "É, mas o Galeão Dourado afundou com todo o ouro dela.";
				link.l1.go = "mtraxx_board_7";
			}
		break;
		
		case "mtraxx_board_1":
			iTotalTemp = GetSquadronGoods(pchar, GOOD_GOLD);
            dialog.text = "Quanto ouro conseguimos, Príncipe?";
			if (iTotalTemp < 1) link.l1 = "Ah... Nada.";
			else link.l1 = "Heh... "+iTotalTemp+" no total!";
			link.l1.go = "mtraxx_board_2";
		break;
		
		case "mtraxx_board_2":
			if (iTotalTemp < 20)
			{
				dialog.text = "Droga! Os espanhóis devem ter jogado isso no mar pra gente não pegar. Pelo menos pagaram por isso. Assim como os homens do Barbazon, o que também é uma vitória...";
				link.l1 = "Desculpe pelo ouro... E agora, Marcus? Vamos para La Vega?";
				link.l1.go = "mtraxx_board_4";
				AddQuestRecord("Roger_8", "18");
				break;
			}
			if (iTotalTemp >= 20 && iTotalTemp < 300)
			{
				dialog.text = "Patético. Isso não cobre nem o custo da minha viagem até aqui. Os espanhóis devem ter jogado isso no mar só pra não cair nas nossas mãos. Pelo menos eles pagaram por isso. Assim como os homens do Barbazon, o que também é uma vitória...";
				link.l1 = "Desculpa pelo ouro... Vamos dividir mesmo assim.";
				link.l1.go = "mtraxx_board_3";
				AddQuestRecord("Roger_8", "19");
				break;
			}
			if (iTotalTemp >= 300 && iTotalTemp < 700)
			{
				dialog.text = "Esse prêmio é uma porcaria. Mal dá pra cobrir os gastos. Os espanhóis devem ter jogado parte no mar só pra não cair nas nossas mãos. Pelo menos pagaram caro por isso. Assim como os homens do Barbazon, o que também é uma vitória...";
				link.l1 = "Desculpa pelo ouro... Vamos dividir mesmo assim.";
				link.l1.go = "mtraxx_board_3";
				AddQuestRecord("Roger_8", "19");
				AddCharacterExpToSkill(pchar, "Fortune", 100);
				break;
			}
			if (iTotalTemp >= 700 && iTotalTemp < 1000)
			{
				dialog.text = "Nada mal, embora eu esperasse mais. Os espanhóis devem ter jogado parte disso no mar pra gente não pegar. Pelo menos pagaram por isso. Assim como os homens do Barbazon, o que também é uma vitória...";
				link.l1 = "Vamos dividir o prêmio!";
				link.l1.go = "mtraxx_board_3";
				AddQuestRecord("Roger_8", "20");
				AddCharacterExpToSkill(pchar, "Fortune", 200);
				break;
			}
			dialog.text = "Excelente! Pegamos um belo prêmio, meu amigo! E os homens do Barbazon tiveram o que mereciam, ha-ha!";
			link.l1 = "Heh, isso é ouro pra caramba! Vamos dividir!";
			link.l1.go = "mtraxx_board_3";
			AddQuestRecord("Roger_8", "21");
			AddCharacterExpToSkill(pchar, "Fortune", 300);
		break;
		
		case "mtraxx_board_3":
			RemoveCharacterGoods(pchar, GOOD_GOLD, makeint(iTotalTemp/2));
			WaitDate("", 0, 0, 0, 3, 10);
			LAi_Fade("", "");
            dialog.text = "... como sempre fazemos na Irmandade – uma parte justa para cada um. Pode ficar com o 'Torero', ela é seu prêmio.";
			link.l1 = "O que vem agora, Marcus? Vamos para La Vega?";
			link.l1.go = "mtraxx_board_4";
		break;
		
		case "mtraxx_board_4": // belamour legendary edition увеличиваем срок до 3х месяцев
            dialog.text = "Com certeza estarei em La Vega, vou te esperar lá por três semanas. Venha quando estiver pronto. De preferência em um navio mais forte, mas só um — seremos um esquadrão inteiro. Estou reunindo toda a minha gente para a jornada. Você vai sob meu comando, junto com Jean Bonito, Geoffrey Careca, Pelly Cutelo e Luke Duende também. Prepare-se. Estamos esperando uma expedição séria e um saque bem grande. Você saberá todos os detalhes depois.";
			link.l1 = "Beleza, chefe! Te vejo em La Vega em três semanas.";
			link.l1.go = "mtraxx_board_5";
		break;
		
		case "mtraxx_board_5":
            dialog.text = "Até logo, assassino! Ha-ha!";
			link.l1 = "...";
			link.l1.go = "mtraxx_board_6";
		break;
		
		case "mtraxx_board_6":
            DialogExit();
            npchar.dialog.currentnode = "mtraxx_board_6x";
			npchar.DeckDialogNode = "mtraxx_board_6x";
			npchar.DontDeskTalk = true;
			Ship_SetTaskRunAway(SECONDARY_TASK, sti(npchar.index), sti(pchar.index));
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.quest.mtraxx_corrida_complete.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_corrida_complete.function = "Mtraxx_CorridaComplete";
			RemoveItems(pchar, "wolfreeks_book", 1);
			// belamour legendary edition забрать флаг обратно
			if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
			{
				DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
				STH_SetJokerFlag(SPAIN, false); 
				log_info("You have given spanish flag");
			}
		break;
		
		case "mtraxx_board_6x":
            dialog.text = "Mais alguma coisa?";
			link.l1 = "Não, acho que não. Já estou indo para o meu navio.";
			link.l1.go = "mtraxx_board_6y";
		break;
		
		case "mtraxx_board_6y":
            DialogExit();
			npchar.DeckDialogNode = "mtraxx_board_6x";
		break;
		
		case "mtraxx_board_7":
            dialog.text = "Heh! E de quem é a culpa, Príncipe? Foi sua?";
			link.l1 = "Me desculpe, chefe, mas nós dois fomos bons o bastante... Você também mandou muito bem nos tiros. Ótima mira, aliás...";
			link.l1.go = "mtraxx_board_8";
		break;
		
		case "mtraxx_board_8":
            dialog.text = "Tanto faz. A culpa é dos dois. Mas não estamos de mãos vazias – os homens do Barbazon receberam o que tínhamos para eles, isso já é uma vitória...";
			link.l1 = "Desculpe pelo ouro... E agora, Marcus? Vamos para La Vega?";
			link.l1.go = "mtraxx_board_4";
		break;
		
		case "mtraxx_90x":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_90";
		break;
		
		case "mtraxx_90":
			pchar.quest.Mtraxx_CartahenaLate.over = "yes";
			if (GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "Príncipe, você perdeu o juízo? Eu disse pra trazer só um navio! Vai se livrar do outro e volta o mais rápido possível! Agora!";
				link.l1 = "Tá bom, tá bom!";
				link.l1.go = "mtraxx_90x";
				break;
			}
			if (RealShips[sti(pchar.Ship.Type)].Type.Merchant) // торговые
			{
				dialog.text = "Príncipe, decidiu ser meu segundo Cutlass? Por que trouxe um navio mercante pra mim? Eu estava contando com você! Vá e me traga um navio de guerra de verdade! Agora!";
				link.l1 = "Tá bom, tá bom!";
				link.l1.go = "mtraxx_90x";
				break;
			}
			if (sti(RealShips[sti(pchar.ship.type)].Class) > 3)
			{
				dialog.text = "Príncipe, você me surpreendeu. Eu disse pra você trazer um navio de guerra! Como pretende me ajudar nesse barco velho? Volte aqui com um navio de segunda ou terceira classe, nem mais nem menos! Agora! Não vou esperar por ninguém.";
				link.l1 = "Tá bom, tá bom!";
				link.l1.go = "mtraxx_90x";
				break;
			}
			if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
			{
				dialog.text = "Príncipe, por que você não traz logo o Sovereign of the Seas pra cá? Quando eu disse pra trazer um navio de guerra, não quis dizer uma maldita nau de linha! Volte aqui com uma fragata ou um navio de segunda classe! Agora! Não vou ficar esperando ninguém.";
				link.l1 = "Tá bom, tá bom!";
				link.l1.go = "mtraxx_90x";
				break;
			}
            dialog.text = "Chegou na hora certa, corsário! Bom te ver inteiro! Pronto pra zarpar?";
			link.l1 = "Pode deixar, chefe. Sempre pronto.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Barbazon")) link.l1.go = "mtraxx_91";
			else link.l1.go = "mtraxx_94";
		break;
		
		case "mtraxx_91":
            dialog.text = "Aliás, quer saber sobre o esquadrão do Barbazon que você mandou para Porto Rico?";
			link.l1 = "Isso me escapou completamente da cabeça. Claro que quero saber. Eles tiveram um fim trágico?";
			link.l1.go = "mtraxx_92";
		break;
		
		case "mtraxx_92":
            dialog.text = "Com certeza, fizeram sim! O navio-chefe – a fragata 'Coruja' do Joker Jim – queimou até a linha d'água. O próprio Joker Jim sumiu sem deixar rastro. O Tramp e o Ghoul apanharam feio, mas conseguiram escapar: o Tramp foi pra Tortuga, sob a proteção dos canhões do La Rocha, e o Ghoul pra Isla Tesoro. O Pasquale me contou que o Ghoul também encalhou o navio nos recifes perto de Sharptown e quase não conseguiu tirar de lá. O mestre Alexus vai ter trabalho agora, hehe. No fim das contas, os espanhóis me decepcionaram um pouco. Achei que iam matar todo mundo.";
			link.l1 = "Heh. Tanto faz, ainda mijamos nas botas do Barbazon. Mandamos o recado pra ele.";
			link.l1.go = "mtraxx_93";
		break;
		
		case "mtraxx_93":
            dialog.text = "Verdade. Vamos falar de negócios.";
			link.l1 = "Estou ouvindo.";
			link.l1.go = "mtraxx_94";
		break;
		
		case "mtraxx_94":
            dialog.text = "Meu serviço de inteligência, na pessoa do meu bom amigo Bernard Vensan, informou sobre uma enorme pilha de lingotes de ouro guardada pelos espanhóis em Cartagena. Mais precisamente, sob o forte da cidade. Normalmente, isso seria atribuído à Frota de Ouro da Espanha, mas desta vez é nossa chance de pegar tudo. Estamos indo para o continente espanhol atacar Cartagena.";
			link.l1 = "Argh! Eu ouvi direito? Vamos saquear uma colônia inteira, com um forte maldito?";
			link.l1.go = "mtraxx_95";
			// belamour legendary edition отказ от великого похода
			link.l2 = "Eu não vou para Cartagena com você, Marcus. Queimar uma cidade inteira não faz parte da minha história.";
			link.l2.go = "mtraxx_94a";
		break;
		
		case "mtraxx_95":
            dialog.text = "You heard right. That's exactly what we're going to do. My warship will deal with the fort, with your help of course. Bold Jeffrey will be carrying ground troops on his new East Indiaman, stolen from the Dutch. Pelly has finally got rid of his battered brigantine and acquired a decent corvette, not without my financial aid, of course. Paul Chant and you are responsible for taking out the patrol fleet; your crews will also take part in the assault, and you, Charles, such a fine fighter and captain, will help me destroy the fort. Jean Picard didn't show up, which is strange since his corvette has been seen in Port Royal. Well, if he isn't interested in Spanish gold, that's his problem, so to hell with him. Instead of him, my friend Bernard Vensan will join the raid. Plus, Leprechaun and his buccaneers will assist our troops. We will take the gold from the fort and ransom from the city. They won't forget it, ha-ha!  Now, go rest. And come join me and the other captains in the tavern this evening! We should drink to our cause! I'll order the bartender to drive out all the local drunks, so only the six of us and some charming girls will be in the tavern. You're drinking with your comrades tonight, and tomorrow morning you'll lead the squadron, you'll set the course. And try to bring us to Cartagena as soon as possible. All clear?";
			link.l1 = "Sim, sim, chefe!";
			link.l1.go = "mtraxx_96";
		break;
		
		case "mtraxx_96":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			chrDisableReloadToLocation = true;
			CloseQuestHeader("Roger_8");
			pchar.questTemp.Mtraxx = "cartahena";
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "LaVega_townhall", "goto", "goto3");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Mtraxx_CartahenaReloadInTavern", 10.0);
			pchar.worldmapencountersoff = "1"; // уберем враждебные энкаунтеры
		break;
		// belamour legendary edition -->
		case "mtraxx_94a":
            dialog.text = "Você... você... Príncipe Louco! Está tentando me passar a perna?! Sabe de uma coisa, vá pro inferno! Você teve a chance de entrar para a Irmandade, teve a chance de sair do meio dessa gentalha inútil. E você simplesmente desperdiçou sua chance como um covarde. Cai fora com esse chororô! Fracote! Se eu te vir de novo – jogo os cães em cima de você!";
			link.l1 = "...";
			link.l1.go = "mtraxx_95a";
		break;
		
		case "mtraxx_95a":
            DialogExit();
			QuestSetCurrentNode("Terrax", "First time");
			CloseQuestHeader("Roger_8");
			DeleteAttribute(pchar, "questTemp.Mtraxx.Corrida");
			DeleteAttribute(pchar, "questTemp.Mtraxx.InTavern");
			LocatorReloadEnterDisable("LaVega_town", "reload6", true); // закрыть на месяц
			SetFunctionTimerCondition("Mtraxx_CartahenaLateOpen", 0, 0, 30, false);
			Mtraxx_TerraxReset(8);
			DoQuestReloadToLocation("LaVega_town", "reload", "reload6", ""); // выставим за дверь
		break;
		// <-- legendary edition
		case "mtraxx_97":
            dialog.text = "Príncipe, finalmente! Olhem, rapazes – preparamos um presente pra ele, e o sujeito some por aí, vai saber onde! Senta aí, vamos começar!\nEntão, corsários valentes! O ouro de Cartagena nos espera, ha-ha! E nós vamos pegar, juro pelo trovão! Mas quem trabalha duro também tem que descansar direito! Por isso, hoje à noite vamos aproveitar esse belo lugar. Sirvam-se de rum, quanto mais melhor! Encham as canecas até a borda! Aos ventos do tesouro, aos ventos da sorte! Vamos beber até a última gota!\nPra você, a melhor bebida das adegas da nossa taverna, e as mulheres mais lindas da ilha, ha-ha-ha!\nE pra você, Charles, da nossa parte — um chapéu magnífico. Experimente, e nem discuta!\nCorsários, cantem nossa música! Aquela preferida!..";
			link.l1 = "";
			link.l1.go = "mtraxx_98";
		break;
		
		case "mtraxx_98":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			LAi_SetSitType(npchar);
			GiveItem2Character(PChar, "hat8");
			EquipCharacterByItem(PChar, "hat8");
			DoQuestCheckDelay("Mtraxx_CartahenaTavernSong", 1.0);
		break;
		
		case "mtraxx_99":
            dialog.text = "Hora de mostrar quem somos, corsários. Leprechaun! Leve seus homens e tome o controle dos portões da cidade. Não queremos que eles mandem reforços para o forte! Ataque forte por trás quando avançarmos pelos soldados do forte!";
			link.l1 = "";
			link.l1.go = "mtraxx_100";
		break;
		
		case "mtraxx_100":
            dialog.text = "Príncipe e Paul! Vocês viram o esquadrão militar com três navios, se livrem deles. Fiquem longe do forte e não embarquem nos navios deles. Não temos tempo nem estamos na posição de lidar com prêmios agora. Está tudo claro?! Príncipe, estou falando especialmente com você, sei do seu vício em heroísmos, vai ter chance pra isso depois!\nNão cheguem muito perto do forte, acabem com esses navios e voltem! Vamos esperar vocês aqui. Está tudo claro? Ótimo, ha-ha-ha-ha! Avante!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CartahenaSquadronAttack");
		break;
		
		case "mtraxx_101":
            dialog.text = "Então, o esquadrão espanhol se foi de vez. Agora é a hora do 'Dragão Vermelho' entrar em ação. Vamos transformar o forte de Cartagena em um monte de escombros. Está comigo?";
			link.l1 = "Claro!";
			link.l1.go = "mtraxx_102";
		break;
		
		case "mtraxx_102":
            dialog.text = "O 'Dragão Vermelho' é um navio muito resistente, com artilharia pesada, o seu não chega nem perto. Então tome cuidado, não banque o herói e fique longe dos meus canhões!";
			link.l1 = "...";
			link.l1.go = "mtraxx_103";
		break;
		
		case "mtraxx_103":
            DialogExit();
			
			Weather.Wind.Speed = 16.0;
			pchar.wind.speed = Weather.Wind.Speed;
			fWeatherSpeed = stf(Weather.Wind.Speed);//халява первого выхода
	
			Weather.Wind.Angle = 0.0;
			pchar.wind.angle = Weather.Wind.Angle;
			fWeatherAngle = stf(Weather.Wind.Angle);//халява первого выхода
			
            npchar.dialog.currentnode = "mtraxx_board_6x";
			npchar.DeckDialogNode = "mtraxx_board_6x";
			npchar.DontDeskTalk = true;
			Group_FindOrCreateGroup("Terrax_SeaGroup2");
			Group_DelCharacter("Terrax_SeaGroup", "Jeffry");
			Group_DelCharacter("Terrax_SeaGroup", "Mtr_Vensan");
			Group_AddCharacter("Terrax_SeaGroup2", "Jeffry");
			Group_AddCharacter("Terrax_SeaGroup2", "Mtr_Vensan");
			Group_AddCharacter("Terrax_SeaGroup2", "Pelly");
			Group_SetGroupCommander("Terrax_SeaGroup2", "Jeffry");
			Group_SetTaskNone("Terrax_SeaGroup2");
			Group_LockTask("Terrax_SeaGroup2");
			sld = CharacterFromID("Cartahena Fort Commander");
			LAi_SetImmortal(sld, false);
			Ship_SetTaskAttack(SECONDARY_TASK, sti(npchar.index), sti(sld.index));
			AddQuestRecord("Roger_9", "5");
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.questTemp.Mtraxx.Cartahena.Fort = "true";
			SetFunctionExitFromLocationCondition("Mtrxtofort", pchar.location, false);
		break;
		
		case "mtraxx_104":
            dialog.text = RandSwear()+"Que luta infernal! É isso aí, meus corsários valentes! Cartagena é nossa! A resistência caiu! Corajoso, Leprechaun! Venha comigo até o forte – Bernie já deve ter achado o ouro. Príncipe, leve o Cutlass e negocie com o governador para nos pagar um resgate de 250.000 pesos! Eles têm o dinheiro, então insista. Eu sei que você consegue.";
			link.l1 = "Heh! Com prazer, chefe!";
			link.l1.go = "mtraxx_105";
		break;
		
		case "mtraxx_105":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "Cartahena_fort", "goto", "goto10", "", 5.0);
			sld = CharacterFromID("Jeffry");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "gate_back", "Cartahena_fort", "goto", "goto11", "", 5.0);
			sld = CharacterFromID("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "gate_back", "Cartahena_fort", "goto", "goto12", "", 5.0);
			sld = CharacterFromID("Pelly");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			AddQuestRecord("Roger_9", "6");
			// запрещаем драки в городе, резиденции, форте
			LAi_LocationFightDisable(&Locations[FindLocation("Cartahena_fort")], true);
			LAi_LocationFightDisable(&Locations[FindLocation("Cartahena_town")], true);
			LAi_LocationFightDisable(&Locations[FindLocation("Cartahena_townhall")], true);
			LAi_LocationDisableOfficersGen("Cartahena_townhall", true);
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1 = "locator";
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1.location = "Cartahena_town";
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1.locator_group = "reload";
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1.locator = "reload3_back";
			pchar.quest.mtraxx_cartahena_townhall.function = "Mtraxx_CartahenaToResidence";
		break;
		
		case "mtraxx_106":
            dialog.text = "Como vai, Príncipe?";
			link.l1 = "Está tudo esplêndido. Eu obriguei os mais ricos de Cartagena a pagar 350.000 pesos.";
			link.l1.go = "mtraxx_107";
		break;
		
		case "mtraxx_107":
            if (sti(Pchar.money) < 350000)
			{
				dialog.text = "Ho-ho, esse é o meu garoto! Mas onde está o dinheiro?";
				link.l1 = RandSwear()+"Eu vou trazer em um instante!";
				link.l1.go = "mtraxx_107x";
			}
			else
			{
				dialog.text = "Ho-ho, esse é meu garoto! Você e o Cutlass podem ficar com 50.000 cada um como bônus pela rapidez e esperteza. O resto será dividido entre todos nós depois.";
				link.l1 = "Aqui está!";
				link.l1.go = "mtraxx_109";
			}
		break;
		
		case "mtraxx_107x":
           DialogExit();
		   npchar.dialog.currentnode = "mtraxx_108";
		break;
		
		case "mtraxx_108":
            if (sti(Pchar.money) < 350000)
			{
				dialog.text = "E aí? Pare de enrolar e traga as moedas aqui!";
				link.l1 = "Já estou indo!";
				link.l1.go = "mtraxx_107x";
			}
			else
			{
				dialog.text = "Ótimo! Você e o Cutlass podem ficar com 50.000 cada um como bônus pela rapidez e esperteza. O resto será dividido entre todos nós depois.";
				link.l1 = "Aqui está!";
				link.l1.go = "mtraxx_109";
			}
		break;
		
		case "mtraxx_109":
			AddMoneyToCharacter(pchar, -300000);
            dialog.text = "Está preocupado com o nosso ouro? Já foi encontrado – 5.000 unidades, e já está sendo transportado para nossos navios. A divisão já foi feita, os homens concordaram, e esperamos que Cutlass e você também não tenham objeções.";
			link.l1 = "Qual é a minha parte?";
			link.l1.go = "mtraxx_110";
		break;
		
		case "mtraxx_110":
            dialog.text = "Já que toda a operação foi planejada por mim, e o 'Dragão Vermelho' ficou com a tarefa mais difícil de enfrentar o forte, meus homens e eu vamos ficar com metade do saque. A outra metade será dividida entre os capitães dos outros quatro navios, de acordo com o tamanho de suas tripulações. Você tem "+GetCrewQuantity(pchar)+" homens à sua disposição, sua parte é "+sti(pchar.questTemp.Mtraxx.Cartahena.Gold)+" unidades de ouro e "+sti(pchar.questTemp.Mtraxx.Cartahena.Money)+" pesos.";
			link.l1 = "Bom, já que todo mundo concorda com isso, então eu também!";
			link.l1.go = "mtraxx_111";
		break;
		
		case "mtraxx_111":
            dialog.text = "Splendid. Congratulations on this successful voyage, corsairs! Nothing left for us here, time to go home. All of us, myself included, receive a month's vacation. Not you, Prince, though; I have another task for you. You see, Janette, the Madame of Tortuga's brothel, had a complaint about you: she said that Charlie Prince doesn't give much attention or affection to her establishment. Therefore, I command you to sail to Tortuga, go to Janette's, and spend your bonuses there. You've earned it. Make the Madame and her girls happy. I don't want to see you before you've had your rest in Tortuga, ha-ha-ha!";
			link.l1 = "Entendido, chefe. Essa é a tarefa mais agradável que já recebi. Vai ser feita!";
			link.l1.go = "mtraxx_112";
		break;
		
		case "mtraxx_112":
            dialog.text = "Até logo, senhores! Voltem para seus navios e zarpem! Vejo todos vocês em La Vega!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CartahenaFinal");
		break;
		
		// Addon 2016-1 Jason пиратская линейка патч 17/1
		case "mtraxx_113":
            dialog.text = "O quê?! Jean agora é um capacho dos ingleses, Bold e Cutlass sumiram, Leprechaun e os homens dele desapareceram! E agora você?!";
			link.l1 = "Marcus, tomei minha decisão. Ganhei um bom dinheiro, você também lucrou bastante comigo. Mas acabou. Estou indo embora.";
			link.l1.go = "mtraxx_114";
		break;
		
		case "mtraxx_114":
            dialog.text = "Você, assim como o Picard, acha que pode ganhar mais sozinho? É? Acha que consegue se virar sem mim? Ha-ha-ha! Cai fora daqui, Príncipe, não vou te segurar. Logo, muito em breve, você vai ver o quanto estava enganado, e aí vai voltar rastejando pra eu aceitar sua bunda de volta. E sabe de uma coisa? Não vou! Ha-ha! Some da minha frente!";
			link.l1 = "...";
			link.l1.go = "mtraxx_115";
		break;
		
		case "mtraxx_115":
            DialogExit();
		    npchar.quest.mtraxx_complete = "true";
		break;
		
		// Jason НСО
		case "patria":
			dialog.text = "Ho-ho! Veio ao lugar certo! Fala logo!";
			link.l1 = "Tem um sujeito que não tem medo de piratas. Ele não nos leva a sério. Precisa aprender a ter respeito. Lembre-se, não o mate.";
			link.l1.go = "patria_1";
		break;
		
		case "patria_1":
			dialog.text = "Olha só! Se não é o velho Charles! Aposto que você já se meteu em outra encrenca! Vamos ao que interessa, quem é o alvo dessa vez e o que quer que a gente faça com ele?";
			link.l1 = "Um convidado da Europa, um inspetor do Ministério das Finanças da França – Barão Noel Forget. Ele quer fundar uma Companhia de Comércio Francesa aqui, mas eu e um grande amigo somos contra. Tentamos convencer o Barão de que negociar por aqui seria muito arriscado por causa dos holandeses, dos ingleses e, principalmente, dos piratas depois que Levasseur foi derrotado, mas ele não quis ouvir. Precisamos fazer ele sentir medo, fazê-lo experimentar isso na pele.";
			link.l1.go = "patria_2";
		break;
		
		case "patria_x":
			dialog.text = "Ho-ho! Veio ao lugar certo! Fala logo!";
			link.l1 = "Tem um sujeito que não tem medo de piratas. Ele não nos leva a sério. Precisa aprender a nos respeitar. Lembre-se, não mate ele.";
			link.l1.go = "patria_x1";
		break;
		
		case "patria_x1":
			dialog.text = "Hã! Por que você resolveu contratar piratas do nada? Tanto faz, desde que me pague. Vamos ao que interessa, quem é o alvo dessa vez e o que quer que a gente ensine pra ele";
			link.l1 = "Um convidado da Europa, um inspetor do Ministério das Finanças da França – Barão Noel Forget. Ele quer fundar uma Companhia Comercial Francesa aqui, mas eu e um amigo próximo somos contra. Tentamos convencer o Barão de que negociar aqui seria muito arriscado por causa dos holandeses, dos ingleses e, principalmente, dos piratas depois que Levasseur foi derrotado, mas ele não quis ouvir. Precisamos assustá-lo, fazer com que ele sinta isso na própria pele.";
			link.l1.go = "patria_2";
		break;
		
		case "patria_2":
			dialog.text = "Sim, sim... Um barão de verdade! Vamos atacar o navio dele?";
			link.l1 = "Aqui está o plano: o navio dele vai partir de Port-au-Prince para Capsterville em breve. Você deve interceptar o Barão perto de Saint Kitts e fazê-lo de refém. Seria melhor se você não afundasse o navio nem matasse ninguém. Os franceses são nossos aliados, afinal de contas. Vai conseguir dar conta disso?";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			dialog.text = "Bem, não posso prometer nada. Mas vou tentar. Que navio é esse?";
			link.l1 = "Uma brigue chamada 'Favory'.";
			link.l1.go = "patria_4";
		break;
		
		case "patria_4":
			dialog.text = "Uma brigue não é páreo para o meu 'Dragão Vermelho'. Vamos acabar com eles facilmente. Se se renderem, deixo todo mundo vivo.";
			link.l1 = "Perfeito. Espalhe o medo e ofereça a eles uma chance de se render. Depois, mande o Barão para o porão infestado de ratos. Procure o lugar mais imundo que conseguir, mas não o deixe lá por mais de um dia, senão ele pode adoecer e morrer. Depois, acomode-o na cabine, encontre algum canto isolado e tranque-o lá. Vista alguns dos seus homens como mercadores franceses capturados e faça-os interpretar o papel. Durante três dias seguidos, eles devem contar a ele tudo sobre como piratas cruéis os perseguem, roubam, exigem resgates, torturam... com todos os detalhes necessários.";
			link.l1.go = "patria_5";
		break;
		
		case "patria_5":
			dialog.text = "Ha-ha-ha! Esse deve ser o trabalho mais engraçado que peguei em muito tempo! Muito bem, vou encontrar esses atores, garoto. Pode apostar, depois das histórias deles, seu Barão vai se borrar de medo! Eles vão mostrar cicatrizes de sabres e de ferros em brasa...";
			link.l1 = "Perfeito! Então você vai obrigá-lo a escrever uma carta para de Poincy, pedindo resgate. Três milhões e quinhentos mil por um figurão desses nem é tanto assim.";
			link.l1.go = "patria_6";
		break;
		
		case "patria_6":
			dialog.text = "Ótimo. O que fazemos agora?";
			link.l1 = "E então você vai levar o Barão para Turks. Lá, você recebe o resgate e me entrega o Barão. Além disso, diga a ele que todos os franceses vão pagar por Tortuga e Levasseur, e não será só uma vez.";
			if (CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax")) link.l1.go = "patria_x7";
			else link.l1.go = "patria_7";
		break;
		
		case "patria_7":
			dialog.text = "Ha-ha-ha! Isso sim é um truque e tanto! Nós, pessoalmente, bem, você sabe o que fizemos com o Levasseur, e agora... ha-ha-ha!.. Muito bem, rapaz. Vai ser feito! Então você diz que o navio vai chegar logo?";
			link.l1 = "Em breve. Temos que ficar atentos.";
			link.l1.go = "patria_8";
		break;
		
		case "patria_x7":
			dialog.text = "Ha-ha-ha! Essa foi uma bela jogada! Quanto será que devo cobrar por esse teatro? Tá bom, cem mil e fechamos o negócio. Me passa o dinheiro.";
			if (sti(pchar.money) >= 100000) 
			{
				link.l1 = "Pegue.";
				link.l1.go = "patria_x8";
			}
			else
			{
				link.l1 = "Certo, eu vou trazer.";
				link.l1.go = "patria_xwait";
			}
		break;
		
		case "patria_xwait":
			DialogExit();
			pchar.questTemp.Patria.Condotier.NeedMoney = "true";
		break;
		
		case "patria_x8":
			AddMoneyToCharacter(pchar, -100000);
			dialog.text = "Perfeito! Você disse que o navio vai chegar em breve?";
			link.l1 = "Em breve. Temos que ficar atentos.";
			link.l1.go = "patria_8";
		break;
		
		case "patria_8":
			dialog.text = "Não se preocupe com isso, não vou te decepcionar. Vou cuidar disso pessoalmente. Quando ouvir um boato de que o Barão foi capturado, venha falar comigo.";
			link.l1 = "Ótimo. Meu agradecimento, Marcus.";
			link.l1.go = "patria_9";
		break;
		
		case "patria_9":
			DialogExit();
			AddQuestRecord("Patria", "71");
			pchar.questTemp.Patria = "epizode_12_wait";
			pchar.questTemp.Patria.Condotier.Success = "true";
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax")) LocatorReloadEnterDisable("Pirates_town", "reload3_back", true);
			else LocatorReloadEnterDisable("Lavega_town", "reload6", true);
		break;
		
		case "patria_10":
			dialog.text = "Claro, garoto. Como combinado. Histórias assustadoras de piratas impiedosos, massacrando mercadores franceses inocentes, o som do chicote, gemidos e gritos. Um braseiro com carvões e algemas queimadas. Do jeito que tem que ser.";
			link.l1 = "Epa, epa! Calma aí! Eu preciso dele vivo";
			link.l1.go = "patria_11";
		break;
		
		case "patria_11":
			dialog.text = "Não se preocupe, ele vai sobreviver. Ele escreveu esta carta com a mão trêmula. Aqui está.";
			link.l1 = "O que está escrito aí? Ele está implorando pro Poincy tirar ele dessa?";
			link.l1.go = "patria_12";
		break;
		
		case "patria_12":
			dialog.text = "Isso mesmo, garoto! Ele tá implorando, ha!";
			link.l1 = "Jogue esta carta fora, ou melhor ainda – queime-a. Vamos nos encontrar em Turks em uma semana. Tem que parecer que precisamos de tempo para juntar o resgate.";
			link.l1.go = "patria_13";
		break;
		
		case "patria_13":
			dialog.text = "Entendido. Daqui a uma semana, no golfo norte, em Turks. Não esqueça de levar o dinheiro: isso precisa parecer legítimo. Depois de tudo isso, venha falar comigo, vamos conversar.";
			link.l1 = "Claro, até mais, Marcus!";
			link.l1.go = "patria_14";
		break;
		
		case "patria_14":
			DialogExit();
			AddQuestRecord("Patria", "73");
			pchar.questTemp.Patria = "epizode_12_terks";
			SetFunctionTimerCondition("Patria_CondotierTerks", 0, 0, 7, false);
			SetFunctionTimerCondition("Patria_CondotierTerksOver", 0, 0, 14, false);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
		break;
		
		case "patria_15":
			pchar.quest.Patria_CondotierTerksOver.over = "yes"; //снять таймер
			dialog.text = "Ei, comedor de rãs! Pare!";
			link.l1 = "Eu não vou sair do lugar.";
			link.l1.go = "patria_16";
		break;
		
		case "patria_16":
			dialog.text = "Aqui está o seu Barão. Um pouco acabado, heh, mas inteiro. Ainda dá pra reconhecer? Ha-ha-ha!";
			link.l1 = "Sim... de certo modo.";
			link.l1.go = "patria_17";
		break;
		
		case "patria_17":
			dialog.text = "Perfeito. Agora passa o dinheiro ou ele tá ferrado! E nem pense em tentar nos enganar, estamos de olho em você!";
			if (sti(pchar.money) >= 350000)
			{
				link.l1 = "Aqui, pega.";
				link.l1.go = "patria_18";
			}
			else
			{
				link.l1 = "Droga! Esqueci no navio...";
				link.l1.go = "patria_22";
			}
		break;
		
		case "patria_18":
			AddMoneyToCharacter(pchar, -350000);
			dialog.text = "Ha-ha-ha! Você é esperto, francês. Pegue sua 'eminência'. E diga ao Poincy que prepare o dinheiro: vocês vão ter que pagar pelo que fizeram com o Levasseur e Tortuga. E seus mercadores vão pagar pra gente com suas mercadorias e navios. Ha-ha-ha! Não esqueça de trazer mais barões pro arquipélago, eles nos dão muito lucro! Ha-ha-ha!";
			link.l1 = "Por favor, vá para o meu barco, Barão.";
			link.l1.go = "patria_19";
		break;
		
		case "patria_19":
			sld = CharacterFromID("Noel");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
			dialog.text = "E nem pense em vir atrás da gente, capitão. Você sabe quem eu sou. Tenho mais franceses presos, e se eu não voltar pra casa na hora certa, todos eles vão ser executados. Entendeu?";
			link.l1 = "Chegará a hora, e vamos acertar as contas com vocês, malditos blasfemos!";
			link.l1.go = "patria_20";
		break;
		
		case "patria_20":
			dialog.text = "Ha-ha-ha-ha! Claro que vai!";
			link.l1 = "...";
			link.l1.go = "patria_21";
		break;
		
		case "patria_21":
			DialogExit();
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Patria", "74");
			LAi_SetActorType(npchar);
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax"))
			{
				LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
				Island_SetReloadEnableGlobal("Bermudes", false); // закрыть остров до отвоза барона
			}
			else LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierTerraxNorm", 10.0);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
			pchar.questTemp.Patria = "epizode_12_baronalive";
			pchar.questTemp.Patria.DodsonAgain = "true";
			sld = CharacterFromID("Noel");
			AddPassenger(pchar, sld, false);//добавить пассажира
			SetCharacterRemovable(sld, false);
			pchar.quest.Patria_Condotier_toPuancie.win_condition.l1 = "location";
			pchar.quest.Patria_Condotier_toPuancie.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_Condotier_toPuancie.function = "Patria_CondotierEnCapstervil";
			// Теркс в норму
			LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
			LAi_LocationDisableOfficersGen("Shore56", false);
		break;
		
		case "patria_22":
			dialog.text = "Você está brincando comigo?! Isso é algum tipo de truque?!";
			link.l1 = "Um momento, vou trazer...";
			link.l1.go = "patria_23";
		break;
		
		case "patria_23":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Shot", "Patria_CondotierBaronDie", 1.0);
		break;
		
		case "patria_24":
			dialog.text = "";
			link.l1 = "Porra, Marcus, o que esse imbecil fez agora!";
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax")) link.l1.go = "patria_25";
			else link.l1.go = "patria_x25";
		break;
		
		case "patria_25":
			dialog.text = "Charles, o que você estava fazendo? Cadê o dinheiro? Eu não contei pros meus rapazes que isso não era de verdade... e aí esse idiota achou que você queria passar a perna na gente...";
			link.l1 = "É um desastre! O Barão está morto... O que de Poincy vai fazer agora?";
			link.l1.go = "patria_26";
		break;
		
		case "patria_x25":
			dialog.text = "Charles, o que você estava fazendo? Cadê o dinheiro? Eu não contei pros meus rapazes que isso não era de verdade... aí esse idiota achou que você tava tentando enganar eles...";
			link.l1 = "É um desastre! O Barão está morto... O que de Poincy vai fazer agora?";
			link.l1.go = "patria_x26";
		break;
		
		case "patria_x26":
			dialog.text = "Bem, garoto, a culpa é sua, espero que entenda isso. Talvez seja até melhor assim, um homem morto não pode causar mais problemas.";
			link.l1 = "Que idiota eu sou! Estraguei tudo. Tá bom, vou pra Poincy... Me perdoa por ser tão imbecil, Marcus, até mais.";
			link.l1.go = "patria_28";
		break;
		
		case "patria_26":
			dialog.text = "Bem, garoto, a culpa é sua, espero que entenda isso. Talvez seja o melhor.";
			link.l1 = "Que idiota eu sou! Estraguei tudo. Tá bom, vou pra Poincy... Me perdoa por ser tão burro, Marcus, até mais.";
			link.l1.go = "patria_27";
		break;
		
		case "patria_27":
			dialog.text = "Você precisa descansar, está perdendo o jeito. Venha me procurar qualquer hora, eu arranjo um pouco de rum e umas moças bonitas pra você.";
			link.l1 = "Obrigado, vou te fazer uma visita quando puder.";
			link.l1.go = "patria_28";
		break;
		
		case "patria_28":
			DialogExit();
			AddQuestRecord("Patria", "75");
			LAi_SetActorType(npchar);
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax")) LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
			else LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierTerraxNorm", 10.0);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
			pchar.questTemp.Patria = "epizode_12_barondie";
			// Теркс в норму
			LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
			LAi_LocationDisableOfficersGen("Shore56", false);
		break;
		
		case "patria_29":
			dialog.text = "De nada, garoto. Pra mim, isso foi a coisa mais divertida que fiz esse ano! Rimos demais, eu e meus rapazes! Então quero te agradecer por isso. Aqui está o seu dinheiro.";
			link.l1 = "Você devia ficar com uma parte disso pelo seu trabalho.";
			link.l1.go = "patria_30";
		break;
		
		case "patria_x29":
			AddMoneyToCharacter(pchar, 350000);
			dialog.text = "Pega seu dinheiro, 'conspirador'. Ha-ha! Isso foi divertido.";
			link.l1 = "Obrigado pela sua ajuda, Marcus. Boa sorte!";
			link.l1.go = "patria_32";
		break;
		
		case "patria_30":
			AddMoneyToCharacter(pchar, 350000);
			dialog.text = "Esqueça. Fiz isso pela nossa amizade. A Irmandade da Costa te deve muito mais, e mesmo assim você não pediu nem um doblón.";
			link.l1 = "Ainda assim, aceite pelo menos cinquenta mil pelos seus serviços e como compensação. Obrigado, Marcus!";
			link.l1.go = "patria_31";
		break;
		
		case "patria_31":
			AddMoneyToCharacter(pchar, -50000);
			dialog.text = "De nada. Charles, venha me visitar quando tiver um tempo!";
			link.l1 = "Com prazer!";
			link.l1.go = "patria_32";
		break;
		
		case "patria_32":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Patria.DodsonAgain");
		break;
		
		case "patria_33":
			dialog.text = "Você está uma semana atrasado! Eu não contei pros meus rapazes que isso não era pra valer... Eles se recusaram a esperar mais e decidiram acabar com o seu Barão!";
			link.l1 = "Que idiota eu sou! Estraguei tudo! O que vou dizer para o Poincy?";
			link.l1.go = "patria_34";
		break;
		
		case "patria_x33":
			dialog.text = "Você está uma semana atrasado! Eu não contei pros meus rapazes que isso não era pra valer... Eles se recusaram a esperar mais e decidiram acabar com o seu Barão!";
			link.l1 = "Que idiota eu sou! Estraguei tudo! O que vou dizer para o Poincy?";
			link.l1.go = "patria_x34";
		break;
		
		case "patria_34":
			dialog.text = "Bem, garoto, a culpa é sua, espero que entenda isso. Talvez no fim das contas isso seja até melhor pra você.";
			link.l1 = "Tá bom, eu vou pra Poincy... Me perdoa por ser um idiota, Marcus, até mais...";
			link.l1.go = "patria_35";
		break;
		
		case "patria_x34":
			dialog.text = "Você se meteu nessa encrenca, a culpa é toda sua.";
			link.l1 = "Até mais, eu acho...";
			link.l1.go = "patria_36";
		break;
		
		case "patria_35":
			dialog.text = "Você precisa descansar, está perdendo o jeito. Venha me procurar qualquer hora, eu arranjo um pouco de rum e umas moças pra você.";
			link.l1 = "Obrigado, vou te visitar quando puder.";
			link.l1.go = "patria_36";
		break;
		
		case "patria_36":
			DialogExit();
			AddQuestRecord("Patria", "75");
			pchar.questTemp.Patria = "epizode_12_barondie";
			DeleteAttribute(pchar, "questTemp.Patria.DodsonFail");
		break;
		
		// Rebbebion, квест "Путеводная звезда"
		case "PZ_1":
			DelLandQuestMark(npchar);
			
			if (pchar.questTemp.Mtraxx == "full_complete")
			{
				dialog.text = "Faz tempo, Príncipe.";
				link.l1 = "Não tenho certeza se esse nome me trouxe outra coisa além de má sorte, Marcus.";
				link.l1.go = "PZ_Prince1";
			}
			else
			{
				dialog.text = "De Maure! O que te traz aqui?";
				link.l1 = "Ah, Marcus. Queria te perguntar uma coisa.";
				link.l1.go = "PZ_DeMaure1";
			}
		break;
		
		case "PZ_Prince1":
			dialog.text = "Vejo que é exatamente o contrário. O que te traz aqui?";
			link.l1 = "Você já ouviu falar do novo bordel em Tortuga?";
			link.l1.go = "PZ_2";
		break;
		
		case "PZ_DeMaure1":
			dialog.text = "Então, pergunte logo. Você sabe que eu não gosto de formalidades, então vá direto ao ponto.";
			link.l1 = "Você ficou sabendo do novo bordel em Tortuga?";
			link.l1.go = "PZ_2";
		break;
		
		case "PZ_2":
			dialog.text = "Você está bêbado? Que tipo de pergunta é essa? Não perca meu tempo se era só isso que queria dizer.";
			link.l1 = "Acho que você ainda não ouviu? Um novo bordel abriu lá recentemente—é caríssimo, e só trabalham as garotas mais bonitas, saudáveis e bem vestidas.";
			link.l1.go = "PZ_3";
		break;
		
		case "PZ_3":
			dialog.text = "Ah, isso! Claro que já ouvi – quem não ouviu?";
			link.l1 = "Bem, eu só fiquei sabendo disso outro dia.";
			link.l1.go = "PZ_4";
		break;
		
		case "PZ_4":
			dialog.text = "Ha-ha-ha-ha, seu canalha, não é que você me surpreendeu! Mas me diz, por que está discutindo isso comigo? Por que não tenta o Hawks primeiro? Heh heh. Ou será que... você já se divertiu por lá?";
			if (CheckAttribute(pchar, "questTemp.PZ.EliteWhoreFucked"))
			{
				link.l1 = "Já consegui. Aliás, eles só aceitam dobrões.";
				link.l1.go = "PZ_Fucked1";
			}
			else
			{
				link.l1 = "Eu estive no lugar, mas não usei os serviços. Porém...";
				link.l1.go = "PZ_NoFucked1";
			}
		break;
		
		case "PZ_Fucked1":
			dialog.text = "Então você veio se exibir! Ha, que safado.";
			link.l1 = "Na verdade, não. Eu queria mesmo era te perguntar uma coisa, Marcus.";
			link.l1.go = "PZ_5";
		break;
		
		case "PZ_NoFucked1":
			dialog.text = "Você não fez isso?! Você é um idiota, De Maure. Se eu fosse você...";
			link.l1 = "Você teria começado uma verdadeira farra, eu sei. Mas não é exatamente sobre isso que eu queria falar com você.";
			link.l1.go = "PZ_5";
		break;
		
		case "PZ_5":
			dialog.text = "O que foi? Vamos, não me deixe na expectativa.";
			link.l1 = "Estou procurando pela dona daquele lugar. Disseram que ela queria te conhecer e te oferecer uma oportunidade de investimento no comércio dela. Não tem como confundir – ela é chinesa.";
			link.l1.go = "PZ_6";
		break;
		
		case "PZ_6":
			dialog.text = "Ho ho. Não, não tive o prazer de conhecer nenhuma chinesa ultimamente. Mas eu não me importaria de conhecê-la e investir no negócio dela. Afinal, não dá pra simplesmente entrar no território do Levasseur, e como súdito do seu rei, ele seria obrigado a disparar seus navios costeiros contra meu 'Dragão' assim que o visse.";
			link.l1 = "Parece que ela está pensando primeiro em Port-au-Prince...";
			link.l1.go = "PZ_7";
		break;
		
		case "PZ_7":
			dialog.text = "Você acha? Isso é um erro. Mesmo que o de Mussac tenha mais dinheiro do que eu, o que eu duvido, ele não pode pegar dinheiro do orçamento da cidade pra investir num bordel, por mais ouro que isso traga.";
			link.l1 = "Bem pensado. Está claro que ela não pensou direito nessa ambição dela.";
			link.l1.go = "PZ_8";
		break;
		
		case "PZ_8":
			dialog.text = "Sabe, eu sempre me perguntei como outros bordéis conseguem se manter. Não é pela inteligência das mulheres, e muito menos pela capacidade de mandar - pode apostar.";
			link.l1 = "Bem, você está enganado quanto a isso. Obrigado pelo seu tempo, Marcus! Se eu encontrá-la primeiro, aviso que você ficaria feliz em vê-la.";
			link.l1.go = "Exit";
			
			AddQuestRecord("PZ", "32");
			
			pchar.quest.PZ_SetHeavyFrigate.win_condition.l1 = "location";
			pchar.quest.PZ_SetHeavyFrigate.win_condition.l1.location = "Hispaniola1";
			pchar.quest.PZ_SetHeavyFrigate.win_condition = "PZ_SetHeavyFrigate";
			DelMapQuestMarkCity("LaVega");
			AddMapQuestMarkCity("PortPax", false);
			LocatorReloadEnterDisable("LaVega_ExitTown", "reload1_back", true);
			LocatorReloadEnterDisable("PortPax_town", "gate_back", true);
		break;
	}
}