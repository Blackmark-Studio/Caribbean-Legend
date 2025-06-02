//Jason общий диалог дворян
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp, iTest;
	string sTemp, sTitle;
	float locx, locy, locz;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	iTest = FindColony(NPChar.City); // 170712
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			//--> проверка межнациональных отношений
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
				dialog.text = NPCStringReactionRepeat("Hm. Vous naviguez sous le pavillon de "+NationNameGenitive(sti(pchar.nation))+", matelot. Que diable fais-tu ici, dans notre ville? Déguerpis!","Je ne veux pas être soupçonné d'être un ami de "+NationNameAblative(sti(pchar.nation))+"Va-t'en ou je te dénonce aux gardes !","C'est ta dernière chance de t'enfuir. Sinon, tu ne pourras t'en prendre qu'à toi-même.","Je t'ai prévenu. Maintenant, tu vas payer pour ton insolence, salaud !","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Un tel patriote, ha !","D'accord, d'accord, calme-toi. Je m'en vais.","Ne fais pas tant de bruit. Je m'en vais.","Quoi?!",npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			break;
			}
			
			//--> проверка репутации - дворяне гнобят супернегодяев
			if (sti(pchar.reputation.nobility) < 10)
			{
				dialog.text = NPCStringReactionRepeat("Regardez-moi ça ! Et comment nos gardes laissent-ils un salaud comme vous se promener en ville ? Impossible...","Fiche le camp, je n'ai même pas envie de te parler ! Bourreau...","C'est ta dernière chance de t'enfuir. Sinon, tu ne pourras t'en prendre qu'à toi-même.","Je t'ai averti. Maintenant tu vas payer pour ton insolence, salaud !","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Eh eh ! Montrez-moi plus de respect, monsieur !","Regarde-toi, saint...","Calme-toi...","Quoi?!",npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			break;
			}
			
			//--> диалог первой встречи
            if(NPChar.quest.meeting == "0")
			{
				// проверка наличия корабля в порту
				bool ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
				if (ok && sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Noblepassenger") && CheckAttribute(pchar, "questTemp.StatusCity") && pchar.questTemp.StatusCity == npchar.city)//дворянин-пассажир
				{
					dialog.text = "Salutations, "+GetAddress_Form(NPChar)+"Je vois que vous êtes capitaine d'un navire solide. Je veux vous demander de faire quelque chose. Vous pouvez l'accepter ou le refuser.";
					link.l1 = "Je vous écoute, "+GetAddress_FormToNPC(NPChar)+"Que veux-tu dire ?";
					link.l1.go = "passenger";
					link.l2 = "Pardonnez-moi, "+GetAddress_FormToNPC(NPChar)+", mais je suis pressé.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				if (ok && sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Noblepassenger") && 4-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0 && or(IsUniversalShipType(pchar), IsMerchantShipType(pchar)))//дворянин-пассажир
				{
					dialog.text = "Salutations, "+GetAddress_Form(NPChar)+". Je vois que vous êtes le capitaine d'un solide navire. Je veux vous demander de faire quelque chose. Vous pouvez accepter ou refuser.";
					link.l1 = "Je vous écoute, "+GetAddress_FormToNPC(NPChar)+"Que veux-tu dire ?";
					link.l1.go = "passenger";
					link.l2 = "Pardonnez-moi, "+GetAddress_FormToNPC(NPChar)+", mais je suis pressé.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				if (CheckAttribute(npchar, "quest.donation"))//клянчит деньги
				{
					dialog.text = "Aha, c'est bon de voir un gentilhomme dans notre petite ville ! Je suis sûr que vous venez tout juste d'Europe. Écoutez, je veux vous demander de m'aider - de gentilhomme à gentilhomme. J'espère que vous me comprendrez correctement.";
					link.l1 = "Bonne journée à vous, monsieur. Je vous écoute.";
					link.l1.go = "donation";
					npchar.quest.meeting = "1";
					break;
				}
				if (CheckAttribute(npchar, "quest.lombard") && !CheckAttribute(pchar, "GenQuest.Noblelombard"))//семейная реликвия
				{
					dialog.text = "Bonne journée, "+GetAddress_Form(NPChar)+" ! C'est un plaisir de rencontrer un gentilhomme dans les rues de notre ville ! Me permettrez-vous de vous prendre quelques minutes ?";
					link.l1 = "Bien sûr, monsieur. Je vous écoute.";
					link.l1.go = "lombard";
					npchar.quest.meeting = "1";
					break;
				}
				if (CheckAttribute(npchar, "quest.slaves") && !CheckAttribute(&Colonies[FindColony(npchar.city)], "questslaves"))//привезти рабов
				{
					dialog.text = "Bonne journée à vous, capitaine ! Je suis heureux de vous voir car vous avez l'air d'un homme capable de résoudre des problèmes.";
					link.l1 = "Ça dépend du problème. Je suis spécialisé dans leur résolution par la violence, c'est ce que tu cherches, "+GetAddress_FormToNPC(NPChar)+"?";
					link.l1.go = "slaves";
					npchar.quest.meeting = "1";
					break;
				}
				dialog.text = RandPhraseSimple("Bonjour, "+GetAddress_Form(NPChar)+"Veux-tu quelque chose de moi ?","Que voulez-vous, monsieur ?");
				link.l1 = TimeGreeting()+", "+GetAddress_FormToNPC(NPChar)+"Je ne prendrai pas beaucoup de votre temps, je veux juste demander...";
				link.l1.go = "question";
				link.l2 = RandPhraseSimple("J'ai besoin d'informations sur votre colonie.","J'ai besoin d'informations.");
				link.l2.go = "quests";//(перессылка в файл города)
				npchar.quest.meeting = "1";
				
				//==> прибыла инспекция на Святом Милосердии
				if (CheckAttribute(pchar, "questTemp.SantaMisericordia.ColonyZapret") && pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_town")
				{
					dialog.Text = LinkRandPhrase(LinkRandPhrase("La ville entière est en émoi - don Fernando de Alamida, l'inspecteur royal, est arrivé. Vous savez, j'ai vu beaucoup de choses ici, mais ça... Ce n'est pas le chagrin qui change les gens, mais la façon dont ils le gèrent. On dit qu'il est devenu un autre homme après la mort de son père. Maintenant, vous ne trouverez pas un serviteur de la Couronne plus incorruptible et... impitoyable dans tout l'archipel.","Regardez donc le 'Sainte Miséricorde' ! On dit que le roi lui-même a ordonné sa construction selon des plans spéciaux. Et remarquez - pas une seule égratignure. Comme si la Vierge Marie elle-même la protégeait. Bien que j'aie entendu des rumeurs... peut-être que ce n'est pas la Vierge du tout.","Vous savez combien de fois ils ont essayé de tuer don Fernando ? Douze attaques en pleine mer - et c'est juste l'année dernière ! Eh bien, avec un équipage aussi loyal et entraîné, et sous la protection du Seigneur - il survivra aussi à la treizième !"),LinkRandPhrase("As-tu entendu? Don Fernando de Alamida est arrivé dans notre ville, et on dit qu'il est quelque part dans les rues en ce moment. J'aimerais bien le voir de mes propres yeux...","Un homme compliqué, ce don Fernando. Certains disent qu'il est un sauveur, purifiant la Mère-Patrie des immondices. D'autres murmurent que quelque chose s'est brisé en lui après la mort de son père et que bientôt nous pleurerons tous. Mais je vais te dire ceci : ne le crains pas. Crains ceux qui l'ont fait devenir ce qu'il est.","Quel homme séduisant, ce don Fernando ! Mais savez-vous ce qui est étrange ? C'est comme s'il ne remarquait personne. Tout pour le devoir et le service. J'ai entendu dire qu'il y avait une fille... mais après avoir rencontré un prêtre, il a complètement rejeté les plaisirs mondains. Comme s'il avait fait un vœu."),RandPhraseSimple(RandPhraseSimple("Maudit inspecteur ! Tant qu'il est là, la ville est comme morte. Pas de commerce, pas de divertissement. Même respirer, on dirait, doit être plus silencieux. Et tu sais ce qui est le plus effrayant ? C'est pareil dans chaque port. Comme un mécanisme d'horlogerie. Sa Majesté Royale n'aurait pas pu inventer délibérément ce supplice pour nous tous !","Don Fernando a de nouveau rendu visite à l'orphelinat. Il fait des dons généreux, prie pendant des heures. Un homme aussi digne devrait être tenu en exemple pour ces maudits détourneurs de fonds !"),RandPhraseSimple("Ha ! Le 'saint' Fernando a encore fermé tous les bordels. Eh bien, peu importe, il partira bientôt et ils rouvriront aussitôt.","L'inspect... l'inspecteur est arrivé, voilà ce que c'est ! Don Fernando de Almeyda, ou, comment il s'appelle, Alamida ! Tellement important que le gouverneur lui-même marche sur la pointe des pieds autour de lui. On dit qu'il te regarde dans les yeux et voit tous tes péchés immédiatement. Terrifiant !")));
					link.l1 = "...";
					link.l1.go = "exit";
					DeleteAttribute(link, "l2");
				}
				//<== прибыла инспекция на Святом Милосердии
				//==> Леди Бет в порту города
				if (CheckAttribute(pchar, "questTemp.LadyBeth.CaptainInColony") && pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_town")
				{
					dialog.Text = findLedyBethRumour(npchar);
					link.l1 = "...";
					link.l1.go = "exit";
					DeleteAttribute(link, "l2");
				}
				//<== Леди Бет в порту города
			}
			else //--> повторные обращения
			{
				dialog.text = NPCStringReactionRepeat("Quoi? Encore? Je n'ai pas le temps pour toi. Cherche quelqu'un d'autre à qui parler. Il y a plein de manants qui se promènent dans les rues. Et je dois y aller, il y aura un banquet ce soir à la résidence du gouverneur et je dois préparer ma tenue...","Non, maintenant c'est vraiment agaçant ! Tu ne comprends pas ? Ou es-tu lent d'esprit ?","Monsieur, je commence à soupçonner que vous n'êtes pas seulement un idiot, mais aussi un rustre et un goujat. Je vous avertis, laissez-moi tranquille ou vous le regretterez de m'avoir importuné.","Assez. Je vais t'apprendre, insolent !","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Je vois. Adieu.","Oui-oui, j'ai juste oublié ce que je voulais demander...","Vous m'avez mal compris...","Quoi?!",npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			}
			NextDiag.TempNode = "First time";
		break;

		case "question":
			dialog.text = LinkRandPhrase("Continuez.","Que veux-tu ?","Des questions ? Très bien, matelot, je t'écoute.");
			link.l1 = LinkRandPhrase("Ne me diriez-vous pas les derniers potins de votre ville ?","A-t-il arrivé quelque chose d'intéressant ici récemment ?","Des nouvelles des Caraïbes, monsieur ?");
			link.l1.go = "rumours_nobleman";
			NextDiag.TempNode = "First time";
		break;

//--------------------------------------------дворянин-пассажир---------------------------------------------------
		case "passenger":
			if (hrand(19) > 9) SetPassengerParameter("Noblepassenger", false);
			else SetPassengerParameter("Noblepassenger", true);
			if (!CheckAttribute(pchar, "GenQuest.Noblepassenger.Enemycity"))
			{
				dialog.text = ""+GetSexPhrase("Monsieur","Madame")+", j'ai besoin de me rendre à la colonie"+XI_ConvertString("Colony"+pchar.GenQuest.Noblepassenger.City+"Acc")+", dès que possible c'est sur "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Noblepassenger.City)+"Voc")+", pour "+FindRussianDaysString(sti(pchar.GenQuest.Noblepassenger.DaysQty))+". Ton navire semble robuste et rapide comparé à la majorité de ces petites barques qui voguent ici. Je peux te payer "+FindRussianMoneyString(sti(pchar.GenQuest.Noblepassenger.Money))+". Que dirais-tu ?"; // belamour gen
			}
			else
			{
				dialog.text = "Bonjour, "+GetSexPhrase("monsieur","madame")+"! J'ai besoin d'aller à "+XI_ConvertString("Colony"+pchar.GenQuest.Noblepassenger.City+"Acc")+"! C'est sur "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Noblepassenger.City)+"Voc")+", au fait. Oui, oui, je sais - ces salauds attendent juste que nous nous montrions là-bas. Mais j'ai une réunion très urgente et importante là-bas ! Je ne suis pas une personne avare - bien que je n'aime pas payer, je paie toujours. Laissez tomber tout ce que vous faites, et dès que nous arrivons, je vous donnerai "+FindRussianDublonString(sti(pchar.GenQuest.Noblepassenger.Money))+".";
			}
			link.l1 = "Hm. Je me dirige aussi par là, donc je suis prêt à vous prendre à bord selon ces termes.";
			link.l1.go = "passenger_1";
			link.l2 = "Je suis désolé, "+GetAddress_FormToNPC(NPChar)+", mais je navigue dans une direction différente. Je ne peux pas vous aider.";
			link.l2.go = "passenger_exit";
		break;
		
		case "passenger_exit":
			dialog.text = "Quel dommage. Eh bien, j'attendrai un autre navire. Adieu.";
			link.l1 = "Au revoir.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Noblepassenger");
		break;
		
		case "passenger_1":
			dialog.text = "Parfait ! Je suis fatigué d'attendre. Vous recevrez votre paiement quand nous y serons.";
			link.l1 = "Va à mon navire, "+GetAddress_FormToNPC(NPChar)+". Nous partons bientôt.";
			link.l1.go = "passenger_2";
		break;
		
		case "passenger_2":
			DialogExit();
			pchar.GenQuest.Noblepassenger.id = npchar.id;
			LAi_SetImmortal(npchar, true);
			DeleteAttribute(npchar, "LifeDay");
			LAi_RemoveLoginTime(npchar);
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sTitle = npchar.index+"Citizpassenger";

