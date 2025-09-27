// Маркус Тиракс, барон Ла Веги
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
					dialog.text = "Ah Prince, tu es enfin là. Au moins un d'entre vous a daigné se montrer ! Le travail attend et vous avez tous disparu ! Où diable est tout le monde ?";
					link.l1 = "Pas la moindre idée... Marcus, j'en ai assez. Je suis à bout. Des hommes morts viennent à moi dans mes rêves et Lucifer lui-même souffle derrière mon dos. Trop de sang a été versé récemment.";
					link.l1.go = "mtraxx_113";
					break;
				}
			}
			// Jason НСО
			// если Сага завалена, то у Маркуса ноды в двух местах и оплата вперед
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "As-tu des 'affaires' pour moi ?";
				link.l1 = "Salutations, Marcus. Oui, j'ai une 'affaire'. Rentable et pratique.";
				link.l1.go = "patria_x";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Condotier.NeedMoney") && pchar.questTemp.Patria == "epizode_12_pirates" && sti(pchar.money) >= 100000)
			{
				dialog.text = "As-tu apporté l'argent ?";
				link.l1 = "Je l'ai fait.";
				link.l1.go = "patria_x8";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "C'est notre client ! Le travail est fait, ton baron est assis dans un cachot bien gardé. Peut-être que tu voudrais jeter un œil, hé-hé ?!";
				link.l1 = "Je vais avoir tout le temps pour faire ça, ha-ha. Est-il bien traité ?";
				link.l1.go = "patria_10";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "Charles, qu'est-ce que c'est que ce bordel?!";
				link.l1 = "Marcus, tout a mal tourné. Je n'ai pu ni venir ni t'informer...";
				link.l1.go = "patria_x33";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "Voici notre marionnettiste !";
				link.l1 = "Ha-ha! Le spectacle était parfait!";
				link.l1.go = "patria_x29";
				break;
			}
            dialog.text = NPCStringReactionRepeat("Bonjour, monami."+GetSexPhrase("As-tu quelque chose à me dire ? Non ? Alors laisse-moi tranquille !","Ha, "+pchar.name+"Tu as affaire avec moi? Non? Alors ne me dérange pas.")+"Bonjour, monami.","Je croyais avoir été clair... Je t'ai dit de partir mais tu continues à m'agacer !","Bon, je commence à en avoir marre de cette impolitesse.","répéter",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Je pars déjà.","Bien sûr, Marcus...","Désolé, Marcus...","Oups...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Es-tu fou ? Tu voulais jouer au boucher, hein ? Tous les pirates sont en colère contre toi, garçon, tu ferais mieux de quitter cet endroit...","Il semble que tu sois devenu un chien enragé, garçon. Tu voulais te dégourdir un peu les bras ? Sans vouloir t'offenser, mais il n'y a rien pour toi ici. Dégage !");
				link.l1 = RandPhraseSimple("Ecoute, je veux arranger la situation.","Aidez-moi à résoudre ce problème, je vous prie...");
				link.l1.go = "pirate_town";
				break;
			}
			// Сага - завершаем искушение барбазона
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "terrax")
			{
				// Addon 2016-1 Jason пиратская линейка патч 17/1
				if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
				{
					link.l1 = "Marcus, cesseras-tu un jour d'être en colère contre moi ? J'ai sauvé ton ami Vincent, qui a pillé Carthagène avec nous, et j'ai aussi sauvé ta peau ! Ou Bernard ne t'a-t-il même pas dit ?";
					link.l1.go = "Temptation_13";
				}
				else
				{
					link.l1 = "Pourquoi es-tu si grossier, Marcus ? Bernard n'a-t-il rien dit à mon sujet ?";
					link.l1.go = "Temptation";
				}
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "to_lavega")
			{
				link.l2 = "Je cherche du boulot... Avez-vous quelque chose de rentable en tête ?";
				link.l2.go = "Mtraxx";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkTrade") && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "J'ai de la soie à vendre.";
				link.l2.go = "Mtraxx_silktrade";
			}
			if (pchar.questTemp.Mtraxx == "silk_14")
			{
				link.l1 = "Je t'ai trouvé un acheteur. C'est un constructeur naval de Port Royal. Il a besoin de soie de navire pour sa production et il pourra acheter des lots de cent rouleaux chaque mois pour 25 doublons le rouleau. Ses hommes recevront les marchandises du 10 au 15, la nuit, à Negril Cape. Le mot de passe - 'Un marchand de Lyon'. Le Chauve Geoffrey a déjà livré le premier lot en Jamaïque.";
				link.l1.go = "mtraxx_13";
			}
			if (pchar.questTemp.Mtraxx == "silk_15")
			{
				link.l1 = "Je t'ai trouvé un acheteur. C'est un constructeur naval de Port Royal. Il a besoin de soie de navire pour sa production et il pourra acheter des lots de cent rouleaux chaque mois pour 25 doublons le rouleau. Ses hommes recevront la marchandise du 10 au 15, la nuit, l'endroit est le Cap Negril. Le mot de passe - 'Un marchand de Lyon'. Il m'a fallu plus de deux mois pour trouver cet acheteur, Geffrey a déjà dû vendre la soie aux contrebandiers. Je suis désolé, Marcus.";
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
				dialog.text = RandPhraseSimple("Es-tu fou ? Tu voulais jouer au boucher ? Tous les pirates sont en colère contre toi, garçon, tu ferais mieux de quitter cet endroit...","On dirait que t'es devenu un chien enragé, gamin. Tu voulais te dégourdir les mains ? Pas d'offense, mais y a pas de place pour toi ici. Dégage !");
				link.l1 = RandPhraseSimple("Ecoute, je veux arranger la situation...","Aidez-moi à résoudre ce problème, s'il vous plaît...");
				link.l1.go = "pirate_town";
				break;
			}
			// Jason НСО
			if(!CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "Charles, qu'est-ce que tu fous ?!";
				link.l1 = "Marcus, tout est allé de travers. Je n'ai pu ni venir ni vous informer...";
				link.l1.go = "patria_33";
				break;
			}
			if(!CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "Content de te voir, ami !";
				link.l1 = "Content de te voir aussi. Merci pour le spectacle incroyable !";
				link.l1.go = "patria_29";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "Content de te voir, garçon ! Comment puis-je t'aider ?";
				link.l1 = "J'ai une proposition pour toi. Convenable pour un pirate, tu sais !";
				link.l1.go = "patria";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "C'est notre client ! Le travail est fait, votre Baron est assis dans un cachot bien gardé. Peut-être que vous voudriez jeter un coup d'œil, hé-hé ?!";
				link.l1 = "J'aurai tout le temps de faire cela, ha-ha. Est-il bien traité ?";
				link.l1.go = "patria_10";
				break;
			}
			// если Сага завалена, то у Маркуса ноды в двух местах и оплата вперед
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "As-tu des affaires pour moi ?";
				link.l1 = "Salutations, Marcus. Oui, une affaire. Profitable et pirate.";
				link.l1.go = "patria_x";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Condotier.NeedMoney") && pchar.questTemp.Patria == "epizode_12_pirates" && sti(pchar.money) >= 100000)
			{
				dialog.text = "As-tu apporté l'argent ?";
				link.l1 = "Je l'ai fait.";
				link.l1.go = "patria_x8";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "C'est notre client ! Le travail est fait, votre Baron est assis dans un cachot bien gardé. Peut-être aimeriez-vous y jeter un œil, hé-hé ?!";
				link.l1 = "J'aurai bien le temps de faire ça, ha-ha. Est-il bien traité ?";
				link.l1.go = "patria_10";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "Charles, c'est quoi ce bordel?!";
				link.l1 = "Marcus, tout est allé de travers. Je n'ai pu ni venir ni t'informer...";
				link.l1.go = "patria_x33";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "Voici notre marionnettiste !";
				link.l1 = "Ha-ha ! Le spectacle était parfait !";
				link.l1.go = "patria_x29";
				break;
			}
			// Тени прошлого
			if(CheckAttribute(pchar, "questTemp.Saga.Shadows") && pchar.questTemp.Saga.Shadows == "islatesoro" && npchar.location == "Pirates_townhall")
			{
				dialog.text = "Content de te voir, garçon ! Comment puis-je t'aider ?";
				link.l1 = "Marcus, je dois te parler. Je ne suis pas sûr que cela te plaira, mais j'ai besoin de ton aide quand même.";
				link.l1.go = "shadows";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "islatesoro" && npchar.location == "Pirates_townhall")
			{
				dialog.text = "Ha, te voilà, "+pchar.name+". Je vous attendais. Le Diable de la Forêt m'a intrigué avec votre problème concernant Tortuga...";
				link.l1 = "Il m'a dit que vous aviez trouvé une solution. Ai-je raison ?";
				link.l1.go = "terrapin";
				break;
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkTrade") && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "J'ai de la soie à vendre.";
				link.l2.go = "Mtraxx_silktrade";
			}
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar)+", content de te voir ! Que veux-tu cette fois, mate ?","Que veux-tu ?","Encore ? Ne dérange pas les gens si tu n'as rien à faire !","Tu es un "+GetSexPhrase("bon corsaire","bonne fille")+", donc tu peux vivre pour l'instant. Mais je ne veux plus te parler.","répéter",10,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Je voulais juste te voir.","Rien.","D'accord, Marcus, je suis désolé.","Bon sang, je suis vraiment désolé, Marcus !",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Vol!!! C'est inacceptable ! Prépare-toi à mourir, rat...","Hé, qu'est-ce que tu fais là ?! Tu pensais pouvoir me voler ? Tu es fichu...","Attends, mais qu'est-ce que c'est que ce bordel ?! Il s'avère que tu es un voleur ! Fin de la route, salaud...");
			link.l1 = LinkRandPhrase("Merde !","Carramba !","Ah, bon sang !");
			link.l1.go = "PL_Q3_fight";
		break;
					
		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(""+GetSexPhrase("Va-t'en","Va-t'en")+" d'ici!","Sors de chez moi !");
			link.l1 = "Oups...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Ne me distrait pas de mon travail avec tes paroles inutiles. La prochaine fois, ça ne se terminera pas aussi bien pour toi...";
        			link.l1 = "Compris, Marcus.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = RandPhraseSimple("Je suis fatigué de toi.","Je ne veux pas parler avec toi, alors tu ferais mieux de garder tes distances.");
			link.l1 = RandPhraseSimple("Eh bien...","Hm, très bien alors...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "J'espère que tu ne m'importuneras plus avec tes bavardages vides, sinon je devrai te tuer. Je dis bien, je ne serais pas ravi de le faire.";
        			link.l1 = "Tu peux en être sûr, Marcus, je ne vais pas...";
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
			dialog.text = "Ha ! Le héros des Turks ? Désolé pour l'accueil rude, garçon. Bernard m'a déjà parlé de ton intervention merveilleuse et a mentionné quelque chose à propos d'un piège pour moi. J'aimerais entendre les détails...";
			link.l1 = "C'était bien un piège. Ils te chassaient, pas Bernard. Il n'était que l'appât";
			link.l1.go = "Temptation_1";
		break;
		
		case "Temptation_1":
			dialog.text = "";
			link.l1 = "Le plan était simple. Vous étiez censé sauver votre ami et être le premier à monter à bord du 'Séparateur'. Et juste à ce moment-là, ils auraient tiré sur le navire et l'auraient réduit en miettes. La brigantine était chargée de poudre à canon comme l'enfer avec du soufre.";
			link.l1.go = "Temptation_2";
		break;
		
		case "Temptation_2":
			dialog.text = "Merde! De qui était cette folie?! Et comment pourrais-je découvrir où ils cachaient Bernard?!";
			link.l1 = "Les auteurs de ce plan étaient Jackman et son frère David. Un messager vous aurait informé que le 'Séparateur' attendait votre aide à la baie sud des Turks. Ils m'ont choisi comme messager et c'était leur erreur.";
			link.l1.go = "Temptation_3";
		break;
		
		case "Temptation_3":
			dialog.text = "Je ne comprends pas ! Quel est ton rôle dans tout ça ?";
			link.l1 = "J'ai observé ce salaud de Jackman pendant longtemps. Je travaille avec Jan Svenson si tu ne savais pas. Moi et le Diable des Forêts avons décidé de le démasquer. Jan est sûr que c'est lui le responsable de la mort de Blaze et que Steven a été accusé à tort.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end") link.l1.go = "Temptation_14";
			else link.l1.go = "Temptation_4"; //патч 17/1
		break;
		
		case "Temptation_4":
			dialog.text = "Héhé ! Mais une dent de requin avec ses initiales a été trouvée sur le corps de Blaze avec ses initiales - S.D. - cette chose appartient à Steven, tout le monde sait ça...";
			link.l1 = "Tout était une mise en scène. Jackman a joué gros. Il s'est débarrassé de Nathaniel Hawk et a pris sa place à Maroon Town, puis il a assassiné Sharp et a fait porter le chapeau à Shark pour le meurtre. J'ai suffisamment de preuves de ses crimes. Je les ai trouvées dans le coffre de Jacob. C'est là que se trouvaient la deuxième partie de la carte de Sharp et l'éclat de Hawk.";
			link.l1.go = "Temptation_5";
		break;
		
		case "Temptation_5":
			dialog.text = "Merde! Alors Steven est innocent? Et pourquoi Jacob a-t-il fait tout ça?";
			link.l1 = "Il s'attendait à devenir le chef des Frères et espérait quelque chose en rapport avec l'Isla Tesoro. Il n'a pas pu obtenir votre soutien ni celui de Svenson, alors il a décidé de se débarrasser de vous deux. Vous étiez le premier sur la liste. Jan, étant le plus dangereux, était le second.";
			link.l1.go = "Temptation_6";
		break;
		
		case "Temptation_6":
			dialog.text = "Où est ce salaud ?! Je vais le déchiqueter !";
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) // Акула жив
			{
				link.l1 = "Jackman et son frère sont morts ainsi que le reste de ses chasseurs. Je me suis personnellement occupé d'eux. Ce salaud ne fera plus de mal à personne. Marcus, voterais-tu pour Steven Dodson ? C'est ma faveur personnelle.";
				link.l1.go = "Temptation_7";
			}
			else
			{
				link.l1 = "Jackman et son frère sont morts ainsi que le reste des chasseurs. Je me suis personnellement occupé d'eux. Ce salaud ne fera plus de mal à personne. Malheureusement, Steven a été tué...";
				link.l1.go = "Temptation_10";
			}
		break;
		
		case "Temptation_7":
			dialog.text = "Bien sûr, je voterai ! J'ai toujours considéré Shark comme le plus digne d'entre nous après Blaze. Et j'ai presque cru en sa culpabilité. Nous l'avons tous fait ! Tiens, prends mon éclat.";
			link.l1 = "Très bien ! Maintenant tu peux respirer librement.";
			link.l1.go = "Temptation_8";
		break;
		
		case "Temptation_8":
			GiveItem2Character(pchar, "splinter_mt"); // дать осколок
			dialog.text = "Vrai... Si je comprends bien, tu représentes les intérêts de Requin ?";
			link.l1 = "Oui. Moi et Jan Svenson. Bien, Marcus, à plus tard!";
			link.l1.go = "Temptation_9";
		break;
		
		case "Temptation_10":
			dialog.text = "Mort ?! Comment ? L'oeuvre de Jackman aussi ?";
			link.l1 = "Non. Son propre maître d'équipage l'a fait, Chad Kapper était son nom. Il a déjà eu ce qu'il méritait... Marcus, Svenson pense que tu es le plus digne d'être le nouveau chef des Frères. Le reste des barons soutiendra cette décision. Acceptes-tu cela ?";
			link.l1.go = "Temptation_11";
		break;
		
		case "Temptation_11":
			dialog.text = "Eh ! Tu n'as pas besoin de me le demander deux fois. C'est un grand honneur d'être à la tête des Frères ! Ne pense même pas que je vais refuser.";
			link.l1 = "Parfait. Je suis heureux que tu aies accepté cela.";
			link.l1.go = "Temptation_12";
		break;
		
		case "Temptation_12":
			GiveItem2Character(pchar, "splinter_mt"); // дать осколок
			dialog.text = "Tiens, prends mon fragment. Remets-le à Svenson. Je suppose qu'il est responsable ?";
			link.l1 = "Oui, c'est lui. Très bien, Marcus, à plus tard !";
			link.l1.go = "Temptation_9";
		break;
		
		case "Temptation_9":
			dialog.text = "Oui, et je veux te remercier d'avoir sauvé mon ami Bernard. Tiens, prends cette bourse pleine d'or.";
			link.l1 = "Merci ! Adieu !";
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
			dialog.text = "Oui, il m'a parlé de l'arrivée magnifique de Charlie Prince aux Turks... Tu dis qu'il m'a sauvé la peau ? Comment ? Bernard m'a dit quelque chose à propos d'un piège...";
			link.l1 = "Oui, c'était un piège. Tu étais la cible, Bernard n'était que l'appât...";
			link.l1.go = "Temptation_1";
		break;
		
		case "Temptation_14":
			dialog.text = "Ha-ha-ha, travailler pour le Diable de la Forêt, hein Prince ? Alors, tu gagnes mieux ta vie avec lui que tu ne le faisais avec moi ? Dis-moi en toute honnêteté !";
			link.l1 = "Marcus, mettons le passé de côté pour de bon. Nous avons un objectif commun maintenant et c'est plus important que de piller des caravanes. Nom d'un chien ! C'est la chose la plus importante maintenant ! L'avenir de la Confrérie est en jeu !";
			link.l1.go = "Temptation_15";
		break;
		
		case "Temptation_15":
			dialog.text = "Bien, Prince, j'ai compris ! Vous êtes un corsaire libre après tout, travailler pour le Diable des Forêts était votre choix, et vous avez pris une bonne décision... Steven alors... Vous avez dit qu'il a été calomnié, n'est-ce pas ?";
			link.l1 = "Absolument raison.";
			link.l1.go = "Temptation_4";
		break;
		
		// Тени прошлого
		case "shadows":
			dialog.text = "Bien sûr, je ferai de mon mieux pour t'aider ! Vas-y.";
			link.l1 = "Jette un coup d'œil, Marcus... Voici une dent de requin. Que peux-tu m'en dire ?";
			link.l1.go = "shadows_1";
		break;
		
		case "shadows_1":
			RemoveItems(pchar, "shark_teeth", 1);
			dialog.text = "Ha ! C'est la dent d'un requin blanc tué par Steven Dodson, il espérait impressionner une fille. Depuis, les gens ont commencé à l'appeler Requin. Peu de gens pourraient faire cela sous l'eau avec un simple sabre. Mais il était jeune et stupide, et Beatrice Sharp était la plus belle fille des Caraïbes... Alors, comment l'as-tu obtenue ?";
			link.l1 = "Il m'a été donné par l'ancien bourreau de Saint John's. Cette dent a servi à tuer un homme. Son nom était... Joshua Leadbeater.";
			link.l1.go = "shadows_2";
		break;
		
		case "shadows_2":
			dialog.text = "C'est une vieille histoire. Steven a tué cet homme. Il était bouleversé par la mort de Beatrice et il pensait que Leadbeater était le seul responsable vivant de sa mort. Mais plus tard, il a trouvé des papiers sur le cadavre de Joshua, les a étudiés et a regretté son acte.\nLe Masque n'était pas à blâmer pour la mort de Beatrice, il avait seulement besoin de Butcher. L'ex-copine jalouse de Butcher, Jessica, avait orchestré tout cela.";
			link.l1 = "As-tu lu ces papiers ?";
			link.l1.go = "shadows_3";
		break;
		
		case "shadows_3":
			dialog.text = "Pourquoi devrais-je ? Bien sûr que non. Je n'étais pas intéressé par eux. Mais je peux te dire pourquoi le Masque poursuivait le Boucher si tu as un peu de temps libre. Le ivrogne Steven m'a raconté cette histoire de nombreuses fois.";
			link.l1 = "J'ai le temps. Fais-moi confiance, mon intérêt a un but. Je peux même écrire cette histoire.";
			link.l1.go = "shadows_4";
		break;
		
		case "shadows_4":
			dialog.text = "Je sais que tu ne perds jamais ton temps. Écoute donc. Joshua Leadbeater était le capitaine de la marine anglaise et le légendaire 'Neptune' était sous son commandement...";
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
			dialog.text = "... mais Leadbeater a survécu et a été récupéré par un navire. Sa blessure l'a défiguré et depuis, il porte un masque. Après un certain temps, les gens ont commencé à l'appeler le Masque. La vengeance contre l'homme qui l'avait marqué à vie est devenue son but dans la vie.";
			link.l1 = "Je vois... J'ai tout écrit. Je pense que je dois le relire et établir des parallèles avec toutes les informations que j'ai déjà. Une histoire triste en effet. As-tu déjà vu Jessica ?";
			link.l1.go = "shadows_7";
		break;
		
		case "shadows_7":
			dialog.text = "Bien sûr ! Elle accompagna le Boucher dans tous ses voyages jusqu'à ce qu'il la largue pour Beatrice. Jess ne put jamais lui pardonner cela. Les gens l'appelaient le talisman du Boucher, car il avait toujours de la chance lorsqu'elle était avec lui.\nCroyez-le ou non, mais dès qu'il s'est débarrassé d'elle à la Barbade, ses affaires ont mal tourné, les butins sont devenus maigres et le 'Neptune' est devenu un invité fréquent au chantier naval de l'Isla Tesoro. Mais cela peut s'expliquer par le fait que le Boucher passait la plupart de son temps avec Beatrice dans la cabine plutôt qu'au gaillard d'arrière.\nBeatrice n'était pas comme Jessica, elle n'était pas accro aux aventures et à la guerre, bien que Nicholas lui ait appris l'escrime et la navigation. Oui, elle aimait les romances maritimes, mais elle n'avait pas assez de dureté en elle. Le 'Neptune' du Boucher n'était pas le bon endroit pour elle. À la fin, cela l'a tuée.";
			link.l1 = "Et qu'en est-il de Jessica ?";
			link.l1.go = "shadows_8";
		break;
		
		case "shadows_8":
			dialog.text = "Oh, elle était quelque chose, c'est sûr... Chaque marin du 'Neptune' obéissait à ses ordres et pas seulement parce qu'elle était la petite amie du capitaine. Jess était une maîtresse de l'escrime et de la navigation, les efforts de Boucher n'étaient pas perdus. Elle était dure et téméraire, et elle était si belle.\nBeaucoup d'hommes voulaient partager un lit avec elle, mais elle ne voulait que Boucher, la déranger était vraiment risqué, beaucoup en ont ressenti les résultats sur leur propre peau littéralement, et pour les plus persistants, ses leçons d'escrime se sont avérées être les dernières de leur vie.\nJess possédait une épée très spéciale, la seule de son genre aux Caraïbes, je n'ai aucune idée d'où elle l'a obtenue. Une épée à lame flamboyante. La lame ne pouvait pas être saisie à la main et même le moindre contact laissait une terrible blessure.\nJess était une aventurière non pas de naissance, mais de vocation. Au fait, si vous avez besoin d'en savoir plus sur elle, vous pouvez parler à une de vos connaissances. Il peut vous en dire bien plus sur elle que moi.";
			link.l1 = "Vraiment ? Et qui est cet homme ?";
			link.l1.go = "shadows_9";
		break;
		
		case "shadows_9":
			dialog.text = "Jan Svenson. Le Diable de la Forêt ne l'admettra jamais, mais il avait des projets avec Jessica. C'était à l'époque où il avait déjà pris l'Ouest pour lui-même et sa renommée était quelque chose à envier, alors la tigresse était un bon parti pour lui.\nAprès que le Boucher se soit débarrassé de Jess, Jan a commencé à visiter la Barbade de manière suspecte, faisant trembler la garnison de peur, hé. Comme tu le sais, Jessica était la fille du planteur de Bridgetown.\nEn fin de compte, ses projets étaient bien connus dans les cercles privés, mais personne n'osait exprimer son opinion à ce sujet. Jan peut bien se prélasser à Blueweld de nos jours, mais à l'époque, un mot de travers à son adresse pouvait mal tourner.\nFinalement, cela n'a pas fonctionné pour eux. Jess ne pouvait pas vivre avec la douleur causée par la trahison du Boucher, et elle a eu sa revanche un an plus tard avec l'aide du Masque. Cette vengeance s'est terminée de manière terrible pour tout le monde : pour le Boucher, pour Beatrice, pour le Masque et pour elle-même. Ils sont tous morts.";
			link.l1 = "Non. Le Boucher est encore en vie.";
			link.l1.go = "shadows_10";
		break;
		
		case "shadows_10":
			dialog.text = "Quoi ?! Ai-je mal entendu ?! Il est vivant ?!";
			link.l1 = "Oui. Le capitaine Butcher n'a pas été pendu. Hm, en fait il l'a été, mais grâce à Jacob Jackman et Henry le Bourreau, qui ont effrayé le bourreau, il s'en est sorti vivant. La pendaison n'était qu'une mise en scène. J'ai des preuves.";
			link.l1.go = "shadows_11";
		break;
		
		case "shadows_11":
			dialog.text = "Incroyable ! Et où est-il maintenant ?";
			link.l1 = "Il est connu sous le nom de Lawrence Beltrop et il vit à Port-Royal. Mais il semble qu'il n'ait pas changé et qu'il soit toujours dangereux. Jackman, qui a semé beaucoup de pagaille parmi les Frères, suivait ses ordres.";
			link.l1.go = "shadows_12";
		break;
		
		case "shadows_12":
			dialog.text = "Bon sang ! Le quartier-maître a finalement retrouvé son capitaine ! Après tant d'années... Beltrop, dites-vous... attendez ! Maintenant je comprends pourquoi dans les papiers de Blaze il y avait ce protocole étrange de l'interrogatoire... Il semble que Blaze ait découvert quelque chose d'intéressant à propos de Boucher-Beltrop...";
			link.l1 = "De quoi parles-tu ?";
			link.l1.go = "shadows_13";
		break;
		
		case "shadows_13":
			dialog.text = "Quand j'ai pris cette résidence, je me suis accordé du temps pour jeter un oeil aux papiers de Blaze. J'ai trouvé un protocole d'interrogatoire de quelqu'un nommé Samuel Brooks. Il y avait beaucoup de détails sur les aventures de Thomas Beltrope, un pirate célèbre et le plus proche ami de Nicolas Sharp. Il semble qu'il soit le père du Boucher.";
			link.l1 = "Intéressant. On dirait que les enfants de Beltrop et Sharp ont repris le métier de leur père...";
			link.l1.go = "shadows_14";
		break;
		
		case "shadows_14":
			dialog.text = "Il semble que oui... Dis-moi, ami, pourquoi t'intéresses-tu tant au passé de gens déjà morts depuis longtemps ? De quoi s'agit-il ?";
			link.l1 = "J'ai besoin de papiers qui prouvent qu'Ellen McArthur est la fille de Beatrice Sharp et la petite-fille de Nicolas Sharp, et qu'elle a tous les droits de porter ce nom. Je me fiche que son nom de famille puisse être Beltrop.";
			link.l1.go = "shadows_15";
		break;
		
		case "shadows_15":
			dialog.text = "Je n'ai rien trouvé sur Ellen McArthur dans les archives de Blaze. Il est étrange que Béatrice n'ait pas parlé à Blaze de la naissance de sa nièce. Ce n'est pas son genre.";
			link.l1 = "Ecoute, peut-être qu'il y a quelque chose de plus dans les documents de Sharp sur cette histoire ? J'ai besoin de chaque détail que je peux obtenir !";
			link.l1.go = "shadows_16";
		break;
		
		case "shadows_16":
			dialog.text = "Hm... Peut-être. D'après les notes de Blaze, il essayait de trouver l'île où sa sœur était morte. Il y a des copies de documents d'archives concernant l'expédition punitive de Leadbeater. Rien d'intéressant, sauf quelques chiffres de latitude.\nCe parallèle traverse la mer des Caraïbes dans sa partie nord. Mais il n'y a aucun signe de longitude. Évidemment, les recherches de Blaze ont échoué, tu ne peux même pas imaginer combien de petites îles se trouvent à cette latitude.";
			link.l1 = "Et quelle est la latitude ?";
			link.l1.go = "shadows_17";
		break;
		
		case "shadows_17":
			dialog.text = "Voyons voir... Ici : 21 32' Nord. Je ne sais pas comment cela peut vous aider.";
			link.l1 = "Ça se peut. Merci beaucoup, Marcus, pour ton récit franc. À bientôt !";
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
			dialog.text = "Eh bien, je peux faire quelque chose pour vous. Comme vous le savez, la sécurité de Tortuga n'est pas seulement assurée par le fort La Roche mais aussi par une escadre pirate qui garde constamment les côtes de l'île. Le port de Tortuga est sûr, ces gars-là connaissent leur métier et ils ont des navires puissants. Levasseur a attiré ces capitaines depuis longtemps.\nIls sont capables de se battre même contre une escadre de ligne et ils seront des adversaires sérieux. Donc, en tant que gardien du Code et aussi chef de la Fraternité de la Côte, je peux faire en sorte que ces chiens de garde quittent les côtes de Tortuga.";
			link.l1 = "Et c'est tout ?";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			dialog.text = "Est-ce que cela ne suffit pas? De toute façon, je ne peux pas t'aider davantage. Tu dois détruire le fort, mais au moins tu n'as pas besoin de te battre contre ces navires de garde. Crois-moi, ils sont plus dangereux que le Fort, donc mon aide rendra tout cela plus facile.";
			link.l1 = "Eh bien, si je dois de toute façon l'attaquer, le départ de l'escadron pirate sera vraiment utile. Merci, Marcus ! Quand puis-je attaquer Tortuga ?";
			link.l1.go = "terrapin_2";
		break;
		
		case "terrapin_2":
			dialog.text = "Quand tu veux. Les navires de garde partiront à mon signal.";
			link.l1 = "Très bien. Je dois y aller alors pour me préparer.";
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
            dialog.text = "Résoudre le problème ? Tu as la moindre idée de ce que tu as fait ? Quoi qu'il en soit, ramène-moi un million de pesos et je persuaderai les gars d'oublier ton acte. Si l'idée ne te plaît pas, alors tu peux aller au diable.";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "D'accord, je suis prêt à payer.";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "Adieu...";
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
            dialog.text = "Bien ! Considère-toi à nouveau propre. Mais j'espère que tu ne feras plus jamais de telles choses répugnantes.";
			link.l1 = "Je n'le ferai pas. Bien trop cher pour moi. Adieu...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
		
		// Addon 2016-1 Jason ------------------------- пиратская линейка --------------------------
		case "Mtraxx":
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				dialog.text = "Commence par te procurer un navire, puis viens demander du boulot. Un terrien n'a rien à faire ici. Dégage !";
				link.l1 = "Hmm... Je vois.";
				link.l1.go = "exit";
				break;
			}
			if(ChangeCharacterHunterScore(Pchar, "spahunter", 0) > 10)
			{
				dialog.text = "Es-tu complètement fou ? La moitié du monde espagnol te poursuit. Tu feras plus de mal que de bien. Résous tes problèmes, puis reviens. C'est tout ce que je voulais dire ! Va-t'en d'ici !";
				link.l1 = "Hmm... Je vois.";
				link.l1.go = "exit";
				break;
			}
            dialog.text = "Tu veux de l'action, hein ? Ha-ha ! Bien... Mais je te préviens, garçon, tu ne trouveras pas de paix avec moi. Si tu as peur de l'odeur de la poudre ou si tu ne peux pas verser de sang - la porte est derrière toi. Je ne supporte pas les mauviettes. De plus, tu ne feras pas long feu avec moi si tu es une balance ou un rat qui aime voler la part de butin d'un partenaire. Alors, quoi ? Tu es partant ?";
			link.l1 = "Je suis partant, Marcus. Je n'ai pas peur de me battre et il n'y a aucun chien qui puisse m'accuser d'être soit un lâche, soit un rat.";
			link.l1.go = "Mtraxx_1";
			link.l2 = "Ouh là, c'est trop dur pour moi ! Je vous demande pardon, Marcus, mais je ferais mieux de m'en aller...";
			link.l2.go = "Mtraxx_exit";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("LaVega");
		break;
		
		case "Mtraxx_exit":
            DialogExit();
			pchar.questTemp.Mtraxx = "fail";
		break;
		
		case "mtraxx_wait":
            dialog.text = "Quoi, tu es encore là ?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkTrade") && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "J'ai de la soie à vendre.";
				link.l2.go = "Mtraxx_silktrade";
				link.l1 = "Je pars déjà.";
				link.l1.go = "exit";
				break;
			}
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		case "Mtraxx_1":
            dialog.text = "Ha-ha, eh bien, mon petit pirate courageux, discutons affaires alors. Ma source à Santo Domingo m'a informé d'un capitaine espagnol si riche en ambre bleu qu'il en fait cadeau aux putains. As-tu entendu parler de l'ambre bleu ?";
			link.l1 = "J'ai. Une pierre rare et précieuse.";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "Précisément. Même ici, les banquiers et les joailliers paient cher pour cela et dans la bonne vieille Europe, vous pouvez en obtenir dix fois plus. L'ambre n'est pas une pierre rare aux Caraïbes mais l'ambre bleu est une rareté. Et maintenant, nous avons un chien rusé castillan qui se vante d'avoir plus d'ambre bleu que les banquiers de Cuba et d'Hispaniola n'ont d'ambre jaune ensemble.";
			link.l1 = "Peut-on faire confiance aux histoires d'un Espagnol ivre ? Il a trouvé trois doublons et dit à tout le monde qu'il a découvert El Dorado.";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "Je ne l'aurais pas cru, mais il offrait en réalité de l'ambre bleu aux putains. Il doit y avoir quelque chose de vrai dans ses fanfaronnades. Va à Santo Domingo et enquête. Si tu trouves le gisement d'ambre bleu, ce sera encore mieux. Fais cela et je peux te garantir une récompense et du respect à La Vega.";
			link.l1 = "Et si tes informations ne valent rien ?";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
            dialog.text = "Alors prouve-moi que Castilian est un menteur.";
			link.l1 = "Très bien. Qui est votre source à Saint-Domingue ?";
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
						SetCharacterPerk(pchar, "FlagSpa");
						log_info("You have received spanish flag");
						pchar.questTemp.GiveMeSpaFlag = true;
					}
					else // есть лицензия
					{	
						if(GetDaysContinueNationLicence(HOLLAND) < 60) 
						{
							sTemp = ". Wait, how are you going to trade without having the right flag?! Here you go, a 60-day trading license, longer than yours. As well as the Spanish flag for landing in Santo Domingo. From now on, I recommend getting your own, it will help to fool the simpleton in the trading pelvis. This one will be returned to me.";
							GiveNationLicence(HOLLAND, 60);
							SetCharacterPerk(pchar, "FlagSpa");
							log_info("You have received spanish flag");
							pchar.questTemp.GiveMeSpaFlag = true;
						}
						else 
						{
							sTemp = ". Wait, how are you going to trade without having the right flag?! Here, take the Spanish flag for the Santo Domingo landings. From now on, I recommend getting your own, it will help to fool the simpleton in the trading pelvis. This one will be returned to me.";
							SetCharacterPerk(pchar, "FlagSpa");
							log_info("You have received spanish flag");
							pchar.questTemp.GiveMeSpaFlag = true;
						}
					}
				}
			}
			// <-- legendary edition
            dialog.text = "Tu as besoin d'une fille de bordel nommée Gabriela Chapado. Dis mon nom et le mot de passe - 'Collier d'ambre'. Elle te donnera les détails. Et ne perds pas de temps - l'information est encore fraîche, mais dans un jour ou deux, elle pourrait devenir obsolète."+sTemp;
			link.l1 = "Compris, Marcus. Je me dirige vers Santo Domingo.";
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
            dialog.text = "On m'a déjà informé de ton arrivée. Fais-moi un rapport !";
			link.l1 = "Je me suis occupé de cet amoureux de l'ambre bleu bien que cela n'ait pas été facile. J'ai réussi à trouver ses dépôts et à les piller. Je vous ai apporté "+FindRussianQtyString(i)+" morceaux d'ambre bleu.";
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
				dialog.text = "Eh bien, eh bien... Fiston, tu te souviens de mon avertissement sur les dangers d'être un mouchard? Qu'est-ce que tu m'as dit alors? Aucun chien ne peut te blâmer pour ça? Tu penses que je suis stupide, gamin? Je sais parfaitement que tu as pillé "+FindRussianQtyString(sti(pchar.questTemp.Mtraxx.JewQty))+" morceaux d'ambre bleu à la Côte des Moustiques. Maintenant cours, petite vermine, cours, et prie pour que nous ne nous rencontrions jamais plus !";
				link.l1 = "Merde !";
				link.l1.go = "AngryExitAgainWithOut";
				pchar.questTemp.Mtraxx = "fail";
				npchar.Dialog.currentnode = "First time";
				CloseQuestHeader("Roger_1");
				// belamour legendary edition забрать флаг обратно
				if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
				{
					DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
					DeleteAttribute(pchar,"perks.list.FlagSpa"); 
					log_info("You have given spanish flag");
				}
			}
			else
			{
				PlaySound("interface\important_item.wav");
				Log_Info("You have given "+FindRussianQtyString(GetCharacterItem(pchar, "jewelry7"))+" pieces of blue amber");
				RemoveItems(pchar, "jewelry7", sti(pchar.questTemp.Mtraxx.JewQty));
				dialog.text = "Bien joué, garçon ! Tu t'es montré sous ton meilleur jour : tu as géré une affaire difficile et rapporté tout ce que tu as pillé. Bon travail ! Je suis content de ne pas m'être trompé à ton sujet.";
				link.l1 = "Qu'en est-il de ma part, Marcus ?";
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
				DeleteAttribute(pchar,"perks.list.FlagSpa"); 
				log_info("You have given spanish flag");
			}
            dialog.text = "Parlé comme un vrai pirate, ha-ha-ha ! La moitié du butin est à toi. Prends-le.";
			link.l1 = "Merci, capitaine. As-tu autre chose pour moi?";
			link.l1.go = "mtraxx_10";
			DeleteAttribute(pchar, "questTemp.Mtraxx.JewQty");
			CloseQuestHeader("Roger_1");
			Achievment_Set("ach_57");
		break;
		
		case "mtraxx_10":
            dialog.text = "J'ai toujours des tâches pour des gars capables. Il y a une affaire délicate dont je veux que tu t'occupes. Il y a un navire stationné à Capsterville, appelé le 'Serpent', sous le commandement de Geffrey Brooke aussi connu sous le nom de Geffrey le Chauve. Il travaille pour moi. Un excellent combattant, il sait tout sur les armes à feu et les lames mais c'est un idiot complet dans tous les autres aspects de la vie. Mais ne soyons pas durs avec le Chauve, personne n'est parfait, ha-ha !\nAlors. Ce dur à cuire a attaqué un convoi hollandais au nord de Saint-Martin et capturé un brick rempli de sacs de blé. Le truc, c'est qu'il a réussi à trouver de la soie de navire cachée parmi les sacs. Un très gros chargement. Cette marchandise est extrêmement précieuse et rare, les Hollandais la rapportent d'Europe uniquement pour les besoins de leur armée. Cette soie est utilisée pour des voiles spéciales qui augmentent la vitesse du navire et sa capacité à naviguer par le vent.\nIl est presque impossible d'en acheter, la vendre n'est pas un problème mais il est difficile de trouver le bon prix. Ces maudits commerçants baissent toujours le prix ! Je sais qu'il y a des gens aux Caraïbes qui sont prêts à donner un bon prix en doublons pour acheter cette soie et ton objectif est de trouver ces personnes.\nQuoi ? N'importe quel idiot peut piller des caravanes mais le commerce est réservé aux gens qui ont au moins un signe d'existence de cerveau dans le crâne. Je prévois de vendre de la soie de navire sur une base mensuelle donc ton objectif est de trouver un acheteur régulier qui paiera au moins vingt doublons d'or pour un rouleau. Tu as deux mois pour cela, je ne peux pas garder Geffrey le Chauve à Capsterville éternellement.\nC'est tout. Mets les voiles vers Capsterville et parle à Geffrey avant qu'il ne vende la cargaison aux contrebandiers pour une bouchée de pain. Je t'ai déjà dit qu'il est un peu 'simple'.";
			link.l1 = "Hm... Compris. Déjà en route.";
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
            dialog.text = "Ha ! Voilà le courageux capitaine "+GetFullName(pchar)+" !  Qu'en est-il de l'acheteur ?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkLate"))
			{
				link.l1 = "Je t'ai trouvé un acheteur. C'est un constructeur naval de Port Royal. Il a besoin de soie pour ses navires et il pourra acheter des lots de cent rouleaux chaque mois pour 25 doublons le rouleau. Ses hommes recevront la marchandise du 10 au 15, la nuit, l'endroit est le Cap Negril. Le mot de passe - 'Un marchand de Lyon'. Cela m'a pris plus de deux mois pour trouver un tel acheteur, Geffrey a dû déjà vendre la soie aux contrebandiers. Je suis désolé, Marcus.";
				link.l1.go = "mtraxx_15";
			}
			else
			{
				link.l1 = "Je t'ai trouvé un acheteur. C'est un constructeur naval de Port Royal. Il a besoin de soie de navire pour sa production et il pourra acheter des lots de cent rouleaux chaque mois pour 25 doublons le rouleau. Ses hommes recevront les marchandises du 10 au 15, la nuit, l'emplacement est le cap Negril. Le mot de passe - 'Un marchand de Lyon'. Le Chauve Geffrey a déjà livré le premier lot à la Jamaïque.";
				link.l1.go = "mtraxx_13";
			}
		break;
		
		case "mtraxx_13":
            dialog.text = "C'est excellent, mon ami ! Bien joué. Il est difficile de trouver un homme capable d'utiliser à la fois ses mains et sa tête. Reviens me voir dans 20 jours pour recevoir ta récompense. Le Chauve Geffrey aura apporté l'argent de la première transaction d'ici là."; // правки прогона 3
			link.l1 = "Très bien, Marcus. À bientôt. J'espère que tu auras une autre mission pour moi.";
			link.l1.go = "mtraxx_14";
		break;
		
		case "mtraxx_14":
            dialog.text = "Je le ferai. À plus tard.";
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
            dialog.text = "Dommage, mais c'est tout de même un énorme succès. Tu as fait du bon boulot ! Tu ne recevras pas ta part du lot de Geffrey, mais tu mérites tout de même une récompense. Reviens me voir dans un mois, j'aurai vendu le premier lot à ton acheteur d'ici là, puis nous en parlerons.";
			link.l1 = "Très bien, Marcus. À bientôt. J'espère que tu auras un autre boulot pour moi.";
			link.l1.go = "mtraxx_14";
		break;
		
		case "mtraxx_16":
			//pchar.quest.Mtraxx_SilkPayLate.over = "yes";
            dialog.text = "Te voilà, "+pchar.name+" Parlons de ta récompense.";
			link.l1 = "J'aime les discussions comme celle-ci, ha-ha-ha ! Je suis tout ouïe.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkLate")) link.l1.go = "mtraxx_19";
			else link.l1.go = "mtraxx_17";
		break;
		
		case "mtraxx_17":
            dialog.text = "Bald Geffrey a vendu à votre acheteur le premier lot de 105 rouleaux de soie de navire. Comme je comptais les vendre vingt doublons le rouleau, je pense qu'il serait équitable de vous donner la différence. C'est ma décision. Votre part est de 525 doublons plus un bonus - un doublon par rouleau. Cela fait un total de 630 doublons. Tenez, prenez-les.";
			link.l1 = "Gratitude, Marcus !";
			link.l1.go = "mtraxx_18";
		break;
		
		case "mtraxx_18":
			TakeNItems(pchar, "gold_dublon", 630);
			Log_Info("You have received 630 doubloons");
			PlaySound("interface\important_item.wav");
            dialog.text = "Encore une chose. Tu peux tirer un bénéfice supplémentaire de cela.";
			link.l1 = "Intéressant... Continue.";
			link.l1.go = "mtraxx_19";
		break;
		
		case "mtraxx_19":
            dialog.text = "Votre acheteur veut plus de 100 rouleaux de soie à livrer pour les deux prochains mois. Si vous en avez, apportez-moi de 20 à 100 rouleaux pour un prix de 24 doublons. L'offre sera valable pendant deux mois.";
			link.l1 = "Très bien ! J'en apporterai plus si j'en ai.";
			link.l1.go = "mtraxx_20";
			pchar.questTemp.Mtraxx.SilkTrade = "true";
			SetFunctionTimerCondition("Mtraxx_SilkTradeOver", 0, 0, 60, false);
		break;
		
		// торговля шелком
		case "mtraxx_silktrade":
			iTotalTemp = GetSquadronGoods(pchar, GOOD_SHIPSILK);
            dialog.text = "Combien as-tu ?";
			link.l1 = ""+FindRussianQtyString(iTotalTemp)+".";
			if (iTotalTemp > 100) link.l1.go = "mtraxx_silktrade_2";
			else link.l1.go = "mtraxx_silktrade_1";
		break;
		
		case "mtraxx_silktrade_1":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, iTotalTemp);
			TakeNItems(pchar, "gold_dublon", iTotalTemp*24);
            dialog.text = "Très bien. Prends l'or - 24 doublons pour un lancer comme convenu.";
			link.l1 = "Gratitude !";
			link.l1.go = "mtraxx_silktrade_3";
		break;
		
		case "mtraxx_silktrade_2":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 100);
			TakeNItems(pchar, "gold_dublon", 2400);
            dialog.text = "Je prendrai cent rouleaux. Prends l'or - 24 doublons par rouleau comme convenu.";
			link.l1 = "Gratitude !";
			link.l1.go = "mtraxx_silktrade_3";
		break;
		
		case "mtraxx_silktrade_3":
            DialogExit();
			npchar.dialog.currentnode = "First time";
			DeleteAttribute(pchar, "questTemp.Mtraxx.SilkTrade");
		break;
		
		case "mtraxx_20":
            dialog.text = "Parlons d'une affaire plus urgente, veux-tu t'occuper de quelque chose de dangereux ?";
			link.l1 = "Bien sûr ! Moi et mes hommes sommes prêts à prendre la mer immédiatement.";
			link.l1.go = "mtraxx_24";
		break;
		
		case "mtraxx_22":
            dialog.text = "Putain de bordel, "+pchar.name+", où diable étais-tu passé ? Tu te souviens quand je t'ai dit de venir me voir ? J'avais un travail pour toi et maintenant c'est fichu grâce à ton excellent sens du timing. Tu m'as vraiment contrarié, garçon. Déguerpis, je ne travaille pas avec ceux sur qui je ne peux pas compter.";
			link.l1 = "Eh bien, merde...";
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
						SetCharacterPerk(pchar, "FlagSpa");
						log_info("You have received spanish flag");
						pchar.questTemp.GiveMeSpaFlag = true;
					}
					else // есть лицензия
					{	
						if(GetDaysContinueNationLicence(HOLLAND) < 40) 
						{
							sTemp = ". Tell me, how are you going to fool the bungler in the fort?! Your paper won't help you without the right flag. I feel that you will let me down one day with such sloppiness... Here, a trading license for 40 days, more than yours. As well as the Spanish flag for landing in Maracaibo. You will return it upon arrival. The new generation, pah...";
							GiveNationLicence(HOLLAND, 40);
							SetCharacterPerk(pchar, "FlagSpa");
							log_info("You have received spanish flag");
							pchar.questTemp.GiveMeSpaFlag = true;
						}
						else 
						{
							sTemp = ". Tell me, how are you going to fool the bungler in the fort?! Your paper won't help you without the right flag. I feel that you will let me down one day with such sloppiness... Here you go... You will return it back upon arrival. The new generation, pah...";
							SetCharacterPerk(pchar, "FlagSpa");
							log_info("You have received spanish flag");
							pchar.questTemp.GiveMeSpaFlag = true;
						}
					}
				}
			}
			// <-- legendary edition
            dialog.text = "Then listen closely. Two months ago I had an appointment with a captain by the name of Jean Picard, also known as Jean the Handsome. He didn't show up to the meeting and since I was going to discuss serious matters with him, I did some investigation regarding his whereabouts. Turned out our good brave privateer and his brigantine had managed to engage in a fight with a Spanish heavy galleon under command of don Eduardo de Losad and he is a tough son of a bitch. As a result, Jean and what's left of his crew was taken to Maracaibo and sold to a local plantation. This is where he is, busy with honest labor, at the moment.\nYour tasks are: firstsly - investigate the details of his misfortunes, secondly - get him out from plantation alive and bring him here; I really need details of his story. I am assigning a captain of a barquentine called 'Moray' to assist you in this. Captain's name is Paul Chant also known as Pelly the Cutlass. Remember Geffrey? He is almost as dumb as him, but good at fighting too.\nHe will be waiting for you at cape Ragget Point, on Barbados. Find him and his 'Moray' and sail to Maracaibo. Cutlass will follow your orders without asking stupid questions. Actually, he won't be asking questions at all. Just do your job and come back here, I'll be waiting for you. Here is ten thousand pesos for future expenses"+sTemp+". Any questions?";
			link.l1 = "Non. Tout est clair. Cap sur la Barbade.";
			link.l1.go = "mtraxx_25";
		break;
		
		case "mtraxx_25":
			AddMoneyToCharacter(pchar, 10000);
            dialog.text = "Je te souhaite bonne chance alors. Sois rapide, ne fais pas attendre Cutlass et le pauvre Jean.";
			link.l1 = "Bien sûr, patron ! J'y vais.";
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
            dialog.text = "Bienvenue, mon brave corsaire, ha-ha ! As-tu abattu une escadre espagnole ? Picard me l'a déjà dit. Bien joué !";
			link.l1 = "Ouais, mes gars les ont bien amochés quand on s'éloignait de Maracaibo.";
			link.l1.go = "mtraxx_28";
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup3"))
			{
				dialog.text = "Bienvenue, mon brave corsaire, ha-ha ! Picard m'a déjà raconté. Bien joué !";
				link.l1 = "... ";
				link.l1.go = "mtraxx_28";
			}
		break;
		
		case "mtraxx_28":
            dialog.text = "Je vois dans tes yeux que tu attends ta récompense. C'est légitime. Jean te paiera, après tout, c'était sa vie que nous essayions de sauver là-bas. Envoie-lui la note mais plus tard - le gamin n'a ni équipage ni navire. C'est un gamin intelligent comme toi, donc son état actuel ne durera pas longtemps.";
			link.l1 = "Hm... Eh bien... Je patienterai. Du travail pour moi, Marcus? Sans sauver ou chercher qui que ce soit?";
			link.l1.go = "mtraxx_29";
		break;
		
		case "mtraxx_29":
            dialog.text = "Fatigue d'être la chandelle la plus brillante ? Je dois te décevoir ici : j'ai assez de brutes sans cervelle comme Cutlass, je vais utiliser tes talents en conséquence. J'aurai un travail pour toi dans un mois, maintenant tu devrais naviguer vers Isla Tesoro et voir Pasquale Lavoisier, c'est un marchand de Sharptown.\nIl a demandé qu'on lui envoie un pirate dur à cuire dès que possible pour une affaire sérieuse - probablement ce que tu veux : moins de réflexion et plus de coups de feu. Tu as une semaine pour te montrer à lui, alors ne perds pas de temps ou tu perdras cette mission. Et sois poli, n'essaie pas de le tromper, cet homme est respecté parmi les Frères. Maintenant va et reviens me voir dans un mois. Ne sois pas en retard !";
			link.l1 = "Très bien, Marcus. À la prochaine!";
			link.l1.go = "mtraxx_30";
		break;
		
		case "mtraxx_30":
            DialogExit();
			// belamour legendary edition забрать флаг обратно
			if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
			{
				DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
				DeleteAttribute(pchar,"perks.list.FlagSpa"); 
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
            dialog.text = "Ouah ! Un homme mort est revenu ! Nous t'avons déjà enterré, garçon ! Mais on dirait que tu es toujours en vie.";
			link.l1 = "Comme tu peux le voir, Marcus...";
			link.l1.go = "mtraxx_32";
		break;
		
		case "mtraxx_32":
            dialog.text = "Alors pourquoi as-tu mis autant de temps pour venir d'Hispaniola depuis Maracaibo ? Tu n'es plus dans mon organisation, gamin. Je suis vraiment content de te voir en vie, mais il n'y a plus de travail pour toi ici.";
			link.l1 = "Eh!.. Quel dommage...";
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
				dialog.text = "Merde "+pchar.name+", où étais-tu passé ?! Je t'ai dit de me voir dans un mois ! Ce n'est pas l'armée mais un peu de foutue discipline est attendue ! Dégage, je ne travaillerai plus avec toi !";
				link.l1 = "Comme tu veux...";
				link.l1.go = "mtraxx_33";
				break;
			}*/
			if (GetNpcQuestPastDayParam(npchar, "task_date") < 28) // рано пришёл
			{
				dialog.text = " "+pchar.name+", je t'ai dit 'reviens me voir dans un mois'. Je n'ai pas de temps à perdre avec toi en ce moment.";
				link.l1 = "D'accord...";
				link.l1.go = "mtraxx_34x";
				break;
			}
			if (pchar.questTemp.Mtraxx == "pasq_angry")
			{
				dialog.text = "Un agent de Lavoisier m'a dit que tu l'avais baisé avec son bois noir. Je t'avais prévenu de ne pas être un rat et d'être juste avec Pasquale. Tu as enfreint mes deux règles. Tu es un gamin intelligent mais c'est inacceptable. Fous le camp d'ici et oublie le chemin vers cet endroit.";
				link.l1 = "Merde...";
				link.l1.go = "AngryExitAgainWithOut";
				pchar.questTemp.Mtraxx = "fail";
				npchar.dialog.currentnode = "First time";
				CloseQuestHeader("Roger_4");
				break;
			}
			if (pchar.questTemp.Mtraxx == "pasq_fail")
			{
				dialog.text = "Un agent de Lavoisier m'a dit que tu l'avais baisé avec son bois noir - t'as pas ramené tout le lot. Si c'était un Espadon sans cervelle ou un Chauve, peut-être j'aurais cru qu'ils n'avaient vraiment pas capturé tout le chargement, mais un gamin aussi malin que toi... T'as décidé de berner Pasquale ? Je t'ai dit 'ne le trompe pas' ! Je n'ai plus confiance en toi, et je n'ai plus d'affaires avec toi non plus. Dégage d'ici et oublie le chemin vers cet endroit !";
				link.l1 = "Ton Lavoisier est lui-même un rat !";
				link.l1.go = "AngryExitAgainWithOut";
				pchar.questTemp.Mtraxx = "fail";
				npchar.dialog.currentnode = "First time";
				CloseQuestHeader("Roger_4");
				break;
			}
			if (pchar.questTemp.Mtraxx == "pasq_late" || pchar.questTemp.Mtraxx == "pasq_sink" || pchar.questTemp.Mtraxx == "pasq_esc")
			{
				pchar.questTemp.Mtraxx.CharleePrince = "true"; // атрибут - ГГ известный пират // правки прогона 3
				dialog.text = "Ha ! Charlie Prince, un capitaine courageux ! C'est ton nouveau nom à La Vega au cas où tu ne le saurais pas. Alors, as-tu aimé être une brute ? Non ? Dame Fortune t'a-t-elle tourné le dos cette fois-ci ? C'est ainsi que vivent mes agents sans cervelle comme Cutlass : aujourd'hui il fait la fête dans un bordel, gaspillant tout ce qu'il a gagné, dans une semaine il est à ma porte, quémandant quelques milliers pour payer son équipage rempli d'idiots, tout comme lui. Peu importe. Parlons affaires ?";
				link.l1 = "Bien sûr !";
				link.l1.go = "mtraxx_36";
				break;
			}
            dialog.text = "Ha ! Charlie Prince, un capitaine courageux ! Ha-ha ! Un agent de Lavoisier m'a dit que tu t'en étais bien sorti. Je suis content que tu aies réussi à montrer un peu de respect à notre profiteur.";
			link.l1 = "Il ne lui ferait pas de mal d'être plus généreux...";
			link.l1.go = "mtraxx_35";
		break;
		
		case "mtraxx_35":
			pchar.questTemp.Mtraxx.Pasquale.Continue = "true"; // правки прогона 3
            dialog.text = "Rappelle-toi ce que j'ai dit à propos des brutes sans cervelle et des acheteurs de biens volés ? Bien. Ne prends jamais un travail comme ça à l'avenir. Laisse ça à Cutlass et à des gens comme lui. Peu importe. Parlons affaires ?";
			link.l1 = "Bien sûr !";
			link.l1.go = "mtraxx_36";
		break;
		
		case "mtraxx_36":
            dialog.text = "Parfait ! Jean Picard arrive ici, il te dira plus. Toi et Jean travaillerez ensemble sur cette mission. De plus, c'est sa chance de te rembourser sa dette... Le voilà !";
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
			TakeNItems(sld, "cartridge", 40);
			LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "cartridge");
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
            dialog.text = "Mon gars se joindra à votre raid. Il s'appelle Luka Bayard, plus connu sous le nom de Luke Leprechaun. Lui et ses hommes sont des boucaniers - des chasseurs qui ont passé la majeure partie de leur vie à chasser dans les forêts d'Hispaniola. Donc, ils sont maîtres du trekking dans la jungle, ajoutez vos combattants à eux et considérez Mérida comme la vôtre. Vous prendrez le tiers du butin. Le reste sera pris par Jean. Jean, vous donnerez votre dette à ce brave capitaine de votre part puis apporterez ce qui reste à moi. On arrangera ça entre nous alors. Des questions? Splendide! Leprechaun vous attendra dans notre port. Bonne chance corsaires, ha-ha!";
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
            dialog.text = "Bienvenue, mon brave forban ! Les rumeurs de ton raid nous sont déjà parvenues.";
			link.l1 = "Je ne peux pas dire que j'aime entendre ça. De telles choses devraient rester inconnues...";
			link.l1.go = "mtraxx_41";
		break;
		
		case "mtraxx_41":
            dialog.text = "Crois-moi, ils ne le sont jamais, mon ami. Peu importe. Est-ce que Picard a effacé sa dette envers toi ?";
			link.l1 = "Oui.";
			link.l1.go = "mtraxx_42";
		break;
		
		case "mtraxx_42":
            dialog.text = "Très bien. Est-ce que Luke Leprechaun t'a fait bonne impression ?";
			link.l1 = "Il l'a fait.";
			link.l1.go = "mtraxx_43";
		break;
		
		case "mtraxx_43":
            dialog.text = "Parfait alors. Tout le monde est content, tout le monde est payé.";
			link.l1 = "As-tu un boulot pour moi, Marcus?";
			link.l1.go = "mtraxx_44";
			// belamour legendary edition отказ после событий Мериды
			link.l2 = "Tu sais, Marcus, j'ai tout pesé et ce boulot n'est pas pour moi. Je suis désolé, mais j'ai déjà pris ma décision.";
			link.l2.go = "mtraxx_44a";
		break;
		
		case "mtraxx_44":
            dialog.text = "Pas de vrai travail pour l'instant. Bien que j'aie une faveur personnelle à demander. Intéressé ?";
			link.l1 = "Bien sûr, patron. Quel service ?";
			link.l1.go = "mtraxx_45";
		break;
		
		case "mtraxx_45":
            dialog.text = "Il y a une pinasse 'Kittie' près des côtes de La Vega. Elle est là depuis des jours, attendant une escorte pour Bridgetown. Pas question que je la laisse naviguer seule là-bas pour des raisons évidentes. Seriez-vous assez aimable pour l'accompagner ? J'aurai un vrai travail pour vous à votre retour. Et, bien sûr, de l'argent pour vous payer cet accompagnement.";
			link.l1 = "Marché conclu.";
			link.l1.go = "mtraxx_46";
		break;
		
		case "mtraxx_46":
            dialog.text = "Chouette ! Bonne navigation.";
			link.l1 = "Merci !";
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
            dialog.text = "Quoi ?! Je t'ai ramassé dans la rue, rempli tes poches d'ambre et de pierres précieuses ! C'est ainsi que tu me remercies ?";
			link.l1 = "Merida m'a montré que je n'ai pas assez de cœur de pierre pour ce boulot. Pas aussi impitoyable que toi et tes gars. Ne sois pas malfaisant.";
			link.l1.go = "mtraxx_45a";
		break;
		
		case "mtraxx_45a":
            dialog.text = "Faiblard ! Eh bien, dégage ! Va te coltiner du fret ou, encore mieux, bois-toi jusqu'à la mort comme le reste des perdants !";
			link.l1 = "D'accord...";
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
            dialog.text = "Ah, te voilà... Je t'attendais déjà. Voici 10 000 pour l'escorte de 'Kittie'.";
			link.l1 = "Merci... J'ai quelque chose à discuter avec toi, Marcus.";
			link.l1.go = "mtraxx_49";
		break;
		
		case "mtraxx_49":
            dialog.text = "Le fais-tu ?! Ha-ha ! Tire !..";
			link.l1 = "Souviens-toi comment Jean Picard s'est fait réduire en esclavage ? D'abord, il a pillé une caravane hollandaise avec un corsaire britannique et puis la même chose lui est arrivée par un lourd galion espagnol.";
			link.l1.go = "mtraxx_50";
		break;
		
		case "mtraxx_50":
            dialog.text = "Rappelle-toi. Et?";
			link.l1 = "J'ai été abordé à Bridgetown par Ignacio Marco. Le même corsaire portugais qui sert l'Angleterre. Il m'a proposé de piller un convoi néerlandais près des côtes d'une île inhabitée entre Curacao et Trinidad.";
			link.l1.go = "mtraxx_51";
		break;
		
		case "mtraxx_51":
            dialog.text = "Eh bien... As-tu accepté ?";
			link.l1 = "Je l'ai fait. D'abord, c'était une bonne affaire. Ensuite, je me suis souvenu de l'histoire de Picard et j'ai décidé d'enquêter...";
			link.l1.go = "mtraxx_52";
		break;
		
		case "mtraxx_52":
            dialog.text = "Je parie que tu l'as fait.";
			link.l1 = "Oui. Il y avait une caravane, nous avons fait le travail de manière propre et nette. Ensuite, nous avons partagé le butin à terre, mais d'abord j'ai discrètement envoyé un guetteur avec une longue-vue sur une colline. Et ça a payé, car une escadre espagnole est apparue peu après, menée par un lourd galion.";
			link.l1.go = "mtraxx_53";
		break;
		
		case "mtraxx_53":
            dialog.text = "Ton partenaire s'est sûrement enfui pour que les Espagnols te poursuivent ?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.LosadaSink")) 
			{
				link.l1 = "Exactement. Ils ne lui ont même pas prêté attention. Tant pis pour eux : nous avons combattu les Espagnols si férocement qu'ils ne l'oublieront jamais. Ces Castillans étaient de bons combattants, mais nous avons réussi à abattre toute l'escadre.";
				link.l1.go = "mtraxx_53x";
			}
			else
			{
				link.l1 = "Exactement. Ils ne lui ont même pas prêté attention. Bien que j'aie réussi à m'échapper. Grâce à mon guetteur...";
				link.l1.go = "mtraxx_53y";
			}
		break;
		
		case "mtraxx_53x":
			DeleteAttribute(pchar, "questTemp.Mtraxx.LosadaSink");
            dialog.text = "Heh ! Abattre un escadron d'Eduardo de Losad ! Tu es un Diable des Mers, Prince ! Je parie que les Espagnols ont déjà envoyé des chasseurs à tes trousses.";
			link.l1 = "Mauvais pour eux... Néanmoins, nous devrions nous occuper de cette racaille Ignacio. Si tu vois ce que je veux dire.";
			link.l1.go = "mtraxx_54";
		break;
		
		case "mtraxx_53y":
            dialog.text = "Hé ! J'imagine bien la tempête de merde qui a éclaté quand les Castillans ont réalisé que tu t'étais échappé ! Bien joué !";
			link.l1 = "Leur problème, pas le mien. Néanmoins, nous devrions nous occuper de cette racaille Ignacio. Si tu vois ce que je veux dire.";
			link.l1.go = "mtraxx_54";
		break;
		
		case "mtraxx_54":
            dialog.text = "Je m'en occuperai. Nous devrions en apprendre davantage sur cet Ignacio Marco. Il pourrait travailler pour quelqu'un. Son 'intérêt' pour mes hommes est suspect. Quel navire possède-t-il ?";
			link.l1 = "Un polacre, le 'Torero'. Un navire unique, ça doit être une conception originale.";
			link.l1.go = "mtraxx_55";
		break;
		
		case "mtraxx_55":
            dialog.text = "Bien, plus facile de la suivre alors... J'ai compris. Et pour toi, Prince, j'ai un boulot. Prêt pour ça ?";
			link.l1 = RandSwear()+"Par tous les moyens, chef !";
			link.l1.go = "mtraxx_56";
		break;
		
		case "mtraxx_56":
            dialog.text = "Ecoute donc. Il y a quelque temps, nous avions un pirate curieux dans notre région. Il s'appelle Wulfric Iogansen, également connu sous le nom de Loup Rouge. Un personnage très coloré. Il est venu ici du Nord de l'Europe il y a quelques années. Ce Viking ne payait pas à Levasseur sa taxe de protection, ne se faisait pas d'amis et restait seul. Un type très secret, personne n'avait jamais quitté son équipage vivant. Il y avait des rumeurs selon lesquelles il coupait personnellement la langue de ceux de son équipage dont la langue se déliait dans les tavernes à propos de leurs raids... Contrairement à la plupart de notre espèce, Wulfric ne gaspillait jamais d'argent en putains ou en boissons. Il ne vendait jamais son butin pour des clopinettes. Il ne faisait jamais confiance aux banquiers et ne changeait jamais de navire. Il avait une belle corvette, le 'Freyja', et un équipage loyal qu'il payait bien pour le servir et pour leur silence. Je crois qu'il prévoyait d'accumuler autant d'or que possible, puis de retourner en Europe et y vivre comme un roi. Ça n'a pas marché pour lui grâce aux chasseurs espagnols. Cet homme avait infligé des dommages et des pertes colossaux à l'Espagne, alors des expéditions punitives l'ont traqué dans les eaux d'Hispaniola et ont coulé le 'Freyja' et tué tout l'équipage avec le Loup. Encerclé dans les eaux peu profondes par les navires espagnols, le Loup Rouge a rencontré sa mort. Le truc, c'est que tout le monde à La Vega connaissait les trésors du Loup et avait même trouvé un 'Freyja' coulé, mais ni les plongeurs locaux ni indiens n'ont trouvé de trésors. Il n'était pas idiot et devait avoir une énorme cachette quelque part dans cet endroit que lui seul et son équipage connaissaient, mais nous ne pouvons pas leur demander pour... des raisons évidentes. Mais maintenant vient la partie intéressante : j'ai son journal de bord intact, qui était caché dans le coffre verrouillé de son navire. Il n'a pas de pistes évidentes vers le trésor, mais tu peux essayer de les trouver entre les mots. Lis le journal, découvre où le Viking a caché ses trésors après deux ans de pillage dans les Caraïbes et trouve-les. Si tu réussis, les deux tiers sont à toi. Tu es partant ?";
			link.l1 = "Hm... on dirait qu'on cherche un chat noir dans une pièce sombre. Où est le journal ?";
			link.l1.go = "mtraxx_57";
		break;
		
		case "mtraxx_57":
            dialog.text = "Tiens, prends-le. Bonne chance !";
			link.l1 = "Merci, je vais en avoir besoin...";
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
            dialog.text = "Ah, voici notre vaillant capitaine. Qu'en est-il des trésors du Loup Rouge ?";
			link.l1 = "Je m'en occupe. J'ai besoin de ton aide pour ça.";
			link.l1.go = "mtraxx_60";
		break;
		
		case "mtraxx_60":
            dialog.text = "Je suis tout ouïe.";
			link.l1 = "Il y a un mot inconnu pour moi écrit plusieurs fois dans le journal de Wulfric 'Gord'. Je dois connaître sa signification pour avancer dans mon enquête.";
			link.l1.go = "mtraxx_61";
		break;
		
		case "mtraxx_61":
            dialog.text = "Hm... Gord tu dis... Jamais entendu parler non plus. Très bien, reviens me voir dans une semaine : je vais consulter quelques gros cerveaux qui servent de commis sur les navires. Au moins, ils savent compter et lire. Ils pourraient nous donner une idée.";
			link.l1 = "D'accord, Marcus. On se voit dans une semaine alors.";
			link.l1.go = "mtraxx_62";
		break;
		
		case "mtraxx_62":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			SetFunctionTimerCondition("Mtraxx_WolfreekTimer", 0, 0, 7, false);
		break;
		
		case "mtraxx_63":
            dialog.text = "J'ai une réponse pour toi. Un petit malin m'a éclairé. Gord est une implantation fortifiée d'un jarl libre.";
			link.l1 = "Un jarl libre ? Qui est-ce ?";
			link.l1.go = "mtraxx_64";
		break;
		
		case "mtraxx_64":
            dialog.text = "Une sorte d'amiral pirate des Vikings. Par exemple, je suis un jarl libre et La Vega est mon gord. On dirait que le Loup Rouge appréciait l'histoire de ses ancêtres, ha-ha ! Cette information vous a-t-elle aidé ?";
			link.l1 = "Je ne sais pas encore. Je devrais d'abord comparer les notes. Gord signifie établissement alors... Merci Marcus !";
			link.l1.go = "mtraxx_65";
		break;
		
		case "mtraxx_65":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			Mtraxx_WolfreekReadLogbookFourth();
		break;
		
		case "mtraxx_66":
            dialog.text = "Alors ? Ta face arrogante me dit que tu as réussi.";
			link.l1 = "Ouais. Le trésor du Loup Rouge a été trouvé ! Mais ce n'était pas facile.";
			link.l1.go = "mtraxx_67";
		break;
		
		case "mtraxx_67":
            dialog.text = "Combien notre Viking a planqué ?";
			link.l1 = "750.000 pesos et 900 doublons.";
			link.l1.go = "mtraxx_68";
		break;
		
		case "mtraxx_68":
            dialog.text = "Ho-ho! Tu t'es bien débrouillé, Prince. Qu'en est-il de ma part?";
			if (sti(pchar.money) >= 250000 && PCharDublonsTotal() >= 300) // belamour legendary edition
			{
				link.l1 = "Tiens, prends ça. Selon notre accord : 250 000 pesos et 300 doublons.";
				link.l1.go = "mtraxx_69";
			}
			else
			{
				link.l1 = "Tous les pesos et doublons sont dans ma cabine. Donne-moi une minute pour les apporter ici !";
				link.l1.go = "mtraxx_68_1";
			}
		break;
		
		case "mtraxx_68_1":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_68_2";
		break;
		
		case "mtraxx_68_2":
            dialog.text = "As-tu apporté ma part ?";
			if (sti(pchar.money) >= 250000 && PCharDublonsTotal() >= 300) // belamour legendary edition
			{
				link.l1 = "Tiens, prends ça. Selon notre accord : 250 000 pesos et 300 doublons.";
				link.l1.go = "mtraxx_69";
			}
			else
			{
				link.l1 = "Oui-oui, je suis en chemin !";
				link.l1.go = "mtraxx_68_1";
			}
		break;
		
		case "mtraxx_69":
			AddMoneyToCharacter(pchar, -250000);
			RemoveDublonsFromPCharTotal(300); // belamour legendary edition
			PlaySound("interface\important_item.wav");
            dialog.text = "Très bien. Tu as encore fait un excellent travail. Bravo !";
			link.l1 = "Marcus, as-tu découvert quelque chose à propos d'Ignacio Marco?";
			link.l1.go = "mtraxx_70";
			// mitrokosta возможность отстройки исламоны
			pchar.questTemp.IslaMona = "start";
		break;
		
		case "mtraxx_70":
            dialog.text = "Oui mais je dois d'abord le verifier...";
			link.l1 = "Quoi?";
			link.l1.go = "mtraxx_71";
		break;
		
		case "mtraxx_71":
            dialog.text = "J'ai le pressentiment que Marco est relié à quelqu'un... Et j'ai besoin que tu le découvres. Navigue jusqu'à la Martinique. Laisse ton navire à Saint Pierre et rends-toi à Le Francois à travers la jungle. On m'a dit que notre homme a été vu là-bas. Ne pose pas de questions aux pirates, contente-toi d'observer. Une fois que tu l'auras trouvé, suis-le et vois où il va ou qui il rencontre. Ne l'attaque pas, ni son navire, car en faisant cela, tu gâcherais un plan que je prépare en ce moment ! Je t'ai prévenu !\nSuis-le et observe-le, reviens vers moi une fois que tu en sauras assez. Je comprends que tes mains ont envie d'étrangler ce salaud, mais garde ton esprit calme. Maintenant, va. Tu as trois semaines. Bonne chance.";
			link.l1 = "En route, patron.";
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
				dialog.text = "Bon sang, Prince ! Tu pourrais avoir ta revanche et une somme d'argent infernale si tu n'étais pas si lent ! Je ne m'attendais pas à cela de ta part, mais comme tu es un bon gamin, je te pardonne. Tu auras une chance de regagner ta réputation à mes yeux dans un mois. Je rassemble tout le monde pour un raid !\nViens me voir dans un mois sur un seul mais puissant navire. Luke, Cutlass, Geffrey et Jean participeront aussi. Ne sois pas en retard, même pas d'un jour !";
				link.l1 = "Je comprends Marcus. Ça n'arrivera plus !";
				link.l1.go = "mtraxx_73x";
				break;
			}*/
			dialog.text = "Bonne synchronisation ! Rapportez-vous à moi, maintenant.";
			link.l1 = "J'ai traqué mon débiteur à Le François. Sa polacre faisait partie d'une escadre comprenant une corvette et une frégate. Marco lui-même rendait visite à Barbaszon, ils ont eu une réunion chez lui pendant deux heures, les autres visiteurs ont été écartés par ses gardes. Puis il est sorti de la maison avec deux types lugubres : l'un était roux avec une barbe et portait une cuirasse de reître, l'autre avait une moustache et portait une lourde armure de tranchée. Tous sont allés au port et ont pris la mer avant que je n'atteigne Saint Pierre.";
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
            dialog.text = "C'est bien. Maintenant je vois le tableau complet. Ces deux salauds que tu as vus travaillent soit pour Barbazon, soit pour Jackman. Ils sont presque comme mes Chauve et Sabre mais ils se battent mieux. Le rouquin s'appelle Prowler, c'est un capitaine du 'Cuttlefish', une corvette, et le gars à la moustache est Ghoul, il navigue sur le 'Merciless', une frégate. Quant à notre ami Ignacio - il travaille non seulement pour les Anglais et le don espagnol Losad mais aussi pour Barbazon. C'est pourquoi il a essayé de te piéger, toi et Picard.";
			link.l1 = "Pourquoi ?";
			link.l1.go = "mtraxx_75";
		break;
		
		case "mtraxx_75":
            dialog.text = "L'ordre de Barbazon. Tu ne le savais pas, mais Jacques ne rate jamais une occasion de pisser dans mon gruau. Il ne s'opposerait jamais ouvertement à moi pour des raisons évidentes, alors il me croise en secret. Il savait que Picard et toi êtes mes hommes. Envoyer son mercenaire après toi était dans son style, et il n'a pas envoyé un idiot, comme tu t'en es assuré.";
			link.l1 = "Je rendrai visite à Barbazon dès que je m'occuperai de Marco...";
			link.l1.go = "mtraxx_76";
		break;
		
		case "mtraxx_76":
            dialog.text = "Sors-toi ces conneries de la tête ! Tu n'as aucune chance contre Barbazon en conflit ouvert. Il va te défoncer facilement. Nous allons lui rendre la monnaie de sa pièce avec ses propres ruses - en frappant ses associés. Prêt à faire ça ? C'est un sale boulot.";
			link.l1 = "Ça me semble être mon genre d'affaires !";
			link.l1.go = "mtraxx_77";
		break;
		
		case "mtraxx_77":
            dialog.text = "Ignacio Marco, Prowler, Goul et un autre gars de Barbazon appelé Joker Jim ont un plan pour capturer un des navires espagnols de la Flotte d'Or. Toute l'opération a été conçue par Barbazon lui-même et j'ai réussi à découvrir les détails grâce à mes espions. Un lourd galion de la flotte d'or s'est attardé à La Havane à l'arsenal, tandis que toute l'escadre est partie pour l'Espagne. Le Galion a été réparé et se dirigera bientôt vers l'Europe, accompagné de deux autres navires. L'escadre ira de Cuba vers le nord-est, mais je ne connais pas son itinéraire.\nJ'ai été informé que les navires espagnols prévoyaient de naviguer jusqu'à Saint-Domingue, puis le long des côtes de Porto Rico et directement dans l'océan. Barbazon le sait aussi. Cependant, comme Hispaniola peut être contournée non seulement par le sud, mais aussi par le nord, en changeant de route et en se dirigeant vers l'océan par Turks ou Isla-Tesoro, sans entrer dans Saint-Domingue, Jacques a décidé d'assurer le coup et a envoyé le renard rusé Ignacio à Cuba.\nMarco a pour tâche d'obtenir un calendrier de navigation du galion espagnol qui doit partir de Cuba et est censé rattraper le reste de la flotte plus tard. Il a des contacts parmi les Espagnols, donc cette tâche ne sera pas un problème pour lui. Le reste de la bande de Barbazon attend Marco à Saint-Martin, qui est une place optimale pour commencer à chasser ce prix. Puisque Marco et les Hollandais ne sont pas de très bons amis, il ne pourra pas entrer dans les eaux de Saint-Martin, donc il devra envoyer un message lointain à ses compagnons...";
			link.l1 = "Je suppose que je sais ce que je suis censé faire ici...";
			link.l1.go = "mtraxx_78";
		break;
		
		case "mtraxx_78":
            dialog.text = "Il me semble que tu es si malin, mais je n'ai pas encore fini. J'ai perturbé ce plan avec l'aide de Gabriela Chapada. Tu la connais. Ensemble, nous avons informé les Espagnols que l'embuscade pirate serait tendue non loin de Porto Rico. Ainsi le galion n'empruntera pas cette zone, mais ils ont secrètement envoyé une escadre de chasseurs de pirates à la place. Tu as plusieurs tâches. La première sera de trouver et capturer le 'Torero'. Je suppose que tu sais quoi faire de son capitaine.";
			link.l1 = "Naturellement...";
			link.l1.go = "mtraxx_79";
		break;
		
		case "mtraxx_79":
            dialog.text = "Deuxièmement, il vous faudra découvrir le véritable itinéraire du galion doré espagnol. Marco doit avoir son emploi du temps. Obtenez-le et envoyez-le-moi.";
			link.l1 = "Comment ?";
			link.l1.go = "mtraxx_80";
		break;
		
		case "mtraxx_80":
			GiveItem2Character(pchar, "Dove"); 
            dialog.text = "Par les airs. Prends une cage... Voici Spyke, un pigeon voyageur né et élevé ici, à La Vega. Il retrouvera toujours son chemin jusqu'ici, même depuis Trinidad. Une fois que tu auras obtenu le programme, écris une note, attache-la à sa patte et relâche-le. Spyke volera vers moi en quelques heures. Prends-en soin, Prince !";
			link.l1 = "Bien sûr, chef !";
			link.l1.go = "mtraxx_81";
		break;
		
		case "mtraxx_81":
            dialog.text = "Troisièmement, naviguez vers Saint-Martin sur le 'Torero'. Uniquement sur elle seule ! Autrement, ils deviendront soupçonneux trop tôt. Envoyez-leur un signal pour naviguer vers Porto Rico où les Espagnols les attendent. Leurs codes de signal doivent être dans les papiers de Marco. Ou vous pouvez les apprendre de lui en personne.";
			link.l1 = "Je vois. Un coup intelligent d'envoyer les hommes de Barbazon aux Espagnols, ha-ha !";
			link.l1.go = "mtraxx_82";
		break;
		
		case "mtraxx_82":
            dialog.text = "Exactement ! Je lui porterai un coup depuis les ombres. Comme il l'a fait. Et une dernière chose : une fois que vous leur envoyez un signal, partez immédiatement intercepter le galion espagnol et son escorte. Il n'y aura pas de temps à perdre.";
			link.l1 = "Sur une polacre ? Contre un lourd galion et deux autres navires, et certainement pas de goelettes ? Ils vont me déchiqueter !";
			link.l1.go = "mtraxx_83";
		break;
		
		case "mtraxx_83":
            dialog.text = "Arrête de pleurnicher comme une gamine ! Pourquoi penses-tu que tu m'enverras Spyke ? Tu ne seras pas laissé sans renforts. Ne laisse juste pas le convoi s'échapper, ne les laisse pas atteindre l'océan. Compris ?";
			link.l1 = "Oui, patron.";
			link.l1.go = "mtraxx_84";
		break;
		
		case "mtraxx_84":
            dialog.text = "Ta récompense sera une lourde cargaison d'or plus la polacre de Marco. On dit que c'est un sacré bon navire. Des questions ? Comprends-tu ta mission ?";
			link.l1 = "Je ne suis pas Cutlass, je sais quoi faire. Où dois-je intercepter le 'Torero' ?";
			link.l1.go = "mtraxx_85";
		break;
		
		case "mtraxx_85":
            dialog.text = "Pendant que nous bavardons, le navire navigue rapidement directement vers Philipsburg depuis Cuba. Il doit être près de Tortuga maintenant ou un peu à l'Est de celle-ci. Alors levez les ancres et mettez le cap sur Saint-Martin, attrapez le 'Torero' non loin de l'île, mais ne laissez pas les hommes de Barbazon voir le combat, sinon mon plan est fichu.";
			link.l1 = "Tout de suite !";
			// belamour legendary edition испанский флаг к выдаче -->
			if(IsCharacterPerkOn(pchar,"FlagSpa")) link.l1.go = "mtraxx_86";
			else link.l1.go = "mtraxx_85f";
		break;
		
		case "mtraxx_85f":
			SetCharacterPerk(pchar, "FlagSpa");
			log_info("You have received a spanish flag");
			pchar.questTemp.GiveMeSpaFlag = true;
            dialog.text = "Mais qu'est-ce que c'est que ce bordel ? Je te briserais avec un tisonnier de la cheminée, Prince. Je ne pensais pas devoir parler de choses aussi élémentaires. Tiens le drapeau espagnol, sinon tu vas tout foirer avant même de commencer. Rends-le-moi. Maintenant, dégage d'ici !";
			link.l1 = "Je suis déjà en mer, Patron";
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
            dialog.text = "Alors Prince, tu fous tout en l'air, hein ?";
			link.l1 = "Je l'ai fait. Cette mission était un défi bien plus grand que je ne le pensais. Tu peux me faire un discours enragé et me montrer la porte.";
			link.l1.go = "mtraxx_88";
		break;
		
		case "mtraxx_88": // belamour legendary edition увеличиваем срок
            dialog.text = "Allez, laisse tomber. Cela arrive. Tu es un bon corsaire et nous échouons tous parfois. Dommage que nous n'ayons pas obtenu cet or... mais si nous ne l'avons pas eu à un endroit, nous devrions l'avoir ailleurs, ha-ha ! Tu auras une chance de regagner ta réputation : viens me voir dans trois semaines, et de préférence sur un navire plus puissant, mais seulement sur un - nous serons toute une escadre. Je rassemble tout le monde pour un raid !\nRejoins-moi dans trois semaines sur un seul mais puissant navire. Luke, Cutlass, Geffrey et Jean y participeront aussi. Ne sois pas en retard !";
			link.l1 = "Je ne veux pas, patron !";
			link.l1.go = "mtraxx_89";
		break;
		
		case "mtraxx_89":
            DialogExit();
			// belamour legendary edition забрать флаг обратно
			if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
			{
				DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
				DeleteAttribute(pchar,"perks.list.FlagSpa"); 
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
            dialog.text = "Ho-ho, Ahoy, gamin ! Tu ne t'attendais pas à me voir ici, n'est-ce pas ? Ha-ha-ha ! Nous avons finalement trouvé la caravane espagnole...";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Gold")) // был абордаж
			{
				link.l1 = "Oui patron, nous l'avons fait, bien que ce ne fût pas facile.";
				link.l1.go = "mtraxx_board_1";
			}
			else
			{
				link.l1 = "Ouais, mais le galion doré a coulé avec tout son or.";
				link.l1.go = "mtraxx_board_7";
			}
		break;
		
		case "mtraxx_board_1":
			iTotalTemp = GetSquadronGoods(pchar, GOOD_GOLD);
            dialog.text = "Combien d'or avons-nous obtenu, Prince ?";
			if (iTotalTemp < 1) link.l1 = "Eh... Rien.";
			else link.l1 = "Heh... "+iTotalTemp+"au total !";
			link.l1.go = "mtraxx_board_2";
		break;
		
		case "mtraxx_board_2":
			if (iTotalTemp < 20)
			{
				dialog.text = "Merde! Les Espagnols ont dû le jeter à la mer pour qu'on ne l'obtienne pas. Au moins, ils ont payé pour ça. Tout comme les hommes de Barbazon, ce qui est aussi une victoire...";
				link.l1 = "Désolé pour l'or... Que faisons-nous ensuite, Marcus ? Allons-nous à La Vega ?";
				link.l1.go = "mtraxx_board_4";
				AddQuestRecord("Roger_8", "18");
				break;
			}
			if (iTotalTemp >= 20 && iTotalTemp < 300)
			{
				dialog.text = "Pathétique. Cela ne compense même pas ma tournée ici. Les Espagnols ont dû le jeter à la mer pour que nous ne l'ayons pas. Au moins, ils l'ont payé de leur vie. Tout comme les hommes de Barbazon, ce qui est aussi une victoire...";
				link.l1 = "Désolé pour l'or... Partageons-le quand même.";
				link.l1.go = "mtraxx_board_3";
				AddQuestRecord("Roger_8", "19");
				break;
			}
			if (iTotalTemp >= 300 && iTotalTemp < 700)
			{
				dialog.text = "C'est un pauvre butin. Juste assez pour couvrir les frais. Les Espagnols ont dû en jeter une partie à la mer pour que nous ne l'ayons pas. Au moins, ils l'ont payé. Ainsi que les hommes de Barbazon, ce qui est aussi une victoire...";
				link.l1 = "Désolé pour l'or... Partageons-le quand même.";
				link.l1.go = "mtraxx_board_3";
				AddQuestRecord("Roger_8", "19");
				AddCharacterExpToSkill(pchar, "Fortune", 100);
				break;
			}
			if (iTotalTemp >= 700 && iTotalTemp < 1000)
			{
				dialog.text = "Pas mal, bien que j'attendais mieux. Les Espagnols ont dû en jeter une partie à la mer pour que nous ne l'obtenions pas. Au moins, ils l'ont payé. Tout comme les hommes de Barbazon, ce qui est aussi une victoire...";
				link.l1 = "Partageons le butin !";
				link.l1.go = "mtraxx_board_3";
				AddQuestRecord("Roger_8", "20");
				AddCharacterExpToSkill(pchar, "Fortune", 200);
				break;
			}
			dialog.text = "Splendide ! Nous avons fait une bonne prise, mon ami ! Et les hommes de Barbazon ont eu ce qu'ils méritaient, ha-ha !";
			link.l1 = "Hé, c'est un tas d'or ! Partageons-le !";
			link.l1.go = "mtraxx_board_3";
			AddQuestRecord("Roger_8", "21");
			AddCharacterExpToSkill(pchar, "Fortune", 300);
		break;
		
		case "mtraxx_board_3":
			RemoveCharacterGoods(pchar, GOOD_GOLD, makeint(iTotalTemp/2));
			WaitDate("", 0, 0, 0, 3, 10);
			LAi_Fade("", "");
            dialog.text = "... comme nous le faisons toujours parmi les Frères - une part équitable pour chacun. Tu peux garder le 'Torero', elle est ton prix.";
			link.l1 = "Et maintenant Marcus ? Allons-nous à La Vega ?";
			link.l1.go = "mtraxx_board_4";
		break;
		
		case "mtraxx_board_4": // belamour legendary edition увеличиваем срок до 3х месяцев
            dialog.text = "Je serai certainement à La Vega, je t'attendrai là-bas pendant trois semaines. Viens quand tu seras prêt. De préférence sur un navire plus robuste, mais seulement sur un - nous serons toute une escadre. Je mets tous mes hommes en marche. Tu passeras sous mon commandement, Jean le Beau, Geoffrey le Chauve, Pelly le Tranchoir et Luke le Lutin aussi. Prépare-toi. Nous attendons une expédition sérieuse et un butin plutôt conséquent. Tu découvriras tous les détails plus tard.";
			link.l1 = "Bien, patron ! On se voit à La Vega dans trois semaines.";
			link.l1.go = "mtraxx_board_5";
		break;
		
		case "mtraxx_board_5":
            dialog.text = "Adieu, coupe-jarret ! Ha-ha !";
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
				DeleteAttribute(pchar,"perks.list.FlagSpa"); 
				log_info("You have given spanish flag");
			}
		break;
		
		case "mtraxx_board_6x":
            dialog.text = "Autre chose ?";
			link.l1 = "Non, je ne pense pas. Je vais déjà à mon navire.";
			link.l1.go = "mtraxx_board_6y";
		break;
		
		case "mtraxx_board_6y":
            DialogExit();
			npchar.DeckDialogNode = "mtraxx_board_6x";
		break;
		
		case "mtraxx_board_7":
            dialog.text = "Heh ! Et à qui la faute, Prince ? C'était la tienne ?";
			link.l1 = "Je suis désolé, patron, mais nous étions tous les deux assez bons... Tu as fait un excellent travail de tir aussi. Beau tir, d'ailleurs...";
			link.l1.go = "mtraxx_board_8";
		break;
		
		case "mtraxx_board_8":
            dialog.text = "Peu importe. La faute est partagée. Nous ne sommes pas les mains vides cependant - les hommes de Barbazon ont obtenu ce que nous avions pour eux, une victoire en soi...";
			link.l1 = "Désolé pour l'or... Quelle est la suite, Marcus ? Allons-nous à La Vega ?";
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
				dialog.text = "Prince, es-tu devenu sans cervelle ? Je t'ai dit de n'apporter qu'un seul navire ! Va te débarrasser du surplus et reviens dès que possible ! Maintenant !";
				link.l1 = "D'accord, d'accord !";
				link.l1.go = "mtraxx_90x";
				break;
			}
			if (RealShips[sti(pchar.Ship.Type)].Type.Merchant) // торговые
			{
				dialog.text = "Prince, as-tu décidé d'être mon second Sabre? Pourquoi m'as-tu amené un navire marchand? Je comptais sur toi! Va me chercher un vaisseau de guerre digne de ce nom! Maintenant!";
				link.l1 = "D'accord, d'accord !";
				link.l1.go = "mtraxx_90x";
				break;
			}
			if (sti(RealShips[sti(pchar.ship.type)].Class) > 3)
			{
				dialog.text = "Prince, tu m'as surpris. Je t'avais dit de ramener un navire de guerre ! Comment vas-tu m'aider sur cette coquille de noix ? Reviens ici sur un navire de troisième ou deuxième rang, pas moins et pas plus ! Maintenant ! Je n'attendrai personne.";
				link.l1 = "D'accord, d'accord !";
				link.l1.go = "mtraxx_90x";
				break;
			}
			if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
			{
				dialog.text = "Prince, pourquoi ne pas amener ici le Souverain des Mers? Quand je t'ai dit d'amener un navire de guerre, je ne voulais pas dire d'amener un putain de vaisseau de ligne! Reviens ici sur un vaisseau de troisième ou deuxième rang! Maintenant! Je n'attendrai personne.";
				link.l1 = "D'accord, d'accord !";
				link.l1.go = "mtraxx_90x";
				break;
			}
            dialog.text = "Bonne synchronisation, corsaire ! Content de te voir entier ! Prêt pour une traversée ?";
			link.l1 = "Bien sûr, chef. Toujours prêt.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Barbazon")) link.l1.go = "mtraxx_91";
			else link.l1.go = "mtraxx_94";
		break;
		
		case "mtraxx_91":
            dialog.text = "Au fait, veux-tu savoir quelque chose sur l'escadron de Barbazon que tu as envoyé à Porto-Rico ?";
			link.l1 = "Ils ont complètement échappé à ma mémoire. Bien sûr que je veux. Ont-ils trouvé leur perte?";
			link.l1.go = "mtraxx_92";
		break;
		
		case "mtraxx_92":
            dialog.text = "Hell oui, ils l'ont fait ! Le navire amiral - la frégate de Joker Jim 'Hibou', a été réduit en cendres. Joker Jim lui-même a disparu sans laisser de trace. Le Clochard et le Goule ont pris une sacrée raclée, mais ils ont réussi à s'échapper : le Clochard - à Tortuga, sous la protection des canons de La Rocha, le Goule - à Isla Tesoro. Pasquale m'a dit que le Goule a aussi échoué son navire sur les récifs près de Sharptown et s'en est à peine sorti. Maître Alexus a beaucoup de travail maintenant, hehe. En général, les Espagnols m'ont un peu déçu. Je pensais qu'ils tueraient tout le monde.";
			link.l1 = "Heh. Peu importe, on a quand même pissé dans les bottes de Barbazon. On lui a passé un message.";
			link.l1.go = "mtraxx_93";
		break;
		
		case "mtraxx_93":
            dialog.text = "Vrai. Parlons affaires.";
			link.l1 = "Je suis tout ouïe.";
			link.l1.go = "mtraxx_94";
		break;
		
		case "mtraxx_94":
            dialog.text = "Mon service de renseignement, sous la forme de mon bon ami Bernard Vensan, a rapporté une énorme pile de lingots d'or que les Espagnols ont stockée à Carthagène. Sous son fort, pour être plus précis. Normalement, cela aurait été attribué à la Flotte d'Or de l'Espagne, mais cette fois-ci, c'est à nous de la prendre. Nous nous dirigeons vers le Continent Sud pour prendre d'assaut Carthagène.";
			link.l1 = "Argh ! Ai-je bien entendu ? Allons-nous piller toute une colonie, avec un putain de fort ?";
			link.l1.go = "mtraxx_95";
			// belamour legendary edition отказ от великого похода
			link.l2 = "Je ne vais pas à Carthagène avec toi, Marcus. Mettre le feu à toute une ville, ce n'est pas mon histoire.";
			link.l2.go = "mtraxx_94a";
		break;
		
		case "mtraxx_95":
            dialog.text = "Tu as bien entendu. C'est exactement ce que nous allons faire. Mon navire de guerre s'occupera du fort, avec ton aide bien sûr. Le hardi Jeffrey transportera les troupes au sol sur son nouvel East-indien volé aux Hollandais. Pelly s'est enfin débarrassé de sa brigantine délabrée et a obtenu une corvette décente, non sans mon aide financière bien sûr. Paul Chant et toi êtes responsables de neutraliser la flotte de patrouille, et vos équipages participeront aussi à l'assaut, et toi, Charles, si bon combattant et capitaine, tu m'aideras à détruire le fort.\nJean Picard ne s'est pas montré, ce qui est étrange puisque sa corvette a été vue à Port Royal. Eh bien, s'il n'est pas intéressé par l'or espagnol, c'est son problème, alors qu'il aille au diable. À sa place, mon ami Bernard Vensan se joindra au raid. De plus, Leprechaun avec ses boucaniers assistera nos troupes. Nous prendrons l'or du fort et la rançon de la ville. Ils ne l'oublieront pas, ha-ha !\n Maintenant, va te reposer. Et viens me rejoindre ainsi que les autres capitaines à la taverne ce soir ! Nous devrions boire à notre cause ! Je demanderai au barman de chasser tous les alcooliques locaux, ainsi nous serons seulement six et quelques charmantes demoiselles dans la taverne. Tu bois avec tes camarades ce soir, et demain matin tu conduiras l'escadron, tu traceras le parcours. Et essaie de nous amener à Carthagène aussi vite que possible. Tout est clair ?";
			link.l1 = "Oui, oui, chef !";
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
            dialog.text = "Toi... toi... Prince fou ! Tu me tends un piège ?! Tu sais quoi, au diable avec toi ! Tu avais la chance d'entrer dans la Fraternité, tu avais la chance de t'échapper des rangs de tout ce bétail inutile. Et tu as lâchement raté cette chance. Dégage avec tes jérémiades ! Faiblard ! Encore une fois tu verras - je lâcherai les chiens !";
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
            dialog.text = "Prince, enfin ! Regardez, les gars - nous lui avons préparé un cadeau, et il se balade je ne sais où ! Asseyez-vous, nous commençons !\nAlors, braves corsaires ! L'or de Carthagène nous attend, ha-ha ! Et nous allons l'obtenir, je le jure par le tonnerre ! Mais ceux qui travaillent bien doivent aussi bien se reposer ! C'est pourquoi aujourd'hui nous passerons un moment merveilleux dans cet établissement magnifique. Servez-vous un peu de rhum, plus il y en a, mieux c'est ! Remplissez vos mugs jusqu'au bord ! Au vent du trésor, au vent de la chance ! Nous buvons jusqu'à la dernière goutte !\nPour vous, la meilleure boisson des caves de notre taverne, et les plus belles dames de l'île, ha-ha-ha !\nEt pour toi, Charles, de notre part - un splendide chapeau. Essaie-le et ne discute pas !\nCorsaires, chantez notre chanson ! Notre préférée !..";
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
            dialog.text = "Il est temps de leur montrer qui nous sommes, corsaires. Leprechaun ! Prends tes hommes et prends le contrôle des portes de la ville. Nous ne voulons pas qu'ils envoient des renforts au fort ! Frappez-les durement dans le dos quand nous foncerons à travers les soldats du fort !";
			link.l1 = "";
			link.l1.go = "mtraxx_100";
		break;
		
		case "mtraxx_100":
            dialog.text = "Prince et Paul ! Vous avez vu l'escadron militaire avec trois navires, débarrassez-vous d'eux. Éloignez-vous du fort et ne montez pas à bord de leurs vaisseaux. Nous n'avons ni le temps, ni la position pour nous occuper des prises. Tout est clair ?! Prince, je parle surtout pour toi, je sais à quel point tu aimes le héroïsme, tu auras l'occasion pour ça plus tard !\nNe vous approchez pas trop du fort, débarrassez-vous de ces navires, et revenez ! Nous vous attendrons ici. Tout est clair ? Parfait, ha-ha-ha-ha ! À l'abordage !";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CartahenaSquadronAttack");
		break;
		
		case "mtraxx_101":
            dialog.text = "Alors, l'escadre espagnole a disparu pour de bon. Il est maintenant temps pour le 'Dragon Rouge' de jouer son rôle. Nous allons transformer le fort de Carthagène en un tas de décombres. Es-tu avec moi ?";
			link.l1 = "Bien sûr !";
			link.l1.go = "mtraxx_102";
		break;
		
		case "mtraxx_102":
            dialog.text = "Le 'Dragon Rouge' est un navire très robuste avec une artillerie puissante, le tien ne lui arrive pas à la cheville. Alors fais attention, ne joue pas au héros et reste loin de mes canons !";
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
            dialog.text = RandSwear()+"Enfer de combat ! C'est ça, mes courageux corsaires ! Carthagène est à nous ! La résistance est tombée ! Audacieux, Leprechaun ! Viens avec moi au fort - Bernie a dû déjà trouver l'or. Prince, prends Cutlass et négocie avec le gouverneur pour qu'il nous paie une rançon de 250 000 pesos ! Ils ont l'argent, alors sois persistant. Je sais que tu peux.";
			link.l1 = "Héhé ! Avec plaisir, patron !";
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
            dialog.text = "Comment ça va, Prince ?";
			link.l1 = "Tout est splendide. J'ai forcé les plus riches de Carthagène à payer 350.000 pesos.";
			link.l1.go = "mtraxx_107";
		break;
		
		case "mtraxx_107":
            if (sti(Pchar.money) < 350000)
			{
				dialog.text = "Ho-ho, c'est mon gars ! Mais où est l'argent ?";
				link.l1 = RandSwear()+"Je l'apporterai dans un instant !";
				link.l1.go = "mtraxx_107x";
			}
			else
			{
				dialog.text = "Ho-ho, c'est mon gars ! Toi et le Cutlass pouvez garder 50 000 chacun comme bonus pour la rapidité et l'ingéniosité. Le reste sera partagé entre nous plus tard.";
				link.l1 = "Voilà pour toi !";
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
				dialog.text = "Alors ? Arrête de jouer et apporte les pièces ici !";
				link.l1 = "En route !";
				link.l1.go = "mtraxx_107x";
			}
			else
			{
				dialog.text = "Superbe! Toi et le Cutlass pouvez garder 50 000 chacun comme prime pour la rapidité et la débrouillardise. Le reste sera partagé entre nous tous plus tard.";
				link.l1 = "Voilà pour toi !";
				link.l1.go = "mtraxx_109";
			}
		break;
		
		case "mtraxx_109":
			AddMoneyToCharacter(pchar, -300000);
            dialog.text = "Tu dois t'inquiéter pour notre or? Il est trouvé - 5 000 unités et il est déjà en cours de transport vers nos navires. Le partage a déjà été fait, les hommes sont d'accord, nous espérons que Cutlass et toi n'y trouverez rien à redire non plus.";
			link.l1 = "Quel est ma part ?";
			link.l1.go = "mtraxx_110";
		break;
		
		case "mtraxx_110":
            dialog.text = "Puisque toute l'opération a été planifiée par moi, et que le 'Dragon Rouge' a fait le travail le plus difficile en s'occupant du fort, moi et mes hommes recevrons la moitié du butin. L'autre moitié sera partagée entre les capitaines des quatre autres navires selon le nombre de leurs équipages. Vous avez "+GetCrewQuantity(pchar)+" hommes à disposition, votre part est "+sti(pchar.questTemp.Mtraxx.Cartahena.Gold)+" unités d'or et "+sti(pchar.questTemp.Mtraxx.Cartahena.Money)+" pesos.";
			link.l1 = "Eh bien, puisque tout le monde est d'accord avec cela, alors moi aussi !";
			link.l1.go = "mtraxx_111";
		break;
		
		case "mtraxx_111":
            dialog.text = "Splendide. Félicitations pour ce voyage réussi, corsaires ! Plus rien à faire ici, il est temps de rentrer à la maison. Nous avons tous, y compris moi-même, un mois de congé. Mais pas toi, Prince, j'ai une autre tâche pour toi. Vois-tu, Janette, une Madame du bordel de Tortuga, a eu une plainte à ton sujet : elle dit que Charlie Prince ne prête pas beaucoup d'attention et d'amour à son établissement. Par conséquent, je t'ordonne de naviguer vers Tortuga, d'aller chez Janette et de gaspiller tes primes là-bas. Tu l'as mérité. Rends la Madame et ses filles heureuses. Je ne veux pas te voir avant que tu ne te sois reposé à Tortuga, ha-ha-ha !";
			link.l1 = "Compris, patron. C'est la mission la plus agréable que j'aie jamais reçue. Ce sera fait !";
			link.l1.go = "mtraxx_112";
		break;
		
		case "mtraxx_112":
            dialog.text = "Adieu, messieurs ! Montez sur vos navires et hissez les voiles ! À La Vega, tous !";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CartahenaFinal");
		break;
		
		// Addon 2016-1 Jason пиратская линейка патч 17/1
		case "mtraxx_113":
            dialog.text = "Quoi ?! Jean est maintenant une pute des Anglais, Bold et Cutlass ont disparu, Leprechaun et ses hommes sont introuvables ! Et maintenant toi ?!";
			link.l1 = "Marcus, j'ai pris ma décision. J'ai gagné une belle somme, tu t'es fait une petite fortune sur moi aussi. Mais j'en ai fini. Je m'en vais.";
			link.l1.go = "mtraxx_114";
		break;
		
		case "mtraxx_114":
            dialog.text = "Toi, tout comme Picard, tu penses que tu peux mieux gagner ta vie tout seul ? Ouais ? Tu penses que tu peux te débrouiller sans moi ? Ha-ha-ha ! Dégage d'ici Prince, je ne te retiens pas. Bientôt, très bientôt tu verras à quel point tu avais tort et alors tu reviendras me supplier de reprendre ton misérable derrière. Et tu sais quoi ? Je ne le ferai pas ! Ha-ha ! Dégage de ma vue !";
			link.l1 = "...";
			link.l1.go = "mtraxx_115";
		break;
		
		case "mtraxx_115":
            DialogExit();
		    npchar.quest.mtraxx_complete = "true";
		break;
		
		// Jason НСО
		case "patria":
			dialog.text = "Ho-ho ! Tu es tombé au bon endroit ! Crache le morceau !";
			link.l1 = "Il y a un gaillard qui n'a pas peur des pirates. Il ne les prend pas au sérieux. Il a besoin d'une bonne leçon de respect. Souviens-toi, ne le tue pas.";
			link.l1.go = "patria_1";
		break;
		
		case "patria_1":
			dialog.text = "Ah! C'est personne d'autre que le vieux Charles! Je parie que tu t'es encore fourré dans une affaire! Allons aux détails, qui est la cible cette fois et que devons-nous lui apprendre?";
			link.l1 = "Un invité d'Europe, un inspecteur du ministère français des Finances - le baron Noel Forget. Il veut établir ici une Compagnie Française de Commerce, mais moi et un ami proche nous y opposons. Nous avons tenté de convaincre le Baron que le commerce ici serait très risqué à cause des Hollandais, des Anglais et surtout des pirates depuis que Levasseur a été vaincu, mais il n'a pas écouté. Nous devons lui inspirer la peur, pour qu'il le ressente dans sa propre chair.";
			link.l1.go = "patria_2";
		break;
		
		case "patria_x":
			dialog.text = "Ho-ho ! Tu es venu au bon endroit ! Crache le morceau !";
			link.l1 = "Il y a un gars qui n'a pas peur des pirates. Il ne les prend pas au sérieux. Il a besoin qu'on lui donne une leçon de respect. N'oublie pas, ne le tue pas.";
			link.l1.go = "patria_x1";
		break;
		
		case "patria_x1":
			dialog.text = "Hé ! Pourquoi as-tu décidé de te mêler des pirates tout à coup ? Très bien, ça m'est égal tant que tu me paies. Passons aux détails, qui est la cible cette fois-ci et qu'est-ce qu'on doit lui apprendre ?";
			link.l1 = "Un invité d'Europe, un inspecteur du ministère français des Finances - le baron Noel Forget. Il veut établir ici une Compagnie Française des Indes, mais moi et un de mes proches amis nous y opposons. Nous avons essayé de convaincre le Baron que le commerce ici serait très risqué à cause des Hollandais, des Anglais et surtout des pirates après la défaite de Levasseur, mais il n'a pas écouté. Nous devons l'effrayer, lui faire sentir le danger dans sa propre peau.";
			link.l1.go = "patria_2";
		break;
		
		case "patria_2":
			dialog.text = "Oui-oui... Un véritable baron ! Devons-nous attaquer son navire ?";
			link.l1 = "Voici le plan : son navire partira bientôt de Port-au-Prince vers Capsterville. Vous devez intercepter le Baron près de Saint-Kitts et le prendre en otage. Il vaudrait mieux que vous ne couliez pas le navire et évitiez de tuer des hommes. Les Français sont nos amis, après tout. Serez-vous capable de gérer cela ?";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			dialog.text = "Eh bien, je ne peux rien promettre. Mais je vais essayer. Quel est le navire?";
			link.l1 = "Une brigantine appelée 'Favory'.";
			link.l1.go = "patria_4";
		break;
		
		case "patria_4":
			dialog.text = "Un brick ne fait pas le poids face à mon 'Dragon rouge'. Nous les gérerons facilement. S'ils se rendent, je laisserai tout le monde en vie.";
			link.l1 = "Parfait. Inspirez la terreur et proposez-leur de se rendre. Ensuite, envoyez le baron dans la cale infestée de rats. Essayez de trouver l'endroit le plus sale possible, mais ne le gardez pas là plus d'un jour, sinon il pourrait tomber malade et mourir. Ensuite, installez-le dans la cabine, trouvez un endroit isolé pour l'enfermer. Habillez certains de vos hommes comme des marchands français capturés et faites-les agir comme tels. Pendant trois jours d'affilée, ils devraient lui raconter comment les pirates impitoyables les poursuivent, les volent, exigent des rançons, les torturent... avec tous les détails requis.";
			link.l1.go = "patria_5";
		break;
		
		case "patria_5":
			dialog.text = "Ha-ha-ha ! Cela doit être le travail le plus drôle que j'ai jamais pris depuis très longtemps ! Eh bien, je trouverai de tels acteurs, garçon. N'aie aucun doute, après leurs histoires, ton Baron se chiera dessus ! Ils lui montreront des cicatrices de sabres et de baguettes chauffées...";
			link.l1 = "Parfait ! Alors vous le forcerez à écrire une lettre à de Poincy, demandant une rançon. Trois millions cinq cent mille pour un tel gros bonnet, ce n'est pas tant que ça.";
			link.l1.go = "patria_6";
		break;
		
		case "patria_6":
			dialog.text = "Bien. Que ferons-nous ensuite ?";
			link.l1 = "Et puis tu amèneras le Baron à Turks. Là, tu prendras la rançon, et tu me donneras le Baron. Et en plus, tu devrais lui dire que tous les Français paieront pour Tortuga et Levasseur, et pas qu'une seule fois.";
			if (CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax")) link.l1.go = "patria_x7";
			else link.l1.go = "patria_7";
		break;
		
		case "patria_7":
			dialog.text = "Ha-ha-ha ! C'est un sacré tour de force ! Nous, personnellement, eh bien, tu sais ce que nous avons fait à Levasseur, et maintenant... ha-ha-ha !... Bien, garçon. Ce sera fait ! Alors tu dis que le navire arrivera bientôt ?";
			link.l1 = "Bientôt. Nous devons rester à l'affût.";
			link.l1.go = "patria_8";
		break;
		
		case "patria_x7":
			dialog.text = "Ha-ha-ha ! C'est un sacré tour ! Combien dois-je te faire payer pour cette farce ? Bien, cent mille scelleront l'affaire. Donne-moi l'argent.";
			if (sti(pchar.money) >= 100000) 
			{
				link.l1 = "Prends-le.";
				link.l1.go = "patria_x8";
			}
			else
			{
				link.l1 = "D'accord, je l'apporterai.";
				link.l1.go = "patria_xwait";
			}
		break;
		
		case "patria_xwait":
			DialogExit();
			pchar.questTemp.Patria.Condotier.NeedMoney = "true";
		break;
		
		case "patria_x8":
			AddMoneyToCharacter(pchar, -100000);
			dialog.text = "Parfait ! Tu dis que le navire arrivera bientôt ?";
			link.l1 = "Bientôt. Nous devons rester sur nos gardes.";
			link.l1.go = "patria_8";
		break;
		
		case "patria_8":
			dialog.text = "Ne t'inquiète pas, je ne te laisserai pas tomber. Je m'occuperai de ça personnellement. Quand tu entendras une rumeur que le Baron a été capturé, viens me voir.";
			link.l1 = "Bien. Mes remerciements, Marcus.";
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
			dialog.text = "Bien sûr, mon garçon. Comme convenu. Des contes effrayants sur des pirates maléfiques, massacrant d'innocents marchands français, les sons d'un fouet, des gémissements et des cris. Un brasier avec du charbon et des menottes brûlées. Comme il se doit.";
			link.l1 = "Whoa whoa ! Doucement ! J'ai besoin de lui vivant";
			link.l1.go = "patria_11";
		break;
		
		case "patria_11":
			dialog.text = "Ne t'inquiète pas, il vivra. Il a écrit cette lettre d'une main tremblante. La voici.";
			link.l1 = "Qu'est-ce qui est écrit là ? Il supplie Poincy de le sortir de là ?";
			link.l1.go = "patria_12";
		break;
		
		case "patria_12":
			dialog.text = "C'est vrai, garçon ! Il supplie, ha !";
			link.l1 = "Jette cette lettre, ou mieux - brûle-la. Nous nous retrouverons aux Turks dans une semaine. Il faut que ça ait l'air comme si nous avions besoin de temps pour rassembler la rançon.";
			link.l1.go = "patria_13";
		break;
		
		case "patria_13":
			dialog.text = "Compris. Dans une semaine, dans le golfe du Nord, aux Turks. N'oublie pas d'apporter l'argent : ça doit avoir l'air joli. Après tout ça, viens me voir, on en discutera.";
			link.l1 = "Bien sûr, à plus tard, Marcus !";
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
			dialog.text = "Hé, mangeur de grenouilles ! Halte !";
			link.l1 = "Je ne bouge pas.";
			link.l1.go = "patria_16";
		break;
		
		case "patria_16":
			dialog.text = "Voici votre Baron. Un peu usé, hein, mais en un seul morceau. Il est toujours reconnaissable ? Ha-ha-ha !";
			link.l1 = "Oui... quelque peu.";
			link.l1.go = "patria_17";
		break;
		
		case "patria_17":
			dialog.text = "Parfait. Maintenant, file le fric ou c'en est fini de lui ! Et ne t'avise pas de nous rouler, on t'a dans notre ligne de mire !";
			if (sti(pchar.money) >= 350000)
			{
				link.l1 = "Tiens, prends-le.";
				link.l1.go = "patria_18";
			}
			else
			{
				link.l1 = "Merde ! Je l'ai oublié sur le navire...";
				link.l1.go = "patria_22";
			}
		break;
		
		case "patria_18":
			AddMoneyToCharacter(pchar, -350000);
			dialog.text = "Ha-ha-ha ! T'es un gamin malin, frenchie. Prends ton 'éminence'. Et dis à Poincy qu'il devrait préparer l'argent : il faudra payer pour ce que t'as fait à Levasseur et à Tortuga. Et tes marchandeurs nous paieront avec leurs marchandises et leurs navires. Ha-ha-ha ! N'oublie pas de nous ramener d'autres barons dans l'archipel, ils nous rapportent beaucoup de profit ! Ha-ha-ha !";
			link.l1 = "S'il vous plaît, allez à mon navire, Baron.";
			link.l1.go = "patria_19";
		break;
		
		case "patria_19":
			sld = CharacterFromID("Noel");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
			dialog.text = "Et n'essaie même pas de nous poursuivre, capitaine. Tu sais qui je suis. Je tiens plus de mangeurs de grenouilles en captivité, et si je ne rentre pas à temps, ils seront tous exécutés. Compris ?";
			link.l1 = "Le temps viendra et nous nous occuperons de vous, maudits blasphémateurs !";
			link.l1.go = "patria_20";
		break;
		
		case "patria_20":
			dialog.text = "Ha-ha-ha-ha ! Bien sûr que tu le feras !";
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
			dialog.text = "Tu te fous de moi ?! C'est une sorte de ruse ?!";
			link.l1 = "Une minute, je l'apporte...";
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
			link.l1 = "Argh, Marcus, qu'a fait ton imbécile !";
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax")) link.l1.go = "patria_25";
			else link.l1.go = "patria_x25";
		break;
		
		case "patria_25":
			dialog.text = "Charles, qu'est-ce que tu faisais ? Où est l'argent ? Je n'ai pas dit à mes gars que ce n'était pas vrai... et donc cet idiot a décidé que tu voulais nous rouler...";
			link.l1 = "C'est un désastre ! Le Baron est mort... Que fera de Poincy maintenant ?";
			link.l1.go = "patria_26";
		break;
		
		case "patria_x25":
			dialog.text = "Charles, qu'est-ce que tu faisais ? Où est l'argent ? Je n'ai pas dit à mes gars que ce n'était pas réel... et donc cet idiot a décidé que tu voulais les tromper...";
			link.l1 = "C'est un désastre ! Le Baron est mort... Que fera de Poincy maintenant ?";
			link.l1.go = "patria_x26";
		break;
		
		case "patria_x26":
			dialog.text = "Eh bien, mon gars, c'est ta faute, j'espère que tu comprends ça. Peut-être que c'est pour le mieux, un homme mort ne peut causer aucun tort.";
			link.l1 = "Quel idiot je suis ! J'ai tout gâché. Bon, je vais aller à Poincy... Pardonne-moi d'être un imbécile, Marcus, à bientôt.";
			link.l1.go = "patria_28";
		break;
		
		case "patria_26":
			dialog.text = "Eh bien, garçon, c'est ta faute, j'espère que tu comprends cela. Peut-être que c'est pour le mieux.";
			link.l1 = "Quel idiot je suis ! Tout gâché. Très bien, j'irai à Poincy... Pardonne-moi d'être un imbécile, Marcus, à bientôt.";
			link.l1.go = "patria_27";
		break;
		
		case "patria_27":
			dialog.text = "Tu as besoin de te reposer, tu perds la main. Viens me voir de temps en temps, je te trouverai du rhum et des belles donzelles.";
			link.l1 = "Merci, je te rendrai visite quand je pourrai.";
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
			dialog.text = "De rien, garçon. Pour moi, c'était le plus grand plaisir de l'année ! On a tellement ri, moi et mes gars ! Donc je tiens à te remercier pour ça. Voici ton argent.";
			link.l1 = "Tu devrais en garder une partie pour ta prestation.";
			link.l1.go = "patria_30";
		break;
		
		case "patria_x29":
			AddMoneyToCharacter(pchar, 350000);
			dialog.text = "Prends ton argent, 'comploteur'. Ha-ha ! C'était amusant.";
			link.l1 = "Merci pour ton aide, Marcus. Bonne chance !";
			link.l1.go = "patria_32";
		break;
		
		case "patria_30":
			AddMoneyToCharacter(pchar, 350000);
			dialog.text = "Laisse tomber. J'ai fait ça pour notre amitié. Les Frères de la Côte te doivent bien plus, mais tu n'as même pas demandé un seul doublon.";
			link.l1 = "Prenez tout de même au moins cinquante mille pour les services et la compensation. Merci, Marcus !";
			link.l1.go = "patria_31";
		break;
		
		case "patria_31":
			AddMoneyToCharacter(pchar, -50000);
			dialog.text = "De rien. Charles, passe me voir quand tu as un peu de temps !";
			link.l1 = "Avec plaisir !";
			link.l1.go = "patria_32";
		break;
		
		case "patria_32":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Patria.DodsonAgain");
		break;
		
		case "patria_33":
			dialog.text = "Tu es en retard d'une semaine ! Je n'ai pas dit à mes gars que ce n'était pas vrai... Ils ont refusé d'attendre plus longtemps et ont décidé de mettre fin à ton Baron !";
			link.l1 = "Quel idiot je suis ! Tout a foiré ! Qu'est-ce que je vais dire à Poincy ?";
			link.l1.go = "patria_34";
		break;
		
		case "patria_x33":
			dialog.text = "Tu es en retard d'une semaine ! Je n'ai pas dit à mes gars que ce n'était pas vrai... Ils ont refusé d'attendre plus longtemps et ont décidé de mettre fin à ton Baron !";
			link.l1 = "Quel idiot je suis ! J'ai tout gâché ! Que vais-je dire à Poincy ?";
			link.l1.go = "patria_x34";
		break;
		
		case "patria_34":
			dialog.text = "Eh bien, garçon, c'est ta faute, j'espère que tu comprends cela. Peut-être que cela te sera plus profitable.";
			link.l1 = "Très bien, j'irai à Poincy... Pardonne-moi d'être un imbécile, Marcus, à bientôt...";
			link.l1.go = "patria_35";
		break;
		
		case "patria_x34":
			dialog.text = "Tu t'es mis dans ce pétrin, c'est ta faute.";
			link.l1 = "À plus tard, je suppose...";
			link.l1.go = "patria_36";
		break;
		
		case "patria_35":
			dialog.text = "Tu dois te reposer, tu perds la main. Viens me voir de temps en temps, je te trouverai du rhum et des belles donzelles.";
			link.l1 = "Merci, je te rendrai visite quand je pourrai.";
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
				dialog.text = "Ça fait un bail, Prince.";
				link.l1 = "Je ne suis pas sûr que ce nom m'ait apporté autre chose que de la malchance, Marcus.";
				link.l1.go = "PZ_Prince1";
			}
			else
			{
				dialog.text = "De Maure ! Qu'est-ce qui t'amène ici ?";
				link.l1 = "Ahoy, Marcus. Je voulais te demander quelque chose.";
				link.l1.go = "PZ_DeMaure1";
			}
		break;
		
		case "PZ_Prince1":
			dialog.text = "Je vois que c'est le contraire. Qu'est-ce qui t'amène ici ?";
			link.l1 = "As-tu entendu parler du nouveau bordel à Tortuga ?";
			link.l1.go = "PZ_2";
		break;
		
		case "PZ_DeMaure1":
			dialog.text = "Alors, n'hésite pas, demande. Tu sais que je n'aime pas les formalités, donc allons droit au but.";
			link.l1 = "As-tu entendu parler du nouveau bordel à Tortuga ?";
			link.l1.go = "PZ_2";
		break;
		
		case "PZ_2":
			dialog.text = "Es-tu ivre? Quelle sorte de question est-ce là? Ne perds pas mon temps si c'est vraiment de cela que tu voulais parler.";
			link.l1 = "Je suppose que tu n'as pas entendu ? Un nouveau bordel a récemment ouvert là-bas - un très cher, où travaillent seulement les filles les plus belles, en bonne santé et bien habillées.";
			link.l1.go = "PZ_3";
		break;
		
		case "PZ_3":
			dialog.text = "Oh, ça ! Bien sûr que j'ai entendu - qui ne l'a pas ?";
			link.l1 = "Eh bien, je l'ai appris seulement l'autre jour.";
			link.l1.go = "PZ_4";
		break;
		
		case "PZ_4":
			dialog.text = "Ha-ha-ha-ha, vaurien, je serai damné ! Mais quand même, pourquoi tu en parles avec moi ? Pourquoi ne pas essayer Hawks d'abord ? Hi hi. Bien que... as-tu déjà eu un peu de plaisir là-bas ?";
			if (CheckAttribute(pchar, "questTemp.PZ.EliteWhoreFucked"))
			{
				link.l1 = "J'en ai. Ils n'acceptent que des doublons, au fait.";
				link.l1.go = "PZ_Fucked1";
			}
			else
			{
				link.l1 = "J'ai visité l'endroit, mais je n'ai pas profité des services. Cependant...";
				link.l1.go = "PZ_NoFucked1";
			}
		break;
		
		case "PZ_Fucked1":
			dialog.text = "Alors, tu viens frimer ! Ha, quel vaurien.";
			link.l1 = "En fait, non. Je voulais vraiment te demander quelque chose, Marcus.";
			link.l1.go = "PZ_5";
		break;
		
		case "PZ_NoFucked1":
			dialog.text = "Tu ne l'as pas fait ?! T'es un idiot, De Maure. Si j'étais toi...";
			link.l1 = "Tu aurais commencé une vraie débauche, je le sais. Mais ce n'est pas exactement ce dont je voulais discuter avec toi.";
			link.l1.go = "PZ_5";
		break;
		
		case "PZ_5":
			dialog.text = "Qu'est-ce que c'est ? Allez, ne me laisse pas dans l'attente.";
			link.l1 = "Je cherche la propriétaire de cet endroit. On m'a dit qu'elle voulait te rencontrer et te proposer une opportunité d'investissement dans son commerce. Tu ne peux pas te tromper - elle est chinoise.";
			link.l1.go = "PZ_6";
		break;
		
		case "PZ_6":
			dialog.text = "Ho ho. Non, je n'ai pas eu le plaisir de rencontrer des femmes chinoises récemment. Mais je ne serais pas contre la rencontrer et investir dans son affaire. Après tout, tu ne peux pas simplement te promener sur le territoire de Levasseur, et en tant que sujet de ton roi, il serait forcé de tirer ses navires côtiers sur mon 'Dragon' dès qu'il la repère.";
			link.l1 = "On dirait qu'elle envisage Port-au-Prince d'abord...";
			link.l1.go = "PZ_7";
		break;
		
		case "PZ_7":
			dialog.text = "Tu crois ça ? C'est une erreur. Même si de Mussac a plus d'argent que moi, ce dont je doute, il ne peut pas se permettre de consacrer une partie du budget de la ville à un bordel, peu importe combien d'or cela rapporte.";
			link.l1 = "Bon point. Elle n'a clairement pas réfléchi à son ambition.";
			link.l1.go = "PZ_8";
		break;
		
		case "PZ_8":
			dialog.text = "Tu sais, je me suis toujours demandé comment d'autres bordels restent à flot. Ce n'est pas l'aptitude d'une femme à penser et, surtout, à gouverner - marque mes mots.";
			link.l1 = "Eh bien, tu te trompes là-dessus. Merci pour ton temps, Marcus ! Si je la rencontre en premier, je lui dirai que tu serais ravi de la voir.";
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