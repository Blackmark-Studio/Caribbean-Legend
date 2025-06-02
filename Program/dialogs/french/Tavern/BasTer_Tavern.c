// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quelles questions avez-vous?","Comment puis-je vous aider, "+GetAddress_Form(NPChar)+"?"),"Qu'est-ce que c'est, "+GetAddress_Form(NPChar)+"...","C'est la troisième fois que tu me déranges maintenant...","Plus de questions, je présume?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("J'ai changé d'avis...","Je n'ai rien à dire pour le moment."),"Humph, où est passée ma mémoire...","Oui, c'est vraiment la troisième fois...","Non, quelles questions?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Jason, суп из черепахи
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "baster" && !CheckAttribute(npchar, "quest.terrapin"))
			{
				link.l1 = "Je cherche mon vieux compagnon de bord Fernand Luc. J'ai deux ou trois questions à lui poser. J'ai entendu dire qu'il s'est bien amusé ici il y a une semaine...";
				link.l1.go = "terrapin";
			}
			//Sinistra Путеводная звезда
			if (CheckAttribute(pchar, "questTemp.PZ_BasTerTavern"))
			{
				link.l1 = "Mon ami et moi avions convenu de nous rencontrer ici, mais je ne le vois nulle part. Savez-vous où il est allé ? Est-il encore en ville, ou au moins sur l'île ? Il s'appelle Longway - il est chinois.";
				link.l1.go = "PZ_BasTerTavern_1";
			}
			//--> Торговля по закону
			if (CheckAttribute(pchar, "questTemp.TPZ_Tavern_2"))
			{
				link.l1 = "Bonne nouvelle, "+npchar.name+". J'ai exactement ce qu'il vous faut pour remettre votre affaire sur pied. Cent bouteilles de bon vin et cent de rhum. Avec une telle cargaison, vos clients nageront à nouveau dans les rivières d'alcool. Êtes-vous prêt à payer?";
				link.l1.go = "TPZ_Tavern2_1";
			}
			if (CheckAttribute(pchar, "questTemp.TPZ_Tavern_3"))
			{
				link.l1 = "Alors, "+npchar.name+", êtes-vous prêt à discuter des termes de l'accord?";
				link.l1.go = "TPZ_Tavern2_11";
			}
			if (CheckAttribute(pchar, "questTemp.TPZ_Tavern_4"))
			{
				link.l1 = "Eh bien, "+npchar.name+". Tout est réglé de mon côté et la cargaison est déjà en route vers la taverne. On passe au paiement?";
				link.l1.go = "TPZ_Tavern3_1";
			}
			//<-- Торговля по закону
		break;
		
		//суп из черепахи
		case "terrapin":
			dialog.text = "Il pourrait encore passer du bon temps en enfer. Ton compagnon est mort, donc tu arrives un tantinet tard, capitaine. Cet homme là-bas, assis à la table la plus éloignée, a payé pour ses funérailles, bien que j'aie l'impression que c'est le même homme qui les a causées. Il a une tête de pendu, comme on dit. Il s'appelle Robert Martene. Si tu veux, tu peux aller le voir et lui demander toi-même. ";
			link.l1 = "Merci, l'ami. Je vais aller parler à monsieur Robert. Nous boirons à l'âme du pauvre vieux Luc pour qu'il repose en paix...";
			link.l1.go = "terrapin_1";
			npchar.quest.terrapin = "true";
		break;
		
		case "terrapin_1":
			DialogExit();
			AddQuestRecord("Terrapin", "4");
			pchar.questTemp.Terrapin = "rober";
		break;
		
		// Sinistra - Квест "Длинные тени старых грехов" ==>
		case "DTSG_BasTerTavern_1":
			dialog.text = "Y a-t-il vraiment à discuter? Il t'a attaqué, toi et ton ami, tu t'es défendu, je vois ça presque tous les jours. Beau boulot. Maintenant, je n'ai plus qu'à nettoyer ce bazar...";
			Link.l1 = "Vous nettoierez ça, je suis sûr que vous y êtes habitué maintenant. Que savez-vous de lui ?";
			Link.l1.go = "DTSG_BasTerTavern_2";
		break;
		
		case "DTSG_BasTerTavern_2":
			dialog.text = "Pas grand-chose, vraiment. Il est arrivé il y a quelques jours. Il appréciait l'endroit, a même loué une maison à la périphérie de la ville. Il venait souvent, payait régulièrement. Et, le plus important, il s’est comporté correctement tout ce temps, n’a jamais dit un mauvais mot à personne. Je suis encore choqué qu'il vous ait attaqué, vous et votre ami. Je pensais qu'il pourrait s'installer ici pour de bon.";
			Link.l1 = "D'une certaine manière, il l'a fait. Bon, ce n'est pas grand-chose, mais merci pour ça, mon ami. À la prochaine.";
			Link.l1.go = "DTSG_BasTerTavern_3";
		break;
		
		case "DTSG_BasTerTavern_3":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DTSG_BasTerTavern");
			LAi_LocationDisableOfficersGen("BasTer_tavern", false);
			SetQuestHeader("DTSG");
			AddQuestRecord("DTSG", "1");
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			sld = CharacterFromID("Knippel");
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			sld.Dialog.CurrentNode = "Knippel_officer";
			sld.location = "None";
			
			PChar.quest.DTSG_BasTerDom.win_condition.l1 = "locator";
			PChar.quest.DTSG_BasTerDom.win_condition.l1.location = "BasTer_town";
			PChar.quest.DTSG_BasTerDom.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_BasTerDom.win_condition.l1.locator = "HutFish1";
			PChar.quest.DTSG_BasTerDom.win_condition = "DTSG_BasTerDom";
			
			SetTimerCondition("DTSG_BasTerDom_Timer", 0, 0, 7, false);
			SetTimerCondition("DTSG_Etap2", 0, 0, 14, false);
		break;
		// <== Квест "Длинные тени старых грехов" - Sinistra
		
		// Sinistra - Квест "Путеводная звезда" ==>
		
		case "PZ_BasTerTavern_1":
			dialog.text = "Ce nom ne me dit rien, et en général, je ne laisse pas entrer des gens comme lui dans mon établissement, ni je ne m'y intéresse.";
			Link.l1 = "D'accord. Très bien, à plus tard.";
			Link.l1.go = "PZ_BasTerTavern_2";
		break;
		
		case "PZ_BasTerTavern_2":
			DialogExit();
			bDisableLandEncounters = true;
			DeleteAttribute(pchar, "questTemp.PZ_BasTerTavern");
			DeleteAttribute(pchar, "questTemp.PZ_BasTerAlkash");
			pchar.questTemp.PZ_BasTerTavern2 = true;
			DeleteQuestCondition("PZ_BasTer_Opozdal");
			DelMapQuestMarkIsland("Guadeloupe");
			
			PChar.quest.PZ_BasTer_Strazha.win_condition.l1 = "location";
			PChar.quest.PZ_BasTer_Strazha.win_condition.l1.location = "BasTer_town";
			PChar.quest.PZ_BasTer_Strazha.win_condition = "PZ_BasTer_Strazha";
		break;
		
		// <== Квест "Путеводная звезда" - Sinistra
		
		//--> Торговля по закону
		case "TPZ_Tavern_1":
			dialog.text = "Oh, "+GetAddress_Form(NPChar)+", la situation est bien pire. Mon fournisseur d'Antigua a perdu sa distillerie – les pirates ont attaqué et tout a brûlé jusqu’aux fondations. Il dit maintenant qu’il n’y aura ni rhum ni vin avant au moins deux mois.";
			link.l1 = "Alors trouvez un nouveau fournisseur. Vous n'allez pas rester les bras croisés pendant deux mois, n'est-ce pas?";
			link.l1.go = "TPZ_Tavern_2";
		break;
		
		case "TPZ_Tavern_2":
			dialog.text = "Trouver un bon fournisseur n’est pas facile. J’ai essayé de traiter avec de petits commerçants, mais ils ne sont pas fiables. Parfois la marchandise arrive, parfois non. Avec un fournisseur sérieux, tout est régulier — livraisons stables et qualité irréprochable.";
			link.l1 = "Eh bien, si les fournisseurs ordinaires posent tant de problèmes, pourquoi ne pas chercher parmi ceux qui opèrent dans l'ombre ? Ils sont généralement plus fiables, et la marchandise est toujours disponible.";
			link.l1.go = "TPZ_Tavern_3";
		break;
		
		case "TPZ_Tavern_3":
			dialog.text = "Vous comprenez bien, "+GetAddress_Form(NPChar)+", la taverne est sous les yeux de tout le monde. Je ne veux pas de problèmes avec les autorités. Si la marchandise était livrée par quelqu’un ayant une bonne réputation, je fermerais volontiers les yeux sur sa provenance.\nAprès tout, quand le besoin est si pressant, qui regarde les détails ? Mais à long terme, je ne traiterai qu’avec des commerçants sérieux et honnêtes.";
			link.l1 = "Je comprends. Eh bien, peut-être que je repasserai. Tous les problèmes ont une solution avec un peu de bon sens.";
			link.l1.go = "TPZ_Tavern_4";
		break;
		
		case "TPZ_Tavern_4":
			DialogExit();
			AddQuestRecord("TPZ", "2");
			pchar.questTemp.TPZ_ContraInfo = true;
			AddLandQuestMark(characterFromId("BasTer_Smuggler"), "questmarkmain");
		break;
		
		case "TPZ_Tavern2_1":
			dialog.text = "Capitaine, c’est incroyable ! Comment avez-vous réussi cela ? Enfin, peu importe. Dites-moi plutôt ce que vous attendez en échange de cette magnifique cargaison d’alcool. Et tout est en ordre côté documents ?";
			if (sti(pchar.reputation.nobility) >= 40)
			{
				link.l1 = "Les documents ? Bien sûr, tout est en règle. Vous n’allez tout de même pas vérifier, si ?";
				link.l1.go = "TPZ_Tavern2_2";
				notification("Test de noblesse réussi", "None");
			}
			else
			{
				link.l1 = "Les documents ?";
				link.l1.go = "TPZ_Tavern2_2_badrep";
				notification("Niveau de noblesse trop bas ! ("+XI_ConvertString(GetReputationName(40))+")", "None");
			}
			DeleteAttribute(pchar, "questTemp.TPZ_Tavern_2");
			DelLandQuestMark(npchar);
		break;
		
		case "TPZ_Tavern2_2_badrep":
			dialog.text = "Capitaine, comprenez-moi, cette cargaison d’alcool est vitale pour moi. Mais ma liberté et ma réputation le sont tout autant. Le gouverneur est impitoyable envers les trafiquants, même les plus insignifiants. Si votre réputation était meilleure, je pourrais fermer les yeux sur l'absence de documents, mais là... Vous attirez bien trop l’attention.";
			link.l1 = "Il est temps de me forger une meilleure réputation. Attendez-moi, je reviendrai bientôt.";
			link.l1.go = "exit";
			pchar.questTemp.TPZ_Tavern_3 = true;
		break;
		
		case "TPZ_Tavern2_2":
			dialog.text = "Pour cette fois, je vais vous croire sur parole. Alors, combien demandez-vous pour cette cargaison ?";
			link.l1 = "Je demande trente doublons pour chaque dizaine de bouteilles de vin, et cinq doublons pour le rhum. Cela fait un total de cent bouteilles de chaque, soit trois cent cinquante doublons.";
			link.l1.go = "TPZ_Tavern2_3";
		break;
		
		case "TPZ_Tavern2_3":
			dialog.text = "Allons donc, capitaine ! C’est du vol pur et simple ! Oui, ma situation est critique, mais je ne vais tout de même pas vendre mon âme pour autant !";
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 50)
			{
				link.l1 = "Très bien, je peux vous accorder une remise. Et ce n’est pas tout. Je souhaite devenir votre fournisseur régulier. Je vous garantis une livraison sans faille. J’ai déjà loué un entrepôt à Basse-Terre, et vous recevrez les marchandises directement de là, sans aucun retard. Il y aura toujours suffisamment d’alcool pour anticiper toute pénurie. Avec la remise, cela vous coûtera deux cent quarante doublons. Qu’en dites-vous ?";
				link.l1.go = "TPZ_Tavern2_4";
				notification("Négociation réussie", SKILL_COMMERCE);
			}
			else
			{
				link.l1 = "Eh bien, je suis prêt"+GetSexPhrase("","e")+" à baisser le prix à deux cent quarante doublons pour la cargaison, car je vise une collaboration à long terme. Je peux répondre à tous vos besoins en boissons et assurer des livraisons régulières. Qu’en dites-vous ?";
				link.l1.go = "TPZ_Tavern2_7";
				notification("Compétence insuffisante (50)", SKILL_COMMERCE);
			}
		break;
		
		case "TPZ_Tavern2_4":
			dialog.text = "C’est encore plus que ce que je payais auparavant. Mais j’ai appris ma leçon — la stabilité a un prix. J’accepte vos conditions, mais sachez-le : au moindre faux pas, je chercherai un autre fournisseur. Je dois savoir pour quoi je paie plus cher. Et aussi... Comment comptez-vous régler les choses avec les autorités ?";
			link.l1 = "Je m’en occupe immédiatement. Dès que tout sera en ordre, je reviendrai avec la marchandise.";
			link.l1.go = "TPZ_Tavern2_5";
		break;
		
		case "TPZ_Tavern2_5":
			dialog.text = "Je vous en prie, ne traînez pas. Mes clients sont impatients de remplir leurs chopes.";
			link.l1 = "Ne vous inquiétez pas, je ne vous ferai pas attendre.";
			link.l1.go = "TPZ_Tavern2_6";
		break;
		
		case "TPZ_Tavern2_6":
			DialogExit();
			AddQuestRecord("TPZ", "5");
			DeleteAttribute(pchar, "questTemp.TPZ_Tavern_3");
			AddLandQuestMark(characterFromId("BasTer_Mayor"), "questmarkmain");
			pchar.questTemp.TPZ_guber_1 = true;
			pchar.questTemp.TPZ_Vino240 = true;
			
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;
		
		case "TPZ_Tavern2_7":
			dialog.text = "C’est encore trop cher, capitaine. Ce prix dépasse celui de mon précédent fournisseur. Même si j'accepte aujourd'hui, je finirai par revenir vers lui une fois la production relancée. Je ne vois pas pourquoi je devrais payer plus.";
			link.l1 = "Je comprends. Très bien. Mon offre finale est de deux cents doublons. Si cela ne vous convient pas non plus, il est inutile de continuer cette discussion.";
			link.l1.go = "TPZ_Tavern2_8";
		break;
		
		case "TPZ_Tavern2_8":
			dialog.text = "D’accord, marché conclu. Deux cents, c’est acceptable. Mais dites-moi, comment comptez-vous régler cela avec les autorités ? Comme je l’ai dit, le gouverneur est extrêmement vigilant contre la contrebande, et il ne permettra pas de telles transactions sous son nez.";
			link.l1 = "Ha ha, là-dessus, je ne serais pas si catégorique. Mais soyez tranquille — je réglerai toutes les formalités administratives dans les plus brefs délais.";
			link.l1.go = "TPZ_Tavern2_9";
		break;
		
		case "TPZ_Tavern2_9":
			dialog.text = "S'il vous plaît, ne tardez pas. Mes clients meurent d’envie de remplir leurs chopes.";
			link.l1 = "Ne vous inquiétez pas, je ne vous ferai pas attendre.";
			link.l1.go = "TPZ_Tavern2_10";
		break;
		
		case "TPZ_Tavern2_10":
			DialogExit();
			AddQuestRecord("TPZ", "6");
			DeleteAttribute(pchar, "questTemp.TPZ_Tavern_3");
			AddLandQuestMark(characterFromId("BasTer_Mayor"), "questmarkmain");
			pchar.questTemp.TPZ_guber_1 = true;
			pchar.questTemp.TPZ_Vino200 = true;
		break;
		
		case "TPZ_Tavern2_11":
			if (sti(pchar.reputation.nobility) >= 40)
			{
				dialog.text = "Bien sûr, capitaine ! Alors, quel prix demandez-vous pour votre cargaison ?";
				link.l1 = "Je demande trente doublons pour chaque dizaine de bouteilles de vin, et cinq doublons pour le rhum. Cela fait cent bouteilles de chaque, soit trois cent cinquante doublons.";
				link.l1.go = "TPZ_Tavern2_3";
				notification("Réputation suffisante", "None");
			}
			else
			{
				dialog.text = "Désolé, capitaine, mais votre réputation laisse encore à désirer.";
				link.l1 = "Merde...";
				link.l1.go = "exit";
				notification("Réputation trop basse ! ("+XI_ConvertString(GetReputationName(40))+")", "None");
			}
		break;
		
		case "TPZ_Tavern3_1":
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino240"))
			{
				dialog.text = "Bien sûr, capitaine ! 240 doublons, comme convenu. Les voici !";
				link.l1 = "C’est un plaisir de faire affaire avec vous ! Le rhum et le vin couleront à nouveau à flots dans votre taverne.";
				link.l1.go = "TPZ_Tavern3_2";
				AddItems(pchar, "gold_dublon", 240);
			}
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino200"))
			{
				dialog.text = "Bien sûr, capitaine ! 200 doublons, comme convenu. Les voici !";
				link.l1 = "C’est un plaisir de faire affaire avec vous ! Le rhum et le vin couleront à nouveau à flots dans votre taverne.";
				link.l1.go = "TPZ_Tavern3_2";
				AddItems(pchar, "gold_dublon", 200);
			}
			DelLandQuestMark(npchar);
		break;
		
		case "TPZ_Tavern3_2":
			dialog.text = "Vous êtes mon sauveur, capitaine ! J’attendrai des livraisons similaires toutes les deux semaines. J’espère que vous respecterez vos engagements à la lettre. Une deuxième pénurie comme celle-ci, ma taverne ne la supporterait pas...";
			link.l1 = "Rassurez-vous, "+npchar.name+". Mon représentant en ville s’appelle Christian Deluche. Il veillera à ce que votre taverne ne manque jamais de vin ni de rhum.";
			link.l1.go = "TPZ_Tavern3_3";
		break;
		
		case "TPZ_Tavern3_3":
			dialog.text = "Christian ? Je le connais, c’est un homme responsable, mais il me semble que... enfin, peu importe. Si tout est en règle avec les autorités, je suppose que je peux lui faire confiance.";
			link.l1 = "Parfait. Sur ce, veuillez m’excuser, il me reste encore une affaire à conclure en ville.";
			link.l1.go = "TPZ_Tavern3_4";
		break;
		
		case "TPZ_Tavern3_4":
			dialog.text = "Revenez nous voir plus souvent !";
			link.l1 = "Avec plaisir.";
			link.l1.go = "TPZ_Tavern3_5";
		break;
		
		case "TPZ_Tavern3_5":
			DialogExit();
			AddQuestRecord("TPZ", "7");
			DeleteAttribute(pchar, "questTemp.TPZ_Tavern_4");
			
			sld = CharacterFromID("TPZ_Kristian");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest\MiniEvents\TradingByLaw_dialog.c";
			sld.dialog.currentnode = "Kristian_31";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		//<-- Торговля по закону
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
