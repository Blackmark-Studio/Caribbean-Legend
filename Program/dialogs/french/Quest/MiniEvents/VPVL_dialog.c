
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		////// Леа Карно //////
		
		case "Exit":
			DialogExit();
		break;
		
		case "First Time":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" ! Pardonnez-moi... êtes-vous marin"+GetSexPhrase("","e")+" ?";
			link.l1 = "Je suis le capitaine "+GetFullName(pchar)+", à votre service.";
			link.l1.go = "Lea First Talk";
			DelLandQuestMark(npchar);
		break;

		case "Lea First Talk":
			dialog.text = "Je suis Lea. Lea Carnot... "+GetSexPhrase("Monsieur","Mademoiselle")+" le capitaine, êtes-vous arrivé depuis longtemps ? Vous n'auriez pas vu une barque de pêche appelée le 'Cormoran' ? Vous voyez, mon mari... mon mari Pierre... il est parti en mer il y a deux jours et n'est jamais revenu.";
			link.l1 = "Le 'Cormoran' ? Non, je n'ai pas croisé pareille embarcation. Un tel nom m'aurait marqué. Je suis désolé de l'apprendre, madame. J'espère de tout cœur que votre mari va bien et qu'il a simplement été retardé en chemin.";
			link.l1.go = "Lea First Talk Rep Plus";
			link.l2 = "Le 'Cormoran' ? Ha ha ! C’est le nom du bateau ou un surnom pour son capitaine ? Enfin, peu importe. Je n’ai vu ni l’un ni l’autre.";
			link.l2.go = "Lea First Talk Rep Minus";
		break;

		case "Lea First Talk Rep Plus":
			dialog.text = "Je ne sais plus quoi penser... Il ne rentrait jamais aussi tard. Il était toujours de retour avant midi. Et maintenant... Quelque chose est arrivé. Je le sens.";
			link.l1 = "Adressez-vous aux autorités. Ils peuvent envoyer un navire de patrouille pour fouiller les côtes.";
			link.l1.go = "Lea First Talk1";
			ChangeCharacterComplexReputation(pchar,"nobility", 3);
		break;

		case "Lea First Talk Rep Minus":
			dialog.text = "Je ne sais plus quoi penser... Il ne rentrait jamais aussi tard. Il était toujours de retour avant midi. Et maintenant... Quelque chose est arrivé. Je le sens.";
			link.l1 = "Adressez-vous aux autorités. Ils peuvent envoyer un navire de patrouille pour fouiller les côtes.";
			link.l1.go = "Lea First Talk1";
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
		break;

		case "Lea First Talk1":
			dialog.text = "Oh, "+GetSexPhrase("monsieur","mademoiselle")+" le capitaine, bien sûr que je me suis adressée au commandant. Mais ça n’a servi à rien... Il a haussé les épaules et m’a dit qu’aucun navire n’était disponible en ce moment pour partir à sa recherche.\nEt moi ? Que puis-je faire ? Je reste là, je regarde l’horizon, j’attends... et j’espère.";
			link.l1 = "Allons, madame Lea. Ne perdez pas espoir trop tôt. Je pense pouvoir consacrer une journée à vous aider dans vos recherches.";
			link.l1.go = "Agree To Help";
			link.l2 = "Pourquoi tant d’inquiétude ? Peut-être que la brise du matin l’a porté dans les bras d’une charmante dame. Il prendra un peu l’air, se dégourdira les jambes et reviendra.";
			link.l2.go = "bad joke";
			link.l3 = "Un conseil ? Cessez d'épuiser vos yeux à scruter l’horizon. Allez donc faire un tour à la taverne de Le François et cherchez votre bien-aimé là-bas. Pardonnez ma franchise, mais il a probablement voulu faire une pause loin des soucis domestiques, et vous dramatisez. Bonne chance dans vos recherches.";
			link.l3.go = "Rejection";
		break;

		case "Agree To Help":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" le capitaine, je... je ne sais même pas comment vous remercier... Vous... vous ne pouvez pas imaginer ce que cela représente pour moi ! Tous les autres se contentent de hausser les épaules... Mais vous... vous êtes prêt à aider. Merci !";
			link.l1 = "Il est encore trop tôt pour me remercier. Mieux vaut me dire où votre mari pêchait habituellement. Avait-il un endroit fixe ou changeait-il souvent ?";
			link.l1.go = "Go To Help";
		break;

		case "bad joke":
			dialog.text = "Une charmante dame, vraiment ? Pensez-vous que ce soit le moment pour plaisanter ? Je sens qu’il est en danger... et vous vous moquez de ma détresse ! (pleure) Tout semble se liguer contre moi. Personne ne veut m’aider... Personne ne comprend à quel point c’est dur.";
			link.l1 = "Madame Lea, pour l’amour du ciel, pardonnez mon impolitesse. Je n’avais aucune intention de vous offenser ! Je vous promets que je vais partir à la recherche de votre mari. Dites-moi seulement par où commencer.";
			link.l1.go = "bad joke1"; 
		break;

		case "bad joke1":
			dialog.text = "Vous... ? Vous voulez vraiment m’aider ?";
			link.l1 = "Bien sûr. C’est le minimum que je puisse faire pour me faire pardonner cette plaisanterie déplacée et inexcusable.";
			link.l1.go = "bad joke2";
		break;

		case "bad joke2":
			dialog.text = "Merci, "+GetSexPhrase("Monsieur","Mademoiselle")+" le Capitaine. Merci... Vraiment, vous me prenez au dépourvu, je ne sais que dire...";
			link.l1 = "Il est trop tôt pour me remercier. Dites-moi plutôt où votre mari allait pêcher d’habitude. Avait-il un endroit fixe, ou bien changeait-il souvent ?";
			link.l1.go = "Go To Help";
		break;

		case "Go To Help":
			dialog.text = "Eh bien... Pierre... Il ne disait jamais exactement où il allait pêcher. Il appelait cela 'son secret'. Mais si cela peut aider à le retrouver... Peut-être... Je ne sais pas... Vous voulez vraiment m’aider, "+GetSexPhrase("Monsieur","Mademoiselle")+" le Capitaine ? Vraiment ?";
			link.l1 = "Vous hésitez à me confier le lieu secret de votre mari ? Je vous assure que ce secret familial restera entre nous — parole de capitaine. J’ai besoin de savoir où c’est, pour savoir où commencer les recherches.";
			link.l1.go = "Go To Help1";
		break;

		case "Go To Help1":
			dialog.text = "Vous avez raison, "+GetSexPhrase("Monsieur","Mademoiselle")+" le Capitaine... Excusez-moi. Ce lieu comptait tant pour Pierre. Il disait toujours que c’était son seul secret, son petit trésor.\nMais je sais où c’est. Et si cela peut aider à le retrouver... Il pêchait dans la baie de Le Marin. Elle est sur la côte sud, pas très loin de la ville. Je vous en prie, trouvez-le !";
			link.l1 = "Ne vous inquiétez pas, Lea. Tout ira bien. Je ferai tout ce qui est en mon pouvoir. Est-ce qu’il avait des ennemis ? Quelqu’un lui aurait-il voulu du mal ?";
			link.l1.go = "Go To Help2";
		break;

		case "Go To Help2":
			dialog.text = "Des ennemis ? Pierre ? Mais c’est l’homme le plus gentil au monde ! Il ne ferait de mal à personne... Ce n’est qu’un simple pêcheur. Qui aurait pu lui en vouloir ? Je ne comprends pas ce qui a bien pu se passer... Tout cela est si étrange... et effrayant...";
			link.l1 = "Ne vous inquiétez pas, Madame Lea. Je pars immédiatement à sa recherche. Je suis certain"+GetSexPhrase("","e")+" qu’il va bien. Je le ramènerai dans vos bras attentionnés. Tenez bon.";
			link.l1.go = "Return Lea Exit";
		break;

		case "Return back to Lea":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" le Capitaine, dites-moi, avez-vous des nouvelles ? Avez-vous appris quelque chose ? Même un petit indice ?";
			link.l1 = "Malheureusement non, pas encore. Mais je le cherche, Lea !";
			link.l1.go = "Exit";
		break;
		
		case "Return Lea Exit":
			DialogExit();
			npchar.dialog.currentnode = "Return back to Lea";
			AddQuestRecord("VPVL", "2"); 
			DoQuestCheckDelay("VPVL_Start", 0.1);
		break;
		
		case "Rejection":
			DialogExit();
			npchar.dialog.currentnode = "Rejection1";
			SetTimerCondition("VPVL_ClearLea", 0, 0, 2, false);  // Удаляем Леа через 2 дня
			CloseQuestHeader("VPVL");
		break;
		
		case "Rejection1":
			dialog.text = "Qu’est-ce que vous voulez encore ? Vous n’en avez pas assez de vous moquer d’une pauvre femme ?";
			link.l1 = "...";
			link.l1.go = "Exit";
		break;

		case "Lea second talk":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" le Capitaine ! Pierre ! Oh, loués soient les saints ! Mes yeux peinent à croire ce qu’ils voient ! Vous me l’avez rendu !";
			link.l1 = "Madame Lea, permettez-moi de vous présenter votre mari—revenu des mâchoires mêmes des profondeurs ! Bien qu’il porte les marques de son épreuve, je gage que vos tendres soins le rétabliront plus vite que le meilleur chirurgien des Indes !";
			link.l1.go = "Lea second talk1";
			locCameraFromToPos(-7.58, 3.1, 82.5, false, -10, -15, 0);
		break;

		case "Lea second talk1":
			dialog.text = "Pierre ! Sainte Mère Marie ! Mon cœur n’a pas connu la paix depuis ta disparition ! Quel terrible sort t’est arrivé ? Ton visage est tiré comme du parchemin... pâle comme l’écume de mer... Cieux miséricordieux ! Ces marques sur ta chair ! Ces horribles blessures ! Ces coupures... ces brûlures...";
			link.l1 = "Chut maintenant, trésor de mon cœur. De simples égratignures qui s’effaceront avec le temps. Contempler ton visage une fois de plus—cela vaut toute la souffrance que j’ai endurée. Sans le courage du Capitaine... je nourrirais maintenant les crabes au fond de la mer. Mon souffle même est son cadeau.";
			link.l1.go = "Lea second talk2";
			CharacterTurnByChr(npchar, CharacterFromID("VPVL_Pier_carno"));
			sld = CharacterFromID("VPVL_Pier_carno");
			CharacterTurnByChr(sld, CharacterFromID("VPVL_Lea_girl"));
			locCameraFromToPos(-7.62, 3.1, 83.26, false, 30, -15, 0);
		break;

		case "Lea second talk2":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" le Capitaine... je... je ne sais même pas comment vous remercier... vous l’avez trouvé ! Vous avez sauvé mon Pierre ! Merci... merci pour tout ! Que Dieu vous protège, "+GetSexPhrase("Monsieur","Mademoiselle")+" le Capitaine !";
			link.l1 = "Assez de ces paroles maintenant. Votre brave homme a besoin de victuailles chaudes dans son ventre et d’une couchette convenable pour reposer ses os fatigués. L’épreuve a fait son effet.";
			link.l1.go = "Exit";
			CharacterTurnByChr(npchar, CharacterFromID("Blaze"));
			locCameraFromToPos(-7.58, 3.1, 82.5, false, -10, -15, 0);
			AddDialogExitQuest("VPVL_PierTalkOnThePirs");
		break;
		
		//////   Контры   //////
		
		case "Kontr Le Maren":
			dialog.text = "Eh bien, te voilà enfin apparu"+GetSexPhrase("","e")+", "+GetSexPhrase("sale cabot","petite friponne")+" ! Où diable étais-tu passé ? Voilà trois jours qu’on cuit sous ce soleil sur cette maudite plage ! Où est notre cargaison ?";
			link.l1 = "On dirait que sans moi, le bal ne commence pas, hein, messieurs ? Bon, j’arrive un peu tard"+GetSexPhrase("","e")+", mais mieux vaut tard que jamais !";
			link.l1.go = "Exit_Sneak";
			link.l2 = "C’est à moi que vous parlez ? Hm, peut-être que vous pourriez apprendre la politesse avant de poser des questions ?"; 
			link.l2.go = "Exit_Lucky";
			//locCameraFromToPos(-3.35, 2.23, 6.93, false, 20, -1, 10);
			locCameraFromToPos(-3.53, 2.35, 6.35, true, 1.93, -0.60, 11.17);
			DeleteAttribute(pchar, "questTemp.VPVL_Contr_V_Lemaren");
		break;
		
		case "Exit_Sneak":
			DialogExit();
			sld = CharacterFromID("VPVL_contr_1");
			sld.dialog.filename = "Quest\MiniEvents\VPVL_dialog.c";
			sld.dialog.currentnode = "Kontr Le Maren0";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddCharacterExpToSkill(pchar, "Sneak", 50);
			notification("Expérience acquise", SKILL_SNEAK);
		break;
		
		case "Exit_Lucky":
			DialogExit();
			sld = CharacterFromID("VPVL_contr_1");
			sld.dialog.filename = "Quest\MiniEvents\VPVL_dialog.c";
			sld.dialog.currentnode = "Kontr Le Maren0";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			notification("Expérience acquise", SKILL_FORTUNE);
		break;
		
		case "Kontr Le Maren0":
			sld = CharacterFromID("VPVL_contr_2");
			dialog.text = ""+sld.name+", t’es complètement bouché ou quoi ? Ouvre les yeux, crétin — c’est pas notre contact du tout !";
			link.l1 = "Argh... Encore un limier du gouverneur ! C’était sûr ! Puisqu’"+GetSexPhrase("elle s’est","il s’est")+" pointé"+GetSexPhrase("e","")+" tout"+GetSexPhrase("e","")+" seul"+GetSexPhrase("e","")+" ici, jetons-le"+GetSexPhrase("a","")+" dans la grotte avec son copain. On va bien s’amuser ! Et on lui arrachera tout ce qu’"+GetSexPhrase("elle","il")+" sait des plans de son patron.";
			link.l1.go = "Kontr Le Maren1";
			locCameraFromToPos(-3.53, 2.35, 6.35, false, -0.03, 0.40, 7.77);
			CharacterTurnByChr(sld, CharacterFromID("VPVL_contr_1"));
			CharacterTurnByChr(pchar, CharacterFromID("VPVL_contr_2"));
			
			sld = CharacterFromID("VPVL_contr_1");
			CharacterTurnByChr(sld, CharacterFromID("VPVL_contr_2"));
		break;

		case "Kontr Le Maren1":
			dialog.text = "Pourquoi tu salives comme ça, espèce de brute ? Retiens ta langue ! On ferait mieux de la... tu sais bien à qui. Il payera un bon sac de pièces pour une fille pareille, et nous, on fêtera ça pendant un mois !";
			if (pchar.sex == "man")
			{
				dialog.text = "Qu’est-ce qu’on ferait d’un autre singe ici ? Faisons parler son copain, il craquera vite. Et ce type, faut s’en débarrasser ici même, qu’il ne nous gêne plus !";
			}
			link.l1 = "Par mille requins, Simon ! Tu es le contrebandier le plus rusé de tout l’archipel !";
			link.l1.go = "Kontr Le Maren2";
		break;
		
		case "Kontr Le Maren2":
			dialog.text = "...";
			if (GetSummonSkillFromName(pchar, SKILL_PISTOL) >= 20)
			{
				if(GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE) == "") {	
					notification("Pistolet manquant", "NONE");
					link.l2 = "Si c’est lui le cerveau du groupe, je n’ose imaginer la stupidité des autres !";
					link.l2.go = "Kontr Le Maren3";
					CharacterTurnByChr(npchar, CharacterFromID("Blaze"));
					locCameraFromToPos(-3.73, 2.45, 5.75, false, -0.53, -0.0, 9.17);
					CharacterTurnByChr(npchar, CharacterFromID("Blaze"));
					sld = CharacterFromID("VPVL_contr_1");
					CharacterTurnByChr(sld, CharacterFromID("Blaze"));
					CharacterTurnByChr(pchar, CharacterFromID("VPVL_contr_1"));
				}
				else
				{
					link.l1 = " (À soi-même)(Pistolet) Tant que ces bavards se perdent dans leurs inepties, j’ai une chance de frapper le premier.";
					link.l1.go = "murder";
					notification("Test réussi", SKILL_PISTOL);
					locCameraFromToPos(-5.73, 2.45, 5.75, true, -0.53, 0.40, 7.17);
				}
			}
			if (GetSummonSkillFromName(pchar, SKILL_PISTOL) < 20)
			{
				notification("Compétence insuffisante (20)", SKILL_PISTOL);
				CharacterTurnByChr(npchar, CharacterFromID("Blaze"));
				sld = CharacterFromID("VPVL_contr_2");
				CharacterTurnByChr(sld, CharacterFromID("Blaze"));
				locCameraFromToPos(-3.73, 2.45, 5.75, false, -0.53, -0.0, 9.17);
				CharacterTurnByChr(pchar, CharacterFromID("VPVL_contr_1"));
			}
			link.l2 = "Si c’est lui le cerveau du groupe, je n’ose imaginer la stupidité des autres !";
			link.l2.go = "Kontr Le Maren3";
		break;

		case "Kontr Le Maren3":
			dialog.text = "Je vais t’arracher la langue, "+GetSexPhrase("sale petit chien insolent","misérable traînée")+" ! Tu ne pourras plus jamais aboyer !";
			link.l1 = "Ah oui ? Vas-y, essaie un peu pour voir.";
			link.l1.go = "Kontr Le Maren Fight";
			CharacterTurnByChr(pchar, CharacterFromID("VPVL_contr_1"));
		break;
		
		case "Kontr Le Maren Fight":
			DialogExit();
			AddDialogExitQuest("VPVL_EveryoneFight");
			LAi_LocationFightDisable(&Locations[FindLocation("Shore39")], false);
			EndQuestMovie();
		break;
		
		case "murder":
			DialogExit();
			AddDialogExitQuest("VPVL_Pistol_Murder");
			//locCameraFromToPos(-5.04, 2.62, 8.65, false, 20, -6, -15);
		break;
		
		/////////////   Пьер Карно   /////////////
		case "PierFirstTalk":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+"... Pardonnez-moi... Je ne comprends plus rien... Êtes-vous venu(e) pour me tuer ?";
			link.l1 = "Vous êtes Pierre Carnot ?";
			link.l1.go = "Pier_1";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.VPVL_SetFlagLeMaren");
		break;
		
		case "Pier_1":
			dialog.text = "Oui, c'est moi. Vous connaissez mon nom ?";
			link.l1 = "Évidemment, sinon que ferais-je ici...";
			link.l1.go = "Pier_2";
		break;
		
		case "Pier_2":
			dialog.text = "Pardonnez-moi, je ne comprends rien... La douleur et la faim m'ont brouillé l'esprit... Pourquoi êtes-vous venu(e) ici ?";
			link.l1 = "C’est simple. Depuis votre disparition, votre fidèle épouse ne quitte plus le quai, espérant voir les voiles du 'Cormoran'. Son désespoir était si poignant que je n’ai pu rester indifférent(e) et j’ai décidé de partir à votre recherche.";
			link.l1.go = "Pier_3";
		break;
		
		case "Pier_3":
			dialog.text = "Ma femme... ma chère Léa... J'étais persuadé de ne jamais la revoir...";
			link.l1 = "Tout cela est derrière vous maintenant. Elle vous attend au quai et n'a jamais perdu espoir. Allons-nous-en d'ici. Je vais vous aider à vous lever.";
			link.l1.go = "Pier_4";
		break;
		
		case "Pier_4":
			dialog.text = "Ouf... Pardonnez-moi, "+GetSexPhrase("monsieur","mademoiselle")+"... j’ai besoin d’un moment... mes jambes me portent à peine, elles sont engourdies... merci infiniment, sans vous... Merci infiniment... Sans vous... c’est le ciel qui vous a envoyé(e) ! Vous ne vous êtes pas présenté(e). Comment dois-je vous appeler ?";
			link.l1 = " Capitaine "+GetFullName(pchar)+". Reprenez vos esprits un instant, et dites-moi comment vous vous êtes retrouvé ici. Aviez-vous des affaires avec ces... gens-là ?";
			link.l1.go = "Pier_5";
			LAi_Fade("VPVL_PierStay", "");
		break;
		
		case "Pier_5":
			dialog.text = "Pas le moins du monde, capitaine. Ce n’est pas mon métier, je suis un simple pêcheur. Tout avait pourtant bien commencé. Je pêchais à l’ouest de la baie. La prise était exceptionnelle.\nJ’étais si pressé de stocker le poisson dans les barils et de relancer les filets que je n’ai même pas vu ma barque dériver vers les récifs. Ses flancs sont aussi fins qu’une coquille — un simple choc a suffi, et l’eau s’est engouffrée. Le 'Cormoran', déjà bien chargé, a sombré en un instant.";
			link.l1 = "Et ensuite vous avez rejoint la côte, et les contrebandiers vous ont pris pour un limier du gouverneur ?";
			link.l1.go = "Pier_6";
		break;
		
		case "Pier_6":
			dialog.text = "Exactement. J’ai à peine atteint la rive, épuisé par les vagues. J’avais besoin de sécher mes os, de me reposer un peu et de retrouver mes forces avant de tenter le trajet jusqu’à la ville. Tout s’est passé si vite... Quand je me suis enfin décidé à partir, je suis tombé sur ces canailles.\nIls m’ont immédiatement pris pour un agent du gouverneur. Je n’ai même pas eu le temps d’ouvrir la bouche qu’ils m’avaient déjà ligoté et traîné ici. Ils m’ont torturé et affamé pendant deux jours, exigeant que je leur livre les espions du gouverneur et ses projets. Mais comment aurais-je pu parler de ce que j’ignore ?";
			link.l1 = "Ces types n’étaient pas des lumières — voilà pourquoi ils reposent six pieds sous terre. Quoi qu’il en soit, tout ça est fini. Vous êtes libre. Il est temps de retrouver votre épouse, elle doit être morte d’inquiétude.";
			link.l1.go = "Pier_7";
		break;
		
		case "Pier_7":
			dialog.text = "J’ai tellement hâte de la serrer dans mes bras. Je crois... je crois que je peux marcher maintenant.";
			link.l1 = "Dans ce cas, ne perdons pas de temps.";
			link.l1.go = "exit_grot";
		break;
		
		case "exit_grot":
			DialogExit();  
			AddQuestRecord("VPVL", "4");
			AddDialogExitQuest("VPVL_PierFollow");
		break;
		
		case "PierInThePirs":
			dialog.text = "Capitaine, venez demain soir à six heures à la taverne. Je ne me le pardonnerais pas si je ne vous remercie pas comme il se doit. En ce moment... je ne trouve pas les mots qu’il faut pour exprimer ma gratitude comme il faut. Je vous en prie, venez. C’est très important pour moi.";
			link.l1 = "D’accord, Pierre, ne vous inquiétez pas, je viendrai.";
			link.l1.go = "GoHome";
			locCameraFromToPos(-8.28, 3.1, 82.93, false, 40, -15, 0);
		break;
		
		case "GoHome":
			DialogExit();
			AddQuestRecord("VPVL", "5");
			AddDialogExitQuest("VPVL_KarnoGoHome");
		break;
		
		case "PierTalkTavern":
			dialog.text = "Capitaine ! Vous voilà ! Prenez donc place.";
			link.l1 = "Avec plaisir !";
			link.l1.go = "PierTalkTavern1";
			LAi_Fade("VPVL_SitOnTheTable", "");
			FreeSitLocator("FortFrance_Tavern", "sit6");  // На всякий случай
			DeleteAttribute(pchar, "questTemp.VPVL_Magor_Dialogue");
			pchar.questTemp.VPVL_DontSpawnSmugglersShipPier = true;
			DelLandQuestMark(npchar);
			AddDialogExitQuest("VPVL_KillCapitanOfSmuggler");
			locCameraFromToPos(-2.87, 1.37, -1.09, false, 0, -0.8, -0.90);
		break;
		
		case "PierTalkTavern1":
			dialog.text = "Levons nos chopes à votre bonne santé !";
			link.l1 = "Non, pas seulement à la mienne, mais à la vôtre aussi ! Vous avez déjà bien meilleure mine que dans cette grotte. Trinquons !";
			link.l1.go = "PierTalkTavern2";
		break;
		
		case "PierTalkTavern2":
			dialog.text = "Capitaine, permettez-moi d’exprimer ma gratitude sans bornes ! Vous ne m’avez pas ignoré, vous ne vous êtes pas détourné, et vous êtes venu en aide à un parfait inconnu, un simple pêcheur. Votre noblesse d’âme force l’admiration, et je tiens à vous remercier de tout ce que j’ai. Tenez. Voici vingt morceaux d’ambre doré et cinq pièces de rare ambre bleu. Je les ai repêchés d’un navire naufragé. Ils sont à vous désormais. Et je veux aussi vous remettre mes instruments de navigation. Tant que je n’aurai pas un nouveau navire, ils me sont inutiles.";
			link.l1 = "Merci, Pierre, ils me seront très utiles. Mais le plus important, c’est que vous soyez de retour à la maison, et que votre épouse n’ait plus à vivre dans l’angoisse. Tout ira mieux à présent.";
			link.l1.go = "PierTakeGift";
			link.l2 = "Merci pour votre générosité, Pierre, mais gardez tout cela. Vous en aurez plus besoin que moi — pour réparer votre barque, acheter de l’équipement, des filets, des tonneaux. Moi, votre gratitude et le fait que vous soyez réunis avec votre femme me suffisent. Prenez soin l’un de l’autre !";
			link.l2.go = "PierWontGift1";
		break;
		
		case "PierTakeGift":
			dialog.text = "Je n’arrive toujours pas à croire que tout cela m’est réellement arrivé. Buvons à un nouveau chapitre dans la vie de ma famille et à votre noblesse, capitaine !";
			link.l1 = "Et à Dame Fortune, Pierre. Elle ne ferait pas de mal à nous tous.";
			link.l1.go = "ZastavkaVPVL";
			AddItems(PChar, "jewelry8", 20);
			AddItems(PChar, "jewelry7", 5);
			AddItems(PChar, "A_map_martiniqua", 1);
			AddItems(PChar, "spyglass3", 1);
			AddItems(PChar, "obereg_7", 1);
		break;
		
		case "PierWontGift1":
			dialog.text = "Capitaine, je ne peux tout simplement pas en rester là... Vous m'avez sauvé la vie, et je vous dois tout. Puisque vous refusez l'ambre et les autres cadeaux, permettez-moi au moins d’enseigner à vos hommes à pêcher dans les eaux peu profondes. Cela leur procurera de la nourriture fraîche et vous aidera à économiser sur les provisions. Qu’en dites-vous ?";
			link.l1 = "Voilà une excellente idée ! Comme on dit, il vaut mieux enseigner à labourer que donner du pain — on mangera soi-même et on nourrira les autres.";
			link.l1.go = "PierWontGift2";
			pchar.questTemp.VPVL_Food = true;
		break;
		
		case "PierWontGift2":
			dialog.text = "Des paroles pleines de sagesse, capitaine ! Je suis heureux de pouvoir être utile. Alors, une autre chope ?";
			link.l1 = "À votre santé et prospérité, Pierre !";
			link.l1.go = "ZastavkaVPVL";
		break;
		
		case "ZastavkaVPVL":
			DialogExit();
			SetLaunchFrameFormParam("Quatre heures se sont écoulées...", "VPVL_SitOnTheTable", 2, 2);
			LaunchFrameForm();
			locCameraFromToPos(-2.87, 1.37, -1.09, false, 0, -0.8, -0.90);
			sld = CharacterFromID("VPVL_Pier_carno");
			sld.dialog.currentnode = "PierTalkTavern3";
			LAi_SetActorType(pchar);
			LAi_ActorDialog(pchar, sld, "", -1, 0);
		break;
		
		case "PierTalkTavern3":
			if(CheckAttribute(pchar, "questTemp.VPVL_Food"))
			{
				int foodDays = CalculateShipFood(&pchar);
				dialog.text = "Par les saints ! Voilà du sacré rhum ! Encore une lampée ou deux, et je... hic... je serai prêt à entonner un chant marin qu’on entendra jusqu’au port !";
				link.l1 = "Garde ta chanson pour des eaux plus calmes, Pierre... hic... Une prochaine fois, peut-être. Si tu t’y mets, je vais finir par te suivre. Et moi... hic... j’ai encore des affaires pressantes. La mer n’attend pas, même pour ceux qui ont bu un coup de trop !";
				link.l1.go = "PierTalkTavern4";
				WaitDate("", 0, 0, 0, 4, 10);
				LAi_AlcoholSetDrunk(pchar, 71, 5600);
				notification("Consommation de provisions du navire -15%", "None");
			}
			else
			{
				dialog.text = "Par les saints ! Voilà du sacré rhum ! Encore une lampée ou deux, et je... hic... je serai prêt à entonner un chant marin qu’on entendra jusqu’au port !";
				link.l1 = "Garde ta chanson pour des eaux plus calmes, Pierre... hic... Une prochaine fois, peut-être. Si tu t’y mets, je vais finir par te suivre. Et moi... hic... j’ai encore des affaires pressantes. La mer n’attend pas, même pour ceux qui ont bu un coup de trop !";
				link.l1.go = "PierTalkTavern4";
				WaitDate("", 0, 0, 0, 4, 10);
				LAi_AlcoholSetDrunk(pchar, 71, 5600);
			}
		break;
		
		case "PierTalkTavern4":
			dialog.text = "Ah, capitaine... vous savez... merci pour tout ! Je vous suis redevable, vous m’entendez ? Si jamais vous repassez par ici... on... on sera toujours heureux de vous voir, comme... comme un membre de la famille ! Parole d’honneur ! Ah... on trinquera encore un jour !";
			link.l1 = "Tiens bon, Pierre... hic... je ferais mieux d’y aller tant que je tiens encore debout !";
			npchar.dialog.currentnode = "RepeatTavern";
			link.l1.go = "Exit2";
			CloseQuestHeader("VPVL");
		break;
		
		case "Exit2":
			DialogExit()
			LAi_Fade("VPVL_ExitFromTableVPVL", "VPVL_PierLivingTavern");
			DeleteAttribute(pchar, "questTemp.VPVL_Delete_Ship_RemoveFlag");
		break;
		
		case "RepeatTavern":
			dialog.text = "À la-a-a mer, et au ve-e-e-ent... hic... à notre route de pêche au lever du jour !... Diable, comment ça continuait déjà ? Capitaine !... Vous êtes encore là ? Tavernier... hic... le meilleur rhum sur cette table !";
			link.l1 = "Je m’en vais déjà, Pierre ! Hic... tant que je suis encore capable de retrouver mon navire !";
			link.l1.go = "Exit";
		break;
		
		case "MeetingInTneCity":
			dialog.text = ""+pchar.name+" ! Quel plaisir de vous revoir ! Alors, une petite mesure de rhum ? À nos retrouvailles !";
			link.l1 = "Moi aussi, je suis ravi"+GetSexPhrase("","e")+" de vous voir, Pierre. Mais hélas, cette fois je dois décliner. Trop de choses à faire, et j’ai besoin d’un esprit clair. Une prochaine fois, peut-être ?";
			link.l1.go = "MeetingInTneCity1";
		break;
		
		case "MeetingInTneCity1":
			dialog.text = "Bien sûr, capitaine. Le devoir avant le plaisir. Mais j’espère qu’on se reverra, et cette fois, on lèvera nos verres !";
			link.l1 = "Sans faute, Pierre. À bientôt !";
			link.l1.go = "Exit";
			npchar.dialog.currentnode = "ExitRepeat";
		break;
		
		case "ExitRepeat":
			dialog.text = "Capitaine ! Êtes-vous enfin libre ?";
			link.l1 = "Hélas non, Pierre. Les affaires m’accaparent encore, malheureusement.";
			link.l1.go = "Exit";
		break;
	}
}   