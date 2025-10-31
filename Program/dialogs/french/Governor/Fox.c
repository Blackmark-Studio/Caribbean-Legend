// полковник Фокс - бравый командир морской пехоты 'морские лисы'.
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Terrapin_KathyReward"))
			{
				dialog.text = "Que voulez-vous, Monsieur? Oh... mon... attendez! Vous êtes le capitaine français qui a sauvé ma fille des sales pattes des sbires de Levasseur ! ";
				link.l1 = "Je vois que Catherine vous a déjà parlé de moi...";
				link.l1.go = "terrapin";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Usurer") && !CheckAttribute(npchar, "quest.utensil"))
			{
				dialog.text = "Que voulez-vous, Monsieur ?";
				link.l1 = "Bonjour, Colonel. Je suis venu vous voir pour une affaire 'peu commune'. Pourriez-vous me consacrer un peu de temps ?";
				link.l1.go = "guardoftruth";
				break;
			}
			// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
			if (CheckAttribute(pchar, "questTemp.FMQN") && pchar.questTemp.FMQN == "eng_reward")
			{
				dialog.text = "Si je ne me trompe pas, vous êtes "+GetSexPhrase("le fameux capitaine","la fameuse femme capitaine")+" qui a aidé mes hommes à accomplir leur mission à Saint-Martin ? "+TimeGreeting()+" !";
				link.l1 = TimeGreeting()+", Colonel. Oui, ce serait moi.";
				link.l1.go = "FMQN";
				break;
			}
			dialog.text = "Que voulez-vous, Monsieur ?";
			link.l1 = "Rien, Colonel. Je prends congé.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "guardoftruth":
			dialog.text = "Alors crache le morceau, puisque tu es déjà allé si loin...";
			link.l1 = "Vous avez récemment abordé un schooner sous le commandement de Rollie le Cap, un pirate hollandais, et amené le capitaine ici, à St. John's.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Capitaine ? Oh, ne me fais pas rire ! Cette racaille criminelle n'a aucun droit d'être appelée par ce titre honorable. J'ai capturé un maudit pirate, la tête d'une meute de loups, qui a pillé et assassiné des marchands et commerçants anglais. Et je me suis assuré qu'il et ses dégénérés reçoivent ce qu'ils méritaient - tout St. John's a assisté à leur pendaison sur le quai !";
			link.l1 = "Je suppose que je ne pourrai pas interroger ce vaurien alors... Colonel, peut-être pourriez-vous m'aider ? Le pirate avait en sa possession quelque chose qui ne lui appartenait pas - le brûle-parfum en or. Avez-vous trouvé quelque chose sur lui qui y ressemble ?";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Non, nous l'avons fouillé et ce vaurien ne possédait aucun bien, d'ailleurs, ils avaient sûrement tous été pris à des marchands honnêtes ! Et à propos de votre préoccupation... hmm non, nous ne l'avons pas trouvée. Et que pourrait bien faire un encensoir sur un bateau pirate ? Pensez-vous vraiment qu'il y avait un prêtre parmi eux ?";
			link.l1 = "Non, je ne l'ai pas. Rollie le Cap l'a acheté chez l'usurier à Willemstad, qui l'avait acheté à un autre pirate. L'encensoir est précieux et cher, et j'essaie de le rendre à ses propriétaires légitimes. Je suppose que Rollie avait les yeux dessus comme une pie.";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "En vérité, Rollie avait des cales vides et quelques coffres avec des doublons lorsque nous avons abordé et capturé son navire. Rien que des ordures. Pas de trésors, pas de ciboire en or. Je me souviendrais d'un tel objet incongru pour un pirate.\nJe soupçonne que ce maudit pirate a caché ses économies à la Dominique. Nous y avons même débarqué et fouillé la zone mais n'avons rien trouvé. Mais nous ne sommes pas restés sur l'île ni n'avons exploré ses profondeurs en raison du grand nombre de sauvages là-bas.";
			link.l1 = "Hm... Le pirate aurait pu cacher l'encensoir avec le reste de ses biens volés quelque part à la Dominique... Quel dommage. Avez-vous interrogé le pirate avant l'exécution?";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "Je l'ai fait... et il a juste commencé à rire en pleine figure. Mais je ne me souciais guère de ses caches. Rollie le Cap a été pendu et c'est la chose la plus importante.";
			link.l1 = "Je vois. Merci pour votre récit et votre temps, Colonel. Adieu...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("GuardOT_Fox_DlgExit");
		break;
		
		case "terrapin":
			dialog.text = "Plusieurs fois, capitaine ! Votre acte honorable et courageux était à peine attendu d'un Français. Je vous dois ma gratitude, en tant que soldat et en tant que père. Il n'y a rien de plus précieux pour moi dans ce monde entier que ma fille...";
			link.l1 = "Je suis heureux d'avoir pu vous aider, et j'espère qu'avec mes actions vous changerez d'avis sur les Français, avec le temps.";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			dialog.text = "La présence d'un gentilhomme aussi honorable et généreux que vous, qui avez risqué votre vie pour une jeune Anglaise inconnue, provoquera un réchauffement essentiel de ma relation avec vos compatriotes !";
			link.l1 = "Il y a des honnêtes gens parmi les rats de toute nation, colonel...";
			link.l1.go = "terrapin_2";
		break;
		
		case "terrapin_2":
			dialog.text = "Et vous l'avez prouvé ! Une récompense vous attend, capitaine. Bien sûr, la vie de ma fille est inestimable, mais Jonathan Fox paie toujours ses dettes, je le jure ! Vous êtes un vrai soldat, donc mon cadeau pour vous est un cadeau de soldat. Tenez, regardez.\nCeci est un tromblon, un excellent mousquet de marine, utilisable d'une seule main. Vous pouvez le charger avec des flèches spéciales qui transperceront toujours même la cuirasse la plus résistante. Il tire également de la mitraille et sa construction solide vous permet de le charger avec des clous. Tenez, prenez-le, il est à vous maintenant.";
			link.l1 = "Un cadeau aussi excellent pour un soldat, je vous remercie, Colonel !";
			link.l1.go = "terrapin_3";
		break;
		
		case "terrapin_3":
			Log_Info("You have received a blunderbuss");
			Log_Info("You have received 10 arrows");
			Log_Info("You have received 10 charges of nails");
			Log_Info("You have received instructions for creating the harpoon arrows");
			Log_Info("You have received instructions for creating the charge of nails");
			GiveItem2Character(pchar, "pistol8");
			TakeNItems(pchar, "harpoon", 10);
			TakeNItems(pchar, "GunEchin", 10);
			GiveItem2Character(pchar, "recipe_harpoon"); 
			GiveItem2Character(pchar, "recipe_GunEchin"); 
			PlaySound("interface\important_item.wav");
			dialog.text = "Je vous remets également un petit lot de munitions et des instructions pour leur fabrication. Ce serait dommage si vous n'utilisiez pas sa puissance au maximum !";
			link.l1 = "Merci, Colonel. Je n'refuserai pas un tel cadeau, mais je veux que vous sachiez que je n'ai pas sauvé Catherine pour une récompense. Je n'aurais tout simplement pas pu laisser la fille sans défense subir un quelconque mal.";
			link.l1.go = "terrapin_4";
		break;
		
		case "terrapin_4":
			dialog.text = "Je le sais, capitaine. Cela vous honore doublement. Catherine était vraiment ravie par vous et ce n'est pas une tâche facile de lui faire bonne impression. Encore une fois, nous vous devons notre gratitude pour l'avoir sauvée. Je vous dois une fière chandelle !";
			link.l1 = "Eh bien, je vous remercie pour le cadeau, Colonel. Transmettez mes salutations à Catherine, et j'espère qu'elle écoutera son père la prochaine fois.";
			link.l1.go = "terrapin_5";
		break;
		
		case "terrapin_5":
			dialog.text = "Je le ferai, Capitaine ! Adieu, et bon voyage !";
			link.l1 = "Adieu, Colonel.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Terrapin_KathyReward");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 5);
			ChangeCharacterNationReputation(pchar, ENGLAND, 20);
		break;
		
		// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
		case "FMQN":
			DelLandQuestMark(npchar);
			dialog.text = "J'ai lu le rapport. Vos actions sont hautement évaluées, vous devez donc être récompensé. Trente mille pesos pour les services d'expédition et des armes pour héroïsme dans la soldatesque. Acceptez cette lame et cette arquebuse. Elles sont maintenant toutes à vous !";
			link.l1 = "Merci, Monsieur.";
			link.l1.go = "FMQN_1";
		break;
		
		case "FMQN_1":
			dialog.text = "Par tous les moyens, Capitaine. Vous êtes également récompensé par l'amour et le respect des colonies britanniques, des autorités et de moi-même personnellement. Je vous remercie de ne pas avoir abandonné mes hommes et de les avoir aidés dans leur mission !";
			link.l1 = "Mon plaisir, Colonel...";
			link.l1.go = "FMQN_2";
		break;
		
		case "FMQN_2":
			dialog.text = "Maintenant, veuillez m'excuser - j'ai d'autres affaires à régler. Bon vent, Capitaine "+pchar.lastname+".";
			link.l1 = "Adieu, "+GetAddress_Form(NPChar)+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_EnglandComplete");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
