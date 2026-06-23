// Addon-2016 Jason, французские миниквесты (ФМК) Тортуга
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
			dialog.text = "Un bug évident. Parlez-en aux dévs.";
			link.l1 = "Oh, je le ferai.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "girl":
			DelMapQuestMarkCity("Tortuga");
			LAi_SetImmortal(npchar, false);
			DelLandQuestMark(npchar);
			LAi_RemoveLoginTime(npchar);
			FMQT_FillChest();
			PlaySound("Voice\English\Girls_1.wav");
			dialog.text = "Oh, bonjour monsieur ! Bienvenue à Tortuga ! Des capitaines aussi nobles que vous sont de rares invités ici...";
			link.l1 = "Salutations, mademoiselle. Merci pour cet accueil chaleureux. Mais comment cela se fait-il ? Je pensais qu'un port si important était toujours un lieu d'intérêt pour des gentilshommes de fortune bien plus nobles que moi.";
			link.l1.go = "girl_1";
		break;
		
		case "girl_1":
			dialog.text = "Ah monsieur... Vous êtes clairement un nouveau venu, ai-je raison ? Vous verrez par vous-même. Vous n'avez aucune idée de combien il est difficile de trouver des hommes dignes pour une fête dansante au palais du gouverneur. Peut-être pourriez-vous m'accompagner... ?";
			link.l1 = "Comment puis-je etre au service d'une si belle femme ?";
			link.l1.go = "girl_2";
		break;
		
		case "girl_2":
			dialog.text = "Oh là là, quelle galanterie ! (rire) Peut-être pourriez-vous nous rendre visite à six heures ce soir ? L'épouse de notre gouverneur organise régulièrement des soirées informelles dans les quartiers des serviteurs du palais. C'est une occasion rare pour nous d'avoir une compagnie intrigante pour de tels événements. Nous rendrez-vous visite ? Venez, s'il vous plaît, nous serions ravis.";
			link.l1 = "Je serais honoré, mademoiselle. Je vous rendrai visite ce soir.";
			link.l1.go = "girl_3";
			link.l2 = "Excusez-moi, mademoiselle, mais j'ai des affaires urgentes à régler. Une autre fois, peut-être ?";
			link.l2.go = "girl_exit";
		break;
		
		case "girl_exit":
			dialog.text = "Dommage. Je devrai trouver quelqu'un d'autre pour me tenir compagnie, ainsi qu'à mes amies... Adieu.";
			link.l1 = "Adieu.";
			link.l1.go = "girl_exit_1";
		break;
		
		case "girl_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 40.0);
			npchar.lifeday = 0;
			FMQT_ClearChest();
		break;
		
		case "girl_3":
			dialog.text = "Merci! Je vous promets, ce sera une nuit que vous n'oublierez jamais, monsieur! Au revoir!";
			link.l1 = "À bientôt...";
			link.l1.go = "girl_4";
		break;
		
		case "girl_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 40.0);
			npchar.lifeday = 0;
			pchar.questTemp.FMQT = "begin_serveroom";
			FMQT_Begin();
			AddQuestRecord("FMQ_Tortuga", "1");
		break;
		
		case "girl_5":
			DelMapQuestMarkCity("Tortuga");
			LAi_SetImmortal(npchar, false);
			DelLandQuestMark(npchar);
			LAi_RemoveLoginTime(npchar);
			FMQT_FillChest();
			PlaySound("Voice\English\Girls_1.wav");
			dialog.text = "Eh là, matelot ! Quel bon vent t'amène ici aujourd'hui ? On voit rarement d'aussi beaux hommes à Tortuga.";
			link.l1 = "Bonjour à vous aussi, mademoiselle, vous êtes sur le point de me faire rougir avec vos compliments. Je suis capitaine de mon propre navire et un homme occupé, mais je suis sûr que cette île peut offrir assez pour qu'un vagabond sauvage comme moi reste diverti.";
			link.l1.go = "girl_6";
		break;
		
		case "girl_6":
			dialog.text = "(rire) Oh oui monsieur, je suis sûre que nous pouvons vous aider avec ça ! Tortuga a toujours quelque chose à offrir. Moi aussi... Pourquoi, je suis capable de faire presque *n'importe quoi* après avoir entendu une bonne histoire de mer. Je les adore tellement ! Un capitaine m'a raconté une fois une histoire incroyable sur la façon dont il a réussi à échapper à l'abandon sur une île déserte en construisant un radeau avec des tortues de mer. Quel galant ! Pourriez-vous ?";
			link.l1 = "Pourrais-je quoi ?";
			link.l1.go = "girl_7";
		break;
		
		case "girl_7":
			dialog.text = "(rire) Pourrais-tu fabriquer un radeau avec des tortues de mer ?";
			link.l1 = "Je ferai mieux. Une fois, avec un apprenti en fuite, nous avons capturé le navire le plus rapide de la marine anglaise à l'aide d'une simple hachette. Je peux aussi retenir mon souffle pendant dix minutes. Tu veux voir ?";
			link.l1.go = "girl_8";
		break;
		
		case "girl_8":
			dialog.text = "Peut-être plus tard. Je travaille comme serviteur dans le palais de notre gouverneur. Viens-y à six heures ce soir et trouve-moi, ainsi que mon ami, dans la tonnelle. Tu pourras alors nous raconter toutes tes aventures...";
			link.l1 = "On dirait une invitation à raconter des histoires que je ne peux refuser. À ce soir, six heures.";
			link.l1.go = "girl_9";
			link.l2 = "S'introduire dans le palais du gouverneur ? Ça me paraît un peu audacieux pour mon goût. Je passe, ma chère. Trouve-moi à la taverne si tu veux la compagnie d'un vrai homme. Yo ho ho !";
			link.l2.go = "girl_exit_2";
		break;
		
		case "girl_exit_2":
			dialog.text = "Ph-f. Peu importe, je trouverai un homme meilleur et plus grand que toi alors. Ton braguette semble trop petite après tout. Bon débarras.";
			link.l1 = "Même un vaisseau de guerre semblerait petit en naviguant à travers votre Passage au Vent.";
			link.l1.go = "girl_exit_1";
		break;
		
		case "girl_9":
			dialog.text = "J'ai hâte de voir ça !";
			link.l1 = "...";
			link.l1.go = "girl_10";
		break;
		
		case "girl_10":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 40.0);
			npchar.lifeday = 0;
			pchar.questTemp.FMQT = "begin_bedroom";
			FMQT_Begin();
			AddQuestRecord("FMQ_Tortuga", "2");
		break;
		
		case "wife":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_01.wav");
			dialog.text = "Ah te voilà ! Capitaine "+GetFullName(pchar)+" ! Je suis si heureux de vous rencontrer, cela fait longtemps que je n'ai pas été honoré par la visite d'une telle noblesse et prestance !";
			link.l1 = "C'est un grand honneur et un plaisir pour moi d'être ici en votre compagnie, madame. Mais qu'en est-il des autres invités ? Suis-je trop tôt ?";
			link.l1.go = "wife_1";
		break;
		
		case "wife_1":
			dialog.text = "Oh, ils sont indisposés et ne peuvent pas venir. Mais ne pensons pas à eux, buvons du vin et parlons... Ah, si seulement tu savais à quel point je m'ennuie et je me sens seule ici ! Tortuga est un repaire sordide rempli de racaille, de vauriens et de pirates ! Des pirates ! Et enfin, un gentilhomme digne dans ma maison ! J'aimerais que mon mari fasse plus d'affaires avec des hommes de votre classe et de vos talents ! Mais non, rien que des pirates, des pirates partout ! Avez-vous entendu parler de cette nouvelle mode qui devient populaire à Paris à la cour royale de Sa Majesté ? Quel est votre avis à ce sujet ?";
			link.l1 = "Je suis désolé, mon avis sur quoi exactement ? Les pirates ? Ou la mode ?";
			link.l1.go = "wife_2";
		break;
		
		case "wife_2":
			dialog.text = "Oh monsieur, vous me comprenez si bien ! Je n'arrive même pas à y croire. Mon mari me donne des sous pendant qu'il fait des MILLIONS avec ses pirates, imaginez ça ! Des pirates ! Je dois commander des robes livrées ici dans ce trou sale, mais quand elles arrivent ici, elles sont déjà démodées depuis six mois ! Comment une femme de mon rang peut-elle porter de tels haillons ? Oh, je veux tellement voir et porter ces modes de Paris ! Pensez-vous que je serais ravissante dedans ?";
			link.l1 = "Madame, vous êtes fort ravissante. Vous n'avez point besoin de modes de Paris pour cela, c'est déjà évident pour chaque homme de cette belle île.";
			link.l1.go = "wife_3";
		break;
		
		case "wife_3":
			dialog.text = "Vous êtes trop aimable avec moi... Capitaine, je dois avouer que je suis dans de grands ennuis. Mais vous aiderez une pauvre femme, n'est-ce pas ?";
			link.l1 = "Bien sûr, madame. Tout ce que vous désirez.";
			link.l1.go = "wife_4";
		break;
		
		case "wife_4":
			dialog.text = "Doucement là, monsieur capitaine, ou je vais perdre la tête ! (rire coquet) Mon mari ne me donne pas un seul centime ces temps-ci. Ce brute ramène des prostituées ordinaires chez nous et ne me prête aucune attention !\nJe sais où il cache une partie de son trésor mal acquis, c'est dans un coffre dans son bureau. C'est mon argent par le droit d'une épouse et d'une femme. Aidez-moi à récupérer ce qu'il me doit et vous serez récompensé... Avec de l'or et... d'autres délices.";
			link.l1 = "C'est une offre intrigante. Très bien, madame, je vais vous aider. Où est ce coffre et comment puis-je l'ouvrir ?";
			link.l1.go = "wife_5";
			link.l2 = "Très bien, madame, je vous apporterai le contenu du coffre. Nous obtiendrons l'argent et nous aurons une très agréable 'conversation' ensemble après. Quel homme pourrait refuser une telle offre ? Où se trouve ce coffre et comment l'ouvrir ?";
			link.l2.go = "wife_6";
			link.l3 = "Madame, vous essayez de me séduire. Je suis désolé, mais mon honneur exige que je décline votre offre. Vous avez toute ma sympathie, vous méritez mieux, mais vous devrez trouver un autre acteur pour votre pièce.";
			link.l3.go = "wife_exit";
		break;
		
		case "wife_exit":
			dialog.text = "Quel dommage. Nous n'avons plus rien à nous dire alors, monsieur. Partez et souvenez-vous : si vous dites un mot de cela à mon mari, vous le regretterez !";
			link.l1 = "Adieu.";
			link.l1.go = "wife_exit_1";
		break;
		
		case "wife_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "questTemp.FMQT.Common");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			pchar.questTemp.FMQT = "huber";
			pchar.quest.FMQT_late1.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late1.win_condition.l1.date.hour  = 18.0;
			pchar.quest.FMQT_late1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late1.function = "FMQT_HuberTime";
			AddQuestRecord("FMQ_Tortuga", "4");
		break;
		
		case "wife_5":
			pchar.questTemp.FMQT.Honour = "true"; // вар 1
			dialog.text = "Je ne m'attendais pas à cela de ta part... Le coffre... Laisse-le pour plus tard, d'abord, nous devons trouver une clé duplicata qui a été volée par un sale pirate. Il est en train de se débaucher en ce moment dans un tripot local, buvant comme un cochon. Hâte-toi et rapporte-moi la clé duplicata. Je t'attendrai.";
			link.l1 = "Pas de perte de temps alors !";
			link.l1.go = "wife_7";
		break;
		
		case "wife_6":
			pchar.questTemp.FMQT.Bed = "true"; // вар 2 
			dialog.text = "Tu ne regretteras pas cela, capitaine. D'abord, nous devons retrouver un double de la clé qui a été volé par un sale pirate. Il est en train de se saouler dans une taverne locale, buvant comme un cochon. Fais vite et rapporte-moi le double de la clé. Je t'attendrai.";
			link.l1 = "Pas de temps à perdre alors !";
			link.l1.go = "wife_7";
		break;
		
		case "wife_7":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "FMQT_PirateInTavern", 10.0);
			pchar.quest.FMQT_late2.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late2.win_condition.l1.date.hour  = 0.0;
			pchar.quest.FMQT_late2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late2.function = "FMQT_TavernTime";
			AddQuestRecord("FMQ_Tortuga", "6");
		break;
		
		case "wife_8":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_01.wav");
			dialog.text = "Capitaine "+GetFullName(pchar)+"! Oh là là ! Quel homme dans mes appartements privés ! Es-tu surpris ? Tu es le seul invité ici ce soir. (rire)";
			link.l1 = "Je suis surpris, madame. Mais cela ne me dérange pas du tout. S'agit-il de affaires ou de plaisir ?";
			link.l1.go = "wife_9";
		break;
		
		case "wife_9":
			dialog.text = "Quelle approche directe ! J'aime les hommes comme vous. J'ai une proposition d'affaire pour vous, capitaine. Je trouverai un moyen de compenser vos efforts si vous réussissez.";
			link.l1 = "Continue.";
			link.l1.go = "wife_10";
		break;
		
		case "wife_10":
			dialog.text = "Ah... Mon mari a un coffre plein d'argent et de bijoux. Je le déteste et je veux une plus grande allocation pour mes peines.";
			link.l1 = "Madame, vous êtes ravissante. Vous n'avez pas besoin de plus de bijoux ou de modes de Paris pour cela, c'est déjà évident pour chaque homme à Hispaniola.";
			link.l1.go = "wife_11";
		break;
		
		case "wife_11":
			dialog.text = "Vous êtes trop bon avec moi... Capitaine, je dois avouer, je suis dans un grand pétrin. Aurez-vous l'amabilité d'aider une femme en détresse ?";
			link.l1 = "Bien sûr, madame. L'honneur l'exige. Tout ce que vous désirez.";
			link.l1.go = "wife_12";
		break;
		
		case "wife_12":
			dialog.text = "Doucement, monsieur capitaine, ou je vais perdre la tête ! (rire coquet) Mon mari ne me donne pas un seul centime ces temps-ci. Ce brute ramène des garces communes chez nous et ne me prête aucune attention !\nJe sais où il cache une partie de ses trésors mal acquis, c'est dans un coffre dans son bureau. Cet argent m'appartient de droit en tant qu'épouse et femme. Aidez-moi à récupérer ce qu'il me doit et vous serez récompensé... Avec de l'or et... d'autres choses délicieuses.";
			link.l1 = "D'accord. Je vais le faire. Où est ce coffre et comment l'ouvrir ?";
			link.l1.go = "wife_13";
			link.l2 = "Ha ! Pas de questions là-dessus, je peux le faire pour une femme comme toi. Tu ne le regretteras pas, ma chère. Nous obtiendrons l'argent et passerons un moment très agréable ensemble. Où est ce coffre et comment l'ouvrir ?";
			link.l2.go = "wife_14";
			link.l3 = "Pas moi, madame. Je ne suis pas un gentilhomme à cocufier et dépouiller un homme en une seule nuit. Pas de cette manière, en tout cas. Trouvez-vous un autre acteur pour cette pièce.";
			link.l3.go = "wife_exit_2";
		break;
		
		case "wife_13":
			pchar.questTemp.FMQT.Honour = "true"; // вар 1
			dialog.text = "Oh... Je t'apprécie de plus en plus... D'abord, nous devrions récupérer un double de clé qui a été volé par un sale pirate. Il est en train de faire la fête dans un repaire local, buvant comme un cochon. Dépêche-toi et rapporte-moi le double. Je t'attendrai.";
			link.l1 = "Ne perdons pas de temps alors !";
			link.l1.go = "wife_7";
		break;
		
		case "wife_14":
			pchar.questTemp.FMQT.Bed = "true"; // вар 2 
			dialog.text = "Garde ton calme, monsieur, il y aura bien le temps pour ça plus tard. (rire) D'abord, nous devons récupérer une clé en double qui a été volée par un sale pirate. Il est en train de festoyer dans une taverne locale, buvant comme un cochon. Hâte-toi et rapporte-moi le double. Je t'attendrai. Tu es sûr de pouvoir gérer ça ?";
			link.l1 = "Ne doutez pas de moi, je suis déjà en route.";
			link.l1.go = "wife_7";
		break;
		
		case "wife_exit_2":
			dialog.text = "Bâtard pudibond ! Hors de ma vue ! Et n'ose même pas le dire à mon mari, sinon tu le regretteras !";
			link.l1 = "Adieu, ma douce.";
			link.l1.go = "wife_exit_1";
		break;
		
		case "wife_15":
			DelLandQuestMark(npchar);
			pchar.quest.FMQT_late3.over = "yes";
			dialog.text = "Capitaine ! As-tu obtenu la clef ?";
			link.l1 = "Oui, je l'ai. Où est le coffre ?";
			link.l1.go = "wife_16";
		break;
		
		case "wife_16":
			dialog.text = "Oh ! Mon ignoble mari va-t-il vraiment obtenir ce qu'il mérite ? Vous êtes un homme incroyable, capitaine ! Un grand avenir vous attend, le saviez-vous ? Oubliez le coffre. Je le ferai moi-même. Venez me voir demain pour obtenir votre récompense. Vous ne le regretterez pas, capitaine...";
			link.l1 = "D'accord. Fais comme tu veux. J'ai hâte de te voir demain.";
			link.l1.go = "wife_17";
			link.l2 = "Non, je suis un homme occupé et je n'ai pas envie de perdre du temps à attendre. Pourquoi attendre ? Dis-moi ce qu'il faut faire et je le ferai. Je ne peux pas laisser une si belle femme gâcher ses jolies petites mains à s'embêter avec une serrure et une clé.";
			link.l2.go = "wife_18";
		break;
		
		case "wife_17":
			RemoveItems(pchar, "kaleuche_key", 1);
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key");
			dialog.text = "Viens me voir avant six heures, mon vaillant chevalier...";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_Deceive");
		break;
		
		case "wife_18":
			dialog.text = "Es-tu sûr? Cela pourrait être dangereux pour toi. Pourquoi veux-tu risquer ta vie, capitaine?";
			link.l1 = "Soit. Fais à ta guise. J'ai hâte de te voir demain.";
			link.l1.go = "wife_17";
			link.l2 = "J'ai déjà pris ma décision. Que dois-je faire exactement ?";
			link.l2.go = "wife_19";
		break;
		
		case "wife_19":
			dialog.text = "Un cœur de lion !... Allez dans le bureau de mon mari, vous y trouverez le coffre. Utilisez la clé dupliquée. Personne n'est là-haut à cette heure de la nuit, alors prenez votre temps. Il y a... des diamants dans ce coffre. Un grand nombre d'entre eux. Prenez-les tous et revenez vers moi. Je vous attendrai. Ne trahissez pas ma confiance... je vous en prie.";
			link.l1 = "Je reviendrai bientôt.";
			link.l1.go = "wife_20";
		break;
		
		case "wife_20":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("FMQ_Tortuga", "11");
			sld = &Locations[FindLocation("Tortuga_townhallRoom")];
			sld.private2.key = "kaleuche_key"; // допуск к сундуку
			pchar.questTemp.FMQT = "chest";
		break;
		
		case "wife_21":
			DelLandQuestMark(npchar);
			pchar.quest.FMQT_GemsTimeOver.over = "yes";
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_02.wav");
			dialog.text = "Oh, capitaine ! Je... Vous... C'est fait ? Oh et qui est-ce ?! A-ah !";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_MercenAttackRoom");
		break;
		
		case "wife_22":
			dialog.text = "Oh là là ! Capitaine, vous m'avez sauvé ! Vous... vous êtes mon héros ! C'était le sbire de mon mari, il voulait vous tuer ! Je l'ai supplié de ne pas le faire ! Êtes-vous blessé ? Avez-vous apporté les diamants ?";
			link.l1 = "Ha. Vraiment? Ton mari est un homme jaloux... Peu importe. Au diable avec lui, j'ai les pierres.";
			link.l1.go = "wife_23";
		break;
		
		case "wife_21x":
			DelLandQuestMark(npchar);
			pchar.quest.FMQT_GemsTimeOver.over = "yes";
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_02.wav");
			dialog.text = "Oh capitaine ! Je... Vous... Est-ce fait ?";
			link.l1 = "Il y a eu une petite complication, mais c'est réglé maintenant. Pourquoi êtes-vous pâle, madame? Vous allez bien? J'ai les bijoux, cela devrait vous remonter le moral, n'est-ce pas?";
			link.l1.go = "wife_23";
		break;
		
		case "wife_23":
			dialog.text = "Dieu merci ! Je suis vengé ! Mon chevalier ! Combien de diamants y avait-il ?";
			if (GetCharacterItem(pchar, "jewelry2") >= 100)
			{
				link.l1 = "Ton chevalier est de retour de son aventure avec un sac plein de butin. Il en laissera la moitié à sa dame pour qu'elle puisse acheter les meilleures modes de Paris. J'ai tenu ma promesse envers toi.";
				if (CheckAttribute(pchar, "questTemp.FMQT.Honour")) link.l1.go = "wife_25";
				else link.l1.go = "wife_26";
			}
			else
			{
				link.l1 = "Oh, il y avait plein de diamants mais tu n'auras rien. Tu as engagé un assassin pour me tuer, espèce de putain ! Crois-tu vraiment que je partagerais avec toi après tout ça ? Ouvre la bouche à ce sujet et ton mari apprendra ton plan pour le voler et le cocufier. Alors, garde-la fermée.";
				link.l1.go = "wife_24";
			}
		break;
		
		case "wife_24":
			PlaySound("Voice\English\LE\Marselina\Marselina_Levasser_03.wav");
			dialog.text = "Canaille ! Salaud ! Tu ne t'en sortiras pas comme ça !";
			link.l1 = "Oui, j'ai déjà entendu celle-là.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_FinalNoJewelry");
		break;
		
		case "wife_25":
			RemoveItems(pchar, "jewelry2", 100);
			Log_Info("You have given diamonds");
			PlaySound("interface\important_item.wav");
			dialog.text = "Tu n'es pas comme... les autres. Tu obtiens ce que tu veux. Un brillant avenir t'attend. Je sais que tu es un homme occupé mais... Restera-tu avec moi un moment ? Personne ne nous dérangera, je te le promets.";
			link.l1 = "J'ai toujours du temps pour une belle femme comme vous. Dois-je ouvrir une bouteille du vin de votre mari ?";
			link.l1.go = "wife_sex";
		break;
		
		case "wife_sex":
			DialogExit();
			LAi_SetActorType(npchar);
			pchar.questTemp.HorseQty = int(pchar.questTemp.HorseQty) + 1;
			DoQuestCheckDelay("PlaySex_1", 1.0);
			
			// Rebbebion, для "Путеводной звезды"
			pchar.questTemp.FMQT.GiveDiamonds = true;
			pchar.questTemp.FMQT.Marceline = "Fuck"; 
		break;
		
		case "wife_26":
			RemoveItems(pchar, "jewelry2", 100);
			Log_Info("You have given diamonds");
			PlaySound("interface\important_item.wav");
			dialog.text = "Je pense que je peux vivre sans eux. Il y a tant de moyens de dépenser de l'argent ici. Tant d'hommes beaux et dignes à Tortuga... Merci pour tout, capitaine. Juste pour que vous le sachiez, veuillez garder le silence sur cette affaire ou mon mari vous fera pendre à une potence. Ce n'est pas un homme bon. Adieu.";
			link.l1 = "Comme ça? Ce fut une expérience instructive. Adieu, madame, je vous suggère de garder cela secret aussi, je ne suis pas un homme de bien non plus. Mais vous le savez déjà, n'est-ce pas?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQT_FinalNoSex");
			
			// Rebbebion, для "Путеводной звезды"
			pchar.questTemp.FMQT.GiveDiamonds = true;
			pchar.questTemp.FMQT.Marceline = "NoFuck"; 
		break;
		
		case "wife_27":
			PlaySound("Voice\English\Girls_2.wav");
			dialog.text = "Qui es-tu et que fais-tu ici ?";
			link.l1 = "Qu'est-ce que tu mijotes? Nous avions un accord...";
			link.l1.go = "wife_28";
		break;
		
		case "wife_28":
			dialog.text = "Quel accord, monsieur ? Je suis une femme mariée, je ne fais pas affaire avec d'autres hommes ! Quittez mes appartements maintenant ou j'appelle mon mari et ses gardes !";
			link.l1 = "Ainsi soit-il, hein ? Très bien, je crois que je vais éclairer votre bon mari dans ce cas !";
			link.l1.go = "wife_29";
		break;
		
		case "wife_29":
			dialog.text = "Pars maintenant, vaurien insolent, ou mes hommes te jetteront dans l'oubliette du Fort La Roche ! Je me fiche de tes menaces ! Va-t'en !";
			link.l1 = "... ";
			link.l1.go = "wife_30";
		break;
		
		case "wife_30":
			DialogExit();
			DoQuestReloadToLocation("Tortuga_town", "reload", "reload3", "FMQT_FinalFail");
			pchar.questTemp.FMQT.Marceline = "Deception"; // Rebbebion, для "Путеводной звезды"
		break;
		
		case "pirate":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\tavern\Pyanici-03.wav");
			pchar.quest.FMQT_late2.over = "yes";
			FreeSitLocator("Tortuga_tavern", "sit_base2");
			dialog.text = "Qui es-tu? Ah, peu importe. Ne fais pas confiance aux femmes, l'ami. Comme dit la Bible... même la plus sotte des catins peut t'entraîner au fond de l'Enfer avec leurs man-manipulations. Prends un siège, camarade, bois un verre!";
			link.l1 = "Avec plaisir !";
			link.l1.go = "pirate_1x";
		break;
		
		case "pirate_1x":
			DialogExit();
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "sit", "sit_base2");
			LAi_SetSitType(pchar);
			npchar.Dialog.currentnode = "pirate_1";
			LAi_SetActorType(npchar);
			LAi_ActorSetSitMode(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 2.0);
		break;
		
		case "pirate_1":
			PlaySound("Voice\English\tavern\Pyanici-05.wav");
			dialog.text = "Qu'est-ce que tu regardes ? Sers donc à boire !!";
			link.l1 = "À la tienne !.. Hé l'ami, je ne vais pas perdre de temps ici. J'ai besoin de ce double de clé que tu as, tu sais de quoi je parle. Donne-le-moi et nous nous séparerons : tu continueras à boire et moi à aider les demoiselles en détresse.";
			link.l1.go = "pirate_2";
		break;
		
		case "pirate_2":
			dialog.text = "Aww matey! N'as-tu rien écouté de ce que je viens de dire ! Tu dois paraître plus intelligent que tu ne l'es vraiment... à travailler pour cette putain. Tu sais qui est son mari ? Récemment, le gouverneur Levasseur a envoyé son fidèle nègre Kampacho aller 'parler' à un marchand local et très respecté. Le noir a battu ce pauvre bougre à mort dans sa propre boutique ! Ce marchand avait manifesté une sorte de léger manque de respect envers la femme du gouverneur lors d'un bal ou quelque chose. Et cette même garce m'a séduit avec son apparence et ses doublons\nLa clé en double existe. J'étais un bon crocheteur de coffres en France, donc c'était un jeu d'enfant. Si ce n'était pas pour la fille du commandant de Lyon... je ne serais jamais devenu pirate. Bah ! Merde alors !";
			link.l1 = "C'est bien triste tout ça, mais parlons affaires. Où est la clé ?";
			link.l1.go = "pirate_3";
		break;
		
		case "pirate_3":
			dialog.text = "Tu écoutes ? Je suis hors du jeu, mon vieux ! J'ai été assez malin pour voir ce qui se prépare ! Je quitte cet endroit pour toujours dès que mon navire sera prêt à prendre la mer. Tu veux la clé, paie pour elle. Ne sois pas avare ici, je pense que tu n'auras plus besoin d'argent très bientôt.";
			link.l1 = "Tu sais, tu as raison. Je ne veux pas être le jouet d'une femme. Merci pour le conseil et prends garde en mer !";
			link.l1.go = "pirate_4";
			link.l2 = "Payer pour ça ? À toi ? Tu es un voleur pathétique et un lâche. Tu aurais dû rester dans ce trou à rats de Lyon. Qui sait, peut-être que le commandant local aurait eu pitié de toi et aurait laissé un voleur dégénéré devenir son beau-fils. Moi, je n'aurai certainement pas pitié de toi. Tu peux me donner la clé de la manière douce ou difficile, à toi de choisir.";
			link.l2.go = "pirate_5";
			link.l3 = "(soupir) Combien?";
			link.l3.go = "pirate_6";
		break;
		
		case "pirate_4":
			dialog.text = "Garçon astucieux, c'est la bonne décision, matey. Bonne chance. J'espère que tu trouveras un jour une femme véritable et aimante. De préférence une rousse ou une blonde, ai-je raison ?";
			link.l1 = "Adieu, camarade...";
			link.l1.go = "pirate_exit";
		break;
		
		case "pirate_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "tables", "stay8");
			LAi_SetPlayerType(pchar);
			pchar.questTemp.FMQT = "huber";
			pchar.quest.FMQT_late1.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late1.win_condition.l1.date.hour  = 18.0;
			pchar.quest.FMQT_late1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late1.function = "FMQT_HuberTime";
			AddQuestRecord("FMQ_Tortuga", "9");
		break;
		
		case "pirate_5":
			dialog.text = "Tu m'insultes ! Tire l'épée, salaud !";
			link.l1 = "Voyons voir comment tu peux forcer des coffres sans bras !";
			link.l1.go = "pirate_duel";
		break;
		
		case "pirate_duel":
			DialogExit();
			LAi_SetSitType(npchar);
			// ключ квестовый от Калеуче - вернуть назад
			GiveItem2Character(npchar, "kaleuche_key");
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key_FMQT");
			i = int(MOD_SKILL_ENEMY_RATE/4);
			pchar.questTemp.FMQT = "duel";
			PChar.questTemp.duel.enemy = NPChar.id;
			if (MOD_SKILL_ENEMY_RATE > 2) PChar.questTemp.duel.enemyQty = i;
			AddDialogExitQuestFunction("Duel_Prepare_Fight");
		break;
		
		case "pirate_6":
			dialog.text = "Vous êtes un homme d'affaires, je vous l'accorde. Vous pourriez bien réussir. Cinquante doublons. Sur la table.";
			link.l1 = "Cinquante pièces d'or ? Pour un morceau d'étain ? Qu'on me passe au fil de la quille. Pose la clé sur la table. Maintenant.";
			link.l1.go = "pirate_7";
			if (PCharDublonsTotal() >= 50)
			{
				link.l2 = "Quel sacré prix... D'accord. Prends-les.";
				link.l2.go = "pirate_8";
			}
			else
			{
				link.l2 = "Assez cher... D'accord. Je les apporterai bientôt. Reste ici.";
				link.l2.go = "pirate_wait";
			}
		break;
		
		case "pirate_wait":
			DialogExit();
			AddLandQuestMark(npchar, "questmarkmain");
			LAi_SetSitType(npchar);
			npchar.Dialog.currentnode = "pirate_dublon";
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "tables", "stay8");
			LAi_SetPlayerType(pchar);
		break;
		
		case "pirate_dublon":
			NextDiag.TempNode = "pirate_dublon"; // mitrokosta правка явного бага
			dialog.text = "As-tu apporté cinquante doublons ?";
			link.l1 = "Tu sais, je pense que tu peux vivre sans eux. La clé. Sur la table.";
			link.l1.go = "pirate_7";
			if (PCharDublonsTotal() >= 50)
			{
				link.l2 = "Ouais. Prends-les.";
				link.l2.go = "pirate_8";
			}
			else
			{
				link.l2 = "Je les reçois encore.";
				link.l2.go = "exit";
			}
		break;
		
		case "pirate_7":
			dialog.text = "Voulez-vous danser ?";
			link.l1 = "Je mènerai.";
			link.l1.go = "pirate_duel";
		break;
		
		case "pirate_8":
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(50);
			Log_Info("You have given 50 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Bien. Utilise ta cervelle et tu pourrais sortir de là avec quelques piastres et ta tête. Prends la clé et écoute mon conseil. Gratuitement. La femme de Levasseur est bête comme un poisson mais elle se croit rusée. Ne lui fais pas confiance. Garde ton braquemart dans ton froc et surveille tes poches. Elle n'est pas vraiment une adversaire, sois juste prudent et évite d'impliquer son mari dans cette affaire\nUne dernière chose - il y a un coffre dans son boudoir où elle garde ses babioles, facile à crocheter. Elle y mettra sa part. Tu m'as bien entendu. Sois prudent en mer, frère. Souviens-toi, les frères avant les catins.";
			link.l1 = "Bon vent, compère...";
			link.l1.go = "pirate_9";
		break;
		
		case "pirate_9":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_Fade("", "");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "tables", "stay8");
			LAi_SetPlayerType(pchar);
			pchar.questTemp.FMQT = "key";
			pchar.questTemp.FMQT.Caution = "true";
			FMQT_KeyNextDay();
			pchar.quest.FMQT_late3.win_condition.l1 = "Timer";
			pchar.quest.FMQT_late3.win_condition.l1.date.hour  = int(GetTime());
			pchar.quest.FMQT_late3.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQT_late3.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQT_late3.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQT_late3.function = "FMQT_KeyTime";
			AddQuestRecord("FMQ_Tortuga", "10");
			// ключ квестовый от Калеуче - вернуть назад
			GiveItem2Character(pchar, "kaleuche_key");
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key_FMQT");
		break;
		
		case "mercen":
			PlaySound("Voice\English\EvilPirates10.wav");
			dialog.text = "Sapristi ! Je ne m'attendais pas à ça... au diable cette femme ! Mon maître m'avait dit d'éviter son genre. Mais un boulot est un boulot. Je t'aurai quand même.";
			link.l1 = "Eh bien, eh bien, camarade... On dirait qu'elle voulait nous tromper tous les deux, je ne suis pas surpris. Pourquoi devrions-nous continuer à nous battre ? Tu cherches un emploi ? J'en ai un. Tu as du talent, j'ai besoin d'hommes comme toi dans mon équipage. Repas, couchette, salaire régulier, rhum, et une part équitable de tout butin. Je te donne ma parole. Que diras-tu ?";
			//if(CheckCharacterPerk(pchar, "IronWill") || CheckCharacterPerk(pchar, "HT2") || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 34 || GetSummonSkillFromName(pchar, SKILL_FORTUNE) > 20) link.l1.go = "mercen_1";
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 34) link.l1.go = "mercen_1";
			else link.l1.go = "mercen_4";
		break;
		
		case "mercen_1":
			//if(CheckCharacterPerk(pchar, "IronWill")) notification("Iron Will", "IronWill");
			//if(CheckCharacterPerk(pchar, "HT2")) notification("Mimicry", "Mimicry");
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 34) notification("Skill Check Passed", SKILL_LEADERSHIP);
			//if(GetSummonSkillFromName(pchar, SKILL_FORTUNE) > 20) notification("Skill Check Passed", SKILL_FORTUNE);
			dialog.text = "Tu as la langue bien pendue et ta renommée te précède, cap'taine, je te l'accorde. Oui, je suis partant. Comment s'appelle ton navire ?";
			link.l1 = "' "+pchar.ship.name+"'. Parle au contremaître, il te trouvera une couchette. Bienvenue à bord !";
			link.l1.go = "mercen_2";
		break;
		
		case "mercen_2":
			dialog.text = "Ha ! Je grimpe dans le monde. Donne un coup de pied à cette garce pour moi.";
			link.l1 = "...";
			link.l1.go = "mercen_3";
		break;
		
		case "mercen_3":
			DialogExit();
			LAi_group_Delete("EnemyFight");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "FMQT_MercenHire", 10.0);
			AddQuestRecord("FMQ_Tortuga", "17");
		break;
		
		case "mercen_4":
			//if(!CheckCharacterPerk(pchar, "IronWill")) notification("Perk check failed", "IronWill");
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 35) notification("Skill Check Failed (35)", SKILL_LEADERSHIP);
			//if(GetSummonSkillFromName(pchar, SKILL_FORTUNE) < 21) notification("Skill Check Failed (21)", SKILL_FORTUNE);
			dialog.text = "Tu parles gentiment. Mais pas assez gentiment si tu veux que de vrais professionnels rejoignent tes rangs. Garde cela à l'esprit pour l'avenir. Si tu en as un.";
			link.l1 = "Essaye donc. Fais vite, j'ai un rendez-vous avec une dame.";
			link.l1.go = "mercen_5";
			link.l2 = "Aucune seconde chance aujourd'hui. Je suis un homme occupé alors ne gachons pas le tapis. On ne te paie pas assez pour mourir pour une petite putain de rien du tout. Si tant est qu'on te paie.";
			link.l2.go = "mercen_6";
		break;
		
		case "mercen_5":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FMQT_MercenDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "mercen_6":
			dialog.text = "Tu as raison. Personne ne m'a payé... encore. Je vais régler ça tout de suite. Fais ce que tu veux...";
			link.l1 = "... ";
			link.l1.go = "mercen_7";
		break;
		
		case "mercen_7":
			DialogExit();
			LAi_SetCurHPMax(npchar); 
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_group_Delete("EnemyFight");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
			AddQuestRecord("FMQ_Tortuga", "18");
			pchar.questTemp.FMQT.Roomfight = "true";
			FMQT_WifeFinalTalk();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
