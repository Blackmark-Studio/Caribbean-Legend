// Оле Кристиансен - Белый Мальчик
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Que veux-tu ?";
			link.l1 = "Rien.";
			NextDiag.TempNode = "First time";
		break;
		
		// в магазине - первая встреча
		case "store":
			dialog.text = "Oups... Bonjour, oncle. As-tu une perle blanche ? Donne-moi la perle blanche...";
			link.l1 = "Hm. Bonne journée. Êtes-vous... le Garçon Blanc ?";
			link.l1.go = "store_1";
		break;
		
		case "store_1":
			dialog.text = "Perle! Perle blanche pour le garçon blanc! As-tu une perle blanche, oncle?";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "Hm, je n'ai pas de perles, mais je peux te donner cette perle. Elle est blanche et c'est comme la perle. Cela te convient-il ?";
				link.l1.go = "store_2";
			}
			link.l2 = "Non, je n'ai pas de perles ni blanches ni rouges. Je ne suis ni une fille ni un Indien pour porter des perles. Dis-moi...";
			link.l2.go = "pearl";
			sld = characterFromId("Axel");
			sld.quest.ole_pearl = "true";
		break;
		
		case "pearl":
			dialog.text = "Perle ! Perle blanche ! Pas de perle - pas de discussion. Mauvais oncle... Donne-moi une perle !";
			link.l1 = "Merde ! Quel fou furieux ! L'Œil de Serpent et Chimiset avaient raison - il a la tête faible... De quel genre de perle a-t-il besoin ?";
			link.l1.go = "exit";
			NextDiag.TempNode = "pearl_repeat";
		break;
		
		case "pearl_repeat":
			dialog.text = "Donne une perle, oncle. Bon oncle... Perle blanche !";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "Tiens, prends ta perle. C'est ce que tu veux ?";
				link.l1.go = "store_2";
			}
			link.l2 = "Oh, sacrebleu...";
			link.l2.go = "exit";
			NextDiag.TempNode = "pearl_repeat";
		break;
		
		case "store_2":
			RemoveItems(pchar, "jewelry52", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Oui, oui ! C'est ça ! Oncle m'a donné une perle ! Merci, bonhomme ! Maintenant Ole a une perle de plus. Bientôt je verrai maman...";
			link.l1 = "Je suis content pour toi. Eh bien, pouvons-nous parler maintenant ?";
			link.l1.go = "store_3";
			sld = characterFromId("Axel");
			DeleteAttribute(sld, "quest.ole_pearl");
		break;
		
		case "store_3":
			dialog.text = "Bien sûr, bonhomme. Es-tu un homme bon, oncle? Nous serons amis. Ole sera ravi de parler. Quel est ton nom?";
			link.l1 = "Mon nom est "+pchar.name+". Ole, un homme m'a parlé de toi et il n'est plus ici. Il a dit que tu l'avais aidé et que tu pouvais m'aider.";
			link.l1.go = "store_4";
		break;
		
		case "store_4":
			dialog.text = "L'Oncle a donné une perle à Ole - c'est un bon oncle. Ole aime aider les bonnes gens. Il n'y a pas beaucoup de bonnes gens - les mauvais oncles sont partout. Je vais t'aider, c'est certain. J'aime aider.";
			link.l1 = "Super ! Eh bien, nous sommes amis maintenant. Ole, dis-moi, te souviens-tu d'un homme à la peau rouge et portant un magnifique chapeau avec des plumes ? Il m'a dit que tu l'avais sauvé il y a longtemps.";
			link.l1.go = "store_5";
		break;
		
		case "store_5":
			dialog.text = "Je me souviens de cet oncle. C'est un homme bon. Je l'ai sauvé. Je l'ai emmené à la statue. Et récemment, j'ai sauvé un autre homme bon de la cale avec de la nourriture. Je l'ai sauvé des oncles du mauvais amiral. Ils l'auraient tué. Je voulais l'emmener à la statue aussi mais il a refusé. Complètement.";
			link.l1 = "De la cale ? Heh, je suppose que je sais de qui tu parles... Et je connais cet oncle. Dis-moi, Ole, qui est cet homme que tu as sauvé ?";
			link.l1.go = "store_6";
		break;
		
		case "store_6":
			dialog.text = "Son nom est oncle Nathan. Il est malade, très-très malade. Il pouvait à peine marcher quand Ole l'a trouvé.";
			link.l1 = "Bien sûr... C'est étrange qu'il ait pu le faire.";
			link.l1.go = "store_7";
		break;
		
		case "store_7":
			dialog.text = "Non, ce n'est pas étrange. Je l'ai trouvé et je lui ai donné du rhum enflammé. J'ai nagé à l'intérieur du trou parce qu'il y a de la nourriture sur ce navire. Les mauvais hommes ferment la porte, mais je l'ouvre toujours. Hi-hi-hi... Mauvais hommes idiots. Ils attirent les crabes, je le sais. Mauvais hommes\nJe suis arrivé là-bas et j'ai trouvé Nathan. Il ne se sentait pas bien. J'avais du rhum enflammé - je lui en ai donné à boire, alors il s'est senti mieux. Puis je lui ai donné la teinture, j'en ai toujours une sur moi, au cas où un vilain crabe mordrait Ole. Le bon oncle Chimiset m'a dit de le faire...";
			link.l1 = "As-tu donné un antidote et du rhum? Heh, tu n'es pas aussi bête qu'ils le pensent tous. Bien joué, Ole.";
			link.l1.go = "store_8";
		break;
		
		case "store_8":
			dialog.text = "Méchants oncles considèrent Ole comme un imbécile et ils se moquent de lui : Ole l'imbécile... Ole n'est pas un imbécile, il doit juste rassembler toutes les perles blanches sinon sa mère l'enverra loin. Me donneras-tu une autre perle plus tard ?";
			link.l1 = "Hm... Bien sûr, Ole, nous sommes amis. Dis-moi, comment allais-tu envoyer Hawk... oncle Nathan à la statue. Oncle Chimiset m'a dit qu'elle avait coulé avec le navire...";
			link.l1.go = "store_9";
		break;
		
		case "store_9":
			dialog.text = "La statue est au fond. Ole sait. Mais ce n'est pas profond et le bon oncle Henrik peut envoyer l'oncle Nathan là-bas. L'oncle Henrik sait marcher sous l'eau. Mais il y a beaucoup de crabes effrayants. Ole les craint. Ils mordent douloureusement.";
			link.l1 = "Oncle Henrik ? Qui est-ce ?";
			link.l1.go = "store_10";
		break;
		
		case "store_10":
			dialog.text = "Oncle Henrik vit parmi les méchants oncles Narvals. Tout le monde le connaît. Il peut marcher sous l'eau et il apprend aux oncles Narvals à y plonger. Oncle Henrik est bon, il a donné une perle blanche à Ole.";
			link.l1 = "Et comment les Narvals vous ont-ils laissé entrer ? Ou leur territoire vous est-il ouvert ?";
			link.l1.go = "store_11";
		break;
		
		case "store_11":
			dialog.text = "Tee-hee... Les oncles méchants n'autorisent pas Ole à entrer, mais Ole peut pénétrer dans n'importe quelle cabine de leurs navires la nuit. Ils sont grands et bruyants, mais Ole est silencieux et prudent. Et j'ai rencontré l'oncle Henrik en nageant autour du navire d'où l'oncle Henrik plonge. L'oncle Henrik a donné une perle blanche à Ole et nous sommes amis maintenant.";
			link.l1 = "Intéressant... Je veux aussi être un ami de l'oncle Henrik.";
			link.l1.go = "store_12";
		break;
		
		case "store_12":
			dialog.text = "Tu veux plonger et aller jusqu'à la statue? Elle est là, dans la brèche du vieux navire. Il y a beaucoup de gros et effrayants crabes. Tu ne les crains pas? Ils peuvent mordre.";
			link.l1 = "Non, je ne les crains pas. J'en ai déjà tué un, alors ils feraient mieux d'avoir peur de moi.";
			link.l1.go = "store_13";
		break;
		
		case "store_13":
			dialog.text = "Oh, "+pchar.name+"est très courageux! Alors tu devrais aller voir l'oncle Henrik, il t'apprendra à marcher au fond et tu tueras tous les crabes là-bas. Tu y trouveras aussi une autre grosse perle pour Ole, n'est-ce pas?";
			link.l1 = "Bien sûr, je le ferai. Mais je dois d'abord trouver oncle Henrik.";
			link.l1.go = "store_14";
		break;
		
		case "store_14":
			dialog.text = "Et pourquoi le chercher ? Il vit sur le navire nommé 'San Gabriel', dans l'atelier. Mais les méchants oncles Narvals pourraient ne pas vous accueillir.";
			link.l1 = "Je m'occuperai moi-même des oncles maléfiques. Et la dernière question, où est l'oncle Nathan maintenant ? Je l'ai cherché et il est la raison pour laquelle je suis ici.";
			link.l1.go = "store_15";
		break;
		
		case "store_15":
			dialog.text = "Je cache oncle Nathan dans mon sanctuaire sur le 'Fernanda'. C'est loin et personne n'y vit. Tout le monde pense qu'il coulera bientôt, mais Ole sait le contraire. J'ai sauvé oncle Nathan et l'ai amené là-bas\nIl est encore très malade et il boit du rhum de feu tout le temps. Il marche à peine et est incapable de soulever quoi que ce soit de plus lourd que cinq livres. Je me sens mal pour oncle Nathan, je lui apporte du rhum de feu des coffres et de la nourriture de la cale des méchants de l'amiral. Je lui cuisine aussi des rats que je capture. Des rats très savoureux !";
			link.l1 = "Des rats savoureux ? Je vois. Alors, Nathan est-il sur le navire nommé... comment as-tu dit - le 'Fernanda' ? Je ne la connais pas...";
			link.l1.go = "store_16";
		break;
		
		case "store_16":
			dialog.text = "Oncle "+pchar.name+", je viens de te dire que ce n'est pas loin d'ici. Tu dois nager pour l'atteindre. Il y a une porte à l'arrière, mais oncle Nathan ne l'ouvre pas. Ole lui a dit de ne pas le faire. Mais si tu es un ami de l'oncle Nathan, je te dirai comment l'ouvrir. Frappe à la porte comme ça : toc-toc... toc-toc. Il l'ouvrira alors.";
			link.l1 = "Je m'en souviendrai. Merci, Ole ! Vous m'avez vraiment aidé ! Je ne sais pas comment vous remercier comme il se doit.";
			link.l1.go = "store_17";
		break;
		
		case "store_17":
			dialog.text = "Apporte-moi encore une perle blanche. Si tu la trouves, bien sûr.";
			link.l1 = "Ah, oui ! Des perles blanches ! Bien. À bientôt, Ole !";
			link.l1.go = "store_18";
		break;
		
		case "store_18":
			DialogExit();
			LAi_SetLoginTime(npchar, 12.0, 21.99);
			LAi_SetCitizenType(npchar);
			LAi_group_MoveCharacter(npchar, "LSC_CITIZEN");
			sld = characterFromId("Nathaniel");
			sld.dialog.currentnode = "diffindoor";
			sld.greeting = "Nathaniel_ill"; // ноду и вякалку Натану
			pchar.questTemp.LSC.DiffIndoor = "true"; //атрибут прохода к Натану
			pchar.questTemp.LSC = "mechanic"; // флаг на разговор с Механиком
			NextDiag.CurrentNode = "ole";
			AddQuestRecord("LSC", "6");
		break;
		
		case "ole":
			dialog.text = "Ah, oncle "+pchar.name+" ! Heureux de te voir ! Comment vas-tu ?";
			link.l1 = "Merci, Ole, je vais bien. Je suis content de te voir aussi.";
			link.l1.go = "exit";
			link.l2 = "Écoute, Ole, tu as dit que les pirates de l'amiral ferment la porte de la cale et que tu l'ouvres toujours... Tous les coffres là-bas sont fermés et tu as dit que tu prends du rhum pour oncle Nathan. Comment fais-tu cela ?";
			link.l2.go = "lock";
			NextDiag.TempNode = "ole";
		break;
		
		case "lock":
			dialog.text = "Ole a un ensemble de clés fines. Elles ouvrent n'importe quelle porte ou coffre. Eh bien, pas toutes. Certaines ne peuvent pas être ouvertes mais la plupart le peuvent. Ole les a trouvées dans la cabine du méchant oncle Jurgen. Il travaille avec son marteau tous les jours près de son fourneau. Il fabrique des serrures et des clés. Et il fabrique aussi de grands et effrayants mousquets pour les méchants Narvals.";
			link.l1 = "Je vois. Ole, peux-tu me vendre ces clés ? Je peux te les payer...";
			link.l1.go = "lock_1";
		break;
		
		case "lock_1":
			dialog.text = "D'accord, oncle "+pchar.name+", je vous vendrai les clés. Je garderai simplement celle pour moi. Elle ouvre la chambre de l'amiral. Il y a beaucoup de nourriture et de rhum pour oncle Nathan. Il n'y a plus de perles ni de rhum dans les coffres de toute façon.";
			link.l1 = "Combien en voulez-vous?";
			link.l1.go = "lock_2";
		break;
		
		case "lock_2":
			dialog.text = "Tout d'abord, dis-moi, oncle "+pchar.name+", as-tu un grand navire ?";
			link.l1 = "Oui, je l'ai fait. Mais elle n'est pas ici, elle est à l'anneau extérieur. Mais je quitterai bientôt l'île et je reviendrai ici sur mon grand navire pour l'oncle Nathan.";
			link.l1.go = "lock_3";
		break;
		
		case "lock_3":
			dialog.text = "Pour oncle Nathan ? Oh, c'est merveilleux ! Écoutez alors, promettez-moi de m'emmener d'ici sur votre grand navire et laissez-moi naviguer avec vous aussi longtemps que j'en aurai besoin. Je peux être utile. Je peux attraper et cuisiner des rats... Aussi, donnez-moi cinq perles blanches. Et je vous donnerai les clés.";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l1 = "Bien sûr ! Voici tes perles. Prends-les.";
				link.l1.go = "lock_4";
			}
			link.l2 = "Attraper et cuisiner des rats ? Hé ! Une compétence intéressante. Bien sûr, Ole, nous avons un accord. Je t'apporterai cinq perles et ma parole.";
			link.l2.go = "exit";
			NextDiag.TempNode = "ole_1";
		break;
		
		case "ole_1":
			dialog.text = "Ah, oncle "+pchar.name+" ! Heureux de te voir ! Comment vas-tu ? ";
			link.l1 = "Merci, Ole, je vais bien. Je suis content de te voir aussi.";
			link.l1.go = "exit";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l2 = "Je t'ai apporté cinq perles blanches pour tes clés.";
				link.l2.go = "lock_4";
			}
			NextDiag.TempNode = "ole_1";
		break;
		
		case "lock_4":
			RemoveItems(pchar, "jewelry52", 5);
			PlaySound("interface\important_item.wav");
			dialog.text = "Perles! Perles blanches! Oncle "+pchar.name+"  a donné des perles à Ole ! Bientôt je te verrai, maman !... Oncle "+pchar.name+"promets-tu de me sortir d'ici quand tu reviendras ?";
			link.l1 = "Je le fais, Ole. Je n'ai pas encore mangé de rats. Je t'emmènerai avec moi.";
			link.l1.go = "lock_5";
		break;
		
		case "lock_5":
			GiveItem2Character(pchar, "keys_skel");
			AddCharacterExpToSkill(pchar, "Sneak", 200);
			dialog.text = "Merci, merci, bon oncle "+pchar.name+"Prends tes clés. C'est facile de les utiliser, il suffit de les insérer une par une et d'essayer. L'une d'elles finira par ouvrir la serrure dont tu as besoin. Si ce n'est pas le cas, alors la serrure est trop compliquée et tu auras certainement besoin d'une clé spéciale.";
			link.l1 = "Je vois. Je suppose que je vais m'en occuper.";
			link.l1.go = "lock_6";
		break;
		
		case "lock_6":
			dialog.text = "Attends, oncle "+pchar.name+" ! J'ai une clef de plus. Elle est jolie et astucieuse. Le méchant oncle Jurgen ne fabrique pas de clefs comme celle-ci. Je ne sais pas ce qu'elle ouvre, mais peut-être le découvrirez-vous. Regardez, c'est une clef très jolie, vous n'avez sûrement jamais vu quelque chose comme ça avant.";
			link.l1 = "Montre-moi... Oui, la clé est très intéressante. Mais à quoi sert-elle si tu ne sais pas ce qu'elle peut ouvrir ?";
			link.l1.go = "lock_7";
		break;
		
		case "lock_7":
			dialog.text = "Oncle "+pchar.name+", , vous êtes très étrange. A quoi bon ? S'il y a la clef, alors quelque part il y a la serrure. S'il y a la serrure, alors quelque part il y a la pièce de monnaie. J'ai trouvé la clef sur l'île. Cela signifie que la serrure est ici aussi. Aucun doute là-dessus. C'est une clef ingénieuse et seuls des objets très précieux sont enfermés par une telle clef. Ole le sait.";
			link.l1 = "Pour être honnête, tu es drôle, Ole. D'accord, je l'achète. Veux-tu des perles en échange ?";
			link.l1.go = "lock_8";
		break;
		
		case "lock_8":
			dialog.text = "Oui, Ole veut cinq perles. Les donneras-tu, oncle "+pchar.name+" ?";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l1 = "Tiens, prends tes perles.";
				link.l1.go = "key";
			}
			link.l2 = "Je ne les ai pas, mais je vous apporterai des perles à coup sûr.";
			link.l2.go = "exit";
			NextDiag.TempNode = "ole_2";
		break;
		
		case "key":
			RemoveItems(pchar, "jewelry52", 5);
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "sant_anna_key");
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			dialog.text = "Perles ! Des perles blanches pour le garçon blanc ! Pour sa maman ! Ici, oncle "+pchar.name+", prends la clé. Et tu trouveras la serrure, Ole sait. Tu es courageux, tu ne crains même pas les effrayants crabes.";
			link.l1 = "Oh, ne me fais pas rire, Ole ! Merci pour la clé. À bientôt !";
			link.l1.go = "exit";
			NextDiag.TempNode = "ole_3";
		break;
		
		case "ole_2":
			dialog.text = "Ah, oncle "+pchar.name+" ! Heureux de te voir ! Comment vas-tu ?";
			link.l1 = "Merci, Ole, je vais bien. Je suis content de te voir aussi.";
			link.l1.go = "exit";
			if (GetCharacterItem(pchar, "jewelry52") >= 5)
			{
				link.l2 = "Je t'ai apporté cinq perles blanches pour ta clé.";
				link.l2.go = "key";
			}
			NextDiag.TempNode = "ole_2";
		break;
		
		case "ole_3":
			dialog.text = "Ah, oncle "+pchar.name+" ! Heureux de vous voir ! Comment allez-vous ? ";
			link.l1 = "Merci, Ole, je vais bien. Je suis content de te voir aussi.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ole_3";
		break;
		
		case "return":
			dialog.text = "Oh, oncle "+pchar.name+", tu es de retour ! Tu es de retour sur le grand navire ! Me prendras-tu d'ici ? Oncle "+pchar.name+", tu m'as promis, souviens-toi ?";
			link.l1 = "Bien sûr, je le fais, l'vieux. Bienvenue à bord ! Je suppose que les rats sont en difficulté, ha-ha !";
			link.l1.go = "return_1";
			link.l2 = "Vraiment ? Et quand ai-je promis cela ? Je ne me souviens d'aucune promesse de ce genre...";
			link.l2.go = "return_3";
		break;
		
		case "return_1":
			dialog.text = "Merci, oncle ! Ole sera utile, tu verras ! Oh, peut-être que je verrai maman ? Je suis en route maintenant !";
			link.l1 = "Ne te précipite pas ainsi, Ole. Tu peux faire tes bagages. Je ne vais pas appareiller immédiatement.";
			link.l1.go = "return_2";
		break;
		
		case "return_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LSC_SetOlePassenger", 10.0);
		break;
		
		case "return_3":
			dialog.text = "Tu m'as promis, tu l'as fait ! Tu as promis d'emmener Ole d'ici ! Méchant oncle ! Tu as trompé Ole ! Mauvais oncle !";
			link.l1 = "...";
			link.l1.go = "return_4";
		break;
		
		case "return_4":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorRunToLocation(npchar, "reload", "reload45", "none", "", "", "", 20.0);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterComplexReputation(pchar, "authority", -3);
			if (GetCharacterIndex("Mary") != -1) // Мэри
			{
				sld = characterFromId("Mary");
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else // иначе завершение
			{
				chrDisableReloadToLocation = false;
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			}
		break;
		
		// Блудный сын
		case "givemepearl":
			dialog.text = "Oncle, oncle... J'ai besoin d'une perle blanche de plus. S'il te plaît, donne une perle blanche à Ole !";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "Je savais que tu le demanderais. Tiens, prends ta perle. Satisfait?";
				link.l1.go = "givemepearl_yes";
			}
			link.l2 = "Oh, et quel casse-tête... Je n'ai plus de perles, Ole, je n'en ai plus !";
			link.l2.go = "givemepearl_no";
			DeleteAttribute(npchar, "pearl_date");
		break;
		
		case "givemepearl_yes":
			RemoveItems(pchar, "jewelry52", 1);
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			dialog.text = "Merci ! Bon, bon oncle "+pchar.name+" ! Ole a encore une perle et il n'en reste plus beaucoup ! Et je vais aller voir la maman...";
			link.l1 = "Oh, et pourquoi es-tu si étrange...";
			link.l1.go = "givemepearl_yes_1";
		break;
		
		case "givemepearl_yes_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			SaveCurrentNpcQuestDateParam(npchar, "pearl_date");
			npchar.quest.pearlqty = int(npchar.quest.pearlqty)+1;
			NextDiag.CurrentNode = "givemepearl_repeat";
		break;
		
		case "givemepearl_repeat":
			dialog.text = "Merci pour une perle, bon oncle "+pchar.name+" !";
			link.l1 = "Vous êtes le bienvenu...";
			link.l1.go = "exit";
			NextDiag.TempNode = "givemepearl_repeat";
		break;
		
		case "givemepearl_no":
			dialog.text = "Pas de perle? Mais comment se fait-il, oncle "+pchar.name+"?! Il ne reste que quelques perles... Je dois les ramasser. Je vais atterrir dans ce cas. Je chercherai des perles...";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "Et où comptes-tu aller ? Que feras-tu seul ? Non, je ne veux pas être responsable de ton destin. Attends, je vais vérifier mes poches... Tiens ! Prends ton perle et reste avec moi. Satisfait ?";
				link.l1.go = "givemepearl_yes";
			}
			link.l2 = "C'est ton droit, Ole. Si tu es lassé de naviguer avec moi, alors je ne te retiendrai pas. Nous avions un accord. Tu as tout de même bien attrapé ces taux...";
			link.l2.go = "givemepearl_no_1";
		break;
		
		case "givemepearl_no_1":
			dialog.text = "Adieu, oncle "+pchar.name+". Ole a besoin de perles blanches ou il ne reviendra jamais auprès de sa mère...";
			link.l1 = "Oh, je suis vraiment désolé pour toi, mais que puis-je faire? Va, Ole. Bonne chance.";
			link.l1.go = "givemepearl_exit";
		break;
		
		case "givemepearl_exit": // Оле уходит - квест не довели до конца
			DialogExit();
			RemovePassenger(Pchar, npchar);
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			DeleteAttribute(pchar, "GenQuest.Ole");
		break;
		
		case "mother":
			dialog.text = "Oncle "+pchar.name+" ! J'ai besoin d'une perle blanche de plus. La dernière. S'il vous plaît, donnez-la à Ole !";
			if (CheckCharacterItem(pchar, "jewelry52"))
			{
				link.l1 = "Je savais que tu le demanderais. Tiens, prends ton perle. Satisfait?";
				link.l1.go = "mother_1";
			}
			link.l2 = "Oh, et quelle plaie... Je n'ai plus de perles, Ole, je n'en ai plus !";
			link.l2.go = "givemepearl_no_1";
		break;
		
		case "mother_1":
			RemoveItems(pchar, "jewelry52", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Merci, merci, bon oncle "+pchar.name+" ! Maintenant Ole a toutes les perles. Oui, toutes ! Maintenant Ole peut les apporter à maman et elle ne renverra pas Ole...";
			link.l1 = "Écoute, qui est cette maman dont tu parles toujours ? Et explique-moi enfin pourquoi tu as besoin de ces perles... perles blanches ? Et qu'est-ce que cela signifie - tu les as toutes ?";
			link.l1.go = "mother_2";
		break;
		
		case "mother_2":
			dialog.text = "Bon oncle "+pchar.name+" a aidé Ole à ramasser des perles pour sa maman... Ole était petit quand il a déchiré le collier de perles blanches de maman. Elles sont toutes tombées dans l'eau. Maman était si en colère contre Ole, et il ne peut pas rentrer à la maison tant qu'il n'a pas récupéré toutes les perles perdues\nJe me souviens combien il y en avait. Cinq fois dix perles. Maintenant Ole les a toutes. Oncle "+pchar.name+" s'il te plaît, ramène-moi chez moi ! Je veux rendre maman heureuse, rendre les perles. Ramène-moi chez moi !";
			link.l1 = "Jésus, quelle histoire incroyable... Tu es arrivé à l'Île Justice étant enfant. As-tu été chassé de chez toi parce que tu as déchiré le collier de perles de ta mère ? Sinistre...";
			link.l1.go = "mother_3";
		break;
		
		case "mother_3":
			dialog.text = "Emmène-moi voir ma mère, bon oncle "+pchar.name+"Je veux la voir. Elle sera ravie de voir des perles.";
			link.l1 = "J'aimerais bien, mais sais-tu où se trouve ta maison ? Où vit ta mère ?";
			link.l1.go = "mother_4";
		break;
		
		case "mother_4":
			dialog.text = "Elle vit sur l'île, dans la maison au toit rouge.";
			link.l1 = "Vraiment ! Sais-tu même combien d'îles il y a ici et combien de maisons avec un toit rouge ? Quel est le nom de cette île ? Donne-moi des détails...";
			link.l1.go = "mother_5";
		break;
		
		case "mother_5":
			dialog.text = "Je ne connais pas son nom. Je sais que c'était une île, maman disait à papa que nous étions sur l'île ! Et nous vivions dans la maison au toit rouge. Jolie maison, une grande. Emmène-moi chez maman, oncle "+pchar.name+" S'il vous plaît...";
			link.l1 = "Oh, très bien. Nous chercherons une telle maison sur chaque île et nous demanderons pour ta mère. Comment s'appelle-t-elle ?";
			link.l1.go = "mother_6";
		break;
		
		case "mother_6":
			dialog.text = "Son nom ? Tu es si étrange, oncle "+pchar.name+"Mère s'appelle mère. Le nom de ta mère est-il différent ?";
			link.l1 = "Oh, mon Dieu, je t'en prie, donne-moi de la patience... Très bien, Ole. Nous allons essayer de trouver ta maison. Maintenant, va au navire.";
			link.l1.go = "mother_7";
		break;
		
		case "mother_7":
			dialog.text = "Merci, oncle "+pchar.name+"Tu es très, très gentil et bon ! Bientôt Ole verra maman !";
			link.l1 = "Oh...";
			link.l1.go = "mother_8";
		break;
		
		case "mother_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			DeleteAttribute(npchar, "pearl_date");
			// ставим Агнес Кристиансен и открываем ее дом в Мариго
			LocatorReloadEnterDisable("Marigo_town", "houseSp2", false);
			sld = GetCharacter(NPC_GenerateCharacter("Agnes", "women_18", "woman", "towngirl", 10, HOLLAND, -1, true, "quest"));
			SetFantomParamFromRank(sld, 10, true);
			sld.name = "Agnes";
			sld.lastname = "Christiansen";
			sld.dialog.FileName = "Quest\LSC\OtherNPC.c";
			sld.dialog.currentnode = "agnes";
			//sld.greeting = "";
			LAi_SetOwnerType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Marigo_houseSp2", "barmen", "stay");
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
		break;
		
		case "home":
			dialog.text = "Mère... Mère, maman ! Je suis de retour !";
			link.l1 = "Fils...";
			link.l1.go = "home_1";
		break;
		
		case "home_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			SetMusic("music_romantic");
			bDisableCharacterMenu = true;//лоченые интерфейсы
			locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.005, 0.0, 2.0, 0.0, 1000);
			Pchar.FuncCameraFly = "";
			DoQuestFunctionDelay("LSC_OleReturnHome", 18.0);
		break;
		
		case "home_2":
			dialog.text = "Maman, je t'ai apporté des perles blanches ! Je les ai toutes ramassées ! Tu auras de nouveau un collier. Es-tu encore fâchée contre moi ?";
			link.l1 = "Dieu... (pleurant) Ole! Mon fils, pourquoi? Pourquoi es-tu parti? Je me fiche de ces perles!";
			link.l1.go = "home_3";
		break;
		
		case "home_3":
			sld = characterFromId("Blaze");
			dialog.text = "Maman, tiens... prends-les. Je les ai recueillis depuis longtemps. De bons oncles m'ont aidé, surtout l'oncle "+sld.name+". Il m'a pris sur son grand navire, m'a aidé à ramasser des perles et m'a ramené chez moi...";
			link.l1 = "Ole... Tu as vraiment grandi, mais tu restes un gamin... Laisse-moi te serrer dans mes bras, mon fils ! Je suis désolé, pardonne-moi pour ce maudit collier ! Je ne te laisserai jamais seul, jamais ! Nous vivrons ensemble et je prendrai soin de toi... Je ferai pénitence, je le promets !...";
			link.l1.go = "home_4";
		break;
		
		case "home_4":
			dialog.text = "Maman, tu m'as manqué... Je veux rester avec toi. Es-tu encore en colère contre moi ? Pourquoi pleures-tu ?";
			link.l1 = "(pleurant) Non, non... Je suis tellement désolé, pardonne-moi, fils !...";
			link.l1.go = "home_5";
		break;
		
		case "home_5": // перекидываем pchar
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Agnes");
			sld.dialog.currentnode = "agnes_11";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "final":
			dialog.text = "Oncle "+pchar.name+"! C'est si bon que tu sois venu ! Merci de m'avoir amené à ma mère. C'est si bon d'être ici avec elle... N'est-ce pas formidable d'être à la maison, n'est-ce pas, oncle "+pchar.name+"?";
			link.l1 = "Oui. Ole. C'est ça. Je suis content que tu sois heureux.";
			link.l1.go = "exit";
			NextDiag.TempNode = "final";
		break;
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Écoute, tu ferais mieux de ranger ton arme. Ça me rend nerveux.","Tu sais, courir avec une lame n'est pas toléré ici. Range-la.","Écoute, ne joue pas au chevalier médiéval qui court avec une épée. Range-la, cela ne te va pas...");
			link.l1 = LinkRandPhrase("Très bien.","D'accord.","Comme tu dis...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Écoutez, je suis citoyen de la ville et je vous demanderais de rengainer votre lame.","Écoute, je suis citoyen de la ville et je te demanderais de rengainer ton épée.");
				link.l1 = LinkRandPhrase("D'accord.","D'accord.","Comme tu dis...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sois prudent, mon ami, en courant avec une arme. Je peux devenir nerveux...","Je n'aime pas quand des hommes marchent devant moi avec leur arme prête. Cela me fait peur...");
				link.l1 = RandPhraseSimple("Compris.","Je l'emporte.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
