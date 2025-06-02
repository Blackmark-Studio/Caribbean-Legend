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
			dialog.text = "Que voulez-vous ?";
			link.l1 = "Rien.";
			link.l1.go = "exit";
		break;

		case "Juli":
			dialog.text = "...";
			if (pchar.sex == "woman")
			{
				link.l1 = "Mademoiselle, on dit que Port-au-Prince perd de son charme lorsque vous ne souriez pas. Aujourd’hui, il semble bien que ce soit le cas. Pardonnez ma franchise, mais quelque chose vous tracasse ?";
			}
			else
			{
				link.l1 = "Mademoiselle, j'ai entendu parler de votre beauté et de votre charme, et je dois dire que les rumeurs ne sont pas exagérées. On dit aussi que Port-au-Prince perd de son éclat lorsque vous ne souriez pas. Aujourd'hui, hélas, il semble que ce soit le cas. Dites-moi le nom du scélérat qui a osé assombrir votre journée, et je le provoquerai en duel pour redonner le sourire à votre beau visage.";
			}
			link.l1.go = "Juli_2";
			DelLandQuestMark(npchar);
		break;

		case "Juli_2":
			if (pchar.sex == "woman")
			{
				dialog.text = "Ah, mademoiselle, vous êtes trop attentionnée... Je dois avouer que votre sollicitude me touche. Mais hélas, la cause de mon souci ne peut être dissipée par une simple conversation. Ce n’est la faute de personne, mais plutôt des circonstances que, je le crains, même la plus résolue des personnes ne peut contrôler.";
				link.l1 = "Des circonstances ? Je vous assure, mademoiselle, que pour "+GetFullName(pchar)+", il n’existe aucun obstacle infranchissable. Dites-moi ce qui s’est passé, peut-être puis-je vous aider.";
			}
			else
			{
				dialog.text = "Oh, monsieur, vous êtes un véritable maître des mots flatteurs. Je dois dire que vous avez presque réussi à faire naître un sourire sur mon visage. Mais hélas, un duel ne pourra pas résoudre mon problème. Celui qui a assombri ma journée n’est pas un vilain, mais plutôt des circonstances que même un gentilhomme aussi valeureux que vous ne pourrait maîtriser.";
				link.l1 = "Des circonstances ? Je vous assure, mademoiselle, que le capitaine "+GetFullName(pchar)+" triomphe de toutes les situations ! Et si je devais échouer, je vous jure que je mangerai le chapeau du premier passant que je croise !";
			}
			link.l1.go = "Juli_3";
		break;

		case "Juli_3":
			if (pchar.sex == "woman")
			{
				dialog.text = "Si vous insistez vraiment, je vais vous dire ce qui s’est passé. Mais d’abord, j’ai besoin de votre promesse que cette conversation restera entre nous.";
				link.l1 = "Je vous donne ma parole d’honneur, mademoiselle. Tout ce que vous me confierez restera entre nous, même si je dois emporter ce secret au fond de l’océan.";
			}
			else
			{
				dialog.text = "Monsieur "+pchar.lastname+", vous avez sans aucun doute le don d'égayer même une dame profondément contrariée. Mais je vous en prie, épargnez les chapeaux des pauvres passants. Si vous insistez vraiment, je vais vous raconter ce qui s’est passé. Donnez-moi simplement votre parole que mes mots resteront un secret entre nous deux.";
				link.l1 = "Je vous le promets, mademoiselle, tout ce que vous me direz restera secret, même sous la menace de la mort.";
			}
			link.l1.go = "Juli_4";
		break;
		
		case "Juli_4":
			dialog.text = "Très bien. Un collier a récemment disparu de ma chambre... mais comprenez que ce n'est pas un simple bijou. Il m'a été offert par une personne qui occupe une place chère dans mon cœur. À présent, j’ai l’impression d’avoir perdu bien plus qu’un objet\nJ’ai longuement réfléchi à qui aurait pu faire cela, et je ne vois qu’une seule possibilité. Je crains que ce ne soit l’un de mes domestiques. Ce sont les seuls à avoir accès à ma chambre, et à pouvoir convoiter un tel bijou. Mais je ne peux pas en parler ouvertement...";
			link.l1 = "C’est en effet une affaire délicate, surtout si vous tenez à ce qu’elle reste secrète. Mais si je dois vous aider, j’ai besoin de comprendre ce qui vous pousse à garder le silence. Je dois savoir ce que nous risquons et de qui nous devons nous méfier, pour éviter de trahir votre secret par mégarde.";
			link.l1.go = "Juli_5";
			if (pchar.sex == "woman")
			{
				link.l2 = "Vous ne le pouvez pas ? Eh bien, mademoiselle, il ne me reste qu’à vous souhaiter bonne chance. Les intrigues ne sont pas dans mes habitudes. Votre problème, à mon sens, pourrait être résolu en faisant appel à la garde. Mais il semble que vous ayez choisi de compliquer les choses.";
				link.l2.go = "Juli_end";
			}
			else
			{
				link.l2 = "Vous ne le pouvez pas ? Pardonnez-moi, mademoiselle, mais dans ce cas, je suis véritablement impuissant. Les jeux de secrets ne sont pas pour moi. Votre problème me semble ridiculement simple : la garde pourrait le résoudre en un instant. Mais vous semblez avoir choisi d’en faire un secret d'État.";
				link.l2.go = "Juli_end";
			}
		break;

		case "Juli_end":
			dialog.text = "C’est ainsi que vous affrontez les difficultés, "+GetFullName(pchar)+" ? On vous confie un secret et vous tournez les talons ? J’espère que vous trouverez des tâches plus dignes de vos talents remarquables – peut-être compter des barils de rhum ou argumenter avec des marchands de quai. Mais au moins, gardez notre échange pour vous, si vous avez encore un soupçon d’honneur. Adieu.";
			link.l1 = "...";
			link.l1.go = "Juli_end_2";
		break;

		case "Juli_end_2":
			DialogExit();
			CloseQuestHeader("UV");
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;

		case "Juli_5":
			dialog.text = "Vous avez raison, "+GetAddress_Form(NPChar)+", vous méritez la vérité. Ce collier était un cadeau d’un homme que mon oncle, le gouverneur des territoires français de cette île, déteste. Il m’a interdit formellement de mentionner son nom. S’il découvre de qui provient ce collier, les conséquences pourraient être désastreuses, pas seulement pour moi, mais aussi...";
			link.l1 = "Inutile d’en dire plus, madame. J’en sais assez. Je vous promets que je ferai tout ce qui est en mon pouvoir pour récupérer votre collier, sans jamais mettre votre secret en danger.";
			link.l1.go = "Juli_6";
		break;

		case "Juli_6":
			dialog.text = "Merci à vous, "+GetSexPhrase("monsieur "+pchar.lastname+"",""+pchar.name+"")+". Votre détermination et votre discrétion me touchent profondément. J’ai confiance en vous – mon secret est en de bonnes mains. Que la chance vous accompagne dans cette tâche difficile.";
			if (pchar.sex == "woman")
			{
				link.l1 = "La chance sourit à celles qui agissent, mademoiselle. Je retrouverai votre collier, soyez-en certaine.";
			}
			else
			{
				link.l1 = "La chance sourit aux forts, mademoiselle. Dès que j’aurai retrouvé ce collier, il sera entre vos mains délicates.";
			}
			link.l1.go = "Juli_7";
		break;
		
		case "Juli_7":
			DialogExit();
			
			NextDiag.CurrentNode = "Juli_7_again";
			AddQuestRecord("UV", "2");
			AddQuestUserData("UV", "sSex", GetSexPhrase("","а"));
			
			pchar.questTemp.UV_Lavochniki = true;
		break;
		
		case "Juli_7_again":
			if (CheckCharacterItem(PChar, "SM_necklace_Julie"))
			{
				dialog.text = "Ah, Capitaine, vous êtes de retour... L'avez-vous trouvé ? Je vous en prie, dites-moi que le collier est à nouveau en sécurité.";
				link.l1 = "Vos inquiétudes sont terminées, Julie. Le collier est en ma possession, et j’ai le plus grand plaisir à le restituer à sa place légitime – entre vos mains délicates.";
				link.l1.go = "Juli_22";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "Ah, Capitaine, vous êtes de retour... L'avez-vous trouvé ? Je vous en prie, dites-moi que le collier est à nouveau en sécurité.";
				link.l1 = "Hélas, Julie, pas encore. Mais ne vous inquiétez pas, je ferai tout pour le récupérer et vous le rendre.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Juli_7_again";
				DelLandQuestMark(npchar);
			}
		break;

		case "Starpom_1":
			dialog.text = "Bonjour, monsieur. Qu'est-ce qui vous amène à bord de notre navire ?";
			link.l1 = "Je cherche Tristan Renier, j’ai une affaire lucrative à lui proposer.";
			link.l1.go = "Starpom_2_sneak";
			link.l2 = "J’ai besoin de parler à Tristan Renier, c’est une affaire d’ordre personnel.";
			link.l2.go = "Starpom_2_fortune";
			DelLandQuestMark(npchar);
		break;

		case "Starpom_2_sneak":
			dialog.text = "Le capitaine est actuellement à terre. Vous pourriez peut-être le trouver en ville.";
			link.l1 = "Auriez-vous une idée plus précise de l’endroit où il est allé ?";
			link.l1.go = "Starpom_3";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;

		case "Starpom_2_fortune":
			dialog.text = "Le capitaine est actuellement à terre. Vous pourriez peut-être le trouver en ville.";
			link.l1 = "Auriez-vous une idée plus précise de l’endroit où il est allé ?";
			link.l1.go = "Starpom_3";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "Starpom_3":
			dialog.text = "Je suis désolé, "+GetAddress_Form(NPChar)+", mais le capitaine ne partage pas ses plans avec moi. Tout ce que je sais, c’est qu’il est descendu à terre il y a quelques heures.";
			link.l1 = "C’est déjà utile. Merci pour votre aide.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("UV_GoldSeagull_RasprashivaemZhiteley");
		break;

		case "Captain_1":
			if (pchar.sex == "man")
			{
				dialog.text = "Qui diable êtes-vous ? Et avec quel droit osez-vous entrer dans mes quartiers privés sans y être invité ?";
				link.l1 = "Je m'appelle "+GetFullName(pchar)+". Et j’ai une affaire à vous proposer.";
			}
			else
			{
				dialog.text = "Et qui êtes-vous, mademoiselle ? Je ne me souviens pas avoir invité qui que ce soit. Quoique, je dois avouer que certaines visites inattendues sont plus... intrigantes que d'autres. Que me vaut cet honneur ?";
				link.l1 = "Je suis le capitaine "+GetFullName(pchar)+". Et je suis venue pour une affaire sérieuse.";
			}
			link.l1.go = "Captain_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Captain_2":
			if (pchar.sex == "man")
			{
				dialog.text = "Des affaires, dites-vous ? Quelle sorte d'affaire pourrait bien justifier une interruption aussi incivile ?";
				link.l1 = "C’est très simple. Vous possédez un collier que je suis venu récupérer.";
			}
			else
			{
				dialog.text = "Des affaires, dites-vous ? Tout à fait fascinant... Quelle affaire commerciale si pressante pousserait une dame de vos charmes considérables à me chercher dans mes appartements privés ?";
				link.l1 = "Épargnez-moi vos paroles mielleuses, monsieur. Je suis venue pour le collier en votre possession. Et oui, je sais précisément que vous l'avez.";
			}
			link.l1.go = "Captain_3";
		break;

		case "Captain_3":
			if (pchar.sex == "man")
			{
				dialog.text = "Ha ! Un collier, dites-vous ? En effet, j'ai acquis une telle pièce récemment, mais en quoi cela vous concerne-t-il ? Vous n'espérez sûrement pas que je cède ma propriété au premier étranger qui l'exige ?";
			}
			else
			{
				dialog.text = "Un collier ? En effet... J'ai récemment acquis un tel bijou. Et dites-moi, capitaine, par quels moyens proposez-vous de me déposséder de ce bijou qui m'appartient légitimement ?";
			}
			if (sti(pchar.Money) >= 5000)
			{
				link.l1 = "Je suis prêt"+GetSexPhrase("","e")+" à vous offrir cinq mille pesos pour cette pièce. Une somme considérable qui vous permettrait d’acheter un ornement tout aussi raffiné, peut-être même plus grandiose. Pendant ce temps, ce collier particulier serait restitué à quelqu’un qui le valorise au-delà de toute mesure—bien plus que n’importe quelle valeur monétaire.";
				link.l1.go = "Captain_4_commerce";
			}
			link.l2 = "Permettez-moi de parler franchement, monsieur. Vos choix se sont considérablement réduits : rendez le collier volontairement et vivez pour naviguer un autre jour, ou résistez et faites-moi le récupérer de votre corps sans vie. La décision vous appartient, mais je vous recommande de la prendre rapidement.";
			link.l2.go = "Captain_4_leadership";
		break;

		case "Captain_4_commerce":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 45)
			{
				dialog.text = "Cinq mille, dites-vous ? Eh bien, Capitaine, vous proposez un marché persuasif. Tenez, prenez ce bijou s’il compte tant pour vous.";
				link.l1 = "Votre sagesse égale votre générosité, monsieur. Cette décision ne sera pas regrettée.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("UV_Ozherelie");
				notification("Vérification réussie", SKILL_COMMERCE);
				GiveItem2Character(pchar, "SM_necklace_Julie");
				ChangeCharacterComplexReputation(pchar, "nobility", 2);
				AddMoneyToCharacter(pchar, -5000);
			}
			else
			{
				dialog.text = "Je n’ai pas acquis ce collier pour le troquer avec le premier vagabond qui fait miroiter de l’argent ! Il est destiné à être un cadeau pour ma femme, et je n’en entendrai pas plus sur ce sujet. Retirez-vous de ma présence avant que je n’appelle mes hommes pour vous escorter dehors !";
				link.l1 = "Puisque vous refusez un accord à l’amiable, je le prendrai par des moyens moins civilisés.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("UV_Ozherelie_Duel");
				notification("Compétence insuffisante (45)", SKILL_COMMERCE);
			}
		break;

		case "Captain_4_leadership":
			if (GetSummonSkillFromName(pchar, SKILL_Leadership) >= 45)
			{
				dialog.text = "Argh... Petit insolent... Tu crois vraiment que je vais trembler devant tes menaces ridicules ? Ha ! Tu ne sais pas à qui tu t’adresses !";
				link.l1 = "Peu m’importe qui tu es. Donne-moi simplement le collier et je m’en vais. Ou es-tu vraiment prêt à mourir pour un bijou qui ne vaut rien pour toi ?";
				link.l1.go = "Captain_4_leadership_2";
				notification("Vérification réussie", SKILL_Leadership);
				AddCharacterExpToSkill(pchar, "Fortune", 100);
			}
			else
			{
				dialog.text = "Je n’ai pas acheté ce collier pour marchander avec des gens comme vous ! C’était un cadeau pour ma femme, et vous n’avez rien à faire ici. Partez, avant qu’on ne vous jette dehors !";
				link.l1 = "Si vous refusez de vous en séparer à l’amiable, je le prendrai de force.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("UV_Ozherelie_Duel");
				notification("Compétence insuffisante (45)", SKILL_Leadership);
			}
		break;

		case "Captain_4_leadership_2":
			dialog.text = "Que le diable t’emporte, toi et ce maudit collier ! Prends-le. Prends-le et fiche le camp avant que je ne change d’avis.";
			link.l1 = "Une sage décision ! Adieu.";
			AddDialogExitQuestFunction("UV_Ozherelie");
			GiveItem2Character(pchar, "SM_necklace_Julie");
		break;

		case "Juli_22":
			dialog.text = ""+pchar.name+", vous m’avez redonné le sourire ! Vous avez rendu bien plus qu’un simple collier — une partie de mon âme. Votre noblesse mérite l’admiration, et je promets que tous ceux que je rencontrerai connaîtront votre vaillance.";
			link.l1 = "Voyons, mademoiselle, je ne l’ai pas fait pour les louanges. Votre sourire est la seule récompense qui compte vraiment pour moi.";
			link.l1.go = "Juli_23";
			TakeItemFromCharacter(pchar, "SM_necklace_Julie");
			AddCharacterExpToSkill(pchar, "Leadership", 300);
		break;

		case "Juli_23":
			dialog.text = "Vous êtes si modeste, "+pchar.name+". Mais je vous en prie, acceptez ce coffre de doublons. Ce n’est qu’en sachant que vous l’avez accepté que je me sentirai véritablement reconnaissante.";
			link.l1 = "Je vous en prie, mademoiselle, n’insistez pas. Vos mots de gratitude valent plus pour moi que n’importe quel trésor.";
			link.l1.go = "Juli_24_nobility";
			link.l2 = "Si cela peut vous apaiser, mademoiselle, j’accepte votre don. Mais sachez que je ne l’ai pas fait pour une récompense. "+GetSexPhrase("Votre reconnaissance","Votre gratitude")+" compte bien plus pour moi que ces doublons.";
			link.l2.go = "Juli_24_chest";
		break;

		case "Juli_24_nobility":
			dialog.text = "J’ai complètement oublié de vous demander... Savez-vous qui a volé ce collier ?";
			link.l1 = "Je ne sais qu’une chose, mademoiselle : il semble qu’une certaine Giselle l’ait vendu au marchand. Et il ne s’agit probablement pas du dernier bijou qu’elle compte écouler.";
			link.l1.go = "Juli_25";
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
		break;

		case "Juli_24_chest":
			dialog.text = "J’ai complètement oublié de vous demander... Savez-vous qui a volé ce collier ?";
			link.l1 = "Je ne sais qu’une chose, mademoiselle : il semble qu’une certaine Giselle l’ait vendu au marchand. Et il ne s’agit probablement pas du dernier bijou qu’elle compte écouler.";
			link.l1.go = "Juli_25";
			GiveItem2Character(PChar, "chest");
		break;

		case "Juli_25":
			dialog.text = "Giselle ? Mais c’est ma servante ! Je la soupçonnais... mais je ne voulais pas y croire. Le pire, c’est que je ne peux même pas la punir comme il se doit. Elle pourrait révéler mon secret, et ça, je ne peux le permettre.";
			link.l1 = "Et qu’allez-vous faire ? Lui pardonner tout et la laisser continuer à vous voler ?";
			link.l1.go = "Juli_26";
		break;

		case "Juli_26":
			dialog.text = "Oh non, certainement pas. D’abord, je vais m’assurer qu’elle ne soit plus à mes côtés. Ensuite, je trouverai un moyen de la punir... discrètement, pour que cela ne semble pas venir de moi.";
			link.l1 = "L’ingéniosité féminine est une arme redoutable, surtout entre les mains d’une dame aussi fine et perspicace que vous. Je suis sûr que votre servante ne soupçonne même pas que la partie est déjà perdue — et pas en sa faveur.";
			link.l1.go = "Juli_27";
		break;

		case "Juli_27":
			dialog.text = "Ah, capitaine... Ce n’est jamais agréable d’avoir recours à de tels stratagèmes, mais parfois la ruse est la seule voie possible.";
			link.l1 = "Bien sûr, Julie. Je suis désolé de devoir vous quitter, mais le devoir m’appelle. Qui prendra soin de mes hommes, si ce n’est moi ?";
			link.l1.go = "Juli_28";
		break;
		
		case "Juli_28":
			dialog.text = "À bientôt, "+pchar.name+". Revenez souvent dans notre port, je vous prie. Notre ville manque cruellement de "+GetSexPhrase("gentilshommes nobles et courageux comme vous.","jeunes femmes au cœur noble et à l’esprit déterminé, comme vous.")+"";
			link.l1 = "Vous me flattez, mademoiselle. Je vous promets de ne manquer aucune occasion de revenir dans votre charmante ville. À très bientôt.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("UV_Juli_GoodEnd");
		break;

		case "Juli_31":	
			if (CheckAttribute(pchar, "questTemp.UV_ojerelie_Julie"))
			{
				switch (rand(1))
				{
					case 0:
						dialog.text = ""+pchar.name+" ! Quelle rencontre inattendue ! Toujours en train de conquérir les mers ?";
						link.l1 = "Ravi de vous voir, mademoiselle. J’essaie, même si la mer reste capricieuse comme toujours. Et vous, profitez-vous de la tranquillité ?";
						link.l1.go = "Juli_32";
					break;

					case 1:
						dialog.text = "Ah, capitaine "+pchar.lastname+", je suis si heureuse de vous voir ! J’espère que tout va bien pour vous ?";
						link.l1 = "Heureux"+GetSexPhrase("","e")+" de vous revoir, mademoiselle. Les affaires exigent temps et énergie, mais des rencontres comme celle-ci embellissent n’importe quelle journée. Et vous, comment allez-vous ?";
						link.l1.go = "Juli_33";
					break;
				}
			}
			else
			{
				switch (rand(1))
				{
					case 0:
						dialog.text = "Capitaine "+pchar.lastname+", encore ici ? Reste-t-il quelqu’un dans notre modeste ville que vous n’ayez pas encore trahi pour une poignée d’or ?";
						link.l1 = "Mademoiselle, je comprends votre ressentiment, mais j’ai agi comme je le jugeais nécessaire. Parfois, les bonnes décisions causent de la peine, et je regrette que cela vous ait blessée.";
						link.l1.go = "exit";
						NextDiag.TempNode = "Juli_34_zlaya";
					break;

					case 1:
						dialog.text = "Capitaine "+pchar.lastname+", encore vous ? Votre avidité est-elle si grande que vous ne pouvez laisser notre ville en paix et cherchez une nouvelle victime ?";
						link.l1 = "Mademoiselle, je suis navré que mes actions vous aient affectée ainsi, mais j’ai agi selon ma conscience.";
						link.l1.go = "exit";
						NextDiag.TempNode = "Juli_34_zlaya";
					break;
				}
			}
			SetTimerFunction("UV_Julie_HelloAgain", 0, 0, 1);
		break;

		case "Juli_32":	
			dialog.text = "Dernièrement, tout est calme et paisible, rien ne vient troubler cette quiétude. Passez au port plus souvent, capitaine. Je suis certaine qu’ici, dans notre boutique comme ailleurs, vous trouverez tout ce que vous pouvez désirer.";
			link.l1 = "Merci, mademoiselle. Je tâcherai de venir plus souvent. Je suis sûr"+GetSexPhrase("","e")+" que votre ville saura encore me surprendre agréablement.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Juli_repeat_residence_1";
		break;

		case "Juli_33":	
			dialog.text = "Grâce à vous, capitaine, tout est bien plus paisible à présent. J’espère que vous nous ferez encore l’honneur de votre visite.";
			link.l1 = "Sans aucun doute, mademoiselle. Votre ville me laisse toujours les plus agréables impressions. À très bientôt.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Juli_repeat_residence_1";
		break;
		
		case "Juli_repeat_residence_1":
			switch (rand(1))
			{
				case 0:
					dialog.text = "Capitaine "+pchar.lastname+", nous nous retrouvons à nouveau. Étonnant, n’est-ce pas ?";
					link.l1 = "Le destin semble favoriser nos rencontres aujourd’hui, mademoiselle.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Juli_repeat_residence_1";
				break;

				case 1:
					dialog.text = "Capitaine "+pchar.lastname+", il semble que nos chemins se croisent encore.";
					link.l1 = "On dirait bien, mademoiselle. Heureux"+GetSexPhrase("","e")+" de vous revoir.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Juli_repeat_residence_1";
				break;
			}
		break;

		case "Juli_34_zlaya":
			switch (rand(1))
			{
				case 0:
					dialog.text = "On dirait que nous nous croisons un peu trop souvent, capitaine. Ou est-ce que vous ne pouvez tout simplement pas vous éloigner de ceux que vous avez déjà trahis ?";
					link.l1 = "Mademoiselle, nos rencontres sont fortuites, mais je comprends votre ressentiment. J’espère seulement qu’un jour vous comprendrez mes motivations.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Juli_34_zlaya";
				break;

				case 1:
					dialog.text = "Que voulez-vous encore ? Il est peu probable que cette rencontre soit un simple hasard. Ou êtes-vous venu me rappeler votre ignominie ?";
					link.l1 = "Mademoiselle, je n’ai aucune intention de m’imposer ni de raviver le passé. Cette rencontre est purement fortuite.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Juli_34_zlaya";
				break;
			}
		break;
		
		
		
		
		
		
		
	}
}