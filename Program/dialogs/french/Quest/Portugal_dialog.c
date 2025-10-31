void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
		dialog.text = "Bug. Informez les devs.";
		link.l1 = "D'accord.";
		link.l1.go = "exit";
		break;
		
		case "Avendel_tavern":
			pchar.quest.Portugal_BeginOver.over = "yes";
			dialog.text = "Oh, un autre brave marin ! Je connais ton genre, mon oeil maudit de Dieu t'est acquis, ha ! Demande-moi pourquoi ?";
			link.l1 = "Je vais te parler d'une autre affaire, c'est à propos de ta dette envers la maîtresse de l'établissement local... hum, établissement. Elle m'a demandé de te rappeler ta dette, je te conseille de faire quelque chose à ce sujet, sinon elle devra faire appel aux gardes pour faire de même demain.";
			link.l1.go = "Avendel_tavern_1";
			DelLandQuestMark(npchar);
		break;
		
		case "Avendel_tavern_1":
			dialog.text = "Local est... oh, putain! Johanna, elle ne peut pas me faire ça! Es-tu sûr? A-t-elle vraiment dit qu'elle m'enverrait aux casemates pour quelques foutues pièces?";
			link.l1 = "Absolument. C'est ce qu'elle a dit. Je suppose que ma mission est terminée, adieu, monsieur Avendell.";
			link.l1.go = "Avendel_tavern_2";
		break;
		
		case "Avendel_tavern_2":
			dialog.text = "Attends! S'il te plaît, attends! Tu as l'air d'un capitaine expérimenté. Sûrement, tu as quelques pièces, je suis fauché, seul le bon vieux barman remplit ma chope à crédit pour notre vieille amitié. Écoute ma pro... proposition ! Tu payes ma dette et je te coupe une part. \nIl y a une affaire... une affaire très rentable, qu'on me pende par les tripes ! Je jure sur mon ancre ensanglantée, fais-moi confiance, capitaine - quel que soit ton nom ! \nIl suffit de racheter une petite dette, dix mille pesos et tu auras une chance de gagner assez de pièces pour acheter tous les bordels du Nouveau-monde-sanguinaire ! Que dis-tu ? Tu me donnes, je te donne, comme font les gens honnêtes...";
			link.l1 = "Un gaillard en haillons qui promet des trésors. Épargne-moi ce baratin, je ne fais pas la charité pour les gens comme toi. Trouve l'argent ou tu finiras bientôt dans les casemates du fort. Adieu !";
			link.l1.go = "Avendel_tavern_3";
			link.l2 = "Une part? Et pourquoi devrais-je faire confiance aux paroles d'un idiot ivre? A cause de promesses imaginaires?";
			link.l2.go = "Avendel_tavern_4";
		break;
		
		case "Avendel_tavern_3":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.Portugal = "end";
		break;
		
		case "Avendel_tavern_4":
			dialog.text = "Ecoutez-moi, capitaine ! Hic, tirez-moi dessus si je mens ! Mais je dis la vérité ! Réfléchissez-y, si vous me prenez en flagrant délit de mensonge, alors vous me couperez les tripes avec cette beauté que vous portez à votre ceinture ! Bon sang, sa poignée coûte cinq fois plus que ma misérable dette ! Alors, qu'en dites-vous ? Vous n'avez rien à perdre !";
			link.l1 = "J'en ai assez de tes discours. Adieu.";
			link.l1.go = "Avendel_tavern_3";
			link.l2 = "Très bien, Hugo... Je vais risquer de croire à ces balivernes que tu racontes. Mais souviens-toi que tu devras me convaincre et t'assurer que mon argent n'a pas été gaspillé pour rien quand je serai de retour, sinon c'est ta tête qui sera en jeu.";
			link.l2.go = "Avendel_tavern_5";
		break;
		
		case "Avendel_tavern_5":
			dialog.text = "Aucune menace n'est nécessaire, je comprends. Je vous donne ma parole, capitaine ! Nous serons riches ! Revenez quand cette maudite dette sera remboursée et nous parlerons... parlerons ! Oui, nous le ferons ! Vous ne serez pas laissé de côté !";
			link.l1 = "Très bien, je vais effacer ta dette, mais tu ferais mieux de prier, Hugo Avendell, pour que ta 'proposition' me satisfasse.";
			link.l1.go = "Avendel_tavern_6";
		break;
		
		case "Avendel_tavern_6":
			DialogExit();
			pchar.questTemp.Portugal = "HostressMoney";
			Nextdiag.Currentnode = "Avendel_repeat";
			AddLandQuestMark(characterFromId("Marigo_Hostess"), "questmarkmain");
		break;
		
		case "Avendel_repeat":
			dialog.text = "Capitaine, reviens aussi vite que possible - cette affaire pourrait s'échapper.";
			link.l1 = "Oui, oui, je rembourserai ta dette bientôt.";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Avendel_repeat";
		break;
		
		case "Avendel_tavern_7":
			pchar.quest.Portugal_BeginOver.over = "yes";
			dialog.text = "Vous êtes de retour, capitaine ! Par la tempête et que le tonnerre de Dieu me damne, je suis si heureux de vous voir ! Qu'en est-il de ma dette ?";
			link.l1 = "Je m'en suis occupé, maintenant c'est ton tour, Hugo. Raconte-moi ton histoire et essaie de la rendre juste un peu crédible !";
			link.l1.go = "Avendel_tavern_8";
			DelLandQuestMark(npchar);
		break;
		
		case "Avendel_tavern_8":
			dialog.text = "N'ayez crainte, capitaine ! Saviez-vous que je suis un chasseur de primes ? Ou plutôt... je l'étais. Je n'ai pas eu assez de chance, je suppose. Peut-être que le Diable lui-même avec toutes ses oeuvres n'était pas aussi perdant que je l'ai été. J'ai tout perdu lors de ma dernière mission... L'équipage s'est enfui et j'ai dû vendre mon navire à cause des dettes...";
			link.l1 = "Je suis déjà informé de ton passé héroïque. Allons droit au but, Hugo, ne mets pas ma patience à l'épreuve.";
			link.l1.go = "Avendel_tavern_9";
		break;
		
		case "Avendel_tavern_9":
			dialog.text = "Oui, oui, capitaine..."+GetFullName(pchar)+", ai-je raison? Je sais aussi quelque chose sur toi. Mais que le diable m'emporte si c'est important. As-tu entendu parler de Bartolomeo le Portugais?";
			link.l1 = "Bart le Portugais ? Bien sûr que j'ai entendu parler de lui. Tout le monde en a entendu parler. C'est un pirate, un boucher et une racaille d'après ce que je sais. Et quel est son rôle dans ton histoire ?";
			link.l1.go = "Avendel_tavern_10";
		break;
		
		case "Avendel_tavern_10":
			dialog.text = "Il joue un rôle maudit de premier plan là-dedans ! Je le poursuis depuis un an et demi. La Compagnie hollandaise a mis un sacré prix sur sa tête. Mais j'ai échoué, et j'ai tout perdu. Et la Compagnie a triplé le prix récemment pour l'avoir vivant, et seulement vivant, maudit soit-il !";
			link.l1 = "Pour une bonne raison, ce n'est pas du gâteau de le capturer vivant. Quoi qu'il en soit, pourquoi devrais-je m'en soucier, Hugo ? On dirait que tu essaies de m'entuber !";
			link.l1.go = "Avendel_tavern_11";
		break;
		
		case "Avendel_tavern_11":
			dialog.text = "Je n'allais même pas le faire, capitaine ! Vous savez, le médecin local Peter Van Stal, un homme très gentil, m'a donné une potion pour soigner mes maux de tête ! Alors, le médecin n'était pas chez lui pendant presque trois jours et...";
			link.l1 = "Hugo, ma patience est presque épuisée ! J'ai promis à la dame que je ne te transpercerai pas avec ma lame, mais mes poings feront très bien l'affaire ! Je jure qu'aucune potion ne pourra guérir ta tête demain !";
			link.l1.go = "Avendel_tavern_12";
		break;
		
		case "Avendel_tavern_12":
			dialog.text = "Attendez, capitaine ! S'il vous plaît ! Écoutez-moi, j'ai vu quelques types près de la maison du docteur et je les ai reconnus. Ils viennent de l'‘Albatros’, une frégate des maudits Portugais ! Et l'un d'eux parlait de la santé de leur capitaine ! Voyez maintenant, "+pchar.name+", Bartolomeo est ici, dans cette ville ! Juste sous notre nez, il est soit blessé, soit malade, c'est pour ça qu'ils ont besoin d'un maudit médecin !\nJe doute que le Portugais ait amené tout son équipage ici, mais je ne peux pas commencer ce bazar tout seul ! Sûrement, tu sais diablement bien manier ton épée maudite ! Prends quelques gars costauds avec toi et nous trouverons ce rat ! Ensuite, nous le capturons et le livrons aux autorités !\nEt deux mille bons doublons d'or sont dans nos poches !";
			link.l1 = "Non, Hugo, j'en ai assez de tes discours. Je ne participerai pas à ce désordre, même si tu as raison. Adieu.";
			link.l1.go = "Avendel_tavern_3";
			link.l2 = "Hmm, intéressant. Sais-tu où il se cache ? Si cela fonctionne, nous pourrons discuter des parts, mais si ce que tu me dis est vrai, alors nous devons nous dépêcher maintenant !";
			link.l2.go = "Avendel_tavern_13";
		break;
		
		case "Avendel_tavern_13":
			dialog.text = "Non, je ne sais pas où il est, capitaine. J'avais trop peur de traquer ces gaillards. Si le Borgne m'avait vu... fuh ! Mais ensemble, avec vos gars, nous serons capables de ratisser toute cette ville, appelez vos hommes et commençons ! Nom d'un chien, les doublons hollandais nous attendent ! Une telle sacrée chance n'arrive qu'une fois dans une vie, croque-moi un hareng !";
			link.l1 = "Un enthousiasme louable... J'espère que tu pourras te lever de table, un 'grand' chasseur de primes. Je vais chercher immédiatement et tu peux me suivre si tu veux, mais ne m'ennuie pas trop.";
			link.l1.go = "Avendel_tavern_14";
		break;
		
		case "Avendel_tavern_14":
			DialogExit();
			SetFunctionTimerCondition("Portugal_DoctorOver", 0, 0, 2, false);
			pchar.quest.Portugal_Guard.win_condition.l1 = "location";
			pchar.quest.Portugal_Guard.win_condition.l1.location = "Marigo_houseF1";
			pchar.quest.Portugal_Guard.function = "CreatePortugalGuard";
			AddQuestRecord("Portugal", "1");
			NextDiag.Currentnode = "Avendel_tavern_repeat";
			QuestPointerToLoc("marigo_town", "reload", "houseF1");
		break;
		
		case "Avendel_tavern_repeat":
			dialog.text = "Oui, oui, capitaine, laissez-moi juste finir mon verre et je vous rejoindrai... Où devrions-nous commencer ?";
			link.l1 = "Où ?!... Je pars, avec ou sans toi.";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Avendel_tavern_repeat";
		break;
		
		case "Portugal_guard":
			dialog.text = "Maison erronée, l'ami. Déguerpis, maintenant !";
			link.l1 = "Hum. Et je pense que c'est la bonne maison...";
			link.l1.go = "Portugal_guard_1";
		break;
		
		case "Portugal_guard_1":
			dialog.text = "Eh bien, je vous avais prévenu...";
			link.l1 = "... ";
			link.l1.go = "Portugal_guard_2";
		break;
		
		case "Portugal_guard_2":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=3; i++)
			{
			sld = characterFromId("PortugalGuard_"+i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.quest.Portugal_Doctor.win_condition.l1 = "location";
			pchar.quest.Portugal_Doctor.win_condition.l1.location = "Marigo_RoomHouseF1";
			pchar.quest.Portugal_Doctor.function = "CreatePortugalDoctor";
		break;
		
		case "Bart_lay":
			dialog.text = "Au plein près, volant haut, fils de... préparez les canons !... ah-ha-ha... oh ma beauté...";
			link.l1 = "Hmm, il a de la chance d'être en vie...";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Bart_lay";
		break;
		
		case "Portugal_doctor":
			pchar.quest.Portugal_DoctorOver.over = "yes";
			dialog.text = "Oh Dieu, qui êtes-vous ? Je vous en prie, baissez votre arme ! Il y a un homme malade ici !";
			link.l1 = "Cet 'homme malade' à vous a tué plus de gens que vous n'en avez vu dans votre vie, docteur. Éloignez-vous !";
			link.l1.go = "Portugal_doctor_1";
		break;
		
		case "Portugal_doctor_1":
			dialog.text = "Il est mon patient et il ne peut même pas se tenir debout ! Ne voyez-vous pas cela ? Je vous en prie, baissez votre lame ! Je vous en supplie !";
			link.l1 = "Et qu'est-ce qui ne va pas avec lui, bon sang !?";
			link.l1.go = "Portugal_doctor_2";
		break;
		
		case "Portugal_doctor_2":
			dialog.text = "Je suppose que c'est à cause de sa blessure, un coup porté par une arme caribe empoisonnée... et les hommes qui l'ont amené ici ont dit que s'il meurt, je mourrai aussi ! Mais je fais tout ce que je peux, dites-leur cela !";
			link.l1 = "Ne vous inquiétez pas pour ces hommes, docteur. Mes gars surveilleront votre maison et je dois aller voir le gouverneur. Je suppose qu'il se pissera de joie. Ne quittez pas cet endroit jusqu'à mon retour, doc.";
			link.l1.go = "Portugal_doctor_3";
		break;
		
		case "Portugal_doctor_3":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetStayType(npchar);
			Nextdiag.Currentnode = "Doctor_repeat";
			pchar.quest.Avendel_House.win_condition.l1 = "location";
			pchar.quest.Avendel_House.win_condition.l1.location = "Marigo_houseF1";
			pchar.quest.Avendel_House.function = "AvendelInHouse";
		break;
		
		case "Doctor_repeat":
			dialog.text = "Je ne partirai pas, ne t'en fais pas pour ça. Remettons-le simplement aux autorités et mettons fin à ce cauchemar.";
			link.l1 = "Bien sûr, je suis en route.";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Doctor_repeat";
		break;
		
		case "Avendel_house":
			dialog.text = "Nous l'avons fait, capitaine ! Nous l'avons trouvé et nous serons bientôt riches, comme je vous l'avais dit ! Quel est notre plan ?";
			link.l1 = "Je l'espère, Hugo. Quoi qu'il en soit, ce n'est pas encore fini. Je suppose que je dois aller voir le gouverneur et discuter de notre récompense ?";
			link.l1.go = "Avendel_house_1";
		break;
		
		case "Avendel_house_1":
			dialog.text = "Non-non, capitaine ! Ne va pas voir ce maudit Thomas ! Crois-moi, ce gredin nous prendra notre prisonnier et si on a de la chance, il nous offrira une tasse de café ! Son Excellence est un type louche, alors si tu veux obtenir ta récompense complète, tu dois naviguer vers Curaçao ! Sinon, les Portugais nous seront pris et emmenés au fort, et ils nous chasseront comme des mendiants !";
			link.l1 = "Eh bien, si tu en es vraiment sûr...";
			link.l1.go = "Avendel_house_2";
		break;
		
		case "Avendel_house_2":
			dialog.text = "Je le suis, capitaine, sacrebleu, je le suis ! Mais souviens-toi que les hommes de Bartolomeo doivent être quelque part en ville et nous ne voulons pas non plus attirer l'attention de la garnison, ça c'est sûr et certain ! Nous devons décider comment amener les Portugais jusqu'à ton navire et comment le faire de manière discrète.";
			link.l1 = "Bien... Je ne veux pas combattre sa frégate en route pour Willemstad. As-tu des idées ?";
			link.l1.go = "Avendel_house_3";
		break;
		
		case "Avendel_house_3":
			dialog.text = "Oui, j'en ai un. Nous devons d'abord lui trouver un habit plus noble, ensuite nous le traînons par l'entrée arrière comme un officier ivre ! Personne ne soupçonnera que c'est un foutu pirate, fais-moi confiance !";
			link.l1 = "Hmm, je ne suis pas sûr de cela, mais nous n'avons pas encore de meilleur plan de toute façon. Je vais essayer d'obtenir de beaux tissus pour notre passager. Reste ici et surveille Bart et le doc.";
			link.l1.go = "Avendel_house_4";
		break;
		
		case "Avendel_house_4":
			DialogExit();
			AddQuestRecord("Portugal", "3");
			LAi_ActorRunToLocation(npchar, "reload", "houseF1", "Marigo_houseF1", "goto", "goto2", "", -1);
			pchar.quest.Portugal_Cloves.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Cloves.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Cloves.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Portugal_Cloves.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Portugal_Cloves.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Portugal_Cloves.function = "PortugalClovesOver";//1 сутки
			pchar.questTemp.Portugal = "Findcloves";
			LAi_SetStayType(npchar);
			npchar.dialog.currentnode = "Avendel_house_guard";
			AddLandQuestMark(characterFromId("Marigo_trader"), "questmarkmain");
			QuestPointerToLoc("marigo_town", "reload", "reload6_back");
		break;
		
		case "Avendel_house_guard":
			dialog.text = "Ne t'en fais pas, capitaine. Le Portugais est sous ma garde fiable, hé-hé...";
			link.l1 = "J'aimerais croire que...";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Avendel_house_guard";
		break;
		
		case "Portugal_doctor_4":
			dialog.text = "Je ne vois pas les soldats, "+GetAddress_Form(NPChar)+"Où sont-ils ? Tu as dit qu'il serait arrêté dès que tu leur parlerais de la situation. Alors pourquoi les soldats ne sont-ils pas ici ?";
			link.l1 = "Il n'y aura pas de soldats, mynheer Van Stal. Je vais faire le travail moi-même et je dois emmener votre patient à Curacao dès que possible.";
			link.l1.go = "Portugal_doctor_5";
			DelLandQuestMark(npchar);
		break;
		
		case "Portugal_doctor_5":
			dialog.text = "Capitaine, écoutez, je ne peux pas soigner sa blessure, tout ce que je peux faire, c'est juste faire baisser un peu la fièvre. Il est principalement inconscient et délirant, il ne fait aucun doute qu'il mourra même sans aucune intervention et le roulis de la mer le tuera en quelques jours. Je vais vous donner quelques mixtures qui aideront...";
			link.l1 = "Non, toubib, tu navigues avec nous. D'abord, je suis nul en médecine et ensuite, je doute que tu veuilles rester ici et expliquer aux hommes portugais où est passé leur capitaine ?";
			link.l1.go = "Portugal_doctor_6";
		break;
		
		case "Portugal_doctor_6":
			dialog.text = "...Oui, je suppose que vous avez raison. Mais sachez que ce pirate est très résistant, j'ai vu des gens avec seulement de petites éraflures faites par des armes indiennes et tous sont morts en moins de trois jours. Et selon ses 'amis', il est dans cet état depuis déjà une semaine ! Néanmoins, j'affirme qu'il survivra pour une courte période sur un navire en haute mer. Trois jours, pas plus !\nC'est tout le temps que nous avons.";
			link.l1 = "  Meme l'oiseau n'atteindra pas Curacao en trois jours. Mais je crois que je sais ce que je peux faire ! Il y a ce... ami a moi, il vit a St. John's, Antigua. Il sait comment guerir les gens de blessures mortelles. Il est la seule personne qui peut nous aider maintenant. Notre but est simple - y arriver avant que le Portugais ne meure.   Emballez vos affaires, doc, nous mettons les voiles immediatement et votre patient sera transfere ensuite ! ";
			link.l1.go = "Portugal_doctor_7";
		break;
		
		case "Portugal_doctor_7":
			DialogExit();
			AddQuestRecord("Portugal", "5");
			pchar.quest.Portugal_Cloves.over = "yes";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sld = characterFromId("Avendel");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			RemoveItems(PChar, "suit_1", 1);
			sld = characterFromId("Portugal");
			sld.model = "Port_B"; //меняем модель
			ChangeCharacterAddressGroup(sld, "My_Deck", "goto", "goto6");
			SetFunctionTimerCondition("Portugal_ToAntiguaOver", 0, 0, 4, false);
			pchar.questTemp.Portugal = "ToAntigua";
			QuestPointerDelLoc("marigo_town", "reload", "houseF1");
			//временно для тестов откроем комнату Джино, потом убрать
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload4", false);
		break;
		
		case "Avendel_goodbye":
			dialog.text = "Quel dommage, capitaine. Nous avons perdu, et nous ne verrons pas ce fichu or. Adieu.";
			link.l1 = "Adieu, Hugo.";
			link.l1.go = "Avendel_goodbye_1";
		break;
		
		case "Avendel_goodbye_1":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
		break;
		
		case "Portugal_doctor_9":
			dialog.text = "...";
			link.l1 = "Doc, préparez votre patient pour l'atterrissage. Le canot est prêt. Dépêchez-vous !";
			link.l1.go = "Portugal_doctor_10";
			DelLandQuestMark(npchar);
		break;
		
		case "Portugal_doctor_10":
			dialog.text = "Je suis en route, "+GetAddress_Form(NPChar)+".";
			link.l1 = "...";
			link.l1.go = "Portugal_doctor_11";
		break;
		
		case "Portugal_doctor_11":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Portugal_PerenesliVDom1", -1);
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "SentJons_HouseF3_Room2", "quest", "quest1");
			sld = characterFromId("Jino");
			ChangeCharacterAddressGroup(sld, "SentJons_HouseF3_Room2", "goto", "goto3");
			pchar.quest.Portugal_ToAntiguaOver.over = "yes";//снять таймер
			pchar.questTemp.Portugal = "TreatmentStart";
			pchar.quest.Portugal_Ill.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Ill.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Ill.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 7);
			pchar.quest.Portugal_Ill.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 7);
			pchar.quest.Portugal_Ill.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 7);
			pchar.quest.Portugal_Ill.function = "Portugal_ToAntiguaOver";//не придёт через 7 дня - Португальцу капут
		break;
		
		case "Avendel_Room":
			dialog.text = "Cette maison pue de foutues mixtures! Ce serait une grande surprise si le Portugais mourait ici, même respirer cette odeur peut guérir n'importe quelle maladie!\nEt l'équipage de l'homme peut nous trouver facilement grâce à la puanteur!";
			link.l1 = "Hugo, epargne-moi tes blagues. J'ai laissé quelques hommes dans les rues pour surveiller la maison, mais un garde de plus ne sera pas inutile pour notre invité. Surveille-le et essaie d'arrêter de jurer, ou Gino te fera boire un de ses breuvages, je suis sûr qu'il peut guérir ça.";
			link.l1.go = "Avendel_Room_1";
		break;
		
		case "Avendel_Room_1":
			dialog.text = "N'ayez crainte, capitaine ! Je veillerai sur notre argent de la manière la plus vigilante, il ne s'enfuira pas même s'il était en pleine santé ! Et je vous en prie, par pitié, plus de mixtures !";
			link.l1 = "Tu vois, tu peux être gentil quand tu veux. Sois sur tes gardes, je dois y aller.";
			link.l1.go = "exit";
			chrDisableReloadToLocation = false;
		break;
		
		case "Avendel_Room_2":
			dialog.text = "Vous partez déjà, capitaine ? Bien ! Il est temps ! J'ai vu quelques sala... types suspects dans la rue. Ils ne ressemblent pas à des Portugais, bien qu'ils cherchaient quelque chose, nous devons être prudents, capitaine !";
			link.l1 = "Bien, merci pour ton avertissement, Hugo. Allons au navire.";
			link.l1.go = "Avendel_Room_3";
		break;
		
		case "Avendel_Room_3":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			//ставим Португальца
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "SentJons_HouseF3", "goto", "goto1");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
		case "Portugal_hunter":
			dialog.text = "Capitaine, nous attendons cette rencontre depuis bien trop longtemps ! Et qui est-ce avec vous ? Bartolomeo le Portugais en personne, ha, il semble que le Hardi Pierre avait raison - c'est lui ! Restez à l'écart, capitaine, nous allons l'emmener avec nous et personne ne sera blessé.";
			link.l1 = "Je suis désolé, monsieur, mais qui diable êtes-vous ? Dégagez de mon chemin ou aucun de vous ne verra demain !";
			link.l1.go = "Portugal_hunter_1";
		break;
		
		case "Portugal_hunter_1":
			dialog.text = "Oh, un gaillard si menaçant, regardez-le les gars ! Ha-ha-ha ! Écoute-moi bien, chiot, ne te mets pas entre Leo Cord et son argent ! Nous avons traqué le Portugais pendant presque six mois et maintenant nous l'avons enfin attrapé. Alors pose ton cure-dents et dégage tant que tu respires encore ! Nous ne sommes pas si gourmands, un homme mort fera l'affaire, ha-ha !";
			link.l1 = "Assez. Dansons, messieurs !";
			link.l1.go = "Portugal_hunter_2";
		break;
		
		case "Portugal_hunter_2":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
		DialogExit();
		sld = characterFromId("Portugal");
		LAi_group_Register("Bart_Portugal");
		LAi_group_SetRelation("Bart_Portugal", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
		LAi_group_MoveCharacter(sld, "Bart_Portugal");
		for (i=1; i<=5; i++)
		{
		sld = characterFromId("PortugalHunter_"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "PortugalHunterDied");
		AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Avendel_street":
			sld = characterFromId("Portugal");
			if (LAi_GetCharacterHP(sld) > 0)
			{
				dialog.text = "Je savais que quelque chose n'allait pas ici ! Bien joué, capitaine ! Mais il est temps de partir, ce maudit Leo Cord a beaucoup de bandits ici et un bon navire ! Nous devons quitter cette île !";
				link.l1 = "Bon argument, Hugo, et je suis très content qu'aucune balle n'ait été tirée sur l'endroit où tu te cachais.";
				link.l1.go = "Avendel_street_1";
			}
			else
			{
				dialog.text = "Quel dommage, capitaine. Nous avons perdu et nous ne verrons pas cet or maudit. Adieu.";
				link.l1 = "Adieu, Hugo.";
				link.l1.go = "Avendel_goodbye_1";
				sld = characterFromId("PortugalDoctor");
				RemovePassenger(Pchar, sld);
				sld.lifeday = 0;
				RemovePassenger(Pchar, npchar);
				AddQuestRecord("Portugal", "35");
				CloseQuestHeader("Portugal");
				pchar.questTemp.Portugal = "end";
			}
		break;
		
		case "Avendel_street_1":
			dialog.text = "Je... Je sécurisais notre arrière, capitaine ! Vous vous en sortiez très bien sans moi, mais que se serait-il passé si quelqu'un nous avait attaqués de l'autre côté de la rue ? Vous n'auriez pas eu le temps de courir jusqu'au navire.";
			link.l1 = "Peut-être est-ce la raison pour laquelle vous n'avez pas réussi dans votre métier ? Quoi qu'il en soit, assez parlé, nous devons rejoindre le navire ! Le temps presse !";
			link.l1.go = "Avendel_street_2";
		break;
		
		case "Avendel_street_2":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10);
			AddQuestRecord("Portugal", "8");
			pchar.quest.Portugal_seahunter.win_condition.l1 = "location";
			pchar.quest.Portugal_seahunter.win_condition.l1.location = "Antigua";
			pchar.quest.Portugal_seahunter.function = "PortugalSeaHunter";
			pchar.quest.Portugal_martinique.win_condition.l1 = "location";
			pchar.quest.Portugal_martinique.win_condition.l1.location = "FortFrance_town";
			pchar.quest.Portugal_martinique.function = "PortugalOnMartinique";
		break;
		
		case "Portugal_doctor_12":
			dialog.text = "Capitaine, le Portugais se sent vraiment mal, nous devons nous arrêter !";
			link.l1 = "C'est pourquoi nous sommes ici, mynheer van Stal, notre voyage est presque terminé. Je vais louer une chambre à la taverne et notre prisonnier y restera quelques jours.";
			link.l1.go = "Portugal_doctor_13";
		break;
		
		case "Portugal_doctor_13":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 5);
		break;
		
		case "Portugal_doctor_14":
			dialog.text = "Monsieur le capitaine, je m'occuperai du Portugais, il a besoin de repos complet.";
			link.l1 = "Je l'ai, doc, ça va. Bon sang, combien de temps devrais-je m'occuper de ce pirate ? C'est mauvais pour lui, ce n'est pas ce dont il a besoin ! On dirait que j'ai été engagé comme nourrice et... agh, pardonnez-moi, docteur, c'est juste trop... Je vous verrai plus tard.";
			link.l1.go = "Portugal_doctor_15";
		break;
		
		case "Portugal_doctor_15":
			DialogExit();
			AddQuestRecord("Portugal", "15");
			pchar.quest.Portugal_patrol.win_condition.l1 = "location";
			pchar.quest.Portugal_patrol.win_condition.l1.location = "FortFrance_town";
			pchar.quest.Portugal_patrol.function = "CreateFrancePatrol";
		break;
		
		case "Portugal_patrol":
			dialog.text = "Monsieur, es-tu capitaine "+GetFullName(pchar)+", dont le navire vient d'arriver dans notre port aujourd'hui ?";
			link.l1 = "Vous avez raison, comment puis-je vous aider ?";
			link.l1.go = "Portugal_patrol_1";
		break;
		
		case "Portugal_patrol_1":
			dialog.text = "Son Excellence Jacques Dille du Parquet, le gouverneur de notre colonie vous attend. L'affaire est urgente !";
			link.l1 = "Bien, monsieur, je rendrai visite à son Excellence aujourd'hui.";
			link.l1.go = "Portugal_patrol_2";
		break;
		
		case "Portugal_patrol_2":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.questTemp.Portugal = "MartiniqueGovernor";
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			AddQuestRecord("Portugal", "9");
		break;
		
		case "Avendel_seapatrol":
			dialog.text = "Nous avons atteint la Martinique, capitaine ! Notre argent n'est plus très loin maintenant...";
			link.l1 = "Seulement si les Portugais vivront jusqu'à ce que nous atteignions Willemstad. Hugo, je dois aller au navire, alors tu devras veiller sur le doc et son patient.";
			link.l1.go = "Avendel_seapatrol_1";
		break;
		
		case "Avendel_seapatrol_1":
			dialog.text = "Aller au navire ? Pourquoi ? Me preterez-vous quelques-uns de vos hommes pour m'aider ? Que se passera-t-il si quelque chose arrive pendant votre absence ?";
			link.l1 = "Je suis désolé, mais non. Je doute que quelque chose puisse te menacer ici. La garnison est en alerte et il y a plus de soldats dans les rues que d'habitude, donc si quelque chose tourne mal, appelle-les. Ils ont vu un grand navire non loin de cette île, peut-être un pirate. Et son Excellence le gouverneur m'a demandé de fortifier l'île en patrouillant avec mon navire.";
			link.l1.go = "Avendel_seapatrol_2";
		break;
		
		case "Avendel_seapatrol_2":
			dialog.text = "Un navire ? Un pirate ? Cela pourrait être l'Albatros ! Ou un collègue de notre vieil ami Leo Cord !";
			link.l1 = "Ou peut-être est-ce simplement un navire pirate ordinaire. Néanmoins, Hugo, si ce vaisseau est ici pour nos têtes, alors je ferais mieux de l'affronter avec la patrouille locale à mes côtés et pour l'or du gouverneur. C'est bien mieux que de surveiller nos arrières pour le reste du voyage. Si cette alerte est fausse cependant, alors cela m'épargnera simplement de rester le cul assis à la taverne pendant quelques jours.";
			link.l1.go = "Avendel_seapatrol_3";
		break;
		
		case "Avendel_seapatrol_3":
			dialog.text = "Pensez-y, capitaine, est-il sage de laisser le dam... le Portugais sans protection alors que sa frégate pourrait croiser dans les parages ? Vous risquez notre récompense en acceptant la commission du gouverneur !";
			link.l1 = "Assez parlé, Hugo Avendell ! Je suis le capitaine ici et la décision finale m'appartient ! Alors fais ce que je te commande. Va à la taverne et garde un oeil sur le docteur et le Portugais jusqu'à mon retour.";
			link.l1.go = "Avendel_seapatrol_4";
		break;
		
		case "Avendel_seapatrol_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("Fortfrance_town", "reload4_back", true);//закрыть таверну
		break;
		
		case "Avendel_seapatrol_5":
			dialog.text = "Vous êtes de retour, capitaine, enfin ! J'ai bien peur d'avoir de mauvaises nouvelles pour vous - le Portugais est parti, et le doc aussi !";
			link.l1 = "Comment?! Et que faisais-tu alors, crétin?!";
			link.l1.go = "Avendel_seapatrol_6";
		break;
		
		case "Avendel_seapatrol_6":
			dialog.text = "Je parie que ce navire était l' 'Albatros'. J'ai vu les Portugais, ils sont entrés dans la taverne et moi... j'ai pris la fuite. Je suis désolé, mais rencontrer le Chien borgne, c'était trop même pour autant d'argent !";
			link.l1 = "Nom de Dieu ! Dis-moi au moins ce qui s'est passé à la taverne ?";
			link.l1.go = "Avendel_seapatrol_7";
		break;
		
		case "Avendel_seapatrol_7":
			dialog.text = "Je t'ai dit que je n'ai rien vu. Je me suis enfui par la cuisine dès que j'ai vu Franz Garcke et ses hommes... C'était trop près ! Cela s'est passé hier soir et je ne savais pas comment te prévenir...";
			link.l1 = "Oui, tu es un homme très brave et ingénieux... Bien, donnons-lui une chance de plus, nous allons les trouver. J'ai gardé ce scélérat trop longtemps et maintenant je le considère comme ma propriété. Nous avons encore un peu de temps pour les attraper, alors commençons par la taverne, peut-être que quelqu'un a vu plus que tes talons en fuite. Va, prépare-toi !";
			link.l1.go = "Avendel_seapatrol_8";
		break;
		
		case "Avendel_seapatrol_8":
			DialogExit();
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			chrDisableReloadToLocation = false;
			LAi_ActorFollowEverywhere(npchar, "", -1);
			SetFunctionTimerCondition("MartiniquePortugalOver", 0, 0, 2, false); //таймер
			sld = characterFromId("PortugalDoctor");
			sld.lifeday = 0;//убираем доктора
			RemovePassenger(Pchar, sld);	
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "none", "", "");//Португальца спрячем
			LocatorReloadEnterDisable("Fortfrance_tavern", "reload2_back", true);//комнату закроем
			AddQuestRecord("Portugal", "12");
		break;
		
		case "Avendel_seapatrol_9":
			dialog.text = "Avez-vous entendu, capitaine, il parlait du Chien Borgne, je vous en ai parlé récemment. Et le Castillan bègue, c'est Hernando Vasquez, ce foutu Don - le boucher de Vera Cruz, je ne l'ai pas vu !";
			link.l1 = "Calme-toi, Hugo. Je suis sûr que Bartholomeo est encore sur l'île, il a peut-être récupéré un peu, mais il est toujours trop faible. Et je crois savoir où le trouver ! Nous les attraperons, je ne renoncerai pas à ma récompense. Si tu n'es pas un lâche, suis-moi, ce n'est pas encore fini.";
			link.l1.go = "Avendel_seapatrol_10";
		break;
		
		case "Avendel_seapatrol_10":
			DialogExit();
			bDisableFastReload = false;//открыть быстрый переход
			pchar.questTemp.Portugal = "PortugalLeFransua";//в Ле Франсуа
			AddQuestRecord("Portugal", "13");
			LAi_LocationDisableOfficersGen("LeFransua_tavern", true);//офицеров не пускать
		break;
		
		case "LeFransua_pirate":
			dialog.text = "Tu poses trop de questions, capitaine... Attends, ne serais-tu pas ce type sournois de Philipsburg ? Tu nous fuis depuis bien trop longtemps et regarde maintenant - te voilà...";
			link.l1 = "Quel dommage pour toi, vermine !";
			link.l1.go = "LeFransua_pirate_1";
		break;
		
		case "LeFransua_pirate_1":
			DialogExit();
			pchar.quest.MartiniquePortugalOver.over = "yes"; //снять таймер
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for (i=1; i<=3; i++)
			{
			sld = characterFromId("LeFransuaPirate_"+i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LeFransuaAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "FranzGarke":
			dialog.text = "... toi, misérable merde de crabe, tu vas tout nous dire, tu peux me croire là-dessus, espèce de rat de merde ! Ensuite, tu seras pendu à une vergue au lieu d'une brigantine... Et qui diable es-tu ? Bordel, ces macaques ne sont pas fiables ! Toujours obligé de tout faire moi-même...";
			link.l1 = "Est-ce que je vous dérange, messieurs ?";
			link.l1.go = "FranzGarke_1";
		break;
		
		case "FranzGarke_1":
			DialogExit();
			chrDisableReloadToLocation = true;
			sld = characterFromId("FranzGarke");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LeFransua_PortugalTalk");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Portugal_LFTalk":
			dialog.text = "J'aime votre ponctualité... Je suppose que je dois vous remercier de m'avoir gardé en vie jusqu'à aujourd'hui ?";
			link.l1 = "Tu as raison. Mon nom est "+GetFullName(pchar)+" et toi, Portugais, tu es toujours mon prisonnier. Alors ne me pose pas de questions, nous devons partir.";
			link.l1.go = "Portugal_LFTalk_1";
		break;
		
		case "Portugal_LFTalk_1":
			dialog.text = "Attends, capitaine... il y a beaucoup d'hommes de Vasquez en ville, ils ne nous laisseront pas partir comme ça. Donne-moi une épée et nous aurons bien plus de chances.";
			link.l1 = "Tu n'es pas en bons termes avec tes partenaires, hein ? Soit, une lame supplémentaire est toujours la bienvenue, prends l'arme du cadavre et reste près de moi !";
			link.l1.go = "Portugal_LFTalk_2";
			link.l2 = "Ne pense même pas que je vais te donner une arme pour que tu puisses me frapper dès que je te tournerai le dos ! Reste juste près de moi.";
			link.l2.go = "Portugal_LFTalk_4";
			pchar.quest.Portugal_LeFransua.win_condition.l1 = "location";
			pchar.quest.Portugal_LeFransua.win_condition.l1.location = "LeFransua_town";
			pchar.quest.Portugal_LeFransua.function = "CreateVaskezsPirates";
			bDisableFastReload = true;//закрыть переход
		break;
		
		case "Portugal_LFTalk_2":
			dialog.text = "Ne t'inquiète pas, capitaine, je préfère mourir que de retomber entre les mains de Vasquez.";
			link.l1 = "Eh bien, le truc, c'est que je ne veux pas encore te voir mort. Allons-y, le temps presse!";
			link.l1.go = "Portugal_LFTalk_3";
		break;
		
		case "Portugal_LFTalk_3":
			DialogExit();
			GiveItem2Character(npchar, "blade_17");
			EquipCharacterbyItem(npchar, "blade_17");
			GiveItem2Character(npchar, "pistol6");
			EquipCharacterbyItem(npchar, "pistol6");
			TakeNItems(npchar, "bullet", 50);
			AddItems(npchar, "gunpowder", 50);
			TakeNItems(npchar, "potion2", 3);
			LAi_SetCharacterUseBullet(npchar, GUN_ITEM_TYPE, "bullet");
			pchar.questTemp.Portugal.Condition1 = "true";
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
		break;
		
		case "Portugal_LFTalk_4":
			dialog.text = "Quel dommage, j'aurais aidé le Borgne si j'avais voulu ta mort...";
			link.l1 = "Mais tu ne m'as pas aidé non plus, alors tais-toi et avance !";
			link.l1.go = "Portugal_LFTalk_5";
		break;
		
		case "Portugal_LFTalk_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
		break;
		
		case "Vaskezs_pirate":
			PlaySound("Voice\English\EvilPirates01.wav");
			dialog.text = "Merde ! C'est eux ! Tuez-les tous !";
			link.l1 = "Nous y revoilà... Venez donc, tas de bâtards !";
			link.l1.go = "Vaskezs_pirate_1";
		break;
		
		case "Vaskezs_pirate_1":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Portugal.Condition1"))
			{
				sld = characterFromId("Portugal");
				LAi_SetImmortal(sld, false);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			for (i=1; i<=9; i++)
			{
				sld = characterFromId("VaskezsPirate_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "VaskezsPiratesDied");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Avendel_LeFransua":
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;//открыть переход
			sld = characterFromId("Portugal");
			if (LAi_GetCharacterHP(sld) > 0)
			{
				dialog.text = "Splendide ! Vous avez tué le Chien Borgne, voilà ce que j'appelle un chef-d'œuvre ! Combien de ses hommes avez-vous envoyés brûler en enfer ?";
				link.l1 = "Je combattais, pas en train de compter. Et où étais-tu, Hugo ?";
				link.l1.go = "Avendel_LeFransua_1";
			}
			else
			{
				dialog.text = "Quel dommage, capitaine. Nous avons perdu et nous ne verrons pas cet or maudit. Adieu.";
				link.l1 = "Adieu, Hugo.";
				link.l1.go = "Avendel_goodbye_1";
				RemovePassenger(Pchar, npchar);
				CloseQuestHeader("Portugal");
				pchar.questTemp.Portugal = "end";
			}
		break;
		
		case "Avendel_LeFransua_1":
			dialog.text = "Je... sécurisais le retrait en toute sécurité... protégeant nos arrières pour ainsi dire.";
			link.l1 = "Eh bien, c'est ça, Hugo Avendell, ta lâcheté a surpassé toutes mes attentes, as-tu la moindre idée de la difficulté de ce combat pour nous ? Nous l'avons à peine réussi !";
			link.l1.go = "Avendel_LeFransua_2";
		break;
		
		case "Avendel_LeFransua_2":
			dialog.text = "Calmez-vous, capitaine... J'admets que je me cachais. Mais j'ai trouvé cette opportunité pour vous ! Rappelez-vous, c'est moi qui vous ai mené aux Portugais ! Eh bien... compte tenu de votre juste indignation, je consens à seulement un tiers de la récompense.";
			link.l1 = "C'est tout simplement glorieux ! Tu marchandes maintenant ? Non, mon ami, ton rôle dans cette affaire est terminé ! Tu as perdu ton argent dans la taverne de Saint-Pierre. Tu l'as laissé là et tu t'es enfui, donc c'est fini pour toi maintenant.";
			link.l1.go = "Avendel_LeFransua_3";
		break;
		
		case "Avendel_LeFransua_3":
			dialog.text = "Capitaine, vous exagérez clairement... D'accord, je suis d'accord pour un quart... pour un cinquième ! Dix pour cent !";
			link.l1 = "Ne mets pas ma patience à l'épreuve ! Déguerpis ! Je n'ai pas besoin de lâches dans mon équipage, surtout maintenant que le temps presse !";
			link.l1.go = "Avendel_LeFransua_4";
		break;
		
		case "Avendel_LeFransua_4":
			dialog.text = ""+pchar.name+", ne penses-tu pas que c'est un peu injuste ?";
			link.l1 = "Cause et effet, Hugo... Tu as fait ton choix, alors adieu. Tire une conclusion et ne te lance pas dans des aventures pareilles, cela n'est clairement pas pour toi.";
			link.l1.go = "Avendel_LeFransua_5";
		break;
		
		case "Avendel_LeFransua_5":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			sld = characterFromId("Portugal");
			sld.dialog.currentnode = "Portugal_LeFransua";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			pchar.questTemp.Portugal.GG2 = "true"; // Jason Дороже золота
		break;
		
		case "Portugal_LeFransua":
			dialog.text = "Larguer le lest, capitaine ? Si vrai, ha... Vasquez est encore libre et il y a beaucoup d'hommes et de canons sur l'Albatros, je parie mes beaux pantalons contre un vieux mouchoir que Hernando ne nous laissera pas échapper.";
			link.l1 = "Eh bien, il semble que nous devions aller le saluer nous-mêmes. Allez, monsieur Portugais, et essayez de garder votre bouche fermée. Nous allons lever l'ancre dès que possible.";
			link.l1.go = "Portugal_LeFransua_1";
		break;
		
		case "Portugal_LeFransua_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.Portugal_LeFransua1.win_condition.l1 = "location";
			pchar.quest.Portugal_LeFransua1.win_condition.l1.location = "Martinique";
			pchar.quest.Portugal_LeFransua1.function = "CreateVaskezsFrigate";
		break;
		
		case "VaskezsHelper_abordage":
			dialog.text = "Qu'attends-tu, bon sang?!";
			link.l1 = "Où est Hernando Vasquez ? Parle et j'épargnerai ta vie.";
			link.l1.go = "VaskezsHelper_abordage_1";
		break;
		
		case "VaskezsHelper_abordage_1":
			dialog.text = "Va au diable avec tes foutues questions !";
			link.l1 = "Après vous...";
			link.l1.go = "VaskezsHelper_abordage_2";
		break;
		
		case "VaskezsHelper_abordage_2":
			DialogExit();
			QuestAboardCabinDialogExitWithBattle(""); 	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Portugal_treasure":
			bQuestDisableMapEnter = false;
			if (CheckAttribute(pchar, "questTemp.Portugal.Condition1") && CheckAttribute(pchar, "questTemp.Portugal.Condition2"))
			{
				dialog.text = "Et te voilà, mon brave ami, nous pouvons enfin avoir une conversation décente ! Félicitations, capitaine - tuer le Chien Borgne et détruire l' 'Albatros' n'était pas une tâche facile ! En fait, tu as fait tant pour sauver ma vie... Peut-être devrais-je même te remercier ?";
				link.l1 = "Tu me remercieras quand tu danseras sur la potence ou quoi que ce soit qu'ils t'ont préparé à Willemstad.";
				link.l1.go = "Portugal_treasure_6";
			}
			else
			{
				dialog.text = "Et te voilà mon brave ami, nous pouvons enfin discuter ! Félicitations, capitaine - tuer le Chien Borgne mérite une chanson honorable ! En fait, tu as fait tellement pour sauver ma vie... Peut-être devrais-je même te remercier ?";
				link.l1 = "Tu me remercieras quand tu danseras sur la potence ou quoi qu'ils t'aient préparé à Willemstad.";
				link.l1.go = "Portugal_treasure_1";
			}
		break;
		
		case "Portugal_treasure_1":
			dialog.text = "Incredible ! Tu m'as sauvé la vie ces deux dernières semaines, tu m'as amené chez toi et protégé lors des combats... et maintenant tu vas m'envoyer à la mort ? J'ai du mal à y croire... En fait, je te considère presque comme un ami maintenant, ha-ha.";
			link.l1 = "Un pirate qui plaide pour l'honneur ? Portugais, tu te moques de moi ? Je te gardais en vie pour une seule raison - laisser l'assassin et vaurien affronter le tribunal de justice !";
			link.l1.go = "Portugal_treasure_2_1";
			link.l2 = "Ami à moi... cela semble une moquerie. Mais néanmoins, tu as raison. Ce serait étrange de ma part de faire cela, Portugais...";
			link.l2.go = "Portugal_treasure_2_2";
		break;
		
		case "Portugal_treasure_2_1":
			dialog.text = "Oh, assez, capitaine. Je parie que vous faisiez tout cela uniquement pour obtenir l'argent que la Compagnie avait promis pour le plaisir de me voir vivant ! N'essayez pas d'être plus honnête que vous ne l'êtes réellement, monsieur, cela ne vous va pas.";
			link.l1 = "Moi seul peux me juger. Alors mettons fin à cette conversation. Il est temps de naviguer vers Willemstad.";
			link.l1.go = "Portugal_treasure_3";
		break;
		
		case "Portugal_treasure_2_2":
			dialog.text = "Il semble qu'il y ait encore un peu d'honnêteté chez les gens de nos jours... Dommage que l'argent s'en mêle toujours - hein, capitaine ?";
			link.l1 = "Étrange d'entendre cela d'un pirate de potence, Portugais. Je vais te laisser partir... ne me demande pas pourquoi, mais dégage au tout premier port. Et souviens-toi que je ne serai pas aussi clément si nous nous rencontrons à nouveau.";
			link.l1.go = "Portugal_treasure_4";
		break;
		
		case "Portugal_treasure_3":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			pchar.questTemp.Portugal.Villemstad = "true";//сдать губернатору
			AddQuestRecord("Portugal", "21");
		break;
		
		case "Portugal_treasure_4":
			dialog.text = "Vraiment ? J'aimerais cela, capitaine ! Ne commanderez-vous pas qu'on apporte ici un peu de rhum ? Vous savez, juste pour célébrer vos qualités chevaleresques, notre relation et le sursis de ma sentence ?";
			link.l1 = "Ne fais pas de plaisanteries malfaisantes, tu es encore mon prisonnier jusqu'à la première côte. Adieu.";
			link.l1.go = "Portugal_treasure_5";
		break;
		
		case "Portugal_treasure_5":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			pchar.quest.Remove_Portugal.win_condition.l1 = "Location_Type";
			pchar.quest.Remove_Portugal.win_condition.l1.location_type = "town";
			pchar.quest.Remove_Portugal.function = "RemovePortugal";
			AddQuestRecord("Portugal", "20");
		break;
		
		case "Portugal_treasure_6":
			dialog.text = "Je vois... alors ce sera la potence. Je m'y attendais. Écoutez bien ce que je vais vous dire, capitaine. Vous étiez si avide de me garder en vie pour m'exécuter correctement plus tard, et je vous en remercie. Je suppose qu'il serait stupide de ma part de vous demander de changer d'avis comme ça, n'est-ce pas ? Et que diriez-vous si je vous proposais quelque chose en échange ? Un marché, pour ainsi dire, hein ?";
			link.l1 = "Je ne dirai rien, Portugais. Tu es un pirate et un bâtard. Tu répondras de tes crimes à Willemstad.";
			link.l1.go = "Portugal_treasure_2_1";
			link.l2 = "Un marché ? Que peux-tu offrir ?";
			link.l2.go = "Portugal_treasure_7";
			link.l3 = "Je n'ai pas besoin de ton marché, va-t'en dès le premier port. C'est ton jour de chance.";
			link.l3.go = "Portugal_treasure_4";
		break;
		
		case "Portugal_treasure_7":
			dialog.text = "Vous savez, un tel sauvetage persistant de ma vie malgré les raisons désagréables qui le motivent mérite tout de même une certaine gratitude. Et Bartolomeo le Portugais sait ce que c'est que d'être reconnaissant. Maintenant écoutez, un mois avant que vous et moi ne nous rencontrions, nous avons capturé un navire de la Compagnie. Ils se sont battus comme des diables jusqu'au dernier homme. Mais leurs cales ne contenaient que des boulets de canon et des rats\nMon équipage n'a pas aimé cela, pourtant j'ai trouvé un coffre très intéressant et des papiers dans la cabine du capitaine. C'était un navire courrier, livrant des échantillons de mines quelque part en Amazonie. Des diamants purs et des rubis, une vraie fortune !";
			link.l1 = "Un prix intéressant... Maintenant, je vois pourquoi la Compagnie s'intéresse tant à vous, mais quel est le but de votre histoire ?";
			link.l1.go = "Portugal_treasure_8";
		break;
		
		case "Portugal_treasure_8":
			dialog.text = "Mes premiers maîtres Vazquez et Franz Garcke maintenaient l'ordre parmi l'équipage, alors j'ai décidé de tenter ma chance. J'ai caché les pierres d'eux et brûlé les papiers. Les Hollandais avaient gravement endommagé notre gréement pendant l'abordage et nous avons dû prendre l'Albatross dans une petite baie d'une petite île au nord. Je suis allé plus profondément dans les jungles seul pendant que tout l'équipage réparait la frégate. J'ai enterré les pierres, les garder à bord était trop risqué étant donné les circonstances. Mon plan était de m'échapper de mon cher équipage au tout premier port, acheter ou voler un petit bateau et naviguer vers l'île, récupérer mon prix, et ensuite... adieux à ma vieille vie ! L'Europe, un manoir décent, une femme chaude, tu connais la suite...";
			link.l1 = "Je parie que quelque chose a mal tourné.";
			link.l1.go = "Portugal_treasure_9";
		break;
		
		case "Portugal_treasure_9":
			dialog.text = "Tout a mal tourné ! Cette maudite île s'est avérée être le pays natal d'une horde de cannibales locaux. Ils nous ont attaqués dès que je suis revenu sur le rivage. Nous avons dû appareiller au plus vite, c'est alors que j'ai été touché. Je pensais que ce n'était qu'une égratignure.\nQuelques jours plus tard, je gisais à moitié mort de fièvre et apparemment, j'ai dit quelque chose à propos des pierres. Franz et Vazquez ont réalisé que j'avais caché quelque chose sur l'île, mais ils ne connaissaient pas l'emplacement exact. Ils n'aimaient pas l'idée d'errer là-bas en se faisant constamment tirer dessus par les Indiens. Alors ces salauds m'ont traîné jusqu'au port le plus proche, puisque notre médecin avait été tué lors de notre combat avec les Hollandais, ils avaient besoin d'un nouveau.\nC'est ainsi que je me suis retrouvé chez ce médecin, ils voulaient me ramener à la conscience assez longtemps pour me torturer et découvrir l'emplacement des pierres. Je crois qu'ensuite, ils m'auraient découpé et nourri les crabes avec ma viande juteuse.";
			link.l1 = "Je ne peux pas dire que je les juge - tu essayais d'entuber tes hommes. Alors je te demande encore, pourquoi me parles-tu de ça ?";
			link.l1.go = "Portugal_treasure_10";
		break;
		
		case "Portugal_treasure_10":
			dialog.text = "Ces chiens n'étaient pas des gens, crois-moi, ils sont maintenant tous à leur place méritée - l'enfer, ha-ha ! En échange de ma liberté et de ma vie, je peux indiquer l'emplacement exact des trésors hollandais.";
			link.l1 = "Non, Bart, ta trahison m'a totalement convaincu de ta méchanceté. Willemstad et une juste rétribution t'attendent. Pas d'accord.";
			link.l1.go = "Portugal_treasure_2_1";
			link.l2 = "Et suis-je censé croire que ces gemmes existent vraiment ? Peu importe, je ne perdrai rien de toute façon... L'affaire était le début de cette histoire et l'affaire en sera la fin. J'accepte vos termes, Portugais.";
			link.l2.go = "Portugal_treasure_11";
		break;
		
		case "Portugal_treasure_11":
			dialog.text = "Considérez cela comme ma modeste gratitude. Eh, je voudrais bien savoir combien vaut la peau de Bartolomeo le Portugais en pesos brillants, ha ! Je comprends que vos objectifs étaient strictement pratiques, mais tout de même, merci, capitaine, pour tout, ha-ha\nC'est aux Turcs, les jungles non loin de ses rives. Trouvez un arbre sec et tordu, il n'y a qu'un tel arbre là-bas. J'ai enterré le coffre près de lui. Alors n'oubliez pas de prendre une pelle. Bonne chasse...";
			link.l1 = "D'accord, je m'en souviendrai et tu peux prendre une chaloupe tout de suite et t'éloigner de mon navire. Adieu.";
			link.l1.go = "Portugal_treasure_12";
		break;
		
		case "Portugal_treasure_12":
			dialog.text = "Une dernière chose, capitaine. Je suppose qu'il y a encore beaucoup de sauvages, mais ce n'est pas seulement d'eux que vous devriez vous inquiéter. Vasquez n'était pas sur l'‘Albatross’, n'est-ce pas? Le Maudit Don est trop malin... surveillez vos arrières jusqu'à ce que vous le voyiez pendu ou avec une balle dans la tête.";
			link.l1 = "Merci pour ton avertissement, Portugais. Maintenant, aurais-tu l'amabilité de quitter mon navire déjà... ne teste pas ma patience.";
			link.l1.go = "Portugal_treasure_13";
		break;
		
		case "Portugal_treasure_13":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 2.0);
			AddQuestRecord("Portugal", "23");
			pchar.quest.Portugal_Terks.win_condition.l1 = "location";
			pchar.quest.Portugal_Terks.win_condition.l1.location = "Terks_Jungle_01";
			pchar.quest.Portugal_Terks.function = "CreateHollIndBattle";
		break;
		
		case "Avendel_Marigo":
			pchar.quest.SetAvendelMarigoOver.over = "yes"; //снять таймер
			dialog.text = "Oh, et qui est-ce ! Capitaine "+pchar.name+" lui-même ! Voulez-vous un verre ?";
			link.l1 = "Tu sais, je suis en fait heureux de te revoir. Mais peut-être ai-je été trop brusque avec toi à la Martinique.";
			link.l1.go = "Avendel_Marigo_1";
		break;
		
		case "Avendel_Marigo_1":
			dialog.text = "Peu importe, capitaine ! Ce qui est fait est fait... Mais à vrai dire, je t'avais vraiment donné une raison de me renvoyer... Mais hé, tu ne devineras jamais qui est un invité à Phillipsburg aujourd'hui !";
			link.l1 = "Ne me dis pas que c'est...";
			link.l1.go = "Avendel_Marigo_2";
		break;
		
		case "Avendel_Marigo_2":
			dialog.text = "Non-non, capitaine, ce n'est pas les Portugais. Et ce n'est pas encore un bâtard blessé. C'est bien mieux ! C'est Hernando Vasquez... Le Don Sanglant en personne ! Il est l'invité du gouverneur local depuis quelques jours.";
			link.l1 = "Vasquez? L'invité du gouverneur? Je vois maintenant. Hugo, dis-moi en plus à ce sujet, bon sang, que diable se passe-t-il ici?";
			link.l1.go = "Avendel_Marigo_3";
		break;
		
		case "Avendel_Marigo_3":
			pchar.questTemp.Portugal.AvMoney = 10000;
			dialog.text = "Eh bien, je sais beaucoup de choses... mais grâce à notre voyage, je suis à nouveau ruiné. Peut-être que ton besoin de cette information vaut quelques pesos ?";
			link.l1 = "Hugo, tu es toujours un extorqueur et un vaurien ! Dis ce que tu as, prends 5000 pesos juste par amitie ancienne.";
			link.l1.go = "Avendel_Marigo_4_1";
			if (sti(pchar.money) >= 10000)
			{
			link.l2 = "Je ne suis pas vraiment surpris. Tiens, prends 10000 pesos et j'espère pour toi que tes informations valent cette somme !";
			link.l2.go = "Avendel_Marigo_4_2";
			}
			link.l3 = "J'ai une meilleure proposition pour vous. Que diriez-vous de rejoindre mon équipage ? Je suppose que vous avez un talent pour conclure et trouver des affaires rentables, alors si vous en avez assez de faire semblant d'être un vaillant combattant - vous êtes plus que bienvenu pour prendre le poste de mon intendant.";
			link.l3.go = "Avendel_Marigo_4_3";
		break;
		
		case "Avendel_Marigo_4_1":
			pchar.questTemp.Portugal.AvMoney = 15000;
			dialog.text = "Non, capitaine, cela ne va pas marcher comme ça ! Vous avez raflé une grosse somme avec ce maudit Portugais, j'en suis sûr. Considérez donc que c'est ma part, ne soyez pas si avide. 15000 pièces et pas un peso de moins !";
			if (sti(pchar.money) >= 15000)
			{
			link.l1 = "Ah, allez au diable, prenez-les !";
			link.l1.go = "Avendel_Marigo_4_2";
			}
			link.l2 = "Eh bien, et on dit que la cupidité est bonne... N'est-ce pas un peu trop pour toi, hein ?";
			link.l2.go = "Avendel_Marigo_wait";
		break;
		
		case "Avendel_Marigo_4_2":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Portugal.AvMoney));
			dialog.text = "Alors ça c'est le butin pour moi ! ... Écoute, Vasquez naviguait avec moi sur le même navire, mais pendant que je récurais le pont pour payer le voyage, il se reposait dans une cabine, donc Dieu merci, nous nous sommes rarement croisés et il ne m'a pas reconnu. Mais j'ai commencé à suivre ce diable immédiatement... Une histoire intéressante lui est arrivée.";
			link.l1 = "Allez-y ! Que fait-il dans le palais du gouverneur ?";
			link.l1.go = "Avendel_Marigo_5";
		break;
		
		case "Avendel_Marigo_5":
			dialog.text = "Je ne sais pas grand-chose, mais la garnison a été alertée quelques jours après son arrivée et le grand vaisseau de guerre a soudain levé l'ancre et est parti en toute hâte, il a navigué vers le nord-ouest je crois. Toute la ville était perdue en conjectures et commérages...";
			link.l1 = "Alors c'était le navire que j'ai rencontré ! Intriguant... Ne t'éloigne pas du sujet, Hugo, continue ton histoire, je te prie.";
			link.l1.go = "Avendel_Marigo_6";
		break;
		
		case "Avendel_Marigo_6":
			dialog.text = "Eh bien, comme je l'ai dit, le navire avait disparu et Vasquez était devenu une sorte d'invité de notre gouverneur Martin Thomas. Je le vois parfois en ville, il est toujours en compagnie de quelques soldats. Je ne sais pas si c'est son escorte ou son convoi, ha-ha. Mais seules les personnes à la résidence pourraient vous en dire plus sur le Don.";
			if (CheckAttribute(pchar, "questTemp.Portugal.AvOfficer"))
			{
				link.l1 = "Peut-être as-tu raison. Mais nous avions un accord, tu te souviens ? Ne joue pas au héros, va à mon navire et attends mon retour. Je vais essayer de parler avec notre gouverneur hospitalier.";
				link.l1.go = "Avendel_hire";
			}
			else
			{
				link.l1 = "Eh bien, c'était intéressant. Tu m'as vraiment aidé, Hugo. Bois ton rhum, le reste ne te concerne pas.";
				link.l1.go = "Avendel_Marigo_del";
			}
			AddDialogExitQuestFunction("InMarigoResidence");
		break;
		
		case "Avendel_Marigo_4_3":
			dialog.text = "Es-tu sérieux, capitaine ? Qu'est-ce qui te prend ? Tu m'as chassé en me pointant une arme au visage et maintenant tu viens avec de telles propositions ?";
			if (sti(pchar.money) >= 10000)
			{
			link.l1 = "Oublie cela, je n'étais pas moi-même et je suis désolé, l'avidité m'a consumé je suppose. Tiens, prends 10000 pesos et dis-moi ce que tu sais sur Vasquez, je suis pressé.";
			link.l1.go = "Avendel_Marigo_4_2";
			}
			link.l2 = "Peut-être devrais-je m'excuser pour cela. Vous êtes un combattant pathétique, mais vous vous débrouillez bien avec les pièces. Je répète ma proposition, qu'en dites-vous ?";
			link.l2.go = "Avendel_Marigo_7";
		break;
		
		case "Avendel_Marigo_7":
			pchar.questTemp.Portugal.AvMoney = 20000;
			pchar.questTemp.Portugal.AvOfficer = "true";
			dialog.text = "Que puis-je dire... Je vais accepter, mais seulement après avoir reçu ma part, capitaine. Dix pour cent, souvenez-vous ? Vous avez reçu deux mille pour ce scélérat, alors si vous me demandez de rejoindre votre équipage, vous feriez mieux de commencer par effacer vos dettes. Dix pour cent et pas de discussion !";
			link.l1 = "Tu es un tel filou, Hugo. Je n'ai pas autant sur moi maintenant, mais je reviendrai bientôt. Reste ici.";
			link.l1.go = "Avendel_Marigo_wait";
			if (sti(pchar.money) >= 20000)
			{
			link.l2 = "J'espere que tu sauras justifier mes attentes avec ton flair pour les affaires, ha ! Prends ta part !";
			link.l2.go = "Avendel_Marigo_4_2";
			}
		break;
		
		case "Avendel_Marigo_wait":
			dialog.text = "C'est à vous de décider, capitaine. Je resterai ici un moment. Revenez si vous changez d'avis.";
			link.l1 = "Très bien, Hugo.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Avendel_Marigo_repeat";
		break;
		
		case "Avendel_Marigo_repeat":
			dialog.text = "Avez-vous changé d'avis, capitaine? J'attends donc mon argent.";
			if (sti(pchar.money) >= sti(pchar.questTemp.Portugal.AvMoney))
			{
				link.l1 = "Prends tes pièces, vaurien ha-ha !";
				link.l1.go = "Avendel_Marigo_4_2";
			}
			link.l2 = "Je n'ai pas encore une telle somme.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Avendel_Marigo_repeat";
		break;
		
		case "Avendel_Marigo_del":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Avendel_hire":
			DialogExit();
			LAi_SetImmortal(npchar, false); // patch-8
			SetCharacterRemovable(npchar, true);
			npchar.quest.OfficerPrice = sti(pchar.rank)*1000;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.loyality = 25;
			npchar.dialog.FileName = "Enc_Officer_dialog.c";
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "Servant":
			//pchar.quest.InMarigoResidenceOver.over = "yes"; //снять таймер
			dialog.text = "Bonjour, capitaine. Vous voulez quelque chose ?";
			link.l1 = "Non-non, j'attends juste, quand le sieur Thomas sera-t-il libre ? J'attends une audience... oui. Dites-moi, son Excellence considère-t-il vraiment le célèbre pirate Hernando Vasquez comme son ami ?";
			link.l1.go = "Servant_1";
		break;
		
		case "Servant_1":
			dialog.text = "Ne vous inquiétez pas, monsieur, il devrait être libéré à tout moment maintenant, et bien sûr que non, monsieur ! Ce bandit s'est rendu aux autorités, mais d'une manière ou d'une autre, il n'a pas été pendu. Peut-être a-t-il acheté sa vie en trahissant ses anciens complices... Je ne suis pas sûr. Il a été emprisonné ici pendant plusieurs jours... C'était un cauchemar, monsieur ! Cette bête sous forme humaine vivait dans notre manoir !";
			link.l1 = "Un cauchemar, c'est! Que pourrait bien dire cette bête à monsieur Thomas pour éviter la potence? Je ne peux même pas imaginer!";
			link.l1.go = "Servant_2";
		break;
		
		case "Servant_2":
			dialog.text = "Je ne sais pas non plus, mais je peux te confier en secret que tous les serviteurs étaient contents lorsque Son Excellence s'est débarrassé d'un tel invité...";
			link.l1 = "Tu t'en es débarrassé ? A-t-il enfin eu ce qu'il méritait ?";
			link.l1.go = "Servant_3";
		break;
		
		case "Servant_3":
			dialog.text = "Pas tout à fait. Pas encore. Il y a quelques jours, il a été emmené dans une brigantine militaire qui a navigué vers Willemstad. Voyez-vous, monsieur Thomas avait perdu tout intérêt pour le vaurien, il semble qu'il ait essayé de le duper\nAussi, ils disent que son ancien capitaine a été attrapé - Bartolomeo le Portugais ! Réfléchissez-y ! On dirait que la Compagnie veut les pendre ensemble. Les oiseaux disent que le procès sera dans un mois, mais pourquoi attendre aussi longtemps ?";
			link.l1 = "Les Portugais ?! Hm... merci de me tenir compagnie, ami... il semble que monsieur Thomas soit libre maintenant, je vais prendre congé.";
			link.l1.go = "Servant_4";
		break;
		
		case "Servant_4":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Portugal", "31");
			pchar.questTemp.Portugal = "SeekPortVillemstad";
			//SetFunctionTimerCondition("InMarigoResidenceOver", 0, 0, 30, false);
			colonies[FindColony("Villemstad")].jail = 0;
			sld = characterFromId("Portugal");
			sld.model = "Port_A"; //меняем модель
			sld.dialog.currentnode = "Portugal_free";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "Villemstad_prison", "goto", "goto9");
			sld = GetCharacter(NPC_GenerateCharacter("PortHolOfficer", "off_hol_4", "man", "man", 35, HOLLAND, 30, true, "soldier"));
			FantomMakeCoolFighter(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+10, 100, 100, "blade_19", "pistol3", "grapeshot", 100);
		
			LAi_CharacterDisableDialog(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Villemstad_prison", "goto", "goto23");
			LAi_LocationDisableOfficersGen("Villemstad_prison", true);//офицеров не пускать
		break;
		
		case "Vaskez":
			dialog.text = "Maintenant vous êtes morts... tous les deux !";
			link.l1 = "...";
			link.l1.go = "Vaskez_1";
		break;
		
		case "Vaskez_1":
			DialogExit();
			LAi_ActorAnimation(npchar, "shot", "VaskezFight", 2.0);
		break;
		
		case "Portugal_free":
			if (LAi_group_GetTarget(pchar) <= 0)
			{
				dialog.text = "Eh bien, voila quelqu'un que je ne m'attendais pas à voir, capitaine ! Mais cela ne ressemble pas à une visite amicale, avec tout ce sang, ce vacarme, et cette fusillade, ou bien est-ce une sorte de célébration avec des feux d'artifice, hein ?";
				link.l1 = "Arrête de faire tes blagues malfaisantes, Portugais. Je n'aime simplement pas la manière dont tu as utilisé ta liberté que tu as achetée de moi. J'ai mis trop d'efforts à sauver ton misérable cul pour te laisser te faire prendre si stupidement juste après notre séparation !";
				link.l1.go = "Portugal_free_1";
				// belamour legendary edition -->
				link.l2 = "Eh bien, je m'ennuyais ! Alors je suis venu ici pour te rendre visite. Es-tu à l'aise ici, mon ami !";
				link.l2.go = "Portugal_free_1a";
				// <-- legendary edition
			}
			else
			{
				dialog.text = "Sois prudent, ami ! Eh, dommage que je ne puisse pas t'aider !";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Portugal_free";
			}
		break;
		// belamour legendary edition -->
		case "Portugal_free_1a":
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			dialog.text = "Alors, la noblesse n'est parfois pas affectée par les pièces, hein ? Hah... ATTENTION, JUSTE DERRIÈRE TOI !";
			link.l1 = "Agh, pas encore cette merde!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CreateErnandoVaskez");
			NextDiag.TempNode = "Portugal_free";
		break;
		
		case "Portugal_free_1":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		// <-- legendary edition
			dialog.text = "Alors, la noblesse n'est parfois pas affectée par les pièces, hein ? Hah... ATTENTION, JUSTE DERRIÈRE TOI !";
			link.l1 = "Ah, pas encore cette merde !";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CreateErnandoVaskez");
			NextDiag.TempNode = "Portugal_free";
		break;
		
		case "Portugal_free_2":
			dialog.text = "Et je t'ai prévenu que ce gars était un problème !";
			link.l1 = "Il a failli me tirer une balle dans le dos ! Comment a-t-il pu passer ?";
			link.l1.go = "Portugal_free_3";
		break;
		
		case "Portugal_free_3":
			dialog.text = "J'ai vu qu'il avait un crochet, il semble que quelqu'un le lui avait donné... il avait toujours des connexions dans les basses sphères. Eh bien, capitaine, je crois que nous devrions quitter cet endroit, n'êtes-vous pas d'accord ?";
			link.l1 = "Tu ne dis pas! Bien, dépêchons-nous avant que toute la garnison n'arrive ici. Je vais briser ton verrou en un rien de temps...";
			link.l1.go = "Portugal_free_4";
		break;
		
		case "Portugal_free_4":
			DialogExit();
			InterfaceStates.Buttons.Save.enable = true;//разрешить сохраняться
			chrDisableReloadToLocation = false;
			DoQuestReloadToLocation("Villemstad_Exittown", "rld", "loc17", "PortugalFree");
		break;
		
		case "Portugal_free_5":
			dialog.text = "Tu sais, capitaine, cet air frais... tu commences à l'apprécier seulement après avoir passé quelques semaines dans un cachot juste après que le canot de ton navire ait été trouvé par la patrouille locale. Je suppose que je te dois encore pour mon sauvetage.";
			link.l1 = "Pas besoin, Portugais. Je ne suis pas un chevalier honorable, je fais juste... Je fais ce que je pense être juste et nécessaire.";
			link.l1.go = "Portugal_free_6";
		break;
		
		case "Portugal_free_6":
			dialog.text = "Ha, et c'est une qualité parfaite ! Mais j'insiste, prends-le... c'est la seule chose que j'ai pu cacher dans la prison... Oui, tu as bien compris. C'est mon talisman. Il m'a toujours porté chance en mer. Tu es un bon marin et toi ou ton navigateur serez capables de l'utiliser, j'en suis sûr.";
			link.l1 = "Oui, et tu as eu assez de chance pour tomber directement entre les mains des Hollandais avec ce talisman.";
			link.l1.go = "Portugal_free_7";
		break;
		
		case "Portugal_free_7":
			dialog.text = "Eh! Je suis encore en vie, n'est-ce pas? Et sachez-le, je ne suis plus en prison. Prenez-le, capitaine, il est temps que le talisman vous serve. Et je vous remercie encore!";
			link.l1 = "Adieu donc, Portugais. Et, s'il te plaît, essaie de rester loin de la potence ! Juste pour l'amour de mon dur labeur, ha-ha !";
			link.l1.go = "Portugal_free_8";
		break;
		
		case "Portugal_free_8":
			TakeNItems(pchar, "talisman2", 1);
			Log_Info("You have received the talisman");
			PlaySound("interface\important_item.wav");
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			LAi_LocationDisableOfficersGen("Villemstad_prison", false);//офицеров пускать
			AddQuestRecord("Portugal", "34");
			CloseQuestHeader("Portugal");
			pchar.questTemp.Portugal = "end";
			pchar.questTemp.Portugal.GG1 = "true"; // Jason Дороже золота
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
