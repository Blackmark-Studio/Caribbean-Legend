// диалоги НПС по квесту НСО
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
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
			dialog.text = "Que cherches-tu ?";
			link.l1 = "Rien.";
			link.l1.go = "exit";
		break;
		
		// инспектор Ноэль Форже
		case "noel":
			dialog.text = "Enchanté de vous rencontrer, capitaine !";
			link.l1 = "Je suis également ravi de vous rencontrer, monsieur Forget. C'est une rare occasion de rencontrer un invité de la métropole ici dans cette contrée sauvage...";
			link.l1.go = "noel_1";
		break;
		
		case "noel_1":
			DialogExit();
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_3";
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "noel_2":
			dialog.text = "Je suis ravi que durant ce voyage je serai sur votre navire, capitaine. Le chevalier de Poincy m'a raconté beaucoup d'histoires intéressantes à votre sujet. Je suis sûr qu'après le dîner dans le mess, nous aurons de nombreux sujets à discuter. Un verre de vin pourrait également s'avérer utile.";
			link.l1 = "Je suis toujours partant pour une conversation agréable, surtout quand j'ai bien mangé. Je serais ravi d'être votre compagnon, Baron. ";
			link.l1.go = "noel_3";
		break;
		
		case "noel_3":
			dialog.text = "Parfait. Quand nous irons dans une colonie, je te demanderai de me guider jusqu'au gouverneur, et je lui expliquerai personnellement ce qu'il faut faire. Tu n'auras qu'à attendre que je termine mes affaires. Marché conclu ?";
			link.l1 = "Oui, monsieur Forget. Bienvenue à bord !";
			link.l1.go = "noel_4";
		break;
		
		case "noel_4":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 12.0);
		break;
		
		case "noel_5":
			dialog.text = "Tortuga est une petite colonie, capitaine. J'estime qu'il me faudra environ trois jours pour inspecter tout ce dont j'ai besoin sur cette île.";
			link.l1 = "Compris, Baron. Donc dans trois jours je viendrai ici pour vous chercher. Bonne chance !";
			link.l1.go = "noel_6";
		break;
		
		case "noel_6":
			DialogExit();
			DoQuestReloadToLocation("Tortuga_town", "reload", "reload3", "Patria_VisiterTortuga");
		break;
		
		case "noel_7":
			dialog.text = "Mon travail sur Tortuga est terminé, il est temps de lever l'ancre.";
			link.l1 = "Compris, Baron. Nous serons en route immédiatement.";
			link.l1.go = "noel_8";
		break;
		
		case "noel_8":
			DialogExit();
			Patria_VisiterTortugaSail();
		break;
		
		case "noel_9":
			dialog.text = "Oui-oui, nous en ferons certainement rapport à Capsterville. La menace qu'une colonie si importante soit conquise... impensable, je m'assurerai personnellement que le Chevalier de Poincy prenne des mesures strictes et impitoyables ! Capitaine, je resterai une semaine sur cette île, il y a beaucoup de plantations ici, cela prendra un certain temps.";
			link.l1 = "Compris, Baron. Je vous attendrai près du palais du gouverneur dans sept jours. Amusez-vous bien et ne vous surmenez pas !";
			link.l1.go = "noel_10";
		break;
		
		case "noel_10":
			DialogExit();
			DoQuestReloadToLocation("PortPax_town", "reload", "reload3", "Patria_VisiterPortPax");
		break;
		
		case "noel_11":
			dialog.text = "Vous voilà, capitaine. Mon travail sur Hispaniola est terminé, il est temps de lever l'ancre.";
			link.l1 = "D'accord, Baron. Nous appareillerons immédiatement.";
			link.l1.go = "noel_12";
		break;
		
		case "noel_12":
			DialogExit();
			Patria_VisiterPortPaxSail();
		break;
		
		case "noel_13":
			dialog.text = "Capitaine, cette île me semble familière. N'est-ce pas Saint-Christophe ?";
			link.l1 = "Oui, baron, précisément. Nous y sommes presque.";
			link.l1.go = "noel_14";
		break;
		
		case "noel_14":
			dialog.text = "Presque arrivés ?! Ne devions-nous pas aussi visiter Saint-Martin ? Cela appartient également aux colonies françaises.";
			link.l1 = "Vous voulez dire Saint-Martin ? C'est une colonie hollandaise, monsieur Forget.";
			link.l1.go = "noel_15";
		break;
		
		case "noel_15":
			dialog.text = "Vraiment ? À Paris, on le considérait comme français. Comment cela ?";
			link.l1 = "Aucune idee, Baron. Depuis que j'ai mis le pied dans l'archipel, Saint-Martin etait une colonie hollandaise. Peut-etre que quelque chose m'echappe. Vous devriez envisager de parler au Chevalier de Poincy a ce sujet.";
			link.l1.go = "noel_16";
		break;
		
		case "noel_16":
			dialog.text = "Très bien, capitaine, ainsi soit-il. Nous sommes presque à Capsterville de toute façon.";
			link.l1 = "...";
			link.l1.go = "noel_17";
		break;
		
		case "noel_17":
			DialogExit();
			Island_SetReloadEnableGlobal("Nevis", true);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			pchar.quest.Patria_visiter_fin.win_condition.l1 = "location";
			pchar.quest.Patria_visiter_fin.win_condition.l1.location = "Charles_Roomtownhall";
			pchar.quest.Patria_visiter_fin.function = "Patria_VisiterFin";
			pchar.questTemp.Patria = "epizode_2_return";
		break;
		
		case "noel_18":
			dialog.text = TimeGreeting()+", capitaine. Je suis heureux de vous voir. J'ai entendu dire que vous avez été promu, veuillez accepter mes félicitations ! À vrai dire, vous êtes vraiment l'un des officiers les plus sensés et doués au service de de Poincy.";
			link.l1 = "Merci, monsieur.";
			link.l1.go = "noel_19";
		break;
		
		case "noel_19":
			dialog.text = "Enfin, il ne reste plus qu'une seule colonie, Saint-Martin. Pour être honnête, je suis lassé de ces voyages. Je serai heureux de terminer cette inspection et de commencer à organiser la prochaine campagne commerciale des Antilles françaises. Sommes-nous prêts à lever l'ancre ?";
			link.l1 = "Oui, Baron. Montez à bord.";
			link.l1.go = "noel_20";
		break;
		
		case "noel_20":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_SanMartinBaron", 5.0);
		break;
		
		case "noel_21":
			dialog.text = "Capitaine, pourriez-vous me dire ce qui vient de se passer ? Cela signifie-t-il une guerre ? Pourquoi diable avons-nous failli être coulés par les Néerlandais ?";
			link.l1 = "Baron, je ne comprends rien moi-même ! Cela doit être un malentendu, sans aucun doute.";
			link.l1.go = "noel_22";
		break;
		
		case "noel_22":
			dialog.text = "Capitaine, je peux parier que ce 'malentendu' a un nom ! Peter Stuyvesant, soi-disant 'locataire' de Saint-Martin et partenaire de notre cher Chevalier de Poincy !";
			link.l1 = "Je n'en ai aucune idée, Baron. Nous ferions mieux de nous dépêcher vers Capsterville et d'en faire rapport au Gouverneur Général.";
			link.l1.go = "noel_23";
		break;
		
		case "noel_23":
			dialog.text = "Sans aucun doute, c'est exactement ce que nous ferons ! Et je demanderai des explications ! Je savais que louer une île aux Hollandais était une grosse erreur ! Quittons cet endroit aussi vite que possible, capitaine, avant que quelqu'un ne décide de nous poursuivre !";
			link.l1 = "Précisément, monsieur ...";
			link.l1.go = "noel_24";
		break;
		
		case "noel_24":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_SanMartinBack", 5.0);
		break;
		
		case "noel_25":
			dialog.text = "Monsieur, permettez-moi d'abord de vous féliciter pour votre promotion ! J'ai soutenu avec empressement la décision de monseigneur de Poincy de vous accorder le rang de Vice-Amiral. Vous méritez ce titre ! Maintenant, je suis récemment rentré de Saint-Martin. Aux entrepôts de Philipsburg, nous avons effectué une révision, toutes les marchandises hollandaises ont été confisquées et appartiennent désormais au trésor de France. Vous, en tant que commandant d'une opération de combat, avez reçu une part des trophées. Je suis d'accord avec le Chevalier que cela est juste. Vos biens ont été transférés à l'entrepôt du magasin de Saint-Christophe, et vous pouvez les récupérer quand vous le souhaitez.";
			link.l1 = "Merci, Baron. Laissez les marchandises rester là pour un moment. À mon retour de Curacao, je les prendrai.";
			link.l1.go = "noel_26";
		break;
		
		case "noel_26":
			dialog.text = "Bonne chance dans votre prochaine campagne, Vice-Amiral ! Je suis convaincu que vous reviendrez victorieux et que vous punirez justement ce scélérat de Stuyvesant.";
			link.l1 = "... ";
			link.l1.go = "noel_27";
		break;
		
		case "noel_27":
			DialogExit();
			pchar.questTemp.Patria = "epizode_11_start";
			AddQuestRecord("Patria", "58");
			pchar.questTemp.Patria.GoodsSM = "true";
		break;
		
		case "noel_28":
			dialog.text = "Qui avons-nous là ! Vice-amiral Charles de Maure ! Heureux de vous voir ! Quelle affaire vous amène à Port-au-Prince ?";
			link.l1 = "Je suis enchanté de vous rencontrer aussi, Baron. Je suis ici par devoir, je devais rendre une visite de courtoisie à monsieur Jeremy Deschamps du Mussaca...";
			link.l1.go = "noel_29";
		break;
		
		case "noel_29":
			dialog.text = "Cette rencontre est en effet très fortuite, car j'attends depuis longtemps de vous rencontrer personnellement. Je veux vous parler, mais pas ici.";
			link.l1 = "Allons à la taverne alors, n'est-ce pas ?";
			link.l1.go = "noel_30";
		break;
		
		case "noel_30":
			DialogExit();
			FreeSitLocator("PortPax_tavern", "sit_base1");
			DoQuestReloadToLocation("PortPax_tavern", "sit", "sit_base1", "Patria_CondotierTavern");
		break;
		
		case "noel_31":
			LAi_SetSitType(pchar);
			dialog.text = "Il n'y a pas d'oreilles indiscrètes ici, nous pouvons parler en toute sécurité...";
			link.l1 = "Je suis tout ouïe, Baron.";
			link.l1.go = "noel_32";
		break;
		
		case "noel_32":
			dialog.text = "Vice-amiral, vous semblez être un homme d'honneur. Un si vaillant officier de marine doit être ainsi...";
			link.l1 = "Hum... Je ne pense pas vous comprendre entièrement, monsieur...";
			link.l1.go = "noel_33";
		break;
		
		case "noel_33":
			dialog.text = "Monsieur de Maure, je voulais vous demander : que pensez-vous de votre suzerain, le Gouverneur Général Philippe de Poincy ?";
			link.l1 = "L'obligation d'un officier n'est pas de penser à son commandant, mais de suivre ses ordres.";
			link.l1.go = "noel_34";
		break;
		
		case "noel_34":
			dialog.text = "Oh, laissez tomber, Vice-Amiral, nous ne sommes pas dans les casernes, et pas dans le hall de de Poincy. Je vais le dire ainsi : ne pensez-vous pas que monsieur de Poincy... abuse de son pouvoir ? Je ne peux toujours pas oublier comment nous avons failli y passer sous les canons du Fort de Saint-Martin. Je suis sûr que la trahison des Hollandais avait une raison.";
			link.l1 = "Ils voulaient conquérir l'île.";
			link.l1.go = "noel_35";
		break;
		
		case "noel_35":
			dialog.text = "Oui, oui, mais pourquoi exactement au même moment où j'ai décidé de l'inspecter ? Pourquoi pas un mois plus tôt ? Ou deux mois plus tard ? Je ne crois pas que ce soit une coïncidence, monseigneur. N'avez-vous pas de soupçons ? Nous avons tous deux risqué nos vies là-bas.";
			link.l1 = "Je risque ma vie chaque jour, monseigneur Forget. Je pense que vous comprenez cela...";
			link.l1.go = "noel_36";
		break;
		
		case "noel_36":
			dialog.text = "Votre courage est au-delà de tout doute. Mais ce n'est pas ce que je voulais dire. Vous voyez... Quand je faisais mon travail sur le Saint-Martin que vous avez libéré, j'ai entendu à plusieurs reprises des chuchotements des habitants au sujet d'une mine dans les profondeurs de l'île. J'ai essayé d'interroger les gens à ce sujet, mais ils faisaient les idiots. Ils avaient peur... Il était évident que je ne semblais pas très digne de confiance, mais cela n'a fait que renforcer mes soupçons : cette mine mystérieuse pourrait-elle être la raison de tout cela, Monsieur de Maure ? Les guerres sont menées à cause de l'or, n'est-ce pas ?";
			link.l1 = "Il y a de nombreuses mines dans l'archipel. La plupart d'entre elles sont épuisées et sont devenues sans valeur. Je connais une grande mine d'or en activité, elle appartient aux Espagnols sur la Terre Ferme. Mais je n'ai jamais entendu parler d'extraction d'or à Saint-Martin.";
			link.l1.go = "noel_37";
		break;
		
		case "noel_37":
			dialog.text = "Vous êtes habile dans l'art de la rhétorique, Vice-amiral ! Je comprends : vous ne me faites pas confiance. Je suis nouveau ici... Monsieur de Maure, mais je suis une personne influente à Paris. Le Ministre des Finances est un de mes proches amis. Je rends visite au Roi régulièrement. Mon autorité est bien plus grande que celle de Philippe de Poincy, formellement, bien sûr, car ici le Gouverneur Général est la personne la plus titrée. Mais à vrai dire, ici, dans les colonies, la loi du plus fort est la seule loi.";
			link.l1 = "Je suis tout à fait d'accord avec toi sur ce point.";
			link.l1.go = "noel_38";
		break;
		
		case "noel_38":
			dialog.text = "Mais pas à Paris. Là, les personnes les plus influentes sont le Roi et le Ministre des Finances... mon ami proche. Monsieur de Maure, vous êtes un brillant militaire, mais je crois que Phillip de Poincy vous utilise à ses propres fins. Vous êtes intelligent, donc vous devez avoir des soupçons. Vous pouvez me faire confiance. Je vous garantis une anonymité complète et le soutien des autorités de Paris. Je le jure sur mon titre.";
			link.l1 = "***RESTEZ LOYAL A POINCY***";
			link.l1.go = "noel_39"; // развилка
			link.l2 = "***SE RANGER DU COTE DU BARON FORGET***";
			link.l2.go = "noel_53";
		break;
		
		case "noel_39":
			dialog.text = "";
			link.l1 = "Je vous comprends, Monsieur Forger. Pour un homme non familier avec les mentalités locales, les actions de de Poincy peuvent en effet sembler étranges. Lorsque je suis arrivé pour la première fois à l'Archipel, j'ai été littéralement choqué par ce qui se passait ici. Je me souviens encore des tout premiers mots qu'on m'a dits : 'Si tu rencontres un navire espagnol non protégé, tu peux essayer de l'aborder.' Trahison, perfidie, tromperie - elles sont présentes ici à chaque pas. Piraterie, pillage, vol...";
			link.l1.go = "noel_40";
		break;
		
		case "noel_40":
			dialog.text = "";
			link.l1 = "Nous sommes en paix avec l'Espagne en Europe. Mais ici, nous sommes des ennemis féroces. Les Hollandais aujourd'hui semblent amicaux et inoffensifs, et demain l'officiel de la Compagnie confisque vos marchandises simplement parce qu'ils ont soudainement annoncé que c'était interdit à l'importation même si vous ne pouviez pas le savoir. L'officier anglais fait ouvertement de la piraterie, coulant les navires de la Compagnie, et la Compagnie engage un assassin qui se déguise en vaisseau fantôme, et terrifie les marchands britanniques...";
			link.l1.go = "noel_41";
		break;
		
		case "noel_41":
			dialog.text = "";
			link.l1 = "Dans cette tanière de loups, nous devons parfois prendre des décisions étranges qui ne sont pas tout à fait évidentes pour quelqu'un qui n'est pas familier avec tout cela. Et ce qui te paraît suspect est en fait la seule action correcte. Il est difficile de s'asseoir sur plusieurs chaises à la fois et de réussir à envoyer des profits à l'État parent. Chevalier de Poincy s'en sort parfaitement, c'est un gestionnaire expérimenté et un politicien visionnaire. Bien sûr, il peut faire des erreurs, mais nous en faisons tous à un moment de notre vie...";
			link.l1.go = "noel_42";
		break;
		
		case "noel_42":
			dialog.text = "";
			link.l1 = "Et tu dois compter avec tout et tout le monde. Avec les ambitions des Espagnols qui croient que tout le Nouveau Monde leur appartient, avec la cupidité des marchands hollandais, avec la froide prudence et la brutalité impitoyable des Anglais. Et même avec les pirates.";
			link.l1.go = "noel_43";
		break;
		
		case "noel_43":
			dialog.text = "Avec des pirates?!";
			link.l1 = "Oui, vous avez bien entendu. Les Hollandais et les Britanniques coopèrent activement avec les pirates... officieusement, bien sûr. La Confrérie de la Côte est une force sérieuse qui peut défier n'importe quelle nation de la région, ils sont en conflit constant avec tous ceux qu'ils rencontrent et personne n'est capable de les arrêter. La seule chose qui les rend légèrement moins dangereux est le fait qu'ils sont dispersés et agissent en leur propre nom. Saviez-vous que l'ancien gouverneur de Tortuga, Levasseur, a en fait créé un état dans l'état, en s'appuyant complètement sur les pirates ?";
			link.l1.go = "noel_44";
		break;
		
		case "noel_44":
			dialog.text = "Je crois avoir entendu quelque chose à ce sujet...";
			link.l1 = "Quelques puissants navires corsaires qui protégeaient l'île étaient constamment amarrés dans le port de Tortuga. Levasseur a trahi la France, devenant une sorte d'autorité locale. Et maintenant, après la destruction du nid de pirates à Tortuga avec leur maître, les pirates sont terriblement en colère contre les Français...";
			link.l1.go = "noel_45";
		break;
		
		case "noel_45":
			dialog.text = "Sans blague !";
			link.l1 = "Oui. Nous devions le faire, sinon Tortuga nous aurait échappé, bien que le résultat obtenu ne soit pas le meilleur. Aucun navire marchand français ne peut se sentir en sécurité dans les Caraïbes maintenant. Les Espagnols, qui n'ont pas non plus d'accords avec les barons pirates, ont au moins des flottes de puissants galions et de navires de guerre capables de repousser les flibustiers. Comme les Néerlandais avec leurs Indiens orientaux et Xebecs. Mais nous ne pouvons pas nous vanter de telle chose, hélas. Et les pirates français pillent souvent les marchands français.";
			link.l1.go = "noel_46";
		break;
		
		case "noel_46":
			dialog.text = "C'est de la folie ! N'y a-t-il aucun moyen d'y mettre fin ?";
			link.l1 = "Beaucoup ont essayé. En fin de compte, au lieu de se battre, ils achètent leur loyauté avec de l'or. Ils délivrent des lettres de marque, je veux dire.";
			link.l1.go = "noel_47";
		break;
		
		case "noel_47":
			dialog.text = "Hmm...";
			link.l1 = "Donc, d'apres mes experiences, etablir une compagnie de commerce francaise ici dans l'Archipel serait une tres mauvaise idee. Comprenez-vous maintenant les difficultes auxquelles vous devrez faire face? Combien de salauds veulent obtenir leur part des revenus ici? Et ils ne comptent pas y renoncer facilement. Et les pirates, ils sont capables de choses impensables, appelez-les fous si vous voulez, mais ils atteignent presque toujours leurs butes infames. Pour proteger les navires marchands, il faudrait entretenir une flotte militaire massive, mais est-ce que ce sera rentable d'un point de vue financier?";
			link.l1.go = "noel_48";
		break;
		
		case "noel_48":
			dialog.text = "Mais les marchands français parviennent à s'en sortir ici d'une manière ou d'une autre ?";
			link.l1 = "Exactement, d'une certaine manière. Surtout maintenant, quand la forteresse pirate de Levasseur sur la Tortue a été prise...";
			link.l1.go = "noel_49";
		break;
		
		case "noel_49":
			dialog.text = "Tes paroles s'alignent avec ce qu'a dit de Poincy.";
			link.l1 = "C'est la vérité. C'est ainsi ici dans l'archipel, ça l'a toujours été.";
			link.l1.go = "noel_50";
		break;
		
		case "noel_50":
			dialog.text = "Vous êtes si prompt à parler. Même moi, je ne connaissais pas beaucoup de ces choses, et vous avez raison : je ne sais toujours pas. Je suppose que mes soupçons envers Poincy étaient infondés. Vous m'avez ouvert les yeux. Je vous remercie, Vice-amiral. Mais le ministre français compte sur la création de la Compagnie. Le Roi a besoin de l'argent...";
			link.l1 = "Je comprends. Mais je vous prie de prendre en considération ce que je viens de dire, si la création des Antilles françaises est inévitable, alors assurez-vous, je vous prie, que nous ayons une flotte militaire robuste pour la protéger.";
			link.l1.go = "noel_51";
		break;
		
		case "noel_51":
			dialog.text = "Votre grâce est vraiment admirable, Vice-amiral ! Quel noble caractère ! Je ne suis pas surpris que vous soyez resté ici si longtemps et que vous ne vous soyez pas empressé de rentrer chez vous. Mais nous nous reverrons : je reviendrai ici dans six mois. La Compagnie Française de Commerce s'élèvera. Et en ce qui concerne les pirates, je pense que vous exagérez un peu. Après tout, nous avons des navires de guerre et des capitaines courageux, tels que vous.";
			link.l1 = "Je suis désolé Baron mais je ne suis qu'un seul homme, et à mes côtés la France n'a qu'un seul navire puissant dans l'archipel 'Eclatant', cela ne suffira pas, nous perdrons beaucoup plus que nous ne gagnerons... Eh bien, peu importe, c'est comme ça, je suppose que nous trouverons quelque chose entre-temps... Quand partirez-vous pour la France ?";
			link.l1.go = "noel_52";
		break;
		
		case "noel_52":
			dialog.text = "Dans deux semaines, je retournerai à Saint-Christophe, et de là, je rentrerai chez moi. Monsieur de Poincy m'a donné un bon navire - une brigantine appelée 'Favory' et un capitaine magnifique. Le navire est rapide et le capitaine est expérimenté, mais, bien sûr, j'étais plus en sécurité avec vous. Je me souviens de nos voyages à travers l'archipel, Vice-Amiral, c'était vraiment une expérience merveilleuse.";
			link.l1 = "Je vous remercie pour vos aimables paroles, Baron. Eh bien, je suppose qu'il est temps pour nous de nous séparer...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Patria_CondotierToPirates");
		break;
		
		case "noel_53":
			dialog.text = "";
			link.l1 = "Ici, tout le monde se sert des autres. Chevalier m'a utilisé dans ses affaires bien avant que je ne devienne officier de la marine.";
			link.l1.go = "noel_54";
		break;
		
		case "noel_54":
			dialog.text = "Et est-ce acceptable ? Qu'en pensez-vous ?";
			link.l1 = "Non. Mais le Chevalier ne m'a laissé aucun choix : soit obéir à ses ordres, soit mon frère resterait derrière les barreaux jusqu'à la fin de ses jours, et le bon nom de ma famille serait ruiné.";
			link.l1.go = "noel_55";
		break;
		
		case "noel_55":
			dialog.text = "Horrible ! C'est du pur terrorisme ! Avait-il une raison pour de telles menaces ?";
			link.l1 = "Mon frère a eu le malheur d'être son homme de confiance. Tout comme je le suis maintenant.";
			link.l1.go = "noel_56";
		break;
		
		case "noel_56":
			dialog.text = "Où est ton frère maintenant ?";
			link.l1 = "J'ai réussi à le libérer mais je l'ai perdu dès le lendemain, il a choisi de ne plus servir sous les ordres de quiconque.";
			link.l1.go = "noel_57";
		break;
		
		case "noel_57":
			dialog.text = "Je savais que Poincy n'était pas celui qu'il prétendait être ! Un loup déguisé en agneau ! Vice-amiral, vous pouvez me faire confiance. Je suis un homme d'honneur. Et je vous sauverai de ce joug de votre 'protecteur' si nous pouvons trouver des preuves tangibles de ses activités criminelles. Savez-vous quelque chose sur cette histoire terne avec Stuyvesant ? Parlez franchement, et ne vous inquiétez pas, vous n'êtes qu'un homme de guerre et vous étiez obligé de suivre vos ordres.";
			link.l1 = "Je sais. Il y a effectivement une mine à Saint-Martin. Seulement, ils n'y extraient pas de l'or, mais du sel. Il est très prisé des Espagnols. Poincy ne pouvait pas commercer directement avec les Espagnols, alors Stuyvesant a fait office d'intermédiaire.";
			link.l1.go = "noel_58";
		break;
		
		case "noel_58":
			dialog.text = "Alors Poincy et Stuyvesant sont partenaires d'affaires?";
			link.l1 = "Il y a longtemps. Après que vous ayez exprimé le désir d'inspecter le Saint-Martin, le Stuyvesant a décidé de mettre Poincy hors-jeu, prenant tous les profits de la mine de sel pour lui-même. Poincy ne pouvait le dire à personne... Mais Stuyvesant a mal calculé, comme nous pouvons le voir.";
			link.l1.go = "noel_59";
		break;
		
		case "noel_59":
			dialog.text = "Penses-tu que la mine continue à fonctionner ?";
			link.l1 = "J'en suis sûr. Il semble que Poincy ait maintenant un nouvel allié commercial. Ce n'est nul autre que le Colonel Doily lui-même.";
			link.l1.go = "noel_60";
		break;
		
		case "noel_60":
			dialog.text = "Peut-on présenter des preuves au ministère ?";
			link.l1 = "Hmm. Lors de l'assaut de la mine, qui, soit dit en passant, a ete mene par des Espagnols, pas par les Hollandais, nous avons capture le proprietaire. Il est toujours sur mon navire. Vous pouvez lui parler. Il y a une chance qu'en echange de sa liberte, il nous revele beaucoup de choses interessantes.";
			link.l1.go = "noel_61";
		break;
		
		case "noel_61":
			dialog.text = "Allons immédiatement à votre navire. Ordonnez que votre prisonnier soit conduit à votre cabine. Je vais m'entretenir avec lui.";
			link.l1 = "D'accord, allons-y.";
			link.l1.go = "exit";
			npchar.greeting = "noel_4";
			AddDialogExitQuestFunction("Patria_CondotierToCabin");
		break;
		
		case "noel_62":
			dialog.text = "Superbe, Vice-Amiral. Je vais m'entretenir avec lui. Restez ici, je vous prie.";
			link.l1 = "Bien sûr...";
			link.l1.go = "noel_63";
		break;
		
		case "noel_63":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "rld", "aloc1", "", -1);
			DoQuestFunctionDelay("Patria_CondotierInCabinTalk", 3.0);
		break;
		
		case "noel_64":
			dialog.text = "J'ai noté toutes les preuves concernant votre captif, et il les a signées. Maintenant, nous devons tenir ce que je lui ai promis, dès qu'une occasion se présente, passez par Carthagène et laissez-le débarquer. Mais vous avez tout entendu vous-même. Quel scélérat, notre Poincy ! Il a loué une île aux Hollandais, mené des activités illégales là-bas et permis aux Espagnols d'y aller et de gérer la mine ! J'ai peur d'imaginer combien d'argent manque au trésor du Roi à cause de son égoïsme !";
			link.l1 = "Ces preuves seront-elles suffisantes pour inculper Poincy ?";
			link.l1.go = "noel_65";
		break;
		
		case "noel_65":
			dialog.text = "Malheureusement, j'ai bien peur que non. Les preuves sont très importantes, mais elles ne suffisent pas. Mais je ne veux pas que tu sois impliqué dans tout cela pour des raisons que nous comprenons tous les deux.";
			link.l1 = "Le Espagnol a accepté de témoigner devant votre commission lorsqu'elle arrivera ici.";
			link.l1.go = "noel_66";
		break;
		
		case "noel_66":
			dialog.text = " Cela n'arrivera pas avant six mois, et qui sait ce qu'il adviendra de ce Espagnol, et serons-nous capables de le retrouver plus tard à Carthagène... Nous avons besoin de preuves encore plus précieuses. A savoir - une preuve que la mine poursuit ses activités secrètes et remplit toujours les poches de notre cher gouverneur général.";
			link.l1 = "Donc tu suggères que nous voyagions à Saint-Martin ?";
			link.l1.go = "noel_67";
		break;
		
		case "noel_67":
			dialog.text = "Oui. Sais-tu comment arriver à la mine ?";
			link.l1 = "Je le fais.";
			link.l1.go = "noel_68";
		break;
		
		case "noel_68":
			dialog.text = "Ensuite, la nuit, toi et moi nous faufilerons là-bas, silencieusement, pour que personne ne voie, et nous vérifierons ce qui s'y passe.";
			link.l1 = "Très bien.";
			link.l1.go = "noel_69";
		break;
		
		case "noel_69":
			dialog.text = "Mais qu'en est-il du Chevalier, hein ? Maintenant je comprends pourquoi il m'a fait allusion avec tant de courage que la création de la Compagnie Française de Commerce sur l'Archipel serait non rentable... Bien sûr, ce serait très non rentable pour lui !";
			link.l1 = "Puisque nous sommes maintenant alliés, Baron, je vais vous dire toute la vérité, Poincy m'a demandé... de vous convaincre de ne pas créer la Compagnie de Commerce ici.";
			link.l1.go = "noel_70";
		break;
		
		case "noel_70":
			dialog.text = "Ah, c'est donc comme ça ! J'espère qu'il ne vous a au moins pas demandé de m'éliminer avec une épée ou un pistolet ?";
			link.l1 = "Non. Il fallait te convaincre d'une autre manière.";
			link.l1.go = "noel_71";
		break;
		
		case "noel_71":
			dialog.text = " Poincy paiera pour cela, mais maintenant nous devons immédiatement naviguer vers Saint-Martin. L'Espagnol sera livré au Continent après. Nous partons, Vice-Amiral !";
			link.l1 = "Il semblera un peu étrange que tu quittes l'île à bord de mon navire, ne crois-tu pas ?";
			link.l1.go = "noel_72";
		break;
		
		case "noel_72":
			dialog.text = "Je ne pense pas. N'étais-tu pas censé me convaincre ? C'est exactement ce que tu as fait, haha ! Oui, avant de naviguer vers l'Europe, je dirai au Chevalier que je suis d'accord avec ses arguments et que la Compagnie de Commerce ne sera pas créée. Laisse-le vivre dans le paisible mensonge pour l'instant... Allons-y !";
			link.l1 = "...";
			link.l1.go = "noel_73";
		break;
		
		case "noel_73":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierToSMartin", 5.0);
		break;
		
		case "noel_74":
			dialog.text = "Montrez-nous le chemin, Vice-Amiral. La nuit nous cachera sous son voile de ténèbres.";
			link.l1 = "Suis-moi...";
			link.l1.go = "noel_75";
		break;
		
		case "noel_75":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.Patria_Condotier_inMine.win_condition.l1 = "location";
			pchar.quest.Patria_Condotier_inMine.win_condition.l1.location = "Location_reserve_03";
			pchar.quest.Patria_Condotier_inMine.function = "Patria_CondotierInMine";
		break;
		
		case "noel_76":
			dialog.text = "(chuchotant) Je l'ai vu ! Je l'ai vu ! L'as-tu vu ? Des Tuniques Rouges ! Ce sont des soldats anglais !";
			link.l1 = "Je t'ai dit - Poincy fait maintenant affaire avec le colonel Doily.";
			link.l1.go = "noel_77";
		break;
		
		case "noel_77":
			dialog.text = "Tu avais raison. J'ai assez vu. Maintenant, sortons d'ici aussi vite que possible avant qu'on ne nous repère !";
			link.l1 = "D'accord...";
			link.l1.go = "noel_78";
		break;
		
		case "noel_78":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocator(pchar, "reload", "reload2_back", "Patria_CondotierToBeach", -1);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		break;
		
		case "noel_79":
			dialog.text = "Tu vois où mènent les 'projets commerciaux' de notre cher Chevalier ! Les Anglais se comportent comme des hôtes sur une île française ! C'est scandaleux !";
			link.l1 = "Nous devons bouger, ou quelqu'un viendra très probablement ici. Nous ne pouvons pas nous permettre d'être reconnus.";
			link.l1.go = "noel_80";
		break;
		
		case "noel_80":
			dialog.text = "Vice-amiral, j'ai réfléchi tout le temps durant notre voyage vers Saint-Martin, et j'ai décidé quelque chose : pouvez-vous m'organiser une rencontre avec Peter Stuyvesant ?";
			link.l1 = "Avec Stuyvesant ? Mais pourquoi ?";
			link.l1.go = "noel_81";
		break;
		
		case "noel_81":
			dialog.text = "Un ancien partenaire d'affaires pourrait avoir des indices sérieux, et certaines preuves sérieuses de l'implication des Chevaliers. Je suis sûr que Stuyvesant n'est pas très content de Poincy et cherchera à se venger, surtout après ces récents événements...";
			link.l1 = "Je le crois bien, Baron. Personnellement, je n'oserai pas me rendre au palais de Stuyvesant. C'est trop risqué pour moi, après tout ce que je leur ai fait...";
			link.l1.go = "noel_82";
		break;
		
		case "noel_82":
			dialog.text = "J'y ai déjà réfléchi. Nous irons à Curaçao, débarquerons dans une baie éloignée de la ville et enverrons notre Espagnol captif de la mine avec une lettre à Stuyvesant. Je ne te mentionnerai pas là-bas, à la place, je lui informerai que je mène une enquête contre Poincy ou quelque chose dans ce genre. Je pense que le Hollandais viendra au rendez-vous.";
			link.l1 = "Hmm. Je ne pense pas que ce soit une bonne idée. Le Stuyvesant n'est pas un imbécile, il prend ce qu'il peut, il pourrait même essayer de t'emprisonner et exiger une énorme rançon, mais si nous lui faisons croire que tout cela est arrivé à cause de Poincy, il pourrait se ranger de notre côté. Eh bien, si tu es si déterminé, essayons.";
			link.l1.go = "noel_83";
		break;
		
		case "noel_83":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Shore40", "reload1_back", false);
			LocatorReloadEnterDisable("Shore40", "boat", false);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_LocationDisableOfficersGen("shore40", false);
			LAi_LocationDisableOfficersGen("Location_reserve_01", false);
			LAi_LocationDisableOfficersGen("Location_reserve_03", false);
			pchar.quest.Patria_CondotierCuracao.win_condition.l1 = "location";
			pchar.quest.Patria_CondotierCuracao.win_condition.l1.location = "shore22";
			pchar.quest.Patria_CondotierCuracao.function = "Patria_CondotierOnCuracao";
			AddQuestRecord("Patria", "81");
		break;
		
		case "noel_84":
			dialog.text = "Monsieur de Maure, veuillez pardonner ma sottise. Vous aviez raison à propos de Stuyvesant. J'aurais dû deviner que seul un gredin encore plus grand aurait pu défier de Poincy !";
			link.l1 = "Hah ! Un million... Poincy voulait un million, Stuyvesant veut un million... On dirait qu'on tourne en rond...";
			link.l1.go = "noel_85";
		break;
		
		case "noel_85":
			dialog.text = "De quoi parlez-vous Vice-Amiral ?";
			link.l1 = "Quand je suis arrivé aux Caraïbes, Poincy voulait que je paie un million comme rançon pour mon frère.";
			link.l1.go = "noel_86";
		break;
		
		case "noel_86":
			dialog.text = "Et tu as payé autant ?";
			link.l1 = "Je l'ai gagné et je l'ai payé. Pas en un mois, bien sûr. Pour dire la vérité, j'étais juste un terre-neuve à l'époque. Pourtant, le Chevalier n'a pas laissé Michel partir.";
			link.l1.go = "noel_87";
		break;
		
		case "noel_87":
			dialog.text = "Et après cela, tu t'es engagé à travailler pour Poincy ? Honnêtement, je ne te comprends pas.";
			link.l1 = "Je me suis engagé pour servir la France et ceux que j'aime, je ne m'incline devant personne d'autre que le roi.";
			link.l1.go = "noel_88";
		break;
		
		case "noel_88":
			dialog.text = "Excusez-moi, Monsieur de Maure. Bien sûr, vous servez la France et le Roi ! Poincy répondra de tout ! Y compris de toute la douleur qu'il vous a causée.";
			link.l1 = "Très bien Baron, je trouverai un million que je peux épargner. Monte à bord... Je résoudrai ce problème.";
			link.l1.go = "noel_89";
		break;
		
		case "noel_89":
			DialogExit();
			//chrDisableReloadToLocation = false; //17-add
			LAi_LocationFightDisable(&Locations[FindLocation("shore22")], false);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "", 10.0);
			pchar.questTemp.Patria = "epizode_12_stivesant";
			AddQuestRecord("Patria", "83");
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Patria_CondotierStivesantTimeOver", 0, 0, 30, false); // таймер на месяц
		break;
		
		case "noel_90":
			dialog.text = "Vous vouliez me voir, Vice-amiral ?";
			link.l1 = "Oui. J'ai eu une réunion avec Stuyvesant. Voici son livre de comptes.";
			link.l1.go = "noel_91";
		break;
		
		case "noel_91":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "Je n'y crois pas ! Hmm, voyons voir... (en lisant)";
			link.l1 = "...";
			link.l1.go = "noel_92";
		break;
		
		case "noel_92":
			LAi_Fade("", "");
			dialog.text = "C'est fait ! Notre cher Chevalier est condamné. Dès que toute cette comptabilité sera vue par le Ministre des Finances... Je n'ose même pas imaginer ce qui lui arrivera. Nous n'aurons même pas à chercher l'Espagnol de Carthagène. Monsieur de Maure, avez-vous vraiment payé des millions pour ce livre ?";
			link.l1 = "Je l'ai fait. Si j'avais essayé autre chose, la France pourrait perdre ses colonies dans les Caraïbes à cause d'une guerre civile, que je pourrais gagner, mais quel genre d'amiral serais-je si je combattais mon propre peuple.";
			link.l1.go = "noel_93";
		break;
		
		case "noel_93":
			dialog.text = "Tu es vraiment digne de ton nom. Je te jure, Vice-amiral, que tu le récupéreras. Je suis sûr que nous trouverons une forte somme d'argent dans les coffres de Poincy et chez ses usuriers. Je te demande seulement d'attendre six mois jusqu'à mon retour d'Europe avec une commission.";
			link.l1 = "Et n'oublie pas d'amener un régiment de soldats bien entraînés et armés. Et un navire comme 'Eclatant'. Je crois aussi que le capitaine de 'Eclatant' se rangera de notre côté quand le moment viendra.";
			link.l1.go = "noel_94";
		break;
		
		case "noel_94":
			dialog.text = "N'en doutez pas, c'est aussi un homme honorable. J'ai compris que les valeurs morales jouent un rôle majeur dans la prise de vos propres décisions. Vous avez fait un excellent travail, en me faisant confiance et en exposant ce criminel d'État. Maintenant, emmenez-moi à Capsterville, où je ferai rapport à Poincy du succès de votre mission - vous avez réussi à me convaincre et j'abandonnerai l'idée de créer la compagnie de commerce. Peut-être que Poincy vous récompensera même pour cela - prenez la récompense avec une conscience claire et ne vous inquiétez de rien, vous le méritez plus que quiconque. Vous ne serez pas impliqué dans cela, et votre nom ne sera pas entaché par les méfaits de votre supérieur, en fait, je dirai toutes les meilleures choses sur vous quand je rencontrerai le roi. Le baron Forget est un homme d'honneur et un homme de parole.";
			link.l1 = "Je suis ravi, baron. Mettons les voiles !";
			link.l1.go = "noel_95";
		break;
		
		case "noel_95":
			DialogExit();
			chrDisableReloadToLocation = false;
			bQuestDisableMapEnter = false;//открыть карту
			Island_SetReloadEnableGlobal("Curacao", true);
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 5.0);
			pchar.questTemp.Patria = "epizode_12_baronwin";
			AddQuestRecord("Patria", "85");
			pchar.quest.Patria_CondotierBaron_win.win_condition.l1 = "location";
			pchar.quest.Patria_CondotierBaron_win.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_CondotierBaron_win.function = "Patria_CondotierBaronWin";
		break;
		
		case "noel_96":
			dialog.text = "Alors, Vice-amiral, nous sommes enfin arrivés. Votre mission est terminée, maintenant c'est à moi de jouer. Allez mener vos propres affaires, défendez les intérêts de la France, comme vous l'avez fait auparavant. Dans environ six mois, cette vile histoire prendra fin. J'enverrai le courrier vous trouver lorsque vous serez nécessaire. Adieu, Monsieur de Maure, j'ai eu beaucoup de chance de rencontrer un homme honorable ici ! Le ministre et le roi entendront parler de vous, je le promets. Et ils n'entendront que le meilleur.";
			link.l1 = "Merci, Baron. Bon voyage !";
			link.l1.go = "noel_97";
		break;
		
		case "noel_97":
			DialogExit();
			AddQuestRecord("Patria", "86");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 15.0);
			SetFunctionTimerCondition("Patria_CondotierPuancieFinal", 0, 0, 1, false); // таймер
		break;
		
		case "noel_98":
			dialog.text = "Heureux de vous voir, Vice-amiral. Je suis ici de nouveau, comme promis. Et avec moi - le premier assistant du Ministre des Finances, le Baron Olivier Bourdin.";
			link.l1 = "Où est le Chevalier de Poincy ?";
			link.l1.go = "noel_99";
		break;
		
		case "noel_99":
			dialog.text = "Où il est censé être, en prison. Il a été arrêté et sera amené en France pour une enquête et un procès. Étant donné sa position, il évitera certainement l'exécution, mais il ne peut pas éviter une lourde amende, une rétrogradation et, probablement, l'emprisonnement.";
			link.l1 = " L'arrestation s'est-elle passée sans heurts ? ";
			link.l1.go = "noel_100";
		break;
		
		case "noel_100":
			dialog.text = "Pas vraiment. Le Chevalier avait ici, dans la résidence, toute une garde de soldats loyaux. Mais nous étions prêts pour une telle escalade à l'avance.";
			link.l1 = "Eh bien, je vous félicite, baron ! Peut-être allez-vous maintenant vous occuper de la Compagnie de commerce française ?";
			link.l1.go = "noel_101";
		break;
		
		case "noel_101":
			dialog.text = "Moi ? Oui. Son excellence monsieur Bourdin - retournera en France avec le Chevalier de Poincy. Et vous, vice-amiral, devriez également vous attendre à quelques changements. Vous avez maintenant un nouveau poste. Son excellence vous en dira plus.";
			link.l1 = "...";
			link.l1.go = "noel_102";
		break;
		
		case "noel_102":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("Finansist");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "noel_103":
			dialog.text = "Monsieur de Maure! Attends une minute!";
			link.l1 = "Oui, Baron. Je vous écoute.";
			link.l1.go = "noel_104";
		break;
		
		case "noel_104":
			dialog.text = "Quant au million que vous avez payé au Stuyvesant... Je n'en ai pas parlé au ministère, afin d'éviter des questions, comme comment un officier français a pu obtenir autant d'argent. Cela aurait pu vous être préjudiciable, car ils vous auraient probablement demandé d'augmenter le trésor du Roi avec le vôtre.";
			link.l1 = "Je comprends, merci.";
			link.l1.go = "noel_105";
		break;
		
		case "noel_105":
			dialog.text = "Tout l'argent trouvé en possession de Poincy à Casterville a été confisqué par le baron Bourdin. Mais, il s'avère que Poincy avait aussi une cachette que les prêteurs anglais cachaient pour lui. Je vais lui parler du retour des investissements, puis je trouverai un moyen de vous dédommager.";
			link.l1 = "J'ai bien peur qu'il ne te soit pas facile de prendre quelque chose des mains des prêteurs sur gages anglais.";
			link.l1.go = "noel_106";
		break;
		
		case "noel_106":
			dialog.text = "Je suis d'accord. Mais nous allons y travailler, et je vous tiendrai au courant des résultats.";
			link.l1 = "Comme vous voulez.";
			link.l1.go = "noel_107";
		break;
		
		case "noel_107":
			dialog.text = "Vice-amiral, vous n'avez pas l'air en grande forme, ou est-ce juste moi ? Vous venez tout juste de recevoir le plus haut poste dans les colonies !";
			link.l1 = "Non-non, pas du tout... C'est juste que tout est arrivé si   inopinément, et je suis un peu perdu.";
			link.l1.go = "noel_108";
		break;
		
		case "noel_108":
			dialog.text = "Ne t'inquiète pas. Tu t'habitueras à ta nouvelle position. Et puis, tu as été plutôt efficace en tant que gouverneur de Saint-Martin pendant six mois, donc ce ne sera rien de nouveau pour toi.";
			link.l1 = "Ah, je suis sûr que je m'y habituerai. J'ai vécu pire pendant mon séjour ici dans les Caraïbes. Je suppose que je m'en sortirai aussi cette fois.";
			link.l1.go = "noel_109";
		break;
		
		case "noel_109":
			// belamour legendary edition -->
			dialog.text = "Eh bien, soit. De plus, j'ai une autre surprise pour vous. Je suis sûr que vous allez l'apprécier. Mais d'abord, je vous demande de retourner à la résidence. Je pense que quelqu'un nous y attend.";
			link.l1 = "Vous m'avez intrigué, Monsieur Forget. Eh bien, retournons-y.";
			link.l1.go = "noel_110";
		break;
		
		case "noel_110":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "ToEcliatonAward", -1);
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, npchar, "", -1);
		break;
		
		case "noel_111":
			dialog.text = "C'est bien, Marquis. Un vrai capitaine doit toujours prendre soin de son navire en premier, n'est-ce pas ? Charles, te souviens-tu du Marquis Hubert Dassier, capitaine du vaisseau de guerre 'Eclatant' ?";
			link.l1 = "Bien sûr que je me souviens ! Sans lui, je ne serais pas en vie aujourd'hui. La plus forte amitié entre officiers de marine naît des batailles menées côte à côte. Et Monsieur Dassier s'est révélé être un capitaine incroyablement expérimenté.";
			link.l1.go = "noel_112";
		break;
		
		case "noel_112":
			DialogExit();
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_17";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "noel_113":
			dialog.text = "Vice-amiral, j'ai l'honneur de vous informer de ce qui suit. En plus de votre nomination en tant que gouverneur général par intérim des colonies françaises de l'archipel, j'ai également soulevé la question de votre navire amiral.";
			link.l1 = "Navire amiral ?";
			link.l1.go = "noel_114";
		break;
		
		case "noel_114":
			dialog.text = "Exactement. Autant que je sache, lorsque vous êtes entré au service de la France, on vous a donné la frégate légère 'Gryffondor' à votre disposition. C'est un navire merveilleux sans aucun doute, mais ce n'est toujours qu'un navire pour un officier, et non pour un vice-amiral et maintenant, un gouverneur général. Vous êtes le visage de la France ici. Et votre navire amiral devrait être approprié. Nous avons donc décidé que le navire qui a traversé ses premières batailles ici dans les Caraïbes soit ajouté à votre escadron...";
			link.l1 = "Monsieur Forget, essayez-vous de dire...";
			link.l1.go = "noel_115";
		break;
		
		case "noel_115":
			dialog.text = "Désormais, la fierté de la Marine française, le navire de guerre de 66 canons 'Éclatant', est à votre disposition ! Cette décision est approuvée par le roi !";
			link.l1 = "Mais Baron, je ne peux pas simplement prendre...";
			link.l1.go = "noel_116";
		break;
		
		case "noel_116":
			dialog.text = "Tu peux, Charles. Cela ne se discute pas. En France, l'‘Eclatant’ a été un peu modifié spécialement pour toi, car, comme il s'est avéré, il n'y a pas de si grandes batailles navales dans les Caraïbes qu'en Europe, et donc les exigences pour les navires individuels sont plus élevées. Ici, tout est décidé par les caractéristiques du vaisseau et l'expérience de son capitaine. L'‘Eclatant’ a eu sa coque renforcée, son port en lourd et la taille de son équipage augmentés, le gréement légèrement rééquipé pour lui permettre de prendre des parcours plus serrés, et aussi tous les canons ont été complètement remplacés par des calibres quarante-deux, ce sont les plus puissants canons que nous ayons.";
			link.l1 = "Oui, maintenant ce navire est tout simplement le maître des mers... Mais Monsieur Forget, car le capitaine de ce navire est le Marquis Hubert Dassier. Je ne peux pas le lui prendre...";
			link.l1.go = "noel_117";
		break;
		
		case "noel_117":
			dialog.text = "C'est juste que je ne vous ai pas encore dit que le Marquis lui-même a exprimé un fort désir de servir sous votre commandement... Monsieur Dassier ?";
			link.l1 = "... ";
			link.l1.go = "noel_118";
		break;
		
		case "noel_118":
			DialogExit();
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_19";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "noel_119":
			dialog.text = "Oui, Monsieur Dassier, je crois que nous ne vous retiendrons pas plus longtemps.";
			link.l1 = "...";
			link.l1.go = "noel_120";
		break;
		
		case "noel_120":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload1");
			sld = characterFromId("Ecliaton_Cap");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "reload", "reload1", "EcliatonAwardNoelTalk", -1);
		break;
		
		case "noel_121":
			dialog.text = "Entre nous, Charles, je te conseillerais vivement de garder le Marquis à ton service. Je t'assure, tu ne trouveras pas un capitaine aussi expérimenté.";
			link.l1 = "Croyez-moi, baron, j'ai eu l'honneur de voir cela personnellement lors des combats contre l'Espagne et la Hollande. Monsieur Dassier est en effet un excellent officier de combat, et aussi mon ami.";
			link.l1.go = "noel_122";
		break;
		
		case "noel_122":
			dialog.text = "Eh bien, permettez-moi maintenant de prendre congé, Votre Grâce, Gouverneur-Général ! Les affaires ne peuvent attendre : la création d'une compagnie de commerce n'en est qu'à son premier jour. À bientôt !";
			link.l1 = "Bonne chance, Monsieur Forget. Et bonne chance avec vos entreprises commerciales !";
			link.l1.go = "noel_123";
		break;
		
		case "noel_123":
			DialogExit();
			// ставим Эклятон после апгрейда в Европе
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_24";
			sld.DeckDialogNode = "ecliaton_cap_24";
			sld.Ship.Type = GenerateShipExt(SHIP_ECLIATON, true, sld);
			SetBaseShipData(sld);
			sld.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS42;
			UpgradeShipFull(sld);
			/* UpgradeShipParameter(sld, "SpeedRate");
			UpgradeShipParameter(sld, "TurnRate");
			UpgradeShipParameter(sld, "WindAgainstSpeed");
			UpgradeShipParameter(sld, "HP");
			UpgradeShipParameter(sld, "MaxCrew");
			sld.ship.HP = 11880; */
			sld.Ship.name = "Ecliaton";
			SetCrewQuantityFull(sld);
			AddCrewMorale(sld, 100);
			ChangeCrewExp(sld, "Sailors", 100);
			ChangeCrewExp(sld, "Cannoners", 100);
			ChangeCrewExp(sld, "Soldiers", 100);
			SetCharacterGoods(sld, GOOD_BALLS, 6000);
			SetCharacterGoods(sld, GOOD_GRAPES, 2000);
			SetCharacterGoods(sld, GOOD_KNIPPELS, 2000);
			SetCharacterGoods(sld, GOOD_BOMBS, 5000);
			SetCharacterGoods(sld, GOOD_FOOD, 4000);
			SetCharacterGoods(sld, GOOD_POWDER, 12000);
			SetCharacterGoods(sld, GOOD_WEAPON, 900);
			SetCharacterGoods(sld, GOOD_MEDICAMENT, 900);
			SetCharacterGoods(sld, GOOD_RUM, 200);
			SetCharacterGoods(sld, GOOD_PLANKS, 100);
			SetCharacterGoods(sld, GOOD_SAILCLOTH, 100);
			Group_AddCharacter("Ecliaton_group", "Ecliaton_Cap");
			Group_SetGroupCommander("Ecliaton_group", "Ecliaton_Cap");
			Group_SetAddress("Ecliaton_group", "Nevis", "quest_ships", "quest_ship_1");
			Group_SetTaskNone("Ecliaton_group");
			Group_LockTask("Ecliaton_group");
			
			bDisableFastReload = false;//открыть переход
			bQuestDisableMapEnter = false;//открыть карту
			AddQuestRecord("Patria", "90");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			pchar.questTemp.Patria = "end"; // конец линейки
			pchar.questTemp.Patria.GenGovernor = "true"; // Шарль генерал-губернатор
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			DoQuestReloadToLocation("Charles_Town", "reload", "reload3", "OpenTheDoors");
		break;
		// <-- legendary edition
		
		case "noel_final":
			dialog.text = "Permettez-moi d'exprimer ma plus sincère reconnaissance envers vous, vice-amiral ! Vous m'avez sauvé la vie en me libérant de ces maudits pirates. Je vous remercie, ainsi que Philippe de Poincy. Je dois admettre que je me suis totalement trompé dans mon jugement à son égard, et je vous prie de me pardonner pour cela. Vous et le Chevalier aviez raison : la Compagnie française de commerce aura beaucoup de problèmes ici, et il semble que nous ne ferons que perdre de l'argent ici. Seules des personnes expérimentées, comme Poincy, et des soldats aussi courageux que vous, peuvent résister à ces loups qui vivent sur chaque île ici. Je dois me rendre au palais, et après cela, je partirai pour l'Europe dès que possible, et j'oublierai ce cauchemar.";
			link.l1 = "Je suis heureux que tout se soit bien terminé, Baron. Adieu !";
			link.l1.go = "noel_final_1";
		break;
		
		case "noel_final_1":
			DialogExit();
			AddQuestRecord("Patria", "76");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 15.0);
			SetFunctionTimerCondition("Patria_CondotierPuancieFinal", 0, 0, 1, false); // таймер
		break;
		
		// капитан Эклятона
		case "ecliaton_cap":
			dialog.text = TimeGreeting()+", monsieur. Qu'est-ce qui vous amène sur le pont de l' 'Éclatant' ?";
			link.l1 = TimeGreeting()+", monsieur. Permettez-moi de me présenter - Capitaine Charles de Maure, je viens du Gouverneur Général des colonies françaises dans l'Archipel, Chevalier de Poincy. J'ai reçu l'ordre de prendre votre navire dans mon escadre et sous mon commandement. Voici la lettre...";
			// belamour legendary edition фикс проверки мундира с мушкетом
			if(IsUniformEquip()) link.l1.go = "ecliaton_cap_1";
			else link.l1.go = "ecliaton_cap_no";
		break;
		
		case "ecliaton_cap_no":
			dialog.text = "C'est une sorte d'erreur, monsieur. Vous vous trouvez sur un vaisseau de ligne de la marine française, et je n'écoute que les ordres émis par ceux qui sont au service de la marine royale. Et vous ne semblez avoir aucun signe d'appartenance à cette flotte. Peut-être confondez-vous notre navire avec un autre.";
			link.l1 = "Mais...";
			link.l1.go = "ecliaton_cap_no_1";
		break;
		
		case "ecliaton_cap_no_1":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_no_2";
		break;
		
		case "ecliaton_cap_no_2":
			if(IsUniformEquip())
			{
				dialog.text = "Tiens, je ne t'avais même pas reconnu dans cet uniforme, Capitaine. Eh bien, laisse-moi voir ta lettre, je souhaite en examiner le contenu.";
				link.l1 = "Ici.";
				link.l1.go = "ecliaton_cap_1";
			}
			else
			{
				dialog.text = "Nous avons déjà tout discuté, monseigneur...";
				link.l1 = "Hmm...";
				link.l1.go = "ecliaton_cap_no_1";
			}
		break;
		
		case "ecliaton_cap_1":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "Eh bien, voyons voir... (lit) Intéressant. Donc, moi et mon navire devons être sous votre commandement, Capitaine de Maure ?";
			link.l1 = "C'est l'ordre du Gouverneur Général.";
			link.l1.go = "ecliaton_cap_2";
		break;
		
		case "ecliaton_cap_2":
			dialog.text = "Oui-oui, les ordres ne se discutent pas. Très bien. Permettez-moi de me présenter : je suis le Marquis Hubert Dassier, Capitaine du vaisseau de ligne de 66 canons de la marine française nommé 'Eclatant', avec cet équipage bien entraîné, et je jure sur mon honneur, c'est l'un des meilleurs navires que la France ait jamais eus.";
			link.l1 = "Ravi de l'entendre, car la tâche que nous a assignée le Gouverneur Général nécessitera une bonne connaissance de la navigation et de l'artillerie.";
			link.l1.go = "ecliaton_cap_3";
		break;
		
		case "ecliaton_cap_3":
			dialog.text = "Me diras-tu les détails de cette opération à venir ?";
			link.l1 = "Bien sûr. Nous nous dirigerons vers l'île espagnole de Trinidad, située à environ une semaine de voyage au sud-est d'ici. Nous attaquerons brusquement le fort qui garde la colonie de San Jose et le mettrons à sac. Ensuite, nous discuterons avec les Espagnols de notre compensation pour la récente attaque sur l'établissement français de Saint-Pierre.";
			link.l1.go = "ecliaton_cap_4";
		break;
		
		case "ecliaton_cap_4":
			dialog.text = "Je vois. Quand partirons-nous ?";
			link.l1 = "Le plus tôt possible. Nous devons achever cette tâche en un mois, donc nous avons largement assez de temps.";
			if (GetCompanionQuantity(pchar) > 4) link.l1.go = "ecliaton_cap_5_1";
			else link.l1.go = "ecliaton_cap_5";
		break;
		
		case "ecliaton_cap_5":
			dialog.text = "D'accord, Capitaine de Maure. Nous partirons à votre commandement.";
			link.l1 = "";
			link.l1.go = "ecliaton_cap_6";
		break;
		
		case "ecliaton_cap_6":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
			Patria_AddEcliaton();
		break;
		
		case "ecliaton_cap_wait":
			dialog.text = "Avez-vous des ordres, ou peut-être des questions, Capitaine de Maure ?";
			link.l1 = "Pas encore...";
			link.l1.go = "ecliaton_cap_wait_1";
		break;
		
		case "ecliaton_cap_wait_1":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
		break;
		
		case "ecliaton_cap_5_1":
			dialog.text = "Mais, Capitaine de Maure, d'abord vous devez réduire votre escadron - mon navire ne peut pas se joindre à vous, sinon ce sera un escadron trop grand.";
			link.l1 = "Hum. Tu as raison. Je laisserai un navire ici dans le port.";
			link.l1.go = "ecliaton_cap_5_2";
		break;
		
		case "ecliaton_cap_5_2":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_5_3";
		break;
		
		case "ecliaton_cap_5_3":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "N'avez-vous pas encore réduit votre escadre, monsieur ?";
				link.l1 = "Oui-oui, je me souviens, je travaille dessus.";
				link.l1.go = "ecliaton_cap_5_2";
			}
			else
			{
				dialog.text = "Alors, l'‘Eclatant’ est prêt à rejoindre votre escadron, monsieur.";
				link.l1 = "Alors j'irai à mon navire, et tu devrais te préparer à entrer en mer.";
				link.l1.go = "ecliaton_cap_5";
			}
		break;
		
		case "ecliaton_cap_7":
			dialog.text = "Salutations, Commodore. Avons-nous une autre bataille devant nous?";
			link.l1 = "En effet, nous le faisons. Une fois de plus, nous unirons nos forces. Nous allons prendre d'assaut Philipsburg. Le gouverneur général nous a chargés de chasser les Hollandais de Saint-Martin.";
			link.l1.go = "ecliaton_cap_9";
			link.l2 = "Nous le ferons Capitaine, mais un peu plus tard. Je vous dirai quand. L' 'Eclatant' doit être prêt à prendre la mer à tout moment.";
			link.l2.go = "ecliaton_cap_8";
		break;
		
		case "ecliaton_cap_8":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_7";
			npchar.DeckDialogNode = "ecliaton_cap_7";
		break;
		
		case "ecliaton_cap_9":
			dialog.text = "Tout est clair. Ce sera une mission ardue, monseigneur. D'après ce que j'ai entendu, le fort de Philipsburg a beaucoup de canons.";
			link.l1 = "Je suis sûr de cela mon ami, mais nous nous débrouillerons. Prépare-toi à prendre la mer, nous partons bientôt.";
			link.l1.go = "ecliaton_cap_10";
		break;
		
		case "ecliaton_cap_10":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
			Patria_BastionAddEcliaton();
		break;
		
		case "ecliaton_cap_11":
			dialog.text = "Heureux de te voir sur le pont de l''Eclatant', vice-amiral ! Quelles sont vos ordres ?";
			link.l1 = "Préparez l'Éclatant pour le départ. D'abord, nous voguerons vers la côte de la Jamaïque, et ensuite, avec l'escadre du colonel D'Oyley, nous attaquerons Curaçao.";
			link.l1.go = "ecliaton_cap_13";
			link.l2 = "Il y aura des ordres, Capitaine, mais plus tard. Je vous dirai quand. L''Eclatant' doit être prêt à prendre la mer à tout moment.";
			link.l2.go = "ecliaton_cap_12";
		break;
		
		case "ecliaton_cap_12":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_11";
			npchar.DeckDialogNode = "ecliaton_cap_11";
		break;
		
		case "ecliaton_cap_13":
			dialog.text = "L''Eclatant' et son équipage sont prêts, Vice-amiral !";
			link.l1 = "Excellent. Alors nous partons immédiatement.";
			link.l1.go = "ecliaton_cap_14";
		break;
		
		case "ecliaton_cap_14":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
			Patria_CuracaoAddEcliaton();
		break;
		
		// belamour legendary edition -->
		case "ecliaton_cap_15":
			dialog.text = "Excusez-moi messieurs, je ne pouvais pas vous rejoindre plus tôt car j'étais occupé à donner des ordres sur le navire. Je pensais déjà être assez en retard, car je ne vous ai pas trouvés à la résidence, et donc j'allais retourner au navire...";
			link.l1 = "...";
			link.l1.go = "ecliaton_cap_16";
		break;
		
		case "ecliaton_cap_16":
			DialogExit();
			Lai_SetPlayerType(pchar);
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_111";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "ecliaton_cap_17":
			dialog.text = "C'était un honneur pour moi de combattre à vos côtés, Monsieur de Maure ! Je dois dire que je rencontre rarement des officiers aussi compétents et habiles que vous. Je suis sûr que je n'aurais pas pu moi-même m'occuper du fort de cette colonie espagnole à Trinidad aussi rapidement !";
			link.l1 = "Vous vous sous-estimez, Monsieur Dassier. Nous l'avons géré ensemble.";
			link.l1.go = "ecliaton_cap_18";
		break;
		
		case "ecliaton_cap_18":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_113";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "ecliaton_cap_19":
			dialog.text = "C'est exact. Bien que je sois marquis, je suis toujours marin. Pour moi, l'archipel caribéen est nouveau, inexploré et plein de nouvelles aventures. La dernière fois que je suis venu ici, ce n'était que pour quelques mois, mais quand je suis retourné en Europe, cet endroit m'a manqué. J'aimerais servir notre patrie ici. Et vous êtes un capitaine très talentueux et expérimenté, vous avez réussi à gagner mon respect sincère et mon amitié. Je serais honoré de servir sous votre commandement, Vice-Amiral !";
			link.l1 = "Eh bien, je ne peux pas et en plus ! - Je ne veux pas vous refuser, Monsieur Dassier !";
			link.l1.go = "ecliaton_cap_20";
		break;
		
		case "ecliaton_cap_20":
			dialog.text = "Je comprends également que l'Eclatant est maintenant votre vaisseau amiral, donc je comprendrai parfaitement si vous décidez d'en prendre personnellement le commandement. Dans ce cas, vous pouvez me laisser en tant qu'officier, me donner un autre navire, ou simplement me relever de mes fonctions - Monsieur Forget m'a gentiment promis qu'alors il me trouverait un poste digne dans la flotte de la Compagnie des Indes occidentales françaises.";
			link.l1 = "Je puis vous assurer, mon ami, que nous n'en arriverons point là. Vous êtes l'un des meilleurs capitaines que j’aie jamais rencontrés, et avec vous à mes côtés, nous serons invincibles.";
			link.l1.go = "ecliaton_cap_21";
		break;
		
		case "ecliaton_cap_21":
			dialog.text = "Je vous remercie pour une évaluation si flatteuse de mes capacités. Et une chose de plus, Vice-amiral. Je ne connais pas la taille de votre escadre en ce moment, donc juste au cas où, je vous attendrai sur la passerelle du capitaine de l'Éclatant au quai de Capsterville. Dès que vous déciderez de prendre le navire sous votre commandement - faites-le moi savoir.";
			link.l1 = "Très bien, Monsieur Dassier.";
			link.l1.go = "ecliaton_cap_22";
		break;
		
		case "ecliaton_cap_22":
			dialog.text = "Alors je demande la permission de me retirer. Vice-amiral, Baron...";
			link.l1 = "À bientôt, Monsieur Dassier.";
			link.l1.go = "ecliaton_cap_23";
		break;
		
		case "ecliaton_cap_23":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_119";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
	
		case "ecliaton_cap_24":
			dialog.text = "Vice-amiral, bienvenue à bord. Souhaitez-vous prendre l'Éclatant sous votre commandement ?";
			if (GetCompanionQuantity(pchar) > 4)
			{
				
				link.l1 = "Pas encore, Marquis. Attendez les ordres.";
				link.l1.go = "ecliaton_cap_24_1";
			}
			else
			{
				link.l1 = "Oui, Marquis, je vous demande de rejoindre mon escadron. Ce beau navire sera un symbole de la grandeur et de la puissance de la France dans les Caraïbes !";
				link.l1.go = "ecliaton_cap_25";
			}
		break;
		
		case "ecliaton_cap_24_1":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_24";
			npchar.DeckDialogNode = "ecliaton_cap_24";
		break;
		
		case "ecliaton_cap_25":
			dialog.text = "Je ne pourrais être plus d'accord, votre Excellence !";
			link.l1 = " ... Maintenant, voyons de quoi nous sommes vraiment capables !";
			link.l1.go = "ecliaton_cap_26";
		break;
		
		case "ecliaton_cap_26":
			DialogExit();
			DeleteAttribute(npchar, "ShipHideImmortal");
			SetCharacterRemovable(npchar, true);
			npchar.CompanionEnemyEnable = true; 
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			npchar.Dialog.CurrentNode = "hired";
			npchar.DeckDialogNode = "hired";
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.Payment = true;
			npchar.loyality = MAX_LOYALITY;
			npchar.OfficerWantToGo.DontGo = true;
			
			// удаление группы Эклятона, иначе клон-призрак
			pchar.quest.Patria_EcliatonDelGroup.win_condition.l1 = "ExitFromSea";
			pchar.quest.Patria_EcliatonDelGroup.function = "Patria_EcliatonDelGroup";
		break;
		// <-- legendary edition
		
		// д'Ойли на Антигуа
		case "doily":
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "end" && colonies[FindColony("Pirates")].nation == PIRATE)
			{
				PlaySound("Voice\English\LE\Doily\Edvard_Doily_01.wav");
				dialog.text = "Oh, quelle rencontre ! N'est-ce pas le Capitaine Charles de Maure lui-même ?! J'ai entendu dire que vous avez maintenant un poste dans la marine française. Quelle surprise, étant donné pour qui vous 'travailliez', disons, auparavant...";
				link.l1 = "Salutations, monsieur. Parlez-vous de l'affaire avec Isla Tesoro? Oh, mais ce n'est pas moi qui ai rédigé les lois anglaises, selon lesquelles l'île a été transmise à l'héritier de l'explorateur qui l'a découverte, selon son testament. Donc, je ne suis pas coupable de cela, j'ai seulement aidé Mademoiselle Sharp à obtenir ce qui lui revenait de droit.";
				link.l1.go = "doily_1";
			}
			else
			{
				dialog.text = TimeGreeting()+", Capitaine. Je suppose que le représentant de la marine française est arrivé à Antigua avec un objectif important en tête ?";
				link.l1 = "En effet, monsieur. J'ai été envoyé ici par le Gouverneur Général des colonies françaises, Philippe de Poincy. Saint-Christophe a été assiégé par les escadrons de la marine espagnole et néerlandaise. Le Chevalier demande de l'aide de votre part ainsi que de monsieur Jonathan Fox. Voici sa lettre pour vous, colonel.";
				link.l1.go = "doily_3";
			}
		break;
		
		case "doily_1":
			dialog.text = "Je me demande, Capitaine, combien d'argent avez-vous gagné avec cela ? Je suppose, pas mal, puisque vous avez réussi à payer pour les services du renégat Loxley, qui ne sont pas bon marché du tout. Je suis sûr que les barons pirates vous versent régulièrement des parts pour garder l'île en leur possession. Nous savons tous deux parfaitement bien que Helen Sharp n'est qu'un masque.";
			link.l1 = "Colonel, nous savons tous deux aussi que les barons pirates opèrent principalement dans l'intérêt de l'Angleterre, pas officiellement, notez bien... Sans eux, il serait assez difficile de résister à l'hégémonie espagnole dans la région, n'êtes-vous pas d'accord ? Donc, du point de vue des politiciens, le fait que les Frères de la Côte aient gardé l'île pour eux-mêmes était peut-être même plus profitable que si Isla Tesoro était devenue une base navale anglaise...";
			link.l1.go = "doily_2";
		break;
		
		case "doily_2":
			dialog.text = "C'est peut-être vrai, Capitaine, mais... soit. Vous êtes arrivé à Antigua avec un objectif important, je suppose ? Peut-être cela a-t-il à voir avec le fait que les relations de deux anciens alliés - la France et la Hollande, se sont considérablement détériorées ?";
			link.l1 = "Tout à fait. J'ai été envoyé par le gouverneur général des colonies françaises, Philippe de Poincy. Saint-Christophe a été assiégé par la marine espagnole et hollandaise. Le Chevalier demande votre aide. Voici sa lettre pour vous, colonel.";
			link.l1.go = "doily_3";
		break;
		
		case "doily_3":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "Laisse-moi voir... (lisant)";
			link.l1 = "";
			link.l1.go = "doily_3_1";
		break;
		
		case "doily_3_1":
			LAi_Fade("", "");
			dialog.text = "Hmm... très intrigant ! Capitaine, votre commandant sait comment éveiller ma curiosité, il n'est pas si inhabituel que l'on l'appelle un renard rusé. Nous aurions dû faire cela il y a longtemps, au lieu de tenter de nous lier d'amitié avec les Hollandais. Car nous savons très bien ce que représentent la Compagnie Hollandaise et leur Directeur. Eh bien, dans cette situation, je pense que nous ne devrions vraiment pas refuser d'aider le Casterville assiégé, et nous avons plus que suffisamment de troupes pour le permettre.\nQuels sont les nombres et types de navires dans leurs escadrons, Capitaine ?";
			link.l1 = "J'ai compté six navires : un vaisseau de ligne de quatre-vingts canons de troisième rang et cinq navires du quatrième. Ils pourraient aussi avoir des frégates et des galions.";
			link.l1.go = "doily_4";
		break;
		
		case "doily_4":
			dialog.text = "Hmm... Nous pouvons avancer notre escadre, composée d'un navire de cent canons de premier rang, de deux vaisseaux de quatrième rang et d'une lourde frégate, contre la leur.";
			if (!CheckAttribute(pchar, "questTemp.Patria.FailLugger"))
			{
				link.l1 = "Monsieur, nous avons aussi un vaisseau de guerre de 66 canons, l'Éclatant, naviguant à l'aide de la défense de Saint-Christophe depuis la côte de la Guadeloupe.";
				link.l1.go = "doily_5";
			}
			else
			{
				link.l1 = "Un navire de premier rang sera d'une grande aide dans la bataille à venir.";
				link.l1.go = "doily_5_1";
			}
		break;
		
		case "doily_5":
			dialog.text = "Parfait. Dans ce cas, nous sommes bien au-dessus de la capacité de tir de nos ennemis. La victoire sera nôtre.";
			link.l1 = "Et n'oublions pas mon propre navire, monsieur. Je ne vais pas manquer une telle bataille, n'y songez même pas.";
			link.l1.go = "doily_6";
		break;
		
		case "doily_5_1":
			dialog.text = "C'est vrai. Avec l'aide du fort de Casterville, la victoire sera notre.";
			link.l1 = "Et n'oublions pas mon propre navire, monsieur. Je ne vais pas manquer une telle bataille, n'y songez même pas.";
			link.l1.go = "doily_6";
		break;
		
		case "doily_6":
			dialog.text = "Bien sûr, monsieur de Maure. Quoi qu'il en soit, des récits de vos talents en navigation se font entendre dans tout l'archipel. Votre navire amiral mènera l'escadron.";
			if (GetCompanionQuantity(pchar) > 1)
			{
				link.l1 = "Je mettrai le reste des navires de mon escadre en attente, puis je reviendrai vers toi, et nous nous précipiterons au secours des assiégés.";
				link.l1.go = "doily_7_1";
			}
			else
			{
				link.l1 = "Je préparerai mon navire sous peu, et nous nous précipiterons à l'aide des assiégés.";
				link.l1.go = "doily_8";
			}
		break;
		
		case "doily_7_1":
			DialogExit();
			npchar.dialog.currentnode = "doily_7_2";
		break;
		
		case "doily_7_2":
			dialog.text = "Alors, es-tu prêt pour le départ ?";
			if (GetCompanionQuantity(pchar) > 1)
			{
				link.l1 = "Attendez juste un peu, monsieur.";
				link.l1.go = "doily_7_1";
			}
			else
			{
				link.l1 = "Oui, monsieur.";
				link.l1.go = "doily_8";
			}
		break;
		
		case "doily_8":
			dialog.text = "Alors commençons, et que Dieu nous vienne en aide !";
			link.l1 = "... ";
			link.l1.go = "doily_9";
		break;
		
		case "doily_9":
			DialogExit();
			npchar.dialog.currentnode = "doily_10";
			chrDisableReloadToLocation = true;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			AddQuestRecord("Patria", "42");
			Patria_SiegeAddEngSquadron();
		break;
		
		case "doily_10":
			dialog.text = "Avez-vous d'autres questions, monsieur ?";
			link.l1 = "Non, colonel...";
			link.l1.go = "doily_11";
		break;
		
		case "doily_11":
			DialogExit();
			npchar.dialog.currentnode = "doily_10";
			npchar.DeckDialogNode = "doily_10";
		break;
		
		case "doily_12":
			PlaySound("Voice\English\LE\Doily\Edvard_Doily_02.wav");
			dialog.text = "Obtenez la lettre pour le Stuyvesant, monsieur. Si vous ne savez pas qui je suis, permettez-moi de me présenter : Colonel Edward Doily, gouverneur de Port-Royal et commandant de cette expédition !\nPour vous dire la vérité, j'ai une grande envie de réduire en cendres le repaire de bandits connu sous le nom de Willemstad. L'organisation la plus vile, hypocrite et méprisable des Caraïbes, connue sous le nom de Compagnie néerlandaise des Indes occidentales, qui pense que tout le commerce de l'archipel leur appartient exclusivement, et qui engage des gens comme Jacob van Berg et d'autres pirates pour capturer et couler les navires des marchands anglais...";
			link.l1 = "...";
			link.l1.go = "doily_13";
		break;
		
		case "doily_13":
			dialog.text = "Je suis ici pour mettre fin à ces actes scandaleux, et, heureusement pour vous, je propose une voie diplomatique. Pour l'instant... Mais si le directeur de cette organisation abominable n'arrive pas ici pour les pourparlers, je mettrai son affaire en faillite. Après avoir pris d'assaut la ville, je ne laisserai derrière moi que des cendres, et toute poudre que nous trouverons, nous la mettrons dans le sous-sol de votre fort, et nous le ferons sauter. Le même sort attendra vos plantations, et Stuyvesant lui-même pendra à la vergue de mon navire amiral...";
			link.l1 = "D'accord...";
			link.l1.go = "doily_14";
		break;
		
		case "doily_14":
			dialog.text = "Il te faudra plus d'une année pour reconstruire ta colonie, et ensuite tu n'auras plus le temps pour tes machinations et complots. Dis à ton 'Monsieur Directeur' tout ce que je viens de dire, et ne pense pas que ce sont des plaisanteries et des promesses en l'air. J'ai perdu patience, alors tu dois me comprendre parfaitement. Comprends-tu, Officier ?!";
			link.l1 = "Tout est parfaitement clair, monsieur le colonel.";
			link.l1.go = "doily_15";
		break;
		
		case "doily_15":
			dialog.text = "Parfait. Alors partez. Je vous donne exactement un jour pour y réfléchir. Si après vingt-quatre heures Peter Stuyvesant ne se tient pas ici comme vous en ce moment, qu'il s'en prenne à lui-même.";
			link.l1 = "...";
			link.l1.go = "doily_16";
		break;
		
		case "doily_16":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("Doily_land");
			sld.dialog.currentnode = "doily_17";
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "doily_17":
			dialog.text = "Je pense que ce maudit chien Stuyvesant viendra ici. Et sinon - il ne pourra s'en prendre qu'à lui-même !";
			link.l1 = "...";
			link.l1.go = "doily_17_1";
		break;
		
		case "doily_17_1":
			DialogExit();
			npchar.dialog.currentnode = "doily_17";
			AddQuestRecord("Patria", "63");
			Patria_CuracaoParlamenterGo();
		break;
		
		case "doily_18": // д'Ойли на берегу
			dialog.text = "Vous avez fait du bon travail avec le fort, monsieur de Maure. Maintenant, nous approcherons des portes de la ville par voie terrestre. Je prendrai les canons d'ici, le chemin ici est plus court et plus facile, et vous débarquerez la compagnie de vos marins au cap Santa-Maria et vous dirigerez vers Willemstad. Si vous rencontrez des ennemis en chemin, vous savez quoi faire. Personne ne doit être laissé derrière nous.";
			link.l1 = "Bien sûr, colonel. Je vous retrouverai aux portes !";
			link.l1.go = "doily_19";
		break;
		
		case "doily_19":
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddQuestRecord("Patria", "61");
			npchar.dialog.currentnode = "doily_10";
			Patria_CuracaoGotoMarch();
		break;
		
		case "doily_20":
			dialog.text = "Eh bien, il semble que notre mission se soit terminée avec beaucoup de succès. Félicitations, Capitaine ! Oh, excusez-moi - Vice-Amiral ! Retournons sur les navires. Je vais dire à mes hommes de monter la garde - cet imbécile de Stuyvesant ne risquera probablement pas de nous attaquer pendant que nous nous retirons, mais il ne fera pas de mal d'être prudent.";
			link.l1 = "Je suis sûr que les Hollandais n'oseront pas rompre un traité qui vient d'être signé.";
			link.l1.go = "doily_21";
		break;
		
		case "doily_21":
			dialog.text = "C'était un plaisir de travailler avec vous, monsieur de Maure. Je pense que nous nous reverrons à Port-Royal ou à Capsterville.";
			link.l1 = "Sans aucun doute, colonel. Maintenant, disons à nos hommes de battre en retraite.";
			link.l1.go = "doily_22";
		break;
		
		case "doily_22":
			DialogExit();
			AddQuestRecord("Patria", "64");
			Patria_CuracaoClear();
		break;
		
		case "doily_23":
			dialog.text = "Il semble que les Hollandais aient enfin compris qu'ils n'ont aucun moyen de nous approcher depuis le fort par ce chemin étroit sous notre feu d'artillerie. Et ceux coincés dans la ville ne risqueront probablement pas une sortie, à moins d'être complètement fous. Maintenant, nous allons semer un peu de panique : bombardons la ville avec nos canons. Les hommes sur mon navire le verront et feront semblant de se préparer à débarquer. Après une heure ou deux, Stuyvesant se fera dans les braies et sera prêt à envoyer les émissaires de trêve.";
			link.l1 = "Tout se déroule selon notre plan, colonel ! Allons-y !";
			link.l1.go = "doily_24";
		break;
		
		case "doily_24":
			DialogExit();
			Patria_CuracaoTownBombing();
		break;
		
		// голландский парламентёр под стенами Виллемстада
		case "holoff":
			dialog.text = "Je suis arrivé ici pour commencer les négociations. Quelles sont vos exigences ?";
			link.l1 = "Nous exigeons une rencontre avec le Directeur de la Compagnie, Peter Stuyvesant. Plus précisément, nous voulons parler du fait qu'à cause de la faute de sa compagnie, ainsi que de la sienne, Willemstad est actuellement menacée de destruction.";
			link.l1.go = "holoff_1";
		break;
		
		case "holoff_1":
			dialog.text = "Très bien, je parlerai à monsieur Stuyvesant de cela, et nous organiserons une route sûre pour votre délégation vers la ville...";
			link.l1 = "Et qu'en est-il d'une sortie sûre ?";
			link.l1.go = "holoff_2";
		break;
		
		case "holoff_2":
			dialog.text = "Je ne comprends pas, monsieur ?";
			link.l1 = "J'ai dit : allez-vous organiser une sortie en sécurité de la ville pour nous ? Je n'en suis pas sûr. J'ai peur que monsieur Stuyvesant ne décide simplement de capturer nos envoyés. Pour cette raison, j'invite monsieur Stuyvesant à venir ici même pour les négociations.";
			link.l1.go = "holoff_3";
		break;
		
		case "holoff_3":
			dialog.text = "Mais...";
			link.l1 = "Officier, c'est nous qui dictons les conditions ici. Votre flotte est détruite, la garnison coupée de la ville, et nous percerons la défense de Willemstad comme une frégate perce une chaloupe si nous décidons de prendre la ville d'assaut. Maintenant, vous recevrez une lettre pour monsieur Stuyvesant, et vous la lui remettrez avec notre invitation...";
			link.l1.go = "holoff_4";
		break;
		
		case "holoff_4": // перекидываем pchar на офицера и говорим с д'Ойли
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Curacao_parlamenter_1"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Doily_land");
			sld.dialog.currentnode = "doily_12";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//лоченые интерфейсы
		break;
		
		// офицер-испанец на маяке Тринидада
		case "SanJoseSpanish":
			dialog.text = "Alors, Capitaine, avez-vous convoqué les émissaires de trêve parce que vous vouliez dicter vos exigences ?";
			link.l1 = "Vous avez absolument raison, señor. Permettez-moi de vous expliquer brièvement la raison de ma venue à Trinidad - c'est notre réponse à votre récente attaque sur Saint-Pierre. Vous avez considérablement endommagé la ville, et maintenant vous serez contraint de la dédommager. Le prix du dédommagement est de trois cent mille Pesos. Et ce n'est pas tant que ça, compte tenu des actes infâmes que vos soldats ont commis en Martinique.";
			link.l1.go = "SanJoseSpanish_1";
		break;
		
		case "SanJoseSpanish_1":
			dialog.text = "Dites-moi, senor, mais qu'est-ce que San Jose a à voir avec Saint-Pierre ? Pourquoi notre colonie doit-elle payer ?";
			link.l1 = "Parce que les attaquants étaient espagnols, pas néerlandais ou anglais. Ensuite, vous mettrez la note sur Providence pour Don de Mendosa, avec mes salutations les plus sincères. Comme vous le comprenez, au cas où vous refuseriez de payer la compensation, j'ordonnerai à mes hommes de débarquer, et alors San Jose perdra beaucoup plus. Je suis sûr que le gouverneur de votre colonie prendra la bonne décision. Vous avez un jour pour répondre. Je vous souhaite tout le meilleur, senores.";
			link.l1.go = "SanJoseSpanish_2";
		break;
		
		case "SanJoseSpanish_2":
			DialogExit();
			npchar.dialog.currentnode = "SanJoseSpanish_3";
			Patria_SanJoseMayakSpanishGo();
		break;
		
		case "SanJoseSpanish_3":
			dialog.text = "";
			link.l1 = "Alors, si je comprends bien, le gouverneur a pris la bonne décision ?";
			link.l1.go = "SanJoseSpanish_4";
		break;
		
		case "SanJoseSpanish_4":
			AddMoneyToCharacter(pchar, 300000);
			dialog.text = "Prends tes trois cent mille et sors de notre colonie.";
			link.l1 = "Excellent, senores. Je vous assure - c'était la meilleure manière. J'espère que cela dissuadera le Don de Mendosa et d'autres d'attaquer nos colonies. N'oubliez pas d'envoyer le message à Providence et à lui personnellement. Je vous souhaite bonne chance, messieurs.";
			link.l1.go = "SanJoseSpanish_5";
		break;
		
		case "SanJoseSpanish_5":
			DialogExit();
			Patria_SanJoseMayakSpanishFin();
		break;
		
		// вестовой на 5 задание
		case "fraofficer":
			dialog.text = "Capitaine Charles de Maure, permettez-moi de vous faire mon rapport : le Chevalier Philippe de Poincy a voulu vous informer que le Baron Noel Forget est prêt à partir pour Saint-Martin et vous attendra sur le quai.";
			link.l1 = "Excellent ! Merci, monsieur.";
			link.l1.go = "fraofficer_1";
		break;
		
		case "fraofficer_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 10.0);
			Patria_SanMartinSetBaron();
		break;
		
		case "fraofficer_2":
			dialog.text = "Capitaine Charles de Maure ! Le Gouverneur Général vous appelle à l'instant. Une puissante escadre ennemie est apparue au large de Saint-Christophe !";
			link.l1 = "Alors ne perdons pas de temps !";
			link.l1.go = "fraofficer_3";
		break;
		
		case "fraofficer_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;
			Patria_SiegeHovernor();
		break;
		
		// патруль у рудника
		case "engofficer":
			dialog.text = "Qui es-tu? Que fais-tu ici?";
			link.l1 = "Euh...";
			link.l1.go = "engofficer_1";
		break;
		
		case "engofficer_1":
			dialog.text = "Personne n'est autorisé à entrer ici ! Qui êtes-vous, des espions ? Je vais vous emmener au bureau du commandant, ils s'occuperont de vous.";
			link.l1 = "Mais nous ne pouvons pas aller au bureau du commandant...";
			link.l1.go = "engofficer_2";
		break;
		
		case "engofficer_2":
			dialog.text = "Si tu n'y vas pas de ton plein gré, nous devrons te traîner de force ! Remets tes armes !";
			link.l1 = "Aucune affaire...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Patria_CondotierBeachFight");
		break;
		
		// бывший управляющий рудника
		case "miner":
			dialog.text = "";
			link.l1 = "Alors, tout est clair ?";
			link.l1.go = "miner_1";
		break;
		
		case "miner_1":
			dialog.text = "Oui, monsieur. La lettre doit être remise en main propre à monsieur Peter Stuyvesant ou Mathias Beck.";
			link.l1 = "Je suis sûr que vous n'aurez pas de mal à trouver un navire de Willemstad à Carthagène. Nous vous avons donné tous les fonds nécessaires pour payer le voyage et l'hébergement. Et au cas où vous auriez besoin de le faire - vous confirmerez vos rapports devant la commission française dans six mois ?";
			link.l1.go = "miner_2";
		break;
		
		case "miner_2":
			dialog.text = "Monsieur, je suis fidele a ma parole.";
			link.l1 = "Très bien. Alors je vous souhaite bonne chance. Ce chemin mène à Willemstad, suivez-le. Ce n'est pas loin d'ici.";
			link.l1.go = "miner_3";
		break;
		
		case "miner_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "Patria_CondotierOnCuracaoWait", 15.0);
			AddQuestRecord("Patria", "82");
			ReleasePrisoner(npchar);
		break;
		
		// курьер в Капстервиль
		case "cureer":
			dialog.text = "Vice-amiral Charles de Maure, n'est-ce pas ?";
			link.l1 = "Précisément. À qui ai-je l'honneur de parler ?";
			link.l1.go = "cureer_1";
		break;
		
		case "cureer_1":
			dialog.text = "J'ai un message pour vous de la part du baron Noel Forget. Il vous a dit de venir au palais du gouverneur à Casterville dès que possible.";
			link.l1 = "Oh ! Excellentes nouvelles ! Merci, je partirai immédiatement !";
			link.l1.go = "cureer_2";
		break;
		
		case "cureer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			Patria_EuropePrepare();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
		break;
		
		case "burden":
			dialog.text = "Salutations, vice-amiral. Le baron Forget m'a raconté des histoires à votre sujet. Beaucoup d'histoires. Je vous adresse mes plus sincères remerciements pour votre service loyal et brillant au profit de la France dans les colonies, ainsi que pour votre aide à démasquer les intrigues de l'escroc de Poincy. Maintenant, moi et le ministre des Finances allons nous occuper de lui personnellement, et vous prendrez la place de votre ancien commandant. Du moins, pour l'instant.";
			link.l1 = "Mais...";
			link.l1.go = "burden_1";
		break;
		
		case "burden_1":
			dialog.text = "Pas de 'mais', vice-amiral ! Cette décision a déjà été prise et approuvée par le Roi. J'ai ici un ordre signé de sa main vous nommant de facto Gouverneur Général des colonies françaises de l'Archipel. Nous n'avons pas de meilleurs candidats pour ce poste. Votre expérience exceptionnelle en matière de guerre, votre connaissance de la région et des personnes responsables de tout ici, vos compétences et vos talents sont dignes de cette position élevée et respectable. Si je puis être honnête avec vous, je m'attends à ce qu'après un certain temps, vous soyez à nouveau nommé à ce poste, sans la partie 'de facto'.";
			link.l1 = "Mais je rêvais de retourner à Paris...";
			link.l1.go = "burden_2";
		break;
		
		case "burden_2":
			dialog.text = "La France a besoin de toi ici ! Le Ministre des Finances rassemble une flotte en Europe à l'heure actuelle, et notre présence ici, dans l'Archipel, ne passera pas non plus inaperçue. Ta tâche principale sera de renforcer et fortifier les colonies et d'accroître la puissance militaire de notre flotte, tandis que le Baron Forget et la Compagnie française des Indes occidentales se concentreront sur le commerce et le développement intérieur ! Et qui d'autre, sinon toi, peut aider à préparer la marine française ?\nAlors, commence à travailler, Gouverneur Général ! Je sais que tu n'aimes pas rester assis dans une pièce toute la journée, mais ta tâche ne l'exige même pas !";
			link.l1 = "Tout de suite, votre Grâce ! Les ordres ne se discutent point !";
			link.l1.go = "burden_3";
		break;
		
		case "burden_3":
			dialog.text = "Je suis heureux que vous m'ayez compris correctement. Et je vais aussi vous demander de rendre visite au Chevalier de Poincy : il a insisté pour vous rencontrer. Nous ne pouvons pas lui refuser un tel plaisir avant son départ pour Paris, n'est-ce pas ? Vous le trouverez en prison.";
			link.l1 = "Très bien, votre Grâce...";
			link.l1.go = "burden_4";
		break;
		
		case "burden_4":
			DialogExit();
			DoQuestReloadToLocation("Charles_prison", "goto", "goto19", "Patria_EuropePuancieInPrison");
		break;
		
		// Портной Пуанси Xenon
		case "Tailor":
			dialog.text = "...va caler, tu comprends? J'ai commandé ces matériaux il y a plusieurs mois!";
			link.l1 = "... ";
			link.l1.go = "Tailor_01";
			CharacterTurnByChr(npchar, characterFromId("Charles_PortMan"));
		break;
		
		case "Tailor_01":
			DialogExit();
			sld = characterFromId("Charles_PortMan");
			sld.dialog.currentnode = "Tailor";
			LAi_SetActorType(pchar);
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;
		
		case "Tailor_02":
			dialog.text = "Et comment ont-ils décidé quoi transporter sur le premier navire et quoi sur le deuxième ?! Je ne suis pas juste une couturière de campagne - j'ai même un ordre du gouverneur-général, son Excellence le chevalier de Poincy !";
			link.l1 = "...";
			link.l1.go = "Tailor_03";
			CharacterTurnByChr(npchar, characterFromId("Charles_PortMan"));
		break;
		
		case "Tailor_03":
			DialogExit();
			Lai_SetPlayerType(pchar);
			sld = characterFromId("Charles_PortMan");
			sld.dialog.currentnode = "Tailor_02";
			LAi_SetActorType(pchar);
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;
		
		case "Tailor_04":
			dialog.text = "Eh bien, que puis-je faire d'autre maintenant... J'attendrai. Mais sachez ceci : je ne serai pas tenu responsable des commandes non exécutées !";
			link.l1 = "Salutations. Je vois que vous avez des ennuis ?";
			link.l1.go = "Tailor_05";
			CharacterTurnByChr(npchar, characterFromId("Charles_PortMan"));
		break;
		
		case "Tailor_05":
			dialog.text = "Des ennuis? C'est peu dire! Oh, je crois que je te reconnais... Tu es le nouveau vice-amiral, n'est-ce pas?";
			link.l1 = "Rapide à comprendre. C'est exact, devant vous se tient le deuxième homme des colonies françaises, Vice-amiral de la flotte française, Charles de Maure.";
			link.l1.go = "Tailor_06";
			link.l2 = "Laisse tomber ces formalités, nous ne sommes pas sur un navire. Et ne t'inquiète pas, je ne vais pas appeler les gardes juste parce que tu ne m'as pas reconnu tout de suite. Appelle-moi simplement Charles de Maure.";
			link.l2.go = "Tailor_07";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Tailor_06":
			AddCharacterExpToSkill(pchar, "Leadership", 300);//харизма
			dialog.text = "Votre Excellence, je vous prie de me pardonner de ne pas vous avoir reconnu immédiatement ! Oui, vous avez raison, j'ai rencontré des circonstances imprévues.";
			link.l1 = "Et quelles seraient ces circonstances? Si j'ai bien compris, ils ne vous ont pas apporté de matériaux de Paris?";
			link.l1.go = "Tailor_08";
		break;
		
		case "Tailor_07":
			AddCharacterExpToSkill(pchar, "Fortune", 300);//везение
			dialog.text = "Oh, merci beaucoup. Vous avez raison, j'ai rencontré des circonstances imprévues, c'est pourquoi je n'ai pas immédiatement réalisé qui était devant moi.";
			link.l1 = "Et quelles seraient ces circonstances ? Si je comprends bien, ils ne vous ont pas apporté de matériaux de Paris ?";
			link.l1.go = "Tailor_08";
		break;
		
		case "Tailor_08":
			dialog.text = "Oui, c'est exact. Je les ai commandés il y a plusieurs mois. Le gouverneur a signé l'ordre pour votre nomination à l'époque et a insisté pour que je prépare tous les matériaux nécessaires pour un nouvel uniforme d'amiral, sûr qu'il serait approuvé dans la métropole.";
			link.l1 = "Et les matériaux n'ont pas été livrés, je présume ?";
			link.l1.go = "Tailor_09";
		break;
		
		case "Tailor_09":
			dialog.text = "Imaginez-vous cela ! J'ai expliqué combien c'était important, passé la commande... Mais ils ont des livraisons plus urgentes à gérer ! Que dois-je faire ? Passer mes commandes un an à l'avance, en espérant qu'ils daigneront m'apporter les matériaux ?";
			link.l1 = "Que vous manque-t-il exactement ? Peut-être peut-il être obtenu aux Caraïbes ?";
			link.l1.go = "Tailor_10";
		break;
		
		case "Tailor_10":
			dialog.text = "Même si c'est possible, je n'ai aucune idée d'où... Vous ne trouverez pas de bons matériaux ici. Quoique... Je pourrais utiliser votre vieille veste d'officier comme base, si vous le permettez. Vous n'en aurez probablement plus besoin une fois que vous aurez un uniforme d'amiral, n'est-ce pas ?";
			link.l1 = "Si j'ai un uniforme d'amiral, alors bien sûr, je n'aurai pas besoin d'une simple veste d'officier. Quoi d'autre ?";
			link.l1.go = "Tailor_11";
		break;
		
		case "Tailor_11":
			dialog.text = "Je dois trouver des boutons de manchette et un col pour l'uniforme. D'habitude, je les commande directement dans des ateliers parisiens. Même s'ils sont très simples, je peux les modifier et leur donner un aspect plus présentable. Mais dans ce cas, il m'en faudra plus...";
			link.l1 = "Puisqu'il n'y a pas d'ateliers parisiens dans les Caraïbes, je te trouverai tout un lot de vêtements locaux avec cols et poignets amovibles. Quoi d'autre ?";
			link.l1.go = "Tailor_12";
		break;
		
		case "Tailor_12":
			dialog.text = "Pour les touches finales, j'ai besoin de tissus de très haute qualité. J'ai bien un fileur capable de fabriquer un tel tissu même à partir de fibres grossières. Mais pour cela, il me faut du matériau - idéalement du coton. Une balle sera plus que suffisante.";
			link.l1 = "Cela peut être obtenu aussi. Quelle est la suite?";
			link.l1.go = "Tailor_13";
		break;
		
		case "Tailor_13":
			dialog.text = "Ils étaient censés livrer un tricorne d'amiral de Paris, mais je peux le faire moi-même si j'ai le matériau. Bien que le tricorne pour vous devait être en tissu, le cuir serait meilleur pour les vents salés et le soleil brûlant des Caraïbes. Il durerait plus longtemps.";
			link.l1 = "I'll get you the leather; don't worry. I won't even have to chase bulls through the jungles of Espanola. Is that all?";
			link.l1.go = "Tailor_14";
		break;
		
		case "Tailor_14":
			dialog.text = "Ils étaient également censés livrer de la soie de première qualité de Lyon. Elle est légère, respirante, absorbe facilement l'humidité, et sèche encore plus vite. Et surtout, elle ne s'étire pas et garde sa forme.";
			link.l1 = "Oui, je comprends de quelle soie tu parles. Cela pourrait être plus difficile à obtenir dans les colonies cependant.";
			link.l1.go = "Tailor_15";
		break;
		
		case "Tailor_15":
			dialog.text = "C'est tout pour les matériaux. J'ai aussi entendu dire que vous avez été décoré de la plus haute distinction de France... L'Ordre de Saint Louis ne doit pas être porté comme un simple bibelot à votre ceinture. Il a sa place. Alors, s'il vous plaît, apportez-le-moi, et je le coudrai comme il se doit.";
			link.l1 = "D'accord, je l'apporterai aussi. Ne le perds pas surtout !";
			link.l1.go = "Tailor_16";
		break;
		
		case "Tailor_16":
			dialog.text = "Certainement pas ! Je le garderai au péril de ma vie !";
			link.l1 = "D'accord alors. Si c'est tout, je vais chercher les matériaux.";
			link.l1.go = "Tailor_17";
		break;
		
		case "Tailor_17":
			dialog.text = "Il y a une chose de plus... Mes outils de couture sont devenus inutilisables. J'ai commandé de nouveaux outils de Paris, mais hélas... Si tu pouvais trouver tous les matériaux nécessaires et me prêter les outils, si tu les as - juste les prêter, j'en obtiendrai de nouveaux plus tard ! - je commencerais immédiatement à coudre.";
			link.l1 = "Eh bien, que puis-je faire? Je vous apporterai tout ce dont vous avez besoin. Où puis-je vous trouver? Vous n'attendrez pas après moi à l'autorité portuaire, n'est-ce pas?";
			link.l1.go = "Tailor_18";
		break;
		
		case "Tailor_18":
			dialog.text = "Mon atelier est situé dans le bâtiment juste sur le quai - quand vous débarquez, il sera sur votre droite.";
			link.l1 = "D'accord. Je te procurerai les matériaux.";
			link.l1.go = "Tailor_19";
		break;
		
		case "Tailor_19":
			DialogExit();
			AddQuestRecord("Patria", "65_1");
			chrDisableReloadToLocation = false;
			ChangeCharacterAddressGroup(npchar, "Charles_houseS3", "barmen", "Stay");
			npchar.dialog.currentnode = "Tailor_20";
			LAi_SetOwnerType(npchar);
			pchar.questTemp.PatriaTailor = true;
		break;
		
		case "Tailor_20":
			dialog.text = "Salutations, vice-amiral ! Avez-vous apporté tout le nécessaire pour votre nouvel uniforme ?";
			link.l1 = "Pas encore, je n'ai pas eu le temps. Attendez, je vais tout chercher.";
			link.l1.go = "Tailor_20_exit";
			if(CheckCoatItems())
			{
				link.l2 = "Oui, j'ai tout apporté. Voici ma vieille veste, l'Ordre et les outils de couture. Le reste des matériaux, mes marins les apporteront bientôt à votre atelier.";
				link.l2.go = "Tailor_21";
			}
		break;
		
		case "Tailor_20_exit":
			npchar.dialog.currentnode = "Tailor_20";
			DialogExit();
		break;
		
		case "Tailor_21":
			RemoveItems(pchar, "talisman9", 1);
			RemoveItems(pchar, "suit1", 1);
			RemoveItems(pchar, "tailor_tool", 1);
			RemoveCharacterGoods(pchar, GOOD_CLOTHES, 1);
			RemoveCharacterGoods(pchar, GOOD_COTTON, 1);
			RemoveCharacterGoods(pchar, GOOD_LEATHER, 1);
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 1);
			dialog.text = "Merveilleux ! Pour être honnête, je ne pensais pas que vous réussiriez à obtenir tout cela. J'ai l'habitude de travailler uniquement avec des tissus de Paris, mais il semble que vous puissiez confectionner des costumes assez décents avec des matériaux locaux.";
			link.l1 = "Combien de temps avant que mon nouvel uniforme soit prêt ?";
			link.l1.go = "Tailor_22";
		break;
		
		case "Tailor_22":
			dialog.text = "D'habitude, cela prend pas moins d'une semaine, mais étant donné que les clients sont les deux plus hauts fonctionnaires de France dans les colonies... Revenez me voir dans trois jours, et je vous promets que tout sera prêt de la meilleure façon possible ! Nous n'avons pas besoin de prendre des mesures, je ferai tout en me basant sur votre vieille veste.";
			link.l1 = "Superbe! Je reviendrai dans trois jours alors.";
			link.l1.go = "Tailor_23";
		break;
		
		case "Tailor_23":
			DialogExit();
			npchar.dialog.currentnode = "Tailor_24";
			SetFunctionTimerCondition("Patria_Tailor_Done", 0, 0, 3, false);
		break;
		
		case "Tailor_24":
			if(CheckAttribute(pchar,"questTemp.PatriaTailorDone"))
			{
				dialog.text = "Vice-amiral ! C'est un plaisir de vous voir !";
				link.l1 = "Eh bien, je suis venu pour le nouvel uniforme, comme convenu.";
				link.l1.go = "Tailor_27";
			}
			else
			{
				dialog.text = "Salutations, vice-amiral ! Je vous prie de m'excuser, mais votre uniforme n'est pas encore prêt.";
				link.l1 = "Eh bien, puis-je au moins jeter un petit coup d'œil à ce qui se passe ?";
				link.l1.go = "Tailor_25";
			}
		break;
		
		case "Tailor_25":
			dialog.text = "Non, non ! En ce moment, cela paraît complètement inprésentable, et je ne veux pas décevoir vos attentes. Je vous prie d'avoir de la patience.";
			link.l1 = "D'accord, j'attendrai.";
			link.l1.go = "Tailor_26";
		break;
		
		case "Tailor_26":
			DialogExit();
			npchar.dialog.currentnode = "Tailor_24";
		break;
		
		case "Tailor_27":
			dialog.text = "Oui, bien sûr ! Je dois vous dire que cela s'est avéré pas pire que ceux fabriqués à Paris ! Vous aviez raison, même dans les colonies, on peut trouver des matériaux appropriés si l'on sait où chercher. Un instant. Le voici ! Je vous en prie, inspectez-le et essayez-le.";
			link.l1 = "Merci. Excellente qualité ! Et ça va bien.";
			link.l1.go = "Tailor_28";
		break;
		
		case "Tailor_28":
			dialog.text = "Pas seulement bien ! Tu peux fièrement porter cela comme le vice-amiral de France dans les colonies ! Et ton Ordre, comme je l'avais promis, est maintenant à sa place, non pas pendu à ta ceinture.";
			link.l1 = "Bon travail ! Quand vous rencontrerez le Chevalier de Poincy, vous pourrez lui dire que je suis satisfait.";
			link.l1.go = "Tailor_29";
		break;
		
		case "Tailor_29":
			dialog.text = "Je lui dirai certainement ! Que l'uniforme vous serve fidèlement ! Bonne chance !";
			link.l1 = "Merci ! Au revoir.";
			link.l1.go = "Tailor_30";
		break;
		
		case "Tailor_30":
			DialogExit();
			npchar.dialog.currentnode = "first time";
			npchar.lifeday = 0;
			DeleteAttribute(pchar,"questTemp.PatriaTailorDone");
			DeleteAttribute(pchar, "questTemp.PatriaTailor");
			//if(CheckAttribute (pchar, "IsMushketer")) SetMainCharacterToMushketer("", false);
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			GiveItem2Character(pchar, "suit5");
			EquipCharacterbyItem(pchar, "suit5");
			GiveItem2Character(pchar, "hat5");
			EquipCharacterbyItem(pchar, "hat5");
			AddItems(pchar, "tailor_tool", 1);
			Log_Info("You have received the Vice-Admiral's uniform!");
			AddQuestRecord("Patria", "65_2");
		break;
		
		//belamour legendary edition
		case "BladeUpg":
			string sItem, attrL, attrB;
			ref rItem;
			aref arItems; 
			int i, n, iItemsNum;
			dialog.text = "Laquelle de ces lames souhaites-tu améliorer?";
			
			i = 1;
			makearef(arItems, pchar.items);
			iItemsNum = GetAttributesNum(arItems);
			for(n=0; n<iItemsNum; n++)
			{
				sItem = GetAttributeName(GetAttributeN(arItems, n));
				rItem = ItemsFromID(sItem);
				if(!CheckAttribute(rItem, "groupID")) continue;
				if(rItem.groupID != BLADE_ITEM_TYPE) continue;
				if(rItem.price == 0) continue;
				if(IsEquipCharacterByItem(pchar, rItem.id)) continue;
				if(sItem != "" && rItem.groupID == BLADE_ITEM_TYPE) 
				{
					attrL = "l" + i;
					Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt") + ": Attack - " + FloatToString(stf(rItem.attack),1) + ", balance - " + FloatToString(stf(rItem.Balance),1) + ", weight - " + FloatToString(stf(rItem.Weight),1);
					Link.(attrL).go = "bladeindex_"+GetItemIndex(rItem.id);
					i++;
				}
			}
			
			link.l500 = "J'ai changé d'avis";
			link.l500.go = "exit";
		break;
	}
} 

bool CheckCoatItems()
{
	if(GetSquadronGoods(pchar, GOOD_CLOTHES) > 0
	&& GetSquadronGoods(pchar, GOOD_COTTON) > 0
	&& GetSquadronGoods(pchar, GOOD_LEATHER) > 0
	&& GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0
	&& GetCharacterFreeItem(pchar, "talisman9") > 0
	&& GetCharacterFreeItem(pchar, "suit1") > 0
	&& GetCharacterFreeItem(pchar, "tailor_tool") > 0)
	return true;
	
	return false;
}
