// отец Винсенто
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "santiago")
			{
				dialog.text = "Enfin, je vois le célèbre capitaine français "+GetFullName(pchar)+" en chair et en os. J'ai entendu beaucoup de choses sur vos exploits. Vous êtes un brave soldat et, j'espère, un fils loyal et fidèle de notre Mère la Sainte Église Catholique Romaine. Asseyez-vous, mon fils. Pas besoin de rester debout à cause de moi. Dominus vobiscum ! ";
				link.l1 = "Et cum spiritu tuo, Votre Excellence. Mon chemin ici fut long et ardu... Per aspera ad astra et tout...";
				link.l1.go = "utensil";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "twoitems" && !CheckAttribute(npchar, "quest.skinmap"))
			{
				dialog.text = "Oui, je vois dans vos yeux que vous avez des nouvelles pour moi. Vous avez toute mon attention.";
				link.l1 = "Votre Excellence, j'ai trouvé votre secrétaire disparu...";
				link.l1.go = "guardoftruth";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "mayak")
			{
				dialog.text = "As-tu apporté des nouvelles de San Jose, mon fils ?";
				link.l1 = "Oui, Votre Excellence. J'ai déterminé ce qui est arrivé à notre connaissance commune Miguel Dichoso et à sa frégate perdue. Dès que son navire a pénétré dans l'Atlantique en route pour l'Espagne, il a été immédiatement pris dans un coup de vent contraire et ramené dans les Caraïbes.";
				link.l1.go = "guardoftruth_10";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "begin")
			{
				dialog.text = "Paix avec vous, mon fils... Que puis-je faire pour vous ?";
				link.l1 = TimeGreeting()+", Votre Excellence. Avez-vous des nouvelles concernant notre arrangement ?";
				link.l1.go ="guardoftruth_17";
				break;
			}
			dialog.text = "Y a-t-il quelque chose que tu voulais, mon fils ?";
			link.l1 = "Non, rien, Père.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "utensil":
			dialog.text = "'Enter by the narrow gate; for wide is the gate and broad is the way that leads to destruction, and there are many who go in by it. Because narrow is the gate and difficult is the way which leads to life, and there are few who find it.' The path of righteousness is always difficult, my son. But the aim that is achieved fully rewards a righteous man for his works.";
			link.l1 = "Je suis d'accord, Votre Excellence. J'ai accompli les tâches que vous m'avez confiées. Vous avez déjà le lâche pirate qui a volé les précieux vases de l'Église. Maintenant, je vous rends toutes les choses qui ont été prises : l'ostensoir, la croix et l'encensoir. Prenez-les pour la paroisse de Santiago.";
			link.l1.go = "utensil_1";
		break;
		
		case "utensil_1":
			RemoveItems(pchar, "jewelry33", 1);
			RemoveItems(pchar, "jewelry34", 1);
			RemoveItems(pchar, "jewelry35", 1);
			dialog.text = "Benedicite ! Je vous remercie du fond du cœur pour votre fidèle service à la Sainte Mère Église et à la paroisse de Santiago, mon fils. Vos œuvres ne resteront pas sans récompense. Les paroissiens ont collecté une offrande pour le courageux guerrier qui a récupéré leurs objets volés, et je vous la remets volontiers en leur nom. 'L'ouvrier mérite son salaire.'";
			link.l1 = "Merci, Votre Excellence. Quelle agréable surprise !";
			link.l1.go = "utensil_2";
		break;
		
		case "utensil_2":
			GiveItem2Character(pchar, "chest");
			Log_Info("You've received a chest of doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Un service fidèle à la Sainte Mère Église est toujours fidèlement récompensé, "+pchar.name+". J'espère pour ma part que vous resterez un guerrier dévoué à la défense et à la protection de la chrétienté, car une menace mortelle plane au-dessus de nous comme la mythique épée de Damoclès.";
			link.l1 = "Que pourrait-ce être, Votre Excellence ?";
			link.l1.go = "utensil_3";
		break;
		
		case "utensil_3":
			dialog.text = "Peut-être es-tu destiné à être notre champion dans la bataille à venir contre les puissances et principautés obscures de ce monde, mon fils, car il y a de nombreux signes et présages qu'un mal approche.";
			link.l1 = "Signes et présages ?";
			link.l1.go = "utensil_4";
		break;
		
		case "utensil_4":
			dialog.text = "Beaucoup, mon fils... L'un d'eux est ton désir de chercher l'or indien perdu du païen Tayasal, car ce qui est conservé dans leur trésor représente exactement ce qui est un danger pour le monde chrétien entier.";
			link.l1 = "Pourriez-vous m'éclairer un peu sur cet or, révérend Père ? J'ai déjà entendu parler de l'histoire de sa disparition, mais de quelle menace parlez-vous ?";
			link.l1.go = "utensil_5";
		break;
		
		case "utensil_5":
			dialog.text = "Écoute-moi bien, mon fils, et sache que tout ce que tu vas entendre est pour tes oreilles seulement. Bien avant que Miguel Dichoso ne prenne ce trésor païen de l'ancienne cité indienne, j'avais fait interroger un homme captif des Indiens Itza concernant notre mission dans les Caraïbes. Le peuple Itza est descendant des Mayas, un puissant empire perdu des siècles avant même que Cristobal Colon et ses hommes ne mettent le pied dans le Nouveau Monde. L'Empire Maya régnait sur les tribus environnantes d'une main de fer, avec un pouvoir indicible qui leur était accordé à travers des accords infernaux avec des démons. Des magies noires achetées avec le sang de générations de sacrifices humains. \nCet homme Itza connaissait Tayasal, une cité maya perdue et le mal incroyable encore scellé en elle. Il nous a dit tout ce qu'il savait. Si ces sceaux sont ouverts, les conséquences seraient apocalyptiques. Depuis ce moment, j'ai fait tout ce que je pouvais pour empêcher ce terrible mal de se réveiller. J'ai écrit à l'Escorial et à Rome en demandant désespérément de l'aide.\nIls ont écouté et ont envoyé Don Ramon de Mendoza y Riba, qui a établi sa base à Providence et commencé à chercher Tayasal. C'est alors que j'ai découvert que le bon Don Mendosa avait... des motivations différentes pour trouver la cité perdue. Plutôt que de prévenir la fin du monde, il cherchait à servir Mammon plutôt que le Christ.\nC'est pourquoi Dieu l'a abandonné et a envoyé l'ange de la mort dans son camp. Toutes ses actions étaient futiles et n'ont conduit qu'à la mort inutile de soldats espagnols et de convertis indiens fidèles. J'ai écrit à l'Escorial pour demander le renvoi de Ramon de Mendoza pour incompétence flagrante et ils ont accepté de le relever de ses fonctions, mais...";
			link.l1 = "Miguel Dichoso est arrivé.";
			link.l1.go = "utensil_6";
		break;
		
		case "utensil_6":
			if (CheckAttribute(pchar, "questTemp.Dolly")) sTemp = "Kukulcan?! Sancta Maria, Mater Dei, ora pro nobis! Kukulcan again, that old serpent...";
			else sTemp = "Hm...";
			dialog.text = "Précisément. Cet aventurier envoyé par le diable a trouvé Tayasal avec les trésors des anciens Mayas. Cependant, la joie de Don Mendosa fut de courte durée. Tous ces trésors ont disparu avec Dichoso en route vers l'Espagne. Il est probable qu'avec tous les lingots d'or et ornements, Miguel a emporté avec lui une source ancienne de diablerie, le masque terrifiant d'un ancien dieu-démon maya nommé Kukulcan.";
			link.l1 = sTemp+"Mais de quel mal parlez-vous, Votre Excellence ? Comment le savez-vous ?";
			link.l1.go = "utensil_7";
		break;
		
		case "utensil_7":
			dialog.text = "C'est un mal qui apporte la mort à tous les chrétiens baptisés des Caraïbes, du Nouveau Monde, et possiblement aussi de l'Ancien Monde. La fin viendra comme un voleur dans la nuit, et personne ne se rendra même compte de ce qui est arrivé. Et il y a déjà partout des signes avant-coureurs de cela !";
			link.l1 = "Quels présages ? Je ne comprends pas...";
			link.l1.go = "utensil_8";
		break;
		
		case "utensil_8":
			dialog.text = "Mon fils, es-tu vraiment si aveugle que tu ne les remarques même pas ? Elles se produisent depuis vingt-cinq ans, presque sans arrêt !";
			link.l1 = "Je voudrais humblement mentionner, Votre Excellence, que le cours de ma vie est énuméré à exactement cette durée, sans oublier que j'ai vécu la plupart de ma vie en Europe. Mon ignorance devrait être légèrement excusée.";
			link.l1.go = "utensil_9";
		break;
		
		case "utensil_9":
			dialog.text = "Je comprends, "+pchar.name+"Maintenant, n'avez-vous pas remarqué des choses étranges se produire dans les Caraïbes dès votre arrivée ici depuis l'Europe? Ne trouvez-vous pas étrange que la sorcellerie, la magie noire et autres rituels aient beaucoup plus de force ici que chez nous? Les amulettes païennes enchantées par des chamans indiens possèdent un véritable pouvoir que tout homme peut ressentir rien qu'en les tenant.\nMême nos alchimistes chrétiens - que Dieu leur fasse voir l'erreur de leurs voies! - ont maîtrisé l'art de fabriquer des objets enchantés. Ils ne réalisent pas qu'ils servent le Diable lui-même en faisant cela. Ne ressentez-vous pas la présence anormale de quelque chose d'infernal qui rôde juste en dehors de votre vision périphérique?";
			link.l1 = "Tu as raison, Père. Cela m'a d'abord surpris, mais maintenant je suppose que je m'y suis habitué... C'est le Nouveau Monde après tout !";
			link.l1.go = "utensil_10";
		break;
		
		case "utensil_10":
			dialog.text = "Mais ce n'était pas toujours comme ça. Les ténèbres dont je parle sont arrivées ici il y a environ vingt-cinq ans et gagnent de plus en plus de pouvoir chaque jour qui passe. Cela ne signifie qu'une chose : 'il' est déjà venu, 'il' est parmi nous, et 'il' est à l'œuvre...";
			link.l1 = "De qui parles-tu ? Qui est ce mystérieux 'il' ?";
			link.l1.go = "utensil_11";
		break;
		
		case "utensil_11":
			dialog.text = "L'ennemi juré des chrétiens, désireux de la destruction de l'Église et de toute la chrétienté.";
			link.l1 = "...Parles-tu de l'Antéchrist ?";
			link.l1.go = "utensil_12";
		break;
		
		case "utensil_12":
			dialog.text = "Que ce soit 'l''Antéchrist ou juste 'un' antéchrist, je ne prétendrai pas le dire. Peu importe le nom que porte cette bête quand elle se drape de chair mortelle dans une parodie grotesque de l'Incarnation de Notre Sauveur. Ce qui est important, c'est ce qu'elle va faire. Je suis ici pour l'arrêter, et vous allez m'aider. Mais nous nous sommes un peu emportés. Vous êtes un homme d'action. Vous préféreriez probablement passer aux choses sérieuses et éviter la théologie, n'est-ce pas ?";
			link.l1 = "Au contraire, j'ai découvert beaucoup de choses nouvelles et importantes grâce à vous, Votre Excellence. Je suis prêt à écouter.";
			link.l1.go = "utensil_13";
		break;
		
		case "utensil_13":
			dialog.text = "Tu es courtois et bien élevé, mon fils. C'est bien. Revenons maintenant à la raison pour laquelle tu m'as consulté. Notre objectif commun est de trouver les trésors de Tayasal emportés par Dichoso. Nous pourrons probablement trouver une arme parmi ces trésors que nous pourrons utiliser dans la bataille à venir contre le Diable.";
			link.l1 = "Mais se peut-il que Dichoso ait déjà quitté les Caraïbes et soit assis sur un tas d'or en Espagne ?";
			link.l1.go = "utensil_14";
		break;
		
		case "utensil_14":
			dialog.text = "Non. J'ai la preuve que ces trésors sont encore ici dans les Caraïbes. Vous n'avez pas encore besoin de connaître mes sources, vous devez me faire confiance. D'ailleurs, je pense que Dichoso mentait au baron.\nSon histoire sur les ruines de Tayasal ne correspond pas à ce que mon Indien Itza m'a dit sous interrogatoire. Sans parler du fait que Dichoso étant le seul survivant de l'embuscade des Mosquitos était un peu trop pratique.";
			link.l1 = "Je suppose que Don Mendosa le croit aussi, puisqu'il a attaqué Saint-Pierre en essayant de trouver Dichoso ?";
			link.l1.go = "utensil_15";
		break;
		
		case "utensil_15":
			dialog.text = "Les actions du baron ne devraient pas te concerner, mon fils. Il n'est motivé que par une soif d'or et de profit personnel. Sa cupidité sera une pierre d'achoppement à son cou alors que tout autour de lui, de bons hommes et femmes chrétiens combattent les forces de l'Enfer.";
			link.l1 = "As-tu des pistes sur où nous devrions chercher Dichoso et le trésor ?";
			link.l1.go = "utensil_16";
		break;
		
		case "utensil_16":
			dialog.text = "J'y pense à chaque minute, mon fils, mais je n'ai rien de précis à te dire. Mais il y a ici un homme qui nous aidera, un philosophe naturel de Gênes. Je l'ai amené ici avec moi pour aider à catégoriser les choses du Nouveau Monde qui pourraient être utiles à la mission de l'Église. Il a assisté à l'interrogatoire de l'Indien Itza et, à mon avis, les choses qu'il avait entendues l'ont choqué et attiré de manière perverse.\nLe Diable a utilisé sa curiosité comme un hameçon appâté et l'a possédé, corps et âme. Le Seigneur lui avait donné une grande capacité en médecine et en alchimie, mais notre Génois est tombé dans la tentation de la magie noire et de la sorcellerie. Il a parlé plusieurs fois avec mon captif Itza sans ma permission, puis a disparu. Nous devons le trouver et sauver son âme.";
			link.l1 = "Je suppose que je suis censé le trouver ?";
			link.l1.go = "utensil_17";
		break;
		
		case "utensil_17":
			dialog.text = "Oui, mon fils. Il est la première étape pour trouver le trésor et l'arme que nous pouvons utiliser contre les forces maléfiques qui nous menacent.";
			link.l1 = "Qui est ce Génois ?";
			link.l1.go = "utensil_18";
		break;
		
		case "utensil_18":
			dialog.text = "Son nom est Gino Gvineili. Trente ans, plus ou moins. Un médecin et alchimiste talentueux. Comme je l'ai dit, il étudie maintenant la magie noire. Selon mes meilleures informations, il se cache quelque part parmi les colonies anglaises dans les Caraïbes.\nTrouve Gino Gvineili, mon fils. Si tu as réussi à trouver ce pirate qui a volé nos vaisseaux d'église, alors tu réussiras aussi à retrouver mon secrétaire en fuite et à le ramener ici. Je prierai pour l'intercession de Saint Antoine en ta faveur.";
			link.l1 = "Je vois, Votre Excellence. Je ne vais pas perdre une minute de plus. À plus tard !";
			link.l1.go = "utensil_19";
		break;
		
		case "utensil_19":
			DialogExit();
			AddQuestRecord("Guardoftruth", "35");
			bool bOk = (pchar.questTemp.HWIC.Detector == "holl_win") || (pchar.questTemp.HWIC.Detector == "eng_win") || (pchar.questTemp.HWIC.Detector == "self_win");
			if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && bOk)
			{
				pchar.questTemp.Guardoftruth = "jino";
				AddQuestUserData("Guardoftruth", "sText", "I almost betrayed myself by a shout of surprise. Father Vincento ordered me to find and bring him his runaway secretary, a physician alchemist named Gino Gvineili. That same Gino who occupies the spare room on the second floor of my house in St. John's!");
			}
			else
			{
				pchar.questTemp.Guardoftruth = "merdok";
				AddQuestUserData("Guardoftruth", "sText", "I must find a man named Gino Gvineili, hiding somewhere in the English Caribbean colonies. He is a physician and an alchemist. Where can a man like him hide?");
			}
		break;
		
		case "guardoftruth":
			dialog.text = "J'avais toute confiance que tu dirais cela, "+pchar.name+". Maintenant, ma foi est encore renforcée par ma certitude que vous m'avez été envoyé par la main de la Divine Providence Elle-même. Où est mon fils misérable et prodigue ?";
			link.l1 = "J'ai bien peur que tu n'apprécies pas ce que tu vas entendre, mais je n'ai pas le choix. Ton secrétaire est mort.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Que Dieu sauve son âme et lui pardonne ses péchés... Comment cela s'est-il passé, mon fils ?";
			link.l1 = "J'ai trouvé Gino à Antigua. Il se cachait là-bas dans l'un des vieux bâtiments construits sous le laboratoire. Il n'a pas accepté de me suivre tranquillement. Après avoir entendu ton nom et vu que j'étais prêt à utiliser la force, il a sorti une fiole de liquide clair des plis de son long vêtement et l'a bue en un instant...";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "";
			link.l1 = "Et puis quelque chose d'horrible arriva : il devint rouge, puis bleu foncé. Il s'effondra sur le sol en se tordant dans un spasme et en une minute mourut dans une douleur atroce. Une forte odeur d'amandes emplit la pièce.";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Gino... Pauvre idiot... Il a même passé la dernière minute de sa vie dans le péché en se suicidant. Quelle perte tragique. Je prierai pour son âme...";
			link.l1 = "Après sa mort, j'ai fouillé sa demeure et j'ai trouvé ce folio. Cela pourrait-il vous intéresser ou peut-être nous aider dans nos recherches ? Il y a ici des notes étranges et ésotériques d'une certaine sorte...";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			RemoveItems(pchar, "Almanac", 1);
			Log_Info("You've given the almanac");
			PlaySound("interface\important_item.wav");
			dialog.text = "Ceci est l'almanach du pauvre Gino. Il y avait écrit des notes sur toutes ses explorations. Donne-le-moi, mon fils, je vais étudier ce qui y est écrit. Peut-être y trouverons-nous un indice.\nBien que tu ne m'aies pas ramené Gino Gvineili, je suis satisfait de tes efforts, mon fils. Maintenant, j'ai des nouvelles pour toi.";
			link.l1 = "Tu as toute mon attention, Père.";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "J'ai acquis des informations selon lesquelles l'île de Trinidad était le dernier endroit où la frégate de Dichoso a été vue. Je connais également un moment approximatif - début avril 1654.\nAllez à Trinidad et essayez d'apprendre quelque chose sur le sort de la frégate : où elle se dirigeait, quels étaient les plans du capitaine, tout ce que vous pouvez trouver. Je comprends qu'il s'est écoulé beaucoup de temps et que la mémoire des gens a ses limites, mais un homme qui se noie s'accroche à tout ce qu'il peut.";
			link.l1 = "Je ferai tout ce qui est en mon pouvoir.";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "Laissez-moi voir votre lettre de sauf-conduit. J'ajouterai la permission pour vous de visiter la colonie de San Jose.";
			link.l1 = "Ici.";
			link.l1.go = "guardoftruth_6a";
		break;
		
		case "guardoftruth_6a":
			RemoveItems(pchar, "VerifyPaper", 1);
			dialog.text = "Voilà... ce sera tout. N'oubliez pas de hisser le drapeau espagnol sur votre navire. Avancez et recevez la bénédiction de Dieu, mon fils !";
			link.l1 = "Un instant, Votre Grâce. Puis-je vous poser une question ?";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Oui, bien sûr. Que souhaitez-vous savoir ?";
			link.l1 = "Lors de notre dernière rencontre, vous avez parlé d'un Indien Itza qui vous avait informé sur Tayasal. J'y ai beaucoup réfléchi... Dites-moi, cet homme avait-il quelque chose sur lui ? Des objets de quelque sorte, des écrits, ou quelque chose du genre ? Cela pourrait s'avérer utile.";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "Aucun objet spécial, mon fils. Un pagne, des bijoux primitifs, une pipe en bambou avec quelques herbes, et un morceau de cuir brut utilisé comme bâillon.\nTout cela a été envoyé à Don Ramon de Mendoza y Riba. Mais je vous assure, il n'y avait rien digne d'intérêt.";
			link.l1 = "Je vois. Merci, Père. À la prochaine fois !";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			DialogExit();
			GiveItem2Character(pchar, "VerifyPaper");
			ChangeItemDescribe("VerifyPaper", "itmdescr_VincentoPaper_A");
			AddQuestRecord("Guardoftruth", "38");
			npchar.quest.skinmap = "true";
			pchar.questTemp.Guardoftruth.Trinidad = "begin";
		break;
		
		case "guardoftruth_10":
			dialog.text = "Que le Tout-Puissant te bénisse et te garde... Qu'est-il finalement arrivé à Miguel Dichoso ? As-tu découvert quelque chose ?";
			link.l1 = "Hélas, je ne l'ai pas fait. La dernière chose que les témoins pouvaient me dire était que la Santa Quiteria avait été emportée par des vents violents en direction de la Martinique. On ne sait pas avec certitude si le navire a été sauvé ou s'il a péri. Mais j'ai des soupçons que Miguel Dichoso s'en est sorti vivant.";
			link.l1.go = "guardoftruth_11";
		break;
		
		case "guardoftruth_11":
			dialog.text = "Qu'est-ce qui t'a poussé à décider cela, mon fils ?";
			link.l1 = "La clé est que la frégate se cachait quelque part en direction de la Martinique. Et tout récemment, un galant caballero du nom de Diego de Montoya, un des hommes de Don Ramon de Mendosa lui-même, a attaqué Saint-Pierre dans le but de trouver Miguel Dichoso qui s'y cachait supposément.";
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			dialog.text = "Alors, le baron pense que Dichoso s'est caché avec les Français...";
			link.l1 = "Je connais bien Saint-Pierre et le Gouverneur Jacques Dyel du Parquet, Votre Excellence. Personne n'y connaissait un Espagnol nommé Miguel Dichoso. Pouvez-vous me dire comment trouver Diego de Montoya? J'aimerais lui parler de Dichoso.";
			link.l1.go = "guardoftruth_13";
		break;
		
		case "guardoftruth_13":
			dialog.text = "Es-tu sûr qu'il serait disposé à te parler, mon fils ? Je ne pense pas qu'il le ferait, à moins que tu ne converses avec l'épée et le pistolet.";
			link.l1 = "Se pourrait-il que ton nom le rende plus accommodant ?";
			link.l1.go = "guardoftruth_14";
		break;
		
		case "guardoftruth_14":
			dialog.text = "Oh, "+pchar.name+"Je doute que l'homme juré de Don Mendosa soit prêt à conclure un accord avec vous. Lui donner l'ordre de se rendre à San Diego pour une audience avec moi pourrait être une option, mais je ne suis pas sûr que Diego soit parfaitement sincère avec moi non plus.";
			link.l1 = "Quelle action devons-nous prendre maintenant, Père ?";
			link.l1.go = "guardoftruth_15";
		break;
		
		case "guardoftruth_15":
			dialog.text = "Laisse-moi un moment, mon fils. J'ai besoin de digérer ce que tu m'as dit et aussi de rassembler tous les faits que je connais déjà de mes diverses sources. Après cela, je te dirai quelle sera notre prochaine démarche. Reviens plus tard.";
			link.l1 = "Oui, Votre Grâce. Je m'en chargerai. Je vérifierai périodiquement...";
			link.l1.go = "guardoftruth_16";
		break;
		
		case "guardoftruth_16":
			DialogExit();
			AddQuestRecord("Guardoftruth", "43");
			pchar.questTemp.Guardoftruth.Trinidad = "end";
			pchar.quest.GuardOT_setSpaOfficer.win_condition.l1 = "ExitFromLocation";
			pchar.quest.GuardOT_setSpaOfficer.win_condition.l1.location = pchar.location;
			pchar.quest.GuardOT_setSpaOfficer.function = "GuardOT_SetSpaOfficerInTown";
			NextDiag.CurrentNode = "guardoftruth_wait";
		break;
		
		case "guardoftruth_wait":
			dialog.text = "Que Dieu te bénisse, mon fils... Que puis-je faire pour toi ?";
			link.l1 = "Avez-vous des nouvelles, Votre Excellence ?";
			link.l1.go = "guardoftruth_wait_1";
		break;
		
		case "guardoftruth_wait_1":
			dialog.text = "Pas pour le moment, mon fils. Ne désespère pas cependant. Mes gens et moi y travaillons. Passe plus tard.";
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "guardoftruth_wait";
		break;
		
		case "guardoftruth_17":
			dialog.text = "Oui, mon fils. J'ai des informations sur Miguel Dichoso. Ce n'était pas en vain que je croyais Dichoso encore vivant et dans les Caraïbes. Il semble que Don Diego de Montoya avait raison. Nous avons reçu une preuve d'un homme qui connaissait Miguel Dichoso de vue, attestant que le gentilhomme disparu a été aperçu dans le repaire de pirates de Le François en Martinique en avril 1654 après la disparition de la Santa Quiteria...";
			link.l1 = "Alors, la frégate a sombré sur les côtes de la Martinique ?";
			link.l1.go = "guardoftruth_18";
		break;
		
		case "guardoftruth_18":
			dialog.text = "Ralentis, mon fils. Nous n'avons aucune information pour l'instant sur un quelconque naufrage à la Martinique à cette époque. Et une frégate n'est pas une gabarre. Sa destruction aurait sûrement attiré l'attention et créé une énorme opportunité de récupération pour les charognards locaux.";
			link.l1 = "Serait-il utile de fouiller le rivage et les plages pour trouver ce qui reste du navire ?";
			link.l1.go = "guardoftruth_19";
		break;
		
		case "guardoftruth_19":
			dialog.text = "Mon fils, Don Diego de Montoya a déjà fait tout cela sans résultat. Continue d'écouter. Mes sources à Providence rapportent que le Baron est sûr que la Santa Quiteria navigue encore à travers les Caraïbes, bien qu'elle porte un autre nom. C'est pourquoi il traque Miguel Dichoso si désespérément. D'après ses dires, la Santa Quiteria a été vue non loin de l'Isla Tesoro et elle a récemment été vue sous pavillon anglais escortée par une escadre militaire.";
			link.l1 = "Quoi ? C'est incroyable. Ils ont dit qu'affronter une tempête d'une telle ampleur serait impossible... Et maintenant le Santa Quiteria n'a pas seulement survécu mais navigue sous le pavillon anglais ? Les deux faits ne correspondent pas. Qu'est-ce qui a poussé le Baron à conclure que c'était le Santa Quiteria ? Est-elle vraiment un navire si unique ?";
			link.l1.go = "guardoftruth_20";
		break;
		
		case "guardoftruth_20":
			dialog.text = "Oh oui. Cette frégate a été construite en utilisant les dernières techniques d'Europe. Elle est très bien armée pour sa classe, et sa vitesse lui permet de distancer tout ce qui pourrait la surpasser en puissance de feu. C'est ce que m'a dit ma source.";
			link.l1 = "Et elle est appelée maintenant sinon Santa Quiteria?";
			link.l1.go = "guardoftruth_21";
		break;
		
		case "guardoftruth_21":
			dialog.text = "Ça, malheureusement, je ne le sais pas... Va à Isla Tesoro, "+pchar.name+", et essaie de découvrir quelque chose sur la frégate de Dichoso. On pourrait aussi retrouver son ancien capitaine de cette manière, deux oiseaux avec une pierre. Ou deux rats avec un piège.";
			link.l1 = "Considérez cela comme fait, Votre Excellence !";
			link.l1.go = "guardoftruth_22";
		break;
		
		case "guardoftruth_22":
			DialogExit();
			AddQuestRecord("Guardoftruth", "59");
			// проверяем, жив ли Акула и где он, если жив
			if (GetCharacterIndex("Dodson") != -1)
			{
				sld = characterFromId("Dodson");
				if (sld.location == "Pirates_townhall") pchar.questTemp.Guardoftruth.Archy = "islatesoro";
				else pchar.questTemp.Guardoftruth.Archy = "islatesorotavern";
			}
			else pchar.questTemp.Guardoftruth.Archy = "islatesorotavern";
			SetTimerCondition("Map_SetNationCoolHanters", 0, 0, 5, false); // немного развлечений
		break;
		
		case "tieyasal":
			dialog.text = "Je suis heureux que tu aies décidé de me voir, mon fils.";
			link.l1 = "Bonjour, Votre Excellence. Après avoir rencontré Don Alonso de Maldonado, je ne pensais même pas vous revoir un jour.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Don Alonso de Maldonado a enfreint mes ordres directs. Je lui avais strictement interdit de te confronter, mon fils, je savais comment cela finirait pour lui. Et ce que j'avais prévu s'est réalisé. Sa mission était de t'escorter jusqu'à Tayasal, car il y était déjà allé.\nEn plus de cela, son escadron et une compagnie de soldats espagnols devaient te défendre contre une attaque des Itza ou des Mosquitos. Alonso a agi de manière indigne, poussé par un désir égoïste de vengeance.\nIl n'a pas seulement échoué l'expédition à Tayasal et condamné les soldats et les navires qui lui avaient été confiés, mais il a aussi semé les graines de la méfiance et du ressentiment contre moi dans ton cœur. Je t'assure, mon fils, je suis complètement de ton côté. Nous devons nous unir contre cette obscurité présente.";
			link.l1 = "J'aimerais bien le croire.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "Rassurez-vous, "+pchar.name+"Moi, un serviteur loyal et dévoué de notre Seigneur et Sauveur Jésus-Christ et un représentant de son Église, suis motivé par une seule chose : empêcher la fin du monde d'arriver avant que toutes les âmes n'aient eu la chance d'entendre la parole de Notre Seigneur Béni. Et cela signifie arrêter l'agent diabolique actuellement entre les mains d'un Indien possédé par un démon. J'ai suspecté cela dès le départ et maintenant je suis complètement certain. Vous avez été choisi par le Seigneur comme Son champion dans la bataille contre Satan.";
			link.l1 = "Mais qu'est-ce qui vous fait dire cela, Père ?";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			dialog.text = "Vous avez réussi à faire quelque chose que ni moi avec l'aide de tous mes agents, ni le Baron Mendosa et Don Diego, ni personne d'autre n'a pu faire. Vous avez réussi à trouver cette maudite île et à chercher l'artefact de Kukulcan dessus. N'est-ce pas ?";
			link.l1 = "Oui, j'ai le masque de Kukulcan.";
			link.l1.go = "tieyasal_4";
		break;
		
		case "tieyasal_4":
			dialog.text = "Et prétendrais-tu que tout cela s'est passé par accident ? Par coïncidence ? 'Le cœur de l'homme médite sa voie, mais c'est le Seigneur qui affermit ses pas.' Mon fils, le Tout-Puissant t'a conduit sur ce chemin ! Il a fortifié ta main au combat, dirigé tes pieds sur le bon chemin, et t'a protégé dans les moments de péril ! 'Voici, l'épée du Seigneur descend pour le jugement sur Edom, sur le peuple que j'ai voué à la destruction !'";
			link.l1 = "Euh... Père, mais la mission est déjà pratiquement accomplie. J'ai le masque. Cela ne signifie-t-il pas que la coquille possédée de Kukulcan ne peut pas entrer dans notre histoire et la changer...?";
			link.l1.go = "tieyasal_5";
		break;
		
		case "tieyasal_5":
			dialog.text = "Tu te trompes, mon fils. Le démon peut franchir cette porte qu'il ait ce masque ou non. Le masque ne fait que faciliter ses actes sombres. La seule chose qui peut l'arrêter est la destruction complète des portes infernales.";
			link.l1 = "Don Alonso m'a dit la même chose...";
			link.l1.go = "tieyasal_6";
		break;
		
		case "tieyasal_6":
			dialog.text = "Et il avait raison ! Au nom de notre Seigneur Jésus-Christ et de Sa Sainte Mère, je t'appelle à prendre la Croix contre ce mal, mon fils ! Tu ne peux pas refuser la grande mission qui t'a été confiée. Moi et toute la chrétienté comptons sur toi, mon fils.";
			link.l1 = "Votre Excellence, c'est trop. Je me sens vraiment... un peu gêné...";
			link.l1.go = "tieyasal_7";
		break;
		
		case "tieyasal_7":
			dialog.text = "Ta modestie te sied bien, mon fils, mais ce n'est pas le moment de jouer les vierges effarouchées. Ne sois pas pusillanime ni craintif, car le Seigneur ton Dieu va devant toi pour te donner la victoire ! Entre dans cette bataille pour tes proches, pour tous les chrétiens... et si ce n'est pas pour eux, alors pour toi-même, car si ce démon l'emporte, tu périras avec tout le monde.";
			link.l1 = "Je suppose que tu m'as convaincu, Père. J'hésitais à propos de ma situation pour entreprendre une croisade à Tayasal, mais maintenant je n'ai plus aucun doute. Comment peux-tu m'aider ?";
			link.l1.go = "tieyasal_8";
		break;
		
		case "tieyasal_8":
			dialog.text = "Seuls deux hommes savaient comment se rendre à Tayasal : Alonso de Maldonado et Miguel Dichoso. Don Alonso est mort. Et Dichoso... On m'a dit qu'on l'a récemment vu à Sharptown sur l'Isla Tesoro. Peut-être est-il encore là. Vous devez trouver Dichoso et le persuader d'être votre guide.\nPar l'or ou la force, vous devez contraindre cet homme à vous mener à Tayasal. Là, vous trouverez les portes de l'enfer, et là, vous les scellerez.";
			link.l1 = "Et qu'en est-il des hommes ?";
			link.l1.go = "tieyasal_9";
		break;
		
		case "tieyasal_9":
			dialog.text = "La dernière compagnie de soldats que j'avais était sous le commandement d'Alonso de Maldonado. Hélas, je n'ai pas la chance de rassembler une autre troupe de soldats espagnols. J'ai épuisé tout mon crédit auprès de la garnison locale. Tu devras le faire avec l'aide de tes propres hommes, mon fils. Mais je te donnerai l'aide que je peux pour tout le reste.";
			link.l1 = "Quel genre d'aide ?";
			link.l1.go = "tieyasal_10";
		break;
		
		case "tieyasal_10":
			dialog.text = "Nous devons tirer parti de chaque avantage que nous avons dans ce combat, tant matériel que spirituel. J'ai demandé à Père Adrian de me rejoindre ici à cette chapelle dans cinq jours. Il apportera avec lui des amulettes sacrées pour vous. Des amulettes qui peuvent aider les guerriers du Christ au combat. Il vous fournira également toutes sortes de potions. Quant à moi, accepte cette lame, mon fils.\nCeci est une épée ancienne des Chevaliers du Temple, une arme formidable de nos ancêtres. Toujours affûtée, et brillante de la bénédiction de l'Église. Seuls les plus grands chevaliers ont eu l'honneur de la manier. Prends-la, possède-la avec fierté, et écrase les ennemis de notre Foi avec le nom de Jésus-Christ sur tes lèvres !";
			link.l1 = "Merci ! Cette épée est absolument incroyable. Je suis sans voix...";
			link.l1.go = "tieyasal_11";
		break;
		
		case "tieyasal_11":
			sTemp = GetBestGeneratedItem("blade_32");
			GiveItem2Character(pchar, sTemp);
			sld = ItemsFromID(sTemp);
			sld.Balance = 2.0;
			sld.Weight = 4.5;
			Log_Info("You've received the Tanath");
			PlaySound("interface\important_item.wav");
			dialog.text = "Que Dieu vous bénisse, "+GetFullName(pchar)+", in this coming battle. I embower you with the Holy Cross. Almighty God, in whose hand victory rests and who also gave David miraculous strength to crush Goliath: humbly we pray your mercy to bless these weapons by your life-giving mercy; and grant your servant "+GetFullName(pchar)+" who wills to bear them, that he may use them freely and victoriously for defending Holy Mother Church against the attacks of all enemies visible and invisible. Through Christ our Lord. Amen.";
			link.l1 = "Amen !";
			link.l1.go = "tieyasal_12";
		break;
		
		case "tieyasal_12":
			dialog.text = "Et maintenant va-t'en, mon fils. Que Dieu te garde, qu'il ne te quitte jamais, ni dans ta quête, ni sur ton chemin, ni dans la bataille. Cherche Miguel Dichoso et rends-toi à Tayasal avec son aide. N'oublie pas le Père Adrian, il te fournira les amulettes et remèdes dont tu pourrais avoir besoin. Et maintenant il est temps pour moi de retourner à Santiago. Adieu, mon fils. Vaya con Dios.";
			link.l1 = "Adieu, Père Vincento...";
			link.l1.go = "tieyasal_13";
		break;
		
		case "tieyasal_13":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Tieyasal_VinsentoGo", -1);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
