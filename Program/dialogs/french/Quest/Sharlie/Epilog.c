void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i, n, iTemp, addGold, NextMonth;
	string attrL, sStr, Month;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Vous vouliez quelque chose ?";
			link.l1 = "Non, rien.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// диалоги в ПУ
		case "SharlieEpilog_Pikar_1":
			dialog.text = "Quelle surprise ! Toi-même "+GetTitle(NPChar,true)+" "+pchar.lastname+" en personne !";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive"))
			{
				link.l1 = ""+npchar.name+"! Je ne m’attendais vraiment pas à te voir… Pour tout dire, je ne pensais même pas que tu étais encore en vie !";
				link.l1.go = "SharlieEpilog_Pikar_2";
			}
			else
			{
				link.l1 = "Je n’en crois pas mes yeux... Un beau gosse ? Mais... comment ?";
				link.l1.go = "SharlieEpilog_PikarResurrected_1";
			}
			PlaySound("Voice\" + LanguageGetLanguage() + "\LE\Rocur\Rocur_03.wav");
		break;
		
		case "SharlieEpilog_Pikar_2":
			if (IsStateTitle())
			  {
				dialog.text = "Ha ha ! Eh bien, tu t’es trompé. Comme tu vois, je suis plus vivant que jamais. J’ai même décidé de m’offrir un petit navire tout propre. Et toi alors… raconte : comment t’en es arrivé là, hein, mon ami ?";
			  }
			  else 
			  {
				dialog.text = "Ha ha ! Eh bien, tu vois, je suis plus vivant que jamais. J’ai décidé de m’offrir un petit navire tout propre. Et toi alors… raconte : qu’est-ce qui t’amène ici, hein, mon ami ?";
			  }
			link.l1 = "Pas ici. Allons à la taverne, les affaires peuvent attendre.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_WithPikarToTavern");
		break;
		
		case "SharlieEpilog_PikarResurrected_1":
			dialog.text = "Chut... Ne crie pas comme ça. Le beau gosse, c'est du passé, tout comme le Prince, j'imagine. N'est-ce pas ?";
			link.l1 = "Mais je l’ai vu de mes propres yeux...";
			link.l1.go = "SharlieEpilog_PikarResurrected_2";
		break;

		case "SharlieEpilog_PikarResurrected_2":
			dialog.text = "Comment j’ai été achevé ? J’aurais préféré, crois-moi, mon ami.";
			link.l1 = "Allons à la taverne. Tu me raconteras tout.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_WithPikarToTavern");
		break;
		
		case "SharlieEpilog_Captain_1":
			dialog.text = "...";
			link.l1 = "Donc, vous êtes le nouveau propriétaire du pinasse '"+GetShipName("Ulysse")+"'?";
			link.l1.go = "SharlieEpilog_Captain_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\z_arest_02.wav");
		break;
		
		case "SharlieEpilog_Captain_2":
			dialog.text = "Moi. "+GetFullName(npchar)+", puisque cela vous intéresse tant. Et vous, qui êtes-vous ?";
			link.l1 = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+", et j’aimerais vous racheter ce navire.";
			link.l1.go = "SharlieEpilog_Captain_3";
		break;
		
		case "SharlieEpilog_Captain_3":
			dialog.text = "Bien sûr, bien sûr, j’en ai entendu parler. Je croyais pourtant avoir déjà découragé tous ceux qui voulaient s’emparer de ce navire. Je vais devoir vous décevoir, "+GetTitle(NPChar,true)+" - '"+GetShipName("Ulysse")+"Il est à moi maintenant, et très bientôt, je pars pour Bordeaux avec. Je ne me suis pas lancé dans le commerce pour gâcher ma première affaire dès le départ. Ce serait de mauvais augure, vous savez.";
			link.l1 = "Bordeaux, dites-vous ? Intéressant... Il se pourrait que j'aie une proposition avantageuse à vous faire. Peut-être pourrions-nous en discuter autour d'une chope de rhum ?";
			link.l1.go = "SharlieEpilog_Captain_4";
		break;
		
		case "SharlieEpilog_Captain_4":
			dialog.text = "Je n'ai pas l'habitude de refuser ni le rhum, ni les bonnes affaires. Allons-y.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_WithPikarToTavern");
		break;
		
		// диалоги в таверне
		case "SharlieEpilog_Pikar_5":
			if (IsStateTitle())
			  {
				dialog.text = "Eh bien, à toi, "+GetTitle(npchar,false)+" "+pchar.lastname+"Je savais bien qu’un gars comme toi ne resterait pas longtemps à faire des courses pour Tirax. Mais que tu deviennes un personnage aussi important… tu sais surprendre, bon sang.";
				link.l1 = "Ha ha. Qui l’aurait cru. Alors, tu as décidé de te lancer dans le commerce ?";
			  }
			  else 
			  {
				dialog.text = "À notre rencontre ! Je le sentais au fond de moi, on allait forcément se revoir.";
				link.l1 = "Ha ha. À elle ! Alors, tu as décidé de te lancer dans le commerce ?";
			  }
			
			link.l1.go = "SharlieEpilog_Pikar_6";
		break;

		case "SharlieEpilog_Pikar_6":
			dialog.text = "On ne va pas risquer sa peau toute sa vie pour deux doublons. Il suffit de graisser la patte à qui il faut, faire taire ceux qu’il faut pas – et voilà : je ne suis plus un voleur ni un pirate, mais un négociant respectable.";
			link.l1 = "Ça alors, c’est inattendu. Je ne sais même plus comment te proposer ce que j’avais prévu pour le tout nouveau capitaine de pinasse '"+GetShipName("Ulysse")+"'.";
			link.l1.go = "SharlieEpilog_Pikar_7";
		break;

		case "SharlieEpilog_Pikar_7":
			dialog.text = "Allez, raconte tout franchement. On se connaît pas d’hier, toi et moi.";
			link.l1 = "Tu vois... je suis arrivé ici, aux Caraïbes, sur la pinasse que tu as rachetée. Quand j'ai appris qu'elle était mise aux enchères, je voulais la récupérer – et rentrer chez moi, en France, à son bord.";
			link.l1.go = "SharlieEpilog_Pikar_8";
		break;

		case "SharlieEpilog_Pikar_8":
			dialog.text = "Ha ha ha ha ! Attends... ah ha ha ha ha !..";
			link.l1 = "Eh bien, qu'est-ce qui te fait rire ? ";
			link.l1.go = "SharlieEpilog_Pikar_9";
		break;

		case "SharlieEpilog_Pikar_9":
			dialog.text = "À peine avais-je remporté les enchères qu’un dandy s’est approché de moi – jeune, soigné : il me dit, transporte-moi, mon cher, avec tous mes effets à Bordeaux, pour une belle somme. Et pas juste une pièce – un sacré sac de pièces, tu vois.";
			link.l1 = "Ah bon ? Ha ha. C’est vraiment drôle. Et alors, tu as accepté ?";
			link.l1.go = "SharlieEpilog_Pikar_10";
		break;

		case "SharlieEpilog_Pikar_10":
			dialog.text = ""+pchar.name+", tu sais, je ne suis pas assez idiot pour refuser une montagne d’or juste pour une traversée ordinaire de l’Atlantique. Ouais, il faudra grignoter des biscuits secs et mâcher du salé pendant quelques mois. Mais tu sais, il m’est déjà arrivé de risquer ma peau pour bien moins que ça. Alors évidemment, je suis partant.";
			link.l1 = "Dans ce cas, je peux te proposer la même chose. Emmène-moi à Bordeaux – et tu recevras tout autant de pièces.";
			link.l1.go = "SharlieEpilog_Pikar_11";
		break;

		case "SharlieEpilog_Pikar_11":
			dialog.text = "Tu es prêt à embarquer comme passager ? Tu connais nos règles : il n’y a qu’un seul capitaine à bord. Et sur mon navire, c’est moi.";
			link.l1 = "Pourquoi pas ? Je vais reprendre mon souffle, réfléchir à la vie. Peut-être qu’il est vraiment temps pour moi de me poser, de me calmer un peu. J’ai du mal à m’imaginer ça pour l’instant, mais il y a peut-être du sens là-dedans. Même toi, tu as choisi de rester à l’écart des combats.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1.go = "SharlieEpilog_Pikar_12_wife";
			}
			else
			{
				link.l1.go = "SharlieEpilog_Pikar_12";
			}
		break;
		
		case "SharlieEpilog_Pikar_12_wife":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive"))
			{
				dialog.text = "Ah, si j'avais une belle femme comme toi, peut-être que moi aussi j'aurais quitté la mer, je me serais installé dans un coin perdu : j'aurais construit une maison et vendu un peu de vin. Faut dire que j'ai de quoi vivre – depuis que tu m'as tiré des griffes des Espagnols, je n'ai pas perdu mon temps.";
			}
			else
			{
				dialog.text = "Ah, si j'avais une belle femme comme toi, peut-être que moi aussi j'aurais quitté la mer pour m'installer dans un coin perdu : construire une maison, vendre un peu de vin. Faut dire, avec l'héritage de la veuve du planteur, il y avait de quoi vivre.";
			}
			link.l1 = "Ma femme ! Nom d’un diable, "+npchar.name+", je ne lui en ai pas encore parlé, tu sais.";
			link.l1.go = "SharlieEpilog_Pikar_13_wife";
		break;
		
		case "SharlieEpilog_Pikar_13_wife":
			dialog.text = "Tu as encore largement le temps pour ça. Moi, il faut que j’équipe mon rafiot comme il faut. Quand tu auras réglé toutes tes affaires, ramène-toi ici. On fêtera ça avant le départ.";
			link.l1 = "Ça, c’est pour moi ! Ne t’en fais pas, tu n’auras pas à attendre longtemps.";
			link.l1.go = "SharlieEpilog_Pikar_14_wife";
		break;
		
		case "SharlieEpilog_Pikar_14_wife":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive")) {AddQuestRecord("SharlieEpilog", "11_1");}
			else {AddQuestRecord("SharlieEpilog", "11_5");}
			AddDialogExitQuestFunction("SharlieEpilog_OutTavern");
		break;
		
		case "SharlieEpilog_Pikar_12":
			dialog.text = "Ah, si j'avais une femme, peut-être que moi aussi j'aurais quitté la mer, je me serais installé dans un coin perdu : j'aurais construit une maison, et vendu un peu de vin. Mais pour l'instant... la mer, c'est chez moi.";
			link.l1 = "Du vin de mes plantations, ha-ha ! À Bordeaux, "+npchar.name+", ces demoiselles-là sont un vrai régal pour les yeux ! Peut-être que tu y trouveras aussi quelqu’un à ton goût – elles ne sont pas maladroites en amour, loin de là. Je me disais : dans les prochains mois, tout ce qu’on va voir, c’est la tronche de tes matelots. On devrait vraiment organiser une sacrée fête dans le bordel du coin avant de prendre la mer.";
			link.l1.go = "SharlieEpilog_Pikar_13";
		break;
		
		case "SharlieEpilog_Pikar_13":
			dialog.text = "Et vous, monsieur, vous savez quoi proposer. Quand vous en aurez fini avec toutes vos affaires, ramenez donc vos fesses ici. Et après, on ira jusqu’au bordel, sois-en sûr.";
			link.l1 = "Eh bien, alors je ne vais pas perdre de temps. Au travail !";
			link.l1.go = "SharlieEpilog_Pikar_14";
		break;
		
		case "SharlieEpilog_Pikar_14":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive")) {AddQuestRecord("SharlieEpilog", "11_2");}
			else {AddQuestRecord("SharlieEpilog", "11_6");}
			AddDialogExitQuestFunction("SharlieEpilog_OutTavern");
		break;
		
		case "SharlieEpilog_PikarResurrected_3":
			dialog.text = "Pour la liberté !";
			link.l1 = "Et à toi, Jean ! À ta résurrection ! J’ai encore du mal à y croire. Comment ?";
			link.l1.go = "SharlieEpilog_PikarResurrected_4";
		break;

		case "SharlieEpilog_PikarResurrected_4":
			dialog.text = "On m’a traîné hors du champ de bataille — j’étais à peine vivant, couvert de sang de la tête aux pieds. On m’a jeté dans une baraque et laissé là pour crever comme une charogne. Parmi les esclaves, il y avait un gars plutôt débrouillard — Moko. C’est lui qui m’a sauvé la peau : il a serré ma blessure avec un morceau de ma propre chemise, m’a donné à boire.";
			link.l1 = "Tu veux dire que les Espagnols t'ont laissé en vie après tout ça ?";
			link.l1.go = "SharlieEpilog_PikarResurrected_5";
		break;

		case "SharlieEpilog_PikarResurrected_5":
			dialog.text = "Comme tu peux le voir. Mais ce n’était pas par pure bonté d’âme. Ils voulaient se venger – interrogatoire musclé, torture. Ils brûlaient, frappaient, tailladaient. Ils menaçaient même de me crever les yeux – tout ça par un immense amour pour ma personne. Mais quelqu’un a lancé la rumeur que les pirates préparaient leur vengeance pour moi et affûtaient déjà leurs couteaux. Le propriétaire de la plantation en a eu un tic à l’œil. Il n’a pas attendu la visite de nos frères et s’est empressé de partir pour ses terres à Campeche. Il nous a emmenés, Moko, les autres et moi, pour qu’il ne reste aucun témoin. Aux autres, il a annoncé que j’étais passé de vie à trépas – et l’affaire a été classée.";
			link.l1 = "Et alors ? Comment as-tu retrouvé ta liberté ? Et comment, bon sang, tu t’es retrouvé ici ?";
			link.l1.go = "SharlieEpilog_PikarResurrected_6";
		break;

		case "SharlieEpilog_PikarResurrected_6":
			dialog.text = "La chance, mon ami. Une chance aveugle et crasseuse. On m’a envoyé à la plantation – et les tortures ont continué. Ce salaud voulait savourer chaque seconde de ma souffrance, mais chaque jour il devenait plus faible… jusqu’à ce qu’il crève de la fièvre. Après ça, plus personne ne s’est soucié de moi. On m’a jeté aux champs comme du bétail, sans oublier de me régaler de coups de fouet.";
			link.l1 = "Je ne comprends toujours pas comment tu as réussi à t’en sortir ?";
			link.l1.go = "SharlieEpilog_PikarResurrected_7";
		break;

		case "SharlieEpilog_PikarResurrected_7":
			dialog.text = "Tu as entendu parler de Christopher Myngs ?";
			link.l1 = "Alonso a mentionné quelque chose... Le raid sur Campeche ! Ils ont vraiment mis une raclée aux Espagnols, ce jour-là. C’est eux qui t’ont libéré ?";
			link.l1.go = "SharlieEpilog_PikarResurrected_8";
		break;

		case "SharlieEpilog_PikarResurrected_8":
			dialog.text = "Pas vraiment. On s’est libérés nous-mêmes. Pendant que les gardes se battaient contre une bande de boucaniers anglais, Moko et moi avons trouvé une brèche dans le toit de la baraque et lancé une révolte. On s’est emparés de l’arsenal et du trésor de la femme du défunt salaud de planteur.";
			link.l1 = "Le trésor public ?! Ça alors.";
			link.l1.go = "SharlieEpilog_PikarResurrected_9";
		break;

		case "SharlieEpilog_PikarResurrected_9":
			dialog.text = "Nous n’avons pas hésité longtemps – armés et chargés de nos biens, nous avons gagné la jungle. Deux jours durant, nous avons lutté à travers la forêt dense, jusqu’à tomber sur un village des Indiens Kan Pech. Leur chaman obéissait aux Espagnols pour la forme, mais il ne les portait pas vraiment dans son cœur. Moko a vite su trouver un terrain d’entente avec lui – on nous a accueillis en échange de la moitié de notre arsenal et d’un coup de main dans leur guerre, peu importe contre qui. C’est ainsi que j’ai vécu là-bas un an et demi.";
			link.l1 = "Jean, tu n’es plus celui que tu étais. Désormais, tu es le Chanceux.";
			link.l1.go = "SharlieEpilog_PikarResurrected_10";
		break;

		case "SharlieEpilog_PikarResurrected_10":
			dialog.text = "Ha ha. Je n’y vois pas d’inconvénient. Ensuite, un prêtre français s’est retrouvé par hasard dans notre batabille. On a tout de suite compris : c’était notre chance de sortir de là sans finir aux fers. On a soudoyé son escorte – et bientôt, on filait déjà vers la Tortue.\nAprès ça, comme tu t’en doutes sûrement, j’ai décidé d’arrêter de jouer à chat avec la mort. J’ai laissé tomber mon ancien métier… et, au passage, j’ai fait une bonne affaire en achetant '"+GetShipName("Ulysse")+".\n"+"Et toi alors ? Comment t’es arrivé là ? Je savais bien qu’un gars aussi débrouillard que toi n’allait pas rester longtemps à faire les quatre volontés de Tirax. Mais que tu deviennes un personnage aussi important… tu sais surprendre, sacré nom d’un chien.";
			link.l1 = "Ha ha. Qui l’aurait cru, venant de toi. Alors, tu t’es décidé à devenir marchand ?";
			link.l1.go = "SharlieEpilog_Pikar_6";
		break;
		
		case "SharlieEpilog_Captain_5":
			dialog.text = "À ceux qui sont en mer !";
			link.l1 = "Et à la chance, madame !";
			link.l1.go = "SharlieEpilog_Captain_6";
		break;

		case "SharlieEpilog_Captain_6":
			dialog.text = "Bon, allons droit au but. Qu'est-ce que vous vouliez me proposer ?";
			link.l1 = "Vous partez pour Bordeaux... Voyez-vous, j’y vais aussi.";
			link.l1.go = "SharlieEpilog_Captain_7";
		break;

		case "SharlieEpilog_Captain_7":
			dialog.text = "Vous voulez que je vous embarque à bord ? À ma connaissance, vous devriez avoir votre propre navire. Peut-être même toute une flottille. Et pourtant, vous avez choisi de voyager sur un autre bâtiment. J’ai bien compris ?";
			link.l1 = "C'est bien ça. Les derniers événements m'ont fait réfléchir : il est peut-être temps de jeter l'ancre, de me poser... Je crois que le rôle de simple passagère sur votre navire m'aidera à comprendre si je peux accepter ce nouveau rythme de vie.";
			link.l1.go = "SharlieEpilog_Captain_8";
		break;

		case "SharlieEpilog_Captain_8":
			dialog.text = "Hum... Alors, vous en avez assez de risquer votre cou pour rien ? Je comprends. Moi aussi, parfois... Enfin, peu importe. Il y aura une place pour vous sur le navire, même pour toute votre suite. La traversée a déjà été payée par un jeune élégant – et c’est lui aussi qui paie pour la rapidité, donc je ne chargerai pas les cales. Quant au paiement...";
			link.l1 = "Ne vous inquiétez pas, capitaine. Je ne suis pas moins généreux que votre employeur et je suis prêt à payer la même somme.";
			link.l1.go = "SharlieEpilog_Captain_9";
		break;

		case "SharlieEpilog_Captain_9":
			dialog.text = "Excellent ! Alors, marché conclu ?";
			link.l1 = "Marché conclu ! Ça mérite un verre !";
			link.l1.go = "SharlieEpilog_Captain_10";
		break;

		case "SharlieEpilog_Captain_10":
			dialog.text = "Ouais, ce rhum est parfait... Il me faudra deux semaines pour remettre le navire en état et faire toutes les provisions nécessaires. Après ça, on pourra lever l’ancre.";
			link.l1 = "Alors, retrouvons-nous ici dans deux semaines. Eh bien, à bientôt, capitaine.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1.go = "SharlieEpilog_Captain_11_wife";
			}
			else
			{
				link.l1.go = "SharlieEpilog_Captain_11";
			}
		break;
		
		case "SharlieEpilog_Captain_11_wife":
			DialogExit();
			AddQuestRecord("SharlieEpilog", "11_3");
			AddQuestUserData("SharlieEpilog", "sName", GetFullName(npchar));
			AddDialogExitQuestFunction("SharlieEpilog_OutTavern");
		break;
		
		case "SharlieEpilog_Captain_11":
			DialogExit();
			AddQuestRecord("SharlieEpilog", "11_4");
			AddQuestUserData("SharlieEpilog", "sName", GetFullName(npchar));
			AddDialogExitQuestFunction("SharlieEpilog_OutTavern");
		break;
		
		case "SharlieEpilog_Pikar_WaitInTavern":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Alors, mon pote, t’as réglé tes affaires ? On va leur montrer comment on s’amuse dans ce poulailler ?";
				link.l1 = "Ce n'est pas encore le moment, "+npchar.name+", il me reste encore quelques affaires à régler.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Capitaine, êtes-vous déjà prêt à monter à bord ?";
				link.l1 = "Hélas, collègue, j'ai encore des affaires à régler.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "SharlieEpilog_Pikar_WaitInTavern";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				// только если знаком с Пикаром и поговорил с женой
				link.l2 = "Hé, tavernier ! À boire pour tout le monde, c’est moi qui régale ! Et pas de la piquette, sors-nous ce que tu as de meilleur !";
				link.l2.go = "SharlieEpilog_Pikar_WaitInTavern_2";
			}
		break;
		
		case "SharlieEpilog_Pikar_WaitInTavern_2":
			dialog.text = "...";
			link.l1 = "À nous, mon ami. Au vent salé, à la mer sans fin et à l’horizon – toujours attirant, toujours hors d’atteinte...";
			link.l1.go = "SharlieEpilog_FrameInSea";
			DelLandQuestMark(npchar);
		break;
		
		case "SharlieEpilog_FrameInSea":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_FrameInSea");
		break;
		
		case "SharlieEpilog_Mary_1":
			dialog.text = "...";
			link.l1 = ""+npchar.name+", ma chérie, je voudrais te parler de mon père.";
			link.l1.go = "SharlieEpilog_Mary_2";
			DelLandQuestMark(npchar);
		break;

		case "SharlieEpilog_Mary_2":
			dialog.text = "Qu'est-ce qu'il y a, mon chéri ? J'espère que tout va bien pour lui, hein ?";
			link.l1 = "Eh bien, pas aussi bien qu’on l’aurait souhaité. Il y a des raisons de penser qu’il ne tiendra pas longtemps, et il est très inquiet à l’idée de ne pas me revoir avant de partir pour son dernier voyage.";
			link.l1.go = "SharlieEpilog_Mary_3";
		break;

		case "SharlieEpilog_Mary_3":
			dialog.text = ""+pchar.name+"...";
			link.l1 = "Je sais, ma chérie, je sais... Mais c’est la vie. J’aurais aimé que tu fasses sa connaissance. Qu’il voie à quel point ma femme est merveilleuse, et qu’il nous donne sa bénédiction.";
			link.l1.go = "SharlieEpilog_Mary_4";
		break;

		case "SharlieEpilog_Mary_4":
			dialog.text = "Et si je ne lui plaisais pas, hein ? Je ne suis pas de sang noble, après tout...";
			link.l1 = "Des bêtises, "+npchar.name+", comment pourrais-tu ne pas lui plaire ? Tu es un vrai miracle ! Si tu as conquis mon cœur, tu conquerras aussi le sien.";
			link.l1.go = "SharlieEpilog_Mary_5";
		break;

		case "SharlieEpilog_Mary_5":
			dialog.text = "Tu le penses vraiment, mon chéri ? Alors il faut qu’on parte le voir au plus vite.";
			link.l1 = "C'est exactement ce que je compte faire. J'ai même déjà trouvé un navire pour nous. Nous partons dans deux semaines.";
			link.l1.go = "SharlieEpilog_Mary_6";
		break;

		case "SharlieEpilog_Mary_6":
			dialog.text = "Un navire ? Nous ne partirons pas à bord du nôtre ?";
			link.l1 = "Non, ma chérie. Nous partirons sur la pinasse '"+GetShipName("Ulysse")+"'. C’est sur lui que je suis arrivé aux Caraïbes – et c’est sur lui que je les quitterai.";
			link.l1.go = "SharlieEpilog_Mary_7";
		break;

		case "SharlieEpilog_Mary_7":
			dialog.text = "Et tu ne seras pas capitaine ?";
			link.l1 = "Tôt ou tard, j’aurais de toute façon dû renoncer à ce rôle. J’espère que ce n’est que temporaire. Mais, quoi qu’il en soit, ça ne me fera pas de mal de ressentir ce que l’avenir me réserve.";
			link.l1.go = "SharlieEpilog_Mary_8";
		break;

		case "SharlieEpilog_Mary_8":
			dialog.text = "Et nos officiers alors ? On ne pourra pas tous les emmener avec nous. Et puis, ils ne vont sûrement pas t’attendre ici.";
			link.l1 = "Hem... Oui, tu as raison. Il va falloir parler à chacun d’eux, et sans doute leur dire adieu pour toujours. Même si ce ne sera pas facile, vu tout ce qu’on a traversé ensemble.";
			link.l1.go = "SharlieEpilog_Mary_9";
		break;
			
		case "SharlieEpilog_Mary_9":
			dialog.text = "Peut-être qu’on devrait organiser un petit festin d’adieu à la taverne ?";
			link.l1 = "J’y ai pensé aussi, ma chère. Tu sais… tu as sans doute raison. C’est vraiment une bonne idée.";
			link.l1.go = "exit";
			link.l2 = "Je ne pense pas que ce soit une bonne idée. Évitons les adieux en grande pompe... Ce sera sans doute mieux pour tout le monde. À moins qu’on n’invite seulement nos amis les plus proches...";
			link.l2.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_FarewellOfficers");
		break;
		
		case "SharlieEpilog_Helena_1":
			dialog.text = "...";
			link.l1 = "Chérie, j’aimerais te parler de mon père.";
			link.l1.go = "SharlieEpilog_Helena_2";
			DelLandQuestMark(npchar);
		break;

		case "SharlieEpilog_Helena_2":
			dialog.text = "Bien sûr, "+pchar.name+". J’espère qu’il va bien ?";
			link.l1 = "Pas vraiment. Il est malade depuis longtemps, et j’ai bien peur que la maladie finisse par l’emporter… Mon père affronte tout cela avec beaucoup de courage. La seule chose qui l’inquiète vraiment, c’est de ne peut-être jamais me revoir. Je veux lui rendre visite… et te le présenter. Recevoir sa bénédiction pour notre mariage.";
			link.l1.go = "SharlieEpilog_Helena_3";
		break;

		case "SharlieEpilog_Helena_3":
			dialog.text = "Je serai ravie de faire sa connaissance, mon amour. Quand est-ce qu’on part ?";
			link.l1 = "Dans deux semaines. Mais ce n'est pas tout. Nous ne partirons pas sur notre propre navire. C'est un pinasse qui nous emmènera vers le Vieux Continent."+GetShipName("Ulysse")+"– celui-là même qui m’a un jour amenée ici.";
			link.l1.go = "SharlieEpilog_Helena_4";
		break;

		case "SharlieEpilog_Helena_4":
			dialog.text = ""+pchar.name+", mais changer de navire avant un long voyage, c'est de mauvais augure.";
			link.l1 = "Nous ne changerons pas de navire, ma chère. Nous serons des passagers.";
			link.l1.go = "SharlieEpilog_Helena_5";
		break;

		case "SharlieEpilog_Helena_5":
			dialog.text = "Mais… mon amour, je ne comprends pas…";
			link.l1 = "C’est nécessaire, "+npchar.name+". Tôt ou tard, je devrai quitter mon poste de capitaine. Et je veux savoir à l’avance quelles émotions m’attendent.";
			link.l1.go = "SharlieEpilog_Helena_6";
		break;

		case "SharlieEpilog_Helena_6":
			dialog.text = "Si tu en as décidé ainsi... Mais qu’allons-nous faire de nos officiers ? Nous ne pourrons pas tous les emmener avec nous. Et puis, il y a peu de chances qu’ils acceptent de t’attendre ici.";
			link.l1 = "Hem... Oui, tu as raison. Il va falloir parler à chacun d’eux, et sans doute leur dire adieu pour toujours. Même si ce ne sera pas facile, vu tout ce qu’on a traversé ensemble.";
			link.l1.go = "SharlieEpilog_Helena_7";
		break;
			
		case "SharlieEpilog_Helena_7":
			dialog.text = "Peut-être qu’on devrait organiser un petit festin à la taverne pour fêter notre départ ?";
			link.l1 = "J’y ai pensé aussi, ma chère. Tu sais… je crois que c’est ce qu’on va faire. C’est vraiment une bonne idée.";
			link.l1.go = "exit";
			link.l2 = "Je ne pense pas que ce soit une bonne idée. Évitons les adieux en grande pompe... Ce sera sans doute mieux pour tout le monde. À moins qu’on n’invite seulement nos amis les plus proches...";
			link.l2.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_FarewellOfficers");
		break;
		
		// Диалог с Алонсо в таверне Сен-Пьера
		case "SharlieEpilog_AlonsoInTavern":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				dialog.text = "Capitaine... J'ai déjà parlé à l'aubergiste – il a préparé la meilleure boisson qu'il ait en réserve. Quand commence-t-on ?";
				link.l1 = "Tout de suite ! Hé, tavernier ! À boire pour tout le monde, c’est moi qui régale !";
				link.l1.go = "SharlieEpilog_AlonsoInTavern_1";
			}
			else
			{
				dialog.text = "Capitaine, vous m'aviez promis de me raconter comment vous avez entendu parler de l'« Ulysse ».";
				link.l1 = "Je me souviens, je me souviens. Hé, tavernier ! Le meilleur rhum pour cette table.";
				link.l1.go = "SharlieEpilog_AlonsoInTavern_3";
			}
			link.l2 = "Trop tôt, "+npchar.name+". J'ai encore des affaires urgentes à régler.";
			link.l2.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_AlonsoInTavern";
		break;
		
		case "SharlieEpilog_AlonsoInTavern_1":
			dialog.text = "...";
			link.l1 = "Alors, mon ami, va chercher les autres – on va montrer à Saint-Pierre comment font la fête les vrais loups de mer !";
			link.l1.go = "SharlieEpilog_AlonsoInTavern_2";
			DelLandQuestMark(npchar);
		break;
		
		case "SharlieEpilog_AlonsoInTavern_2":
			dialog.text = "Ha ha ! Capitaine, vous n’allez pas le croire – je les ai déjà appelés !";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_FrameInSea";
		break;
		
		case "SharlieEpilog_AlonsoInTavern_3":
			dialog.text = "...";
			link.l1 = "À nous, "+npchar.name+"À la bonne fortune et au vent qui gonfle nos voiles !";
			link.l1.go = "SharlieEpilog_FrameInSea";
			DelLandQuestMark(npchar);
		break;
		
		// На пинасе Улисс
		case "SharlieEpilog_Alonso_1":
			dialog.text = "On a vraiment tout retourné, capitaine. Ha ha. Je crois que seuls les maigres réserves de rhum du tavernier ont sauvé la taverne de la ruine totale.";
			link.l1 = "Ne me le rappelle pas, "+npchar.name+", je ne commence à me sentir un peu mieux que maintenant.";
			link.l1.go = "SharlieEpilog_Alonso_2";
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "tutorial_4", "", -1);
			CharacterTurnByLoc(pchar, "quest", "quest6");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "tutorial_5", "", -1);
			CharacterTurnByLoc(npchar, "quest", "quest7");
		break;
		
		case "SharlieEpilog_Alonso_2":
			dialog.text = "Comme vous voudrez, monsieur "+pchar.lastname+". Ha ha. Mais au moins, nous avons fait nos adieux à la Martinique en beauté. On parlera longtemps de votre départ là-bas.";
			link.l1 = "Je crois qu’on est allés un peu loin, quand on a mis l’aubergiste dans la chaloupe pour l’envoyer chercher à boire à Le François.";
			link.l1.go = "SharlieEpilog_Alonso_2_1";
		break;
		
		case "SharlieEpilog_Alonso_2_1":
			if (GetAttributeInt(pchar, "questTemp.SharlieEpilog_Friends") >= 2)
				{
					dialog.text = "Ha ha ha. Ne vous en faites pas pour lui. En quelques jours, il a amassé assez d’or pour s’acheter une plantation, et même un titre par-dessus le marché.";
				}
			else
				{
					dialog.text = "Ha ha ha. Ne vous en faites pas pour lui. En quelques jours, il a amassé assez d’or pour s’acheter une plantation, et même un titre en prime. Dommage seulement que vous n’ayez parlé à aucun des officiers. Ils vont nous manquer.";
				}
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Alonso_3";
		break;
		
		case "SharlieEpilog_Alonso_3":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
				{
					sld = CharacterFromID("Helena");
					locCameraFromToPos(-8.97, 6.39, -12.78, true, -8.54, 4.94, -13.90);
				}
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
				{
					sld = CharacterFromID("Mary");
					locCameraFromToPos(-3.62, 4.03, 2.30, true, -4.98, 2.62, 3.26);
					// locCameraFromToPos(-4.13, 4.23, 2.55, true, -5.71, 2.54, 3.58);
				}
				dialog.text = "On dirait que "+sld.name+" est toujours fâché contre vous parce que vous avez disparu pendant toute la nuit.";
			}
			else
			{
				dialog.text = "Mais avec ce marchand… là, capitaine, vous y êtes vraiment allé un peu fort.";
			}
			link.l1 = "Bon sang, il a fallu que Jean et moi allions traîner dans cette boutique locale…";
			link.l1.go = "SharlieEpilog_Alonso_4";
		break;
		
		case "SharlieEpilog_Alonso_4":
			dialog.text = "Comment avez-vous fait pour ne pas vous faire attraper ? Ça aurait été drôle, vraiment - "+GetTitle(PChar,true)+" pris en train de voler quelques bouteilles de vin. ";
			link.l1 = "Ça te fait rire, "+npchar.name+", et je ne me souviens même pas de la moitié de tout ça. La dernière fois que j’ai bu autant... eh bien... jamais, en fait.";
			link.l1.go = "SharlieEpilog_Alonso_5";
			locCameraFromToPos(-8.74, 6.30, 7.38, true, -14.34, 4.16, 6.56);
		break;
		
		case "SharlieEpilog_Alonso_5":
			dialog.text = "Alors, à la tienne, cap’. Ha ha. J’ai bien aimé. Je recommencerais volontiers. Dites, c’est quand qu’on y retourne ?";
			link.l1 = "Va donc plutôt vérifier si toutes nos affaires sont là. On a bien tout pris ? Je descendrai plus tard – l’air de la cale ne me ferait sûrement pas du bien pour l’instant.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_UlysseInSea_8");
		break;
		
		// диалог с Алонсо у горы золота
		case "SharlieEpilog_Alonso_11": // этап 1
			dialog.text = "...";
			link.l1 = "Regarde-moi ça... le navire a vraiment été secoué.";
			link.l1.go = "SharlieEpilog_Alonso_12";
			SharlieEpilog_GoldInTheDeck_1_1();
		break;
		
		case "SharlieEpilog_Alonso_12":
			dialog.text = "Il y a tout un tas de foutu or ici, capitaine !";
			link.l1 = "Je vois, "+npchar.name+". Il faut vite tout cacher dans les coffres avant que l’équipage ne voie ça. Ils n’ont pas besoin de telles tentations.";
			link.l1.go = "SharlieEpilog_Alonso_13";
		break;
		
		case "SharlieEpilog_Alonso_13":
			dialog.text = "Non, je ne vais pas résister...";
			link.l1 = "Quoi ?";
			link.l1.go = "exit";
			locCameraFromToPos(-1.28, 7.70, -10.26, true, 0.74, 5.42, -9.49);
			AddDialogExitQuestFunction("SharlieEpilog_GoldInTheDeck_2");
		break;
			
		case "SharlieEpilog_Alonso_21": // этап 2
			dialog.text = "...";
			link.l1 = "Hé, qu'est-ce qui t'arrive ?";
			link.l1.go = "SharlieEpilog_Alonso_22";
			// SharlieEpilog_GoldInTheDeck_6();
		break;
		
		case "SharlieEpilog_Alonso_22":
			dialog.text = "...";
			link.l1 = "Allez, debout. Tu choisis bien ton moment...";
			link.l1.go = "SharlieEpilog_Alonso_23";
		break;
		
		case "SharlieEpilog_Alonso_23":
			dialog.text = "Rejoignez-nous, cap’taine.";
			link.l1 = "Lève-toi, arrête de faire l’imbécile.";
			link.l1.go = "SharlieEpilog_Alonso_24";
		break;
		
		case "SharlieEpilog_Alonso_24":
			dialog.text = "Détendez-vous. Il faut le ressentir.";
			link.l1 = "D'accord, tant pis pour toi. Allez, pousse-toi.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_GoldInTheDeck_7");
		break;
		
		case "SharlieEpilog_Alonso_31": // этап 3
			dialog.text = "J'ai toujours rêvé de faire ça...";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Alonso_32";
			SharlieEpilog_GoldInTheDeck_10();
		break;
		
		case "SharlieEpilog_Alonso_32":
			dialog.text = "Quelle sensation magnifique, n’est-ce pas, capitaine ?";
			link.l1 = "Ah ah ah. Voilà comment on visite les Caraïbes – juste pour prendre des nouvelles de son frère. Papa ne s’attendait sûrement pas à un tel retournement. Ah ah !";
			link.l1.go = "SharlieEpilog_Alonso_33";
		break;
		
		case "SharlieEpilog_Alonso_33":
			dialog.text = "Monseigneur "+GetTitle(NPChar,false)+" "+pchar.lastname+"... Ha ha ! Vous souvenez-vous de comment vous êtes arrivé dans l’archipel ?";
			link.l1 = "Je m’en souviens très bien. Ha ha. J’ai du mal à croire qu’un jour j’étais aussi fringant que ce jeune homme qui se pavane sur le pont. Tant de choses vécues dans ces maudites Caraïbes… Intrigues, morts-vivants, ce bon vieux Kukulkan…";
			link.l1.go = "SharlieEpilog_Alonso_34";
		break;
		
		case "SharlieEpilog_Alonso_34":
			dialog.text = "Vous avez un sacré coup de chance, capitaine. Amasser une telle fortune et rester en vie… ce n’est pas donné à tout le monde.";
			link.l1 = "Bon. Allez, assez traîné. On ne sait jamais, quelqu’un pourrait vraiment finir par nous remarquer.";
			link.l1.go = "exit";
			locCameraSleep(true);
			AddDialogExitQuestFunction("SharlieEpilog_GoldInTheDeck_11");
		break;
		
		// диалоги в катсцене с брашпилем
		case "SharlieEpilog_windlass_1":
			dialog.text = "...";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				link.l1 = "Écoute, mon ami, je n’aime pas du tout le cliquet du cabestan sur ce navire. Il est bien trop peu fiable. Quelqu’un pourrait l’enclencher par inadvertance.";
			}
			else
			{
				link.l1 = "Écoutez, capitaine, je n’aime pas du tout le système de sécurité du cabestan sur ce navire. Il me paraît bien trop peu fiable. Quelqu’un pourrait l’enclencher par mégarde.";
			}
			link.l1.go = "SharlieEpilog_windlass_2";
			locCameraFromToPos(-7.57, 9.68, -21.21, true, -9.79, 7.76, -20.01);
		break;
		
		case "SharlieEpilog_windlass_2":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Laisse tomber, "+pchar.name+", sur le navire, tout le monde sait que…";
			}
			else
			{
				dialog.text = "Allons, capitaine. Qui irait imaginer une chose pareille...";
			}
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_windlass_3");
		break;
		
		case "SharlieEpilog_windlass_3": // диалог Пикара и дворянина
			dialog.text = "Hé, toi, espèce d’andouille... Qu’est-ce que tu fabriques, bon sang ? On t’a jamais appris à ne pas fourrer tes sales pattes n’importe où ?";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_windlass_4";
			locCameraFromToPos(-10.28, 9.94, -22.90, true, -9.29, 7.86, -21.36);
			NPCsLookEachOther("SharlieEpilog_Pikar", "SharlieEpilog_Bernard_Clone");
			CharacterTurnByChr(pchar, CharacterFromID("SharlieEpilog_Bernard_Clone"));
		break;
		
		case "SharlieEpilog_windlass_4":
			dialog.text = "...";
			link.l1 = "Du calme, ne t’emporte pas ! Je suis un gentilhomme, et je ne tolérerai pas ça…";
			link.l1.go = "SharlieEpilog_windlass_5";
		break;
		
		case "SharlieEpilog_windlass_5":
			dialog.text = "Sur mon navire, tu n’es personne. Même mes matelots ont ici plus de droits que toi. Alors, soit tu restes tranquille sans déranger personne, soit je te jette moi-même par-dessus bord.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_windlass_6";
		break;
		
		case "SharlieEpilog_windlass_6": // диалог Пикара и Шарля
			dialog.text = "...";
			link.l1 = "Ha ha ha. J’ai eu l’impression de me voir de l’extérieur.";
			link.l1.go = "SharlieEpilog_windlass_7";
			SharlieEpilog_windlass_9_1();
		break;
		
		case "SharlieEpilog_windlass_7":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "De quoi tu parles ?";
				link.l1 = "Ouais, peu importe, "+npchar.name+". Ne sois pas si dur avec notre passager. Tout ça est encore nouveau pour lui. Après tout, nous non plus, on n’est pas devenus des loups de mer en un jour.";
			}
			else
			{
				dialog.text = "De quoi parlez-vous ?";
				link.l1 = "N’y faites pas attention, "+npchar.name+". Et ne jugez pas trop sévèrement votre passager. Tout cela est nouveau pour lui. Après tout, nous non plus, nous ne sommes pas devenus des loups de mer du jour au lendemain.";
			}
			link.l1.go = "SharlieEpilog_windlass_8";
		break;
		
		case "SharlieEpilog_windlass_8":
			dialog.text = "Avec son talent, il finirait plutôt enroulé autour du cabestan qu’à devenir marin. Faut le faire, quand même…";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				link.l1 = "Qui sait, qui sait. Je suis arrivé sur l’archipel tout aussi insouciant, curieux et arrogant que jamais.";
			}
			else
			{
				link.l1 = "Qui sait. Quand je suis arrivé sur l’archipel, j’étais moi aussi un jeune homme insouciant, curieux et un peu trop sûr de moi.";
			}
			link.l1.go = "SharlieEpilog_windlass_9";
		break;
		
		case "SharlieEpilog_windlass_9":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Tu parles d’une comparaison.\n"+"Attends\n"+"Alors tu te reconnais en lui ? Ha ha ha. Dans ce cas, prends-le sous ta responsabilité. Moi, je ne vais pas jouer les nourrices avec lui.";
				link.l1 = "Je vais garder un œil sur lui. Jusqu’à ce que tu lui fasses la peau. Mais pour l’ancre, il doit payer jusqu’au dernier sou.";
			}
			else
			{
				dialog.text = "Alors, vous vous êtes reconnu en lui ? Ha ha. Eh bien, capitaine, prenez-le donc sous votre aile. Moi, je ne vais pas le materner.";
				link.l1 = "Je vais garder un œil sur lui. Tant que vous ne l’avez pas déjà écorché vif. Mais pour l’ancre – qu’il paie comme il se doit.";
			}
			link.l1.go = "SharlieEpilog_windlass_10";
		break;
		
		case "SharlieEpilog_windlass_10":
			dialog.text = "Choisissez l’ancre. On attend le vent. Gardez le cap.";
			link.l1 = "...";
			link.l1.go = "exit";
			SharlieEpilog_windlass_10();
			AddDialogExitQuestFunction("SharlieEpilog_AlonsoTrollingHighSailor_1");
		break;
		
		// диалоги Старшего матроса и Алонсо		
		case "SharlieEpilog_AlonsoTrollingHighSailor_2": // Алонсо
			dialog.text = "";
			link.l1 = "Levez l’ancre. Captez le vent. Cap au nord-est.";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_3";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_2();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_3": // Старший матрос
			dialog.text = "";
			link.l1 = "Levez l’ancre ! Abaissez le foc – on va attraper le vent. Au travail...";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_4";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_1();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_4": // Алонсо
			dialog.text = "";
			link.l1 = "Qu'est-ce que tu fais ?";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_5";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_2();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_5": // Старший матрос
			dialog.text = "";
			link.l1 = "Qu'est-ce que tu fais ?";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_6";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_1();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_6": // Алонсо
			dialog.text = "";
			link.l1 = "Non, qu'est-ce que tu fais ?";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_7";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_2();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_7": // Старший матрос
			dialog.text = "";
			link.l1 = "Argh... Qu'est-ce que tu fais ? Le maître d'équipage répète les ordres du capitaine.";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_8";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_1();
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_8": // Алонсо
			dialog.text = "";
			link.l1 = "Alors le maître d'équipage les répète à son tour.";
			link.l1.go = "exit";
			SharlieEpilog_AlonsoTrollingHighSailor_camera_2();
			AddDialogExitQuestFunction("SharlieEpilog_AlonsoTrollingHighSailor_2");
		break;
		
		// Шарль ругает Алонсо
		case "SharlieEpilog_AlonsoTrollingHighSailor_9":
			dialog.text = "...";
			link.l1 = "Laisse tomber, Alonso. Nous ne sommes ici que des passagers. Tu as oublié ?";
			link.l1.go = "SharlieEpilog_AlonsoTrollingHighSailor_10";
			locCameraFromToPos(-8.00, 4.49, -1.91, true, -9.97, 2.64, -1.90);
		break;
		
		case "SharlieEpilog_AlonsoTrollingHighSailor_10":
			dialog.text = "Euh... Désolé, capitaine. Je n'ai pas pu m'en empêcher\nMais ça en valait la peine. C'était comme un voyage dans le passé.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_AlonsoTrollingHighSailor_5");
		break;
		
		// Диалог Шарля с Пикаром о всяком (можно попасть в Поместье де Монпе)
		case "SharlieEpilog_PikarOnUliss":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+"... Que désirez-vous ? ";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_A"))
				{
					link.l1 = "Alors, mon ami, comment tu te sens ?";
					link.l1.go = "SharlieEpilog_PikarOnUliss_A_1";
				}
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_B"))
				{
					if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarAlive"))
					{
						link.l2 = "Avoue, "+npchar.name+", tu avais déjà décidé de devenir marchand quand tu as choisi de quitter Tirax, non ?";
						link.l2.go = "SharlieEpilog_PikarOnUliss_B_1";
					}
					else
					{
						link.l2 = "Avoue, "+npchar.name+", tu avais déjà décidé de devenir marchand à l’époque, sur la plantation ?";
						link.l2.go = "SharlieEpilog_PikarOnUliss_B_1";
					}
				}
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_C"))
				{
					link.l3 = "Je me souviens très bien qu’un messager a essayé de me parler. Mais impossible de me rappeler pourquoi, même sous la torture. Tu n’en saurais pas plus, par hasard ?";
					link.l3.go = "SharlieEpilog_PikarOnUliss_C_1";
				}
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_E"))
				{
					link.l1 = "Vous êtes déjà allé à Bordeaux, capitaine ?";
					link.l1.go = "SharlieEpilog_PikarOnUliss_E_1";
				}
				if (!CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_F"))
				{
					link.l2 = "Capitaine, à vrai dire, je ne me souviens même plus vraiment comment nous avons quitté la Martinique. Je devais recevoir un courrier important d'une certaine personne, mais il semble bien que je ne l'ai jamais eu. Personne ne vous a parlé de ça, par hasard ?";
					link.l2.go = "SharlieEpilog_PikarOnUliss_F_1";
				}
			}
			link.l4 = "Il semble qu’une légère brise se lève. Il est temps de déployer les voiles. (Prendre la mer)";
			link.l4.go = "SharlieEpilog_PikarOnUliss_D_1";
			link.l5 = "Rien pour l’instant. Je vais y aller.";
			link.l5.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_A_1":
			dialog.text = "Ha ha... Comme jamais auparavant ! Plein de force et de santé.";
			link.l1 = "Vraiment ? On dirait pourtant qu’un requin t’a mâchouillé.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_A_2";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_A = true;
		break;

		case "SharlieEpilog_PikarOnUliss_A_2":
			dialog.text = "Tu parles ! Tu as l’air d’un chien battu, toi aussi.";
			link.l1 = "Et je me sens pareil. Ha ha. Bon sang, je ne me souviens même plus comment ni quand on a levé l’ancre.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_A_3";
		break;

		case "SharlieEpilog_PikarOnUliss_A_3":
			dialog.text = "Ah, quelle sacrée fête c’était. Mais diablement chère. Mes idiots ont failli mettre le feu au bordel – j’ai dû lâcher un sac de pièces pour étouffer l’affaire. Du coup, ces crétins me seront redevables jusqu’à la fin de leurs jours.\nAlors, comment tu te sens dans la peau d’un passager ? Tu n’as pas encore commencé à hurler d’ennui ?";
			link.l1 = "J’ai l’impression que mon destin ne m’appartient plus. Mais en même temps, je ressens un étrange soulagement. Comme si j’avais déposé un lourd coffre de boulets d’épaule.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_A_4";
		break;

		case "SharlieEpilog_PikarOnUliss_A_4":
			dialog.text = "Ha ha. Eh bien, si jamais la mélancolie te gagne, je suis prêt à t’accueillir comme officier à mon bord.";
			link.l1 = "C'est très généreux de ta part, mais je dois refuser. Il n'y a pas assez de rhum dans tout les Caraïbes pour alimenter nos fêtes.";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_1":
			if (IsStateTitle()) 
			{
				dialog.text = "Pas vraiment, mon pote. Cette idée m’a parfois traversé l’esprit, mais je n’y ai jamais vraiment prêté attention. Elle m’est revenue une seconde fois quand j’ai entendu dire que toute la bande des chiens fidèles de Tirax avait disparu sans laisser de traces. Tous, sans exception – le Coutelas, le Chauve, et même cette vieille loque puante de Leprechaun.\nEt puis, quand j’ai appris quels exploits tu avais accomplis, j’ai décidé pour de bon que j’en avais assez. On ne peut pas risquer sa peau pour quelques pièces toute sa vie.\nJ’ai assez d’or pour ne jamais ramper devant un seul salopard en perruque. Mais quitter la mer… ça, je n’y étais pas prêt. Alors j’ai choisi de changer de métier.";
			} 
			else 
			{
				dialog.text = "Pas vraiment, mon pote. L’idée m’a déjà traversé l’esprit de temps en temps, mais je n’y prêtais pas vraiment attention. Elle m’est revenue une seconde fois quand j’ai entendu dire que toute la bande des fidèles molosses de Tirax avait disparu sans laisser de trace. Tous, sans exception – Machette, Le Chauve, et même ce vieux dégoûtant de Leprechaun.\nEt puis, quand les boulets ennemis ont failli me faire sauter la cervelle deux fois dans le même combat, j’ai décidé que ça suffisait. On ne peut pas risquer sa tête pour quelques pièces toute sa vie.\nJ’ai assez d’or pour ne jamais ramper devant un salaud en perruque. Mais quitter la mer… ça, je n’y étais pas prêt. Alors j’ai choisi de changer de métier.";
			}
			link.l1 = "Couperet, Le Chauve, Le Leprechaun... Tu sais où ils ont disparu ?";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_2";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_B = true;
		break;

		case "SharlieEpilog_PikarOnUliss_B_2":
			dialog.text = "Non, je ne sais pas. Et franchement, je m’en fiche de savoir où ces saletés ont filé. Même si c’est droit en enfer.";
			link.l1 = "C'est à peu près là que je les ai envoyés.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_3";
		break;

		case "SharlieEpilog_PikarOnUliss_B_3":
			dialog.text = "Alors c’est toi qui as décimé toute leur bande ? Eh bien dis donc ! Et Marcus t’a pardonné ça ?";
			link.l1 = "Il ne le sait pas. Et il ne le saura probablement jamais.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_4";
		break;

		case "SharlieEpilog_PikarOnUliss_B_4":
			dialog.text = "Alors, bon sang, j’ai bien fait de les quitter à temps, ha ha. Tu m’aurais peut-être même pas épargné la tête, hein ?\nMais y a un truc que je pige pas – pourquoi diable t’as eu besoin de tout ça ?";
			link.l1 = "Tu avais raison – pour un misérable morceau d’or, ces salauds seraient prêts à s’étrangler, à trahir, à tuer n’importe qui. On nous a attirés dans un des souterrains, sur le Main du Sud, en nous racontant des histoires de trésors fabuleux. C’était un piège soigneusement préparé, et ces foutus brutes ont mordu à l’hameçon sans réfléchir. Au lieu de partager le butin équitablement, ils ont décidé qu’il valait mieux ne rien partager du tout, qu’il suffisait de me liquider et de tout garder pour eux.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_5";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_5":
			dialog.text = "Et ils n’y sont pas arrivés, ces idiots, ha ha ! Attends, mais qui a bien pu tendre ce piège ?";
			if (CharacterIsAlive("Tonzag") && CheckPassengerInCharacter(pchar, "Tonzag"))
			{
				link.l1 = "Un certain Zorro, justicier populaire espagnol – pour venger Carthagène. Celui qui aurait survécu à ce massacre devait rester à jamais dans les souterrains – toutes les issues étaient verrouillées. Mais ce salaud n’a pas eu de chance – mon officier l’a roulé.";
			}
			else
			{
				link.l1 = "Un certain Zorro, justicier populaire espagnol – pour venger Carthagène. Celui qui aurait survécu à ce carnage infernal devait rester à jamais dans les souterrains – toutes les issues étaient hermétiquement closes. J’ai réussi à m’en échapper. Mais à un prix très élevé.";
			}
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_6";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_6":
			dialog.text = "Au moins, tu es encore en vie. Et j’imagine que tu as récupéré tout l’or pour lequel tu as failli y laisser ta peau ?";
			link.l1 = "Il n’y avait pas d’or là-bas. C’était du plomb doré...";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_7";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_7":
			dialog.text = "...";
			link.l1 = "Après tout ça, j’ai décidé de quitter Tirax. Tu es le premier à qui j’en parle. Enfin, si on ne compte pas mes officiers.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_8";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_8":
			dialog.text = "Je n’aime pas dire « je te l’avais bien dit », mais… je te l’avais bien dit.";
			link.l1 = "Savoir s’arrêter à temps, ce n’est pas vraiment mon point fort. Alors il va falloir que tu m’apprennes un peu.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_B_9";
		break;
		
		case "SharlieEpilog_PikarOnUliss_B_9":
			dialog.text = "Tu me connais – pour deux ou trois chopes de bon rhum, je pourrais même te révéler où je planque mon or, hé hé.";
			link.l1 = "Mais ne t’attends pas à tant de générosité de ma part, ha ha ha. Tes provisions te suffiront largement.";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_C_1":
			dialog.text = "Je sais. Il a essayé de te refiler des lettres — soit d’un certain Ben, soit d’un Benoît. Mais tu as grogné que tu ne connaissais aucun Ben et tu as menacé de le jeter dehors s’il continuait à gâcher notre soirée.";
			link.l1 = "Le diable... On dirait que c'étaient des lettres de l'abbé Benoît. Des lettres importantes.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_C_2";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_C = true;
		break;

		case "SharlieEpilog_PikarOnUliss_C_2":
			dialog.text = "Eh bien, tant mieux que je les aie pris. Hé hé.  J’ai senti au fond de moi que ce gamin ne s’était pas trompé de personne. Tiens.";
			link.l1 = "Tu m’as vraiment sauvé la mise, "+npchar.name+", merci.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_C_3";
		break;

		case "SharlieEpilog_PikarOnUliss_C_3":
			dialog.text = "Un simple 'merci', ça ne suffit pas, mon pote. Tu me dois un verre – et pas n'importe lequel, le meilleur qu'on puisse trouver à Bordeaux.";
			link.l1 = "Tu vas l’avoir, ta boisson, mendiant. Le rhum ici ne vaut pas celui des Caraïbes, mais le vin… Ça, tu n’en as sûrement jamais goûté d’aussi bon.";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_E_1":
			dialog.text = "Jamais eu l'occasion...";
			link.l1 = "Je vous envie. J’aimerais revoir Bordeaux comme la première fois. Vous préférez sans doute le rhum, mais je vous conseille tout de même de passer à la foire aux vins près de l’hôtel de ville. Ici, les connaisseurs paient une fortune pour notre clairet.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_E_2";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_E = true;
		break;

		case "SharlieEpilog_PikarOnUliss_E_2":
			dialog.text = "Merci pour le conseil. Puis-je vous poser une question ?";
			link.l1 = "Bien sûr.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_E_3";
		break;

		case "SharlieEpilog_PikarOnUliss_E_3":
			dialog.text = "Qu'est-ce que ça fait d'être passagère après tant d'années à la barre ? Vous êtes déjà habituée à ce nouveau rôle ?";
			link.l1 = "Hum... J'ai l'impression de ne plus tenir mon destin entre mes mains. Mais en même temps, je ressens un étrange soulagement. Comme si j'avais déposé un lourd fardeau de mes épaules. Je crois qu'il est encore trop tôt pour tirer des conclusions.";
			link.l1.go = "SharlieEpilog_PikarOnUliss_E_4";
		break;

		case "SharlieEpilog_PikarOnUliss_E_4":
			dialog.text = "Vu la foutue pétole dans laquelle on s’est retrouvés, vous aurez tout le temps du monde.";
			link.l1 = "En bonne compagnie, même le calme plat ne pèse pas. Et il faut avouer, capitaine, que j’ai eu de la chance avec la compagnie.";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
		break;
		
		case "SharlieEpilog_PikarOnUliss_F_1":
			dialog.text = "Oui, il y en a eu. Un messager d’un certain abbé. J’oublie toujours de vous remettre ces lettres. Tenez, les voilà.";
			link.l1 = "Excellent. Vous m'avez vraiment rendu service, capitaine. Je vous remercie.";
			link.l1.go = "SharlieEpilog_PikarOnUliss";
			pchar.questTemp.SharlieEpilog_PikarOnUliss_F = true;
		break;
		
		case "SharlieEpilog_PikarOnUliss_D_1":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PikarOnUliss_A")){dialog.text = "Tu as raison.";}
			else {dialog.text = "Vous avez raison.";}
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarOnUliss_D_2";
		break;
		
		case "SharlieEpilog_PikarOnUliss_D_2":
			dialog.text = "Vent tribord ! Toutes voiles dehors, du foc à la brigantine ! En avant toute !";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_InEstateDeMonpe";
			locCameraFromToPos(-9.34, 8.28, -16.03, true, -9.33, 7.32, -20.48);
			CharacterTurnToLoc(CharacterFromID("SharlieEpilog_Pikar"), "quest", "quest10");
		break;
		
		case "SharlieEpilog_InEstateDeMonpe":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_InEstateDeMonpe");
		break;
		
		//Матрос 1 на верхней палубе
		case "SharlieEpilog_Sailor_1":
			dialog.text = "Une excellente lame, "+GetTitle(NPChar,true)+". Je peux jeter un œil ?";
			link.l1 = "Peut-être une autre fois.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Sailor_1";
			PlaySound("Voice\" + LanguageGetLanguage() + "\officer05.wav");
		break;
		
		//Матрос 2 на верхней палубе
		case "SharlieEpilog_Sailor_2":
			dialog.text = "Quand est-ce qu’on va enfin sonner la cloche ? Je vais finir par avaler ma langue.";
			link.l1 = "Patience, matelot.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Sailor_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\other\Matrosi na Korablyah-07.wav");
		break;
		
		//Матрос 3 на орудийной палубе
		case "SharlieEpilog_Sailor_3":
			dialog.text = "Vous avez vu ce rat qui vient de passer ? Je vous jure, j’en ai jamais vu d’aussi énormes !";
			link.l1 = "Mouais...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Sailor_3";
			PlaySound("Voice\" + LanguageGetLanguage() + "\other\Matrosi na Korablyah-04.wav");
		break;
		
		//Матрос 4 на орудийной палубе
		case "SharlieEpilog_Sailor_4":
			dialog.text = "Qu'est-ce que je vais faire maintenant, monsieur ? J'ai tellement bu que je ne me souviens même plus comment je me suis retrouvé sur ce navire. Je ne suis pas du tout marin... Et chez moi, il y a ma femme, deux enfants.";
			link.l1 = "Il fallait moins boire. Maintenant, c’est trop tard – il va falloir devenir marin.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Sailor_4";
			PlaySound("Voice\" + LanguageGetLanguage() + "\Ransack_2.wav");
		break;
		
		//Старший матрос
		case "SharlieEpilog_HighSailor_1":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+". C'est un honneur pour nous de vous accueillir à bord de notre navire.";
			link.l1 = "Vous êtes bien courtois, monsieur le maître d’équipage. La politesse n’est pas la qualité la plus répandue parmi les vieux loups de mer. Mais ne mettons pas l’équipage mal à l’aise – nous ne sommes pas à la cour de Sa Majesté. Appelle-moi simplement : capitaine.";
			link.l1.go = "SharlieEpilog_HighSailor_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\YoungMan03.wav");
		break;

		case "SharlieEpilog_HighSailor_2":
			dialog.text = "Eh bien, je ne suis devenu marin que récemment. Avant, j’étais scribe chez monsieur Levasseur. Et quand il a été… hum… éliminé, un nouveau gouverneur est arrivé. Dans les cercles restreints, on a vite appris à quel point le sieur de René de Baudoufle de Lestre était un vaurien. Là, j’ai compris que je ne trouverais plus jamais de travail honnête. Les gens penseraient que je savais tout – et que je me suis tu.";
			link.l1 = "Et ce n’était pas le cas ?";
			link.l1.go = "SharlieEpilog_HighSailor_3";
		break;

		case "SharlieEpilog_HighSailor_3":
			dialog.text = "Bien sûr que non. Je n’ai jamais eu l’habitude de me mêler de ce qui ne me regarde pas. En plus, Levasseur punissait sévèrement la curiosité.";
			link.l1 = "Je veux bien le croire.";
			link.l1.go = "SharlieEpilog_HighSailor_4";
		break;

		case "SharlieEpilog_HighSailor_4":
			dialog.text = "Alors, quand vous l’avez éliminé, je me suis engagé comme matelot sur le premier navire pirate venu. Et, chose étrange, je me suis vite adapté et transformé. J’ai même réussi à gagner le respect des pires coupe-jarrets. Mais ce qu’ils faisaient… ça ne me plaisait pas. C’est comme ça que je me suis retrouvé ici.";
			link.l1 = "Alors, tu savais que j'avais pris part au destin de Levasseur ?";
			link.l1.go = "SharlieEpilog_HighSailor_5";
		break;

		case "SharlieEpilog_HighSailor_5":
			dialog.text = "Bien sûr, capitaine. Et je suis heureux que vous ayez débarrassé le monde de ce monstre. En même temps, vous m’avez sorti de mon trou à rats. Vous m’avez forcé à voir ma vie autrement.";
			link.l1 = "Incroyable comme le monde est petit...";
			link.l1.go = "SharlieEpilog_HighSailor_6";
		break;

		case "SharlieEpilog_HighSailor_6":
			dialog.text = "Aussi paradoxal que cela puisse paraître, le monde est à la fois minuscule et immense.";
			link.l1 = "C'est drôle. Je n'y avais jamais pensé.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_HighSailor_7";
		break;
		
		case "SharlieEpilog_HighSailor_7":
			dialog.text = "Capitaine "+pchar.lastname+"... Quelle soirée merveilleuse, n'est-ce pas ?";
			link.l1 = "Sans doute. Seule une brise modérée du nord-ouest pourrait rendre ce moment encore plus parfait.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_HighSailor_7";
			PlaySound("Voice\" + LanguageGetLanguage() + "\YoungMan03.wav");
		break;
		
		//Диалог с боцманом Моко
		case "SharlieEpilog_Moko_1":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Capitaine "+pchar.lastname+"...";
				link.l1 = "En fait… Enfin, peu importe. Je me souviens de toi ! Tu t’appelles Moko. C’est bien toi qui as vidé tout un tonneau de rhum d’un coup ?";
				link.l1.go = "SharlieEpilog_Moko_2";
			}
			else
			{
				dialog.text = "Que voulez-vous… monsieur ?";
				link.l1 = "Ce n’est pas tous les jours qu’on croise un gaillard comme toi. Comment tu t’appelles ?";
				link.l1.go = "SharlieEpilog_Moko_4";
			}
			PlaySound("Voice\" + LanguageGetLanguage() + "\citizen\Kapitani Korabley-07.wav");
		break;

		case "SharlieEpilog_Moko_2":
			dialog.text = "Je... Et je ne me suis réveillé que deux jours plus tard.";
			link.l1 = "Un autre à ta place n’aurait pas tenu deux heures. Si tu te bats aussi bien que tu bois, Jean a rudement de la chance d’avoir un bosco comme toi.";
			link.l1.go = "SharlieEpilog_Moko_3";
		break;

		case "SharlieEpilog_Moko_3":
			dialog.text = "Moi aussi, j’ai eu de la chance avec mon capitaine. C’est grâce à lui que j’ai retrouvé la liberté. Et grâce à vous aussi. Je croupirais encore sur les plantations si vous n’aviez pas aidé Jean.";
			link.l1 = "C'était une aventure intéressante. Et je suis content qu'elle se soit terminée mieux que ce que j'aurais pu craindre.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Moko_repeat";
		break;
		
		case "SharlieEpilog_Moko_4":
			dialog.text = ""+npchar.name+". Je suis le maître d'équipage sur ce navire.";
			link.l1 = "Ha ha, j’aimerais bien voir celui qui oserait te contredire. Tu sers le capitaine depuis longtemps ?";
			link.l1.go = "SharlieEpilog_Moko_5";
		break;

		case "SharlieEpilog_Moko_5":
			dialog.text = "Quelques années. Je lui dois beaucoup. Sans lui, je serais pourri dans...";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Moko_6";
		break;

		case "SharlieEpilog_Moko_6":
			dialog.text = "...";
			link.l1 = "Tu voulais dire – à la plantation ?";
			link.l1.go = "SharlieEpilog_Moko_7";
		break;

		case "SharlieEpilog_Moko_7":
			dialog.text = "...";
			link.l1 = "Laisse tomber, "+npchar.name+", tu sais, tu n’es pas obligé de tout me raconter, mais au cas où tu ne l’aurais pas remarqué, je ne fais pas partie de ces précieux en perruque. Le capitaine t’a racheté ?";
			link.l1.go = "SharlieEpilog_Moko_8";
		break;

		case "SharlieEpilog_Moko_8":
			dialog.text = "Nous nous sommes enfuis ensemble. De la plantation à Maracaibo. Sans Jean, nous n’y serions jamais arrivés. Depuis, je fais partie de son équipage. D’abord comme matelot, et maintenant – je suis le bosco.";
			link.l1 = "Le capitaine a été esclave ? Jamais je n’aurais cru ça. Enfin, moi aussi j’ai quelques squelettes dans le placard. Content que tu sois sorti de sous la botte espagnole, "+npchar.name+". Alors, ça te fait quoi d’être marin ?";
			link.l1.go = "SharlieEpilog_Moko_9";
		break;

		case "SharlieEpilog_Moko_9":
			dialog.text = "Comme si je n’avais jamais vraiment vécu avant. La mer, c’est ma maison maintenant.";
			link.l1 = "Là, je te comprends, mon ami. Comme personne d'autre.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Moko_repeat";
		break;
		
		case "SharlieEpilog_Moko_repeat":
			dialog.text = "Capitaine "+pchar.lastname+"... En quoi puis-je vous aider ?";
			link.l1 = "Merci, "+npchar.name+", pour l’instant je n’ai besoin de rien.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Moko_repeat";
		break;
		
		//Диалог с дворянином Бернардом
		case "SharlieEpilog_Bernard_1":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,true))+"! Quel bonheur de voir enfin un visage sensé sur ce navire. Ces... marins... ce sont des barbares.";
			link.l1 = "À votre place, je ne parlerais pas ainsi à bord d’un navire étranger. Je ne sais pas comment vous êtes arrivé aux Caraïbes, mais ici, voyez-vous, les règles sont différentes. Vous feriez mieux de montrer un peu de respect à l’équipage.";
			link.l1.go = "SharlieEpilog_Bernard_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\citizen\Dvoryane-06.wav");
		break;

		case "SharlieEpilog_Bernard_2":
			dialog.text = "Du respect ? Pour eux ? Ce sont des sauvages ! Je suis un noble, "+GetTitle(NPChar,true)+", j’ai l’habitude de l’ordre, du service, de… la civilisation ! Qu’ils essaient seulement de me contredire – mon père les…";
			link.l1 = "Votre père apprendra que vous êtes mort de la fièvre en chemin. Et il aura bien du mal à prouver le contraire.";
			link.l1.go = "SharlieEpilog_Bernard_3";
		break;

		case "SharlieEpilog_Bernard_3":
			dialog.text = "Que le colonel Fox soit maudit ! Tout ça, c’est à cause de lui ! Pour sa fille, j’ai traversé l’océan, sacrifié mon confort, supporté ces regards de travers, cette nourriture infecte, ce... tangage ! Et maintenant, je me retrouve à naviguer sur un navire qui n’est même pas le mien !";
			link.l1 = "Colonel Fox…";
			link.l1.go = "SharlieEpilog_Bernard_4";
		break;

		case "SharlieEpilog_Bernard_4":
			dialog.text = "Vous le connaissez, "+GetTitle(NPChar,true)+"?";
			link.l1 = "Hum... J'ai entendu parler de lui.";
			link.l1.go = "SharlieEpilog_Bernard_5";
		break;

		case "SharlieEpilog_Bernard_5":
			dialog.text = "Eh bien, vous n’avez pas perdu grand-chose. Cet homme incarne l’entêtement aveugle du soldat et tous ses préjugés.";
			link.l1 = "C'est un militaire...";
			link.l1.go = "SharlieEpilog_Bernard_6";
		break;

		case "SharlieEpilog_Bernard_6":
			dialog.text = "Exactement ! Tout est dit. Quand je suis venu demander à voir sa fille, vous savez ce qu’il a fait ? Vous savez ? Il m’a mis à la porte ! Sans un mot !";
			link.l1 = "Mais vous, apparemment, vous n’avez pas reculé ?";
			link.l1.go = "SharlieEpilog_Bernard_7";
		break;

		case "SharlieEpilog_Bernard_7":
			dialog.text = "Bien sûr ! J’ai essayé d’obtenir une audience pendant toute une semaine ! Je me suis humilié ! J’ai même... proposé un pot-de-vin à la garde ! Finalement, j’ai réussi à me faufiler jusqu’à lui, sans invitation. Je voulais juste lui parler !";
			link.l1 = "Je ne pense pas qu'il en ait été ravi.";
			link.l1.go = "SharlieEpilog_Bernard_8";
		break;

		case "SharlieEpilog_Bernard_8":
			dialog.text = "Content ? Oh, il a fait une véritable crise ! On m’a mise à la porte, interdit d’approcher de la résidence, confisqué le navire de mon père, et pour finir, tous les capitaines anglais ont reçu l’ordre de ne pas m’embarquer ! J’ai dû chercher un navire français à la Martinique… Un vrai cauchemar.";
			link.l1 = "On dirait que vous l'avez vraiment mis en colère.";
			link.l1.go = "SharlieEpilog_Bernard_9";
		break;

		case "SharlieEpilog_Bernard_9":
			dialog.text = "Il a toujours été contre moi. Sa phrase préférée : « Fille d’officier, femme d’officier. » Vous, "+GetTitle(NPChar,true)+", il a estimé qu’elle était un parti bien plus convenable.";
			link.l1 = "Peut-être qu'il avait d'autres raisons cette fois-ci...";
			link.l1.go = "SharlieEpilog_Bernard_10";
		break;

		case "SharlieEpilog_Bernard_10":
			dialog.text = "...";
			link.l1 = "Alors, vous êtes venu ici pour retrouver votre bien-aimée.";
			link.l1.go = "SharlieEpilog_Bernard_11";
		break;

		case "SharlieEpilog_Bernard_11":
			dialog.text = "Oui. Je n’ai pas reçu une seule lettre d’elle depuis qu’elle a quitté l’Europe. Je suis sûr que c’est son père qui intercepte notre correspondance. Elle ne pouvait pas m’oublier ! Bien sûr, elle était réservée avec moi… même froide… Mais je refuse de croire qu’elle m’ait rayé de sa vie.";
			link.l1 = "Je compatis, monsieur. Les blessures de l’âme guérissent bien plus difficilement que celles du corps. Attendez… Pourquoi, vous, un Anglais, allez-vous à Bordeaux ?";
			link.l1.go = "SharlieEpilog_Bernard_12";
		break;

		case "SharlieEpilog_Bernard_12":
			dialog.text = "Je n’ai pas l’intention de rentrer chez moi couvert de honte. Il va falloir que je reste quelque temps chez mon oncle à Bordeaux, le temps que tout ça se tasse. D’ailleurs, son domaine est bien plus vaste et élégant que le nôtre. Et puis, son personnel est bien mieux formé.";
			link.l1 = "Eh bien, ce n’est sans doute pas la pire des solutions. Peut-être trouverez-vous même une autre élue. Bordeaux ne manque pas de jeunes beautés, croyez-moi.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Bernard_repeat";
		break;
		
		case "SharlieEpilog_Bernard_repeat":
			dialog.text = "Quand est-ce qu'on va enfin arriver, "+GetTitle(NPChar,true)+"? Je souffre atrocement entourée de tous ces... messieurs. Il me faut absolument prendre un bain au plus vite.";
			link.l1 = "Je crains que, pendant les deux prochains mois, il ne vous reste plus qu’à rêver d’elle.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Bernard_repeat";
			PlaySound("Voice\" + LanguageGetLanguage() + "\citizen\Dvoryane-06.wav");
		break;
		
		//Диалог с Книппелем на корабле Улисс
		case "SharlieEpilog_Knippel_1":
			dialog.text = "Maudit calme plat, qu’un boulet de mitraille l’emporte.";
			link.l1 = "Ne râle pas, "+npchar.name+", tôt ou tard le vent se lèvera.";
			link.l1.go = "SharlieEpilog_Knippel_2";
		break;

		case "SharlieEpilog_Knippel_2":
			dialog.text = "Et qu'est-ce qu'on fait en attendant, monsieur ? Je ne peux même pas inspecter les canons... On est quand même sur un navire qui n'est pas le nôtre.";
			link.l1 = "Essaie juste de te reposer. Il n'y a pas que le travail dans la vie.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Knippel_repeat";
		break;
		
		case "SharlieEpilog_Knippel_repeat":
			dialog.text = "Maudit calme plat...";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Knippel_repeat";
		break;
		
		//Диалог с Лонгвэем на корабле Улисс
		case "SharlieEpilog_Longway_1":
			dialog.text = "Pas mal, ce navire, monsieur le capitaine. Vous pensez la même chose ?";
			link.l1 = "Encore mieux que Meifeng ?";
			link.l1.go = "SharlieEpilog_Longway_2";
		break;

		case "SharlieEpilog_Longway_2":
			dialog.text = "Pour "+npchar.name+" Aucun navire n’est meilleur que le Meifeng. Aucun autre ne remontera jamais le vent aussi bien que lui. ";
			link.l1 = "Du calme, "+npchar.name+", je plaisantais. Bien sûr, Meifeng est hors concours. Mais l’Ulysse est aussi un bon navire. Solide.";
			link.l1.go = "SharlieEpilog_Longway_3";
		break;

		case "SharlieEpilog_Longway_3":
			dialog.text = ""+npchar.name+" vouloir prendre la barre. Sentir le navire obéir à la main...";
			link.l1 = "Hélas, mon ami, ce navire ne nous appartient pas. Tu ferais mieux de proposer à ce grand gaillard là-bas de t’entraîner à l’escrime. Ça ne pourra que vous faire du bien à tous les deux.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Longway_repeat";
		break;
		
		case "SharlieEpilog_Longway_repeat":
			dialog.text = "À quelle vitesse pourrons-nous aller si le vent est favorable ?";
			link.l1 = "Ça, je ne peux pas te le dire avec certitude, "+npchar.name+". Tu ferais mieux de demander à leur navigateur.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Longway_repeat";
		break;
		
		//Диалог с Тонзагом на корабле Улисс
		case "SharlieEpilog_Tonzag_1":
			dialog.text = "Tu as vu le géant qui fait office de maître d’équipage ici ? On raconte qu’il peut écraser une noix de coco d’une seule main.";
			link.l1 = "Ha ha. Je vois que tu le crains un peu, non ?";
			link.l1.go = "SharlieEpilog_Tonzag_2";
		break;

		case "SharlieEpilog_Tonzag_2":
			dialog.text = "Pourquoi donc ? La taille, ça ne fait pas tout. J’en ai déjà terrassé des plus coriaces.";
			link.l1 = "Alors, tu pourrais peut-être lui proposer un combat à mains nues ? Un contre un, à la loyale.";
			link.l1.go = "SharlieEpilog_Tonzag_3";
		break;

		case "SharlieEpilog_Tonzag_3":
			dialog.text = "Argh...";
			link.l1 = "Tu as l’air tout pâle. Ha ha. Bon, tant pis. On va ménager tes os pas si jeunes que ça.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Tonzag_repeat";
		break;
		
		case "SharlieEpilog_Tonzag_repeat":
			dialog.text = "Dans ces eaux, il y a tellement de poissons qu’on pourrait en remplir une barque, et ces fainéants n’ont même pas daigné jeter un filet.";
			link.l1 = "Va parler à leur bosco. Je pense qu’il appréciera ta remarque, hé hé.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Tonzag_repeat";
		break;
		
		//Диалог с Тичингиту, охраняющим золото
		case "SharlieEpilog_Tichingitu_21":
			dialog.text = "L'or est en sécurité, capitaine "+pchar.name+". Dis à Tichingitu de bien le surveiller.";
			link.l1 = "Merci, mon ami. Alonso va bientôt te remplacer.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Tichingitu_21";
		break;
		
		//Диалог с Книппелем, охраняющим золото
		case "SharlieEpilog_Knippel_21":
			dialog.text = "Nom d’un tonneau, monsieur, il y a plus de rats sur cette épave que j’en ai jamais vu de toute ma vie.";
			link.l1 = "Le navire est resté longtemps au port, sans véritable surveillance. Le nouvel équipage s’en débarrassera bientôt.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Knippel_21";
		break;
		
		//Диалог с Лонгвэем, охраняющим золото
		case "SharlieEpilog_Longway_21":
			dialog.text = "Longway entendre le bruit de la chaîne. Capitaine jeter l'ancre ?";
			link.l1 = "C'est notre passager qui a fait sauter le fusible. Le vent est encore très faible, mais j'espère que ça ne durera pas.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Longway_21";
		break;
		
		//Диалог с Тонзагом, охраняющим золото
		case "SharlieEpilog_Tonzag_21":
			dialog.text = "Oui, bon sang... Je ne dirais pas non à une chope de bon rhum, là.";
			link.l1 = "Le dîner sera bientôt prêt, sois patient. Alonso va te relayer.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharlieEpilog_Tonzag_21";
		break;
		
		//Диалог с Мэри перед походом в каюту
		case "SharlieEpilog_Mary_11":
			dialog.text = "...";
			link.l1 = ""+npchar.name+", ma chérie, comment tu te sens ? ";
			link.l1.go = "SharlieEpilog_Mary_12";
			DelLandQuestMark(npchar);
		break;

		case "SharlieEpilog_Mary_12":
			dialog.text = "...";
			link.l1 = "Laisse tomber, chérie, tu es vraiment fâchée contre moi juste parce que je suis allé acheter du vin ?";
			link.l1.go = "SharlieEpilog_Mary_13";
		break;

		case "SharlieEpilog_Mary_13":
			dialog.text = "Aller à la boutique pour du vin ? Tu aurais au moins pu prévenir ! Comment veux-tu que je sache que tu n’étais pas au bordel — avec une fille… ou avec toutes à la fois ?!";
			link.l1 = "Chérie, tu crois vraiment que je prendrais de tels risques ? J’ai la femme la plus belle, la plus intelligente et, il faut bien l’avouer, la plus jalouse de tout l’archipel. Tu penses vraiment que j’irais perdre mon temps avec des filles de port sans intérêt ?";
			link.l1.go = "SharlieEpilog_Mary_14";
		break;

		case "SharlieEpilog_Mary_14":
			dialog.text = "Tu aurais au moins pu me dire un mot, ouais, hein ? Je suis restée là et…";
			link.l1 = "Je te promets, la prochaine fois, je ne me contenterai pas de t’en parler – je t’emmènerai avec moi. Mais pour l’instant… je me demande soudain si tout va bien avec les meubles de la cabine du capitaine. Surtout avec le lit. On vérifie ?";
			link.l1.go = "SharlieEpilog_Mary_15";
		break;

		case "SharlieEpilog_Mary_15":
			dialog.text = ""+pchar.name+"... Et si quelqu’un entrait ?\nHmm… maintenant, j’en ai encore plus envie.";
			link.l1 = "Alors ne perdons pas une seconde.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_1");
		break;
		
		//Диалог с Элен перед походом в каюту
		case "SharlieEpilog_Helena_11":
			dialog.text = "...";
			link.l1 = ""+npchar.name+", ma chérie, comment te sens-tu ?";
			link.l1.go = "SharlieEpilog_Helena_12";
			DelLandQuestMark(npchar);
		break;

		case "SharlieEpilog_Helena_12":
			dialog.text = "...";
			link.l1 = "Laisse tomber, chérie, tu m’en veux vraiment parce que je suis parti acheter du vin ?";
			link.l1.go = "SharlieEpilog_Helena_13";
		break;

		case "SharlieEpilog_Helena_13":
			dialog.text = "Tu aurais pu m’emmener avec toi. Ou tu penses que je m’en serais moins bien sortie que tes complices ?";
			link.l1 = "Je pense que tu les aurais éclipsées sans difficulté. Mais alors, le vin ne serait plus du tout dans mes pensées.";
			link.l1.go = "SharlieEpilog_Helena_14";
		break;

		case "SharlieEpilog_Helena_14":
			dialog.text = "Et de quoi donc ?";
			link.l1 = "Penser à m’isoler avec toi, là-bas… Cette idée ne me quitte pas en ce moment.";
			link.l1.go = "SharlieEpilog_Helena_15";
		break;

		case "SharlieEpilog_Helena_15":
			dialog.text = "Ah bon ? Et où comptes-tu te cacher des regards indiscrets ?";
			link.l1 = "Dans la cabine du capitaine. Je suppose qu'il faudrait tester la solidité de son lit.";
			link.l1.go = "SharlieEpilog_Helena_16";
		break;

		case "SharlieEpilog_Helena_16":
			dialog.text = "Ha ha. Et si le capitaine nous surprenait ?\nQuoique… rien que cette idée fait battre mon cœur plus fort.";
			link.l1 = "Alors ne perdons pas de temps !";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_1");
		break;
		
		//Диалог с Мэри в каюте
		case "SharlieEpilog_Mary_21":
			dialog.text = "C'était merveilleux, mon capitaine...\nJ'ai une nouvelle pour toi.";
			link.l1 = "Une nouvelle ? Je suis tout ouïe.";
			link.l1.go = "SharlieEpilog_Mary_22";
			SharlieEpilog_LoveInCabin_CameraDialog();
		break;

		case "SharlieEpilog_Mary_22":
			dialog.text = ""+pchar.name+"... Nous allons avoir un enfant. Je suis enceinte, ouais, hein.";
			link.l1 = "Chérie... C’est vrai ?";
			link.l1.go = "SharlieEpilog_Mary_23";
		break;

		case "SharlieEpilog_Mary_23":
			dialog.text = "Tu vas être père, "+pchar.name+"!";
			link.l1 = ""+npchar.name+"... C'est incroyable !";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_6");
		break;
		
		case "SharlieEpilog_Mary_31":
			dialog.text = "Tu es heureux, mon amour ?";
			link.l1 = "Heureux ? Tu plaisantes ? Nom de Dieu, je suis l’homme le plus heureux du monde ! Mais… pourquoi tu ne m’en as pas parlé plus tôt ?";
			link.l1.go = "SharlieEpilog_Mary_32";
		break;

		case "SharlieEpilog_Mary_32":
			dialog.text = "Pour retarder le départ ? J’ai vraiment envie de rencontrer ton père, "+pchar.name+".";
			link.l1 = ""+npchar.name+"... Je t'aime !";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_9");
		break;
		
		//Диалог с Элен в каюте
		case "SharlieEpilog_Helena_21":
			dialog.text = "Tu as été, comme toujours, à la hauteur, mon chéri. J'ai une nouvelle pour toi.";
			link.l1 = "Une nouvelle ? Je suis tout ouïe.";
			link.l1.go = "SharlieEpilog_Helena_22";
			SharlieEpilog_LoveInCabin_CameraDialog();
		break;

		case "SharlieEpilog_Helena_22":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+GetFullName(pchar)+", chevalier de Montpe - tu vas devenir père.";
			link.l1 = "C'est... c'est vrai ?";
			link.l1.go = "SharlieEpilog_Helena_23";
		break;

		case "SharlieEpilog_Helena_23":
			dialog.text = "Aussi vrai que je m’appelle "+npchar.name+". Dans moins de six mois, nous aurons un enfant – un petit monsieur de Mor... ou peut-être une demoiselle.";
			link.l1 = "Hélène... C'est incroyable !";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_6");
		break;
		
		case "SharlieEpilog_Helena_31":
			dialog.text = "...";
			link.l1 = "Alors c’est pour ça que tu n’as pas voulu boire avec nous pour fêter le départ ! Mais… pourquoi tu ne me l’as pas dit plus tôt ?";
			link.l1.go = "SharlieEpilog_Helena_32";
		break;

		case "SharlieEpilog_Helena_32":
			dialog.text = "J’avais peur que tu choisisses de ne pas prendre de risques et que tu restes sur l’archipel. Je voulais que tu tiennes ta promesse à ton père. Et puis… j’ai très envie de faire sa connaissance moi-même.";
			link.l1 = ""+npchar.name+"… Je t’aime !";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_9");
		break;
		
		// Диалог с Пикаром
		case "SharlieEpilog_PikarInCabin_1":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Eh bien… Et qu’est-ce qu’on fait ici ? On fabrique des petits Gascons ?";
				link.l1 = "Ha ha ha ! Je vais avoir un fils, "+npchar.name+"! Je vais devenir père !";
				link.l1.go = "SharlieEpilog_PikarInCabin_1_1";
			}
			else
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+". Vous ne trouvez pas que s’installer dans la cabine du capitaine sans sa permission, c’est un peu trop, même pour quelqu’un de votre rang ?";
				link.l1 = "Je vous demande pardon, capitaine. Mais j’ai une excellente raison ! Je vais devenir père !";
				link.l1.go = "SharlieEpilog_PikarInCabin_12";
			}
			SharlieEpilog_PikarInCabin_camera_2();
		break;
		
		case "SharlieEpilog_PikarInCabin_1_1":
			locCameraSleep(true);
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				StartInstantDialogTurnToNPC("Helena", "SharlieEpilog_PikarInCabin_2", "Quest\Sharlie\Epilog.c", "Blaze");
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				StartInstantDialogTurnToNPC("Mary", "SharlieEpilog_PikarInCabin_2", "Quest\Sharlie\Epilog.c", "Blaze");
			}
		break;

		case "SharlieEpilog_PikarInCabin_2":
			dialog.text = "Ou bien une fille !";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarInCabin_2_1";
		break;
		
		case "SharlieEpilog_PikarInCabin_2_1":
			StartInstantDialogTurnToNPC("SharlieEpilog_Pikar", "SharlieEpilog_PikarInCabin_3", "Quest\Sharlie\Epilog.c", "Blaze");
		break;

		case "SharlieEpilog_PikarInCabin_3":
			dialog.text = "Et tu me cachais ça, vaurien ? Je te considérais pourtant comme un ami !";
			link.l1 = "Je viens juste de l’apprendre ! Tu te rends compte ? Moi ! Je vais ! Être père !";
			link.l1.go = "SharlieEpilog_PikarInCabin_4";
		break;

		case "SharlieEpilog_PikarInCabin_4":
			dialog.text = "Ha ha ha ! Tu es vraiment heureux, mon ami ! Je ne t’ai jamais vu comme ça\nBon, continuez à roucouler, moi je vais préparer les canons pour le tir de fête. Tu me diras quand tu seras prêt à donner l’ordre.";
			link.l1 = "...";
			link.l1.go = "exit";
			locCameraSleep(false);
			SharlieEpilog_PikarInCabin_camera_1();
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_13");
		break;

		case "SharlieEpilog_PikarInCabin_12":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				sld = CharacterFromID("Helena");
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				sld = CharacterFromID("Mary");
			}
			dialog.text = "Ha... Croyez-moi, je me doutais bien de la raison de votre visite.";
			link.l1 = "Mais non ! "+sld.name+" Je suis enceinte ! J’aurai un fils ! ";
			link.l1.go = "SharlieEpilog_PikarInCabin_12_1";
		break;
		
		case "SharlieEpilog_PikarInCabin_12_1":
			locCameraSleep(true);
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				StartInstantDialogTurnToNPC("Helena", "SharlieEpilog_PikarInCabin_13", "Quest\Sharlie\Epilog.c", "Blaze");
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				StartInstantDialogTurnToNPC("Mary", "SharlieEpilog_PikarInCabin_13", "Quest\Sharlie\Epilog.c", "Blaze");
			}
		break;

		case "SharlieEpilog_PikarInCabin_13":
			dialog.text = "Ou bien une fille !";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarInCabin_13_1";
		break;
		
		case "SharlieEpilog_PikarInCabin_13_1":
			StartInstantDialogTurnToNPC("SharlieEpilog_Pikar", "SharlieEpilog_PikarInCabin_14", "Quest\Sharlie\Epilog.c", "Blaze");
		break;

		case "SharlieEpilog_PikarInCabin_14":
			dialog.text = "Euh... Eh bien, toutes mes félicitations !\nJe vais donner l’ordre de tirer une salve de fête avec tous les canons. Prévenez-moi quand vous serez prêt à donner le signal.\nEn attendant... la cabine est à votre disposition.";
			link.l1 = "...";
			link.l1.go = "exit";
			locCameraSleep(false);
			SharlieEpilog_PikarInCabin_camera_1();
			AddDialogExitQuestFunction("SharlieEpilog_LoveInCabin_13");
		break;
		
		// Диалог с Пикаром после интима с женой
		case "SharlieEpilog_PikarZalp_1":
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Pikar"))
			{
				dialog.text = "Hem... Eh bien, papa... je vois que vous avez tout de suite voulu faire un autre héritier, hein ?";
				link.l1 = "Ha ha ! Si c’était moi qui décidais, j’en aurais fait une douzaine d’un coup ! Alors, mon ami, on tire une salve de tous les canons ?";
				link.l1.go = "SharlieEpilog_PikarZalp_2";
				link.l2 = "J’ai bien peur que ça ne marche pas comme ça, mon ami. Mais on a essayé.";
				link.l2.go = "exit";
			}
			else
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar,true))+"...";
				link.l1 = "Alors, capitaine, on fait feu de toutes nos pièces ?";
				link.l1.go = "SharlieEpilog_PikarZalp_3";
				link.l2 = "Pas maintenant.";
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "SharlieEpilog_PikarZalp_1";
		break;
		
		case "SharlieEpilog_PikarZalp_2":
			dialog.text = "L’équipage n’attend que ça ! Donnez l’ordre, "+GetTitle(NPChar,true)+".";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarZalp_final";
			DelLandQuestMark(npchar);
		break;
		
		case "SharlieEpilog_PikarZalp_3":
			dialog.text = "L’équipage est prêt. Donnez vos ordres.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_PikarZalp_final";
			DelLandQuestMark(npchar);
		break;
		
		case "SharlieEpilog_PikarZalp_final":
			dialog.text = "...";
			link.l1 = "Canonniers ! Feu de tous les canons ! Feu !";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_ZalpInSea");
			locCameraFromToPos(-9.34, 8.28, -16.03, true, -9.33, 7.32, -20.48);
			CharacterTurnToLoc(pchar, "quest", "quest10");
			CharacterTurnToLoc(npchar, "quest", "quest10");
		break;
		
		// Диалог с отцом в поместье де Монпе
		case "SharlieEpilog_HenriDeMonper_1":
			NextMonth = GetDataMonth() + 2;
			if (NextMonth == 13) NextMonth = 1;
			else if (NextMonth == 14) NextMonth = 2;
			Month = XI_ConvertString("MonthVoc_" + NextMonth);
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.lastname+"... Comme je suis heureux de te voir, mon fils !";
			if (GetDataMonth() >= 4 && GetDataMonth() <= 10)
			{
				link.l1 = "Père... J'ai du mal à croire que je suis de retour à la maison... J'avais presque oublié à quoi ressemble la neige. On dirait que rien n'a changé ici...";
			}
			else
			{
				link.l1 = "Père... J'ai du mal à croire que je sois de retour à la maison... On dirait même que la neige a décidé de tomber pour fêter ça. "+month+". Ici, rien n'a vraiment changé...";
			}
			link.l1.go = "SharlieEpilog_HenriDeMonper_2";
			locCameraFromToPos(-8.76, 7.86, 0.75, true, -7.41, 6.11, 0.18);
			Achievment_Set("ach_CL_202");
		break;
		
		case "SharlieEpilog_HenriDeMonper_2":
			dialog.text = "Mais on ne peut pas en dire autant de toi ! Ta tenue, ta démarche, tes cicatrices\n"+"Non, ce n'est plus le garçon gâté que j'ai vu partir vers des contrées lointaines.";
			link.l1 = "On grandit vite aux Caraïbes, père. Mais nous aurons le temps d’en reparler. Dites-moi plutôt, comment va votre santé ? J’espère que la maladie a reculé, puisque vous vous tenez devant moi en tenue de combat ?";
			link.l1.go = "SharlieEpilog_HenriDeMonper_3";
		break;
		
		case "SharlieEpilog_HenriDeMonper_3":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				dialog.text = "Hélas, "+pchar.name+", elle s'est seulement agrippée plus fort à ma gorge. Mais pouvais-je accueillir mon fils bien-aimé dans une tenue ordinaire ? Pour moi, c'est un jour exceptionnel, "+pchar.name+"\n"+"Il paraît que tu dois me présenter à quelqu’un.";
				link.l1 = "...";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("SharlieEpilog_InEstateDeMonpe_10");
			}
			else
			{
				dialog.text = "Hélas, "+pchar.name+", sa poigne ne fait que se renforcer avec les années. Mais pouvais-je accueillir mon fils bien-aimé dans une tenue ordinaire ? Pour moi, c’est un jour exceptionnel, "+pchar.name+"\n"+"Je vois que tu n'es pas venu seul\n"+"Vous devez avoir faim après ce long voyage ? Suzanne a préparé du foie d’oie selon ta recette préférée !\n"+"Viens t’installer à table – tu pourras nous présenter en chemin !";
				link.l1 = "Je dois avouer, j’ai senti ce parfum dès que j’approchais du domaine !";
				link.l1.go = "SharlieEpilog_HenriDeMonper_8"; // заходят в поместье
			}
		break;
		
		case "SharlieEpilog_HenriDeMonper_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
			dialog.text = "...";
			link.l1 = "Père, permettez-moi de vous présenter ma femme - "+sld.name+" "+pchar.lastname+". "+sld.name+", c'est mon père – le chevalier "+GetCharacterName("Henri")+" "+GetCharacterName("de Monper")+".";
			link.l1.go = "SharlieEpilog_HenriDeMonper_5";
			SharlieEpilog_InEstateDeMonpe_11_1();
		break;
		
		case "SharlieEpilog_HenriDeMonper_5":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				sld = CharacterFromID("Helena");
				dialog.text = ""+pchar.name+", je suis charmé ! Ton élue ne ressemble en rien à ces dames du monde gâtées auxquelles nous sommes habitués ici. J’ose supposer qu’elle manie le navire avec autant d’assurance que le cœur de mon fils.";
				link.l1 = "...";
				link.l1.go = "SharlieEpilog_HenriDeMonper_Helena_1";
				CharacterTurnByChr(npchar, sld);
			}
			else
			{
				sld = CharacterFromID("Mary");
				dialog.text = "C'est un grand bonheur pour moi de faire votre connaissance, madame. Permettez-moi de vous assurer que mon fils a un goût remarquable !";
				link.l1 = "...";
				link.l1.go = "SharlieEpilog_HenriDeMonper_Mary_1";
				CharacterTurnByChr(npchar, sld);
			}
		break;
		
		case "SharlieEpilog_HenriDeMonper_Helena_1":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_HenriDeMonper_Helena_1");
		break;
		
		case "SharlieEpilog_HenriDeMonper_Helena_2":
			dialog.text = "Je suis flattée, chevalier ! Vous avez raison, je peux vraiment tenir la barre même en pleine tempête. Mais en ce qui concerne le cœur de votre fils, il n’y a nul besoin de le diriger. Nous sommes unis dans nos buts et nos aspirations.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_HenriDeMonper_Helena_2_1";
			SharlieEpilog_InEstateDeMonpe_11_2();
		break;
		
		case "SharlieEpilog_HenriDeMonper_Helena_2_1":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_HenriDeMonper_Helena_2_1");
		break;
		
		case "SharlieEpilog_HenriDeMonper_Helena_3":
			dialog.text = "L’abbé Benoît vous a décrite comme une jeune femme sage et courageuse – et il semble qu’il n’ait pas exagéré. Je suis heureux que "+pchar.name+" j'ai trouvé en toi non seulement une épouse, mais aussi une compagne qui m'égale en esprit\n"+"Vous devez avoir faim après ce long voyage ? Suzanne a préparé du foie d’oie selon ta recette préférée !\n"+"Eh bien, je vous invite tous à table ! Et j’espère qu’en chemin, nous aurons l’occasion de mieux faire connaissance.";
			link.l1 = "Je l’avoue, j’ai senti ce parfum dès que j’approchais du domaine !";
			link.l1.go = "SharlieEpilog_HenriDeMonper_6";
			SharlieEpilog_InEstateDeMonpe_11_1();
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_1":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_HenriDeMonper_Mary_1");
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_2":
			dialog.text = "Je suis ravie de faire votre connaissance, chevalier ! "+pchar.name+" on m’a beaucoup parlé de vous, et je vous imaginais exactement comme ça, ouais, hein !";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_HenriDeMonper_Mary_2_1";
			CharacterTurnByChr(pchar, npchar);
			SharlieEpilog_InEstateDeMonpe_11_2();
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_2_1":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_HenriDeMonper_Mary_2_1");
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_3":
			sld = CharacterFromID("Mary");
			dialog.text = ""+pchar.name+", je suis sous le charme ! Ta bien-aimée ne ressemble en rien à ces dames poudrées de la haute société – et c’est là sa véritable valeur\n"+"Il me semble que tu as choisi une magnifique rose plutôt que des lys délicats et capricieux.";
			link.l1 = "La rose sauvage, père… "+sld.name+"  - un véritable trésor. Je suis sûr que vous serez d'accord avec moi quand vous la connaîtrez mieux.";
			link.l1.go = "SharlieEpilog_HenriDeMonper_Mary_4";
			SharlieEpilog_InEstateDeMonpe_11_1();
		break;
		
		case "SharlieEpilog_HenriDeMonper_Mary_4":
			if (GetAttributeInt(pchar, "questTemp.SharlieEpilog_Friends") >= 2) sStr = "ты познакомишь меня с остальными";
			else sStr = "ты представишь меня нашему гостю";
			dialog.text = "Alors, ne tardons pas davantage ! Tu dois avoir faim après un si long voyage ? Suzanne a préparé du foie d’oie selon ta recette préférée !\n"+"Je vous invite tous à table ! Et en chemin, j’espère que "+sStr+"";
			link.l1 = "Je l’avoue, j’ai senti ce parfum dès que j’approchais du domaine !";
			link.l1.go = "SharlieEpilog_HenriDeMonper_6";
			CharacterTurnByChr(CharacterFromID("HenriDeMonper"), pchar);
		break;
		
		case "SharlieEpilog_HenriDeMonper_6":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_InEstateDeMonpe_14");
		break;
		
		case "SharlieEpilog_HenriDeMonper_7":
			dialog.text = "...";
			link.l1 = "Chérie, tu dois absolument goûter ça – rien ne peut rivaliser avec le foie d’oie préparé selon notre recette de famille ! Elle nous vient de grand-père – et lui, on la lui a offerte en cadeau d’un pays méditerranéen.";
			link.l1.go = "SharlieEpilog_HenriDeMonper_8"; // заходят в поместье
			SharlieEpilog_InEstateDeMonpe_11_1();
		break;
		
		case "SharlieEpilog_HenriDeMonper_8":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_InEstateDeMonpe_15");
		break;
		
		// диалог на ужине в поместье де Монпе
		case "SharlieEpilog_InKitchenDeMonpe":
			dialog.text = "";
			link.l1 = "Je n’aimerais pas commencer ce festin sur une note triste, mais en tant que famille, nous devons nous souvenir de ceux qui nous ont quittés avant nous. Je vous demande de lever vos verres à Michel. Que le Seigneur accorde la paix à son âme.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_2";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_2":
			dialog.text = "";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_3";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_3":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				if (GetAttributeInt(pchar, "questTemp.SharlieEpilog_Friends") >= 2) sStr = "добрых друзей";
				else sStr = "соратника";
				dialog.text = "";
				link.l1 = "J'ai tant de choses à te demander, "+pchar.name+"... Mais avant, permets à ton épouse de s’exprimer et "+sStr+". Je vous en prie, racontez-moi comment vous avez fait la connaissance de Charles.";
			}
			else
			{
				if (GetAttributeInt(pchar, "questTemp.SharlieEpilog_Friends") >= 2) sStr = "твоих добрых друзей";
				else sStr = "твоего друга";
				dialog.text = "";
				link.l1 = "J’ai tellement de choses à te demander, "+pchar.name+"... Mais avant, permets-moi d'écouter "+sStr+". Je vous en prie, racontez-moi comment vous avez rencontré Charles.";
			}
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_4";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		// if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
		
		case "SharlieEpilog_InKitchenDeMonpe_4":
			dialog.text = "";
			link.l1 = "J'ai aussi hâte que vous d'entendre ça !";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_5";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_6";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7";
			}
			else
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_5":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				link.l1 = "J’ai été en danger de mort... "+pchar.name+", en vrai gentleman, il n’a pas laissé le malheur arriver ! Il a pris ma défense et s’est occupé de ces vauriens, ouais, hein ?";
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1 = ""+pchar.name+" il m’a arrachée des griffes d’un Anglais sans scrupules, qui a osé… m’enlever. S’il était arrivé ne serait-ce qu’une heure plus tard, nous ne nous serions jamais rencontrés.";
			}
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_5_1";
			SharlieEpilog_InKitchenDeMonpe_camera_Wife();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_5_1":
			dialog.text = "";
			link.l1 = "Je n’ai jamais douté qu’il agirait en vrai gentilhomme. L’honneur n’est pas qu’un mot pour notre famille. Je suis fier de toi, mon fils.";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_6";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7";
			}
			else
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_6":
			sld = CharacterFromID("Tichingitu");
			dialog.text = "";
			link.l1 = ""+sld.name+" entrer dans la maison du visage pâle pour trouver de la nourriture. Le visage pâle surprendre "+sld.name+" - et l’envoyer en prison. Capitaine "+pchar.name+" venir, délivrer "+sld.name+" de prison. Depuis ce jour "+sld.name+" servir le capitaine "+pchar.name+" et rester fidèle jusqu’à mon dernier souffle.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_6_1";
			SharlieEpilog_InKitchenDeMonpe_camera_Tichingitu();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_6_1":
			sld = CharacterFromID("Tichingitu");
			dialog.text = "";
			link.l1 = "Cela me réjouit de savoir que mon fils n’est pas seulement un noble gentilhomme, mais aussi un homme au grand cœur. Je suis heureux qu’il ait à ses côtés des amis aussi fidèles que vous, "+sld.name+".";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7";
			}
			else
			{
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_7":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
			{
				link.l1 = "Un jour, le capitaine est venu chez moi – il cherchait du travail. Je lui ai confié une mission, et il s’en est très bien sorti. Le patron l’a trouvé à son goût, et il l’a de plus en plus impliqué dans ses affaires, tandis que moi, il m’a envoyé sur son navire – pour surveiller… Et puis ce… monsieur a levé l’ancre en douce, que le diable l’emporte, et il a quitté l’archipel sans dire un mot au capitaine. Il l’a laissé seul dans la pagaille qu’il avait lui-même créée. J’ai proposé mes services au capitaine, et même si Richard s’est conduit comme un traître, que le diable l’emporte, le capitaine ne m’a pas chassé.";
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7_2";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
			{
				link.l1 = "Longwei et monsieur le capitaine travaillaient pour le même homme. Mais cet homme a trahi Longwei. Alors Longwei a décidé : ne plus servir cet homme. Monsieur le capitaine m’a pris sur son navire comme officier, et il a fait beaucoup pour Longwei.";
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7_2";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1 = "La première fois que nous nous sommes croisés, c’était à la taverne de Bridgetown : "+pchar.name+" il cherchait une affaire, et moi – un homme de confiance pour la mener à bien. Cette rencontre n’a été qu’un début, suivi d’événements qui ont lié nos destins. Je suis devenu son officier, et aujourd’hui je peux sans hésiter l’appeler mon ami – un homme pour qui je suis prêt à risquer ma vie.";
				link.l1.go = "SharlieEpilog_InKitchenDeMonpe_7_2";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Gambitnik();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_7_2":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
			{
				link.l1 = "Voir l’homme au-delà des circonstances est une qualité rare. Cela montre sans doute que mon fils n’est pas dépourvu de discernement.";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
			{
				link.l1 = "Je suis heureux que mon fils ne soit pas un soldat sans cœur, mais un vrai chef, capable de prendre soin de ses compagnons.";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1 = "On n’entend pas de telles paroles tous les jours. Voilà sans doute la meilleure preuve que mon fils n’est pas seulement un marin accompli, mais aussi un véritable ami.";
			}
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_8":
			dialog.text = "";
			link.l1 = "Nous nous sommes rencontrés à Bordeaux. Le capitaine est monté à bord de notre navire en tant que passager et nous l’avons conduit jusqu’en Martinique. Depuis ce jour — et jusqu’à notre départ pour ici — je suis resté la voix de son équipage et j’ai observé comment "+GetFullName(pchar)+" pas à pas, il devenait celui qu’il est aujourd’hui.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_8_1";
			SharlieEpilog_InKitchenDeMonpe_camera_Alonso();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_8_1":
			dialog.text = "";
			link.l1 = "Alors, vous avez connu Charles quand il n’était encore qu’un jeune impertinent que j’ai, à mon grand regret, poussé à quitter la maison ? Je pense, monsieur, que nous aurons beaucoup à nous dire.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_9";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_9":
			dialog.text = "";
			link.l1 = "Mon cher "+pchar.name+", tu as parcouru un long et glorieux chemin... Tu es parti dans la savane sauvage pour une simple peau de lapin, mais tu as affronté un lion et tu es revenu en triomphateur, sa peau sur les épaules. Aujourd'hui, je suis plus que jamais rassuré pour le destin de notre domaine et de toutes nos terres.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_10";
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_10":
			dialog.text = "";
			link.l1 = "J’ai hâte de te confier au plus vite les rênes de toutes les affaires de notre famille. Il y aura beaucoup à faire, mais j’en suis sûr : le Seigneur lui-même veille sur toi et tu sauras non seulement préserver l’héritage qui t’est confié, mais aussi accroître l’honneur et la prospérité de la famille de Montpe.";
			link.l1.go = "SharlieEpilog_InKitchenDeMonpe_11";
		break;
		
		case "SharlieEpilog_InKitchenDeMonpe_11": //выбор Шарля
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l1 = "C’est un immense honneur pour moi d’être votre fils et votre héritier. J’accepte avec joie de prendre soin de notre famille. Je suis certain que mon épouse sera un soutien fidèle à mes côtés. Je vous promets de tout faire pour que notre nom rayonne encore davantage… Et la naissance d’un enfant sera la première pierre de cette prospérité !";
				link.l1.go = "SharlieEpilog_ChooseEstate_HaveWife_1";
			}
			else
			{
				link.l1 = "C’est un immense honneur pour moi d’être votre fils et héritier. Je prends avec joie la responsabilité de notre famille et je vous promets de tout faire pour rendre notre nom encore plus illustre.";
				link.l1.go = "SharlieEpilog_ChooseEstate_Single_1";
			}
			link.l2 = "Père, les années passées dans le Nouveau Monde m'ont changé. J'ai bien peur de ne plus pouvoir me faire à la vie tranquille d'ici, en Europe.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				link.l2.go = "SharlieEpilog_ChooseCaribbean_HaveWife_1";
			}
			else
			{
				link.l2.go = "SharlieEpilog_ChooseCaribbean_Single_1";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		// --> Выбрал остаться в поместье с женой
		case "SharlieEpilog_ChooseEstate_HaveWife_1":
			dialog.text = "";
			link.l1 = ""+pchar.name+", vraiment...";
			link.l1.go = "SharlieEpilog_HaveWife_12";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
			pchar.questTemp.SharlieEpilog_ChooseEstate = true;
		break;
		
		case "SharlieEpilog_HaveWife_12":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
			dialog.text = "";
			link.l1 = "Oui, père. "+sld.name+" enceinte.";
			link.l1.go = "SharlieEpilog_HaveWife_13";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_HaveWife_13":
			dialog.text = "";
			link.l1 = "Voilà une nouvelle extraordinaire, mon cher fils ! Le Seigneur a exaucé mes prières ! Que tous ici présents soient témoins : en l'honneur du nouveau-né, j'organiserai le bal le plus somptueux que notre domaine ait jamais connu ! Levons nos verres — à l'héritier !";
			link.l1.go = "SharlieEpilog_HaveWife_14";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_HaveWife_14":
			dialog.text = "";
			link.l1 = "Ou bien une héritière !";
			link.l1.go = "SharlieEpilog_HaveWife_15";
			SharlieEpilog_InKitchenDeMonpe_camera_Wife();
		break;
		
		case "SharlieEpilog_HaveWife_15":
			dialog.text = "";
			link.l1 = "À un nouveau chapitre dans l’histoire de notre famille !";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				link.l1.go = "SharlieEpilog_HaveWife_16";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_HaveWife_17";
			}
			else
			{
				link.l1.go = "SharlieEpilog_HaveWife_18";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_HaveWife_16":
			dialog.text = "";
			link.l1 = "À l’avenir du vaillant fils ou de la bonne fille !";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_HaveWife_17";
			}
			else
			{
				link.l1.go = "SharlieEpilog_HaveWife_18";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Tichingitu();
		break;
		
		case "SharlieEpilog_HaveWife_17":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
			{
				link.l1 = "À la santé robuste du nouveau-né !";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
			{
				link.l1 = "À la chance qui vous a réunis !";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1 = "À l’avenir radieux de votre famille !";
			}
			link.l1.go = "SharlieEpilog_HaveWife_18";
			SharlieEpilog_InKitchenDeMonpe_camera_Gambitnik();
		break;
		
		case "SharlieEpilog_HaveWife_18":
			dialog.text = "";
			link.l1 = "Pour le futur Alonso de Mora ou la petite Alonsita de Mor !";
			link.l1.go = "SharlieEpilog_HaveWife_19";
			SharlieEpilog_InKitchenDeMonpe_camera_Alonso();
		break;
		
		case "SharlieEpilog_HaveWife_19":
			dialog.text = "";
			link.l1 = "Ah-ah-ah !";
			link.l1.go = "SharlieEpilog_HaveWife_20";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_HaveWife_20":
			dialog.text = "";
			link.l1 = "Ha ha !";
			link.l1.go = "SharlieEpilog_HaveWife_21";
			SharlieEpilog_InKitchenDeMonpe_camera_Wife();
		break;
		
		case "SharlieEpilog_HaveWife_21":
			dialog.text = "";
			link.l1 = "Ha ha ha !";
			link.l1.go = "SharlieEpilog_toast";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_toast":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_toast");
		break;
		// <-- Выбрал остаться в поместье с женой
		
		// --> Выбрал остаться в поместье будучи холостяком
		case "SharlieEpilog_ChooseEstate_Single_1":
			dialog.text = "";
			link.l1 = "C’est pour moi un immense honneur d’être votre fils et votre héritier. Je prendrai avec joie toutes les responsabilités de notre famille et je vous promets de faire tout mon possible pour rendre notre nom encore plus illustre.";
			link.l1.go = "SharlieEpilog_ChooseEstate_Single_2";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
			pchar.questTemp.SharlieEpilog_ChooseEstate = true;
		break;
		
		case "SharlieEpilog_ChooseEstate_Single_2":
			dialog.text = "";
			link.l1 = "Dis, "+pchar.name+", as-tu réfléchi à ma proposition de t’unir à Yvonne par les liens du mariage ?";
			link.l1.go = "SharlieEpilog_Single_13";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_Single_13":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_ChooseCaribbean"))
			{
				link.l1 = "Je l’avoue, père… Yvonne n’a jamais été proche de mon cœur. Mais il y a tant de jeunes femmes charmantes dans le Nouveau Monde. Je vous promets : quand j’en rencontrerai une digne de moi, je n’hésiterai pas.";
			}
			else
			{
				link.l1 = "Je l’avoue, père… Yvonne n’a jamais été proche de mon cœur. Mais il y a tant de jolies filles en France. Je vous promets : quand j’en rencontrerai une digne de ce nom, je n’hésiterai pas.";
			}
			link.l1.go = "SharlieEpilog_Single_14";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_Single_14":
			dialog.text = "";
			link.l1 = "J’aime ton état d’esprit, mon cher fils. Levons nos verres – à toi, à tes exploits et à ton retour digne à la maison !";
			link.l1.go = "SharlieEpilog_Single_15";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_Single_15":
			dialog.text = "";
			link.l1 = "Aux amis fidèles, sans qui il serait impossible de survivre dans le Nouveau Monde !";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tichingitu"))
			{
				link.l1.go = "SharlieEpilog_Single_16";
			}
			else if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_Single_17";
			}
			else
			{
				link.l1.go = "SharlieEpilog_Single_18";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_Single_16":
			dialog.text = "";
			link.l1 = "Pour le grand cœur du capitaine Charles !";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway") || CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1.go = "SharlieEpilog_Single_17";
			}
			else
			{
				link.l1.go = "SharlieEpilog_Single_18";
			}
			SharlieEpilog_InKitchenDeMonpe_camera_Tichingitu();
		break;
		
		case "SharlieEpilog_Single_17":
			dialog.text = "";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Knippel"))
			{
				link.l1 = "À la volonté de fer du capitaine !";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Longway"))
			{
				link.l1 = "À la sagesse de monsieur le capitaine !";
			}
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_Tonzag"))
			{
				link.l1 = "Pour la fidélité à la cause !";
			}
			link.l1.go = "SharlieEpilog_Single_18";
			SharlieEpilog_InKitchenDeMonpe_camera_Gambitnik();
		break;
		
		case "SharlieEpilog_Single_18":
			dialog.text = "";
			link.l1 = "À ta capacité à toujours t’en sortir sans une égratignure !";
			link.l1.go = "SharlieEpilog_toast";
			SharlieEpilog_InKitchenDeMonpe_camera_Alonso();
		break;
		// <-- Выбрал остаться в поместье будучи холостяком
		
		// Шарль губернатор разговаривает с зелёным капитаном
		case "SharlieEpilog_GreenCaptain":
			dialog.text = "";
			link.l1 = "J'ai entendu dire que vous aviez insisté pour obtenir une audience. Alors, qu'est-ce qui vous amène chez le gouverneur de la Martinique ?";
			link.l1.go = "SharlieEpilog_GreenCaptain_1";
			locCameraFromToPos(-1.80, 3.84, -9.08, true, -2.38, 2.21, -7.33);
			PlaySound("Voice\" + LanguageGetLanguage() + "\officer_common_2.wav");
		break;
		
		case "SharlieEpilog_GreenCaptain_1":
			dialog.text = "Je veux parler de travailler pour le bien de la couronne de France.";
			link.l1 = "Oui, j'ai une mission pour vous qui exigera toute votre rapidité et votre talent pour le combat naval. Êtes-vous prêt à faire vos preuves ?";
			link.l1.go = "SharlieEpilog_GreenCaptain_2";
		break;

		case "SharlieEpilog_GreenCaptain_2":
			dialog.text = "Votre Altesse, pourriez-vous expliquer plus en détail l’essence de la mission à venir ?";
			link.l1 = "Bien sûr. Vous devez trouver le navire de messagerie espagnol appelé 'Santa Esperanza', l'aborder et m'apporter les documents que vous trouverez dans la cabine du capitaine. Le navire en question passera près de Trinidad dans environ douze jours.";
			link.l1.go = "SharlieEpilog_GreenCaptain_3";
		break;

		case "SharlieEpilog_GreenCaptain_3":
			dialog.text = "D'accord, je m'occupe de cette mission. Mais quels sont les documents que je dois chercher ?";
			link.l1 = "La correspondance postale. Parmi d’autres choses, il y aura des documents très importants pour moi. Mais inutile de fouiller dans les papiers, apportez-moi simplement tout le paquet en entier. Pour ce service, je vous paierai quinze mille pesos... Alors, je vous attends dans ma résidence avec le résultat de votre travail.";
			link.l1.go = "SharlieEpilog_GreenCaptain_4";
		break;

		case "SharlieEpilog_GreenCaptain_4":
			dialog.text = "Je suppose que je ne vous ferai pas attendre longtemps, Votre Altesse.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_GuberOnMartinique_5");
		break;
		
		//Шарль разговаривает с комендантом форта
		case "SharlieEpilog_KomendantFort":
			dialog.text = "Votre Altesse... Permettez-moi de faire mon rapport ?";
			link.l1 = "Faites votre rapport, "+GetAddress_Form(NPChar)+" "+npchar.lastname+".";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) link.l1.go = "SharlieEpilog_KomendantFort_1";
			else link.l1.go = "SharlieEpilog_KomendantFort_2";
			PlaySound("Voice\" + LanguageGetLanguage() + "\military02.wav");
		break;
		
		case "SharlieEpilog_KomendantFort_1":
			dialog.text = "Euh-euh...";
			link.l1 = "Parlez librement. Je n'ai aucun secret pour ma femme.";
			link.l1.go = "SharlieEpilog_KomendantFort_2";
		break;
		
		case "SharlieEpilog_KomendantFort_2":
			dialog.text = "Les renseignements rapportent : une escadre vient de quitter Willemstad. À sa tête, le vaisseau de ligne de second rang « Gouden Leeuw », un véritable monstre des mers. La puissance totale de l’escadre dépasse deux cent cinquante canons et compte plus de mille cinq cents soldats. Leur objectif : Saint-Pierre.";
			link.l1 = "Hmm... Donc, nous n'avons pratiquement pas de temps pour nous préparer.";
			link.l1.go = "SharlieEpilog_KomendantFort_3";
		break;

		case "SharlieEpilog_KomendantFort_3":
			dialog.text = "Que faisons-nous, Monsieur le Gouverneur ?";
			link.l1 = "Nous avons plusieurs navires en rade, capables de frapper l’ennemi à revers...";
			link.l1.go = "SharlieEpilog_KomendantFort_4";
		break;

		case "SharlieEpilog_KomendantFort_4":
			dialog.text = "Vous comptez les attaquer des deux côtés ?";
			link.l1 = "Exactement. Le fort attirera le feu sur lui. Et quand la nuit tombera, l'escadre sous mon commandement attaquera depuis la mer. Nous détournerons leur attention, et alors des brûlots chargés de poix et de planches partiront du port. Il ne restera rien de leur flotte, pas même une écharde.";
			link.l1.go = "SharlieEpilog_KomendantFort_5";
		break;

		case "SharlieEpilog_KomendantFort_5":
			dialog.text = "Excellent plan, Votre Altesse ! Permettez-moi de donner l'ordre de commencer les préparatifs ?";
			link.l1 = "Allez-y. Que le Seigneur soit avec nous.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_GuberOnMartinique_11");
		break;
		
		// Стражник вызывает Алонсо
		case "SharlieEpilog_Guard":
			dialog.text = "";
			link.l1 = "Garde, faites venir Alonso.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_AlonsoArrive");
		break;
		
		//Шарль разговаривает с Алонсо после коменданта
		case "SharlieEpilog_Alonso35":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")))
			{
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
				dialog.text = "Monsieur le gouverneur...";
				link.l1 = ""+npchar.name+", une escadre hollandaise arrivera ici d'un jour à l'autre et commencera le siège. Écoute l'ordre : prends Philippe et "+sld.name+", et conduis-les immédiatement chez l’abbé. Qu’il rassemble toutes les femmes, les enfants et les vieillards, et qu’il veille à leur sécurité.";
				link.l1.go = "SharlieEpilog_Alonso36_Wife";
				break;
			}
			dialog.text = "Monsieur le gouverneur...";
			link.l1 = ""+npchar.name+", une escadre hollandaise doit arriver d’un jour à l’autre et assiéger la ville. Dis à l’abbé de rassembler toutes les femmes, les enfants et les vieillards, et de veiller à leur sécurité. Quant à toi, je compte te confier le commandement d’un brûlot. Les détails viendront plus tard. D’abord, il faut protéger les civils.";
			link.l1.go = "SharlieEpilog_Alonso37";
		break;

		case "SharlieEpilog_Alonso36_Wife":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
			dialog.text = "Je ne pense pas que "+sld.name+" acceptera de rejoindre les autres femmes. Elle meurt d’ennui.";
			link.l1 = "Hmm... Alors transmets-lui ceci : qu'elle se prépare au combat. Toi non plus, tu ne resteras pas les bras croisés — tu prendras le commandement du brûlot. Les détails viendront plus tard. Pour l'instant, veille sur mon fils.";
			link.l1.go = "SharlieEpilog_Alonso37";
		break;
		
		case "SharlieEpilog_Alonso37":
			dialog.text = "Ce sera un honneur ! Puis-je commencer ?";
			link.l1 = "Je t’autorise. Vas-y. Chaque seconde compte pour nous.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_GuberOnMartinique_13");
		break;
		// --> Выбрал отправиться назад на Карибы с женой
		case "SharlieEpilog_ChooseCaribbean_HaveWife_1":
			dialog.text = "";
			link.l1 = "Eh bien... Je dois avouer que je m’attendais à cette réponse – même si j’espérais autre chose. Mais je respecte ton choix et je ne vais pas insister.";
			link.l1.go = "SharlieEpilog_ChooseCaribbean_HaveWife_2";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
			pchar.questTemp.SharlieEpilog_ChooseCaribbean = true;
		break;
		
		case "SharlieEpilog_ChooseCaribbean_HaveWife_2":
			dialog.text = "";
			link.l1 = "Je comprends que je vous ai déçu. Mais j’ai une nouvelle pour vous, qui, je l’espère, fera oublier tout ce qui a été dit auparavant.";
			link.l1.go = "SharlieEpilog_ChooseCaribbean_HaveWife_3";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_ChooseCaribbean_HaveWife_3":
			dialog.text = "";
			link.l1 = "Je suis tout ouïe.";
			link.l1.go = "SharlieEpilog_ChooseCaribbean_HaveWife_4";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		
		case "SharlieEpilog_ChooseCaribbean_HaveWife_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = CharacterFromID("Helena");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sld = CharacterFromID("Mary");
			dialog.text = "";
			link.l1 = "Je compte rester ici au moins un an. "+sld.name+" dans sa condition, le tangage est contre-indiqué.";
			link.l1.go = "SharlieEpilog_ChooseCaribbean_HaveWife_5";
			SharlieEpilog_InKitchenDeMonpe_camera_Sharle();
		break;
		
		case "SharlieEpilog_ChooseCaribbean_HaveWife_5":
			dialog.text = "";
			link.l1 = ""+pchar.name+", vraiment...";
			link.l1.go = "SharlieEpilog_HaveWife_12";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
		break;
		// <-- Выбрал отправиться назад на Карибы с женой
		
		// --> Выбрал отправиться назад на Карибы один
		case "SharlieEpilog_ChooseCaribbean_Single_1":
			dialog.text = "";
			link.l1 = "Eh bien... Je dois avouer que je m’attendais à cette réponse, même si j’espérais autre chose. Mais je respecte ton choix, et je ne vais pas insister. Dis-moi, "+pchar.name+", as-tu réfléchi à ma proposition de t’unir à Yvonne par les liens du mariage ?";
			link.l1.go = "SharlieEpilog_Single_13";
			SharlieEpilog_InKitchenDeMonpe_camera_Father();
			pchar.questTemp.SharlieEpilog_ChooseCaribbean = true;
		break;
		// <-- Выбрал отправиться назад на Карибы один
		
		//Диалог Шарль и Мишеля на Рифе Скелета
		case "SharlieEpilog_Mishelle_1":
			dialog.text = "Tu n’as pas pu t’arrêter, hein ?";
			link.l1 = "Toi ?! Je rêve ?";
			link.l1.go = "SharlieEpilog_Mishelle_2";
			SharlieEpilog_OnReefs_6();
			PlaySound("Voice\" + LanguageGetLanguage() + "\sharlie\mishelle-04.wav");
		break;

		case "SharlieEpilog_Mishelle_2":
			dialog.text = "La soif du gain facile, le pouvoir, l’illusion de l’invulnérabilité… Qu’est-ce qui t’a perdu, mon frère ? Qu’est-ce qui a obscurci ton esprit, comme cela trouble l’esprit de tous les visages pâles ?";
			link.l1 = "Va-t’en ! Tu n’es qu’un fantôme ! Tu n’es pas ici !";
			link.l1.go = "SharlieEpilog_Mishelle_3";
		break;

		case "SharlieEpilog_Mishelle_3":
			dialog.text = "Tu n’as donc toujours pas compris ? Spectra sunt memoria peccatorum. C’est toi le fantôme… La légende des Caraïbes parle d’un homme dévoré par la cupidité et une vanité aveugle. Combien as-tu tué pour de l’or, "+pchar.name+"?";
			link.l1 = "Eh bien, mon cher frère, je ne vois aucun inconvénient à te tuer une seconde fois ! Tu l’as bien cherché !";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieEpilog_OnReefs_9");
		break;
		
		
		
		
		
	}
}