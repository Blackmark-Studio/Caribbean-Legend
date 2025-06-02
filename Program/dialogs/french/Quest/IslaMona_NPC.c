void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "Que veux-tu?";
			link.l1 = "Rien.";
			link.l1.go = "exit";
		break;
		
		// Родриго Хименес
		case "Himenes_exit":
			dialog.text = "Autre chose, Capitaine ?";
			link.l1 = "Rien pour l'instant...";
			link.l1.go = "Himenes_exit_1";
		break;
		
		case "Himenes_exit_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_exit";
		break;
		
		case "Himenes":
			dialog.text = "Ha-ha-ha ! Seigneur Jesus-Christ ! Gloire à Saint-Jacques le Protecteur ! Gloire à la Vierge Marie ! Nous sommes sauvés ! Ha-ha-ha !";
			link.l1 = "Espagnols ! Aux armes !";
			link.l1.go = "Himenes_1_1";
			link.l2 = "Bonjour. Je comprends que vous avez des problemes ? Qui etes-vous ?";
			link.l2.go = "Himenes_2";
		break;
		
		case "Himenes_1_1":
			AddComplexSelfExpToScill(100, 100, 100, 100);
			dialog.text = "Ah-ah-ah-ah-ah-ah-ah-ah !";
			link.l1 = "Très bien, d'accord, calme-toi. C'est juste une habitude.";
			link.l1.go = "Himenes_2";
		break;
		
		case "Himenes_2":
			dialog.text = "Ha-ha ! Senor, je me nomme Rodrigo Jimenez. Je suis arpenteur et, par la volonté du destin, el jefe de ces pauvres gens.";
			link.l1.go = "Himenes_3";
		break;
		
		case "Himenes_3":
			dialog.text = "Nous... avons été débarqués ici. Mais, señor, nous ne sommes pas des criminels ! Ha-ha-ha-ha !";
			link.l1 = "Qu'est-ce qui est drôle ?";
			link.l1.go = "Himenes_4";
		break;
		
		case "Himenes_4":
			dialog.text = "Ah... Je m'excuse, señor ! C'est toute mon affliction, depuis l'enfance je ris quand je suis très nerveux. Ha.";
			link.l1 = "Et vous avez été choisi comme chef?.. Très bien. Les gens n'atterrissent pas sur des îles inhabitées sans raison, señor. Voulez-vous expliquer? Je ne vous donne qu'une seule chance.";
			link.l1.go = "Himenes_5";
		break;
		
		case "Himenes_5":
			string nationManName[4];
			nationManName[0] = "English";
			nationManName[1] = "French";
			nationManName[2] = "If you are seeing this, it's a bug";
			nationManName[3] = "Spaniard";
			dialog.text = "Désolé, j'ai peur de ne pas avoir saisi votre nom, monsieur. Êtes-vous anglais ?";
			link.l1 = nationManName[sti(pchar.BaseNation)]+". Est-ce si important ? Ne nous inquiétons pas de mon nom pour l'instant.";
			link.l1.go = "Himenes_6";
		break;
		
		case "Himenes_6":
			dialog.text = "En effet, étant reconnus comme hérétiques par l'Église catholique espagnole, nous devons comparaître devant le tribunal juste de la Sainte Inquisition. C'est pourquoi votre nationalité est si importante pour nous. Un capitaine espagnol serait obligé de nous livrer aux autorités locales. Nous ne survivrions pas à une telle chose encore une fois ! Ha-ha !";
			if (sti(pchar.BaseNation) == SPAIN) dialog.text = "Ha-ha-ha-ha-ha-ha ! Telle est notre chance, eh bien, nous n'avons rien à perdre de toute façon. "+dialog.text;
			link.l1 = "Eh bien, heureusement pour vous, les affaires de l'Inquisition ne me concernent pas. Alors quoi ? Vous êtes des païens ?";
			link.l1.go = "Himenes_7";
		break;
		
		case "Himenes_7":
			dialog.text = "Non, je te le jure ! Notre communauté s'occupait d'artisanat et de commerce dans la glorieuse ville de Cadix depuis cinquante ans. Tout se passait bien, nous avons même acquis un navire et une licence pour commercer avec les colonies de notre Empire. Maintenant je comprends qu'à l'époque nous avons franchi une certaine limite et étions complètement impréparés face à nos nouveaux concurrents... et leurs méthodes.";
			link.l1 = "Tu n'as pas partagé le commerce avec quelqu'un en Europe et, par conséquent, toute la communauté s'est retrouvée coincée sur une île déserte dans les Caraïbes ? Et moi qui pensais avoir des problèmes de vie...";
			link.l1.go = "Himenes_8";
		break;
		
		case "Himenes_8":
			dialog.text = "Malheureusement, c’est le cas. Notre communauté a été fondée par des Juifs qui se sont convertis à la nouvelle foi et ont eu l’occasion de rentrer chez eux en Espagne. Cette ancienne histoire a suffi pour des accusations et un examen officiel.";
			link.l1 = "Et donc tu as couru...";
			link.l1.go = "Himenes_9";
		break;
		
		case "Himenes_9":
			dialog.text = "Oui ! Ha-ha-ha ! Sur notre propre navire ! Nous nous dirigions vers Curacao pour y construire une nouvelle maison et un nouveau commerce. Cependant, nous avons sous-estimé l'obstination de l'Inquisition et nous l'avons payé cher. Leur courrier nous a interceptés non loin d'ici et a ordonné au capitaine de nous ramener chez nous...";
			link.l1 = "Merde !";
			link.l1.go = "Himenes_10";
		break;
		
		case "Himenes_10":
			dialog.text = "Il y a plus ! Ha ! Notre capitaine ne voulait pas s'embêter à nous ramener de l'autre côté de l'Atlantique ni à nous libérer sous sa responsabilité au port le plus proche. Et, prenant une décision vraiment digne de Salomon, il nous a donné de la nourriture, nous a débarqués ici, et voilà.";
			link.l1 = "Une histoire tragique en effet, pas de doute là-dessus. Résumons : tu ne peux pas rentrer chez toi, les colonies amies te dénonceront, et les ports étrangers ne t'accueilleront pas non plus - la guerre n'a pas de fin dans cette région. Quels sont tes plans ?";
			link.l1.go = "Himenes_11";
		break;
		
		case "Himenes_11":
			dialog.text = "Vous avez peint un tableau si sombre, monsieur, que je suis à court de mots. C'est comme s'il n'y avait pas de meilleur endroit pour nous que cette île.";
			link.l1 = "Je ne crois pas, il y a une meilleure île.";
			link.l1.go = "Himenes_12";
		break;
		
		case "Himenes_12":
			dialog.text = "Vraiment? Est-ce espagnol?";
			link.l1 = "C'est à moi. Par le destin, j'ai hérité d'une ancienne cachette de pirates sur une île inhabitée. Maintenant, c'est ma base, et je veux l'agrandir, explorer l'île, et si possible, y construire une usine.";
			link.l1.go = "Himenes_13";
		break;
		
		case "Himenes_13":
			dialog.text = "Es-tu un pirate ?";
			link.l1 = "Oui.";
			link.l1.go = "Himenes_14_1";
			link.l2 = "Non.";
			link.l2.go = "Himenes_14_2";
		break;
		
		case "Himenes_14_1":
			dialog.text = " Nouveau Monde ! En effet, nous y sommes. Chez nous, ils disent que les pirates sont de vrais démons et même pas humains. Qu'ils mangent les enfants, violent les femmes, et écorchent la peau des bons catholiques. Est-ce vrai ?";
			link.l1 = "Ca depend du jour de la semaine. Parlons-en une autre fois. Je cherche des gens. Des individus travailleurs et capables prets a vivre loin de la civilisation pendant plusieurs annees. Seriez-vous interesse par quelque chose comme ca?";
			link.l1.go = "Himenes_15";
		break;
		
		case "Himenes_14_2":
			dialog.text = "C'est dommage, puisque je suis déjà un criminel, j'aimerais voir au moins un pirate.";
			link.l1 = "Peut-être aurez-vous une telle opportunité à nouveau. Discutons-en une autre fois. Je cherche des individus travailleurs et capables, prêts à vivre loin de la civilisation pendant plusieurs années. Seriez-vous intéressé par quelque chose comme ça?";
			link.l1.go = "Himenes_15";
		break;
		
		case "Himenes_15":
			dialog.text = "Nous n'avons pas d'autre issue. Mais ce n'est pas vraiment une mauvaise option. Nous l'accepterons si vous nous permettez de vivre et de travailler en paix. Et promettez de nous renvoyer chez nous un jour ! Donnez-nous votre parole, monsieur, et dites-nous votre nom..";
			link.l1 = "Moi, Capitaine "+GetFullName(pchar)+", te donne ma parole. ?";
			link.l1.go = "Himenes_16";
		break;
		
		case "Himenes_16":
			dialog.text = "Ha-ha ! Nous sommes sauvés ! Ainsi soit-il ! Nous sommes plusieurs familles, environ 30 personnes. Tous sont lettrés, formés aux métiers et au commerce.";
			link.l1 = "Le destin a décidé... S'il vous plaît, montez à bord !";
			link.l1.go = "Himenes_17";
		break;
		
		case "Himenes_17":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto1", "none", "", "", "", 10.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			IslaMona_TerksHimenesOnBoard();
		break;
		
		case "Himenes_18":
			dialog.text = "Enchanté de faire votre connaissance, Senor Rodgar. Il semble que nous devrons vivre et travailler ensemble pendant longtemps... Mon Dieu, comment supportez-vous cette chaleur ?";
			link.l1 = "";
			link.l1.go = "Himenes_19";
		break;
		
		case "Himenes_19":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_14";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Himenes_20":
			dialog.text = "Si cela ne vous dérange pas, je vais intervenir : Capitaine, donnez-nous une journée pour nous installer et inspecter rapidement l'inventaire et la terre. Je suis sûr que Senor Rodgar a plein d'idées sur ce qu'on peut faire de ce lopin de terre. Je pense que nous ferons une bonne équipe.";
			link.l1 = "Tu n'as pas vraiment le choix, Hymenese. Ha-ha.!";
			link.l1.go = "Himenes_21";
		break;
		
		case "Himenes_21":
			dialog.text = "Ha-ha-ha-ha-ha-ha !";
			link.l1 = "";
			link.l1.go = "Himenes_22";
		break;
		
		case "Himenes_22":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_16";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Himenes_23":
			dialog.text = "Oui, Capitaine ?";
			link.l1 = "Hyme'ne'se, des bonnes nouvelles pour moi ?";
			link.l1.go = "Himenes_24";
		break;
		
		case "Himenes_24":
			dialog.text = "Capitaine, c'est un cauchemar. Votre maison n'est pas mal, bien sûr. Mais autrement... C'est impossible de vivre dans ces huttes, entourées de broussailles, et Senor Rodgar ne sait même pas ce qui se passe à l'autre bout de l'île !! Incroyable ! Ha-ha !";
			link.l1 = "Es-tu nerveux ou es-tu vraiment en train de rire de cela en ce moment ?";
			link.l1.go = "Himenes_25";
		break;
		
		case "Himenes_25":
			dialog.text = "Bien sûr, c'est drôle ! Que faisaient-ils toutes ces années ? Tout d'abord, nous devons finir de construire quelques maisons et réparer ces huttes pour qu'elles soient dans un état acceptable. Les gens ont besoin de vivre décemment pour travailler avec zèle. De plus, je demanderai aux pirates de mener une reconnaissance complète de l'île. Peut-être que cet endroit est riche non seulement en rochers et en sable. Quand tout sera fait, je pourrai vous dire exactement quoi faire de cette terre.";
			link.l1 = "Ça a l'air génial ! Que dois-je faire ?";
			link.l1.go = "Himenes_26";
		break;
		
		case "Himenes_26":
			AddQuestRecordInfo("IslaMonaData", "1");
			dialog.text = "Matériaux pour maisons, meubles, et abris temporaires. J'ai tout calculé. Voici, prends la liste.";
			link.l1 = "Impressionnant...";
			link.l1.go = "Himenes_27";
		break;
		
		case "Himenes_27":
			dialog.text = "Vraiment ? Monsieur, nous avons construit des cathédrales ! Ça, c'est impressionnant....";
			link.l1 = "Je suis enclin à te croire ! Ne construis pas accidentellement une cathédrale ici. Devrai-je transporter beaucoup de matériel ici à chaque fois ?";
			link.l1.go = "Himenes_28";
		break;
		
		case "Himenes_28":
			dialog.text = "Non, ces matériaux nous soutiendront un moment, mais nous devrons encore apporter certaines choses plus tard. Si tu veux éviter de tels ennuis à l'avenir, apporte deux fois plus de matériaux.";
			link.l1 = "Eh bien, tu m'as convaincu. Je verrai ce que je peux faire. Des délais ?";
			link.l1.go = "Himenes_29";
		break;
		
		case "Himenes_29":
			dialog.text = "Non, monsieur. Mais je vous prie de ne pas tarder - c'est le travail qui doit être fait pour faire avancer les choses. Et les gens ont besoin d'un endroit où vivre aussi. Chargez les matériaux dans l'entrepôt et n'oubliez pas de me prévenir quand tout sera prêt. Oh, j'ai presque oublié ! Parlez à M. Rodgar de l'exploration de l'île.";
			link.l1 = "D'accord!";
			link.l1.go = "Himenes_30";
		break;
		
		case "Himenes_30":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_exit";
			pchar.questTemp.IslaMona = "stalk";
			AddQuestRecord("IslaMona", "6");
		break;
		
		case "Himenes_31":
			dialog.text = "Ouais, Capitaine ?";
			if (IslaMona_CheckBuild()) // привез товары на стройку
			{
				link.l1 = "Bonjour, Hymenez. Vérifie l'entrepôt.";
				link.l1.go = "Himenes_32_1";
			}
			else // не привез товары на стройку
			{
				link.l1 = "Bonjour, Hymenez. Mes hommes ont fouillé toute l'île. Que dis-tu ?";
				if (CheckAttribute(pchar, "questTemp.IslaMona.Food")) link.l1.go = "Himenes_32_2"; // привез еду и лекарства
				else link.l1.go = "Himenes_32_3";
			}
		break;
		
		case "Himenes_32_1":
			IslaMona_RemoveBuild(); // сразу удаляем товары со склада
			dialog.text = "Vous avez géré cette responsabilité avec brio ! Si jamais vous êtes à Cadix, venez travailler pour moi comme magasinier !";
			link.l1 = "Je suis en route ! Dis-moi, compadre, que vas-tu faire maintenant ?";
			if (CheckAttribute(pchar, "questTemp.IslaMona.Food")) link.l1.go = "Himenes_34_1"; // привез еду и лекарства
			else link.l1.go = "Himenes_34_2";
		break;
		
		case "Himenes_32_2":
			dialog.text = "Señor Capitaine, traitons d'abord du logement et des provisions. Nous ferons des plans ensuite. J'attends les marchandises de votre liste à l'entrepôt.";
			link.l1 = "D'accord, je comprends. D'abord, nous devons construire des maisons et ranger cet endroit. Les marchandises arriveront bientôt.";
			link.l1.go = "Himenes_33";
		break;
		
		case "Himenes_32_3":
			dialog.text = "Capitaine, occupons-nous d'abord du logement et des provisions. Nous pourrons faire des plans plus tard. J'attends les marchandises de votre liste à l'entrepôt. Et votre ami pirate attend aussi des provisions et des médicaments.";
			link.l1 = "D'accord, je comprends. D'abord, nous devons construire des maisons et ranger cet endroit. Les marchandises arriveront bientôt. Et pour mon ami pirate aussi.";
			link.l1.go = "Himenes_33";
		break;
		
		case "Himenes_33":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_31";
		break;
		
		case "Himenes_34_1":
			dialog.text = "Donnez-nous six mois, Capitaine, et vous ne reconnaîtrez pas cet endroit.";
			link.l1 = "Es-tu en train de dire que dans six mois, il n'y aura ni toi, ni la colonie, ni les matériaux ici ? À plus tard !";
			link.l1.go = "Himenes_37"; // все выполнил
		break;
		
		case "Himenes_34_2":
			dialog.text = "Nous commencerons à travailler dès que vous aurez réglé vos affaires avec ce bandit. Il a demandé des provisions et des médicaments de votre part, et je suis d'accord avec lui - c'est une demande raisonnable.";
			link.l1 = "Je transmettrai vos paroles à lui.";
			link.l1.go = "Himenes_35";
			AddQuestRecord("IslaMona", "11");
		break;
		
		case "Himenes_35":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_36";
		break;
		
		case "Himenes_36":
			dialog.text = "Eh bien, Capitaine ? Avez-vous fait tout ce que votre pirate a demandé ?";
			if (CheckAttribute(pchar, "questTemp.IslaMona.Food"))
			{
				link.l1 = "J'ai résolu tous les problèmes avec Rodgar. La reconnaissance de l'île a commencé, provisions et médicaments sont dans l'entrepôt. Maintenant c'est ton tour.";
				link.l1.go = "Himenes_34_1";
			}
			else
			{
				link.l1 = "Ne t'inquiète pas, nous allons le résoudre. Je m'en occupe.";
				link.l1.go = "Himenes_35";
			}
		break;
		
		case "Himenes_37":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_exit";
			DeleteAttribute(pchar, "questTemp.IslaMona.Food");
			pchar.questTemp.IslaMona = "build";
			AddQuestRecord("IslaMona", "12");
			SetFunctionTimerCondition("IslaMona_BuildDone", 0, 0, 180, false);
		break;
		
		case "Himenes_38":
			dialog.text = "Seigneur Capitaine ! Que pensez-vous ? Ha-ha-ha ?";
			link.l1 = "C'est bien plus agréable. Rapport, Himenes !";
			link.l1.go = "Himenes_39";
		break;
		
		case "Himenes_39":
			dialog.text = "Maintenant vous pouvez vraiment vivre ici ! Nous avons nettoyé et reconstruit toutes les maisons, sauf la vôtre, bien sûr. Pas très luxueux, mais pas pire que dans notre Belize.";
			link.l1 = "Belize appartient depuis longtemps à l'Angleterre, Himenes.";
			link.l1.go = "Himenes_40";
		break;
		
		case "Himenes_40":
			dialog.text = "Je ne suis pas sûr que les maisons le sachent, Capitaine, ha-ha !";
			link.l1 = "Maintenant, vous avez un endroit où vivre, et la colonie a l'air habitée. Que faire ensuite ?";
			link.l1.go = "Himenes_41";
		break;
		
		case "Himenes_41":
			dialog.text = "Regarde autour de toi, parle au Senior Janssen, et reviens me voir. Nous discuterons des résultats de la reconnaissance de l'île et de nos plans.";
			link.l1 = "Depuis quand as-tu commencé à appeler Rodgar ainsi? N'étais-tu pas constamment en désaccord?";
			link.l1.go = "Himenes_42";
		break;
		
		case "Himenes_42":
			dialog.text = "Et nous les avons toujours. Mais nous devons établir des relations de travail d'une manière ou d'une autre.";
			link.l1 = "Merci, Rodrigo. Je reviendrai bientôt.";
			link.l1.go = "Himenes_43";
		break;
		
		case "Himenes_43":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload6", "none", "", "", "", 10.0); // возможно будет иной локатор в новой локации
			pchar.questTemp.IslaMona = "village";
		break;
		
		case "Himenes_44":
			dialog.text = "Capitaine. Señor Janssen.";
			link.l1 = "Allez, raconte-moi les résultats de la reconnaissance de l'île.";
			link.l1.go = "Himenes_45";
		break;
		
		case "Himenes_45":
			dialog.text = "Oui, Capitaine. Certains endroits, je les ai inspectés personnellement avec notre prospecteur. Eh bien, que puis-je dire... Isla Mona est une île pauvre, minuscule et assez inintéressante. Il y a très peu d'espace pour la construction, le paysage est difficile, escarpé, et il n'y a presque pas de terre fertile. Trois plages, une grotte inondée, des fourrés denses, quelques perroquets, un troupeau de chèvres, et nous...";
			link.l1 = "Es-tu sérieux ? Tu dis que le bien le plus précieux de cette île est un troupeau de chèvres ?";
			link.l1.go = "Himenes_46";
		break;
		
		case "Himenes_46":
			dialog.text = "Ha-ha-ha-ha ! Je demanderais, Señor ! Ha-ha ! Vous ne m'avez pas laissé finir !";
			link.l1 = "";
			link.l1.go = "Himenes_47";
		break;
		
		case "Himenes_47":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_38";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_48":
			dialog.text = "";
			link.l1 = "Très bien, d'accord, calme-toi et continue. Tu sais, j'ai beaucoup investi dans cet endroit.";
			link.l1.go = "Himenes_49";
		break;
		
		case "Himenes_49":
			dialog.text = "Et pas en vain ! Il y a suffisamment d'eau douce dans la grotte, assez de terre pour faire pousser des arbres fruitiers, et on peut élever des chèvres. Avec la pêche et les efforts de vos camarades, le problème de la nourriture sera résolu très rapidement.";
			link.l1 = "Alors, tu n'auras plus besoin d'apporter plus de nourriture ici ? Pas mal. J'espérais que cet endroit pourrait vivre sans mes soins constants. Continuons.";
			link.l1.go = "Himenes_50";
		break;
		
		case "Himenes_50":
			dialog.text = "Vous avez raison sur tout, Señor. Mais ce n'est pas toutes les nouvelles ! Premièrement, Señor Rodgar a eu l'idée de construire une taverne. Je ne sais pas ce que cela vous apportera, mais ce fripon mijote quelque chose.";
			link.l1 = "Il veut se soûler, c'est ça !";
			link.l1.go = "Himenes_51";
		break;
		
		case "Himenes_51":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_40";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_52":
			dialog.text = "Deuxièmement, la Baie du Gouverneur s'est avérée être beaucoup plus profonde que nous ne le pensions à l'origine. Nous pouvons construire un quai en bonne et due forme.";
			link.l1 = "Je ne comprends pas vraiment comment cela me profitera, mais c'est déjà une bonne nouvelle. Ce n'est pas tout, j'espère ?";
			link.l1.go = "Himenes_53";
		break;
		
		case "Himenes_53":
			dialog.text = "Nous avons trouvé un bosquet d'arbres de bacote. Un endroit idéal pour une usine.";
			link.l1 = "Tu me rends heureux, Rodrigo ! En effet, d'excellentes nouvelles !";
			link.l1.go = "Himenes_54";
		break;
		
		case "Himenes_54":
			dialog.text = "C'est tout pour le moment, señor. Nous pourrions avoir plus d'idées à l'avenir. Vous comprenez, les meilleures idées viennent en travaillant ! De quoi aimeriez-vous vous renseigner ?";
			link.l1 = "Parle-moi du bacote. Cela semble prometteur.";
			link.l1.go = "Himenes_55";
		break;
		
		case "Himenes_55":
			dialog.text = "Selon mon estimation, une petite usine pourra extraire ce bois précieux pendant plusieurs années. Les réserves sont modestes, mais la ressource est stratégique. Nous pouvons défricher un site au centre de l'île et y construire une maison avec un entrepôt. C'est un début. En plus des matériaux de construction, nous aurons également besoin d'environ 15 paires de menottes et de mousquets.";
			link.l1 = "Et pourquoi avons-nous besoin de menottes? Et pourquoi exactement quinze?";
			link.l1.go = "Himenes_56";
		break;
		
		case "Himenes_56":
			dialog.text = "C'est un travail ardu, señor. Je dirais même que c'est un travail d'esclave.";
			link.l1 = "Je comprends. Hi-hi...";
			link.l1.go = "Himenes_57_1";
			link.l2 = "Es-tu devenu fou? Je ne deviendrai pas un propriétaire d'esclaves!";
			link.l2.go = "Himenes_57_2";
		break;
		
		case "Himenes_57_1":
			dialog.text = "";
			link.l1 = "Et pourquoi avons-nous besoin d'un mousquet ? Et pourquoi seulement un ?";
			link.l1.go = "Himenes_59";
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
		break;
		
		case "Himenes_57_2":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_42";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
		break;
		
		case "Himenes_58":
			dialog.text = "Je suis d'accord avec le pirate, señor. Je ne te comprends pas, capitaine. Toute l'économie de cette région repose sur le travail des esclaves, et il en sera ainsi pendant de nombreuses années à venir. En quoi sommes-nous meilleurs ?";
			link.l1 = "Je prendrai une décision. En attendant, dis-moi pourquoi tu as besoin d'un mousquet ? Et pourquoi précisément un seul ?";
			link.l1.go = "Himenes_59";
		break;
		
		case "Himenes_59":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_44";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_60":
			dialog.text = "Bien sûr, l'usine nécessitera de l'entretien. Avec sa construction, cette île aura une économie dont vous serez le principal partenaire commercial. Nous nourrirons les esclaves nous-mêmes, mais vous devrez payer la sécurité et la production de votre propre poche. Les colons prendront cent doublons et cinq bouteilles de vin pour chaque lot. Pour les questions de sécurité, négociez avec Señor Janssen.";
			link.l1 = "";
			link.l1.go = "Himenes_61";
		break;
		
		case "Himenes_61":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_46";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_62":
			dialog.text = "quarante mesures chaque mois. Et l'or est pour l'avenir. Un jour, tu nous emporteras d'ici, te souviens-tu de ta promesse ? Tout travail doit être payé, et avec tes doublons, nous paierons les chasseurs et les artisans pour leur travail dans la colonie. Ainsi, nous aurons du commerce, et avec lui - la civilisation !";
			link.l1 = "C'est l'esprit ! D'accord ! Pour l'instant, tout semble suffisamment convaincant...";
			link.l1.go = "Himenes_63";
		break;
		
		case "Himenes_63":
			dialog.text = "Quoi d'autre vous intéresse ?";
			link.l1 = "Alors, quelle est l'histoire avec la taverne ? Pourquoi ne pas construire un théâtre ?";
			link.l1.go = "Himenes_64";
		break;
		
		case "Himenes_64":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_48";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_65":
			dialog.text = "Capitaine, je l'ai averti que vous n'aimeriez pas l'idée de la maison. Mais c'est la seule option. Vous avez la plus grande maison de... hum, la ville, nous transformerons le rez-de-chaussée en salle, installerons des tables et une cuisine. Nous stockerons les boissons et la nourriture dans les grottes sous la maison. Nous avons des gens pour cuisiner et jouer de la musique. Le deuxième étage restera à vous, et nous n'y toucherons pas. Nous monterons toutes vos affaires du rez-de-chaussée nous-mêmes.";
			link.l1 = "D'accord. Alors, qu'est-ce que la taverne nous donnera exactement ?";
			link.l1.go = "Himenes_66";
		break;
		
		case "Himenes_66":
			dialog.text = "Nous aurons un peu de vie culturelle, et tu auras l'occasion d'avoir environ trois cents personnes en réserve en plein cœur des Caraïbes.";
			link.l1 = "Intéressant... Je vais y réfléchir.";
			link.l1.go = "Himenes_67";
		break;
		
		case "Himenes_67":
			dialog.text = "Quoi d'autre vous intéresse ?";
			link.l1 = "Eh bien, qu'en est-il du quai ?";
			link.l1.go = "Himenes_68";
		break;
		
		case "Himenes_68":
			dialog.text = "C'est simple. Nous dégagerons la Baie du Gouverneur des récifs, installerons des feux de signalisation et construirons un quai. Le señor Janssen affirme que vous pourrez abriter trois navires dans la baie, ou un navire de première classe. Et il sera plus agréable pour vous de revenir ici, sans traîner l'annexe sur la plage à chaque fois.";
			link.l1 = "Ce serait agréable.";
			link.l1.go = "Himenes_69";
		break;
		
		case "Himenes_69":
			dialog.text = "Que voudrais-tu savoir?";
			link.l1 = "C'est tout pour l'instant. Je reviendrai quand j'aurai décidé quoi construire.";
			link.l1.go = "Himenes_70";
		break;
		
		case "Himenes_70":
			dialog.text = "Seigneur Capitaine, prenez ce document. J'ai pris la liberté de noter tous les détails pour ne pas les répéter une douzaine de fois. Étudiez-le, apportez des matériaux, et fixez la tâche.";
			link.l1 = "Merci, Rodrigo.";
			link.l1.go = "Himenes_71";
		break;
		
		case "Himenes_71":
			DialogExit();
			IslaMona_HouseDialogFin();
		break;
		
		case "Himenes_72": // нода Хименеса строителя и управляющего факторией
			if (CheckAttribute(pchar, "questTemp.IslaMona.RecordPart")) // после защиты Исла Моны - нужно еще 10 рабов
			{
				dialog.text = "Seigneur Capitaine, nous avons besoin de 10 esclaves pour travailler dans l'usine - je vous l'ai dit, vous n'avez pas oublié, n'est-ce pas ?";
				if (GetSquadronGoods(pchar, GOOD_SLAVES) >= 10)
				{
					link.l1 = "Deja livre. Dechargez-les et commencez la production.";
					link.l1.go = "Himenes_plantation_12";
				}
				else
				{
					link.l1 = "Ma mémoire est intacte. Je les apporterai bientôt.";
					link.l1.go = "Himenes_plantation_14";
				}
				break;
			}
			dialog.text = "Alors, Senor Capitaine, que dites-vous ?";
			if (!CheckAttribute(pchar, "questTemp.IslaMona.Harbour"))
			{
				link.l1 = "Je veux une baie propre et un quai sûr. Ce sera la base pour ma flotte.";
				link.l1.go = "Himenes_harbour";
			}
			if (!CheckAttribute(pchar, "questTemp.IslaMona.Tavern"))
			{
				link.l2 = "Allez-y et construisez la taverne. Tout le monde l'appréciera, et je pourrai garder une réserve ici.";
				link.l2.go = "Himenes_tavern";
			}
			if (!CheckAttribute(pchar, "questTemp.IslaMona.Plantation"))
			{
				link.l3 = "Commencez à construire la plantation. Il est temps de récupérer les investissements.";
				link.l3.go = "Himenes_plantation";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Plantation.Slave") && IslaMona_CheckSlave())
			{
				link.l4 = "Rodrigo, les spécialistes et équipements particulièrement précieux ont été livrés à l'usine. Tu peux commencer à travailler.";
				link.l4.go = "Himenes_plantation_7";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Factory.Part") && sti(pchar.questTemp.IslaMona.Factory.Part) > 0)
			{
				link.l4 = "Rodrigo, je suis venu pour mon bois de fer.";
				link.l4.go = "Himenes_bacaut";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Harbour") && pchar.questTemp.IslaMona.Harbour == "done" && CheckAttribute(pchar, "questTemp.IslaMona.Tavern") && pchar.questTemp.IslaMona.Tavern == "done" && CheckAttribute(pchar, "questTemp.IslaMona.Factory") && !CheckAttribute(pchar, "questTemp.IslaMona.Church"))
			{
				link.l5 = "Rodrigo, avons-nous terminé notre grande construction ?";
				link.l5.go = "Himenes_church";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Church") && pchar.questTemp.IslaMona.Church == "start" && IslaMona_CheckChurch())
			{
				link.l5 = "Rodrigo, construisons ton église.";
				link.l5.go = "Himenes_church_10";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Church") && pchar.questTemp.IslaMona.Church == "Wait_candles" && IslaMona_CheckCandles())
			{
				link.l5 = "Rodrigo, j'ai apporté tes objets d'église.";
				link.l5.go = "Himenes_church_10_3";
			}
			link.l10 = "Rien pour l'instant...";
			link.l10.go = "Himenes_73";
		break;
		
		case "Himenes_harbour":
			if (IslaMona_CheckHarbour())
			{
				dialog.text = "Les matériaux sont disponibles, tout est prêt. La construction prendra 4 mois.";
				link.l1 = "Tu n'es pas pressé, n'est-ce pas ! Eh bien, bonne chance, Rodrigo.";
				link.l1.go = "Himenes_harbour_1";
			}
			else
			{
				dialog.text = "J'ai bien peur qu'il n'y ait pas assez de matériaux dans l'entrepôt. S'il te plaît, vérifie la liste à nouveau.";
				link.l1 = "Je m'en occuperai.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_tavern":
			if (IslaMona_CheckTavern())
			{
				dialog.text = "Les matériaux sont disponibles, tout est prêt. La construction prendra 3 mois.";
				link.l1 = "Tu n'es pas pressé, n'est-ce pas ! Eh bien, bonne chance, Rodrigo.";
				link.l1.go = "Himenes_tavern_1";
			}
			else
			{
				dialog.text = "J'ai bien peur qu'il n'y ait pas assez de matériaux dans l'entrepôt. Je vous prie de vérifier à nouveau la liste.";
				link.l1 = "Je m'en occuperai.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_plantation":
			if (IslaMona_CheckPlantation())
			{
				dialog.text = "Les matériaux sont disponibles, tout est prêt. La construction prendra 6 mois.";
				link.l1 = "Vous n'êtes pas pressé, n'est-ce pas ! Bonne chance, Rodrigo.";
				link.l1.go = "Himenes_plantation_1";
			}
			else
			{
				dialog.text = "J'ai bien peur qu'il n'y ait pas assez de matériaux dans l'entrepôt. S'il vous plaît, vérifiez la liste à nouveau.";
				link.l1 = "Je m'en occuperai.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_73":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
		break;
		
		case "Himenes_harbour_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_RemoveHarbour();
			pchar.questTemp.IslaMona.Harbour = "true";
			SetFunctionTimerCondition("IslaMona_BuildHarbour", 0, 0, 120, false);
		break;
		
		case "Himenes_harbour_2":
			dialog.text = "Bienvenue, Capitaine. Comment trouvez-vous votre nouveau port ?";
			if (stf(environment.time) > 22.0 || stf(environment.time) < 5.0)
			{
				link.l1 = "C'est sombre, Rodrigo ! Nous avons failli nous écraser sur ton quai tant vanté ! Bien joué de l'avoir au moins éclairé !";
				link.l1.go = "Himenes_harbour_3";
			}
			else
			{
				link.l1 = "Pas mal, Rodrigo ! Cela paraît peu de chose, mais c'est agréable de marcher sur ces planches jusqu'au rivage. Et la baie est devenue plus facile à naviguer. Alors, je suppose que maintenant je peux accueillir plus de navires dans cette petite baie ?";
				link.l1.go = "Himenes_harbour_4";
			}
		break;
		
		case "Himenes_harbour_3":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_51";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_harbour_4":
			sld = characterFromId("Islamona_carpenter");
			sld.portman.info = "true"; // если вдруг до сих пор не говорил об условиях стоянки
			pchar.questTemp.IslaMona.Harbour = "done"; // флаг - пристань построена и сдана
			dialog.text = "Oui, Capitaine. Je dois dire qu'il y a une certaine fierté à cela. N'hésitez pas à me faire savoir comment vous souhaitez poursuivre notre grand projet de construction.";
			if (CheckAttribute(pchar, "questTemp.IslaMona.Plantation") && pchar.questTemp.IslaMona.Plantation == "complete") // если пересеклось со сдачей фактории
			{
				link.l1 = "En parlant de construction. Ma fabrique devrait aussi être terminée maintenant. N'est-ce pas, Rodrigo ?";
				link.l1.go = "Himenes_plantation_2";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "Himenes_harbour_5";
			}
		break;
		
		case "Himenes_harbour_5":
			DialogExit();
			IslaMona_HarbourClear();
		break;
		
		case "Himenes_tavern_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_RemoveTavern();
			pchar.questTemp.IslaMona.Tavern = "true";
			SetFunctionTimerCondition("IslaMona_BuildTavern", 0, 0, 90, false);
		break;
		
		case "Himenes_tavern_2":
			dialog.text = "H-hic ! Cap ! On fête ça ici !";
			link.l1 = "Rodgar. Rodrigo. Oh, diable!";
			link.l1.go = "Himenes_tavern_3";
		break;
		
		case "Himenes_tavern_3":
			dialog.text = "Qu'y a-t-il, c-c-capitaine ? La couleur des murs ne vous plaît-elle pas ?";
			link.l1 = "Je viens juste de réaliser que vous deux partagez le même nom ! Ha-ha-ha ! Un Espagnol et un pirate, avec le même nom, ont construit une taverne sur une île déserte et boivent ensemble comme si les dieux indiens allaient dévorer tout le monde et mettre fin au monde au lever du soleil ! Ha-ha ! Je suis avec vous !";
			link.l1.go = "Himenes_tavern_4";
		break;
		
		case "Himenes_tavern_4":
			dialog.text = "Ha-ha-ha! Si vrai! Score!";
			link.l1 = " Butin ! ";
			link.l1.go = "Himenes_tavern_5";
		break;
		
		case "Himenes_tavern_5":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_ReloadTavern();
		break;
		
		case "Himenes_plantation_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_RemovePlantation();
			pchar.questTemp.IslaMona.Plantation = "true";
			SetFunctionTimerCondition("IslaMona_BuildPlantation", 0, 0, 180, false);
		break;
		
		case "Himenes_plantation_2":
			dialog.text = "Tout est prêt. Allons-y ? Laisse-moi te montrer ton usine.";
			link.l1 = "Mene le chemin.";
			link.l1.go = "Himenes_plantation_3";
		break;
		
		case "Himenes_plantation_3":
			DialogExit();
			pchar.questTemp.IslaMona.Plantation.Harbour = "true"; // наложилась сдача пристани и фактории
			IslaMona_PlantationGo();
		break;
		
		case "Himenes_plantation_4":
			dialog.text = "Capitaine, presque tout est prêt pour commencer les opérations. Logements pour les ouvriers, entrepôt pour les matières premières, zone de traitement - une usine digne a été construite. Nous avons déjà marqué les arbres les plus prometteurs pour l'abattage dans la jungle. Amenez quinze ouvriers et l'inventaire convenu - 15 fers et mousquets, et nous commencerons à travailler.";
			link.l1 = "Nous ? Vous voulez dire les esclaves ?";
			link.l1.go = "Himenes_plantation_5";
		break;
		
		case "Himenes_plantation_5":
			dialog.text = "Ha ! Esclaves... Les esclaves couperont, les colons traiteront, et les pirates garderont. Tout le monde aura du travail - vous avez entrepris une affaire sérieuse, Capitaine.";
			link.l1 = "Presque comme la terre promise, hein. Attends la marchandise, il est temps pour moi de partir à la chasse.";
			link.l1.go = "Himenes_plantation_6";
		break;
		
		case "Himenes_plantation_6":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Plantation.Slave = "true"; // привезти рабов, кандалы и мушкет для запуска фактории
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "IslaMona_factoria_residence", "sit", "sit1", "IslaMona_PlantationHouse", -1);
			sld = characterFromId("Islamona_carpenter");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5);
			pchar.questTemp.IslaMona.Plantation = "done"; // флаг - фактория построена и сдана
		break;
		
		case "Himenes_plantation_7":
			dialog.text = "Un triste destin... Ils ne quitteront jamais cet endroit.";
			link.l1 = "Rodgar... Je veux dire, Rodrigo ! Premièrement, ils pourraient partir. Et deuxièmement, si tu rencontrais quelqu'un d'autre à Terks, ton sort ne serait pas meilleur.";
			link.l1.go = "Himenes_plantation_8";
		break;
		
		case "Himenes_plantation_8":
			dialog.text = "Je le sais très bien, Capitaine. Et je ne l'oublie pas. Laissez-moi vous parler du fonctionnement de cette usine. A partir du mois prochain, le quinzième jour, nous livrerons quarante bûches de bois traité. Bien sûr, vous n'avez pas besoin de venir pour chaque livraison chaque mois - tous les lots seront stockés et vous attendront ici, à l'usine.";
			link.l1 = "Alors, je peux prendre plusieurs lots à la fois ?";
			link.l1.go = "Himenes_plantation_9";
		break;
		
		case "Himenes_plantation_9":
			dialog.text = "Dans la mesure du raisonnable, bien sûr - ne t'éloigne pas trop longtemps. Les gens ne travailleront pas des années sans paie, sans savoir si leur seul client est encore en vie ou non. Je pense que nous livrerons six lots avant de suspendre les opérations.";
			link.l1 = "Dois-je ramasser toutes les marchandises d'un coup ? Qu'en est-il du prix, rappelle-moi ?";
			link.l1.go = "Himenes_plantation_10";
		break;
		
		case "Himenes_plantation_10":
			dialog.text = "Oui,   tout d'un coup.   Le prix d'un tronc de bacout standard est de dix doublons.   En outre, pour chaque lot, tu devras donner cinq bouteilles de bon rhum et le même nombre de bouteilles de vin. Rodgar prétend que tu ne trouveras pas de tels prix ailleurs dans le monde.";
			link.l1 = "En effet, je suis d'accord ! Merci, Rodrigo. Allons au travail !";
			link.l1.go = "Himenes_plantation_11";
		break;
		
		case "Himenes_plantation_11":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			DeleteAttribute(pchar, "questTemp.IslaMona.Plantation.Slave");
			AddQuestRecordInfo("Unique_Goods", "5");
			IslaMona_RemoveSlave();
		break;
		
		case "Himenes_plantation_12":
			dialog.text = "Excellent! Maintenant, nous allons reprendre le travail!";
			link.l1 = "Bien.";
			link.l1.go = "Himenes_plantation_13";
		break;
		
		case "Himenes_plantation_13":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_FactoryReActivar(); // запустить факторию
		break;
		
		case "Himenes_plantation_14":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
		break;
		
		case "Himenes_bacaut":
			dialog.text = "Bien sûr, capitaine, prenez-le. Nous avons les lots suivants prêts pour la prochaine date : "+sti(pchar.questTemp.IslaMona.Factory.Part)+", c'est "+sti(pchar.questTemp.IslaMona.Factory.Goods)+" bûches. Par conséquent, tu nous dois "+sti(pchar.questTemp.IslaMona.Factory.Dublon)+" doublons, "+sti(pchar.questTemp.IslaMona.Factory.Bottle)+" bouteilles de rhum, et "+sti(pchar.questTemp.IslaMona.Factory.Bottle)+" bouteilles de vin, avez-vous tout cela ?";
			if (PCharDublonsTotal() >= sti(pchar.questTemp.IslaMona.Factory.Dublon) && PCharItemsTotal("potionrum") >= sti(pchar.questTemp.IslaMona.Factory.Bottle) && PCharItemsTotal("potionwine") >= sti(pchar.questTemp.IslaMona.Factory.Bottle))
			{
				link.l1 = "Bien sûr. Voici votre paiement.";
				link.l1.go = "Himenes_bacaut_1";
			}
			else
			{
				link.l1 = "Il semble que je n'ai pas tout. Je l'apporterai tout de suite.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_bacaut_1":
			if (IslaMona_CheckBacautSpace())
			{
				dialog.text = "Excellent. Nous transporterons le bacout de l'usine à votre entrepôt, d'où vous pourrez le récupérer quand vous le souhaitez.";
				link.l1 = "Génial. Prépare le prochain lot.";
				link.l1.go = "Himenes_bacaut_2";
			}
			else
			{
				dialog.text = "Attendez, capitaine ! Votre entrepôt est plein - nous ne pourrons pas charger tout le tabac récolté là-bas. Faites de la place dans l'entrepôt - puis revenez me voir.";
				link.l1 = "D'accord, je m'en occuperai.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_bacaut_2":
			dialog.text = "Bien sûr, capitaine !";
			link.l1 = "...";
			link.l1.go = "Himenes_73";
			IslaMona_FactoryTrade();
		break;
		
		case "Himenes_church":
			dialog.text = "Ha ! Capitaine, j'ai bien peur que construire quoi que ce soit d'autre serait une folie et une extravagance inutiles. A moins que...";
			link.l1 = "À moins que quoi ?";
			link.l1.go = "Himenes_church_1";
		break;
		
		case "Himenes_church_1":
			dialog.text = "Capitaine, cela me gêne de vous demander cela... Vous avez déjà investi une somme énorme dans cet endroit !";
			link.l1 = "Un bordel ?";
			link.l1.go = "Himenes_church_2_1";
			link.l2 = "Une église ?";
			link.l2.go = "Himenes_church_2_2";
		break;
		
		case "Himenes_church_2_1":
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			dialog.text = "Je jure par Saint Jacques, ce ne serait pas mal ! Mais dès la première nuit, nos femmes le réduiraient en cendres. Avec nous. Non, capitaine, je parle d'une église. Oui, nous avons des logements décents et une paie, la mer et des divertissements, des familles et des amis. Mais malgré tout, il manque quelque chose, vous comprenez ?";
			link.l1 = "Je peux imaginer.";
			link.l1.go = "Himenes_church_3";
		break;
		
		case "Himenes_church_2_2":
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			AddCharacterExpToSkill(pchar, "Defence", 500);
			dialog.text = "Vous voyez clair en moi, capitaine. Oui, nous avons des logements décents et un salaire, la mer et des divertissements, des familles et des amis. Mais pourtant, il manque quelque chose, vous comprenez ?";
			link.l1 = "Je peux imaginer.";
			link.l1.go = "Himenes_church_3";
		break;
		
		case "Himenes_church_3":
			dialog.text = "Exactement. Nous ne pouvons pas construire la Maison de Dieu sans votre aide. Un tel lieu doit être spécial, il doit être hors de ce monde. Et donc, il devrait être coûteux. Nous aurons besoin de bougies, de lingots d'or, d'ambre et, bien sûr, de matériaux de construction, et pas des moins chers. Cela ne vous apportera aucun profit, donc je n'ose pas demander.";
			link.l1 = "Alors, as-tu besoin d'amener un pretre ici ?";
			link.l1.go = "Himenes_church_4";
		break;
		
		case "Himenes_church_4":
			dialog.text = "Non.";
			link.l1 = "Avez-vous déjà un prêtre parmi vous ?";
			link.l1.go = "Himenes_church_5";
		break;
		
		case "Himenes_church_5":
			dialog.text = "Non, capitaine. Et je pense que vous avez déjà tout compris.";
			link.l1 = "Alors, les saints pères de l'Inquisition avaient-ils une raison de vous persécuter ? Êtes-vous des hérétiques ?";
			link.l1.go = "Himenes_church_6";
		break;
		
		case "Himenes_church_6":
			dialog.text = "Selon les lois canoniques, nous sommes les pires des hérétiques. Nous ne croyons pas que communiquer avec Dieu nécessite forcément un intermédiaire de ce monde.";
			link.l1 = "De ce monde ?";
			link.l1.go = "Himenes_church_7";
		break;
		
		case "Himenes_church_7":
			dialog.text = "Capitaine, nous ne sommes pas des satanistes, et notre communauté n'est pas une secte. Nous sommes des chrétiens, comme vous, mais nous voyons les choses avec une perspective très large. Trop large, selon certaines personnes très instruites et dignes. Si jamais vous trouvez une place dans votre cœur pour l'ouverture et la compréhension, alors je vous en dirai plus. Mais pour l'instant, prenez simplement cette liste. Juste au cas où.";
			link.l1 = "Tu aurais dû m'en parler plus tôt, Rodrigo. Je ne veux pas revenir un beau jour et voir un sabbat de sorcières ou la naissance d'une nouvelle foi sur mes terres ! Pendant que tu attends - je vais prendre une décision.";
			link.l1.go = "Himenes_church_8_1";
			link.l2 = "Liste impressionnante. Je commence à comprendre pourquoi les saints pères ont besoin de tant d'argent ! Je vais réfléchir à votre offre, Rodrigo, et prendre une décision.";
			link.l2.go = "Himenes_church_8_2";
		break;
		
		case "Himenes_church_8_1":
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			dialog.text = "";
			link.l1 = "Si c'est positif, j'apporterai toutes les marchandises de votre liste à l'entrepôt, et je disposerai les trésors pour vous sur la table.";
			link.l1.go = "Himenes_church_9";
		break;
		
		case "Himenes_church_8_2":
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			dialog.text = "";
			link.l1 = "Si c'est positif, j'apporterai toutes les marchandises de votre liste à l'entrepôt, et j'étalerai les trésors pour vous sur la table.";
			link.l1.go = "Himenes_church_9";
		break;
		
		case "Himenes_church_9":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Church = "start";
			AddQuestRecord("IslaMona", "14");
			AddQuestRecordInfo("IslaMonaData", "3");
		break;
		
		case "Himenes_church_10":
			dialog.text = "Au nom de toute notre communauté, je vous remercie, capitaine. Vous ne le regretterez pas, je le jure !";
			link.l1 = "Je ne le regretterai que si tu construis quelque chose de complètement minable.";
			link.l1.go = "Himenes_church_10_1";
		break;
		
		case "Himenes_church_10_1":
			dialog.text = "Capitaine, tous les matériaux de construction sont en stock ! Nous commencerons la construction une fois que vous aurez apporté les articles de luxe listés. Ils seront utilisés pour les bijoux et les outils rituels. Encore une fois, merci beaucoup, Capitaine ! Muchas gracias !";
			link.l1 = "Je vous en prie !";
			link.l1.go = "Himenes_church_10_2";
		break;
		
		case "Himenes_church_10_2":
			DialogExit();
			IslaMona_RemoveChurch();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Church = "Wait_candles";
			pchar.questTemp.IslamonaChurch.GoldNugget = 50;
			pchar.questTemp.IslamonaChurch.Candle = 100;
			pchar.questTemp.IslamonaChurch.Amber = 30;
			pchar.questTemp.IslamonaChurch.BlueAmber = 1;
		break;
		
		case "Himenes_church_10_3":
			IslaMona_RemoveCandles();
			string sAdd = "";
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.Candle"))
			{
				sAdd += " "+sti(pchar.questTemp.IslamonaChurch.Candle)+ " candles,"
			}
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.Amber"))
			{
				sAdd += " "+sti(pchar.questTemp.IslamonaChurch.Amber)+ " amber,"
			}
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.GoldNugget"))
			{
				sAdd += " "+ sti(pchar.questTemp.IslamonaChurch.GoldNugget) + " ingots,"
			}
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.BlueAmber"))
			{
				sAdd += " and one blue amber"
			}
			if(sAdd == "")
			{
				dialog.text = "Un grand merci, capitaine ! Tout est prêt, nous commençons la construction. Revenez dans quelques mois pour le premier service. Oh, et une chose de plus, les raisins sont mûrs ! Nous ferons du vin maison, organiserons une fête et festoierons en votre honneur !";
				link.l1 = "Je pense que nous méritons tous une célébration. Je serai de retour dans deux mois.";
				link.l1.go = "Himenes_church_12";
			}
			else
			{
				dialog.text = "Capitaine, il y a encore "+sAdd+" gauche.";
				link.l1 = "Bien sûr, donnez-moi juste un peu plus de temps s'il vous plaît. Honnêtement, s'il n'y avait pas les bougies, je croirais que vous alliez enterrer un trésor.";
				link.l1.go = "Himenes_church_11";
			}
		break;
		
		case "Himenes_church_11":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
		break;
		
		case "Himenes_church_12":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Church = "build";
			AddQuestRecord("IslaMona", "15");
			//IslaMona_RemoveChurch();
			SetFunctionTimerCondition("IslaMona_ChurchComplete", 0, 0, 60, false);
		break;
		
		case "Himenes_church_13":
			dialog.text = "Ha-ha-ha-ha-ha-ha-ha-ha-ha-ha-ha!";
			link.l1 = "Et ici je pensais que tu t'étais débarrassé de cette habitude idiote.";
			link.l1.go = "Himenes_church_14";
		break;
		
		case "Himenes_church_14":
			sld = characterFromId("Islamona_carpenter");
			i = sti(sld.crew.qty);
			if (i >= 50) sTemp = "that we won't have to sit here for weeks waiting for events to unfold.";
			else sTemp = "that not everyone will have to participate in the battle.";
			dialog.text = "Ha-ha-ha-ha-ha... ha. Je le pensais aussi, capitaine ! Rodgar a raison, votre présence signifie déjà, "+sTemp+"";
			link.l1 = "Je sais déjà ce qui s'est passé. Y a-t-il des pertes ?";
			if (GetCharacterIndex("Mirabella") != -1) link.l1.go = "Himenes_church_15";
			else link.l1.go = "Himenes_church_16";
		break;
		
		case "Himenes_church_15":
			DialogExit();
			sld = characterFromId("Mirabella"); 
			sld.dialog.currentnode = "mirabelle_44";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_16":
			dialog.text = "Ne t'inquiète pas tant, Rodgar. Ce n'est pas ta faute, les fusiliers sont arrivés trop vite. Nous n'aurions pas pu les retenir derrière nos lignes de toute façon, et il n'y avait pas le temps de tous les passer au fil de l'épée.";
			link.l1 = "Qu'en est-il des Espagnols ?";
			link.l1.go = "Himenes_church_17";
		break;
		
		case "Himenes_church_17":
			sld = characterFromId("Islamona_carpenter");
			i = sti(sld.crew.qty);
			if (CheckAttribute(pchar, "questTemp.IslaMona.Defend.Force")) // решил проблему самостоятельно
			{
				dialog.text = "Seulement trois d'entre eux sont arrivés jusqu'à nous, et un seul a survécu. Le capitaine lui-même ! Apparemment, un marin militaire très sérieux. Mais il ne peut pas encore nous aider - il devra rester alité pendant au moins quelques jours de plus. Au fait, capitaine, nous avons entendu des coups de feu et à en juger par votre apparence, vous aussi.";
				link.l1 = "On pourrait dire ça. Les invités imprévus ne s'attendaient clairement pas à une visite si inattendue et furent rejetés à la mer.";
				link.l1.go = "Himenes_church_20";
			}
			else
			{
				dialog.text = "Seulement trois d'entre eux sont parvenus jusqu'à nous, et un seul a survécu. Le capitaine lui-même ! Apparemment, un marin militaire très sérieux. Mais il ne peut pas encore nous aider - il devra rester au lit pendant au moins quelques jours de plus.";
				if (i >= 50) 
				{
					link.l1 = "La derniere fois, j'ai laisse pas mal de mes hommes ici pour monter la garde, donc il devrait y avoir beaucoup plus de vous que de fusiliers. Pourquoi ne les avez-vous pas tous simplement rejetes a la mer d'un coup ?";
					link.l1.go = "Himenes_church_17_1";
				}
				else 
				{
					link.l1 = "Bien, résolvons ce problème. Le plan est le suivant : je vais les attirer pour une attaque en plein air, et tout de suite. Il n'y a pas de raison de retarder. Préparez-vous avec du plomb et des mousquets, les pirates aux portes, les autres restent à la maison - et ne bougez pas.";
					link.l1.go = "Himenes_church_18";
				}
			}
		break;
		
		case "Himenes_church_17_1":
			dialog.text = "Cap, ce sont tous des soldats professionnels, avec un commandant. Et nous n'avons même pas d'armes appropriées. Oui, bien sûr, nous aurions pu les submerger par le nombre, mais nous aurions perdu au moins deux fois plus de gens, et chaque personne est précieuse et nécessaire ici.";
			link.l1 = "D'accord, résolvons ce problème. Voici le plan : je vais les attirer pour une attaque en plein jour, et dès maintenant. Il n'y a pas de raison de tarder. Préparez-vous avec de la grenaille et des mousquets, des pirates aux portes, les autres restent à la maison - et restez tranquilles.";
			link.l1.go = "Himenes_church_18";
		break;
		
		case "Himenes_church_18":
			dialog.text = "Capitaine, nous sommes prêts à combattre !";
			link.l1 = "Je sais, Rodrigo. Mais tu ne m'as pas laissé finir : si ne serait-ce qu'un ennemi parvient à franchir les portes, vous devez tous vous précipiter sur lui de tous côtés. Et au combat, vos chances de prendre une balle ou un éclat diminuent. D'autres questions ?";
			link.l1.go = "Himenes_church_19";
		break;
		
		case "Himenes_church_19":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_68";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_20":
			dialog.text = "Bien joué ! C'est désagréable, bien sûr, qu'un sort si malheureux soit tombé sur vos compatriotes. Mais je suis reconnaissant que vous ayez encore une fois pris notre parti.";
			link.l1 = "Ce n'était pas facile, Rodrigo. Les gens ordinaires appelleront ça une trahison, et ils auront raison.";
			link.l1.go = "Himenes_church_20_1";
			link.l2 = "C'est ma terre, Rodrigo. Elle doit être défendue toujours et peu importe contre qui.";
			link.l2.go = "Himenes_church_20_2";
		break;
		
		case "Himenes_church_20a":
			dialog.text = "Oui, le vieux Rodrigo ne s'attendait pas, lorsqu'il a quitté Cadix, à ce que de telles aventures l'attendent dans le Nouveau Monde.";
			link.l1 = "N'en dis pas plus. Parfois j'ai exactement les mêmes pensées.";
			link.l1.go = "Himenes_church_20b";
		break;
		
		case "Himenes_church_20b":
			dialog.text = "C'est désagréable, bien sûr, qu'un sort si malheureux ait frappé vos compatriotes. Mais je suis reconnaissant que, encore une fois, vous ayez pris notre parti.";
			link.l1 = "Ce n'était pas facile, Rodrigo. Les gens ordinaires appelleront cela une trahison, et ils auront raison.";
			link.l1.go = "Himenes_church_20_1";
			link.l2 = "C'est ma terre, Rodrigo. Elle doit être défendue toujours et contre quiconque.";
			link.l2.go = "Himenes_church_20_2";
		break;
		
		case "Himenes_church_20_1":
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			dialog.text = "Je comprends, capitaine. Permettez-moi alors de vous donner un bref aperçu de la situation dans notre colonie durant votre absence.";
			link.l1 = "Vraiment? Attendez... Capitaine?";
			link.l1.go = "Himenes_church_21";
		break;
		
		case "Himenes_church_20_2":
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			dialog.text = "Je comprends, capitaine. Permettez-moi alors de vous donner un bref aperçu de la situation dans notre colonie pendant votre absence.";
			link.l1 = "Vraiment ? Attendez... Capitaine ?";
			link.l1.go = "Himenes_church_21";
		break;
		
		case "Himenes_church_21":
			dialog.text = "Je ne voulais pas offenser. C'est juste que Rodgar dit ce mot de manière si délicieuse que je voulais l'essayer aussi. Très... pirate.";
			link.l1 = "Aucun probleme, juste surpris. Alors, que s'est-il passe ici ?";
			link.l1.go = "Himenes_church_22";
		break;
		
		case "Himenes_church_22":
			dialog.text = "Premièrement, nous avons construit l'église. Cela prendra une minute, entrez. Il y a quelque chose à voir. Vous avez fait une grande action, capitaine. Cela ne vous semble peut-être pas ainsi, mais pouvoir communiquer avec Dieu est très, très important pour nous. À partir de ce jour, nous appelons Isla Mona notre hogar.";
			link.l1 = "Foyer, doux foyer? Je vais certainement y jeter un coup d'œil. Ai-je transporté toutes ces chandelles pour rien?";
			link.l1.go = "Himenes_church_23";
		break;
		
		case "Himenes_church_23":
			dialog.text = "Pas pour rien ! Deuxièmement, l'usine a été ruinée - nous avons perdu toute la main-d'œuvre. Vous devrez apporter un nouveau lot d'esclaves. Heureusement, après avoir réévalué l'efficacité du travail, nous avons conclu que dix esclaves suffiront amplement. Donc, moins de tracas pour vous.";
			link.l1 = "D'accord. Autre chose ?";
			link.l1.go = "Himenes_church_24";
		break;
		
		case "Himenes_church_24":
			dialog.text = "Tout est prêt pour la célébration. Eh bien, presque : nous devons nettoyer ici, enterrer les corps de ces pauvres âmes... Alors viens à l'église demain et nous commencerons.";
			link.l1 = "À l'église ? Drôle d'endroit pour commencer la fête. As-tu l'intention de faire ta demande, Rodrigo ?";
			link.l1.go = "Himenes_church_25";
		break;
		
		case "Himenes_church_25":
			dialog.text = "Ha-ha ! Non, capitaine, bien que certaines de nos filles ne diraient pas non. Cela ne nous dérange pas si vous le faites.";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && IsOfficer(characterFromId("Mary")))
			{
				link.l1 = "";
				link.l1.go = "Himenes_church_25_1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1 && IsOfficer(characterFromId("Helena")))
				{
					link.l1 = "";
					link.l1.go = "Himenes_church_25_2";
				}
				else
				{
					link.l1 = "D'accord, nous viendrons à l'église demain. Pour prier, bien sûr.";
					if (CheckAttribute(pchar, "questTemp.IslaMona.Defend.Common") || CheckAttribute(pchar, "questTemp.IslaMona.Defend.Force")) link.l1.go = "Himenes_church_28";
					else link.l1.go = "Himenes_church_26";
				}
			}
		break;
		
		case "Himenes_church_25_1":
			DialogExit();
			sld = characterFromId("Mary");
			sld.dialog.currentnode = "IslaMona";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_25_2":
			DialogExit();
			sld = characterFromId("Helena");
			sld.dialog.currentnode = "IslaMona";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_26":
			dialog.text = "Et une chose de plus, capitaine. Avant la célébration, allez d'abord vous occuper du prisonnier. La décision doit être prise, et je comprends que cela sera désagréable de toute façon.";
			link.l1 = "D'accord. J'y vais tout de suite.";
			link.l1.go = "Himenes_church_27";
		break;
		
		case "Himenes_church_27":
			DialogExit();
			DoQuestReloadToLocation("IslaMona_factoria", "reload", "reload1", "IslaMona_DefFraPrisoner"); /// ОПРЕДЕЛИТЬ ЛОКАТОР
		break;
		
		case "Himenes_church_28":
			DialogExit();
			WaitDate("", 0, 0, 0, 3, 5); //крутим время
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			IslaMona_DefBattleLightClear();
			DoQuestReloadToLocation("IslaMona_town", "quest", "detector1", "");
		break;
		
		case "Himenes_church_29":
			dialog.text = "Tout le monde est ici ! Senor, nous ne savons pas ce que vous vouliez initialement de cet endroit et comment vous le voyez maintenant pour vous-même. Pour nous, c'était d'abord un refuge forcé, et maintenant c'est devenu un véritable foyer. Vos marins, pirates et hérétiques espagnols en fuite vivent ici. Dans n'importe quel autre endroit sur terre, nous nous serions déjà tranchés la gorge. Mais ici, nous sommes amis, travaillons et profitons de la vie. Isla Mona n'est pas le point final sur la carte de ce monde pour aucun d'entre nous, mais peut-être que nous y passerons les années les plus heureuses et les plus fructueuses de nos vies. Et c'est votre mérite, votre terre et votre peuple. Muchas gracias, "+pchar.name+" !";
			link.l1 = "";
			link.l1.go = "Himenes_church_30";
			locCameraFromToPos(-4.11, 1.55, 1.09, true, -4.55, -0.20, 3.08);
		break;
		
		case "Himenes_church_30":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_86";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.0);
		break;
		
		case "Himenes_church_31":
			dialog.text = "D'accord, d'accord. Capitaine, nous avons rassemblé des présents pour vous - une multitude de choses utiles et simplement agréables. Certaines que nous avons apportées avec nous, et d'autres que nous avons fabriquées nous-mêmes. Acceptez ce cadeau avec un coeur pur, et le reste nous vous offrirons par notre dur labeur.";
			link.l1 = "Merci... Je ne m'attendais pas à cela. Si peu de moments lumineux et d'humanité simple dans mon odyssée... Cela compte beaucoup pour moi, crois-moi.";
			link.l1.go = "Himenes_church_32";
			locCameraFromToPos(-4.11, 1.55, 1.09, true, -4.55, -0.20, 3.08);
		break;
		
		case "Himenes_church_32":
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "GunEchin", 10);
			TakeNItems(pchar, "slave_01", 10);
			TakeNItems(pchar, "grenade", 10);
			TakeNItems(pchar, "obereg_7", 1);
			TakeNItems(pchar, "purse3", 1);
			TakeNItems(pchar, "jewelry47", 1);
			TakeNItems(pchar, "jewelry52", 1);
			TakeNItems(pchar, "berserker_potion", 1);
			TakeNItems(pchar, "potion5", 10);
			TakeNItems(pchar, "cannabis7", 1);
			dialog.text = "Et maintenant - retour au travail !";
			link.l1 = "Non, maintenant c'est - à la taverne ! Rodrigo, allons-y !";
			link.l1.go = "Himenes_church_33_1";
			link.l2 = "Oui, savourons encore un peu ce moment merveilleux.";
			link.l2.go = "Himenes_church_33_2";
		break;
		
		case "Himenes_church_33_1":
			DialogExit();
			DoQuestReloadToLocation("IslaMona_Town", "sit", "sit_base2", "IslaMona_ChurchToTavern"); /// ОПРЕДЕЛИТЬ ЛОКАТОР
		break;
		
		case "Himenes_church_33_2":
			DialogExit();
			LAi_SetActorType(pchar);
			ChangeShowIntarface();
			ResetSound();
			SetMusic("music_terrain");
			InterfaceStates.Buttons.Save.enable = false;
			bDisableCharacterMenu = true;
			pchar.GenQuest.FrameLockEsc = true;
			locCameraRotateAroundHero(0.0, 1.5, 0.0, 0.005, 0.0, 1.5, 0.0, 10000);
			Pchar.FuncCameraFly = "";
			DoQuestCheckDelay("IslaMona_ChurchTavernExit", 45.0);
		break;
		
		case "Himenes_74":
			dialog.text = "Ha-ha! Hips!";
			link.l1 = "Au fait, je vois que tu as presque cessé de rire follement pour tout et rien. L'air frais des Caraïbes ?";
			link.l1.go = "Himenes_75";
		break;
		
		case "Himenes_75":
			dialog.text = "Plutôt comme l'influence corruptrice de Rodgar. En le regardant, j'ai appris à tout envoyer au diable.";
			link.l1 = "";
			link.l1.go = "Himenes_76";
		break;
		
		case "Himenes_76":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_90";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_77":
			dialog.text = "Je connais bien des gens respectables de là-bas.";
			link.l1 = "";
			link.l1.go = "Himenes_78";
		break;
		
		case "Himenes_78":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_93";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_79":
			dialog.text = "Non, je préfère continuer à boire du rhum et te lancer des regards noirs.";
			link.l1 = "";
			link.l1.go = "Himenes_80";
		break;
		
		case "Himenes_80":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_96";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_81":
			dialog.text = "Capitaine ! Hip !";
			link.l1 = "Salut à toi aussi, Rodrigo. Une soirée mouvementée, à ce que je vois ?";
			link.l1.go = "Himenes_82";
		break;
		
		case "Himenes_82":
			dialog.text = "Mieux vaut... ne pas demander. Un mois... je ne boirai pas. Oh. J'ai des nouvelles ! Le capitaine... a repris ses esprits.";
			link.l1 = "Le seul Espagnol survivant ?";
			link.l1.go = "Himenes_83";
		break;
		
		case "Himenes_83":
			dialog.text = "Hic ! Aïe ! Oui, ils l'ont mis dans la factorerie, dans une maison sous garde.";
			link.l1 = "D'accord. J'irai le voir. Fais attention à ne pas en faire trop.";
			link.l1.go = "Himenes_84";
		break;
		
		case "Himenes_84":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10); /// ОН ИДЕТ НА ВЫХОД, ПОСТАВИТЬ ПРАВИЛЬНЫЙ ЛОКАТОР
			IslaMona_ChurchSetHispanos();
		break;
		
		case "Himenes_85":
			dialog.text = "J'ai pris un bain et tout est comme neuf ! Nous vivrons et travaillerons. J'essaierai de faire fonctionner la factorie aussi longtemps que possible. Eh bien, et faire des réparations, des travaux de construction mineurs. Peut-être même décider d'avoir des enfants avec la mienne.";
			link.l1 = "Heureux pour vous tous ! Ce fut une aventure très nerveuse, coûteuse... et merveilleuse, et je suis content que cela ait marché pour nous. Bonne chance à tous, et à ceux d'entre nous qui lèvent l'ancre, encore plus de chance !";
			link.l1.go = "Himenes_86";
		break;
		
		case "Himenes_86":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "IslaMona_Final", -1);
			sld = characterFromId("Islamona_carpenter");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
		break;
		
		// солдат в бухте
		case "Capral":
			dialog.text = "Halte ! Caporal "+GetFullName(npchar)+"  Vous avez atterri dans une zone de combat ! Identifiez-vous immédiatement et indiquez la raison de votre présence ici ! ";
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				link.l1 = "Caporal, au repos ! "+GetFullName(pchar)+", capitaine de la Marine française. Je vous ordonne de m'escorter jusqu'à votre officier supérieur. Exécutez l'ordre !";
				link.l1.go = "Capral_1";
			}
			else
			{
				link.l1 = ""+GetFullName(pchar)+", capitaine du navire nommé '"+pchar.ship.name+"'. Arrivé sur cette île entièrement par hasard - pour d'éventuelles réparations et pour refaire le plein d'eau douce.";
				link.l1.go = "Capral_3";
			}
		break;
		
		case "Capral_1":
			if(IsUniformEquip())
			{
				dialog.text = "Oui, monsieur, Capitaine ! Je vous en prie, suivez-moi. Je vous implore, faites attention ! Cette île grouille de bandits.";
				link.l1 = "";
			}
			else
			{
				dialog.text = "Je vous demande pardon, Capitaine. Vous n'êtes pas en uniforme, donc je suis obligé de vérifier votre brevet d'officier.";
				link.l1 = "Tu vois. Satisfait? Maintenant - dépêche-toi d'exécuter l'ordre, caporal!";
			}
			link.l1.go = "Capral_2";
		break;
		
		case "Capral_2":
			DialogExit();
			AddQuestRecord("IslaMona", "16");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "IslaMona_DefReloadFactory", 20.0);
		break;
		
		case "Capral_3":
			dialog.text = "Vous devrez m'accompagner, Capitaine. Notre officier supérieur s'entretiendra avec vous. À partir de ce moment, votre navire est considéré comme réquisitionné temporairement pour les besoins de la Marine française. Informez immédiatement la vigie actuelle et suivez-moi.";
			link.l1 = "Réquisitionner le navire Charle Prince ? Je ne crois pas !";
			link.l1.go = "Capral_5";
			link.l2 = "Il semble que je n'ai pas le choix. Je ferai comme tu dis.";
			link.l2.go = "Capral_4";
		break;
		
		case "Capral_4":
			DialogExit();
			AddQuestRecord("IslaMona", "18");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "IslaMona_DefReloadFactory", 5.0);
		break;
		
		case "Capral_5":
			DialogExit();
			DoQuestFunctionDelay("IslaMona_DefKillCapral", 1.0);
		break;
		
		case "Capral_6":
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				dialog.text = "Monsieur le Capitaine, le chemin vers le camp ennemi est à notre droite. Je vous escorterai.";
				link.l1 = "Calmez-vous, Caporal. Je préfère y aller seul.";
			}
			else
			{
				dialog.text = "Capitaine, le chemin vers le camp ennemi est à notre droite. Vous ne vous perdrez pas.";
				link.l1 = "Merci de votre sollicitude.";
			}
			link.l1.go = "Capral_7";
		break;
		
		case "Capral_7":
			DialogExit();
			chrDisableReloadToLocation = false;
			IslaMona_DefGotoMarch();
			pchar.quest.islamona_def_killslaves.win_condition.l1 = "location";
			pchar.quest.islamona_def_killslaves.win_condition.l1.location = "IslaMona_town";
			pchar.quest.islamona_def_killslaves.function = "IslaMona_DefKillSlaves";
		break;
		
		case "FraOfficer":
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				dialog.text = "Capitaine "+GetFullName(pchar)+" ! Dieu merci ! Permettez-moi de me présenter - Lieutenant "+GetFullName(npchar)+"Un grand admirateur de vous ! Je ne sais pas ce que vous faites sur ce misérable bout de terre, mais vous arrivez juste à temps !\nJe dois dire, Capitaine, que vous êtes devenu très populaire parmi notre corps d'officiers. Bien que beaucoup soient agacés par votre... style de service 'spécial', tout le monde s'accorde à dire que votre brevet rend notre flotte plus forte. Nous sommes actuellement dans une impasse totale, donc l'aide de quelqu'un comme vous sera difficile à surestimer !";
				link.l1 = "Que puis-je faire? Et que se passe-t-il ici?";
				link.l1.go = "FraOfficer_1";
			}
			else
			{
				dialog.text = "Capitaine "+GetFullName(pchar)+". Votre nom a été mentionné plusieurs fois dans les rapports de la flotte. Et toujours d'une manière très douteuse. Cependant, vous avez maintenant une chance d'interrompre cette tendance moins honorable et de servir la mère patrie.";
				link.l1 = "Que puis-je faire? Et que se passe-t-il ici?";
				link.l1.go = "FraOfficer_8";
			}
		break;
		
		case "FraOfficer_1":
			dialog.text = "Nous étions sur le 'Guerrier', une mission de routine - traquer des corsaires espagnols particulièrement audacieux. L'affaire est généralement très simple : l'espion fournit la zone et les informations sur la cible, et vous l'attrapez à l'horizon. Il n'y a rien de spécial à raconter, et tout s'est terminé très mal : les Espagnols nous ont trouvés les premiers et ont attaqué, bien qu'ils fussent eux-mêmes sur une corvette. Si nous avions eu quelque chose de plus sérieux, nous ne serions pas allés par le fond avec nous... mais au moins nous avons réussi à faire sauter toute leur coque. Seule mon escouade a survécu. Les Castillans, cependant, ont aussi eu quelqu'un qui a survécu. Mais pas pour longtemps, haha !";
			if (CheckAttribute(pchar, "questTemp.IslamonaSpaOfficer"))
			{
				link.l1 = "La frégate 'Guerrier'? Le capitaine Shocke est mort?";
				link.l1.go = "FraOfficer_1_1";
			}
			else
			{
				link.l1 = "";
				link.l1.go = "FraOfficer_2";
			}
		break;
		
		case "FraOfficer_1_1":
			dialog.text = "Je ne suis pas surpris que vous ayez demandé à son sujet, Capitaine. J'ai entendu parler de votre implication dans l'interception de l' 'Alcantara'. Un grand exploit, même alors vous avez posé les bases pour votre brevet ! Le Commandeur Shocke n'est pas mort, bien au contraire ! Il a été promu, et à sa demande, envoyé servir en Méditerranée. Nous ne pouvons que l'envier dans une situation comme la nôtre maintenant. Alors, en fait, à propos de notre situation...";
			link.l1 = "";
			link.l1.go = "FraOfficer_2";
		break;
		
		case "FraOfficer_2":
			dialog.text = "Nous avons trouvé un établissement sur l'île - un véritable repaire de bandits pour - écoute bien - pirates et Espagnols. Incroyable ! Tu sais, d'habitude ces salauds ne font que se couper et se pendre entre eux, mais ici - regarde : en plein centre de l'archipel, ils travaillent ensemble comme une famille pour extraire le bois des boucaniers. As-tu vu le quai qu'ils se sont construit ? Les invités ne viennent pas à cette espèce en chaloupes. Notre tâche est extrêmement claire : avec ton aide, nous capturons l'établissement, prenons le bois des boucaniers et les prisonniers, et tu emmènes tout le monde à Capsterburg. Pendant ce temps, les autorités se débrouilleront toutes seules... Et pendant qu'elles se débrouillent, nous nous occuperons du bois des boucaniers et célébrerons comme il se doit avec d'autres officiers de mon escadron à domicile !";
			link.l1 = "Qu'est-ce qui vous a empêché de prendre la colonie par vous-même d'ici là ?";
			link.l1.go = "FraOfficer_3";
		break;
		
		case "FraOfficer_3":
			sld = characterFromId("Islamona_carpenter");
			i = sti(sld.crew.qty);
			if (i >= 50) sTemp = "There are probably many more bandits than us - we saw tents on the shore. And besides tents, they also have a wall, gates, cannon!";
			else sTemp = "There are probably not so many bandits, otherwise they would have kicked us out of here already, but they still have a wall, gates, cannon and plenty of time!";
			dialog.text = "Qu'est-ce qui nous a empêchés ?! Nous n'avons que douze fusiliers et sept marins. Tous fatigués et épuisés. Nous n'avons sauvé que cinq mousquets, avec au mieux une cartouche chacun !"+sTemp+"";
			link.l1 = "Mais as-tu un plan ?";
			link.l1.go = "FraOfficer_4";
		break;
		
		case "FraOfficer_4":
			dialog.text = "Ecoute, nous n'avons pas perdu de temps. Tout d'abord, nous avons pris le contrôle de cette usine, capturant ainsi quelques provisions de nourriture et d'eau, et surtout - un entrepôt plein de bois de boucanier et plus d'une douzaine d'esclaves ! De toute façon, nous n'aurions pas pu garder les esclaves, alors nous avons immédiatement effectué une reconnaissance par le combat, les envoyant attaquer leurs anciens maîtres sous la couverture de nos mousquets. C'est ainsi que nous avons découvert que les bandits ont des armes en stock.";
			link.l1 = "Est-ce que je comprends bien que maintenant vous voulez m'envoyer, moi et mes hommes, pour nous occuper de cette arme à la place des esclaves ?";
			link.l1.go = "FraOfficer_5";
		break;
		
		case "FraOfficer_5":
			dialog.text = "Non, mais tu peux aller chez les bandits pour une parlementaire. Ton arrivée signifie que leur repaire est exposé, et maintenant les soldats du roi ont un navire et des renforts. Eh bien, pendant qu'ils pendent l'oreille et évaluent la profondeur de leur profondeur, tu te rapprocheras le plus possible du canon, lanceras une grenade à main en dessous, et ne te feras pas tuer jusqu'à ce que nos gens et les tiens approchent. Si tu n'es pas sûr de pouvoir t'en occuper, essaie d'envoyer un de tes hommes à ta place.";
			link.l1 = "Laissez-moi d'abord aller vers eux sans bombe et leur offrir de se rendre. Je vais observer, comprendre leur humeur et leurs forces, semer le doute dans leurs âmes. S'ils ne se rendent pas, alors j'irai vers eux à nouveau, mais avec une bombe.";
			if (CheckCharacterItem(pchar, "patent_fra")) link.l1.go = "FraOfficer_6";
			else link.l1.go = "FraOfficer_6_1";
		break;
		
		case "FraOfficer_6":
			GiveItem2Character(pchar, "grenade");
			//Log_Info("Вы получили гранату");
			PlaySound("interface\important_item.wav");
			dialog.text = "... et d'ici là, ils seront déjà habitués à toi, ce sera donc plus facile de mener à bien le sabotage ! Astucieux ! Eh bien, je n'attendais rien d'autre de ta part, Capitaine. Procède quand tu seras prêt. Mais tout de même, tiens... Cela pourrait être utile.";
			link.l1 = "";
			link.l1.go = "FraOfficer_7";
		break;
		
		case "FraOfficer_6_1":
			dialog.text = "... et à ce moment-là, ils seront déjà habitués à toi, donc ce sera plus facile de mener le sabotage. C'est ce que nous ferons. Continuez !";
			link.l1 = "";
			link.l1.go = "FraOfficer_7";
		break;
		
		case "FraOfficer_7":
			DialogExit();
			AddQuestRecord("IslaMona", "19");
			chrDisableReloadToLocation = false;
			pchar.quest.islamona_def_goout.win_condition.l1 = "location";
			pchar.quest.islamona_def_goout.win_condition.l1.location = "IslaMona_Jungle_01";
			pchar.quest.islamona_def_goout.function = "IslaMona_DefCapralTalk";
		break;
		
		case "FraOfficer_8":
			dialog.text = "Il y a eu une longue bataille avec les Espagnols dans cette région. Les deux navires ont coulé, et les survivants ont fini ici. Principalement des Français, mais quelques-uns de nos ennemis ont réussi à survivre aussi. Et vous n'avez pas besoin d'en savoir plus, désolé, Capitaine. Information secrète, vous comprenez.";
			link.l1 = "Compris.";
			link.l1.go = "FraOfficer_9";
		break;
		
		case "FraOfficer_9":
			dialog.text = "Nous avons trouvé une colonie sur l'île - un repaire de bandits assez peuplé pour - écoutez bien - des pirates et des Espagnols. Incroyable ! Vous savez, d'habitude ces salauds ne font que se couper et se pendre entre eux, mais ici - voyez-vous : au cœur même de l'archipel, ils travaillent ensemble comme une famille pour extraire du bois de flibustier. Avez-vous vu le quai qu'ils se sont construit ? Les invités ne viennent pas à cette espèce en chaloupes. Notre tâche est extrêmement claire : avec votre aide, nous capturons la colonie, prenons le bois de flibustier et les prisonniers, et vous emmenez tout le monde à Capsterburg. Pendant ce temps, les autorités s'arrangeront par elles-mêmes... Et pendant qu'elles s'en occupent, je pourrais même être prêt à vous donner l'occasion de prendre du bois précieux pour vos besoins.";
			link.l1 = "Qu'est-ce qui vous a empêché de prendre l'établissement par vous-même d'ici là ?";
			link.l1.go = "FraOfficer_3";
		break;
		
		case "FraOfficer_10":
			dialog.text = "Te voilà ! Quoi de neuf ?";
			link.l1 = "Est-ce une garde d'honneur ?";
			link.l1.go = "FraOfficer_11";
		break;
		
		case "FraOfficer_11":
			dialog.text = "De toute évidence, une décision sera prise sous peu concernant nos actions futures. Je ne voudrais pas chercher mes hommes partout sur l'île pour donner de nouveaux ordres.";
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				link.l1 = "Excellente initiative ! Vous aurez vos ordres. J'ai effectué des reconnaissances : l'ennemi est faible et le canon est à court de munitions. Je vous ordonne d'attaquer immédiatement le repaire des bandits, Lieutenant. Arrêtez de vous tourner les pouces. Juste une autre journée dans la flotte. Exécutez !";
				link.l1.go = "FraOfficer_12";
			}
			else
			{
				link.l1 = "De mon avis, tu aurais pu les prendre juste après la reconnaissance 'esclave' par la force. Leur défense est risible, juste quelques combattants sérieux. Pas besoin de trop réfléchir - on aurait pu boire du vin de trophée en étant assis sur une montagne de bois de fer.";
				link.l1.go = "FraOfficer_14";
			}
		break;
		
		case "FraOfficer_12":
			dialog.text = "Affirmatif, Capitaine !";
			link.l1 = "...";
			link.l1.go = "FraOfficer_13";
		break;
		
		case "FraOfficer_13":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -25);
			AddQuestRecord("IslaMona", "22");
			IslaMona_DefAttackLight();
		break;
		
		case "FraOfficer_14":
			dialog.text = "Et sont-ce là les résultats de votre reconnaissance ? Je comprends qu'il puisse être étrange d'attendre trop d'une personne non militaire, mais j'ai besoin de faits ! Des faits, Capitaine, pas votre opinion !";
			link.l1 = "Tu m'offenses, Lieutenant. Rapport!";
			link.l1.go = "FraOfficer_15";
		break;
		
		case "FraOfficer_15":
			dialog.text = "";
			link.l1 = "En ce moment, il y a un capitaine survivant d'un navire espagnol que tu as coulé avec toi. Un commandant expérimenté qui se rétablira bientôt. Si tu tardes, il se rétablira et organisera la défense selon les règles de la science militaire, et alors nous aurons du fil à retordre. Nous devons nous dépêcher - je le répète, ils sont faibles et démoralisés.";
			link.l1.go = "FraOfficer_15_1";
			link.l2 = "Les renforts arrivent bientôt - pour prendre le bois du boucanier. Je ne pense pas que ce soit un bluff : tu as vu toi-même les quais et un tas de marchandises prêtes à être livrées dans l'entrepôt de l'usine. Nous devons nous dépêcher - je répète, ils sont faibles et démoralisés. Si tu tardes, tu attendras l'arrivée d'un navire pirate.";
			link.l2.go = "FraOfficer_15_2";
			link.l3 = "Presque la moitié des habitants de ce trou sont des femmes. Vous n'avez même pas combattu contre la milice : il n'y a pas eu plus d'une douzaine de combattants contre vous tout ce temps. Ils sont faibles et démoralisés.";
			link.l3.go = "FraOfficer_15_3";
			link.l4 = "The cannon is out of ammunition. I've seen enough guns in my lifetime and can tell when a crew is ready to fire and when it's not. Without their artillery, they're nothing but poor warriors; they are weak and demoralized.";
			link.l4.go = "FraOfficer_15_4";
			link.l5 = "Pensez aux trophées et à la gloire, Lieutenant ! Une victoire en solitaire sur un corsaire espagnol, capturer un repaire de bandits et une source unique de bois de flibustier - tout cela exige de commander votre propre navire ! Je le répète, ils sont faibles et démoralisés, il est temps de les écraser !";
			link.l5.go = "FraOfficer_15_5";
		break;
		
		case "FraOfficer_15_1":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 80)
			{
				notification("Skill Check Passed", SKILL_LEADERSHIP);
				dialog.text = "Merci, Capitaine. C'est une information précieuse, et vous aviez raison, il n'y a pas besoin de s'attarder ici. Mes hommes sont tous ici, nous sommes forts, entraînés et prêts. Tout sera terminé en une demi-heure. Capitaine, veuillez vous préparer à recevoir des personnes, des prisonniers et des cargaisons sur votre navire. Nous ne nous attarderons pas ici longtemps.";
				link.l1 = "Tout est prêt, Lieutenant. Nous n'attendions que vous. À plus tard !";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				notification("Skill Check Failed (80)", SKILL_LEADERSHIP);
				dialog.text = "Merci, Capitaine. Ce sont des informations précieuses. Dans ce cas, dirigez-vous vers le quai et préparez votre équipe d'abordage. Nous prendrons d'assaut le repaire des bandits ensemble et immédiatement. Les meilleurs de mes hommes et des vôtres mèneront l'avant-garde - ce seront eux qui captureront les portes. Nous discuterons du reste après avoir inspecté nos forces ensemble. Ne me décevez pas, ni votre pays, "+GetFullName(pchar)+".";
				link.l1 = "Qu'il en soit ainsi. A plus tard, Lieutenant.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_2":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 60 && sti(pchar.reputation.nobility) > 41)
			{
				notification("Reputation Check Passed", "None");
				notification("Skill Check Passed", SKILL_LEADERSHIP);
				dialog.text = "Merci, Capitaine. Ce sont des informations précieuses, et vous aviez raison, il n'y a pas besoin de s'attarder ici. Mes hommes sont tous là, nous sommes forts, entraînés et prêts. Tout sera terminé en une demi-heure. Capitaine, veuillez vous préparer à recevoir des gens, des prisonniers et de la cargaison sur votre navire. Nous ne nous attarderons pas ici longtemps.";
				link.l1 = "Tout est prêt, Lieutenant. Nous n'attendions que vous. À plus tard !";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(42))+")", "None");
				notification("Skill Check Failed (60)", SKILL_LEADERSHIP);
				dialog.text = "Merci, Capitaine. Ce sont des informations précieuses. Dans ce cas, rendez-vous au quai et préparez votre équipe d'abordage. Nous attaquerons ensemble le repaire des bandits immédiatement. Les meilleurs de mes hommes et des vôtres mèneront l'avant-garde - ce seront eux qui captureront les portes. Nous discuterons du reste après avoir inspecté nos forces ensemble. Ne décevez pas moi et votre pays, "+GetFullName(pchar)+".";
				link.l1 = "...Ainsi soit-il. À plus tard, Lieutenant.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_3":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 70 && sti(pchar.reputation.nobility) > 41)
			{
				notification("Reputation Check Passed", "None");
				notification("Skill Check Passed", SKILL_LEADERSHIP);
				dialog.text = "Merci, Capitaine. Ce sont des informations précieuses, et vous aviez raison, il n'y a pas besoin de retarder ici. Mes hommes sont tous là, nous sommes forts, entraînés et prêts. Tout sera fini en une demi-heure. Capitaine, veuillez vous préparer à recevoir des gens, des prisonniers et du fret sur votre navire. Nous ne nous attarderons pas ici longtemps.";
				link.l1 = "Tout est prêt, Lieutenant. Nous ne faisions qu'attendre votre arrivée. À plus tard !";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(42))+")", "None");
				notification("Skill Check Failed (70)", SKILL_LEADERSHIP);
				dialog.text = "Merci, Capitaine. C'est une information précieuse. Dans ce cas, dirigez-vous vers le quai et préparez votre équipe d'abordage. Nous attaquerons le repaire des bandits ensemble et immédiatement. Les meilleurs de mes hommes et des vôtres mèneront l'avant-garde - ce seront eux qui captureront les portes. Nous discuterons du reste après avoir inspecté nos forces ensemble. Ne me décevez pas, ni votre pays, "+GetFullName(pchar)+".";
				link.l1 = "Qu'il en soit ainsi. À plus tard, Lieutenant.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_4":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 60 && sti(pchar.reputation.nobility) > 41)
			{
				notification("Reputation Check Passed", "None");
				notification("Skill Check Passed", SKILL_LEADERSHIP);
				dialog.text = "Merci, Capitaine. C'est une information précieuse, et vous aviez raison, il n'y a pas besoin de traîner ici. Mes hommes sont tous là, nous sommes forts, entraînés et prêts. Tout sera terminé dans une demi-heure. Capitaine, veuillez vous préparer à recevoir des gens, des prisonniers et de la cargaison sur votre navire. Nous ne nous attarderons pas ici longtemps.";
				link.l1 = "Tout est prêt, Lieutenant. Nous n'attendions que vous. À plus tard !";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(42))+")", "None");
				notification("Skill Check Failed (60)", SKILL_LEADERSHIP);
				dialog.text = "Merci, Capitaine. C'est une information precieuse. Dans ce cas, dirigez-vous vers le quai et preparez votre equipe d'abordage. Nous prendrons d'assaut le nid des bandits ensemble et immediatement. Les meilleurs de mes hommes et les votres meneront l'avant-garde - ce seront eux qui captureront les portes. Nous discuterons du reste apres avoir inspecte nos forces ensemble. Ne decevez pas moi et votre pays, "+GetFullName(pchar)+".";
				link.l1 = "...Qu'il en soit ainsi. À plus tard, Lieutenant.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_5":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 90)
			{
				notification("Skill Check Passed", SKILL_LEADERSHIP);
				dialog.text = "Merci, Capitaine. C'est une information précieuse, et vous aviez raison, il n'est pas nécessaire de traîner ici. Mes hommes sont tous présents, nous sommes forts, entraînés et prêts. Tout sera terminé en une demi-heure. Capitaine, veuillez vous préparer à recevoir des gens, des prisonniers et des marchandises sur votre navire. Nous ne nous attarderons pas ici longtemps.";
				link.l1 = "Tout est prêt, Lieutenant. Nous n'attendions que vous. À plus tard !";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				notification("Skill Check Failed (90)", SKILL_LEADERSHIP);
				dialog.text = "Merci, Capitaine. C'est une information précieuse. Dans ce cas, rendez-vous au quai et préparez votre équipe d'abordage. Nous prendrons d'assaut le nid des bandits ensemble et immédiatement. Les meilleurs de mes hommes et les vôtres mèneront l'avant-garde - ce sont eux qui captureront les portes. Nous discuterons du reste après avoir inspecté nos forces ensemble. Ne me décevez pas, ni votre pays, "+GetFullName(pchar)+".";
				link.l1 = "...Ainsi soit-il. À plus tard, Lieutenant.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_16": // французы атакуют сами
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -10);
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			AddQuestRecord("IslaMona", "24");
			IslaMona_DefAttackLight();
		break;
		
		case "FraOfficer_17": // совместная атака
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -7);
			AddQuestRecord("IslaMona", "23");
			IslaMona_DefAttackCommon();
		break;
		
		case "FraOfficer_18":
			if (CheckCharacterItem(pchar, "patent_fra")) dialog.text = "Et moi, idiot, je t'admirais ! A-ah ! La fierté de la France, Capitaine "+GetFullName(pchar)+"!! Tu n'es pas digne de ton brevet!!!";
			else dialog.text = ""+GetFullName(pchar)+", ordure, traître, et maudit pirate ! J'aurais dû deviner que ce repaire misérable est ton domaine puant ! La France n'oublie ni ne pardonne les hommes comme toi !";
			link.l1 = "";
			link.l1.go = "FraOfficer_19";
		break;
		
		case "FraOfficer_19":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_75";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "FraOfficer_20":
			dialog.text = "Es-tu prêt, Capitaine ? Ton équipage semble digne !";
			link.l1 = "Merci, Lieutenant. Commençons-nous?";
			link.l1.go = "FraOfficer_21";
		break;
		
		case "FraOfficer_21":
			dialog.text = "Oui, allons-y immédiatement !";
			link.l1 = "...";
			link.l1.go = "FraOfficer_22";
		break;
		
		case "FraOfficer_22":
			DialogExit();
			IslaMona_DefAttackCommonRun();
		break;
		
		// обиженный пират
		case "Pirate":
			dialog.text = "Ha ! "+GetFullName(pchar)+"! Quelle rencontre. Hé, attrapez-le ! Ce salaud possède tout ici ! C'est son île !";
			link.l1 = "Quelle journée c'est...";
			link.l1.go = "Pirate_1";
		break;
		
		case "Pirate_1":
			DialogExit();
			IslaMona_DefCheckJungleFight();
		break;
		
		// Алонсо
		case "Alonso":
			dialog.text = "Capitaine, quels sont les ordres ? Il y a un signal pour se tenir prêt et envoyer le groupe d'abordage.";
			link.l1 = "L'ordre est donné. Garçons, suivez-moi, nous devons débarrasser notre maison des invités indésirables. Le prix est à moi, tous les trophées sont à vous !";
			link.l1.go = "Alonso_1";
		break;
		
		case "Alonso_1":
			dialog.text = "Houpla !";
			link.l1 = "À l'abordage !";
			link.l1.go = "Alonso_2";
		break;
		
		case "Alonso_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_CharacterDisableDialog(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			for (i=1; i<=5; i++) 
			{
				sld = characterFromId("IM_our_soldier_"+i);
				LAi_SetActorType(sld);
				LAi_CharacterDisableDialog(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Defend.Common"))
			{
				pchar.quest.islamona_attack_common1.win_condition.l1 = "location";
				pchar.quest.islamona_attack_common1.win_condition.l1.location = "IslaMona_Jungle_01";
				pchar.quest.islamona_attack_common1.function = "IslaMona_DefAttackCommonPrepare";
			}
			else
			{
				LocatorReloadEnterDisable("IslaMona_Jungle_01", "reload3_back", true);
				LocatorReloadEnterDisable("IslaMona_Jungle_01", "reload1_back", true);
				pchar.quest.islamona_attack_force.win_condition.l1 = "location";
				pchar.quest.islamona_attack_force.win_condition.l1.location = "IslaMona_factoria";
				pchar.quest.islamona_attack_force.function = "IslaMona_DefAttackForce";
			}
		break;
		
		// испанский офицер
		case "SpaOfficer":
			dialog.text = "Salutations, señor. Êtes-vous le propriétaire de cette terre? Permettez-moi de me présenter, Grand Francisco de Alba, ancien capitaine de la corvette 'Perro Marino'.";
			link.l1 = "Oui, ceci est ma terre. Je suis "+GetFullName(pchar)+", capitaine du navire '"+pchar.ship.name+"Grand ? Nous n'avons jamais eu d'invités aussi distingués ici auparavant.";
			link.l1.go = "SpaOfficer_1";
		break;
		
		case "SpaOfficer_1":
			dialog.text = "Oh, Monsieur "+GetFullName(pchar)+" ! Ton nom est bien connu. Tu vois, dernièrement, ton nom est apparu si souvent dans les rapports de la Casa de Contratacion que je m'attendais sérieusement à recevoir des ordres pour m'occuper de toi.";
			link.l1 = "Traiter avec moi ?";
			link.l1.go = "SpaOfficer_2";
		break;
		
		case "SpaOfficer_2":
			dialog.text = "Je pense qu'il n'y a pas de raison de faire semblant. Mon boulot est de chercher et détruire les ennemis de l'Espagne et du roi Philippe sur toutes les mers du globe.";
			link.l1 = "C'est une chance que de tels ordres ne soient pas encore arrivés. Vous êtes manifestement un très habile officier naval.";
			link.l1.go = "SpaOfficer_3";
		break;
		
		case "SpaOfficer_3":
			dialog.text = "Le fait que je sois maintenant un prisonnier à moitié mort sur une petite île grouillante de pirates et que mes compatriotes soient en fuite ne fait que confirmer votre conclusion, ha-ha ! C'était une affaire très dangereuse, mais les ordres sont les ordres. Nous avons presque réussi ! C'est profondément regrettable pour mes hommes - je les connaissais tous par leur nom, nous avons servi ensemble pendant de nombreuses années. Mais mon pays devra verser encore plus de sang de ses fils pour maintenir son statut impérial. Notre famille le sait mieux que la plupart.";
			if (CheckAttribute(pchar, "questTemp.IslamonaSpaOfficer"))
			{
				link.l1 = "";
				link.l1.go = "SpaOfficer_4";
			}
			else
			{
				link.l1 = "Revenons à des affaires plus urgentes pour l'instant. Que dois-je faire de vous, Grand?";
				link.l1.go = "SpaOfficer_5";
			}
		break;
		
		case "SpaOfficer_4":
			dialog.text = "Au fait, Monsieur de Mor, le 'Guerrier' - ce petit navire vous était familier, n'est-ce pas ? Votre audacieuse opération à Porto Bello n'est pas passée inaperçue. Audacieuse, voire suicidaire. Vous aviez désespérément besoin d'argent, ai-je raison ? Ha !";
			link.l1 = "Tu en sais beaucoup sur moi, Grand. Mais passons à ton destin.";
			link.l1.go = "SpaOfficer_5";
		break;
		
		case "SpaOfficer_5":
			dialog.text = "Qu'y a-t-il à réfléchir ? Comme dans toute bonne histoire, vous avez trois options : me tuer, me laisser ici, ou me libérer. Si vous me libérez, je vous donne la parole de la famille de Alba que je ne parlerai jamais à quiconque de cet endroit et de votre implication dans mes mésaventures. De plus, je serai votre débiteur, et jusqu'à ce que cette dette soit remboursée, je ne me battrai jamais contre vous.";
			link.l1 = "Je ne peux pas prendre ce risque, Grand.";
			link.l1.go = "SpaOfficer_6";
			link.l2 = "Tu passeras quelque temps ici. Tu vivras et travailleras sur un pied d'égalité avec tes compatriotes.";
			link.l2.go = "SpaOfficer_7";
			link.l3 = "Bienvenue à bord de mon navire, Grand. Je vous débarquerai au phare de Santiago quand le moment sera venu. J'espère que vous tiendrez parole.";
			link.l3.go = "SpaOfficer_8";
		break;
		
		case "SpaOfficer_6":
			dialog.text = "Je comprends, señor. Eh bien, en tout cas, je suis déjà mort dans cette bataille avec mes hommes. C'est une bonne fin.";
			link.l1 = "";
			link.l1.go = "SpaOfficer_6_1";
		break;
		
		case "SpaOfficer_6_1":
			DialogExit();
			DoQuestFunctionDelay("IslaMona_KillSpanish", 1.0);
		break;
		
		case "SpaOfficer_7":
			dialog.text = "J'admets que je n'aime pas être tiède. Mais il n'y a pas de déshonneur à être prisonnier, donc j'accepte votre don de vie et vivrai en paix avec ces gens aimables et apparemment très heureux. Néanmoins, si jamais je quitte cet endroit, je ne vous devrai rien.";
			link.l1 = "";
			link.l1.go = "SpaOfficer_7_1";
		break;
		
		case "SpaOfficer_7_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			AddQuestRecord("IslaMona", "27");
			IslaMona_FinalPrepare();
		break;
		
		case "SpaOfficer_8":
			dialog.text = "Je te donne ma parole et celle de la famille de Alba ! À bientôt sur le navire !";
			link.l1 = "";
			link.l1.go = "SpaOfficer_8_1";
		break;
		
		case "SpaOfficer_8_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("IslaMona", "28");
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			ChangeCharacterComplexReputation(pchar, "nobility", 6);
			pchar.quest.islamona_final_mayak.win_condition.l1 = "location";
			pchar.quest.islamona_final_mayak.win_condition.l1.location = "Mayak9";
			pchar.quest.islamona_final_mayak.function = "IslaMona_FinalMayakSpanish";
			pchar.questTemp.IslaMona.Mayak = "true";
			IslaMona_FinalPrepare();
		break;
		
		case "SpaOfficer_9":
			dialog.text = "Capitaine "+GetFullName(pchar)+"! You saved my life and brought me back to my own. I understand how difficult it was to take such a risk - I would never have dared to do such a thing. I owe you, senor. I give you my word that I will never tell anyone about the circumstances of that ill-fated battle. When you return to the Old World, be sure to find me; you will always be welcome at our family estate in Madrid. For now, take this...";
			link.l1 = "Un morceau de carte ?";
			link.l1.go = "SpaOfficer_10";
		break;
		
		case "SpaOfficer_10":
			AddMapPart();
			dialog.text = "C'est tout ce que j'avais de valeur sur moi. Je n'ai aucun doute que vous trouverez facilement l'autre pièce. Adieu ! Et bonne chance à vous, mon ami.";
			link.l1 = "Adieu, Grand. Souviens-toi de ta parole, et bonne chance à toi !";
			link.l1.go = "SpaOfficer_11";
		break;
		
		case "SpaOfficer_11":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
			pchar.questTemp.IslaMona.Mayak = "done";
			ChangeCharacterNationReputation(pchar, SPAIN, 20);
			AddQuestRecord("IslaMona", "29");
			CloseQuestHeader("IslaMona");
		break;
		
		// Диалоги обитателей Исламоны
		// мужское население
		case "island_man":
			dialog.text = LinkRandPhrase("Salutations ! Comment allez-vous, Capitaine ? Les choses vont bien pour nous.","Travailler pour la communauté est la plus grande joie !","Votre île est merveilleuse, Capitaine, et nous ferons tout pour sa prospérité.");
			link.l1 = LinkRandPhrase("Ravi de l'entendre.","Ravi d'entendre que tout va bien.","J'admire ton enthousiasme, amigo.");
			link.l1.go = "island_man_1";
			if(CheckAttribute(pchar,"questTemp.IslaMona.TownStage"))
			{
				switch(sti(pchar.questTemp.IslaMona.TownStage))
				{
					case 0:
						dialog.text = RandPhraseSimple(RandPhraseSimple("Ne le prenez pas pour de l'impudence, señor, mais vivre ici est impossible.","Tout vaut mieux que de croupir dans les cachots de l'Inquisition..."),RandPhraseSimple("Merci de nous avoir sauvés, Capitaine.","Est-ce que ces... pirates sont vos amis ?"));
						link.l1 = "...";
						link.l1.go = "island_man_1";
					break;
					
					case 1:
						dialog.text = RandPhraseSimple(RandPhraseSimple("Ce n'est pas mal ici ! Juste un peu ennuyeux.","Capitaine, ravi de vous voir. Passez nous voir un de ces jours !"),RandPhraseSimple("Quelqu'un a trouvé des crânes sur la plage et les a apportés à la réunion du matin. C'est toujours comme ça ici ?","Je vais te dire un secret, Senor Himenes profite évidemment de l'air frais et de la sécurité de cet endroit."));
						link.l1 = "...";
						link.l1.go = "island_man_1";
					break;
					
					case 2:
						dialog.text = RandPhraseSimple(RandPhraseSimple("C'est pas mal ici ! Juste un peu ennuyeux.","Capitaine, heureux de vous voir. Passez nous voir un de ces jours !"),RandPhraseSimple("Quelqu'un a trouvé des crânes sur la plage et les a apportés à la réunion du matin. Est-ce toujours comme ça ici?","Je vais te dire un secret, le Seigneur Himenes profite évidemment de l'air frais et de la sécurité de cet endroit."));
						link.l1 = "...";
						link.l1.go = "island_man_1";
					break;
					
					case 3:
						dialog.text = RandPhraseSimple(RandPhraseSimple("Dieu vous bénisse, Capitaine !","Une fois par semaine, nous organisons des spectacles sur la plage et dans la taverne. Passez nous voir un de ces jours."),RandPhraseSimple("Vos marins nous apportent sans cesse toutes sortes de bibelots en échange de nourriture fraîche. Merci d'encourager cela.","C'est incroyable que cet endroit n'ait pas encore été découvert. J'espère que cela restera ainsi."));
						link.l1 = "...";
						link.l1.go = "island_man_1";
					break;
				}
			}
		break;
		
		case "island_man_1":
			DialogExit();
			npchar.dialog.currentnode = "island_man";
		break;
		
		case "island_man_2":
			dialog.text = "Merci, senor. Grâce à vous, nous avons vu le vrai Nouveau Monde. Que Dieu vous bénisse !";
			link.l1 = "";
			link.l1.go = "island_man_3";
			locCameraFromToPos(1.64, 1.58, -5.11, false, 2.66, 0.20, -5.74);
		break;
		
		case "island_man_3":
			DialogExit();
			npchar.dialog.currentnode = "island_man";
			sld = characterFromId("Himenes_companion_12");
			sld.dialog.currentnode = "island_woman_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.0);
		break;
		
		// женское население
		case "island_woman":
			dialog.text = LinkRandPhrase("La securite et la paix - c'est ce que j'aime ici !","Un merveilleux paradis ! Enfin, presque...","Nous sommes heureux de trouver un nouveau foyer ici, après tant de difficultés.");
			link.l1 = LinkRandPhrase("Je suis heureux pour toi et ta communauté.","Oui, j'aime aussi cette petite île.","C'est agréable de savoir que vous êtes satisfait.");
			link.l1.go = "island_woman_1";
			if(CheckAttribute(pchar,"questTemp.IslaMona.TownStage"))
			{
				switch(sti(pchar.questTemp.IslaMona.TownStage))
				{
					case 0:
						dialog.text = LinkRandPhrase("Oh... Bonjour.","Seigneur, qui sont ces... hommes rudes avec des armes ?","Merci de nous avoir sauvés, Capitaine.");
						link.l1 = "...";
						link.l1.go = "island_woman_1";
					break;
					
					case 1:
						dialog.text = LinkRandPhrase("Nos hommes ont fait un excellent travail - les maisons sont superbes. Mais nous avons aussi travaillé dur !","Seigneur Capitaine, ne vous inquiétez pas : les femmes de notre petit clan ne craignent pas les difficultés et les inconvénients temporaires.","Quel air ici ! Et la mer ! On se sent plus proche de Dieu !");
						link.l1 = "D'accord...";
						link.l1.go = "island_woman_1";
					break;
					
					case 2:
						dialog.text = LinkRandPhrase("Nos hommes ont fait un excellent travail - les maisons sont excellentes. Mais nous avons aussi travaillé dur !","Seigneur Capitaine, ne vous inquiétez pas : les femmes de notre petit clan ne craignent ni les difficultés ni les inconforts temporaires.","Quel air ici ! Et la mer ! On se sent plus proche de Dieu !");
						link.l1 = "...";
						link.l1.go = "island_woman_1";
					break;
					
					case 3:
						dialog.text = LinkRandPhrase("Revenez plus souvent, Senor Capitaine. Je suis toujours heureux de vous voir.","Senor Rodgar est un conteur incroyable. Vous pouvez l'écouter parler éternellement !","Hehe. Ils disent que quelqu'un de notre groupe attend déjà un ajout à la famille. La vie continue même sur Isla Mona !");
						link.l1 = "...";
						link.l1.go = "island_woman_1";
					break;
				}
			}
		break;
		
		case "island_woman_1":
			DialogExit();
			npchar.dialog.currentnode = "island_woman";
		break;
		
		case "island_woman_2":
			dialog.text = "Toi... Muchas gracias, senor! Viens plus souvent...";
			link.l1 = "";
			link.l1.go = "island_woman_3";
			locCameraFromToPos(-1.86, 1.18, 4.51, true, -1.49, 0.20, 6.13);
		break;
		
		case "island_woman_3":
			DialogExit();
			npchar.dialog.currentnode = "island_woman";
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.0);
		break;
		
		// пираты Родгара
		case "fort_pirate":
			if(npchar.location == "islamona_factoria")
			{
				dialog.text = dialog.text = RandPhraseSimple(RandPhraseSimple("Tout va bien, Capitaine !","Esclaves sous contrôle, ne t'inquiète pas."),RandPhraseSimple("Vous n'avez pas à vous inquiéter, la mutinerie est exclue.","Merci pour le rhum ! Nous allons nous mettre au travail !"));
			}
			else
			{
				dialog.text = dialog.text = RandPhraseSimple(RandPhraseSimple("Espagnols ? Nous ne nous attendions pas à cela de votre part.","Maintenant, nous devons marcher jusqu'à la plage juste pour dormir en paix !"),RandPhraseSimple("Pourquoi as-tu décidé de tout cela - hein, Cap?","Le patron te faisait confiance à l'époque - et il n'avait pas tort. On te fera de nouveau confiance."));
			}
			link.l1 = "... ";
			link.l1.go = "fort_pirate_1";
		break;
		
		case "fort_pirate_1":
			DialogExit();
			npchar.dialog.currentnode = "fort_pirate";
		break;
		
		// посетители таверны
		case "citizen_tavern":
			dialog.text = LinkRandPhrase("Après un labeur éreintant, ce n'est pas un péché de boire un ou deux verres...","I'm almost done and heading home; the wife must be waiting...","Ah, it's nice to relax in our tavern after work! We're all grateful to you, captain!");
			link.l1 = LinkRandPhrase("Profite de ta boisson, compadre, ha-ha !","Relax, l'ami, mais ne va pas trop loin, ou la femme te grondera, ha-ha !","Du calme, mon gars, la vie ne se résume pas qu'au travail !");
			link.l1.go = "citizen_tavern_1";
		break;
		
		case "citizen_tavern_1":
			DialogExit();
			npchar.dialog.currentnode = "citizen_tavern";
		break;
		
		case "sailor_tavern":
			if (GetCharacterIndex("Mirabella") != -1) sTemp = "Who's that pretty mulatto woman living here?";
				else sTemp = "Captain, nice place you got here!";
			dialog.text = RandPhraseSimple(RandPhraseSimple("Capitaine, bel endroit que vous avez ici!","Imagine que nous nous retrouvions soudainement privés de rhum. Tu irais sûrement en chercher d'autre, n'est-ce pas ?"),RandPhraseSimple("J'ai rêvé de vacances comme celles-ci depuis longtemps. J'aimerais bien un bordel par contre... juste une pensée sauvage, Cap.",sTemp));
			link.l1 = "...";
			link.l1.go = "sailor_tavern_1";
		break;
		
		case "sailor_tavern_1":
			DialogExit();
			npchar.dialog.currentnode = "sailor_tavern";
		break;
		
		case "sailor_town":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Merci pour les vacances, Capitaine.","Bel endroit que vous avez construit ici - vous avez le don de garder les choses en ordre, Capitaine."),RandPhraseSimple("Des vivres fraîches, de la gnôle, un sol solide sous les pieds. C'est un rêve.","Je voudrais rester ici un peu plus longtemps."));
			link.l1 = "... ";
			link.l1.go = "sailor_town_1";
		break;
		
		case "sailor_town_1":
			DialogExit();
			npchar.dialog.currentnode = "sailor_town";
		break;
		
		// рабы
		case "slave":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Je suis si fatigué - je peux à peine me tenir debout.","Plus de force pour vivre comme ça!"),RandPhraseSimple("Ce travail est trop dur pour moi.","Les surveillants n'ont laissé aucune cellule vivante sur ma peau !"));				
			link.l1 = "";
			link.l1.go = "slave_1";
		break;
		
		case "slave_1":
			DialogExit();
			npchar.dialog.currentnode = "slave";
		break;
		
		// энкауниеры в домах
		case "HouseMan":
			dialog.text = LinkRandPhrase("Puis-je vous aider avec quelque chose, capitaine ?","Entrez, prenez un peu de paella locale. Mais, pour l'amour du ciel, ne demandez pas de quoi c'est fait !","Bienvenue, capitaine. Comment vous plaisez-vous ici ?");
			link.l1 = "D'accord, ami.";
			link.l1.go = "HouseMan_1";
		break;
		
		case "HouseMan_1":
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			npchar.dialog.currentnode = "HouseMan";
		break;
		
		case "HouseWoman":
			dialog.text = LinkRandPhrase("Señor, bienvenue !","Bonjour, capitaine. Resterez-vous ?","Es-tu ici pour moi ? S'il te plaît, entre, ignore juste le désordre, senor.");
			link.l1 = "...";
			link.l1.go = "HouseWoman_1";
		break;
		case "HouseWoman_1":
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			npchar.dialog.currentnode = "HouseWoman";
		break;
	}
}