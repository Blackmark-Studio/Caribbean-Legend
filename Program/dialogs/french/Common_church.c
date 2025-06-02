// boal 25/04/04 общий диалог церковь
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Church\" + NPChar.City + "_Church.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06
    
    string iDay, iMonth, lastspeak_date, eggStr;
    string sTemp, sTitle;

	iDay           = environment.date.day;
	iMonth         = environment.date.month;
	lastspeak_date = iday + " " + iMonth;
	int iMoneyToCharacter;

	if (!CheckAttribute(npchar, "quest.HealthMonth"))
    {
        npchar.quest.HealthMonth = "";
    }
	
    if (!CheckAttribute(npchar, "quest.BadMeeting"))
    {	
        npchar.quest.BadMeeting = "";
    }
    if (!CheckAttribute(npchar, "quest.GhostShipMonth"))
    {
        npchar.quest.GhostShipMonth = "";
    }
    
	if (!CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.GiveQuestDateParam"))
	{
		NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = "";
	}
	
	if(!CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.GiveQuestDay"))
	{
		NPChar.GenQuest.ChurchQuest_2.GiveQuestDay = "";
	}
	
	if (!CheckAttribute(NPChar, "GenQuest.ChurchQuest_1.GiveQuestDateParam"))
	{
		NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = "";
	}
	
	if(!CheckAttribute(NPChar, "GenQuest.ChurchQuest_1.GiveQuestDay"))
	{
		NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = "";
	}
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase(""+GetSexPhrase("Mon fils","Ma fille")+", malheureusement, je ne peux pas te donner refuge. Fuis !","Les gardes de la ville ratissent la ville à votre recherche, "+GetSexPhrase("mon fils","ma fille")+"Les portes de mon église sont toujours ouvertes aux souffrants, mais je ne peux pas vous offrir d'abri...",""+GetSexPhrase("Mon fils","Ma fille")+", tu dois fuir ! Ne tarde pas, je t'en prie !"),LinkRandPhrase("Que fais-tu dans l'église, âme déchue ? Je te somme de partir sur-le-champ, avant que les soldats ne te trouvent ici et ne perpètrent un massacre !","Sors du temple sur-le-champ, vile moqueur ! Jamais je ne protégerai un scélérat comme toi !","Sortez du temple de notre Seigneur sur-le-champ ! Nous n'avons pas besoin de meurtriers ici !"));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Oh, allez, mon père...","Je n'ai pas besoin de ton aide de toute façon..."),LinkRandPhrase("Ne vous mettez pas en travers de mon chemin, mon Père...","Je m'en vais, ne vous inquiétez pas...","Mon père, cessez ce tapage - je n'ai vraiment pas le temps pour cela."));
				link.l1.go = "fight";
				break;
			} 
            if (npchar.quest.BadMeeting != lastspeak_date)
			{
				if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_2.StartQuest") && !CheckAttribute(PChar, "GenQuest.ChurchQuest_1.StartQuest") && NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam != iMonth && NPChar.GenQuest.ChurchQuest_2.GiveQuestDay != lastspeak_date && NPChar.location != "Panama_church" && NPChar.location != "LosTeques_church" && rand(5) == 1 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock")) // 280313
				{
					dialog.text = "...ils brûleront dans l'enfer ardent pour l'éternité ! Jamais ils ne verront...";
					link.l1 = RandPhraseSimple("Hem! Est-ce que je dérange, padre?","C'est le discours !");
					link.l1.go = "GenQuest_Church_2_Start_1";
					NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth; // Предлагает квест не чаще раза в месяц
					break;
				}
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.QuestTown") && PChar.GenQuest.ChurchQuest_2.QuestTown == NPChar.city && CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete"))
				{
					Dialog.Text = ""+GetSexPhrase("Mon fils","Ma fille")+", je suis heureux de vous revoir !";
					link.l1 = "Et je suis heureux de vous voir en bonne santé, padre "+NPChar.name+"... ";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1";
					break;
				}
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.QuestTown") && PChar.GenQuest.ChurchQuest_1.QuestTown == NPChar.city && CheckAttribute(PChar, "GenQuest.ChurchQuest_1.Complete"))
				{
					Dialog.Text = ""+GetSexPhrase("Mon fils","Ma fille")+"Je suis heureux de vous revoir en bonne santé et de bonne humeur. Le Seigneur a dû nous aider dans notre affaire, n'est-ce pas ?";
					link.l1 = "Oui, "+RandPhraseSimple("père","saint Père")+", bien que le vent n'ait pas toujours soufflé dans mes voiles, bien que j'aie passé plus de temps, de forces et d'argent - votre mission est accomplie.";
					link.l1.go = "GenQuest_Church_1_Complete_1";
					break;
				}
				Dialog.Text = "Bienvenue dans notre saint refuge, "+GetSexPhrase("mon fils","ma fille")+".";
				link.l1 = "Bonjour, saint Père.";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_church")
				{
					dialog.text = "Salutations, Ellen, mon enfant.";
					link.l1 = "Et à vous, Mon Père.";
				}
				link.l1.go = "node_3";
				Link.l2 = "Tu n'es pas mon père et ne t'adresse plus jamais à moi de cette façon.";
				Link.l2.go = "node_2";
				NPChar.GenQuest.ChurchQuest_2.GiveQuestDay = lastspeak_date;	// Если не дал сегодня, то токо на след день.
			}
			else
			{
				Dialog.Text = "Va-t'en du temple du Seigneur, blasphémateur ! Nous n'avons rien à nous dire !";
				Link.l1 = "Je ne voulais même pas.";
				Link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "node_2":
			dialog.text = "Oh, toi, blasphémateur ! Va-t'en ! N'ose pas souiller le temple de notre Seigneur avec ta présence !";
			link.l1 = "Je n'avais même pas l'intention de rester ici.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -0.25);
			npchar.quest.BadMeeting = lastspeak_date;
		break;

		case "node_3":
			if(startHeroType == 4 && NPChar.location == "SantaCatalina_church")
			{
				dialog.text = "Je suis heureux que, malgré vos... activités avec Jan, vous n'oubliez pas notre Seigneur et Sa maison. Comment puis-je vous aider ?";
			}
			else
			{
				dialog.text = "Que le Seigneur bénisse vous et vos affaires... Êtes-vous venu me voir pour une raison particulière ?";
			}
    		link.l1 = RandPhraseSimple("Je voudrais faire un don.","Je veux faire un don pour une bonne cause.");
    		link.l1.go = "donation";
    		link.l2 = RandPhraseSimple("Je pense qu'il est temps pour une confession.","Je veux me confesser, "+RandPhraseSimple("padre.","Père saint."));
    		link.l2.go = "ispoved";
    		link.l3 = RandPhraseSimple("J'ai affaire avec vous, "+RandPhraseSimple("père.","saint Père."),"Je suis arrivé pour affaires, "+RandPhraseSimple("padre.","saint Père."));
    		link.l3.go = "work";
			
			//--> Сага
			// Картахена, Чика Гонсалес
			if(CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "cartahena" && pchar.location == "Cartahena_church" && sti(pchar.money) >= 1000)
			{
				link.l4 = "Je souhaite commander un service de prières pour le repos de l'âme d'une dame.";
				link.l4.go = "saga";				
			}
			// поиски исцеления от заклятий
			if(CheckAttribute(pchar, "questTemp.Saga.JessSeekTreatment") && pchar.location != "Bridgetown_church" && !CheckAttribute(npchar, "quest.seektreatment"))
			{ // все церкви, кроме Бриджтауна
				link.l4 = "Mon Père, j'ai besoin d'aide. Je suis vraiment malade. Une vile malédiction païenne s'est abattue sur moi. Je vous en prie, aidez-moi, je vous en supplie !";
				link.l4.go = "seektreatment";
			}
			if(CheckAttribute(pchar, "questTemp.Saga.JessSeekTreatment") && pchar.location == "Bridgetown_church")
			{ // попал в Бриджтаун
				link.l4 = "Père, j'ai besoin d'aide. Je suis vraiment malade. Une maudite malédiction païenne s'est abattue sur moi. S'il vous plaît, aidez-moi, je vous en supplie !";
				link.l4.go = "findtreatment";
			}
			if(CheckAttribute(pchar, "questTemp.Saga.JessFindTreatment") && pchar.location == "Bridgetown_church")
			{ // пришёл в Бриджтаун по направлению
				link.l4 = "Mon Père, j'ai besoin d'aide. Je suis vraiment malade. Une malédiction païenne infâme s'est abattue sur moi. On m'a dit que vous êtes celui qui peut m'aider. Je vous en supplie...";
				link.l4.go = "findtreatment";
			}
			// исцеление от заклятий Джесс
			if(CheckAttribute(pchar, "questTemp.Saga.JessTreatment") && pchar.location == "Bridgetown_church")
			{
				link.l4 = "Mon père, j'ai besoin d'aide. Je suis vraiment malade. Une malédiction païenne immonde s'est abattue sur moi. On m'a envoyé vers vous par... Jessica Rose. Elle m'a dit que vous pourriez m'aider.";
				link.l4.go = "treatment";
			}
			if(CheckAttribute(npchar, "quest.candle"))
			{
				link.l4 = "À propos des bougies...";
				link.l4.go = "candle";
			}
			if(CheckAttribute(npchar, "quest.prayer") && GetNpcQuestPastDayParam(npchar, "prayer_date") >= 1 && stf(environment.time) >= 22.0)
			{
				link.l4 = "Je suis prêt à prier, mon Père.";
				link.l4.go = "prayer";
			}
			//<-- Сага
			
			// Warship, 30.05.11. Миниквест из дел чести "Divine justice".
			if(CheckAttribute(Pchar, "QuestTemp.AffairOfHonor.GodJudgement.CanSpeakPriest") && AffairOfHonor_GetCurQuest() == "GodJudgement" &&
				NPChar.city == PChar.QuestTemp.AffairOfHonor.GodJudgement.CityId)
			{
				link.l5 = "Des choses terribles se passent, saint Père.";
				link.l5.go = "AffairOfHonor_GodJudgement_1";
			}
			
			link.l6 = "Excusez-moi, mais je dois m'en aller.";
			link.l6.go = "exit";
		break;

		case "AffairOfHonor_GodJudgement_1":
			dialog.text = "Ne t'inquiète pas, mon fils. Le Seigneur verra ta souffrance et Il tendra une main secourable. Porte toujours une croix sur toi pour renforcer ta foi.";
			Link.l1 = "Merci, saint Père.";
			Link.l1.go = "exit";
			AddItems(PChar, "amulet_3", 15);
			DeleteAttribute(Pchar, "QuestTemp.AffairOfHonor.GodJudgement.CanSpeakPriest");
		break;

// Jason-------------------------------------------------Сага----------------------------------------------
		//--> Чика Гонсалес
		case "saga" :
			dialog.text = "Je m'acquitterai humblement de votre volonté pour 1000 pesos.";
			Link.l1 = "Voici pour vous, mon Père - veuillez prendre ces pièces.";
			Link.l1.go = "saga_1";
		break;
		
		case "saga_1" :
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "Merci, mon fils. Quel est le nom de la senora, pour l'âme de qui je prierai ?";
			Link.l1 = "Elle s'appelle Chica Gonzales, et elle a quitté ce monde il y a de nombreuses années.";
			Link.l1.go = "saga_2";
		break;
		
		case "saga_2" :
			dialog.text = "C'est étrange... Est-il arrivé quelque chose à Alvarez, et vous a-t-il posé cette question ?";
			Link.l1 = "Et qui est cet Alvarez et qu'y a-t-il d'étrange dans ma demande ?";
			Link.l1.go = "saga_3";
		break;
		
		case "saga_3" :
			dialog.text = "Eh bien, comment ! Chaque mois, Alvarez, le gardien de notre phare depuis deux décennies, commande un service de prière pour le repos de l'âme de cette dame. Personne d'autre que lui ne s'est encore soucié de Lady Gonzales. Et vous venez ici. Alors, j'y ai pensé. Cependant, ce n'est pas mon affaire. Certainement, je serai ravi d'accomplir humblement vos souhaits pour aider l'âme égarée à trouver la tranquillité et le chemin vers le paradis.";
			Link.l1 = "Merci, saint Père.";
			Link.l1.go = "saga_4";
		break;
		
		case "saga_4" :
			DialogExit();
			if(CheckAttribute(pchar,"questTemp.Saga7"))
			{
				AddQuestRecord("Saga", "151");
				DeleteAttribute(pchar,"questTemp.Saga7");
			}
			else AddQuestRecord("Saga", "15");
			Saga_SetOrtega();
			pchar.questTemp.Saga = "ortega";
			pchar.quest.Saga_Gonsales1.over = "yes"; //снять возможное прерывание
			if (GetCharacterIndex("SagaGonsalesB") != -1)
			{
				sld = characterFromId("SagaGonsalesB");
				sld.lifeday = 0;
			}
		break;
		
		// belamour участвовал в событиях Картахены
		case "saga_5" :
			dialog.text = "Y a-t-il quelqu'un d'autre pour qui vous souhaiteriez commander un requiem ?";
			Link.l1 = "Mmm... Non, je ne pense pas. Dois-je commander pour quelqu'un d'autre ?";
			Link.l1.go = "saga_6";
		break;
		
		case "saga_6" :
			dialog.text = "Eh bien, peut-être pour les centaines d'innocents qui sont tombés par ta main ou par les lames de tes compagnons impies lorsque tu as pillé cette malheureuse cité?.. Cependant, un humble prêtre est peu susceptible d'espérer atteindre la conscience d'un homme qui a tué de simples citoyens paisibles sans remords...";
			Link.l1 = "Mon père, vous ne comprenez pas... Tout cela appartient au passé. Ici et maintenant, je n'ai pas l'intention de blesser qui que ce soit.";
			Link.l1.go = "saga_7";
		break;
		
		case "saga_7" :
			pchar.questTemp.saga7 = true;
			dialog.text = "Puis-je faire confiance à votre parole...? Mais, en tout cas, ceci est un sol sacré qui ne devrait pas être couvert de sang. Alors, je n'appellerai pas les gardes. Allez en paix. Peut-être avant de faire face au jugement de Dieu, aurez-vous le temps de racheter au moins une partie de vos péchés.";
			Link.l1 = "Peut-être. Que la volonté de Dieu soit faite.";
			Link.l1.go = "saga_4";
		break;
		// <-- Чика Гонсалес
		
		// --> исцеление от заклятий
		case "treatment":
			dialog.text = "Jessica ? Je me souviens d'elle. Pauvre pécheresse. Mais n'est-elle pas morte ?";
			link.l1 = "Elle est morte, saint Père. Maintenant qu'elle est décédée, que le Seigneur repose son âme. Mais elle m'a assuré que vous pourriez m'aider.";
			link.l1.go = "treatment_1";
			DeleteAttribute(pchar, "questTemp.Saga.JessTreatment");
		break;
		
		case "treatment_1":
			dialog.text = "Qui a jeté ces sorts sur toi, mon fils ? Dis-moi honnêtement.";
			link.l1 = "Elle... elle l'a fait. Jessica.";
			link.l1.go = "treatment_2";
		break;
		
		case "treatment_2":
			dialog.text = "Que Dieu nous sauve ! C'est ce que je pensais. Se plonger dans les rites païens peut précipiter même les âmes les plus fortes dans l'abîme des ténèbres... Mais... est-elle vraiment morte ? Ou... pas complètement ?";
			link.l1 = "Vous êtes extrêmement perspicace, Père. Maintenant, elle est totalement morte.";
			link.l1.go = "treatment_3";
		break;
		
		case "treatment_3":
			dialog.text = "Cette pauvre pécheresse s'est confessée à moi plusieurs fois. La haine l'a complètement détruite de l'intérieur. Je savais ce qu'elle préparait. J'ai tenté de l'arrêter, essayé de la faire marcher droit, mais tous mes efforts furent vains. Je l'ai mise en garde contre le terrible danger et les conséquences funestes de ses actes impies...";
			link.l1 = "Oui, saint Père. Ce que j'ai vu était vraiment terrible. Mais... comment puis-je être guéri ?";
			link.l1.go = "treatment_4";
		break;
		
		case "treatment_4":
			dialog.text = "Par la puissance de la prière, mon fils. Par la puissance de la sainte prière purificatrice dans notre temple. Il te faudra prier très longtemps, et pas seulement pour toi. Il te faudra prier pour elle aussi.";
			link.l1 = "Pour Jessica ?";
			link.l1.go = "treatment_5";
		break;
		
		case "treatment_5":
			dialog.text = "Oui. Pour vous et pour son âme. Venez ici à dix heures du soir, pour que personne ne vous distrait. Vous devrez prier toute la nuit. Apportez avec vous vingt grosses bougies de cire, allumez-les, et priez jusqu'à ce qu'elles soient toutes consumées.";
			link.l1 = "Et ensuite, je serai guéri ?";
			link.l1.go = "treatment_6";
		break;
		
		case "treatment_6":
			dialog.text = "Tout est entre les mains du Seigneur. Je vous apprendrai à prier et je vous laisserai les Saintes Écritures. La puissance de la prière sainte détruira les sorts maléfiques qui vous ont frappé, et purifiera également l'âme de la pauvre Jessica.";
			if (GetCharacterItem(pchar, "mineral3") >= 20)
			{
				link.l1 = "J'ai vingt cierges avec moi. Je suis prêt à rester au temple et à commencer à prier.";
				link.l1.go = "treatment_9";
			}
			else
			{
				link.l1 = "Je n'ai pas encore vingt bougies sur moi. Je vais les chercher !";
				link.l1.go = "treatment_7";
			}
		break;
		
		case "treatment_7":
			dialog.text = "D'accord, mon fils. Je t'attendrai. Ne perds pas de temps !";
			link.l1 = "Je serai bientôt ici...";
			link.l1.go = "treatment_8";
		break;
		
		case "treatment_8":
			DialogExit();
			npchar.quest.candle = "true";
		break;
		
		case "candle":
			dialog.text = "As-tu apporté vingt cierges, mon fils ?";
			if (GetCharacterItem(pchar, "mineral3") >= 20)
			{
				link.l1 = "Oui, Mon Père. J'ai vingt cierges de cire avec moi. Je suis prêt à rester au temple et commencer à prier.";
				link.l1.go = "treatment_9";
				DeleteAttribute(npchar, "quest.candle");
			}
			else
			{
				link.l1 = "Pas encore - mais je les obtiendrai par tous les moyens.";
				link.l1.go = "exit";
			}
		break;
		
		case "treatment_9":
			dialog.text = "Eh bien, mon fils. Donne-les-moi et reviens demain après dix heures du soir. Je t'enseignerai les prières nécessaires et te laisserai à l'église pour la nuit.";
			link.l1 = "Merci, saint Père. À demain !";
			link.l1.go = "treatment_10";
		break;
		
		case "treatment_10":
			DialogExit();
			RemoveItems(pchar, "mineral3", 20);
			LAi_RemoveLoginTime(npchar);
			LAi_SetLoginTime(npchar, 6.0, 22.99);
			npchar.quest.prayer = "true";
			SaveCurrentNpcQuestDateParam(npchar, "prayer_date");
		break;
		
		case "prayer":
			dialog.text = "I have prepared the texts of the prayers for you , my son. I also left your twenty candles and the Holy Scripture. Light the candles and start praying. Pray without a stop; pray for your recovery and for the soul of this poor sinner Jessica. If you forget something or if you don't understand something - it doesn't really matter. Pray from your heart, your sincere desire is what matters to our Lord.";
			link.l1 = "Merci, Père. J'ai compris.";
			link.l1.go = "prayer_1";
		break;
		
		case "prayer_1":
			dialog.text = "Je reviendrai le matin. Je prierai aussi pour vous...";
			link.l1 = "Merci, saint Père.";
			link.l1.go = "prayer_2";
		break;
		
		case "prayer_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Saga_BarbadosTreatment", -1);
			chrDisableReloadToLocation = true;//закрыть локацию
		break;
		
		case "seektreatment":
			dialog.text = "Quels sorts païens t'ont frappé, mon fils ?";
			link.l1 = "I don't know how they are called. I am weak and sluggish; I cannot run around, and it is very difficult for me to fight.";
			link.l1.go = "seektreatment_1";
		break;
		
		case "seektreatment_1":
			if (sti(pchar.questTemp.Saga.JessSeekTreatment) == 3)
			{
				dialog.text = "J'ai entendu parler de cela... Elles ont été amenées dans notre monde par des sorcières impies de ces païens à la peau rouge. Je vous conseillerais de voir le père supérieur de l'église de Bridgetown - il a passé plusieurs années à étudier l'influence pernicieuse des malédictions indiennes sur les corps et les âmes des chrétiens.";
				link.l1 = "Et il serait en mesure de m'aider?!";
				link.l1.go = "seektreatment_4";
			}
			else
			{
				dialog.text = "J'ai entendu parler de cela... Ils ont été introduits dans notre monde par des sorcières impies de ces païens à la peau rouge. Malheureusement, le seul conseil que je peux te donner est de passer plus de temps à prier, mon fils, et de placer tes espoirs dans la miséricorde de notre Seigneur.";
				link.l1 = "Mais est-ce qu'il n'y a vraiment rien à faire, mon Père ?! Vais-je rester comme ça... jusqu'à la fin de mes jours ?";
				link.l1.go = "seektreatment_2";
			}
		break;
		
		case "seektreatment_2":
			dialog.text = "Ne désespérez pas, mon fils. Le Seigneur vous écoutera et Il vous enverra de l'aide. Mais je vous recommanderais de vous renseigner dans d'autres lieux saints - peut-être y a-t-il des prêtres qui savent comment lever les malédictions païennes.";
			link.l1 = "Merci, Père ! Je serai guéri - même si je dois visiter chaque église de l'archipel !";
			link.l1.go = "seektreatment_3";
		break;
		
		case "seektreatment_3":
			dialog.text = "Va, mon fils, et que le Seigneur veille sur toi.";
			link.l1 = "Adieu, padre.";
			link.l1.go = "exit";
			npchar.quest.seektreatment = "true";
			pchar.questTemp.Saga.JessSeekTreatment = sti(pchar.questTemp.Saga.JessSeekTreatment)+1;
		break;
		
		case "seektreatment_4":
			dialog.text = "Seul le Seigneur peut vous aider - et vous-même, mon fils. Un prêtre peut seulement vous enseigner quoi faire et comment. Venez le voir.";
			link.l1 = "Merci, padre ! Vous m'avez sauvé ! Je vais immédiatement naviguer vers la Barbade !";
			link.l1.go = "seektreatment_5";
		break;
		
		case "seektreatment_5":
			dialog.text = "Allez maintenant, et que le Seigneur veille sur vous.";
			link.l1 = "Au revoir, Père.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Saga.JessSeekTreatment");
			pchar.questTemp.Saga.JessFindTreatment = "true";
		break;
		
		case "findtreatment":
			dialog.text = "Quels sorts païens se sont abattus sur toi, mon fils ? Laisse-moi deviner : tu ne peux plus courir, un sabre est trop lourd pour toi et tes mouvements sont lents et maladroits ?";
			link.l1 = "Comment l'avez-vous su, Père ?";
			link.l1.go = "findtreatment_1";
		break;
		
		case "findtreatment_1":
			dialog.text = "Il n'était pas difficile de le voir, en regardant votre démarche en vous approchant de moi, mon fils. Que le Seigneur soit miséricordieux envers nos âmes pécheresses... Dites-moi, mon fils, et soyez honnête - qui a placé ces enchantements sur vous ?";
			link.l1 = "Vous avez besoin d'un nom, Mon Père ?";
			link.l1.go = "findtreatment_2";
		break;
		
		case "findtreatment_2":
			dialog.text = "Si vous connaissez le nom, alors dites-le.";
			link.l1 = "Son nom était... Jessica Rose.";
			link.l1.go = "findtreatment_3";
		break;
		
		case "findtreatment_3":
			dialog.text = "Dieu nous garde ! Se plonger dans les rites païens peut jeter même les âmes les plus fortes dans l'abîme des ténèbres... Que lui est-il arrivé, à cette pauvre âme ?";
			link.l1 = "Elle est morte, Père.";
			link.l1.go = "findtreatment_4";
		break;
		
		case "findtreatment_4":
			dialog.text = "Mais... est-elle vraiment morte ? Ou... pas complètement ?";
			link.l1 = "Vous êtes extrêmement perspicace, saint Père. Maintenant elle est totalement morte.";
			link.l1.go = "treatment_3";
			DeleteAttribute(pchar, "questTemp.Saga.JessSeekTreatment"); // если было
			DeleteAttribute(pchar, "questTemp.Saga.JessFindTreatment"); // если было
		break;
		//<-- Сага
		
		// Church GenQuest_2 -->	
		case "GenQuest_Church_2_Start_1":
			dialog.text = "...et la miséricorde du Seigneur! Que les ténèbres universelles consument leurs âmes pour leurs péchés...";
			link.l1 = LinkRandPhrase("Saint Père","Mon père","Père")+", n'êtes-vous pas un peu trop zélé ? Vous savez, vous pourriez avoir une attaque...";
			link.l1.go = "GenQuest_Church_2_Start_2";
			link.l2 = "Hé bien... merde. Adieu alors.";
			link.l2.go = "exit";
		break;
			
		case "GenQuest_Church_2_Start_2":
			dialog.text = "Oh, "+GetSexPhrase("mon fils","mafille")+", terrible sacrilège, le plus ignoble des crimes venait de se produire ! Voler à l'église !!! C'est comme plonger la main dans la poche du Seigneur Lui-même !";
			link.l1 = "Oh, je vois... Comment cela est-il arrivé ?";
			link.l1.go = "GenQuest_Church_2_Start_3";
			link.l2 = LinkRandPhrase("C'est très triste et tout ça, mais je dois vraiment y aller...","Mes condoléances, padre, mais je dois y aller...","Tu as dû trop compter sur le Tout-Puissant. Tu aurais dû utiliser des serrures plus sûres. Eh bien, je dois y aller...");
			link.l2.go = "exit";
		break;
			
		case "GenQuest_Church_2_Start_3":
			dialog.text = "Sous le couvert de la nuit, des vauriens ont tout dérobé ce qui avait été collecté par la paroisse ! Ces blasphémateurs ont même pris le calice sacrificiel !";
			link.l1 = "O tempora, o mores... Mais j'espère que vous avez entrepris quelque chose sur une piste brûlante ?";
			link.l1.go = "GenQuest_Church_2_Start_4";
		break;
			
		case "GenQuest_Church_2_Start_4":
			dialog.text = "Mais bien sûr ! J'ai excommunié ces voleurs blasphématoires, et maintenant je prononce une anathème contre eux !";
			link.l1 = "Je n'ai aucun doute que c'est une mesure des plus efficaces. Mais je pensais à quelque chose de plus pratique. Organiser une poursuite, par exemple.";
			link.l1.go = "GenQuest_Church_2_Start_5";
		break;
			
		case "GenQuest_Church_2_Start_5":
			dialog.text = "Ah, que peut faire un simple prêtre, lié par le vœu de non-résistance au mal ? Ces vauriens sont certainement déjà loin d'ici, buvant dans des tavernes remplies de leurs rapines ou se livrant à la débauche et à la dissipation en compagnie de femmes de mauvaise vie ! J'espère bien qu'ils y trouveront leur fin !";
			link.l1 = RandPhraseSimple("Je suis sûr qu'une telle fin est bien plus attrayante que d'être pendu. Cependant, je ne vais plus vous distraire. Tout le meilleur.","Eh bien, tôt ou tard, nous irons tous rejoindre nos ancêtres, mais je ne dirais pas non à une fin plus rapide pour eux. Cependant, je dois y aller. Bonne chance.");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Saint Père","Padre","Père")+", mais je ne suis lié par aucun vœu et avec empressement j'aiderai le Seigneur à faire venir le temps de la rétribution.";
			link.l2.go = "GenQuest_Church_2_Start_5_1";
		break;
		
		case "GenQuest_Church_2_Start_5_1": //выше - выход из диалога без подтверждения - странно, однако
			dialog.text = "Je prierai pour vous, mon fils! Allez maintenant et donnez à ces escrocs ce qu'ils méritent!";
			link.l1 = "N'ayez aucun doute, Padre";
			link.l1.go = "GenQuest_Church_2_Start_6";
		break;
			
		case "GenQuest_Church_2_Start_6":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_2.StartQuest = true;
			PChar.GenQuest.ChurchQuest_2.QuestTown = NPChar.City;	// Город, в котором спрашиваем
			PChar.GenQuest.ChurchQuest_2.QuestTown.PriestName = NPChar.name;
			PChar.GenQuest.ChurchQuest_2.IslandId = locations[FindLocation(NPChar.location)].islandId; // На каком острове опрашиваем бандюков
			PChar.GenQuest.ChurchQuest_2.Nation = sti(NPChar.nation);
			PChar.GenQuest.ChurchQuest_2.AskPeople = true;
			PChar.GenQuest.ChurchQuest_2.AskBarmen = true;
			PChar.GenQuest.ChurchQuest_2.AskAlcash = true;
			PChar.GenQuest.ChurchQuest_2.MoneyCount = (sti(pchar.rank)+8)*543+3210;
			PChar.GenQuest.ChurchQuest_2.MoneyToCharacter = makeint(sti(PChar.GenQuest.ChurchQuest_2.MoneyCount)/3);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			ReOpenQuestHeader(sQuestTitle);
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "1");
			AddQuestUserDataForTitle(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
		break;
			
		case "GenQuest_Church_2_Thief_2":
			dialog.text = "Eh bien, peut-être que le Créateur tout-puissant envoie à ses enfants insensés la pestilence et la faim pour les punir de leurs péchés...";
				link.l1 = "Pour l'orgueil, par exemple, ou l'avidité... Pourquoi êtes-vous devenu pâle, padre ?";
				link.l1.go = "GenQuest_Church_2_Thief_3";
			break;
			
		case "GenQuest_Church_2_Thief_3":
			if(rand(1) == 0) // Священник искренне раскаивается...
			{
				dialog.text = "Jesus, mon Seigneur, ayez pitié de votre serviteur pécheur... Avez-vous... Avez-vous trouvé les voleurs ? Les avez-vous tués ?";
					link.l1 = "Rappelons-nous les dix commandements, connus de tout bon chrétien dès le berceau : tu ne tueras point, tu ne voleras point, tu ne porteras point de faux témoignage. Un homme craignant Dieu peut-il les violer - et, à plus forte raison, un prêtre spirituel...?!";
					link.l1.go = "GenQuest_Church_2_Thief_4_1_1";
			}
			else
			{
				dialog.text = "Il y a une atmosphère si lourde ici... Alors, as-tu trouvé les voleurs ? Les as-tu tués ?";
					link.l1 = "N'oublions pas les dix commandements, connus de tout bon chrétien dès le berceau : tu ne tueras point, tu ne voleras point, tu ne porteras point de faux témoignage. Un homme craignant Dieu peut-il les violer - et, surtout, un prêtre spirituel ?!";
					link.l1.go = "GenQuest_Church_2_Thief_4_2_1";
			}
		break;
			
		case "GenQuest_Church_2_Thief_4_1_1":
			dialog.text = ""+GetSexPhrase("Mon fils","Ma fille")+"... Que Dieu me pardonne... tant d'argent, tant de tentation... l'homme est faible, vraiment faible ! Je n'ai pas pu y résister... j'étais hors de moi... je priais jour et nuit, je faisais pénitence, je jeûnais rigoureusement, je mortifiais ma chair... Indigne, je suppliais les Cieux seulement d'épargner ces pauvres hommes, que j'avais tentés, poussé par ma propre avidité...";
			link.l1 = LinkRandPhrase("Père","Padre","Mon Père")+", calmez-vous. Ils n'ont rien dit à ce sujet... et ils ne le diront pas, c'est certain. D'ailleurs, ils m'ont volontairement rendu le calice de la Communion, que je vous ai rapporté.";
			link.l1.go = "GenQuest_Church_2_Thief_4_1_2";
		break;
			
		case "GenQuest_Church_2_Thief_4_1_2":
			dialog.text = "Mon Seigneur, je Vous remercie ! Mon Dieu, Vous avez entendu les prières de votre indigne serviteur, un pécheur trébuchant embourbé dans la crasse et les vices...";
			link.l1 = "Tout le monde peut trébucher... Mais puisque ton repentir semble sincère, je dirais que oui : tu es un homme décent et un bon prêtre. Si tu te tiens devant le tribunal, il n’en sortira rien de bon. Et c’est à toi de décider si tu veux demeurer au service du Seigneur ou non - Lui seul peut te le dire et te guider...";
			link.l1.go = "GenQuest_Church_2_Thief_4_1_3";
		break;
			
		case "GenQuest_Church_2_Thief_4_1_3":
			if(rand(1) == 0) // Священник хочет всучить ГГ бабло
			{
				dialog.text = ""+GetSexPhrase("Mon fils","Ma fille")+"... Avec les larmes de repentir et de gratitude, j'accepterai ce calice de vous. La pureté et la noblesse de votre âme m'ont véritablement bouleversé. Je vous bénis de tout cœur et je vous implore humblement d'accepter cette petite récompense de "+FindRussianMoneyString(iMoneyToCharacter)+"... J'espère que cela suffira à couvrir vos frais ?";
				// ГГ не берёт деньги. Плюсанем репу
				link.l1 = "C'est inutile, saint Père "+NPChar.name+"Je ne suis pas exactement la personne la plus pauvre, alors tu ferais mieux d'utiliser cet argent pour le bien de ta paroisse.";
				link.l1.go = "GenQuest_Church_2_Thief_4_1_4";
				// ГГ берёт деньги
				link.l2 = "Merci, "+LinkRandPhrase("Père","père","saint Père")+", c'est plus que suffisant.";
				link.l2.go = "GenQuest_Church_2_Thief_4_1_5";
			}
			else
			{
				dialog.text = ""+GetSexPhrase("Mon fils","Ma fille")+"... Avec les larmes du repentir et de la gratitude, j'accepterai ce calice de votre part comme un signe de la miséricorde et du pardon du Seigneur. La pureté et la noblesse de votre âme m'ont véritablement bouleversé. Je vous bénis de tout mon cœur !";
				link.l1 = "Merci pour la bénédiction, "+LinkRandPhrase("padre.","Père.")+".";
				link.l1.go = "GenQuest_Church_2_Thief_4_1_4";
				link.l1 = "La bénédiction est certainement nécessaire, mais cela ne ferait pas de mal de la soutenir avec quelque chose de plus matériel, compte tenu des dépenses considérables que j'ai engagées...";
				link.l1.go = "GenQuest_Church_2_Thief_4_1_6";
			}
			ChurchGenQuest2_RemoveCup();
		break;
			
		case "GenQuest_Church_2_Thief_4_1_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", 3);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_1");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_1_5":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_2");
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_1_6":
			iMoneyToCharacter = sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter);
			dialog.text = "Oh, enfant, je suis vraiment désolé... J'espère que cette modeste contribution de "+FindRussianMoneyString(iMoneyToCharacter)+" suffira pour couvrir vos dépenses ?";
			link.l1 = "Oui, "+LinkRandPhrase("padre.","Père.")+"ça suffit, merci.";
			link.l1.go = "GenQuest_Church_2_Thief_4_1_6_1";
		break;
			
		case "GenQuest_Church_2_Thief_4_1_6_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_3");
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_2_1":
			dialog.text = "Je ne comprends pas vraiment vos insinuations, "+GetSexPhrase("mon fils","ma fille")+", de quoi parles-tu?!";
			link.l1 = "Je parle des terribles choses que la cupidité peut faire à un homme et que j'ai reçues de gueux prétendument en train de voler votre église... Vouliez-vous dire quelque chose ?";
			link.l1.go = "GenQuest_Church_2_Thief_4_2_2";
		break;
			
		case "GenQuest_Church_2_Thief_4_2_2":
			dialog.text = "Je te dirais, mon enfant, que tu t'adresses à un homme d'église et que tu devrais montrer un peu plus de respect, sinon tu pourrais le regretter. Quant à ce calice - je ne l'ai jamais vu auparavant, mais si tu es prêt à le donner à la paroisse, alors...";
			link.l1 = "Doucement, padre. Vous ne l'aurez pas tant que vous ne vous serez pas expliqué.";
			link.l1.go = "GenQuest_Church_2_Thief_4_2_3";
		break;
			
		case "GenQuest_Church_2_Thief_4_2_3":
			if(rand(1) == 0) // Просто несколько разные варианты диалога
			{
				dialog.text = "Qu'y a-t-il à expliquer ?! Maintenant, regarde - tu es un "+GetSexPhrase("homme avisé","fille astucieuse")+", et vous devez sûrement comprendre que tout ce que ces escrocs ont pu vous dire - que je les aurais soi-disant engagés - est un mensonge flagrant ! Le Seigneur punira ces blasphémateurs non seulement pour sacrilège, mais aussi pour faux témoignage !";
				link.l1 = "Laisse le Seigneur tranquille ! Comment peux-tu savoir ce que ces pauvres âmes m'ont raconté - ceux que tu m'as mis à dos ? Peut-être que je les ai tués avant qu'ils n'aient le temps de me dire quelque chose de mauvais sur toi ?";
				link.l1.go = "GenQuest_Church_2_Thief_4_2_4_1";
			}
			else
			{
				dialog.text = "There's nothing for me to talk about with you! You haven't fulfilled your obligation in the face of our Lord; you're swearing at the temple; you're attempting to blackmail a priest, displaying some church utensils - and it remains yet to be seen how you got it! Thank the God that I am not calling the acolytes to catch you red-handed!";
				link.l1 = "Eh bien... Je vois que vous vous êtes enfoncé dans le péché si profondément que vous ne craignez plus le jugement des hommes. Mais il y a encore la justice divine, et chacun de nous devra y répondre tôt ou tard. Prenez vos 'ustensiles d'église' et réfléchissez si vous êtes digne de les toucher, Père "+NPChar.name+".";
				link.l1.go = "GenQuest_Church_2_Thief_4_2_4_2_1";
				link.l2 = "Je vous prie de pardonner mes doutes, Mon Père, car le coeur d'un mortel est faible, et l'âme est confuse. Je vous prie de prendre le calice et de me donner votre bénédiction.";
				link.l2.go = "GenQuest_Church_2_Thief_4_2_4_2_2";
			}
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_1":
			dialog.text = "Mmmm... "+GetSexPhrase("Mon fils... Monsieur... Sire...","Ma fille... Mademoiselle... Dame...")+" "+PChar.name+"... Je suis prêt à me prosterner devant vous... et à considérer nos désaccords, pour ainsi dire... et à compenser vos dépenses avec cette modeste somme de "+FindRussianMoneyString(iMoneyToCharacter)+"... bien sûr, si vous n'avez pas l'intention d'impliquer d'autres personnes dans cette affaire...";
			// При этом варианте репу плюсуем
			link.l1 = "Je ne vais impliquer personne. Prenez le calice ! Et ne pensez même pas que j'accepterais l'or que vous dérobiez en secret dans les poches de vos paroissiens !";
			link.l1.go = "GenQuest_Church_2_Thief_4_2_4_1_1";
			// При этом - минусуем
			link.l2 = "Je ne vais impliquer personne. Prenez le calice ! Cet or, je le prends seulement parce que j'ai dépensé beaucoup de temps et d'argent pour vous.";
			link.l2.go = "GenQuest_Church_2_Thief_4_2_4_1_2";
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_1_1":
			DialogExit();
			iMoneyToCharacter = PChar.GenQuest.ChurchQuest_2.MoneyToCharacter;
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			ChurchGenQuest2_RemoveCup();
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_5");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex2", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(iMoneyToCharacter));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", 3);
			ChurchGenQuest2_RemoveCup();
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_4");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_2_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChurchGenQuest2_RemoveCup();
			ChangeCharacterComplexReputation(PChar,"nobility", 3);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_6");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_2_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChurchGenQuest2_RemoveCup();
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_7");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1":
			// ничего не принесли священнику.
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Without_All"))
			{
				link.l1 = "Terribles nouvelles, "+LinkRandPhrase("Mon Père","Padre","Père")+": les bandits étaient trop traîtres et ingénieux, et donc je n'ai pas réussi à récupérer l'or de l'église...";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_1";
				break;
			}
			// Принесли священнику только чашу.
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Only_With_Cup"))
			{
				link.l1 = "Nouvelles funestes, "+LinkRandPhrase("Père","Mon père","Père")+": J'ai réussi à rattraper les voleurs, mais mon seul trophée était ce calice.";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1";
				ChurchGenQuest2_RemoveCup();
				break;
			}
			// Принесли священнику и деньги и чашу.
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.With_All"))
			{
				if(sti(PChar.money) >= sti(PChar.GenQuest.ChurchQuest_2.MoneyCount))
				{
					link.l1 = "Je suis certain que vous aimerez la nouvelle - j'ai dûment châtié les brigands et récupéré l'argent de la paroisse ainsi que ce calice.";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_1";
				}
				// Деньги можно заныкать.
				link.l2 = LinkRandPhrase("Père","Padre","Père")+", j'ai apporté de mauvaises nouvelles... J'ai dû passer beaucoup de temps, dépenser des forces et des ressources pour traquer les scélérats, mais quand je les ai trouvés, j'ai découvert qu'ils avaient eu le temps de tout boire et de tout dépenser, sauf ce calice...";
				link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1";
				ChurchGenQuest2_RemoveCup();
				break;
			}
			// Священник - вор.
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.PriestIsThief"))
			{
				dialog.text = "Oh, "+GetSexPhrase("mon fils","ma fille")+", qu'est-ce qui aurait pu m'arriver ? C'est votre chemin qui est plein de dangers et d'anxiété, et ma paisible cellule, domaine de réflexion et de prière, est une île tranquille dans un océan déchaîné de passions humaines...";
					link.l1 = "Et rien ne peut troubler la sérénité de votre bienheureuse solitude ?";
					link.l1.go = "GenQuest_Church_2_Thief_2";
				break;
			}
			// Короткий вариант прохождения квеста.
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Short_With_Mon"))
			{
				if(sti(PChar.money) >= sti(PChar.GenQuest.ChurchQuest_2.MoneyCount))
				{
					link.l1 = "Je suis sûr que cette nouvelle te réjouira - j'ai puni les voleurs et rapporté l'argent de la paroisse.";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_1";
				}
				// Деньги можно заныкать.
				link.l2 = LinkRandPhrase("Père","Mon père","Père")+"... Je dois vous décevoir. J'ai poursuivi des voleurs à travers tout l'archipel, surmonté un grand nombre de dangers et d'obstacles, failli me ruiner, et finalement je les ai rattrapés, mais hélas... ils avaient déjà eu le temps de dilapider l'argent de l'église.";
				link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1";
			}
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1": // ГГ решил заныкать деньги...
			if(rand(1) == 0)	// Священник верит ГГ но не даёт денег...
			{
				if(rand(4) == 3) // Более "мягкий" исход событий.
				{
					dialog.text = "Oh, "+GetSexPhrase("mon fils","ma fille")+"Vos paroles m'ont plongé dans une profonde tristesse - mais pas dans le désespoir, car le désespoir est un péché mortel ! Le Seigneur nous a confrontés à une autre épreuve pour renforcer notre foi.";
						link.l1 = "Amen, Père...";
						link.l1.go = "exit";
						sQuestTitle = NPChar.City + "ChurchGenQuest2";
						AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_9");
						AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
						CloseQuestHeader(sQuestTitle);
						ChangeCharacterComplexReputation(PChar,"nobility", -2);
						DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
						NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
				}
				else
				{
					dialog.text = ""+GetSexPhrase("Mon fils","Ma fille")+", ne mens pas à ton berger spirituel.";
						link.l1 = "Je suis vraiment désolé, Mon Père, mais je jure que je dis la vérité.";
						link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3";
				}
			}
			else
			{
				// Священник даёт деньги ГГ...
				iMoneyToCharacter = sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter);
				dialog.text = "Oh, "+GetSexPhrase("mon fils","ma fille")+". Vos paroles m'ont plongé dans une profonde tristesse - mais pas dans le désespoir, car le désespoir est un péché mortel ! Le Seigneur nous a confrontés à une autre épreuve pour renforcer notre foi. Mais vos efforts et dépenses doivent être compensés, malgré leur infructuosité. Je vous prie d'accepter cette modeste somme - "+FindRussianMoneyString(iMoneyToCharacter)+" - et continuez votre chemin vertueux !";
					link.l1 = "Hmm!... Merci, padre, j'utiliserai cet argent pour une cause vertueuse.";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_1";
					link.l2 = LinkRandPhrase("Père","Padre","Père")+"... Je ne peux pas accepter de récompense pour un travail que je n'ai pas accompli. Vous feriez mieux d'utiliser cet argent pour restaurer l'autel.";
					link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1_2";
			}
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_3":
			if(rand(6) == 3)
			{
				dialog.text = "D'accord, je vous crois, "+GetSexPhrase("mon fils","ma fille")+"Le Seigneur nous a infligé une autre épreuve pour renforcer notre foi.";
				link.l1 = "Amen...";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3_1"
				break;
			}
				dialog.text = "Abominable, pensais-tu vraiment tromper notre Seigneur ?! Malédiction sur toi"+GetSexPhrase(", vaurien",", catin")+" ! Sortez et souvenez-vous que cet argent ne vous apportera aucun bénéfice !";
				link.l1 = "Comment est-ce possible ?! Padre !..";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3_2";
			break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_3_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "5");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			AddCharacterExpToSkill(PChar, "Sneak", 20);
			ChangeCharacterComplexReputation(PChar,"nobility", -3);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_3_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "6");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			ChangeCharacterComplexReputation(PChar, "nobility", -6);
			AddCharacterExpToSkill(PChar, "Leadership", -50);
			AddCharacterExpToSkill(PChar, "Fortune", -70);
			AddCharacterExpToSkill(PChar, "Sneak", 20);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			npchar.quest.BadMeeting = lastspeak_date;
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_4_1":
			if(rand(1) == 0) // Поверил.
			{
				dialog.text = "Oh, "+GetSexPhrase("mon fils","ma fille")+". Vos paroles m'ont plongé dans une profonde tristesse - mais pas dans le désespoir, car le désespoir est un péché mortel ! Le Seigneur nous a confrontés à une autre épreuve afin de renforcer notre foi.";
				link.l1 = "Amen, Père...";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_2"; // Переход сюда, т.к. одно и тоже.
			}
			else
			{
				dialog.text = "Oui, c'est bien ce calice qui a été volé avec l'argent... Mais... Si vous l'avez, comment se fait-il que vous n'ayez pas ramené l'argent ? C'était une somme considérable, et sûrement ces vauriens n'ont pas pu tout dépenser si vite... "+GetSexPhrase("Mon fils","Ma fille")+", souviens-toi qu'il n'y a pas de plus grand péché que de mentir à ton berger spirituel et de porter un faux témoignage dans le temple face à Dieu !";
				link.l1 = "Saint Père "+NPChar.name+", j'ai failli perdre la vie pour obtenir ce vase, pensant vous faire plaisir. Je ne dirai rien sur la somme d'argent que j'ai dépensée pour tout cela !";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1_2";
			}
			break;
			
		case "GenQuest_Church_2_Finally_Complete_1_4_1_2":
			dialog.text = "Sors d'ici et remercie le Tout-Puissant, qui m'a donné un cœur humble. C'est la seule raison pour laquelle tu n'es pas encore marqué comme un voleur et un gredin !";
			link.l1 = "Comment se fait-il ?! "+LinkRandPhrase("Saint Père","Padre","Père")+"!..";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1_2_1";
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_4_1_2_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -5);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_12");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.quest.BadMeeting = lastspeak_date;
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_1":
			DialogExit();
			iMoneyToCharacter = PChar.GenQuest.ChurchQuest_2.MoneyToCharacter;
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			AddMoneyToCharacter(PChar, iMoneyToCharacter);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_10");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -1);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_11");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_1_1":
			dialog.text = "Oh, "+GetSexPhrase("mon fils","ma fille")+". Vos paroles m'ont plongé dans un profond chagrin - mais pas dans le désespoir, car le désespoir est un péché mortel ! Le Seigneur nous a confrontés à une autre épreuve pour renforcer notre foi.";
			link.l1 = "Amen, mon Père...";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_2";
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_8");
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_2_1":
			dialog.text = "Seigneur, je Te remercie ! En effet, tu étais Son instrument, mon enfant ! Je savais que notre Père Céleste te montrerait le chemin et te fournirait toute l'aide dont tu avais besoin. Je priais sans relâche, et...";
			link.l1 = "Vous savez, padre, dans des affaires comme celle-ci, les armes sont sûrement plus utiles que les prières. Mais, apparemment, vos prières ont effectivement été entendues.";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_2";
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_2_2":
			dialog.text = ""+GetSexPhrase("Mon fils","Ma fille")+", je veux te récompenser comme il se doit, toi"+GetSexPhrase(", comme un vrai chevalier de la Sainte Mère Église,","")+"  ai fait tout ce qui était en mon pouvoir surca...";
			link.l1 = "Mon père, vous exagérez vraiment mes humbles exploits. Je vais maintenant vous laisser louer notre Seigneur...";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_3";
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_2_3":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", 5);
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_2.MoneyCount));
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "4");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
		// <-- квесты церкви

		case "donation":
			dialog.Text = "Bien sûr, "+GetSexPhrase("mon fils","ma fille")+"Combien aimeriez-vous donner à la Sainte Église ?";
			Link.l1 = "Je suis désolé, saint Père, mais j'ai changé d'avis.";
			Link.l1.go = "No donation";
			if(makeint(PChar.money)>=100)
			{
				Link.l2 = "Ma donation sera modeste - seulement 100 pesos.";
				Link.l2.go = "donation paid_100";
			}
			if(makeint(PChar.money)>=1000)
			{
				Link.l3 = "1000 pesos. Je pense que cela devrait suffire.";
				Link.l3.go = "donation paid_1000";
			}
			if(makeint(PChar.money)>=5000)
			{
				Link.l4 = "J'ai de la chance avec l'argent, donc je vais donner 5000 pesos.";
				Link.l4.go = "donation paid_5000";
			}
			//-->> квест пожертвования хозяйки борделя
			if(pchar.questTemp.different == "HostessChurch_toChurch" && pchar.questTemp.different.HostessChurch.city == npchar.city && sti(pchar.money) >= sti(pchar.questTemp.different.HostessChurch.money))
			{
				Link.l5 = "Mon père, je veux faire un don, mais pas en mon nom. Je le fais à la demande de quelqu'un.";
				Link.l5.go = "HostessChurch";
			}
			//<<-- квест пожертвования хозяйки борделя
		break;

		case "No donation":
			dialog.Text = "Hmm... Eh bien, c'est votre décision, et vous êtes libre de changer d'avis. Et n'oubliez pas que cela sera pris en compte le jour du Jugement dernier.";
			Link.l1 = "Comme bien d'autres choses le feront aussi. Changeons de sujet.";
			Link.l1.go = "node_3";
			Link.l2 = "Je suis désolé, Père, mais il est temps pour moi de partir.";
			Link.l2.go = "exit";
		break;

		case "donation paid_100":
			AddMoneyToCharacter(pchar, -100);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 100;
			dialog.Text = "Au nom de la Sainte Église, je vous remercie, "+GetSexPhrase("mon fils","ma fille")+", pour votre don.";
			Link.l1 = "J'ai besoin de vous parler, Père.";
			Link.l1.go = "node_3";
			Link.l2 = "Je suis désolé, Mon Père, mais il est temps pour moi de partir.";
			Link.l2.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "donation paid_1000":
			AddMoneyToCharacter(pchar, -1000);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 1000;
			dialog.Text = "Au nom de la Sainte Église, je vous remercie.";
            Link.l1 = "J'ai besoin de vous parler, mon Père.";
			Link.l1.go = "node_3";
			Link.l2 = "Je suis désolé, Mon Père, mais il est temps pour moi de partir.";
			Link.l2.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "donation paid_5000":
			AddMoneyToCharacter(pchar, -5000);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 5000;
			dialog.Text = "Au nom de la Sainte Église, je vous remercie pour votre don.";
            Link.l1 = "J'ai besoin de vous parler, mon Père.";
			Link.l1.go = "node_3";
			Link.l2 = "Je suis désolé, mon Père, mais il est temps pour moi de partir.";
			Link.l2.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "ispoved":
			dialog.text = "Bien sûr, "+GetSexPhrase("mon fils","ma fille")+", je vous écoute.";
			link.l1 = "J'ai changé d'avis. Peut-être la prochaine fois.";
			link.l1.go = "exit";
			link.l2 = "Je suis tellement plein de péchés, Mon Père. Une journée ne suffira pas pour énumérer toutes mes méfaits...";
			link.l2.go = "ispoved_1";
		break;

		case "ispoved_1":
			dialog.text = "Chacun de nous est un pécheur, mon enfant...";
			link.l1 = "Oui, mais sur ma conscience le poids de milliers de morts pèse lourdement. J'ai pillé et coulé des navires...";
			link.l1.go = "ispoved_2";
		break;

		case "ispoved_2":
			dialog.text = "J'espère qu'il n'y avait personne parmi ceux qui naviguaient sous le pavillon de "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "Non, bien sûr que non, Père.";
			link.l1.go = "ispoved_3";
			link.l2 = "De toutes sortes, mon Père...";
			link.l2.go = "ispoved_4";
		break;

		case "ispoved_3":
			dialog.text = "Alors notre Seigneur vous absoudra de ces péchés. Car c'est une époque cruelle, et en détruisant les ennemis de votre souverain, vous sauvez la vie de ses loyaux sujets.";
			link.l1 = "Merci, Mon Père, c'était une grande consolation... Je vais y aller maintenant.";
			link.l1.go = "exit";
		break;

		case "ispoved_4":
			dialog.text = "Le Seigneur ne vous absoudra pas d'un tel péché ! Priez et repentez-vous, repentez-vous et priez ! Il n'y a qu'un seul chemin pour vous désormais - le cloître !";
			link.l1 = "Le cloître devra attendre. Pas dans cette vie, du moins. Adieu...";
			link.l1.go = "exit";
			npchar.quest.BadMeeting = lastspeak_date;
		break;

        case "work":
        	if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.AskOwner") && NPChar.location == PChar.GenQuest.ChurchQuest_1.ToColony + "_church")
        	{
        		dialog.text = "Je suis désolé, "+GetSexPhrase("mon fils","ma fille")+", mais tous les confessionnaux sont occupés pour le moment. Je pourrai écouter votre confession dans une demi-heure au plus tôt.";
				link.l1 = "Excusez-moi, "+RandPhraseSimple("père","Père")+", c'est une autre affaire. Père "+PChar.GenQuest.ChurchQuest_1.PriestName+", de "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown+"Gen")+", t'a jadis offert des trésors inestimables de la bibliothèque théologique. Il m'a demandé de les rendre.";
				link.l1.go = "GenQuest_Church_1_Dialog_1";
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.AskOwner");
				break;
        	}
			dialog.text = "Quel genre d'affaire vous amène ici, "+GetSexPhrase("mon fils","ma fille")+"?";
			link.l1 = "Je veux vous poser une question, Padre...";
			link.l1.go = "quests"; // ссылка к НПС
            link.l2 = RandPhraseSimple("Je voulais parler de travailler pour le bien de l'église de "+NationNameGenitive(sti(NPChar.nation))+".","Comment vont les choses dans la paroisse ? Avez-vous besoin d'aide ?");
			link.l2.go = "prihod";
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
	            link.l3 = RandPhraseSimple("Mon Père","Père")+", je veux te parler d'affaires financières."; //(пересылка в кредиты)
	            link.l3.go = "LoanForAll";
            }
			// -->
            if (stf(pchar.Health.HP) < 60.0)
            {
                link.l4 = "J'ai besoin de soins.";
                link.l4.go = "healthAdd_1";
            }
            
			//квест мэра - на связь с нашим шпионом
			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "")
			{
	            link.l7 = RandPhraseSimple("Mon père","Saint Père")+", je suis ici à la demande d'un homme. Son nom est gouverneur "+GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))+".";
	            link.l7.go = "IntelligenceForAll";
            }
			//--> Jason Церковная депеша
			if (CheckAttribute(pchar, "GenQuest.Monkletter") && npchar.city == pchar.GenQuest.Monkletter.City)
			{
	            link.l10 = "Mon père, je vous ai apporté des documents d'un moine de la ville de "+XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.StartCity)+".";
	            link.l10.go = "Monkletter";
            }
			//<-- Церковная депеша
			//--> Jason Доставка молитвенников
			if (CheckAttribute(pchar, "GenQuest.Churchbooks") && pchar.GenQuest.Churchbooks == "go" && sti(npchar.nation) == sti(pchar.GenQuest.Churchbooks.Nation) && npchar.city != pchar.GenQuest.Churchbooks.StartCity)
			{
	            link.l11 = "Padre, je viens de la colonie de "+XI_ConvertString("Colonie"+pchar.GenQuest.Churchbooks.StartCity)+"  L'église locale a besoin de plus de livres de prières, et un moine local a suggéré de vous voir à ce sujet. ";
	            link.l11.go = "Churchbooks";
            }
			if (CheckAttribute(pchar, "GenQuest.Churchbooks") && pchar.GenQuest.Churchbooks == "return" && npchar.city == pchar.GenQuest.Churchbooks.StartCity)
			{
	            link.l11 = "Mon père, j'ai apporté les livres de prières pour votre paroisse.";
	            link.l11.go = "Churchbooks_2";
            }
			//<-- Доставка молитвенников
			link.l99 = "J'ai changé d'avis, j'ai beaucoup à faire.";
			link.l99.go = "exit";
		break;

		case "prihod":
			if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_1.StartQuest") && !CheckAttribute(PChar, "GenQuest.ChurchQuest_2.StartQuest") && NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam != iMonth && NPChar.GenQuest.ChurchQuest_1.GiveQuestDay != lastspeak_date && NPChar.location != "Panama_church" && rand(5) == 1)
		    {
		        dialog.text = "C'est formidable. Et pourtant, en ces temps sombres, "+GetSexPhrase("mon fils","ma fille")+", tous les visiteurs du temple ne peuvent pas être utiles à notre Sainte Mère l'Église.";
				link.l1 = LinkRandPhrase("Père","Padre","Mon Père")+", je suis un vrai chrétien, et mes intentions de servir notre Sainte Mère l'Église sont des plus sincères."+GetSexPhrase(" Qui soutiendra Elle, sinon son loyal chevalier, comme moi ?","Bonjour, mon ami.")+"";
				link.l1.go = "GenQuest_Church_1_Start_1";
				NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = iMonth; // Предлагает квест не чаще раза в месяц
		    }
			else
			{
				NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = lastspeak_date;	// Если не дал сегодня, то токо на след день.
			}	
            dialog.text = "Tout est calme dans la paroisse jusqu'à présent, "+GetSexPhrase("mon fils","ma fille")+"Merci pour l'offre.";
    		link.l2 = "Eh bien, si tout va bien, je suppose que je vais vaquer à mes affaires.";
    		link.l2.go = "exit";
			DeleteAttribute(npchar, "quest.add");
			NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = lastspeak_date;	// Если не дал сегодня, то токо на след день.
		break;
		
		// Church GenQuest_1 -->
		case "GenQuest_Church_1_Start_1":
			dialog.text = "Eh bien, j'ai une mission délicate, qui nécessiterait non seulement la pureté des intentions, mais aussi un grand courage et une discrétion considérable...";
			link.l1 = LinkRandPhrase("Père","Mon Père","Père")+", je serai heureux de vous rendre n'importe quel service, même si pour cela je devrai me diriger directement vers l'enfer ! Que Dieu me pardonne pour mes paroles impies.";
			link.l1.go = "GenQuest_Church_1_Start_2";
		break;
			
		case "GenQuest_Church_1_Start_2":
			PChar.GenQuest.ChurchQuest_1.QuestTown = NPChar.City;
			Church_GenQuest1_InitStartParam(NPChar);
			dialog.text = "Oh! Bon... Mais, encore une fois, c'est une affaire très délicate... Il y a quelque temps, le père supérieur "+PChar.GenQuest.ChurchQuest_1.ToName+" de "+XI_ConvertString("Colonie"+PChar.GenQuest.ChurchQuest_1.ToColony+"Gen")+" sur "+XI_ConvertString(PChar.GenQuest.ChurchQuest_1.ToIsland+"Voc")+"a emprunté quelques ouvrages théologiques et manuscrits anciens d'une bibliothèque d'église pour moi pendant un certain temps. Parce que la demande était soutenue par l'insistance de l'archevêque à ne pas empêcher la diffusion de la charmante lumière de la connaissance, je ne pouvais pas refuser, même si je supposais que les difficultés des voyages en mer ne lui permettraient pas de retourner les manuscrits à temps... Pourriez-vous m'aider à résoudre ce problème ?";
			link.l1 = "J'ai bien peur, "+LinkRandPhrase("Père","père","saint Père")+", je ne pourrai pas faire cela pour vous. C'est une affaire très délicate, et seul un véritable diplomate réussirait à la régler.";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Père","Mon père","Père")+", votre mission ne me semble pas trop compliquée. J'y vais tout de suite.";
			link.l2.go = "GenQuest_Church_1_Start_3";
		break;
			
		case "GenQuest_Church_1_Start_3":	// Квест взят
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.StartQuest = true;
			PChar.GenQuest.ChurchQuest_1.PriestName = NPChar.name;
			PChar.GenQuest.ChurchQuest_1.Nation = sti(NPChar.nation);
			PChar.GenQuest.ChurchQuest_1.AskOwner = true;
			sQuestTitle = NPChar.City + "ChurchGenQuest1";
			ReOpenQuestHeader(sQuestTitle);
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "1");
			AddQuestUserDataForTitle(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			AddQuestUserData(sQuestTitle, "sOwnerCity", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Gen"));
		break;
			
		case "GenQuest_Church_1_Dialog_1":
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.2A_Scene"))	// Сцена 2а
			{
				dialog.text = "Oh! Oui... En effet, maintenant je me souviens... Mais, "+GetSexPhrase("mon fils","ma fille")+", ces trésors sont de nature spirituelle plutôt que matérielle ! Ils ont déjà beaucoup aidé mes paroissiens et pourraient le faire à l'avenir !";
				link.l1 = "Mais, "+LinkRandPhrase("Père","Mon père","Père")+", les paroissiens du Père "+PChar.GenQuest.ChurchQuest_1.PriestName+" ont également besoin de salut, et sans ces oeuvres, il manquera le soutien des piliers de la théologie, et ses sermons manqueront d'inspiration.";
				link.l1.go = "GenQuest_Church_1_Dialog_1_1";
			}
			else	// Сцена 2б-а и 2б-б
			{
				dialog.text = "Oh, oui !.. En effet... "+GetSexPhrase("Mon fils","Ma fille")+", ces trésors sont de nature plus spirituelle que matérielle ! Ils ont déjà énormément aidé mes paroissiens, si bien que, à ma honte, j'ai 'oublié' de les rendre à leur légitime propriétaire...";
				link.l1 = "En effet, "+RandPhraseSimple("Père","Padre","Mon père")+", en effet. C'est pourquoi Père "+PChar.GenQuest.ChurchQuest_1.PriestName+"m'a demandé de lui livrer ces livres personnellement.";
				link.l1.go = "GenQuest_Church_1_Dialog_1_2";
			}
		break;
			
		case "GenQuest_Church_1_Dialog_1_1": // Сцена 2а
			dialog.text = "Je comprends, mon enfant, mais ne prions-nous pas notre Seigneur chaque jour : 'et pardonne-nous nos offenses, comme nous pardonnons aussi à ceux qui nous ont offensés'? Et l'église de "+XI_ConvertString("Colonie"+PChar.GenQuest.ChurchQuest_1.QuestTown+"Gen")+"plus riche que ma modeste paroisse.";
			link.l1 = "Vous avez certainement raison, Père, mais je viens de penser à d'autres lignes des Saintes Écritures : 'ne cherchez pas un chemin facile, car c'est là que le Diable nous attend, et sa voix est d'autant plus subtile et la tentation d'autant plus forte, que le chemin est facile !' Et padre "+PChar.GenQuest.ChurchQuest_1.PriestName+" avait déjà l'intention d'envoyer un message concernant votre oubli à l'archevêque - je viens juste de le dissuader de le faire.";
			link.l1.go = "GenQuest_Church_1_Dialog_1_1_1";
		break;
			
		case "GenQuest_Church_1_Dialog_1_1_1":
			dialog.text = "À l'archevêque ?! Pour une si petite affaire !.. Pourquoi ? Vraiment ? J'avais de toute façon l'intention d'envoyer ces œuvres à mon cher frère en Christ - c'est juste qu'il n'y avait pas de bonne occasion de les lui livrer. Mais en vous, "+GetSexPhrase("mon fils","ma fille")+", je vois un serviteur vraiment méritant de notre Seigneur. Tenez - prenez ces livres et manuscrits et veuillez les livrer au Père "+PChar.GenQuest.ChurchQuest_1.PriestName+" sain et sauf. Et ajoutez à cela ma plus sincère gratitude.";
			link.l1 = "Bien sûr, "+LinkRandPhrase("Père","Padre","Mon père")+"Bien sûr...";
			link.l1.go = "GenQuest_Church_1_Dialog_1_1_2";
		break;
			
		case "GenQuest_Church_1_Dialog_1_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.Complete.Short = true;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "2");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			// Предмет "рукопись" -->
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			// <-- Предмет "рукопись"
		break;
			
		case "GenQuest_Church_1_Dialog_1_2":	// Сцена 2б-а и 2б-б
			// Генерим кэпа -->
			sld = GetCharacter(NPC_GenerateCharacter("ChurchGenQuest1_Cap", "mercen_" + (rand(14)+14), "man", "man", 15, NPChar.nation, -1, true, "quest"));
			FantomMakeCoolFighter(sld, 35, 40, 35, "blade_13", "pistol3", "grapeshot", 30);
			FantomMakeCoolSailor(sld, 7 + rand(2), "", CANNON_TYPE_CANNON_LBS16, 75, 70, 65);
			sld.Abordage.Enable = false;
			sld.ShipEnemyDisable  = true; // флаг не обижаться на выстрелы
			LAi_SetImmortal(sld, true);
			sld.Dialog.FileName = "GenQuests_Dialog.c";
			sld.Dialog.CurrentNode = "ChurchGenQuest_1_DeckDialog_1";
			Group_FindOrCreateGroup("ChurchGenQuest1_CapGroup");
			Group_AddCharacter("ChurchGenQuest1_CapGroup", "ChurchGenQuest1_Cap");
			Group_SetType("ChurchGenQuest1_CapGroup", "trade");
			Group_SetGroupCommander("ChurchGenQuest1_CapGroup", "ChurchGenQuest1_Cap");
			Group_SetTaskNone("ChurchGenQuest1_CapGroup");
			Group_LockTask("ChurchGenQuest1_CapGroup");
			PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
			PChar.GenQuest.ChurchQuest_1.CurPortManColony = "";
			PChar.GenQuest.ChurchQuest_1.CapFullName = GetFullname(sld);
			PChar.GenQuest.ChurchQuest_1.CapShipName = sld.Ship.Name;
			PChar.GenQuest.ChurchQuest_1.NoCapColony = NPChar.city;
			PChar.GenQuest.ChurchQuest_1.CapColony = GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown);
			// <-- Генерим кэпа
			
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.2BA_Scene")) // Сцена 2б-а
			{
				dialog.text = "Mais, "+GetSexPhrase("mon fils","ma fille")+"... Vous voyez, la chose est que la semaine dernière, j'ai rencontré un capitaine du navire '"+sld.Ship.Name+"où j'ai été appelé pour administrer la communion d'un marin mourant. À ma grande joie, capitaine "+GetFullName(sld)+" m'a dit qu'il allait "+XI_ConvertString("Colonie"+GetColonyExpect2Colonies(NPChar.city,PChar.GenQuest.ChurchQuest_1.QuestTown))+". Et bien qu'il n'ait garanti aucune condition, il a tout de même accepté d'aider et m'a assuré que le port de "+XI_ConvertString("Colonie"+PChar.GenQuest.ChurchQuest_1.QuestTown+"Gen")+" il viendra certainement. Alors j'ai profité de cette occasion, j'ai envoyé des livres avec cet homme bon et j'ai confié leur avenir au Seigneur.";
				link.l1 = "Hmm, es-tu sûr que ce capitaine est digne de confiance ? A-t-il compris la valeur des oeuvres qui lui ont été confiées et l'importance de cette mission ?";
				link.l1.go = "GenQuest_Church_1_Dialog_1_2_1";
			}
			else // Сцена 2б-б
			{
				dialog.text = "Oh, "+GetSexPhrase("mon fils","ma fille")+"! Vous arrivez juste avec quelques heures de retard ! J'ai déjà envoyé les livres du Père "+PChar.GenQuest.ChurchQuest_1.PriestName+" avec le capitaine "+PChar.GenQuest.ChurchQuest_1.CapFullName+"Ce matin, cet homme craignant Dieu est venu se confesser et a mentionné qu'aujourd'hui son navire allait appareiller vers "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.CapColony)+". Et bien que le capitaine monsieur n'ait garanti aucune condition, il a quand même accepté d'aider et m'a assuré que le port de "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.QuestTown+"Gen")+" il viendra certainement visiter.";
				link.l1 = LinkRandPhrase("Père","Padre","Père")+"... es-tu sûr que ce capitaine est digne de confiance ? Et je veux aussi savoir comment s'appelle son navire.";
				link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_1";
			}
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_1":	// 2б-а
			dialog.text = "Je fais confiance aux gens, "+GetSexPhrase("mon fils","ma fille")+", chacun de nous est créé à l'image et à la ressemblance de notre Seigneur, et Son feu sacré brûle dans chaque âme !";
			link.l1 = "Ugh. C'est un argument de poids, c'est certain. Eh bien... Alors bénissez-moi, Mon Père, et souhaitez-moi bonne chance dans ma quête de ce capitaine.";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_1_1";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_1_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = NPChar.city;
			PChar.GenQuest.ChurchQuest_1.CapFullInfo = true; // Полная инфа о кэпе
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "3_1");
			AddQuestUserData(sQuestTitle, "sCapName", PChar.GenQuest.ChurchQuest_1.CapFullName);
			AddQuestUserData(sQuestTitle, "sShipName", PChar.GenQuest.ChurchQuest_1.CapShipName);
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_1":
			dialog.text = "Vous devriez faire confiance aux gens, "+GetSexPhrase("mon fils","ma fille")+"Quant à son navire - je n'ai rien à dire.";
			link.l1 = "Et vous avez donné des manuscrits précieux à un capitaine sans même vous soucier de connaître le nom de son navire ?!!";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_2";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_2":
			dialog.text = "Voyez-vous, "+GetSexPhrase("mon fils","ma fille")+", capitaine "+PChar.GenQuest.ChurchQuest_1.CapFullName+" est très craignant Dieu...";
			link.l1 = "Eh bien, j'ai déjà entendu cela.";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_3";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_3":
			dialog.text = "Patience, "+GetSexPhrase("jeune homme","jeune dame")+" ! Capitaine "+PChar.GenQuest.ChurchQuest_1.CapFullName+" est une personne très pieuse, et jusqu'à ce jour, son navire portait un nom qu'un clergé ne devrait jamais prononcer même en pensée, encore moins à voix haute ! Et aujourd'hui, lors de sa confession, je le lui ai fait remarquer. Car, comme dit la Bible, la pureté de l'âme doit être préservée par nous, pécheurs, plus que la pureté du corps, car notre Seigneur refuse Son Royaume aux grossiers...";
			link.l1 = "Je vois, "+LinkRandPhrase("Père","Padre","Père")+", je vois ! "+PChar.GenQuest.ChurchQuest_1.CapFullName+", un notoire joueur et ivrogne, bien connu dans tous les Caraïbes, a décidé de renommer sa vieille barque sur votre suggestion ?";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_4";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_4":
			dialog.text = "Vous êtes très perspicace, "+GetSexPhrase("mon fils","ma fille")+"Je ne connais pas le nouveau nom de ce navire, mais c'est certainement quelque chose d'exaltant.";
			link.l1 = "Oh, "+RandPhraseSimple("Père","Padre","Père")+"... Merci pour tout. Et priez pour mon âme pécheresse...";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_5";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_5":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = NPChar.city;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "3_2");
			AddQuestUserData(sQuestTitle, "sCapName", PChar.GenQuest.ChurchQuest_1.CapFullName);
		break;
			
		case "GenQuest_Church_1_Complete_1":
			dialog.text = "Oh, mon enfant ! J'ai prié avec ferveur, et tout semble s'être résolu de la meilleure manière possible ! Pour votre aide et votre foi, "+GetSexPhrase("mon fils","ma fille")+", le paradis et le chant angélique vous attendront certainement...";
			link.l1 = RandPhraseSimple("Père.","Père.")+", je ne vais pas rencontrer Saint Pierre de sitôt, Dieu m'en garde. Quant aux vivants - ils ont besoin de bien des choses matérielles en plus des promesses de béatitude céleste...";
			link.l1.go = "GenQuest_Church_1_Complete_2";
		break;
			
		case "GenQuest_Church_1_Complete_2":
			dialog.text = "Oui, oui, "+GetSexPhrase("mon fils","ma fille")+", bien sûr. Je vous récompenserai comme il se doit. Tenez, prenez ceci et souvenez-vous que notre Seigneur punit ces âmes insensées, qui convoitent trop les bénédictions terrestres et vénèrent le diable jaune !";
			link.l1 = "Merci, "+LinkRandPhrase("Père","Padre","saint Père")+". S'il vous plaît, prenez vos livres et manuscrits tant attendus et priez pour mon âme pécheresse... Adieu !";
			link.l1.go = "GenQuest_Church_1_Complete_3";
		break;
			
		case "GenQuest_Church_1_Complete_3":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			RemoveItems(PChar, "Bible", 1);
			items[FindItem("Bible")].Name = "itmname_bible";
			BackItemDescribe("Bible");
			DeleteAttribute(items[FindItem("Bible")], "City");
			ChangeCharacterComplexReputation(PChar,"nobility", 5);
			AddCharacterExpToSkill(PChar, "Leadership", 50); // Бонус в авторитет
			AddCharacterExpToSkill(PChar, "Fortune", 50); // Бонус в удачу
			TakeNItems(pchar, "chest", 3+hrand(1));
			PlaySound("interface\important_item.wav");
			sQuestTitle = NPChar.City + "ChurchGenQuest1";
			characters[GetCharacterIndex("ChurchGenQuest1_Cap")].LifeDay = 0;
			Group_DeleteGroup("ChurchGenQuest1_CapGroup"); // Трем кэпа
			PChar.Quest.Church_GenQuest1_ChangeCapitanLocation.over = true; // Завершаем, если вдруг осталось
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "7");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			AddQuestUserData(sQuestTitle, "sSumm", FindRussianMoneyString(sti(PChar.GenQuest.ChurchQuest_1.AwardSumm)));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1");
			NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
			break;
		// <-- Church GenQuest_1

        case "healthAdd_1":
            if (stf(pchar.Health.maxHP) == 60.0) // отлично
            {
                dialog.text = "Votre santé est "+GetHealthNameMaxSmall(pchar)+", et les blessures se refermeront d'elles-mêmes. Vous devez simplement éviter l'effusion de sang et prendre soin de votre santé.";
    			link.l1 = "Merci, c'est sûrement un soulagement. Je vais essayer de m'abstenir de me battre pendant un certain temps.";
    			link.l1.go = "exit";
            }
            else
            {
    			dialog.text = "Votre santé est "+GetHealthNameMaxSmall(pchar)+", et bien que les blessures se refermeront d'elles-mêmes, tu devrais t'en occuper.";
    			link.l1 = "Que faut-il pour cela?";
    			link.l1.go = "healthAdd_2";
			}
			link.l2 = "Et pourquoi ma santé se dégrade-t-elle ?";
    		link.l2.go = "healthAdd_info";
		break;

		case "healthAdd_info":
			dialog.text = "C'est très simple, "+GetSexPhrase("mon fils","ma fille")+"Vous subissez des dégâts chaque fois que vous êtes blessé. Cela ne passe pas sans laisser de trace. Votre santé se dégrade à chaque blessure, et, par conséquent, vous devenez plus faible. Votre équipage, voyant un capitaine faible, perd le respect pour vous. Cependant, vous devenez plus prudent, et la capacité à vous défendre augmente temporairement. Le repos et la minimisation des blessures vous aideront à rester en pleine forme.";
			link.l1 = "Merci pour l'illumination.";
			link.l1.go = "exit";
		break;

		case "healthAdd_2":
			dialog.text = "Prières et abstinence de la violence, "+GetSexPhrase("mon fils","ma fille")+"Alors le Seigneur vous rendra ce que vous avez perdu.";
			link.l1 = "Mais pourriez-vous prier pour moi ?";
			link.l1.go = "healthAdd_3";
			link.l2 = "Alors il n'y a pas moyen ? Hmm... Tu m'as vraiment rassuré, merci.";
			link.l2.go = "exit";
		break;

		case "healthAdd_3":
            if (npchar.quest.HealthMonth != iMonth)
            {
    			dialog.text = "Moi ? Cela est probablement possible. Mais vous devrez faire un don à notre paroisse.";
    			link.l1 = pcharrepphrase("Combien?","Volontiers ! Combien ?");
    			link.l1.go = "healthAdd_4";
    			link.l2 = "Je suppose que je vais me débrouiller tout seul...";
    			link.l2.go = "exit";
			}
			else
			{
                dialog.text = ""+GetSexPhrase("Mon fils","Ma fille")+", je prie déjà pour votre bien-être. Ces prières occuperont tout mon temps jusqu'à la fin du mois.";
    			link.l1 = "Merci, "+RandPhraseSimple("père.","Saint Père.");
    			link.l1.go = "exit";
			}
		break;

		case "healthAdd_4":
			dialog.text = "Cent mille pesos seront un paiement suffisant pour le miracle de la guérison.";
			link.l1 = pcharrepphrase("Quoi ?!! Es-tu complètement fou ? Je paierais une telle somme seulement après avoir pillé quelques églises !","C'est trop pour moi. Comme on dit, la vérité - la santé ne s'achète pas avec de l'argent.");
			link.l1.go = "exit";
            if (sti(pchar.Money) >= 100000)
            {
    			link.l2 = "Je suis d'accord !";
    			link.l2.go = "healthAdd_5";
			}
		break;

		case "healthAdd_5":
            AddMoneyToCharacter(pchar, -100000);
            AddCharacterMaxHealth(pchar, 4); // можно не проверять, тк явно меньше 51
            npchar.quest.HealthMonth = iMonth;
			dialog.text = "D'accord. Votre santé s'améliorera un peu. Mais vous devez encore éviter les escarmouches et prendre bien soin de vous, sinon cet effet s'estompera. Je devrai passer un mois entier en prières pour votre corps périssable.";
			link.l1 = "Merci. Si quelque chose arrive, je reviendrai vous voir dans un mois.";
			link.l1.go = "exit";
		break;
		
		//квест пожертвования хозяйки борделя
		case "HostessChurch":
			dialog.text = "Et qui est cette âme charitable faisant un don d'argent ?";
			link.l1 = "Hmm... C'est la madame du bordel local.";
			link.l1.go = "HostessChurch_call";
			link.l2 = "Je préférerais garder les noms secrets. Il peut y avoir un don anonyme, n'est-ce pas ?";
			link.l2.go = "HostessChurch_notCall";
			pchar.questTemp.different = "HostessChurch_return"; //флаг на возвращение
		break;
		
		case "HostessChurch_call":
			if (isBadReputation(pchar, 5)) 
			{
				if (rand(100) < GetCharacterSkill(pchar, "Fortune")) //рендом вешаем на удачу
				{
					dialog.text = "Tu es un pécheur, mais pour un pécheur demandes-tu? Tu ferais mieux de penser à ton âme d'abord, en fait, nous comparaîtrons tous devant le Seigneur!";
					link.l1 = "C'est vrai. J'espère que notre Seigneur me sera clément... Alors, qu'en est-il de la donation ?";
					link.l1.go = "HostessChurch_ok";
				}
				else
				{
					dialog.text = "Arrière de moi, Satan!!! Prends ton argent impie et sors d'ici!";
					link.l1 = "Comment cela, Mon Père?! Nous sommes venus à vous le coeur ouvert, et vous...";
					link.l1.go = "HostessChurch_bad";
				}
			}
			else
			{
				if (rand(10) < GetCharacterSPECIAL(pchar, "Charisma")) //рендом вешаем на харизму
				{
					dialog.text = "Je suis heureux que vous aidiez les pécheurs à trouver leur chemin vers notre Seigneur. Pour cela, vous recevrez votre récompense au Ciel !";
					link.l1 = "Ce serait formidable ! Alors, qu'en est-il du don ?";
					link.l1.go = "HostessChurch_ok";
				}
				else
				{
					dialog.text = "Je ne peux pas accepter d'argent acquis dans le péché. Rends-le à cette femme déchue, "+GetSexPhrase("mon fils","ma fille")+". Personne ne peut trouver le chemin vers Dieu à travers l'argent.";
					link.l1 = "C'est dommage que vous la rejetiez. Quel dommage en effet.";
					link.l1.go = "HostessChurch_bad_1";
				}
			}
		break;
		
		case "HostessChurch_notCall":
			if (rand(10) < GetCharacterSPECIAL(pchar, "Charisma"))
			{
				dialog.text = "Prendre cet argent, sans même savoir d'où il vient...";
				link.l1 = "Oui, padre, exactement. Je vous prie d'accepter cette contribution, faite de tout coeur !";
				link.l1.go = "HostessChurch_ok_1";
			}
			else
			{
				dialog.text = "Prendre cet argent, sans même savoir d'où il vient ? Êtes-vous fou ?! Et si cet argent est tâché de sang !";
				link.l1 = "Mon père, tout l'argent est teinté de sang...";
				link.l1.go = "HostessChurch_bad_2";
			}
		break;

		case "HostessChurch_ok":
			dialog.text = "Je l'accepte, "+GetSexPhrase("mon fils","ma fille")+". Va dire cela à ta femme déchue.";
			link.l1 = "Très bien, padre. Merci.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.HostessChurch.money));
			AddCharacterExpToSkill(pchar, "Fortune", 20);
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "yes";
		break;
		
		case "HostessChurch_ok_1":
			dialog.text = "Je l'accepte, "+GetSexPhrase("mon fils","ma fille")+"Parlez-en à votre bienfaiteur.";
			link.l1 = "Très bien, mon père. Merci.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.HostessChurch.money));
			AddCharacterExpToSkill(pchar, "Fortune", 20);
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "yes";
		break;
		
		case "HostessChurch_bad":
			dialog.text = "Sors, rejeton de l'Enfer, et n'ose plus jamais montrer ton visage ici !";
			link.l1 = "Eh bien, comme vous le souhaitez.";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			npchar.quest.BadMeeting = lastspeak_date;
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;
		
		case "HostessChurch_bad_1":
			dialog.text = "C'est ma décision. Allez en paix, "+GetSexPhrase("mon fils","ma fille")+".";
			link.l1 = "Adieu, padre.";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;
		
		case "HostessChurch_bad_2":
			dialog.text = "Tu penses cela, blasphémateur ?! Quitte le temple sur-le-champ et n'ose plus montrer ton visage ici !";
			link.l1 = "Oh, vraiment ? Peu importe, je m'en vais...";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 40);
			npchar.quest.BadMeeting = lastspeak_date;
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;

		//--> Jason Церковная депеша
		case "Monkletter":
			if (CheckAttribute(pchar, "GenQuest.Monkletter.Late"))
			{
				dialog.text = "J'avais presque perdu espoir de revoir ces documents. Pourquoi as-tu mis tant de temps, mon fils ?";
				link.l1 = "C'était... des développements imprévus, Père.";
				link.l1.go = "Monkletter_1";
			}
			else
			{
				dialog.text = "J'attendais ces papiers, mon fils. Merci pour la livraison rapide. Je te prie d'accepter ces pièces et pars avec ma bénédiction.";
				link.l1 = "Merci, Père. Ce fut un plaisir d'aider la Sainte Église !";
				link.l1.go = "Monkletter_3";
			}
		break;
		
		case "Monkletter_1":
			dialog.text = "Nous sommes tous entre les mains de Dieu, mon fils... L'homme propose, mais Dieu dispose. Remets-moi ces papiers et pars en paix.";
			link.l1 = "Voici pour vous, mon père. Tout le meilleur pour vous !";
			link.l1.go = "Monkletter_2";
		break;
		
		case "Monkletter_2":
			DialogExit();
			RemoveItems(PChar, "letter_church", 1);//заменить на нужный
			AddQuestRecord("Monkletter", "2");
			CloseQuestHeader("Monkletter");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			DeleteAttribute(pchar, "GenQuest.Monkletter");
		break;
		
		case "Monkletter_3":
			dialog.text = "Bénédiction de Dieu, mon fils. Que le Tout-Puissant veille sur vous dans vos voyages !";
			link.l1 = "Adieu, Père.";
			link.l1.go = "Monkletter_4";
		break;
		
		case "Monkletter_4":
			pchar.quest.Monkletter_Over.over = "yes"; //снять таймер
			DialogExit();
			RemoveItems(PChar, "letter_church", 1);//заменить на нужный
			AddQuestRecord("Monkletter", "3");
			CloseQuestHeader("Monkletter");
			TakeNItems(pchar, "gold_dublon", 10+rand(5));
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 5);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			DeleteAttribute(pchar, "GenQuest.Monkletter");
			addLiberMisBonus();
		break;
		//<-- Церковная депеша
		
		//--> Jason Доставить молитвенники
		case "Churchbooks":
			dialog.text = "Vous avez été envoyé pour prendre des livres de prières chez nous - pour l'église de "+XI_ConvertString("Colonie"+pchar.GenQuest.Churchbooks.StartCity+"Gen")+"? Eh bien. J'ai un colis contenant trente livres de prières. Prends-le, mon fils.";
			link.l1 = "Merci, padre. Au revoir !";
			link.l1.go = "Churchbooks_1";
		break;
		
		case "Churchbooks_1":
			dialog.text = "Que le Seigneur veille sur vous lors de vos voyages ! Allez en paix...";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddQuestRecord("Churchbooks", "2");
			pchar.GenQuest.Churchbooks = "return";
			GiveItem2Character(pchar, "prayer_book");//поставить соотв.предмет
		break;
		
		case "Churchbooks_2":
			if (CheckAttribute(pchar, "GenQuest.Churchbooks.Late"))
			{
				dialog.text = "Merci pour votre aide, mon fils, bien qu'elle soit arrivée avec un certain retard.";
				link.l1 = "J'ai été retardé par des événements imprévus, Père.";
				link.l1.go = "Churchbooks_3";
			}
			else
			{
				dialog.text = "Merci pour ton aide, mon fils. Tu as apporté ces livres juste à temps. S'il te plaît, accepte cet amulette sanctifiée en récompense - elle te sauvera du danger à l'heure la plus sombre.";
				link.l1 = "Merci, mon Père. Ce fut un plaisir d'aider la Sainte Église !";
				link.l1.go = "Churchbooks_4";
			}
		break;
		
		case "Churchbooks_3":
			dialog.text = "Tout est entre les mains de Dieu, mon fils. Va en paix !";
			link.l1 = "Adieu, padre.";
			link.l1.go = "exit";
			RemoveItems(PChar, "prayer_book", 1);//заменить на нужный
			AddQuestRecord("Churchbooks", "3");
			CloseQuestHeader("Churchbooks");
			DeleteAttribute(pchar, "GenQuest.Churchbooks");
		break;
		
		case "Churchbooks_4":
			dialog.text = "Que Dieu te bénisse, mon fils. Que le Tout-Puissant te protège du mal sur tes chemins !";
			link.l1 = "Adieu, Mon Père.";
			link.l1.go = "Churchbooks_5";
		break;
		
		case "Churchbooks_5":
			pchar.quest.Churchbooks_Over.over = "yes"; //снять таймер patch-5
			DialogExit();
			RemoveItems(PChar, "prayer_book", 1);//заменить на нужный
			GiveItem2Character(pchar, pchar.GenQuest.Churchbooks.Item);
			Log_Info("You have received '"+XI_ConvertString(pchar.GenQuest.Churchbooks.Item)+"'");
			AddQuestRecord("Churchbooks", "4");
			CloseQuestHeader("Churchbooks");
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 1);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			DeleteAttribute(pchar, "GenQuest.Churchbooks");
			addLiberMisBonus();
		break;
	}
}

