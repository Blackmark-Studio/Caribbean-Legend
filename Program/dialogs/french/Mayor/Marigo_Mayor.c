// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Que voulez-vous ? Demandez donc.","Je vous écoute, quelle est la question ?"),"C'est la deuxième fois que vous essayez de demander...","C'est la troisième fois que vous essayez de demander...","Quand cela va-t-il finir?! Je suis un homme occupé, travaillant sur les affaires de la colonie et vous continuez à me déranger!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("J'ai changé d'avis...","Pas maintenant. Mauvais endroit et mauvais moment."),"Vrai... Mais plus tard, pas maintenant...","Je demanderai... Mais un peu plus tard...","Je suis désolé, "+GetAddress_FormToNPC(NPChar)+"... ",npchar,Dialog.CurrentNode);			  
			link.l1.go = "exit";
			//Jason, Португалец
			if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "ToGovernor")
			{
				link.l1 = "Votre Grâce, j'ai des nouvelles absolument excellentes et urgentes pour vous ! J'ai capturé Bartolomeo le Portugais, le bâtard est sous garde et attend un procès équitable ! Et je cherche une modeste reconnaissance de la Compagnie...";
				link.l1.go = "Portugal";
			}
			//Португалец
			
			// Addon-2016 Jason ФМК-Сент-Кристофер
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "governor")
			{
				link.l1 = "Vous avez insisté pour me voir, Monsieur le gouverneur...";
				link.l1.go = "FMQN";
			}
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "hol_battle_complete")
			{
				link.l1 = "Je suis ici pour parler des espions anglais, monsieur le gouverneur...";
				link.l1.go = "FMQN_7";
			}
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("Vous avez déjà tout pris. Que voulez-vous de plus ?","Y a-t-il quelque chose que vous n'avez pas encore raflé ?");
            link.l1 = RandPhraseSimple("Je regarde simplement autour de moi...","Je vérifie juste, je pourrais oublier de prendre quelque chose...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		//Jason, Португалец
		case "Portugal":
			dialog.text = "Bartolomeo... Bart le Portugais est dans ma ville ?! Vivant ?!!";
			link.l1 = "Il l'est, votre Grâce, et il est sous une garde fiable. Je vous le remettrai après avoir reçu une lettre de change pour la tête de Bart, promise par la Compagnie. Des doublons d'or feraient aussi l'affaire...";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "Bill, des doublons ? Es-tu fou ?! A quoi pensais-tu en amenant ce monstre dans ma ville ?! S'il est ici, alors sa frégate n'est pas loin de l'île et son équipage peut être en ville à l'instant même !";
			link.l1 = "J'ai tué ceux qui étaient avec lui, je ne sais pas pour les autres, mais cela n'a pas vraiment d'importance je suppose parce que Bartolomeo est...";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			dialog.text = "Ça oui ! Ne comprends-tu vraiment pas ce que tu as fait ?! Le 'Albatross' est près de l'île et tu as capturé le pirate dont la brutalité effraie même ses propres gens assoiffés de sang ! Éloigne-toi d'ici ! Quitte l'île ! Et emmène ce monstre avec toi !";
			link.l1 = "Mais écoute, et la récompense promise et...";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			dialog.text = "Je ne veux pas voir ma ville brûler à cause de votre cupidité et de la vengeance de la Compagnie ! Il n'y a que des recrues fraîches dans mon fort et la moitié d'entre elles s'enfuiront dès qu'elles apprendront qui attaque leurs redoutes et pourquoi ! Et puis le massacre commencera... Je ne vais pas prendre ce risque, vous m'entendez ?! Dégagez et livrez-le vous-même à Curacao si la Compagnie veut sa tête à ce point !\nFaites-le immédiatement avant qu'il ne soit trop tard ! Et vous pouvez faire de lui ce que vous voulez, même le jeter par-dessus bord, mais ne le faites pas dans ma ville !\nHans ! Hans, où es-tu, espèce d'idiot paresseux ! Apporte-moi une potion de valériane ou quelque chose, et que quelqu'un, pour l'amour de Dieu, jette cet aventurier hors de ma résidence !";
			link.l1 = "Mais votre Grâce...";
			link.l1.go = "Portugal_4";
		break;
		
		case "Portugal_4":
			DialogExit();
			DoQuestReloadToLocation("Marigo_town", "reload", "reload3_back", "PortugalOutResidence");
		break;
		
		// Addon-2016 Jason ФМК-Сент-Кристофер
		case "FMQN":
			DelLandQuestMark(npchar);
			dialog.text = "Très bien ! Dites-moi capitaine, avez-vous rencontré des navires militaires ou marchands anglais en approchant de notre île ?";
			link.l1 = "Non, Monsieur. Je n'ai vu ni navires militaires, ni navires marchands sous pavillon anglais dans vos eaux.";
			link.l1.go = "FMQN_1";
		break;
		
		case "FMQN_1":
			dialog.text = "Je vois. Combien de temps comptez-vous rester ici ?";
			link.l1 = "Trois jours environ...";
			link.l1.go = "FMQN_2";
		break;
		
		case "FMQN_2":
			dialog.text = "Dans ce cas, j'ai une offre pour vous. Selon nos renseignements, il y a un risque d'espions anglais ici. Je donnerai dix mille pesos en récompense pour toute information concernant des navires ou des personnes suspectes sur l'île, dans la ville, à proximité, sur les rives, etc. La récompense sera considérablement augmentée en cas d'assistance aux autorités dans la détention ou l'élimination d'un ennemi.\nChaque capitaine civil est invité à participer à l'enquête et à sillonner les côtes locales et la jungle à la recherche des espions.\nIl est possible que vous rencontriez notre corvette militaire, le Zeepard, ne soyez pas effrayé, elle est en patrouille. Vous êtes libre de vous adresser à son capitaine si vous trouvez les Britanniques.";
			link.l1 = "Hélas, votre Excellence, mais je suis ici uniquement avec des intentions de commerce pacifique. Je devrai quitter cette île dès que je me serai réapprovisionné et que j'aurai terminé mes affaires ici.";
			link.l1.go = "FMQN_3";
			link.l2 = "Une offre tentante ! Je pense que je vais participer et piller les eaux et les côtes de votre île. Je pourrais même rester ici un moment.";
			link.l2.go = "FMQN_5";
		break;
		
		case "FMQN_3":
			dialog.text = "C'est juste une information gratuite, capitaine. Pas de pression. Vous savez à qui vous adresser en cas de quelque chose de suspect.";
			link.l1 = "Très bien, Monsieur, j'ai compris. Adieu !";
			link.l1.go = "FMQN_4";
		break;
		
		case "FMQN_4":
			DialogExit();
			pchar.questTemp.FMQN = "way_eng_1";
			AddQuestRecord("FMQ_Nevis", "8");
			chrDisableReloadToLocation = false;
			FMQN_SetSoldiersInCave();
		break;
		
		case "FMQN_5":
			dialog.text = "Splendide, capitaine ! Puisque vous êtes si sérieux, assurez-vous de parler aussi à notre commandant. Il est chargé de capturer les espions et pourrait vous fournir des informations supplémentaires.";
			link.l1 = "Bien, Monsieur. J'irai le voir.";
			link.l1.go = "FMQN_6";
		break;
		
		case "FMQN_6":
			DialogExit();
			pchar.questTemp.FMQN = "way_div";
			AddQuestRecord("FMQ_Nevis", "9");
			chrDisableReloadToLocation = false;
			AddLandQuestMarkToPhantom("marigo_prison", "marigoJailOff");
		break;
		
		case "FMQN_7":
			DelLandQuestMark(npchar);
			dialog.text = "Nous vous attendions, Monsieur "+GetFullName(pchar)+" . Permettez-moi d'exprimer notre gratitude pour vos actions en éliminant le dangereux groupe de raid anglais. Acceptez ces dix mille pesos. De plus : 200 soies de navire seront chargées dans la cale de votre navire et une récompense très spéciale - une licence de trois ans de la Compagnie néerlandaise des Indes occidentales. C'est un document extrêmement précieux, j'espère que vous le savez ?";
			link.l1 = "Bien sûr ! Une licence de trois ans - c'est certain, c'est énorme.";
			link.l1.go = "FMQN_8";
		break;
		
		case "FMQN_8":
			dialog.text = "Veuillez, prendre votre récompense. De plus, vous pouvez compter sur la gratitude de tous les citoyens et autorités néerlandais. Vous êtes une sensation à Philipsburg, nous serions ravis de vous revoir.";
			link.l1 = "Entendre des paroles si chaleureuses est plus précieux que la licence. Merci, ce fut un plaisir. Et maintenant, je dois prendre la mer. Adieu!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_HollandBattleComplete");
		break;
		
		// Jason НСО
		case "tomas":
			dialog.text = "Nous nous rendons ! Au nom de tout ce qui est sacré, je vous en prie, n'attaquez pas et ne pillez pas Philipsburg et ses habitants ! Je suis prêt à écouter vos exigences !";
			link.l1 = "Ne vous inquiétez pas pour les citoyens, Monsieur. Les sujets de la Couronne française ne devraient pas craindre les soldats français.";
			link.l1.go = "tomas_1";
		break;
		
		case "tomas_1":
			dialog.text = "La Couronne française ?";
			link.l1 = "Exactement. Cette île appartient à la France, et vous n'êtes ici que des locataires. Des locataires impudents, qui ont cru que cette île pouvait être leur propriété. À partir d'aujourd'hui, l'autorité néerlandaise à Saint-Martin a pris fin. Est-ce clair ?";
			link.l1.go = "tomas_2";
		break;
		
		case "tomas_2":
			dialog.text = "Mais... Mais que va-t-il nous arriver, avec les soldats hollandais qui se sont rendus à vous, et les blessés? Et quoi...";
			link.l1 = " Cela ne dépendra que de vous, Mynheer Thomas. Si vous me rendez un service, alors je permettrai à tous ceux qui se sont rendus de prendre leurs blessés et de partir d'ici sur un ou plusieurs navires que nous trouverons dans les docks, vers Curaçao, chez Mynheer Stuyvesant.";
			link.l1.go = "tomas_2_1";
		break;
		
		case "tomas_2_1":
			dialog.text = "";
			link.l1 = "Sinon, vous serez gardé dans les cales de mes navires et les casemates de Saint-Christophe. De plus, certains fonctionnaires hollandais importants devront être pendus, juste pour s'assurer que Stuyvesant perdra son intérêt pour conquérir nos colonies...";
			link.l1.go = "tomas_3";
		break;
		
		case "tomas_3":
			dialog.text = "(b-bégayant) Quoi... Quoi... à propos de qu...el genre de f-fa... veur?";
			link.l1 = "Dans les profondeurs de l'île se trouve un os de discorde - une mine de sel. Je sais qu'il n'y a pas seulement des mineurs et des esclaves, mais aussi des soldats hollandais, armés jusqu'aux dents. Ils doivent appartenir à la Garde de la Compagnie, n'est-ce pas, Monsieur? Je leur proposerai de se rendre, ou j'utiliserai la force en cas de refus. J'ai besoin d'un guide qui me montrera le chemin vers la mine. Trouvez-moi un tel guide.";
			link.l1.go = "tomas_4";
		break;
		
		case "tomas_4":
			dialog.text = "U-une mine de s-sel ?";
			link.l1 = "Exactement. N'aie pas peur, Mynheer Thomas, si les gardes de la mine sont assez sages pour déposer les armes, je leur donnerai l'occasion de quitter l'île. Je n'ai pas besoin de verser inutilement du sang. Ne t'inquiète pas, ta conscience sera tranquille : même si tu ne me dis pas où se trouve la mine, l'île de Saint Maarten est assez petite pour que je puisse la trouver sans ton aide, je ne veux simplement pas perdre mon temps à errer dans les fourrés et les marais. Donc, cet accord est plus profitable pour toi que pour moi.";
			link.l1.go = "tomas_5";
		break;
		
		case "tomas_5":
			dialog.text = "Bi-bien, je vais vous dire comment atteindre la mine, m-mais vous devez me p-promettre que t-tous... tous, nous quitterons cette île !";
			link.l1 = "Je vous donne ma parole d'officier et de gentilhomme.";
			link.l1.go = "tomas_6";
		break;
		
		case "tomas_6":
			dialog.text = "Dans la baie de Grand Case... à son extrémité, près de l'eau, il y a ... il y a des pierres. Là ... là, derrière elles, le long de la côte, il y a un passage le long de l'eau, là ... c'est peu profond là-bas, jusqu'à la taille ou moins. Vous devez contourner le rocher et vous arriverez à une grande plage, où ... où vous ne pouvez pas accoster votre navire à cause des récifs autour. De cette plage, il y a un chemin directement ... vers ... vers la mine.";
			link.l1 = "Excellent. Je mets les voiles. Et vous, Monsieur, resterez ici sous la surveillance attentive de mes soldats jusqu'à mon retour.";
			link.l1.go = "tomas_7";
		break;
		
		case "tomas_7":
			DialogExit();
			SetReturn_Gover_Dialog_Exit(NPChar);
			LAi_SetActorType(npchar);
			pchar.quest.Patria_BastionGate.win_condition.l1 = "location";
			pchar.quest.Patria_BastionGate.win_condition.l1.location = "Shore40";
			pchar.quest.Patria_BastionGate.function = "Patria_BastionShore";
			AfterTownBattle();
			AddQuestRecord("Patria", "50_1");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