// LDH 13Sep17 - do not add to an existing Citizpassenger record -->
// "Rename" the quest record by copying it to a new name and deleting the old record
			if (CheckAttribute(pchar, "questinfo."+sTitle))
			{
				string sTempLDH = frand(1);
				sTempLDH = strcut(sTempLDH, 2, 5);    // 4 random digits
				string sTitle1 = sTitle+sTempLDH;

				aref arTo, arFrom;
				makearef(arFrom, pchar.questinfo.(sTitle));
				makearef(arTo,   pchar.questinfo.(sTitle1));
				CopyAttributes(arTo, arFrom);
				pchar.questinfo.(sTitle1) = "";

				DeleteAttribute(pchar, "questinfo."+sTitle);

				Trace("Duplicate Citizpassenger record "+sTitle+" copied to "+sTitle1+" **");
			}
// <--

			AddQuestRecordEx(sTitle, "Citizpassenger", "1");
			AddQuestUserDataForTitle(sTitle, "sType", "nobleman");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			sTemp = XI_ConvertString("Colony" +pchar.GenQuest.Noblepassenger.City+"Gen") + ", at " + XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Noblepassenger.City)+"Dat")+".";
			AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sDays", FindRussianDaysString(sti(pchar.GenQuest.Noblepassenger.DaysQty)));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
            if (!CheckAttribute(pchar, "GenQuest.Noblepassenger.Enemycity")) AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Noblepassenger.Money)));
			else AddQuestUserData(sTitle, "sMoney", FindRussianDublonString(sti(pchar.GenQuest.Noblepassenger.Money)));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			pchar.quest.Noblepassenger.win_condition.l1 = "location";
			pchar.quest.Noblepassenger.win_condition.l1.location = pchar.GenQuest.Noblepassenger.City+"_town";
			pchar.quest.Noblepassenger.function = "Noblepassenger_complete";
			SetFunctionTimerCondition("Noblepassenger_Over", 0, 0, sti(pchar.GenQuest.Noblepassenger.DaysQty), false);
		break;
		
		case "passenger_3":
			pchar.quest.Noblepassenger_Over.over = "yes"; //снять таймер
			dialog.text = "Nous y voilà, très excellent ! Voyager sur votre navire fut fort satisfaisant. Vous avez un équipage discipliné et des ponts propres ! Mes remerciements. Prenez votre argent, monsieur.";
			link.l1 = "Bonne chance, "+GetAddress_FormToNPC(NPChar)+"Adieu.";
			link.l1.go = "passenger_4";
		break;
		
		case "passenger_4":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			npchar.lifeday = 0;
			RemovePassenger(Pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
			OfficersReaction("good");				
			AddCharacterExpToSkill(pchar, "Sailing", 80);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			if (CheckAttribute(pchar, "GenQuest.Noblepassenger.Enemycity"))
			{
				AddCharacterExpToSkill(pchar, "Sneak", 50);
				TakeNItems(pchar, "gold_dublon", sti(pchar.GenQuest.Noblepassenger.Money));
			}
			else AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Noblepassenger.Money));
			sTitle = npchar.index+"Citizpassenger";
			AddQuestRecordEx(sTitle, "Citizpassenger", "3");
			CloseQuestHeader(sTitle);
			DeleteAttribute(Pchar, "GenQuest.Noblepassenger");
		break;
