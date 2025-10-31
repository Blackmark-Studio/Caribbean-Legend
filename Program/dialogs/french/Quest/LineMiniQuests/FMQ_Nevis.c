// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
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
			dialog.text = "Un bug évident. Parlez-en aux développeurs.";
			link.l1 = "Ah, je le ferai.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "seafox":
			DelMapQuestMarkCity("Charles");
			LAi_SetImmortal(npchar, false);
			DelLandQuestMark(npchar);
			LAi_RemoveLoginTime(npchar);
			PlaySound("Voice\English\LE\SeaFox\SeaFox_01.wav");
			dialog.text = TimeGreeting()+", capitaine. (salue) Permettez-moi de me présenter - Lieutenant "+GetFullName(npchar)+", Regiment Maritime d'Antigua, en garnison à Saint-Jean. J'ai une faveur à demander.";
			link.l1 = "Salutations Lieutenant Gretton. Mon nom est "+GetFullName(pchar)+" . Quel genre de service ?";
			link.l1.go = "seafox_1";
		break;
		
		case "seafox_1":
			dialog.text = "Laissez-moi vous expliquer brièvement la situation. Quatre de mes hommes et moi naviguions de St. Johns à Sint-Maarten quand une tempête a frappé notre navire. Le mauvais temps n'a pas duré longtemps mais c'était suffisant pour que notre vieux rafiot prenne une voie d'eau. Nous avons dû changer de cap et nous arrêter ici pour des réparations. Cela prend du temps que nous n'avons pas\nNous sommes pressés de nous rendre à Sint-Maarten, en particulier à Grand Case Beach. Aidez-moi, capitaine, et je vous récompenserai généreusement. Deux jours de voyage pour une paye généreuse !";
			link.l1 = "Le paiement devrait être généreux en effet, lieutenant, si vous voulez que j'introduise clandestinement des marins anglais sur une île hollandaise.";
			link.l1.go = "seafox_2";
		break;
		
		case "seafox_2":
			dialog.text = ""+UpperFirst(GetAddress_Form(PChar))+", cela ne devrait pas vous inquiéter. Vous ne risquez rien. Il suffit de nous déposer dans la baie, et c'est tout. Alors, marché conclu ?";
			link.l1 = "D'accord, je suis partant. Ce n'est pas si loin d'ici. Parlons de cette paie.";
			link.l1.go = "seafox_3";
			link.l2 = "Je suis désolé, mais j'ai des affaires urgentes dans une autre direction et je préfère ne pas contrarier les Hollandais.";
			link.l2.go = "seafox_exit";
		break;
		
		case "seafox_exit":
			dialog.text = "Comme vous dites, capitaine. Je vais continuer à chercher alors. Adieu et bon vent !";
			link.l1 = "Adieu, lieutenant.";
			link.l1.go = "seafox_exit_1";
		break;
		
		case "seafox_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
		break;
		
		case "seafox_3":
			GiveItem2Character(pchar, "purse2"); 
			Log_Info("You have received a purse of doubloons");
			dialog.text = "Dix mille pièces de huit. Voici une avance.";
			link.l1 = "Bien. Embarque tes hommes, ne perdons pas de temps.";
			link.l1.go = "seafox_4";
		break;
		
		case "seafox_4":
			dialog.text = "Oui, oui, capitaine !";
			link.l1 = "...";
			link.l1.go = "seafox_5";
		break;
		
		case "seafox_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "FMQN_SailMaarten", 10.0);
			AddQuestRecord("FMQ_Nevis", "1");
			pchar.questTemp.FMQN = "begin";
			
			chrDisableReloadToLocation = false;
			sld = CharacterFromID("FMQN_seafox_1");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload4_back", "", "", "", "", 10.0); // англичане на борт
			sld.location = "None";
			AddPassenger(pchar, sld, false);//добавить пассажира
			SetCharacterRemovable(sld, false);
			pchar.quest.FMQN_sailing.win_condition.l1 = "location";
			pchar.quest.FMQN_sailing.win_condition.l1.location = "Shore40";
			pchar.quest.FMQN_sailing.win_condition.l2 = "Ship_location";
			pchar.quest.FMQN_sailing.win_condition.l2.location = "Shore40";
			pchar.quest.FMQN_sailing.function = "FMQN_ArriveMaarten";
			if(bImCasual)
			{
				NewGameTip(StringFromKey("FMQ_69"));
			}
			else SetFunctionTimerCondition("FMQN_SailingLate", 0, 0, 10, false);
			for(i = 0; i < MAX_LOCATIONS; i++)
			{	
				sld = &Locations[i];
				if (CheckAttribute(sld, "islandId") && sld.islandId == "SentMartin")
				{
					sld.DisableEncounters = true;	
				}
			}
			sld = &Locations[FindLocation("Shore40")];
			sld.QuestlockWeather = "23 Hour";
			AddMapQuestMarkShore("Shore40", true);
		break;
		
		case "seafox_6":
			PlaySound("Voice\English\LE\SeaFox\SeaFox_02.wav");
			dialog.text = "Merci pour la traversée sans encombre, capitaine ! Je suis vraiment désolé, mais je ne peux pas vous payer à cet instant précis... il devait y avoir une de nos chaloupes dans cette zone, mais elle n'est pas là. Comme vous pouvez le constater. Je dois vous demander encore une fois votre aide. Pourriez-vous attendre dans cette baie pendant deux ou trois jours ? Nous devons aller jeter un œil aux alentours. Une fois que nous serons de retour, emmenez-nous à Antigua. Le colonel Fox vous récompensera généreusement.";
			link.l1 = "Hmm... Ce n'est pas vraiment ce dont nous étions convenus...";
			link.l1.go = "seafox_7";
		break;
		
		case "seafox_7":
			dialog.text = "Je vous en prie, ne soyez pas frustré, capitaine. Je sais ce que vous devez ressentir mais hélas : je n'ai pas d'argent du tout. Je peux vous promettre que vous recevrez une compensation pour les deux voyages et pour nous avoir attendus ici. Ainsi que les remerciements du colonel Fox lui-même !";
			link.l1 = "Je ne peux pas exactement te laisser dans le pétrin... Très bien, Lieutenant Gretton. J'attendrai trois jours, mais pas plus.";
			link.l1.go = "seafox_8";
		break;
		
		case "seafox_8":
			dialog.text = "Merci "+GetAddress_Form(NPChar)+" ! Nous nous dirigeons vers l'intérieur des terres. Je jure que nous serons de retour dans 72 heures, pas une minute de plus.";
			link.l1 = "Bon vent, lieutenant. Ne te fais pas attraper.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_EnglishmanGo");
		break;
		
		case "seafox_9":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\LE\SeaFox\SeaFox_02.wav");
			dialog.text = "Quelle rencontre fortuite ! Je pensais que vous nous attendriez à la plage de Grand Case, Capitaine "+pchar.lastname+" !";
			link.l1 = "Bonjour lieutenant, la surprise est mutuelle. Je ne m'attendais pas à te voir vêtu comme un soldat néerlandais.";
			link.l1.go = "seafox_10";
		break;
		
		case "seafox_10":
			dialog.text = "C'est notre déguisement... Pourquoi êtes-vous ici, "+GetAddress_Form(NPChar)+" ?";
			link.l1 = "C'est un déguisement dangereux, matelot. Les espions risquent d'être exécutés sommairement sans procès. Et en parlant d'exécution, si tu veux éviter la tienne, tu ferais mieux d'écouter.";
			link.l1.go = "seafox_11";
		break;
		
		case "seafox_11":
			dialog.text = "Tu as toute mon attention.";
			link.l1 = "J'ai navigué jusqu'à Philipsburg et parlé avec les locaux après votre débarquement. Les Hollandais sont sur votre piste. Ils sont au courant de votre mission pour secourir ces officiers anglais de haut rang capturés.";
			link.l1.go = "seafox_12";
		break;
		
		case "seafox_12":
			dialog.text = "Mille tonnerres et damnation ! Comment diable ont-ils pu découvrir cela ?";
			link.l1 = "Un des officiers anglais capturés. En échange de sa liberté, il a raconté aux Hollandais tout ce qu'il savait sur l'opération de sauvetage. Tout Philipsburg est prêt pour que vous et vos hommes essayiez d'entrer dans la ville. Pour aggraver les choses, une corvette hollandaise patrouille la mer autour de Sint-Maartin. C'est un piège, lieutenant.";
			link.l1.go = "seafox_13";
		break;
		
		case "seafox_13":
			dialog.text = RandSwear()+"Ce scélérat déshonorant ! Je découvrirai qui est ce traître et le dénoncerai devant le Parlement !";
			link.l1 = "Il faudra attendre, M. Gretton. Retournez à Grand Case Beach ce soir et remontez sur mon navire avant qu'ils ne vous attrapent.";
			link.l1.go = "seafox_14";
		break;
		
		case "seafox_14":
			dialog.text = "Et abandonner des gentilshommes anglais dans une prison hollandaise ? Je préférerais mourir, monsieur. Je ne trahirai pas le Colonel Fox.";
			link.l1 = "Hm, penses-tu que les Hollandais te laisseront choisir entre la potence ou le peloton d'exécution après t'avoir capturé ?";
			link.l1.go = "seafox_15";
		break;
		
		case "seafox_15":
			dialog.text = "Ne crois pas qu'ils te laisseront quitter ces lieux à la voile non plus, Capitaine de Maure. Nous sommes tous deux dans cette affaire jusqu'au cou.";
			link.l1 = "Diantre, tu as probablement raison. Cette corvette nous tombera dessus dès que nous lèverons l'ancre...";
			link.l1.go = "seafox_16";
		break;
		
		case "seafox_16":
			dialog.text = "Les Hollandais savent peut-être que nous arrivons, mais ils ne savent pas *comment* nous arrivons. Nous avons déjà pris soin du déguisement - regarde cet uniforme. Charmant, n'est-ce pas ? Si notre plan n'avait pas été trahi, nous serions simplement allés à la prison locale, les aurions pris par surprise et tué tout le monde à l'intérieur. Mais ils sont certainement en embuscade là-bas. Alors nous improvisons\nCapitaine, allez à l'église de Philipsburg et trouvez un prédicateur là-bas nommé Filippe Jacobsen. Il devrait être là de six à dix heures du matin. Filippe est l'un de nos hommes à l'intérieur\nDites-lui ce mot de passe : 'Il y a combien de temps que les marins captifs ont confessé ?'. Après cela, dites-lui la situation et exigez son assistance au nom du Colonel Fox. Ensuite, vous me livrez sa réponse. Simple et sans risque pour vous.";
			link.l1 = "Ça semble sacrément risqué de demander une confession dans une église calviniste hollandaise, lieutenant. Le pasteur essaiera de me pendre pour être papiste. D'accord, parlez-moi de ces uniformes... les avez-vous pris à une patrouille hollandaise ?";
			link.l1.go = "seafox_17";
		break;
		
		case "seafox_17":
			dialog.text = "Oui, monsieur.";
			link.l1 = "Et où sont-ils maintenant ?";
			link.l1.go = "seafox_18";
		break;
		
		case "seafox_18":
			dialog.text = "Retenus en otages dans les buissons non loin de cette caverne.";
			link.l1 = "Compris. Gardez-les en sécurité, je me rends en ville. Attendez-moi ici et restez discrets - les Hollandais ratissent la jungle aussi bien que les mers à votre recherche.";
			link.l1.go = "seafox_19";
		break;
		
		case "seafox_19":
			dialog.text = "Nous serons silencieux comme des souris d'église, capitaine. Dépêchez-vous, je vous en prie !";
			link.l1 = "...​";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_ToChurch");
		break;
		
		case "seafox_20":
			PlaySound("Voice\English\soldier_common_4.wav");
			DelLandQuestMark(npchar);
			dialog.text = "Vous êtes de retour ? Capitaine, que faites-vous ici ? Allez en ville, vous attirez l'attention sur notre planque !";
			link.l1 = "Je suis de retour de la ville. Quel genre de jeux jouez-vous, vous les Anglais?";
			link.l1.go = "seafox_21";
		break;
		
		case "seafox_21":
			dialog.text = "Je vous demande pardon ?";
			link.l1 = "Je suis allé à l'église. Grand bâtiment, beau et austère, exactement comme ces iconoclastes néerlandais l'aiment. Devine quoi, lieutenant ? Il n'y a pas de prédicateur nommé Filippe Jacobsen.";
			link.l1.go = "seafox_22";
		break;
		
		case "seafox_22":
			dialog.text = "C'est impossible, il visite l'endroit chaque matin-";
			link.l1 = "Ferme-la et écoute-moi ! Si ton Jacobsen existe vraiment, il ne va pas à l'église ! Ils ne l'ont jamais vu ! Ni le matin, ni le soir ! Nom de Dieu, putain ! Pourquoi ai-je même accepté ce foutu boulot ?! Mené par un imbécile de fils de pute, novice, encore mouillé derrière les oreilles, lieutenant-";
			link.l1.go = "seafox_23";
		break;
		
		case "seafox_23":
			dialog.text = "Monsieur, j'exige réparation pour cet affront. Une fois que nous serons sortis d'ici, nous nous battrons en duel selon les coutumes de-";
			link.l1 = ""+RandSwear()+"";
			link.l1.go = "seafox_24";
		break;
		
		case "seafox_24":
			PlaySound("Ambient\Jail\chain.wav");
			PlaySound("Ambient\Land\door_001.wav");
			dialog.text = "Tais-toi, bordel de merde, vous tous !!! ... Je viens d'entendre quelque chose.";
			link.l1 = "";
			link.l1.go = "seafox_25";
		break;
		
		case "seafox_25":
			if (pchar.sex == "man") {PlaySound("VOICE\English\LE\SeaFox\SeaFox_04.wav");}
			dialog.text = "Sapristi, quelqu'un est dehors ! Toi ! Tu as ramené les Néerlandais ici, canaille !";
			link.l1 = ""+RandSwear()+"!!!";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattleFight");
		break;
		
		case "seafox_26":
			DelLandQuestMark(npchar);
			pchar.quest.FMQN_fail1.over = "yes";
			PlaySound("Voice\English\LE\SeaFox\SeaFox_02.wav");
			dialog.text = "Content de vous voir, monsieur, quelles nouvelles ?";
			link.l1 = "J'ai rencontré ton homme. Ce soir, il livrera du vin 'aromatisé' à la garnison de la prison. Il a obtenu une potion d'une gitane, pas mortelle, mais ils dormiront comme des morts. Tu dois y entrer ce soir et faire sortir tes messieurs capturés. Au fait, cette livraison de vin m'a coûté vingt-cinq doublons. Assure-toi de mentionner cela dans le rapport.";
			link.l1.go = "seafox_27";
		break;
		
		case "seafox_27":
			dialog.text = "Ne vous inquiétez pas pour l'argent. Capitaine, je vous demanderais de vous joindre à nous pour cette opération et de nous montrer le chemin vers la prison. Vous êtes déjà allé à Philipsburg, donc vous connaissez mieux la ville que nous. Pas besoin de nous accompagner à l'intérieur de la prison, nous nous chargerons nous-mêmes de l'évasion. Menez-nous simplement jusqu'à la porte.";
			link.l1 = "Que le diable m'emporte, Monsieur Gretton, ce boulot ne cesse de s'améliorer. La paie ferait mieux d'augmenter en conséquence.";
			link.l1.go = "seafox_28";
		break;
		
		case "seafox_28":
			dialog.text = "Cela ne fait aucun doute, capitaine. Vous ne regretterez pas de nous aider. Votre navire est-il à la plage de Grand Case ?";
			if (pchar.location.from_sea == "Shore40")
			{
				link.l1 = "Ouais.";
				link.l1.go = "seafox_29";
			}
			else
			{
				link.l1 = "Non.";
				link.l1.go = "seafox_29x";
			}
		break;
		
		case "seafox_29":
			dialog.text = "Bien. Alors préparez-vous et rejoignez-nous aux portes de la ville à onze heures du soir.";
			link.l1 = "Je te verrai là-bas.";
			link.l1.go = "seafox_30";
		break;
		
		case "seafox_29x":
			dialog.text = "Assurez-vous de l'y amener, car nous devons faire sortir nos hommes par la jungle. Naviguer depuis le port ou Simpson Bay est impossible à cause du fort. Préparez tout et retrouvez-nous aux portes de la ville à onze heures du soir.";
			link.l1 = "À bientôt là-bas.";
			link.l1.go = "seafox_30";
		break;
		
		case "seafox_30":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddDialogExitQuestFunction("FMQN_EnglandPrepare");
		break;
		
		case "seafox_31":
			PlaySound("Voice\English\Gr_hovernor01.wav");
			dialog.text = "Prêt, capitaine ?";
			link.l1 = "Oui.";
			link.l1.go = "seafox_32";
		break;
		
		case "seafox_32":
			dialog.text = "Allons-y alors.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_EnglandReload");
		break;
		
		case "seafox_33":
			dialog.text = "Chuttt... Capitaine ! C'est fait, foutons le camp d'ici !..";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_EnglandRunToJungle");
		break;
		
		case "seafox_34":
			dialog.text = "Je ne sais pas comment nous avons réussi, mais nous l'avons fait ! Rien de tout cela n'aurait été possible sans votre aide, monsieur. Maintenant, pour la partie relativement facile - nous devons quitter Sint-Maartin en vie et en un seul morceau. Allons à la plage de Grand Case !";
			link.l1 = "En avant !";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_EnglandRunToShore");
		break;
		
		case "seafox_35":
			PlaySound("Voice\English\LE\SeaFox\SeaFox_05.wav");
			dialog.text = "Capitaine "+pchar.lastname+"... "+GetAddress_Form(NPChar)+", merci pour votre aide ! Je vous supplie, ne quittez pas le port immédiatement mais restez ici un jour de plus pendant que je fais mon rapport au Colonel Fox. Rendez-lui visite demain, son bureau est dans le palais du gouverneur.";
			link.l1 = "Très bien, Lieutenant Gretton. Veuillez faire en sorte que cela en vaille la peine. Il va me falloir beaucoup de temps pour réparer ma réputation auprès des Hollandais à cause de votre escapade.";
			link.l1.go = "seafox_36";
		break;
		
		case "seafox_35x":
			PlaySound("Voice\English\LE\SeaFox\SeaFox_05.wav");
			dialog.text = "Merci pour votre assistance, capitaine ! Vous "+GetSexPhrase("vous êtes comporté comme un véritable héros","êtes une jeune femme très courageuse")+", "+GetAddress_Form(NPChar)+" ! C'est une tragédie que le lieutenant Gretton n'ait pas survécu. Il est mort en véritable gentilhomme et fils de l'Angleterre. Je vous demanderais de rester ici un jour de plus pendant que je fais mon rapport au colonel Fox. Rendez-lui visite demain, son bureau se trouve dans le palais du gouverneur.";
			link.l1 = "Très bien. Veuillez faire en sorte que cela en vaille la peine. Il me faudra beaucoup de temps pour réparer ma réputation auprès des Hollandais à cause de votre escapade.";
			link.l1.go = "seafox_36";
		break;
		
		case "seafox_36":
			dialog.text = "Ne vous inquiétez pas, "+GetAddress_Form(NPChar)+". Je vous donnerai le crédit le plus élevé possible dans mon rapport. (salue) Ce fut un plaisir, "+GetAddress_Form(NPChar)+" !";
			link.l1 = "... ";
			link.l1.go = "seafox_37";
		break;
		
		case "seafox_37":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", -1);
			pchar.quest.FMQN_eng_reward.win_condition.l1 = "Timer";
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.hour  = 6.0;
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQN_eng_reward.function = "FMQN_EnglandReward";
			AddQuestRecord("FMQ_Nevis", "28");
		break;
		
		case "soldier":
			PlaySound("Voice\English\soldier_common_2.wav");
			dialog.text = "Capitaine "+GetFullName(pchar)+"?";
			link.l1 = "Hm... Oui, que puis-je faire pour vous ?";
			link.l1.go = "soldier_1";
		break;
		
		case "soldier_1":
			dialog.text = "Le bureau du port nous a informés de l'arrivée récente de votre navire. Son Excellence Monsieur Martin Thomas, le gouverneur de Philipsburg, désire vous voir.";
			link.l1 = "Pour quelle raison? Suis-je en état d'arrestation?";
			link.l1.go = "soldier_2";
		break;
		
		case "soldier_2":
			AddLandQuestMark(characterFromId("Marigo_Mayor"), "questmarkmain");
			dialog.text = "Oh non, non, "+GetAddress_Form(NPChar)+" le capitaine, vous n'êtes pas en état d'arrestation. Le gouverneur a ordonné d'inviter chaque capitaine nouvellement arrivé à son palais pour du café et des présentations. Suivez-moi !";
			link.l1 = "On dirait une offre que je ne peux pas refuser. Montrez le chemin.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_ReloadToGovernor");
		break;
		
		case "hol_officer":
			PlaySound("Voice\English\hol_gov_complete.wav");
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", montrez-nous où vous avez vu ces soldats anglais.";
			link.l1 = "Ils se cachent dans une grotte dans la jungle, comme de vulgaires bandits.";
			link.l1.go = "hol_officer_1";
		break;
		
		case "hol_officer_1":
			dialog.text = "Mène la danse, nous te suivons !";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattleMarch");
		break;
		
		case "hol_officer_2":
			PlaySound("Voice\English\hol_gov_quest.wav");
			dialog.text = "Attendez capitaine ! Vous avez mentionné que vous aviez rencontré les espions là-bas - près de l'entrée de la grotte ?";
			link.l1 = "Oui. Je les ai aperçus brièvement entrer après qu'ils m'ont parlé.";
			link.l1.go = "hol_officer_3";
		break;
		
		case "hol_officer_3":
			dialog.text = "Il est fort probable qu'ils soient encore là-dedans. Si nous nous ruons tous en même temps, ils se retireront dans la grotte. Ce serait un cauchemar de les en déloger... Jouons cela intelligemment. Capitaine, vous y allez seul et vous les distrayez. Moi et mes hommes nous déplacerons vers ce puits sec au coin. Il mène directement à l'intérieur de la grotte. Ces salauds ne nous verront pas venir par derrière.\nVous entrez et si les espions sont encore là, parlez-leur, posez-leur des questions stupides, et occupez-les. Une fois que vous avez toute leur attention - jurez aussi grossièrement que possible. Vous êtes marin, cela devrait vous venir naturellement. Ce sera notre signal. Deux de mes hommes garderont l'entrée principale pour empêcher leur fuite par là. Nous les prendrons.";
			link.l1 = "Ton plan semble terriblement dangereux pour ma santé. À mon avis, ils essaieront simplement de me tuer en premier.";
			link.l1.go = "hol_officer_4";
		break;
		
		case "hol_officer_4":
			dialog.text = "Ne vous inquiétez pas, capitaine. Votre objectif est de crier aussi fort que possible dès que vous verrez le groupe de raid ennemi. S'ils vous attaquent - alors fuyez et continuez à crier. Mes hommes sont bien entraînés, alors ne vous inquiétez pas, ils mettront ces espions hors d'état de nuire avant que vous ne soyez blessé.";
			link.l1 = "Ils ont intérêt. J'y vais.";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattlePosition");
		break;
		
		case "hol_officer_5":
			PlaySound("Voice\English\hol_gov_common.wav");
			dialog.text = "Durs salauds qu'ils étaient... Bien joué, capitaine, les chiens anglais sont éliminés. Les saboteurs ont été éliminés, le commandant et le gouverneur seront satisfaits.";
			link.l1 = "Vous avez pris votre temps, monseigneur...";
			link.l1.go = "hol_officer_6";
		break;
		
		case "hol_officer_6":
			dialog.text = "Blamez la corde, elle avait un seau au bout qui faisait un vacarme absolu. Nous devions être prudents.";
			link.l1 = "Ouais...la corde. Peu importe. Une de vos patrouilles disparues est attachée là-bas dans les buissons. Ils devraient encore être vivants.";
			link.l1.go = "hol_officer_7";
		break;
		
		case "hol_officer_7":
			dialog.text = "Je m'en occupe. Vous devriez aller en ville et vous reposer un peu. Rendez visite à notre gouverneur demain, il aura mon rapport avec des éloges flamboyants à votre sujet d'ici là.";
			link.l1 = "Je ferai cela. Bon vent mynheer.";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattleRest");
		break;
		
		case "monk":
			DelLandQuestMark(npchar);
			DelLandQuestMarkToPhantom();
			if (GetCharacterIndex("marigojailoff") != -1)
			{
				DelLandQuestMark(characterFromId("marigojailoff"));
			}
			pchar.questTemp.FMQN = "way_eng_2";
			dialog.text = "Que puis-je faire pour vous, mon fils ?";
			link.l1 = "Bonjour pasteur, par pure curiosité, il y a combien de temps que les marins captifs se sont confessés ?";
			link.l1.go = "monk_1";
		break;
		
		case "monk_1":
			dialog.text = "Hier soir, mon fils... (chuchotant) Je suppose que vous savez que le plan est trahi ?";
			link.l1 = "Je ne serais pas là sinon. Le lieutenant Casper Gratton et ses hommes sont actuellement dans la jungle. Ils sont tous habillés comme des soldats néerlandais, mais nous avons besoin d'une aide supplémentaire car les gardes de la prison les attendent.";
			link.l1.go = "monk_2";
		break;
		
		case "monk_2":
			dialog.text = "(à haute voix) J'ai prié chaque jour pour sauver son âme anglicane de la damnation ! (en chuchotant) J'ai un plan, mais j'ai besoin de deux douzaines de doublons d'or pour obtenir tout ce dont j'ai besoin.";
			link.l1 = "Plan coûteux. A quoi sert l'argent ?";
			link.l1.go = "monk_3";
		break;
		
		case "monk_3":
			dialog.text = "Être gardien de prison est une tâche ennuyeuse. Pour maintenir le moral, l'officier responsable commande du vin chaque soir pour accompagner leur dîner. Le vin est apporté d'un entrepôt auquel j'ai accès. Il y a une gitane en ville qui me doit une faveur, elle nous préparera une potion de sommeil. Tout ce dont j'ai besoin, c'est d'acheter quelques bouteilles de bon vin, d'ajouter la potion et de remplacer les bouteilles dans l'entrepôt. C'est pourquoi j'ai besoin de l'or.";
			if (PCharDublonsTotal() >= 24)
			{
				link.l1 = "J'ai les doublons. Prends-les.";
				link.l1.go = "monk_4";
			}
			else
			{
				link.l1 = "Laisse-moi retourner à mon navire et t'en apporter.";
				link.l1.go = "monk_wait";
			}
		break;
		
		case "monk_wait":
			DialogExit();
			npchar.dialog.currentnode = "monk_repeat";
		break;
		
		case "monk_repeat":
			dialog.text = "Ah mon fils, as-tu la 'donation' dont nous avons discuté ?";
			if (PCharDublonsTotal() >= 24)
			{
				link.l1 = "Oui, ici.";
				link.l1.go = "monk_4";
			}
			else
			{
				link.l1 = "Je l'obtiendrai bientôt...";
				link.l1.go = "monk_wait";
			}
		break;
		
		case "monk_4":
			RemoveDublonsFromPCharTotal(24);
			dialog.text = "Splendide. Viens me voir à la même heure demain - je te dirai les résultats.";
			link.l1 = "Très bien...";
			link.l1.go = "monk_5";
		break;
		
		case "monk_5":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("FMQ_Nevis", "18");
			pchar.quest.FMQN_monk.win_condition.l1 = "Timer";
			pchar.quest.FMQN_monk.win_condition.l1.date.hour  = 6.0;
			pchar.quest.FMQN_monk.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQN_monk.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQN_monk.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQN_monk.function = "FMQN_EnglandMonkPlan";
			pchar.quest.FMQN_fail.win_condition.l1 = "Timer";
			pchar.quest.FMQN_fail.win_condition.l1.date.hour  = 11.0;
			pchar.quest.FMQN_fail.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQN_fail.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQN_fail.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQN_fail.function = "FMQN_EnglandFail";
			pchar.questTemp.FMQN = "way_eng_3";
		break;
		
		case "monk_6":
			DelLandQuestMark(npchar);
			pchar.quest.FMQN_fail.over = "yes";
			dialog.text = "Salutations, mon fils.";
			link.l1 = "À vous aussi, pasteur. Des nouvelles?";
			link.l1.go = "monk_6x";
		break;
		
		case "monk_6x":
			dialog.text = "Oui. C'est fait. Le vin a été 'aromatisé' et les gardes auront droit à un traitement spécial ce soir. Ils dînent à neuf heures du soir, ils dormiront tous avant minuit. C'est votre seule occasion de faire le travail, pas de seconde chance. Soyez prudent, vous ne pouvez pas vous fier entièrement à votre déguisement hollandais.";
			link.l1 = "Compris. Ne perdons pas de temps. Adieu.";
			link.l1.go = "monk_7";
		break;
		
		case "monk_7":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("FMQ_Nevis", "20");
			sld = CharacterFromID("FMQN_seafox_1");
			sld.dialog.currentnode = "seafox_26";
			LAi_CharacterEnableDialog(sld);
			sld.talker = 9;
			AddLandQuestMark(sld, "questmarkmain");
			pchar.quest.FMQN_fail1.win_condition.l1 = "Timer";
			pchar.quest.FMQN_fail1.win_condition.l1.date.hour  = 20.0;
			pchar.quest.FMQN_fail1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.FMQN_fail1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.FMQN_fail1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.FMQN_fail1.function = "FMQN_EnglandFail";
			pchar.questTemp.FMQN = "way_eng_4";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
