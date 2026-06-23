// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Allez-y, que voulez-vous ?","Nous en parlions justement. Vous devez avoir oublié...","C'est la troisième fois aujourd'hui que tu parles d'une certaine question...","Ecoutez, c'est une boutique. Les gens achètent des choses ici. Ne me dérangez pas !","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Tu sais, "+NPChar.name+", peut-être la prochaine fois.","Ah, j'ai oublié pour une raison quelconque...","Oui, c'est vraiment la troisième fois...","Hm, je ne vais pas...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			/* //--> Бремя гасконца
			if (!CheckAttribute(npchar, "quest.storehelper") && pchar.questTemp.Sharlie == "ship")
			{
				Link.l1 = "Écoutez, monsieur, je cherche un emploi. Pas un travail à plein temps ou à porter des sacs de cargaison, mais plutôt à faire des commissions, pour ainsi dire. Auriez-vous besoin d'assistance ?";
				Link.l1.go = "Sharlie_storehelper";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "return")
			{
				Link.l1 = "J'ai accompli ta corvée. J'ai trouvé Gralam Lavoie.";
				Link.l1.go = "Sharlie_storehelper_2";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "choise")
			{
				Link.l1 = "Rencontrez votre nouvel assistant, monsieur.";
				Link.l1.go = "Sharlie_storehelper_11";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "final")
			{
				Link.l1 = "C'est encore moi, monsieur. Je suis venu pour ma récompense.";
				Link.l1.go = "Sharlie_storehelper_13";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
			{
				link.l1 = "Jetez un oeil à ces boucles d'oreilles, monsieur. Je les ai trouvées sur le corps d'un bandit qui a été tué dans la jungle. C'est clairement l'œuvre d'un bon joaillier qui, j'en suis sûr, n'est pas d'ici. Pouvez-vous me dire quelque chose à propos de ces boucles d'oreilles ?";
                link.l1.go = "Sharlie_junglejew";
			}
			//<-- Бремя гасконца */
		break;
		
		//--> Бремя гасконца
		case "Sharlie_storehelper":
			if (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) == "") 
			{
				dialog.text = "Excusez-moi, monsieur, mais où est votre épée ? Il n'est pas sûr de quitter la ville sans une arme blanche. On ne sait jamais ce qui peut arriver dans la jungle !";
				link.l1 = "Diable, j'ai complètement oublié ! Tout a été emporté !";
				link.l1.go = "Store_noweapon";
				break;
			}
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("Fortfrance_town", "reload", "reload6_back");
			dialog.text = "Un travail ? Hum. Je suppose que j'ai un boulot qui pourrait t'intéresser. Mon assistant a disparu, il travaillait dans mon entrepôt. Il est déjà absent depuis une semaine et ça m'agace diablement, parce que je suis forcé de faire son travail et je n'ai pas le temps.\nS'il te plaît, trouve cet idiot et découvre pourquoi diable il a abandonné son poste. Ou mieux encore - ramène-le-moi. Je te paierai mille pièces de huit.";
			link.l1 = "D'accord, je suis partant. Dis-moi son nom et décris-moi son apparence. As-tu des idées sur où le chercher ?";
			link.l1.go = "Sharlie_storehelper_1";
			link.l2 = "Rechercher un homme Dieu sait où pour un misérable millier ? Tu plaisantes, j'espère !";
			link.l2.go = "Sharlie_storehelper_exit";
			npchar.quest.storehelper = "true";
		break;
		
		case "Sharlie_storehelper_exit":
			AddTimeToCurrent(2,0);
			LocatorReloadEnterDisable("Fortfrance_town", "reload10_back", false);// пу откр
			dialog.text = "Hey, monsieur. Qui cherche un emploi, vous ou moi ? Si vous ne voulez pas, je ne vous force pas. Bonne journée.";
			link.l1 = "Hm... Think I'll go check the port authority; perhaps they'll offer something more substantial there.";
			link.l1.go = "exit";
		break;
		
		case "Sharlie_storehelper_1":
			dialog.text = "Mon nom est Gralam Lavois. Son apparence ? Trente-cinq ans, barbe et moustache, long manteau brun, chemise blanche. Oh, et il porte toujours ce chapeau ridicule en forme de tricorne, prétend être un amiral avec une ancre dans le derrière. \nIl n'est pas à St. Pierre, j'ai vérifié toute la ville. Il doit être dans la jungle ou à Les Francois, se cachant avec les pirates qui rôdent là-bas.\nD'un autre côté, il est probablement dans le repaire de pirates de Le Francois, qui se trouve dans la partie est de notre île. Peut-être qu'il discute avec les pirates là-bas, ou passe du temps à l'auberge, ou se dispute avec le marchand local à la boutique.\nComment se rendre à Le Francois ? Sortez par les portes de la ville dans la jungle, à la croisée des chemins, prenez le chemin de gauche, puis suivez la route jusqu'à ce que vous tourniez à droite, et ensuite prenez le passage à gauche entre les rochers, et vous trouverez Le Francois. Je ne pense pas que vous vous perdiez.";
			link.l1 = "Très bien. Je vais commencer mes recherches. Dès que j'ai quelque chose, je vous en informe immédiatement.";
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
			dialog.text = "Ah oui? Et où est-il?";
			link.l1 = "Je l'ai trouvé à Le Francois. Il ne travaillera plus pour vous. Il a aussi ajouté beaucoup de choses plutôt salées à votre sujet... Seriez-vous intéressé à les entendre ?";
			link.l1.go = "Sharlie_storehelper_3";
		break;
		
		case "Sharlie_storehelper_3":
			dialog.text = "Non. Epargne-moi les détails... Quel dommage ! Que vais-je faire maintenant sans assistant ?";
			link.l1 = "Loue quelqu'un d'autre. Ou est-ce vraiment aussi grave que Gralam l'a dit ?";
			link.l1.go = "Sharlie_storehelper_4";
		break;
		
		case "Sharlie_storehelper_4":
			dialog.text = "Une sacrée poisse, en effet. Et qu'a dit ce bon à rien?";
			link.l1 = "Eh bien, pour commencer, il ne perd évidemment pas son temps, hé hé. Il a dit que personne à Saint Pierre ne voudrait s'engager à votre service parce que... vous ne payez pas assez vos travailleurs. Oui, d'ailleurs, "+npchar.name+", vous devez mille pesos comme promis.";
			link.l1.go = "Sharlie_storehelper_5";
		break;
		
		case "Sharlie_storehelper_5":
			AddMoneyToCharacter(pchar, 1000);
			dialog.text = "Je vous en prie, prenez votre argent. Ha ! On ne paie pas assez ! Bien sûr, personne ne veut travailler pour moi. Le salaud a fait de son mieux pour répandre des ragots immondes. Que puis-je faire ? Je ne peux pas tout faire seul !\nJe ne peux pas aller dormir tant que je n'ai pas compté chaque pièce de cargaison parce que ces maudits travailleurs en volent toujours. Après le dernier chargement, il me manque cinq barils de rhum. Je suis sûr que les travailleurs les ont 'pris par erreur'...";
			link.l1 = "Eh bien, je ne sais pas quoi conseiller. D'accord, tout le meilleur. Il est temps pour moi de partir.";
			link.l1.go = "Sharlie_storehelper_6";
		break;
		
		case "Sharlie_storehelper_6":
			dialog.text = "Attends ! Je pense que tu peux m'aider. Si tu as pu retrouver ce salaud, alors tu pourrais bien être capable de...";
			link.l1 = "Et que pourrais-je bien faire, je me demande, si personne dans cette ville ne te croit ? Je suis nouveau ici et...";
			link.l1.go = "Sharlie_storehelper_7";
		break;
		
		case "Sharlie_storehelper_7":
			dialog.text = "Laissez-moi finir, monsieur. Vous êtes déjà allé à Le Francois. J'aimerais que vous y retourniez pour essayer de trouver un employé pour moi. Peut-être que Gralam n'a pas complètement ruiné ma réputation dans cette tanière de pirates.\nLe travail est simple - compter le fret et surveiller les travailleurs du port pour prévenir le vol. Parfois, faire mon travail ici à ma place pendant mon absence, moyennant un supplément bien sûr.\nDites-leur que j'offre une chambre dans le magasin pour vivre et cinq cents pièces de huit par semaine. Monsieur, j'avais l'intention d'étendre mon commerce et les choses vont enfin bien, j'ai besoin d'un assistant !\nAu fait, il vaut mieux chercher de l'aide pour trouver un travailleur auprès de l'aubergiste local, Cesare Craig. Ce vaurien vous aidera sûrement, bien que pas gratuitement, à trouver des individus intéressés à travailler pour moi.";
			link.l1 = "Hm. Je peux essayer, bien que je ne sois pas sûr... Combien me paierez-vous pour ce travail ?";
			link.l1.go = "Sharlie_storehelper_8";
		break;
		
		case "Sharlie_storehelper_8":
			dialog.text = "Cela dépendra du travailleur que tu pourras engager. Plus il s'avérera compétent, plus je te paierai pour tes efforts. C'est équitable, n'est-ce pas ?";
			link.l1 = "Ne penses-tu pas que tu me forces à avancer à l'aveuglette ? Comment puis-je savoir comment tu vas évaluer un travailleur ? Tu pourrais qualifier n'importe qui de mauvais ou...";
			link.l1.go = "Sharlie_storehelper_9";
		break;
		
		case "Sharlie_storehelper_9":
			dialog.text = "Monsieur ! Il se peut que l'on me traite de radin, mais personne ne pourrait me qualifier de malhonnête ! Si je vous dis que je paierai pour vos efforts en fonction du résultat, alors je le pense vraiment. Voyez cela de mon point de vue également. Vous pourriez bien m'amener ici quelque gitan paresseux qui non seulement traînerait sans rien faire, mais pourrait même me voler pendant la nuit !";
			link.l1 = "D'accord. J'accepte. Je te crois sur parole, "+npchar.name+". Je veillerai à ne pas ramener de gitans.";
			link.l1.go = "Sharlie_storehelper_10";
		break;
		
		case "Sharlie_storehelper_10":
			DialogExit();
			SetLaunchFrameFormParam("Back to Le Francois...", "Reload_To_Location", 0, 3.0);
			SetLaunchFrameReloadLocationParam("LeFransua_tavern", "reload", "reload1", "SharlieA_TeleportLF");
			LaunchFrameForm();
		break;
		
		case "Sharlie_storehelper_11":
			dialog.text = "As-tu trouvé un ouvrier pour moi ? Merveilleux. Permets-moi de lui parler, reviens dans une heure pour ta récompense.";
			link.l1 = "Très bien. Je reviendrai dans une heure.";
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
			switch (int(pchar.questTemp.Sharlie.Storehelper.Quality))
			{
				case 0:
					AddMoneyToCharacter(pchar, 3000);
					dialog.text = "Je suis assez satisfait de l'ouvrier que vous m'avez trouvé, bien qu'il parle plus qu'il n'agit, mais ne vous inquiétez pas, je lui ferai perdre son bavardage avec le temps. Votre récompense est de trois mille pièces de huit. Tenez, les voici.";
					link.l1 = "Merci ! Dites-moi, Monsieur, savez-vous si quelqu'un d'autre en ville pourrait avoir besoin d'aide pour une affaire importante ?";
					link.l1.go = "Sharlie_storehelper_14a";
				break;
				
				case 1:
					AddMoneyToCharacter(pchar, 5000);
					dialog.text = "Vous avez réussi à trouver un travailleur vraiment précieux ! Il est même meilleur que ce vaurien de Gralam. Je suis très, très satisfait, monsieur. Tenez, prenez votre récompense - cinq mille pièces de huit.";
					link.l1 = "Merci ! Dites-moi, Monsieur, savez-vous si quelqu'un d'autre en ville pourrait avoir besoin d'aide pour une affaire importante ?";
					link.l1.go = "Sharlie_storehelper_14a";
				break;
				
				case 2:
					AddMoneyToCharacter(pchar, 4000);
					dialog.text = "Vous avez trouvé un bon ouvrier. Et bien qu'il ne connaisse pas encore toutes les ficelles du métier, je suis sûr qu'il s'en sortira sans trop de peine. Je suis satisfait de vous, monsieur. Tenez, prenez votre récompense - quatre mille pièces de huit.";
					link.l1 = "Merci ! Dites-moi, Monsieur, savez-vous si quelqu'un d'autre en ville aurait besoin d'aide pour une affaire importante ?";
					link.l1.go = "Sharlie_storehelper_14a";
				break;
			}
		break;
		
		case "Sharlie_storehelper_14a":
			LocatorReloadEnterDisable("Fortfrance_town", "reload10_back", false);// пу откр
			dialog.text = "Hmm... Récemment, j'ai vu le maître de port, visiblement contrarié, se diriger vers l'autorité portuaire. Va le voir, qui sait ce qui a pu se passer.";
			link.l1 = "Je ferai exactement cela. Merci, Monsieur.";
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
			dialog.text = "Eh bien, que suis-je censé dire, des boucles d'oreilles magnifiques. Je peux vous donner... voyons voir... quatre mille pièces de huit pour elles. Je doute que quelqu'un vous offre plus. Avons-nous un accord ?";
			link.l1 = "Marché conclu ! Ils sont à vous.";
			link.l1.go = "Sharlie_junglejew_1";
			link.l2 = "Non. Je pense que je vais garder ces bijoux pour moi.";
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
			dialog.text = "Cela ne suffira pas. Je vous suggère d'approcher notre gouverneur et de demander son assistance.";
			link.l1 = "Merci pour le conseil. C'est ce que je compte faire.";
			link.l1.go = "exit";
		break;
		//<-- Бремя гасконца
	}
	UnloadSegment(NPChar.FileDialog2);
}