//<-- дворянин-пассажир

//-------------------------------------------------помощь деньгами------------------------------------------------
		case "donation":
			sTemp = DonationText();
			dialog.text = "J'ai une affaire assez délicate..."+sTemp+" J'ai besoin d'argent maintenant ou je suis dans de beaux draps. Je ne demanderais jamais normalement de l'argent à un autre gentilhomme, mais la situation est vraiment mauvaise.";
			link.l1 = "Combien as-tu besoin ?";
			link.l1.go = "donation_1";
		break;
		
		case "donation_1":
			iTemp = hrand(4)+1;
			pchar.GenQuest.Nobledonation.Money = iTemp*1000+rand(iTemp)*150;
			dialog.text = "La somme est assez petite, c'est "+FindRussianMoneyString(sti(pchar.GenQuest.Nobledonation.Money))+"Alors, quoi, pouvez-vous m'aider ?";
			if (sti(pchar.money) >= sti(pchar.GenQuest.Nobledonation.Money))
			{
				link.l1 = "Oui, bien sûr. Prenez-le.";
				link.l1.go = "donation_2";
			}
			link.l2 = "Je serais heureux de t'aider, mais mes poches sont vides aussi - pas un seul peso de rechange.";
			link.l2.go = "donation_exit";
		break;
		
		case "donation_exit":
			DialogExit();
			ChangeOfficersLoyality("bad_all", 1);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.Nobledonation");
		break;
		
		case "donation_2":
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Nobledonation.Money));
			dialog.text = "Ma gratitude, "+GetAddress_Form(NPChar)+" ! Vous m'avez sauvé ! J'ai des amis à la résidence du gouverneur et je leur parlerai de votre générosité. Mille mercis encore !";
			link.l1 = "Je vous en prie, monsieur. Je suis sûr que vous feriez de même pour moi.";
			link.l1.go = "donation_3";
		break;
		
		case "donation_3":
			DialogExit();
			ChangeOfficersLoyality("good_all", rand(2)+1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), rand(1)+2);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.Nobledonation");
		break;
