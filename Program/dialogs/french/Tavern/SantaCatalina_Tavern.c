// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			if(startHeroType == 4)
			{
				dialog.text = NPCStringReactionRepeat("Bien sûr, Hélène. Qu'est-ce que c'est ?","Ah, enfin tu t'es souvenu de ce que tu voulais ?","Es-tu sûr que tu vas bien ? Tu commences à m'inquiéter. Peut-être devrais-tu voir un médecin ? ","D'accord, Helen. Dors un peu, prends l'air - bref, fais une pause. Puis reviens. Mhm ?","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Non, rien vraiment.","Non, non, désolé de vous déranger.","Vous avez probablement raison...","Oui, tu as probablement raison. C'est la meilleure chose à faire.",npchar,Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quelles questions as-tu?","Comment puis-je vous aider, "+GetAddress_Form(NPChar)+"?"),"Tu as essayé de me poser une question il n'y a pas longtemps, "+GetAddress_Form(NPChar)+"...","Pendant toute cette journée, c'est la troisième fois que tu parles d'une certaine question...","Encore des questions, je présume ?","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(RandPhraseSimple("J'ai changé d'avis...","Je n'ai rien à dire pour le moment."),"Hum, où donc est passée ma mémoire...","Oui, c'est vraiment la troisième fois...","Non, quelles questions ?...",npchar,Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "blueveld")
			{
				link.l1 = "Ecoute, "+npchar.name+", qui est Jan Svenson et comment puis-je le trouver ?";
                link.l1.go = "Svenson";
			}	
			//<-- Бремя гасконца
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok" && !CheckAttribute(npchar, "quest.jino"))
			{
				link.l1 = "Ecoutez, y a-t-il eu un alchimiste qui est arrivé ici en ville, un médecin ? Il est Italien, environ trente ans, son nom est Gino Gvineili. Avez-vous entendu parler de cela ?";
				link.l1.go = "guardoftruth";
			}
		break;
		
		case "Svenson":
			dialog.text = "C'est la première fois que je rencontre un homme qui ne sait pas qui est le Diable de la Forêt. Ce surnom lui a été donné par les Espagnols et ils ont offert un sac entier rempli d'or pour la tête de ce corsaire de l'île de Providence il y a quinze ans ! Oui, les années passent vite... Les gens ont déjà commencé à oublier notre Jan. Peut-être est-il vraiment temps pour lui de se reposer.";
			link.l1 = "Je suis récemment arrivé ici et je ne sais pas grand-chose...";
			link.l1.go = "Svenson_1";			
		break;
		
		case "Svenson_1":
			dialog.text = "Si tu t'intéresses au passé, je peux te vendre un livre d'histoire. Beaucoup donneraient une fortune pour ça, mais moi...";
			link.l2 = "Ne me fais pas tourner en bourrique ! Je t'ai posé une question. Je répète. Où habite Jan Svenson ? J'ai une conversation sérieuse à lui tenir.";
			link.l2.go = "Svenson_2";
		break;
		
		case "Svenson_2":
			dialog.text = "Il vit dans un manoir en face de la résidence de notre maire, à côté de la fontaine. Mais en ce moment, il traverse des moments difficiles et je ne recommanderais pas de le déranger à moins que ce ne soit d'une importance capitale.";
			link.l1 = "Pourquoi donc ?";
			link.l1.go = "Svenson_3";			
		break;
		
		case "Svenson_3":
			dialog.text = "Sa fille préférée Helen, aussi connue sous le nom de Rumba, la fille de son défunt vieil ami Shawn McArthur, a disparu. Repose en paix, vieux loup... Jan traite la jeune diablesse comme sa propre fille, puisqu'il n'a pas d'enfants. Mais la demoiselle s'est volatilisée avec sa goélette 'Arc-en-ciel' et tout l'équipage.\nJe plains la fille. Une rare beauté, intelligente aussi. Brûlante et fougueuse comme le feu, c'est pourquoi ils l'appelaient Rumba ! Son père lui a tout appris, elle a hérité du navire et chaque membre d'équipage est resté à ses côtés. Même les vieux loups de mer l'ont reconnue comme capitaine...";
			link.l1 = "Une femme pirate ? Que pourrait-il lui être arrivé ?";
			link.l1.go = "Svenson_4";			
		break;
		
		case "Svenson_4":
			dialog.text = "Qui sait... Une semaine n'est pas si longue, mais la veuve de MacAthur est convaincue qu'un malheur est arrivé à sa fille et elle a réussi à convaincre Svenson de cela. Il a rassemblé ses hommes et a commencé à chercher lui-même sans résultat pour l'instant. 'Rainbow' et son équipage ont simplement disparu.\nJe peux te dire où trouver Gladys pour mille pièces de huit.";
			if (int(pchar.money) >= 1000)
			{
				link.l1 = "Ton savoir est bien coûteux, mais tu as éveillé ma curiosité. Voici ton argent. Où puis-je la trouver ?";
				link.l1.go = "Svenson_5";
			}
			else
			{
				link.l1 = "Ne t'inquiète pas. Je m'en occuperai moi-même si besoin. Adieu, merci pour l'histoire !";
				link.l1.go = "Svenson_6";
			}		
		break;
		
		case "Svenson_5":
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "Sa maison est à côté du quai, à gauche de l'amarrage. Mais elle n'est probablement pas là. Elle passe toute la journée à traîner près des murs du fort à guetter sa fille bien-aimée. Elle doit déjà avoir pleuré toutes les larmes de son corps.";
			link.l1 = "Merci pour l'histoire ! Adieu, camarade !";
			link.l1.go = "Svenson_6";			
		break;
		
		case "Svenson_6"://устанавливаем Глэдис на форт
			DialogExit();
			ref sld = characterFromId("Gladis");
			ChangeCharacterAddressGroup(sld, "SantaCatalina_fort", "goto", "goto53");
			LAi_SetStayType(sld);
			sld.dialog.currentnode = "FindHelena";
			pchar.questTemp.Saga = "gladis";
			sld = characterFromId("JS_girl");
			sld.dialog.currentnode = "js_girl_8";
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("JS_girl"));
			DelMapQuestMarkCity("SantaCatalina");
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase("Non, je n'en ai pas entendu parler. Nous avons des herboristes et des médecins, mais personne avec un nom comme ça.","C'est la première fois que j'entends un nom aussi étrange. Non, nous n'avons jamais reçu la visite de l'homme dont vous parlez.","Nous n'avons même pas d'alchimistes ici du tout. Nous avons des médecins, mais aucun avec un nom bizarre comme ça.");
			link.l1 = "Je vois. C'est dommage. Je continuerai à chercher !";
			link.l1.go = "exit";
			npchar.quest.jino = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
