// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quel genre de questions ?","Que veux-tu, "+GetAddress_Form(NPChar)+"?"),"Vous avez déjà essayé de me poser une question "+GetAddress_Form(NPChar)+"...","Vous avez parlé de cette question pour la troisième fois aujourd'hui...","Ecoutez, si vous n'avez rien à me dire au sujet des affaires du port, alors ne me dérangez pas avec vos questions.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("J'ai changé d'avis.","Je n'ai rien à dire."),"Peu importe.","En effet, déjà la troisième fois...","Desolé, mais je ne suis pas intéressé par les affaires du port pour le moment.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Бремя гасконца
		if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "ship" && !CheckAttribute(npchar, "quest.RescueDaughter"))
		{
			DelLandQuestMark(npchar);
			link.l1 = "Monsieur, je cherche un emploi. Mais pas un travail de porteur, quelque chose de plus approprié à mon rang. Mission, service, avec des affaires délicates... J'accepterai toute mission que vous avez.";
			link.l1.go = "Sharlie";
		}
		//<-- Бремя гасконца
		
		// Jason „олго и счастливо
		if (CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "portman")
		{
			link.l1 = "On m'a dit que vous aviez une lettre pour moi. Le nom est Capitaine Charles de Maure.";
			link.l1.go = "LH_letter";
		}
		//--> Эпилог
		if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PU_Ulysse"))
		{
			link.l1 = "J'ai entendu dire que la pinasse '"+GetShipName("Ulysse")+"' a été récemment mise aux enchères. C’est vrai ?";
			link.l1.go = "SharlieEpilog_PU_Ulysse_1";
		}
		//<-- Эпилог
		break;
		
		case "Sharlie":
			dialog.text = "Aider ? Hm. Je me porte bien, grâce à Dieu. Mais un de mes amis a vraiment besoin d'aide et c'est urgent. Il va entrer seul dans la jungle pour combattre les Indiens, c'est une folie pure !\nJ'ai essayé de le raisonner, je le suppliais, mais il n'a pas écouté ! Il s'inquiète trop pour sa fille et est prêt à donner sa vie pour elle !";
			link.l1 = "Attends, reprenons depuis le début : qui est ton ami, où puis-je le trouver, et quel genre d'aide a-t-il besoin?";
			link.l1.go = "Sharlie_1";			
		break;
		
		case "Sharlie_1":
			dialog.text = "Ah, pardonnez-moi, je suis juste trop anxieux. Son nom est Prosper... Prosper Troubale. Il va mourir à coup sûr ! Et je ne peux pas l'aider - je ne suis pas un soldat. Sa fille a disparu et il croit que les Indiens locaux sont responsables\nImaginez ça, il prévoit de partir à la poursuite des sauvages tout seul ! Ils le découperont en morceaux... En ce moment, il achète un mousquet et se prépare à s'aventurer dans la selva !";
			link.l1 = "Vous êtes un conteur pitoyable, monsieur. Où puis-je trouver votre ami... comment s'appelait-il déjà... Prosper ?";
			link.l1.go = "Sharlie_2";			
		break;
		
		case "Sharlie_2":
			dialog.text = "Je viens de lui parler et j'essayais de le faire changer d'avis. Il n'est pas loin des portes de la ville, près du puits, vérifiant son mousquet et ses munitions. Va le voir et fais quelque chose ! S'il s'aventure seul dans la jungle, il ne reviendra pas, j'en suis sûr. Les diables à peau rouge le déchireront en morceaux...";
			link.l1 = "Arrête de radoter, tu parles comme une vieille femme ! Je vais voir ton ami immédiatement. J'espère pouvoir l'aider.";
			link.l1.go = "Sharlie_3";			
		break;
		
		case "Sharlie_3":
			DialogExit();
			AddQuestRecord("SharlieF", "1");
			RescueDaughter_CreateProsper();
			npchar.quest.RescueDaughter = "true";
			QuestPointerDelLoc("fortfrance_town", "reload", "reload10_back");
		break;
		
		// Jason „олго и счастливо
		case "LH_letter":
			dialog.text = "Oui, tu as raison - il y a une enveloppe. La voici, mais d'abord, il te faut payer pour la livraison - douze mille pesos d'argent.";
			if (sti(pchar.money) >= 12000)
			{
				link.l1 = "J'ai toujours suspecté que votre commerce était à l'origine une affaire de voleurs, mais d'une manière ou d'une autre, j'ai raté le courrier, hm. S'il vous plaît, voici votre argent.";
				link.l1.go = "LH_letter_1";
			}
			else
			{
				link.l1 = "Je reviendrai un peu plus tard, je crois que j'ai laissé ma bourse à la taverne.";
				link.l1.go = "exit";
			}
		break;
		
		case "LH_letter_1":
			DialogExit();
			AddMoneyToCharacter(pchar, -12000);
			LongHappy_RecibeLetter();
		break;
		
		//--> Эпилог
		case "SharlieEpilog_PU_Ulysse_1":
			dialog.text = "C’est exact. Le propriétaire du navire s’est enlisé dans des dettes d’assurance et l’a mis aux enchères. Mais vous arrivez un peu tard – la vente est déjà terminée et le nouveau propriétaire s’occupe des papiers.";
			link.l1 = "Vous sauriez où je peux le trouver ? J’ai besoin de lui parler.";
			link.l1.go = "SharlieEpilog_PU_Ulysse_2";
			DelLandQuestMark(npchar);
			SharlieEpilog_SpawnPikar();
		break;
		
		case "SharlieEpilog_PU_Ulysse_2":
			dialog.text = "Pourquoi le chercher ? Retournez-vous – il est juste derrière vous.";
			link.l1 = "...";
			link.l1.go = "exit";			
		break;
		//<-- Эпилог
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