//<-- помощь деньгами

//-------------------------------------------------семейная реликвия---------------------------------------------
		case "lombard":
			LombardText();
			dialog.text = "J'ai besoin de votre aide. Vous êtes riche et un gentilhomme, alors j'espère que vous comprendrez. J'avais grand besoin d'argent il n'y a pas longtemps, alors j'ai dû aller chez le banquier pour mettre en gage "+pchar.GenQuest.Noblelombard.Item+"\nIl a proposé de bonnes conditions. Dix pour cent par mois, sur trois mois au total. Mais le temps est écoulé et je n'ai pas l'argent pour racheter l'objet en raison d'un cours des événements malheureux\nMaintenant, il dit qu'il a trouvé un acheteur pour "+pchar.GenQuest.Noblelombard.Item+" et il va le vendre si je ne rembourse pas immédiatement ma dette et les intérêts. Mais je n'ai pas beaucoup d'argent en ce moment, et l'objet que j'ai mis en gage est très cher...";
			link.l1 = "Et comment puis-je vous aider avec cela, "+GetAddress_FormToNPC(NPChar)+"?";
			link.l1.go = "lombard_1";
		break;
		
		case "lombard_1":
			dialog.text = "Je vous demande de parler à notre banquier. Offrez-lui de l'argent, garantissez pour moi... ou faites autre chose. Malheureusement, je n'ai personne à qui demander, tous mes bons amis sont soudainement devenus 'en faillite'. Dans trois mois "+pchar.GenQuest.Noblelombard.Text+", et je vous rembourserai tous vos frais, doublement ! Vous avez ma parole de gentilhomme !";
			link.l1 = "D'accord, je vais essayer de vous aider dans ce cas.";
			link.l1.go = "lombard_2";
			link.l2 = "Malheureusement, je suis aussi 'ruiné' en ce moment. Alors je ne peux pas vous aider, je suis vraiment désolé !";
			link.l2.go = "lombard_exit";
		break;
		
		case "lombard_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.Noblelombard");
		break;
		
		case "lombard_2":
			dialog.text = "Merci pour votre compréhension. Je vous attendrai à la taverne. Venez-y dès que possible.";
			link.l1 = "...";
			link.l1.go = "lombard_3";
		break;
		
		case "lombard_3":
			DialogExit();
			pchar.GenQuest.Noblelombard = "true"
			pchar.GenQuest.Noblelombard.Name = GetFullName(npchar);
			pchar.GenQuest.Noblelombard.id = npchar.id;
			pchar.GenQuest.Noblelombard.City = npchar.city;
			pchar.GenQuest.Noblelombard.Money = 20000+hrand(60)*500;
			pchar.GenQuest.Noblelombard.Percent = makeint(sti(pchar.GenQuest.Noblelombard.Money)*0.3);
			pchar.GenQuest.Noblelombard.Summ = sti(pchar.GenQuest.Noblelombard.Money)+sti(pchar.GenQuest.Noblelombard.Percent);
			pchar.GenQuest.Noblelombard.Chance = hrand(9);
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_SetActorType(npchar);
			LAi_RemoveLoginTime(npchar);
			DeleteAttribute(npchar, "CityType");//удалить признак фантома
			FreeSitLocator(pchar.GenQuest.Noblelombard.City + "_tavern", "sit1");
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", pchar.GenQuest.Noblelombard.City+"_tavern", "sit", "sit1", "Nobleman_lombardTavern", 10);
			SetFunctionTimerCondition("Noblelombard_Over", 0, 0, 1, false); //таймер до конца суток
			ReOpenQuestHeader("Noblelombard");
			AddQuestRecord("Noblelombard", "1");
			AddQuestUserData("Noblelombard", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Noblelombard.City));
			AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
		break;
		
		case "lombard_4":
			if (CheckAttribute(pchar, "GenQuest.Noblelombard.Regard"))
			{
				pchar.quest.Noblelombard_Over.over = "yes"; //снять таймер
				dialog.text = "Que peux-tu dire, "+GetAddress_Form(NPChar)+"Avez-vous été à la banque ? Des bonnes nouvelles ou des mauvaises ?";
				if (pchar.GenQuest.Noblelombard == "full") link.l1 = "Je l'ai fait. J'ai remboursé toutes vos dettes. Vous pouvez y aller et récupérer votre relique.";
				if (pchar.GenQuest.Noblelombard == "maxpercent") link.l1 = "Je l'ai fait. J'ai remboursé tous les intérêts des trois derniers mois et même pour les trois prochains. Vous pouvez attendre votre argent en toute sécurité. N'oubliez pas de rembourser votre dette principale dans trois mois.";
				if (pchar.GenQuest.Noblelombard == "minpercent") link.l1 = "Je l'ai fait. J'ai remboursé tous les intérêts des trois derniers mois. Le banquier a accepté d'attendre trois mois de plus jusqu'à ce que vous obteniez la somme totale.";
				link.l1.go = "lombard_5";
			break;
			}
			if (pchar.GenQuest.Noblelombard == "fail")
			{
				dialog.text = "Que peux-tu dire, "+GetAddress_Form(NPChar)+"? Es-tu allé à la banque? A des bonnes nouvelles ou des mauvaises?";
				link.l1 = "Je l'ai fait. Cet avare a demandé une somme incroyable. Il a rejeté toutes les demandes de concessions et je n'ai pas la somme requise. Donc, je n'ai pas pu vous aider. Désolé.";
				link.l1.go = "lombard_fail";
			}
			else
			{
				dialog.text = "Que peux-tu dire, "+GetAddress_Form(NPChar)+"? As-tu ete a la banque? As-tu de bonnes nouvelles ou de mauvaises?";
				link.l1 = "Je m'en charge. Attends.";
				link.l1.go = "exit";
				NextDiag.TempNode = "lombard_4";
			}
		break;
		
		case "lombard_fail":
			pchar.quest.Noblelombard_Over.over = "yes"; //снять таймер
			dialog.text = "Bof, "+GetAddress_Form(NPChar)+"... Maintenant vous êtes aussi témoin de l'avidité irrépressible de ces maudits usuriers assoiffés de sang. Par Dieu monsieur, ils font honte aux Juifs ! Souvenez-vous de cela quand vous essayerez d'emprunter de l'argent à eux comme je l'ai fait. Merci d'avoir essayé au moins...";
			link.l1 = "Je ne les ai jamais aimés. Eh bien, qui aime les usuriers ? Je suis désolé, "+GetAddress_FormToNPC(NPChar)+"Adieu.";
			link.l1.go = "lombard_fail_1";
		break;
		
		case "lombard_fail_1":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Noblelombard", "4");
			AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
			CloseQuestHeader("Noblelombard");
			sld = characterFromId(pchar.GenQuest.Noblelombard.City+"_usurer");
			DeleteAttribute(sld, "quest.noblelombard");
			DeleteAttribute(Pchar, "GenQuest.Noblelombard");
		break;
		
		case "lombard_5":
			dialog.text = "Incroyable ! Vous m'avez juste sauvé, "+GetAddress_Form(NPChar)+"Je ne l'oublierai jamais. Je vous assure que tous vos frais vous seront remboursés au double. Venez voir notre banquier dans trois mois. J'ouvrirai un dépôt à votre nom.";
			link.l1 = "Très bien, je ferai comme tu dis. À bientôt !";
			link.l1.go = "lombard_6";
		break;
		
		case "lombard_6":
			dialog.text = "Merci encore, capitaine. Bonne chance !";
			link.l1 = "...";
			link.l1.go = "lombard_7";
		break;
		
		case "lombard_7":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeOfficersLoyality("good_all", 1);
			AddQuestRecord("Noblelombard", "5");
			AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
			SetFunctionTimerCondition("Noblelombard_Regard", 0, 0, 90, false); //таймер
		break;