void ChurchGenQuest2_RemoveCup()
{
	RemoveItems(PChar, "Bible", 1);
	ref rItem = ItemsFromID("Bible");
	DeleteAttribute(rItem, "City");
	rItem.Weight = 2;
	rItem.Name = "itmname_Bible";
	rItem.picIndex = 6;
	rItem.picTexture = "ITEMS_9";
	BackItemDescribe("Bible");
}

void Church_GenQuest1_InitStartParam(ref chr)
{
	string sColony = SelectNotEnemyColony(chr); 
	PChar.GenQuest.ChurchQuest_1.IslandId = colonies[FindColony(PChar.GenQuest.ChurchQuest_1.QuestTown)].Island;
	PChar.GenQuest.ChurchQuest_1.ToColony = sColony;
	PChar.GenQuest.ChurchQuest_1.ToIsland = colonies[FindColony(sColony)].Island;
	PChar.GenQuest.ChurchQuest_1.ToName = characters[GetCharacterIndex(sColony + "_Priest")].Name;
	
	// Чтоб жизнь медом не казалась... Какие сцены будут в квесте, определяем в самом начале.
	int iRand = Rand(2);
	switch(iRand)
	{
		case "0":
			PChar.GenQuest.ChurchQuest_1.2A_Scene = true;
			Log_TestInfo("Church generator 1: key scene - 2A (just pick up the manuscript from the priest)."); 
		break;
		
		case "1":
			PChar.GenQuest.ChurchQuest_1.2BA_Scene = true;
			Log_TestInfo("Church generator 1: key scene - 2B-A (search for a cap. There is full information about him).");
		break;
		
		case "2": // Этот флаг уже не проверяем, т.к. если нет тех, что выше, по-любому есть этот
			PChar.GenQuest.ChurchQuest_1.2BB_Scene = true;
			Log_TestInfo("Church generator 1: key scene - 2B-B (search for a cap. The name of the ship is unknown)."); 
		break;
	}
}
