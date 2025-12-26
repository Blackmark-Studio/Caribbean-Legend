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
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Qu'est-ce que vous voulez ? ";
			link.l1 = "Rien.";
			link.l1.go = "exit";
		break;
		
		case "LEDR_Gonsalo_1":
			if (pchar.sex == "man")
			{
				dialog.text = "Hé, garçon ! Je vois que tu es un marin courageux, et sans doute un sacré bagarreur. Tu ne voudrais pas m'aider à faire une petite expédition quelque part, hein ?";
			}
			else
			{
				dialog.text = "Hé, beauté ! Je vois que tu n’as pas froid aux yeux pour venir ici. Tu ne voudrais pas m’aider à faire un petit raid quelque part, hein ?";
			}
			link.l1 = "Je suppose que c'est toi le vieux qui cherche un guide vers le vieux navire ?";
			link.l1.go = "LEDR_Gonsalo_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LEDR_Gonsalo_2":
			dialog.text = "Héhé... Alors, les rumeurs vont plus vite que le vent. Oui, c'est bien moi. Gonzalo Peralta – le seul survivant du naufrage de 'La Espada del Rey'.";
			link.l1 = "Et moi, je suis capitaine "+GetFullName(pchar)+". Tu veux revoir ton rafiot ?";
			link.l1.go = "LEDR_Gonsalo_3";
		break;

		case "LEDR_Gonsalo_3":
			dialog.text = "Oui. Tu sais, depuis quelque temps, je fais sans cesse le même cauchemar. Mais ce n'est même pas ça le pire... Crois-le ou non, chaque matin, dès que le cauchemar prend fin, je me réveille, et... devant moi se tient un foutu squelette...";
			link.l1 = "En tenue indienne. On m’a dit que tu racontes cette histoire à tout le monde.";
			link.l1.go = "LEDR_Gonsalo_4";
		break;

		case "LEDR_Gonsalo_4":
			dialog.text = "Une histoire ? Hé... J’aimerais bien que ce ne soit qu’une histoire. Il y a encore quelques mois, je menais une vie tranquille, comme il sied à un vieux marin à la retraite. Mais maintenant, ce sac d’os me rend visite chaque matin, me fixe, pousse un cri à glacer le sang... nom d’un boulet, même un maître d’équipage aurait la chair de poule... et puis il se jette dans la mêlée. Et tu sais quoi ? À chaque fois, il attaque avec encore plus de rage. Voilà pourquoi je veux rejoindre le navire au plus vite — j’ai le sentiment que je dois y trouver quelque chose.";
			link.l1 = "Hmm... Intéressant. Et qu'espères-tu y trouver, après tout ce temps ?";
			link.l1.go = "LEDR_Gonsalo_5";
		break;
		
		case "LEDR_Gonsalo_5":
			dialog.text = "Je ne sais pas, capitaine, je ne sais pas... Mais ce navire m’attire comme une vieille barque dans la tempête. Mon rêve, ce squelette et cette étrange sensation... Par la mer, je te jure qu’ils sont liés d’une façon ou d’une autre. Mais comment – ça, je n’en ai pas la moindre idée.";
			link.l1 = "Que se passe-t-il exactement dans ton rêve ? Est-ce que ça a un rapport avec les Indiens ?";
			link.l1.go = "LEDR_Gonsalo_6";
			link.l2 = "Alors, la nuit tu vois des visions, et le matin tu te bats contre un squelette ? Peut-être que le problème n’est pas dans le navire, mais que tu devrais plutôt aller voir un médecin ? Je ne vais pas encourager tes délires. Trouve un autre idiot pour croire à tes histoires.";
			link.l2.go = "LEDR_Gonsalo_6_end";
		break;
		
		case "LEDR_Gonsalo_6_end":
			DialogExit();
			AddDialogExitQuestFunction("LEDR_End");
		break;
		
		case "LEDR_Gonsalo_6":
			dialog.text = "Et comment que c'est lié, qu'on me pende... Dans ce rêve, je suis avec l'équipage perdu  sur le 'La Espada del Rey'. Nous... pillons les villages des Caraïbes sur Hispaniola, massacrant tout le monde - hommes, femmes, enfants. Ceux qui se battent, et même ceux qui tombent à genoux, suppliant pour leur vie. Nous réduisons les villages en cendres, un après l'autre. Les flèches et massues des indigènes contre nous, c'est comme une barque percée contre un galion de guerre. Les Caraïbes, désespérés, demandent à négocier, et alors...";
			link.l1 = "Seigneur miséricordieux ! Alors tu as pris part à ces exactions ? Ce n’est pas d’aide qu’il te faut, mais une corde au cou !";
			link.l1.go = "LEDR_Gonsalo_7";
		break;
		
		case "LEDR_Gonsalo_7":
			dialog.text = "Non ! Non, que le diable m’emporte, il n’y a jamais eu rien de tel, tu comprends ?! Je n’ai aucune idée de pourquoi tout ça me hante dans mes rêves... mais je le jure sur tous les saints, ni moi, ni mon équipage n’avons jamais pris part à de telles atrocités !";
			link.l1 = "Il vaudrait mieux pour toi que ce soit vraiment le cas. Continue.";
			link.l1.go = "LEDR_Gonsalo_8";
		break;

		case "LEDR_Gonsalo_8":
			dialog.text = "Les Caraïbes ont demandé à négocier, et le capitaine a accepté. Il les a tous invités dans l’une de ces cabanes que ‘nous’ avions prises. Les chefs sont venus – une vingtaine, pas moins, menés par leur reine, Anacaona. Mais le capitaine lui-même n’est pas entré... aucun de nous n’est entré. Dès que le dernier chef est passé, la porte a été claquée et bloquée avec des poutres. Et puis... bon sang... ils y ont mis le feu. Seule la reine a été épargnée, mais pas pour longtemps. On l’a forcée à regarder son peuple brûler vif... Et ensuite, ils l’ont pendue à un arbre.";
			link.l1 = "Et ça se répète chaque nuit ? Toujours le même rêve, encore et encore ? Tu sais, je ne serais pas surpris si, après tout ça, ce squelette n’était qu’un fruit de ton esprit devenu fou...";
			link.l1.go = "LEDR_Gonsalo_9";
		break;

		case "LEDR_Gonsalo_9":
			dialog.text = "Ce n’est pas tout. Les Caraïbes survivants se sont enfuis à Cuba, ont trouvé du soutien auprès des tribus locales et se sont bientôt rassemblés en une seule armée – sous la direction d’un certain chef. Atuey – il me semble que c’était son nom. Ils le suivaient comme leur dernier espoir. Mais nous les avons tous massacrés sans difficulté. Atuey a été capturé et préparé pour l’exécution. Quand on l’a attaché à la croix, prêt à être brûlé, un moine lui a proposé d’accepter la vraie foi – il disait que cela allégerait ses souffrances et qu’il irait au paradis. Atuey a demandé au moine si le paradis était ouvert aux Espagnols. Et quand celui-ci a répondu qu’évidemment, les bons Espagnols y étaient admis, le cacique a répondu sans hésiter que dans ce cas, il préférait l’enfer – pour ne pas partager la demeure des hommes aussi cruels. Après cela, il a prononcé encore quelques phrases dans sa langue, et le bûcher a été allumé. Il n’a pas poussé un seul cri lorsque les flammes ont commencé à ronger sa chair. Par la mer, je ne voudrais jamais voir ça de mes propres yeux. Mon rêve se termine toujours de la même façon : le capitaine est assis, immobile. Seule une bougie fume à côté de lui, et il feuillette un vieux journal usé. Lentement, comme si chaque mot pesait de l’or, il marmonne quelque chose pour lui-même. Même dans mon sommeil, "+GetSexPhrase("le gars","la fille")+", je comprends - c'est un signe. Il est temps de dégainer, car il attaque déjà\nAide-moi à me débarrasser de ce cauchemar, capitaine. Viens avec moi jusqu'à la crique. Je n'oserai pas y aller seul - je n'ai plus assez de poudre dans mes cornes. Mais avant que tu répondes, je dois te prévenir : je n'ai rien pour te payer, sinon il y aurait déjà une file d'aides devant ma porte. Je n'ai plus qu'à compter sur l'entraide entre marins.";
			link.l1 = "Très bien. Si aller jusqu'au navire peut t'aider à te débarrasser de ces rêves et autres visions, je vais t'aider. Monte à bord. Dès que j'aurai fini mes affaires, nous partirons pour la baie.";
			link.l1.go = "LEDR_Gonsalo_10";
		break;
		
		case "LEDR_Gonsalo_10":
			DialogExit();
			AddDialogExitQuestFunction("LEDR_1");
			AddQuestRecord("LEDR", "2");
			AddQuestUserData("LEDR", "sSex", GetSexPhrase("ся","ась"));
		break;
		
		case "LEDR_Gonsalo_11":
			if (GetHour() >= 7 && GetHour() <= 19)
			{
				dialog.text = "Le voilà... Jadis la fierté de la flotte marchande espagnole, et maintenant – un tas de planches pourries, qui tiennent ensemble par miracle.";
				link.l1 = "On voit rarement un colosse pareil terrassé — allongé sur la rive. Comment est-il arrivé ici ?";
				link.l1.go = "LEDR_Gonsalo_12";
				link.l2 = "Alors, regardons autour de nous. Peut-être que tu arriveras vraiment à trouver quelque chose ici.";
				link.l2.go = "LEDR_Gonsalo_20_1";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "Je ne veux pas paraître ingrat ou lâche... mais je ne me sens pas à l’aise ici en ce moment. Revenons quand le soleil se lèvera.";
				link.l1 = "D'accord, l'ami, comme tu veux.";
				link.l1.go = "exit";
				NextDiag.TempNode = "LEDR_Gonsalo_11";
			}
		break;
		
		case "LEDR_Gonsalo_12":
			dialog.text = "Nous sommes partis de Santiago, cap sur Séville. Il n’y avait pas beaucoup de cargaison, mais nous avions un passager — un personnage important, un évêque en personne. Pour l’équipage, je l’avoue, ce genre de traversée n’était pas du goût de tous... mais qui nous a jamais demandé notre avis ?\nNous n’avons jamais atteint l’océan. Près de Turks, une goélette pirate nous a attaqués — rapide, agile, armée jusqu’aux dents. Pas des miséreux, mais de vrais loups de mer. Le capitaine a d’abord voulu fuir — il ne tenait pas à risquer la vie de l’évêque. Mais avec ce vent, impossible de faire demi-tour, et la tempête arrivait déjà du sud. Alors il n’y avait plus le choix — le combat a commencé.";
			link.l1 = "Se retrouver pris entre deux feux, ce n'est guère enviable. Et qu'est-il arrivé ensuite ?";
			link.l1.go = "LEDR_Gonsalo_13";
			AddCharacterExpToSkill(pchar, "Sailing", 200);
		break;

		case "LEDR_Gonsalo_13":
			dialog.text = "Le combat n’a pas duré longtemps. Nous avons eu le temps de leur abattre le mât de misaine, mais les pirates ne sont pas restés en reste : un boulet perdu a sectionné la barre de gouvernail et, comme si le diable lui-même s’en mêlait, le navire s’est retrouvé figé, la proue tournée vers la tempête qui approchait. Elle arrivait si vite que les pirates — qu’un double boulet leur tombe sur la grand-voile — ont préféré prendre la fuite, se cachant dans l’une des criques de Turks. Il ne nous restait plus qu’une chose à faire : attendre que la tempête nous engloutisse. Le capitaine a ordonné de ferler les voiles et de remplacer la barre, mais il était déjà trop tard.";
			link.l1 = "Alors, la tempête vous a attrapé près de Turks, vous a traîné jusqu'ici et finalement rejeté sur la côte ?";
			link.l1.go = "LEDR_Gonsalo_14";
		break;

		case "LEDR_Gonsalo_14":
			dialog.text = "C'est exactement comme ça que tout s'est passé. À bord, c'était l'enfer. Le vent arrachait les cordages, les mâts tombaient les uns après les autres, fracassaient le pont et écrasaient les hommes. Ceux qui n'avaient pas eu le temps de s'attacher étaient emportés par-dessus bord, et ceux qui l'avaient fait étaient broyés par les débris. Dans la cale, ce n'était pas mieux : canons, caisses, boulets volaient dans tous les sens comme des démons, broyant tout sur leur passage. Quand, finalement, nous avons été jetés sur la côte, j'étais inconscient. Je me suis réveillé sur le sable. C'est le bosco Sergio qui m'a trouvé. Il était accompagné de deux autres hommes.";
			link.l1 = "Ce n'est pas grand-chose, pour un si grand navire.";
			link.l1.go = "LEDR_Gonsalo_15";
		break;

		case "LEDR_Gonsalo_15":
			dialog.text = "Ah, capitaine... Il y avait tant de cadavres... On a tout de suite compris qu’on ne pouvait pas rester ici. Les vagues pouvaient emporter le navire, et nous avec. Tout près, on a trouvé une grotte – là, épuisés, on s’est endormis à peine touché le sol. Quand je me suis réveillé, dans la grotte il n’y avait plus ni Sergio, ni les deux autres\nJ’ai fouillé toute la plage, mais, par le tonnerre, ils n’étaient plus là. Remonter seul à bord du navire, c’était au-dessus de mes forces, alors j’ai décidé de m’enfoncer dans l’île. C’est comme ça que je suis arrivé à Sharptown, où, par pure naïveté, j’ai fait des bêtises\nJe voulais juste savoir s’il y avait des survivants, alors j’ai raconté à tout le monde ce qui nous était arrivé. Mais ces filous ne s’intéressaient ni à moi, ni à l’équipage, seulement au butin qu’ils pourraient voler sur le navire. La rumeur s’est vite répandue sur toute l’île, et des hordes de ces ladrons s’y sont précipitées.";
			link.l1 = "Alors, tu ignores toujours ce qu'il est advenu de ces gens ?";
			link.l1.go = "LEDR_Gonsalo_16";
		break;

		case "LEDR_Gonsalo_16":
			dialog.text = "Il était trop dangereux de retourner sur le navire. Ceux qui avaient osé s’y aventurer pour le butin pouvaient ne pas se partager le trésor et tirer sur quiconque se trouvait à côté... par accident. Ou peut-être — pas du tout par accident\nJe le jure sur la mer, je suis resté coincé à la taverne toute une semaine, à interroger chaque personne qui était passée par la baie. Mais personne n’avait entendu parler de mes gars, ni de ce qui leur était arrivé\nFinalement, j’ai fini par accepter l’idée : il semble bien que je sois le seul à avoir survécu à cette maudite tempête. Le destin m’a juste été plus clément qu’aux autres. Ou alors... c’est peut-être grâce à l’amulette que m’a offerte, il y a longtemps, le jeune capitaine Eugenio de la Torre. Je l’ai toujours gardée sur moi. Et, bon sang, il faut croire qu’elle portait vraiment chance.";
			link.l1 = "Et où est-il maintenant ? On dirait qu’il ne protège pas des squelettes, hein...";
			link.l1.go = "LEDR_Gonsalo_17";
		break;

		case "LEDR_Gonsalo_17":
			dialog.text = "Il a glissé de mon cou quand nous réparions le puits dans ma cour. Une poutre m’a frôlé le cou, et l’amulette est tombée à l’eau. Le puits était déjà plein, et personne n’allait l’épuiser pour une simple babiole.";
			link.l1 = "Et depuis ce moment-là, tu as commencé à faire des cauchemars ?";
			link.l1.go = "LEDR_Gonsalo_18";
		break;

		case "LEDR_Gonsalo_18":
			dialog.text = "Nom d’un chien ! Je n’y avais jamais pensé, mais c’est vrai ! Dès qu’on a fini de creuser le puits, les cauchemars ont commencé.";
			link.l1 = "Quelle coïncidence amusante. Eh bien, te voilà ici, comme tu le voulais. Qu'as-tu l'intention de faire maintenant ?";
			link.l1.go = "LEDR_Gonsalo_19";
		break;

		case "LEDR_Gonsalo_19":
			dialog.text = "Je ne sais pas, capitaine... Je ne sais pas. Commençons par explorer les environs – j’ai l’impression de plus en plus forte qu’il y a quelque chose que je dois trouver ici.";
			link.l1 = "D'accord. J'espère que nous ne sommes pas venus ici pour rien.";
			link.l1.go = "LEDR_Gonsalo_20";
		break;
		
		case "LEDR_Gonsalo_20":
			DialogExit();
			AddDialogExitQuestFunction("LEDR_3");
		break;
		
		case "LEDR_Gonsalo_20_1":
			DialogExit();
			AddDialogExitQuestFunction("LEDR_3");
			pchar.questTemp.LEDR_NoStory = true;
		break;
		
		case "LEDR_Gonsalo_21":
			dialog.text = "Écoute... Ce sentiment ne fait que grandir. C'est comme si j'étais à un pas de quelque chose que je dois découvrir. Il faut que je monte à bord du navire. Par tous les océans, il y a là-bas quelque chose qui expliquera pourquoi ce maudit squelette ne me laisse jamais en paix.";
			link.l1 = "Alors, peut-être que tu n’es pas venu ici pour rien ? Tu as caché quelque chose de précieux sur le navire, et maintenant tu es revenu pour récupérer ton bien ?";
			link.l1.go = "LEDR_Gonsalo_22";
		break;

		case "LEDR_Gonsalo_22":
			dialog.text = "Quelle absurdité ! Tu crois vraiment que je me serais traîné jusqu'ici à travers tout l'archipel pour quelques doublons après quarante ans ? Si seulement tu avais rencontré ce squelette au moins une fois, jamais de telles idées ne t'auraient traversé l'esprit.";
			link.l1 = "D'accord, d'accord, ne t'énerve pas. Et comment comptes-tu monter à bord du navire ?";
			link.l1.go = "LEDR_Gonsalo_23";
		break;

		case "LEDR_Gonsalo_23":
			dialog.text = "À la poupe, il y a une porte secrète. Le capitaine l’a découpée lui-même — au cas où l’abordage tournerait mal pour nous. Par tous les diables, je ne pourrais pas y traîner ma vieille carcasse tout seul, mais à deux...";
			link.l1 = "Eh bien, montre-moi le chemin, qu’on en finisse.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LEDR_5");
		break;
		
		case "LEDR_Gonsalo_24":
			DelLandQuestMark(npchar);
			dialog.text = "Par les boulets, quel carnage ! Heureusement que ceux-là étaient pas aussi féroces que celui qui me rend visite chaque matin. Alors, tu me crois maintenant ?";
			link.l1 = "Après un spectacle pareil, difficile de pas te croire. Ça va, t’es entier ?";
			link.l1.go = "LEDR_Gonsalo_24_1";
		break;

		case "LEDR_Gonsalo_24_1":
			dialog.text = "Je crois bien. Maudits morts-vivants... mes jambes ont lâché comme des mâts brisés.";
			link.l1 = "Bon, si t’es entier, c’est pas le moment de glander. Donne-moi la main, je vais t’aider à te relever.";
			link.l1.go = "LEDR_Gonsalo_24_2";
		break;

		case "LEDR_Gonsalo_24_2":
			CharacterTurnByChr(npchar, CharacterFromID("blaze"));
			dialog.text = "...";
			link.l1 = "Voilà qui est mieux. On dirait bien qu’on n’est pas les premiers à savoir comment entrer ici.";
			link.l1.go = "LEDR_Gonsalo_25";
			LAi_Fade("LEDR_GonsaloStay", "");
		break;

		case "LEDR_Gonsalo_25":
			dialog.text = "On dirait que ce sont mes gars. Ceux qui ont survécu à la tempête... J'ai reconnu le gilet de Sergio... enfin, ce qu'il en reste. Ça veut dire qu'ils sont revenus — soit pour chercher des survivants, soit pour enterrer les morts. Mais il semble bien que ces créatures les aient tous massacrés.";
			link.l1 = "Étonnamment, il ne reste que des lambeaux de son gilet. Et rien d’autre.";
			link.l1.go = "LEDR_Gonsalo_26";
		break;

		case "LEDR_Gonsalo_26":
			if(CheckAttribute(pchar, "questTemp.LEDR_NoStory"))
			{
			dialog.text = "Pas même une trace de la soutane de notre passager — l’évêque. À en juger par la clé serrée dans sa main, ce pauvre type là-bas, c’est lui. Il ne s’en séparait jamais, même pas une seconde. On dirait qu’il n’a pas eu plus de chance que les autres. Par la mer, ces morts-vivants n’erraient pas ici pour rien. Quelque chose les retient... ou bien ils gardent quelque chose.";
			DeleteAttribute(pchar, "LEDR_NoStory");
			}
			else
			{
			dialog.text = "Pas même une trace de la soutane de l’évêque. À en juger par la clé serrée dans sa main, ce pauvre type là-bas, c’est lui. Il ne s’en séparait jamais, même pas une seconde. On dirait qu’il n’a pas eu plus de chance que les autres. Par la mer, ces morts-vivants n’erraient pas ici pour rien. Quelque chose les retient... ou bien ils gardent quelque chose.";
			}
			link.l1 = "Moi aussi, j’ai le sentiment qu’on est censés trouver quelque chose ici. Finissons-en au plus vite — j’ai aucune envie de traîner ici plus que nécessaire.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LEDR_8");
		break;
		
		case "LEDR_Gonsalo_27":
			dialog.text = "Alors, capitaine ? Vous avez trouvé quelque chose ?";
			link.l1 = "On dirait que c'était le coffre de l'évêque. Je suis à nous"+GetSexPhrase("merde","ла")+" il y a quelque chose. Regarde.";
			link.l1.go = "LEDR_Gonsalo_28";
		break;

		case "LEDR_Gonsalo_28":
			dialog.text = "Velasquez... Que le tonnerre me frappe... J'ai vu ce journal dans mes rêves ! C'est bien celui que feuilletait le capitaine, juste avant que...";
			link.l1 = "...";
			link.l1.go = "LEDR_Gonsalo_29";
		break;

		case "LEDR_Gonsalo_29":
			dialog.text = "Le diable, c'est comme s'il me brûlait les mains !";
			link.l1 = "Ça te brûle les mains ? Allons, ce n’est qu’un vieux journal. Ou tu crois vraiment qu’il y a une force obscure là-dedans ?";
			link.l1.go = "LEDR_Gonsalo_30";
		break;

		case "LEDR_Gonsalo_30":
			dialog.text = "Je le jure sur tous les saints, je ne plaisante pas ! Ce foutu journal me brûle presque les mains. Il faut le détruire ! Le déchirer, le brûler, le jeter à la mer – n’importe quoi ! Non, attends... Mieux vaut le brûler. Oui, le brûler, pour qu’il n’en reste même pas de cendres !";
			link.l1 = "Comme tu voudras. Alors allons à terre, faisons un feu et envoyons cette chronique de méfaits aux flammes.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LEDR_10");
		break;
		
		case "LEDR_Gonsalo_31":
			dialog.text = "Voilà, c'est fini... Comme si un poids s'était arraché de mon âme.";
			link.l1 = "Tu crois que tout est fini maintenant ?";
			link.l1.go = "LEDR_Gonsalo_32";
			TakeItemFromCharacter(pchar, "LEDR_book");
		break;

		case "LEDR_Gonsalo_32":
			dialog.text = "Qui sait... Mais, par la mer, il y a longtemps que je ne me suis pas senti aussi libre. Comme si une vieille dette avait enfin été effacée. Pourtant... J’aurais préféré ne jamais voir ce maudit journal. Et ne jamais savoir ce qui y était écrit.";
			link.l1 = "Ce n’est pas étonnant que tu aies rêvé de ça. Même si tu n’as pas pris part à tout cela, tu es le seul vivant à avoir été lié d’une façon ou d’une autre au journal.";
			link.l1.go = "LEDR_Gonsalo_33";
		break;
		
		case "LEDR_Gonsalo_33":
			dialog.text = "Ni l'or, ni la foi ne sauraient justifier ce que les hommes aux ordres de Velasquez ont fait. Et je suis heureux que tout ce qui pouvait rappeler cela ait brûlé. De telles choses ne doivent jamais tomber entre les mains de ceux qui voudraient leur emboîter le pas.";
			link.l1 = "Velasquez n'est qu'un parmi tant d'autres. Qui sait combien de journaux de ce genre circulent encore dans la vieille Europe, attisant la cupidité et l'impunité des nouveaux conquérants ? Une chose me rassure : celui-ci n'empoisonnera plus personne. D'ailleurs, dans le coffre de l'évêque, il n'y avait pas que le journal, mais aussi un joli stock de doublons – trois cents. La moitié t'appartient de plein droit.";
			link.l1.go = "LEDR_Gonsalo_34_share";
			link.l2 = "Velasquez a payé pour ses péchés, et si quelqu’un décide de suivre sa voie, il connaîtra le même sort. Tôt ou tard, le destin rend à chacun ce qu’il mérite.";
			link.l2.go = "LEDR_Gonsalo_34_silence";
		break;
		
		case "LEDR_Gonsalo_34_share":
			dialog.text = "Dans ce cas, je ne dirai pas non. Tout le monde a besoin d’argent, et moi plus que jamais en ce moment. On ne me prendra plus comme matelot sur aucun navire – je suis devenu trop vieux. Alors merci, capitaine, de ne pas m’avoir envoyé promener."+GetSexPhrase("ся","ась")+", comme les autres.";
			link.l1 = "Je dois avouer que ton histoire m’a d’abord paru être le délire d’un fou. Mais tu l’as racontée avec tant de conviction que, qu’on le veuille ou non, on finit par y croire. Pourtant, l’apparition de ces morts-vivants indiens m’a vraiment pris au dépourvu.";
			link.l1.go = "LEDR_Gonsalo_35_1";
			link.l2 = "Je voulais juste vérifier si tu n’étais pas fou. Tu comprends, ce n’est pas facile de croire à de telles histoires.";
			link.l2.go = "LEDR_Gonsalo_35_2";
			RemoveDublonsFromPCharTotal(150);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.quest.LEDR_share = true;
		break;
		
		case "LEDR_Gonsalo_34_silence":
			dialog.text = "J’aimerais y croire... Mais, par la mer, j’en ai vu trop à qui le destin souriait, malgré toutes leurs mauvaises actions. Peut-être que la justice les rattrapera – mais ce sera là-bas, dans ce fichu chaudron. Et toi, merci, capitaine. Pour ne pas t’être détourné, pour m’avoir écouté et raccompagné. Tu sais, ça compte beaucoup.";
			link.l1 = "Je t'avoue, ton histoire m'a d'abord paru comme le délire d'un fou. Mais tu la racontais avec une telle conviction que, bon gré mal gré, on finit par y croire. Pourtant, l'apparition de ces morts-vivants indiens m'a pris au dépourvu.";
			link.l1.go = "LEDR_Gonsalo_35_1";
			link.l2 = "Je voulais juste vérifier si tu n’étais pas fou. Tu comprends, ce n’est pas facile de croire à de telles histoires.";
			link.l2.go = "LEDR_Gonsalo_35_2";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
		break;

		case "LEDR_Gonsalo_35_1":
			dialog.text = "Maintenant tu sais ce que j'ai ressenti la première fois que j'ai vu ces morts-vivants. J'espère qu'on en a fini avec eux pour de bon... Sinon, je doute de survivre à une nouvelle rencontre.";
			link.l1 = "Eh bien, puisque nous avons terminé ici, il est temps de partir. Monte à bord, je te déposerai au port de Sharptown.";
			link.l1.go = "LEDR_Gonsalo_36";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "LEDR_Gonsalo_35_2":
			dialog.text = "Maintenant tu sais ce que j'ai ressenti la première fois que j'ai vu ces morts-vivants. J'espère qu'on en a fini avec eux pour de bon... Sinon, je doute de survivre à la prochaine rencontre.";
			link.l1 = "Eh bien, puisque nous avons terminé ici, il est temps de partir. Monte à bord, je te déposerai au port de Sharptown.";
			link.l1.go = "LEDR_Gonsalo_36";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		
		case "LEDR_Gonsalo_36":
			DialogExit();
			AddDialogExitQuestFunction("LEDR_12");
		break;
		
		case "LEDR_Gonsalo_37":
			dialog.text = "Encore merci, capitaine "+GetFullName(pchar)+". Je le jure sur la mer, cette étrange sensation s'est dissipée, et j'espère qu'elle a emporté avec elle son maudit sac d'os. On se prendrait pas une chope, hein ?";
			link.l1 = "Merci pour l’invitation, Gonzalo, mais j’ai encore du pain sur la planche. Une autre fois, peut-être. Bois à notre santé.";
			link.l1.go = "LEDR_Gonsalo_38";
		break;
		
		case "LEDR_Gonsalo_38":
			if (CheckAttribute(npchar, "quest.LEDR_share"))
			{
				dialog.text = "Je comprends. Mais laisse-moi te dire, capitaine : après tout ce que nous avons traversé ensemble, je ne peux pas partir comme ça, sans te remercier. Ce ne serait pas humain. Tiens, prends ça. Dans ma jeunesse, j’ai souvent couru après des trésors, je te le jure sur la mer. Mais aujourd’hui, la santé n’est plus la même, et mon dos me fait défaut. Toi, tu es jeune, un vrai loup de mer aguerri. Tu le trouveras sans difficulté. Bonne chance à toi, "+GetFullName(pchar)+", bon vent et sept pieds sous la quille.";
				link.l1 = "Merci, Gonzalo. Bonne chance à toi aussi, adieu.";
				AddMapPart();
			}
			else
			{
				dialog.text = "Eh bien, il est temps de se dire au revoir. Bon vent et que la mer te soit clémente, capitaine "+GetFullName(pchar)+"!";
				link.l1 = "Bonne chance, Gonzalo.";
			}
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LEDR_14");
		break;
		
		
		
	}
}