//<-- семейная реликвия

//------------------------------------------привезти рабов под заказ--------------------------------------------
		case "slaves":
			npchar.quest.slaves.price = 3+hrand(1);//цена на рабов в дублонах
			npchar.quest.slaves.qty = 50+hrand(5)*10;//количество
			npchar.quest.slaves.money = sti(npchar.quest.slaves.qty)*sti(npchar.quest.slaves.price);
			dialog.text = "Je possède un "+LinkRandPhrase("usine","mien","plantation")+"et j'ai toujours besoin d'esclaves frais. Le climat les épuise vraiment. En ce moment, j'ai besoin de"+sti(npchar.quest.slaves.qty)+"tetes. Je suis pret a commander un lot d'entre elles. Je paierai de l'or pour chaque tete, "+sti(npchar.quest.slaves.price)+" doubloons\nPas de précipitation, je ne te limiterai pas dans le temps si tu obtiens ce dont j'ai besoin. Eh bien, dans la mesure du raisonnable bien sûr, ne le prolonge pas plus de six mois. Alors, qu'en dis-tu? Marché conclu?";
			link.l1 = "Marché conclu ! La traite des esclaves est une affaire sale, mais cela vaut le risque.";
			link.l1.go = "slaves_1";
			link.l2 = "Excusez-moi, mais je ne suis pas un négrier. Ce n'est pas mon métier.";
			link.l2.go = "exit_slaves";
		break;
		
		case "exit_slaves":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;
		
		case "slaves_1":
			dialog.text = "Très bien alors. Je vous attendrai lorsque vous apporterez la cargaison. Vous pouvez me trouver à l'église de 11 heures à 13 heures chaque jour. Je suis occupé ou au travail pour le reste de la journée.";
			link.l1 = "Très bien. Je m'en souviendrai. À plus tard, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "slaves_2";
		break;
		
		case "slaves_2":
			DialogExit();
			sGlobalTemp = npchar.id;
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			SaveCurrentNpcQuestDateParam(npchar, "slaves_date");//запоминаем дату
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", npchar.city+"_church", "sit", "sit"+(1+rand(5)), "Nobleslaves_Place", 10.0);
			chrDisableReloadToLocation = true;//закрыть локацию
			Colonies[FindColony(npchar.city)].questslaves = true;
			sTitle = npchar.city+"Nobleslaves";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "Nobleslaves", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sQty", sti(npchar.quest.slaves.qty));
			AddQuestUserData(sTitle, "sMoney", sti(npchar.quest.slaves.money));
		break;
		
		case "slaves_3":
			if (GetNpcQuestPastDayParam(npchar, "slaves_date") < 180)
			{
				dialog.text = "As-tu apporté "+sti(npchar.quest.slaves.qty)+"des esclaves comme je vous l'ai demandé, capitaine ?";
				if (GetSquadronGoods(pchar, GOOD_SLAVES) >= sti(npchar.quest.slaves.qty))
				{
					link.l1 = "Oui. Tout le lot est dans ma cale. Je suis prêt à vous les remettre.";
					link.l1.go = "slaves_4";
				}
				else
				{
					link.l1 = "Non, je m'en occupe.";
					link.l1.go = "exit";
					NextDiag.TempNode = "slaves_3";
				}
			}
			else
			{
				dialog.text = "Capitaine, si vous êtes ici pour ces esclaves... J'en ai déjà acheté assez et je n'ai pas besoin de plus pour le moment. Vous avez pris trop de temps, désolé.";
				link.l1 = "Quel dommage ! Mais tu as raison, je n'étais pas assez rapide. Adieu !";
				link.l1.go = "slaves_8";
			}
		break;
		
		case "slaves_4":
			dialog.text = "Excellent. J'enverrai une chaloupe pour eux immédiatement.";
			link.l1 = "Et ma paie ?";
			link.l1.go = "slaves_5";
		break;
		
		case "slaves_5":
			dialog.text = "Ne t'inquiète pas, je m'en souviens. Tiens, prends la somme, "+sti(npchar.quest.slaves.price)+" doublons par tête. Une belle affaire pour nous deux, n'est-ce pas ?";
			link.l1 = "Merci. C'était un plaisir de faire affaire avec vous.";
			link.l1.go = "slaves_6";
		break;
		
		case "slaves_6":
			RemoveCharacterGoods(pchar, GOOD_SLAVES, sti(npchar.quest.slaves.qty));
			TakeNItems(pchar, "gold_dublon", sti(npchar.quest.slaves.money));
			Log_Info("You have received "+FindRussianDublonString(sti(npchar.quest.slaves.money))+"");
			PlaySound("interface\important_item.wav");
			dialog.text = "Je devrais dire cela... Pardonnez-moi maintenant, je dois y aller. À bientôt !";
			link.l1 = "Bonne chance, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "slaves_7";
		break;
		
		case "slaves_7":
			DialogExit();
			npchar.lifeday = 0;
			DeleteAttribute(Colonies[FindColony(npchar.city)], "questslaves");
			LAi_SetActorType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
         	ChangeCharacterAddressGroup(npchar, npchar.city+"_church", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10.0);
			AddCharacterExpToSkill(pchar, "Commerce", 150);//торговля
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Fortune", 30);//везение
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			sTitle = npchar.city+"Nobleslaves";
			AddQuestRecordEx(sTitle, "Nobleslaves", "2");
			CloseQuestHeader(sTitle);
		break;

		case "slaves_8":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			DeleteAttribute(Colonies[FindColony(npchar.city)], "questslaves");
			sTitle = npchar.city+"Nobleslaves";
			AddQuestRecordEx(sTitle, "Nobleslaves", "3");
			CloseQuestHeader(sTitle);
		break;
//<-- привезти рабов под заказ

		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Ecoute, en tant que citoyen de cette ville je te demande de rengainer ta lame.","Ecoute, en tant que citoyen de cette ville, je te demande de rengainer ta lame.");
			link.l1 = LinkRandPhrase("D'accord.","Comme vous le souhaitez.","Très bien.");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetHP(NPChar, 400, 400);
			TakeNItems(NPChar, "potion2", 3);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_MoveCharacter(NPChar, "TempFight");
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
			ChangeCharacterNationReputation(pchar, sti(npchar.nation), -3);
		break;
	}
}

string DonationText()
{
	string sText;
	switch (hrand(5))
	{
		case 0: sText = "I've lost all my money in gambling yesterday and I don't have enough sum to wipe away the debt. Can you help me?" break;
		case 1: sText = "I had a nice time yesterday with a... certain lady of the evening, and now she is trying to blackmail me. I need to pay her first and then I will deal with her... Can you help me with some money?" break;
		case 2: sText = "I ran through a local fool with my rapier recently and now the commandant demands a bribe to hush up the event. I am short of money now. Can you help me?" break;
		case 3: sText = "I was unlucky enough to lose a bet and I don't have a trifling sum to repay the debt of honor. Can you help me?" break;
		case 4: sText = "Some bastard knows about my... indiscreet activities concerning a married woman. I don't have enough money to shut his mouth. Just a few gold coins are needed... " break;
		case 5: sText = "Some bastard has stolen important papers from my house and demanding a significant sum for their return. I've almost got it, just a few more coins needed. Can you help me?" break;
	}
	return sText;
}

void LombardText()
{
	switch (hrand(5))
	{
		case 0:
			pchar.GenQuest.Noblelombard.Item = "my mother's diamond pendant made by a jeweler from Madrid";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("I will get my inheritance","my ship will return from Africa loaded with slaves");
		break;
		case 1: pchar.GenQuest.Noblelombard.Item = "an emerald necklace of my sister crafted by a jeweler in Paris";
				pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("I will inherit a county in Europe","my ship will return from India loaded with spices and silk");
		break;
		case 2:
			pchar.GenQuest.Noblelombard.Item = "family ring with an emblem of our kin";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("my expedition will return from the Spanish Main with gold ingots","I will get my inheritance");
		break;
		case 3:
			pchar.GenQuest.Noblelombard.Item = "a ruby bracelet of my wife, a gift from her mother";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("I will get my investment with the interest from a European bank","I will get the profits from my plantation");
		break;
		case 4:
			pchar.GenQuest.Noblelombard.Item = "a necklace of gold and diamonds, piece work, a pride of my wife";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("I will get profits from my current business","my ship will be back from Africa with the cargo hold stuffed with black ivory");
		break;
		case 5:
			pchar.GenQuest.Noblelombard.Item = "an ivory cane of semiprecious stones, a gift from my grandfather";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("my ship will be back from India with the cargo hold filled with silks and spices","I will receive my interest from a European bank");
		break;
	}
}
