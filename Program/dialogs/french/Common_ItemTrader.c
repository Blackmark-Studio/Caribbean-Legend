#include "DIALOGS\%language%\Rumours\Common_rumours.c" //Jason
void ProcessDialogEvent()
{
 	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\ItemTrader\" + NPChar.City + "_ItemTrader.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
// ============================================================================
// ============================= блок angry ==========>>>>>>>>>>>>>>>>>>>>>>>>>
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
			
        }
    }
// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
// ============================================================================	   
	switch(Dialog.CurrentNode)
	{
		// -----------------------------------Диалог первый - первая встреча
  		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;

  		case "First time":
			dialog.text = NPCharSexPhrase(npchar,"Souhaiteriez-vous acheter de l'équipement pour vous-même ou pour vos officiers, capitaine? Si c'est le cas, vous êtes venu juste à la bonne personne!","Oh, capitaine, je savais que vous m'approcheriez! Je peux vous proposer de l'équipement pour vous et vos officiers, parmi de nombreuses autres choses utiles.");
			link.l1 = "Montre-moi ce que tu as.";
			link.l1.go = "Trade_exit";
			
   			/*link.l2 = "Je suis venu pour une affaire différente.";
			link.l2.go = "quests";*/
			// --> Мангароса
			if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "find" && npchar.Merchant.type == "potion" && !CheckAttribute(npchar, "quest.mangarosa"))
			{
				link.l4 = "Hey, j'ai trouvé une plante intéressante aux alentours. Pourriez-vous me dire si elle peut être utilisée pour préparer des potions ou des décoctions ? Cela me semble juste intéressant. Pouvez-vous y jeter un coup d'oeil ?";
				link.l4.go = "mangarosa";
			}
			// <-- Мангароса
			

			//Jason --> мини-квест Дефицитный товар
			if (CheckAttribute(pchar, "questTemp.Wine.bottle") && NPChar.location == pchar.questTemp.Wine.City + "_town" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
   				link.l4 = "Dites, pouvez-vous me vendre une bouteille de bon vin européen?";
				link.l4.go = "Wine_ItemTrader";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.bottles") && NPChar.location == pchar.questTemp.Wine.City + "_town" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
   				link.l4 = "Écoute, je sais que tu vends du vin européen. J'ai besoin de soixante bouteilles.";
				link.l4.go = "Wine_Bottles";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.Repeat1") && NPChar.location == pchar.questTemp.Wine.City + "_town" && npchar.id == pchar.questTemp.Wine.ItemTraderID && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
   				link.l4 = "C'est moi à nouveau. Qu'est-ce que tout cela signifie, hein?";
				link.l4.go = "Wine_Repeat1";
			}
			// <-- мини-квест Дефицитный товар
			
			//Sinistra --> мини-квест "Знакомство с индейцами"
			if (CheckAttribute(pchar, "questTemp.ZsI_PokupaemPistolety") && npchar.Merchant.type == "armourer")
			{
   				link.l4 = "J'ai besoin de deux pistolets, avec des balles et de la poudre pour vingt tirs.";
				link.l4.go = "ZsI_PokupaemPistolety";
			}
			// <-- мини-квест "Знакомство с индейцами"
			
			// --> Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l4 = "Écoute, est-ce que le nom 'Juan' te dit quelque chose?";
				link.l4.go = "Consumption";
			}
			// <-- Цена чахотки
			
			//--> Украденное воспоминание
			if(CheckAttribute(pchar, "questTemp.UV_Lavochniki") && !CheckAttribute(npchar, "quest.UV_Vopros") && npchar.city == "PortPax")
			{
				link.l4 = "Bon marchand, je cherche quelque chose d'une qualité exceptionnelle. Pas les babioles communes qui satisfont la majorité, mais une pièce de raffinement authentique—peut-être une paire de boucles d'oreilles finement travaillées ou un pendentif élégant digne du goût aristocratique. Il me faut un cadeau qui ravira une dame de noble lignée.";
				link.l4.go = "UV_Lavochniki_1";
			}
            if(CheckAttribute(pchar, "questTemp.UV_Lavochniki_2") && !CheckAttribute(npchar, "quest.UV_Vopros") && npchar.city == "PortPax")
            {
				link.l4 = "Je me demande si, parmi vos marchandises, vous possédez quelque chose de véritablement précieux ? Je cherche une pièce qui satisferait même le goût le plus exigeant d'une noble dame—quelque chose de distinctif et raffiné, bien au-delà de ce qui pourrait séduire un simple citoyen. Peut-être un pendentif d'une rare élégance ou un bracelet d'un design sophistiqué ?";
				link.l4.go = "UV_Lavochniki_2";
			}
			if(CheckAttribute(pchar, "questTemp.UV_Lavochniki_3") && !CheckAttribute(npchar, "quest.UV_Vopros") && npchar.city == "PortPax")
            {
				link.l4 = "Dites-moi, êtes-vous versé dans l'art de la joaillerie ? Je cherche quelque chose d'extraordinaire à offrir à une dame de qualité. Soyons clairs—je n'ai aucun intérêt pour les colifichets ordinaires. Ce qu'il me faut, c'est une pièce d'une véritable magnificence : peut-être une broche ornée de pierres précieuses ou une bague d'un artisanat inégalé.";
				link.l4.go = "UV_Lavochniki_3";
			}
			//<-- Украденное воспоминание
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l5 = "Écoutez, vous traitez toutes sortes de marchandises... Hier ou aujourd'hui - quelqu'un vous a-t-il proposé de vous vendre "+pchar.GenQuest.Device.Shipyarder.Type+"?";
				link.l5.go = "Device_ItemTrader";
			}
			//<-- генератор Неудачливый вор

			link.l9 = "Merci, pas intéressé.";
			link.l9.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Trade_exit":
            if (CheckNPCQuestDate(npchar, "Item_date"))
			{
				SetNPCQuestDate(npchar, "Item_date");
				GiveItemToTrader(npchar);
			}
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchItemsTrade(npchar, 0);
		break;
		
		//Jason --> мини-квест Дефицитный товар
		case "Wine_ItemTrader":
			dialog.text = "Certainement. Sept cents pesos par bouteille.";
			if (makeint(Pchar.money) >= 700)
			{
				link.l1 = "Excellent. Prenez l'argent et donnez-le-moi.";
				link.l1.go = "Wine_ItemTrader_1";
			}
			link.l2 = "Excellent ! Je reviendrai une fois que j'aurai décidé d'acheter quelque chose.";
			link.l2.go = "exit";
		break;
		
		case "Wine_ItemTrader_1":
			dialog.text = "S'il vous plaît, prenez votre bouteille.";
			link.l1 = "Merci!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -700);
			TakeNItems(pchar, "potionwine", 1);
			PlaySound("interface\important_item.wav");
			DeleteAttribute(pchar, "questTemp.Wine.bottle");
			AddQuestRecord("Wine", "1_1");
			WineTraderQMDel();
		break;
		
		case "Wine_Bottles":
			dialog.text = "Ha! Je suis juste un détaillant, pas un grossiste. Je vendrais autant de bouteilles pendant plus d'une demi-année - ce vin est rare et cher, et tout le monde ne peut pas se le permettre, tu sais. Je n'en ai pas autant.";
			link.l1 = "D'accord, vous ne les avez pas - pas de problème. Mais vous l'obtenez quelque part pour vous-même, n'est-ce pas? Peut-être pourriez-vous me dire le nom de votre fournisseur, et je l'achèterais directement de lui. Ou le vin vous est-il livré depuis l'Europe?";
			link.l1.go = "Wine_Bottles_1";
		break;
		
		case "Wine_Bottles_1":
			dialog.text = "Non, ce n'est pas le cas. Je l'obtiens ici. Mais je ne vais pas vous nommer mon fournisseur comme ça. Mais pour mille pesos... peut-être que je le ferais...";
			if (makeint(Pchar.money) >= 1000)
            {
				link.l1 = "D'accord. Voici ton mille - et maintenant dis-moi, qui est ton fournisseur.";
				link.l1.go = "Wine_Bottles_2";
			}
			link.l2 = "Maintenant, vous, les colporteurs, vous êtes devenus trop effrontés! Ne serait-ce pas trop bien pour vous? Je m'en sortirai très bien sans votre fournisseur, merci.";
			link.l2.go = "Wine_Bottles_fail";
		break;
		
		case "Wine_Bottles_free":
			dialog.text = "Je suppose... d'accord alors. Voici votre note, et j'espère que vous me rendrez la faveur à l'avenir.";
			link.l1 = "...";
			link.l1.go = "Wine_Bottles_free_1";
		break;
		
		case "Wine_Bottles_free_1":
			pchar.questTemp.Wine.TraderID = pchar.questTemp.Wine.City +"_trader";
			sld = characterFromId(pchar.questTemp.Wine.TraderID);
			pchar.questTemp.Wine.Name = GetFullName(sld);
			pchar.questTemp.Wine.ItemTraderID = npchar.id;
			dialog.text = "Le nom de mon fournisseur de vin est "+pchar.questTemp.Wine.Name+", il possède le magasin local.";
			link.l1 = "Compris! Merci!";
			link.l1.go = "exit";
			//pchar.questTemp.Wine.Trader = "true";
			DeleteAttribute(pchar, "questTemp.Wine.bottles");
			pchar.questTemp.Wine.Repeat2 = "true";
			TakeNItems(pchar, "letter_1", 1);
			ChangeItemDescribe("letter_1", "itmdescr_letter_1");
			PlaySound("interface\important_item.wav");
		break;
		
		case "Wine_Bottles_2":
    		AddMoneyToCharacter(pchar, -1000);
			pchar.questTemp.Wine.TraderID = pchar.questTemp.Wine.City +"_trader";
			sld = characterFromId(pchar.questTemp.Wine.TraderID);
			AddLandQuestMark(sld, "questmarkmain");
			pchar.questTemp.Wine.Name = GetFullName(sld);
			pchar.questTemp.Wine.ItemTraderID = npchar.id;
			dialog.text = "Le nom de mon fournisseur de vin est "+pchar.questTemp.Wine.Name+", il possède le magasin local.";
			link.l1 = "Compris ! Merci !";
			link.l1.go = "exit";
			pchar.questTemp.Wine.Trader = "true";
			DeleteAttribute(pchar, "questTemp.Wine.bottles");
			AddQuestRecord("Wine", "3");
			AddQuestUserData("Wine", "sName", pchar.questTemp.Wine.Name);
			WineTraderQMDel();
		break;
		
		case "Wine_Bottles_fail":
			dialog.text = "Comme vous le souhaitez, capitaine. Tout le meilleur pour vous.";
			link.l1 = "Au revoir.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Wine.bottles");
			AddQuestRecord("Wine", "4");
			WineTraderQMDel();
		break;
		
		case "Wine_Repeat1":
			DeleteAttribute(pchar, "questTemp.Wine.Repeat1");
			dialog.text = "Que voulez-vous dire par là? Expliquez-vous.";
			link.l1 = "Tu m'as trompé, espèce de vaurien ! Je viens tout juste d'être au magasin, "+pchar.questTemp.Wine.Name+" ne traite jamais de vin, comme il me l'a lui-même dit ! Rends-moi mon argent !";
			link.l1.go = "Wine_Repeat1_fail";
			link.l2 = "Il y a eu un malentendu... Je suis allé chez l'épicier, et "+pchar.questTemp.Wine.Name+" a prétendu qu'il n'a jamais fait affaire dans le vin. Comment pouvez-vous l'expliquer?";
			link.l2.go = "Wine_Repeat1_1";
		break;
		
		case "Wine_Repeat1_1":
			dialog.text = "Heh ! Il fait affaire dans le vin, c'est certain. Il ne vend pas du vin à n'importe qui - comme avec peu d'autres marchandises, aussi. Et il y a plusieurs raisons à cela... Si vous voulez acheter du vin chez lui, je peux lui écrire une note. Il me connaît et reconnaît mon écriture, donc, après l'avoir lue, il vous vendra ce vin. Bien sûr, ce service n'est pas gratuit non plus.";
			link.l1 = "C'est un scandale ! Tu viens juste de me prendre mille !";
			link.l1.go = "Wine_Repeat1_2";
		break;
		
		case "Wine_Repeat1_2":
			dialog.text = "J'ai pris mille de toi pour des informations. Et pour une lettre, tu devras payer deux mille pesos séparément, et en aucun cas moins que cela.";
			if (makeint(Pchar.money) >= 2000)
			{
				link.l1 = "Oh ... Vous les marchands êtes tellement maudits cupides. Pas étonnant que personne n'aime votre genre. Eh bien, voici votre argent, alors allez-y et écrivez le billet.";
				link.l1.go = "Wine_Bottles_3";
			}
			if(CheckCharacterPerk(pchar, "Trustworthy"))
			{
				notification("Trustworthy", "Trustworthy");
				link.l2 = "(Digne de confiance) Concluons un compromis. Vous fournissez une recommandation maintenant, gratuitement, et je vous rendrai la pareille avec une recommandation pour vous plus tard, également sans frais. Cette affaire de vin n'est que le début.";
				link.l2.go = "Wine_Bottles_free";
			}
			link.l3 = "Mais c'est complètement déplacé ! Je préférerais abandonner toute l'affaire, je n'enrichirai pas un tel avare rusé. Et par cet avare, je veux dire toi. Adieu.";
			link.l3.go = "Wine_Repeat1_goaway";
		break;
		case "Wine_Bottles_free":
			dialog.text = "Je suppose... d'accord alors. Voici votre note, et j'espère que vous rendrez la pareille à l'avenir.";
			link.l1 = "...";
			link.l1.go = "Wine_Bottles_free_1";
		break;
		
		case "Wine_Bottles_free_1":
			pchar.questTemp.Wine.Repeat2 = "true";
			TakeNItems(pchar, "letter_1", 1);
			ChangeItemDescribe("letter_1", "itmdescr_letter_1");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Wine", "6_1");
			DelLandQuestMark(npchar);
			sld = characterFromId(pchar.questTemp.Wine.TraderID);
			AddLandQuestMark(sld, "questmarkmain");
			DialogExit();
		break;
		
		case "Wine_Bottles_3":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = "Vous êtes un drôle d'oiseau, capitaine! Bien sûr, je comprends que votre économe gère toutes les finances, mais vous devriez aussi parfois utiliser votre propre tête. Vous aurez l'occasion d'acheter un lot décent de vins en gros sans ma majoration de prix et de réaliser un bénéfice considérable. Alors ne nous empêchons pas de gagner de l'argent, car c'est vous qui semblez avide maintenant. \nD'accord...(écrit) Tenez, prenez cette lettre - "+pchar.questTemp.Wine.Name+"  vous vendra le vin sans aucune question.";
			link.l1 = "J'espère bien... Si quelque chose tourne mal à nouveau, je reviendrai. À bientôt !";
			link.l1.go = "Wine_Bottles_4";
		break;
		
		case "Wine_Bottles_4":
			pchar.questTemp.Wine.Repeat2 = "true";
			TakeNItems(pchar, "letter_1", 1);
			ChangeItemDescribe("letter_1", "itmdescr_letter_1");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Wine", "6");
			DelLandQuestMark(npchar);
			sld = characterFromId(pchar.questTemp.Wine.TraderID);
			AddLandQuestMark(sld, "questmarkmain");
			DialogExit();
		break;
		
		case "Wine_Repeat1_goaway":
			dialog.text = "Comme vous le souhaitez, capitaine. Au revoir.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddQuestRecord("Wine", "4");
			DelLandQuestMark(npchar);
		break;
		
		case "Wine_Repeat1_fail":
			dialog.text = "Oh, alors tu es venu ici pour me menacer et être impoli? J'appellerai les gardes, alors! Eh, gardes! Juste ici!";
			link.l1 = "Oh, tais-toi! Tu as gagné, je pars! Maudits sois-tu "+NPCharSexPhrase(npchar,"","")+", cormoran, puisses-tu être ruiné !";
			link.l1.go = "exit";
			AddQuestRecord("Wine", "7");
			DelLandQuestMark(npchar);
		break;
		// <-- мини-квест Дефицитный товар
		
		//Sinistra --> мини-квест "Знакомство с индейцами"
		case "ZsI_PokupaemPistolety":
			sld = CharacterFromID("Tichingitu");
			if (sld.location == pchar.location && !LAi_IsDead(sld))
			{
				dialog.text = "Ah, je vois. Tu fais des affaires avec les indigènes ? J'ai entendu dire que celui-ci t'a déjà coûté une jolie somme, ha ha !";
			}
			else
			{
				dialog.text = "Attendiez-vous des ennuis, Capitaine ? Ou planifiez-vous une aventure dans la jungle ? Ha-ha !";
			}
			link.l1 = "Alors, pouvons-nous conclure un accord?";
			link.l1.go = "ZsI_PokupaemPistolety_1";
			DelLandQuestMark(npchar);
		break;
		
		case "ZsI_PokupaemPistolety_1":
			dialog.text = "Bien sûr ! Les clients sont toujours les bienvenus. Pour trois mille pesos, vous obtiendrez des pistolets fiables, des balles et de la poudre comme demandé.";
			if (sti(pchar.Money) > 2999)
			{
				link.l1 = "Cher, mais d'accord. Je le prends.";
				link.l1.go = "ZsI_PokupaemPistolety_2";
			}
			if (sti(pchar.Money) > 2299)
			{
				link.l2 = "Le prix semble injuste. Que diriez-vous d'une réduction pour un ami de Fadey Moscovite?";
				link.l2.go = "ZsI_Torg";
			}
			link.l3 = "Trois mille? C'est du vol! Au revoir, Monsieur!";
			link.l3.go = "ZsI_NetDeneg";
		break;
		
		case "ZsI_NetDeneg":
			DialogExit();
			
			LocatorReloadEnterDisable("BasTer_town", "gate_back", false);
			PChar.quest.ZsI_Timer.over = "yes";
			sld = CharacterFromID("ListKakao");
			sld.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.ZsI_PokupaemPistolety");
		break;
		
		case "ZsI_PokupaemPistolety_2":
			dialog.text = "Passez un bon moment là-bas, Capitaine!";
			link.l1 = "Au revoir, Monsieur.";
			link.l1.go = "ZsI_PokupaemPistolety_3";
			AddMoneyToCharacter(pchar, -3000);
			Log_info("You have acquired the required pistols for Cocoa Leaf");
			PlaySound("Interface\important_item.wav");
		break;
		
		case "ZsI_PokupaemPistolety_3":
			DialogExit();
			
			LocatorReloadEnterDisable("BasTer_town", "gate_back", false);
			DeleteAttribute(pchar, "questTemp.ZsI_PokupaemPistolety");
			PChar.quest.ZsI_Patrul.win_condition.l1 = "location";
			PChar.quest.ZsI_Patrul.win_condition.l1.location = "BasTer_ExitTown";
			PChar.quest.ZsI_Patrul.win_condition = "ZsI_Patrul";
		break;
		
		case "ZsI_Torg":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) > 18)
			{
				notification("Skill Check Passed", SKILL_COMMERCE);
				dialog.text = "En effet, Capitaine. Les amis de Fadey sont toujours les bienvenus ici. Deux mille trois cents pour le lot?";
				link.l1 = "Cela semble mieux. Je le prends.";
				link.l1.go = "ZsI_Torg_2";
				AddCharacterExpToSkill(pchar, "Commerce", 30);
			}
			else
			{
				notification("Skill Check Failed (19)", SKILL_COMMERCE); 
				dialog.text = "Les amis de Monsieur Fadey sont toujours les bienvenus, mais les prix n'ont pas d'amis. Ce sera trois mille pesos, Capitaine.";
				if (sti(pchar.Money) > 2999)
				{
					link.l1 = "Cher, mais d'accord. Je le prends.";
					link.l1.go = "ZsI_PokupaemPistolety_2";
				}
				link.l2 = "Trois mille? C'est du vol! Au revoir, Monsieur!";
				link.l2.go = "ZsI_NetDeneg";
				//Log_info("Trading skill is not sufficient");
				AddCharacterExpToSkill(pchar, "Commerce", -30);
			}
		break;
		
		case "ZsI_Torg_2":
			dialog.text = "Passez une bonne journée là-bas, Capitaine!";
			link.l1 = "Au revoir, Monsieur.";
			link.l1.go = "ZsI_PokupaemPistolety_3";
			AddMoneyToCharacter(pchar, -2300);
			Log_info("You have acquired the required pistols for Cocoa Leaf");
			PlaySound("Interface\important_item.wav");
		break;
		// <-- мини-квест "Знакомство с индейцами"
		
		// --> Цена чахотки
		case "Consumption":
			dialog.text = "Non, cela ne le fait pas... Maintenant, s'il vous plaît, ne me dérangez pas, je suis assez occupé... Quelle question idiote...";
			link.l1 = "Je vois. Désolé de vous avoir fait perdre votre temps...";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
		// <-- Цена чахотки
		//Jason --> генератор Неудачливый вор
		case "Device_ItemTrader":
			dialog.text = "Hmm, "+pchar.GenQuest.Device.Shipyarder.Type+"? Jamais entendu parler auparavant... C'est quoi, en fait ? Je n'ai jamais entendu parler d'une telle chose de toute ma vie"+NPCharSexPhrase(npchar,"","")+".";
			link.l1 = "Eh bien, c'est un outil de charpentier naval, "+pchar.GenQuest.Device.Shipyarder.Describe+". Quelqu'un vous a-t-il offert quelque chose comme ça?";
			link.l1.go = "Device_ItemTrader_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_ItemTrader_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) > 0 && sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 4 && npchar.location.group == "merchant" && npchar.location.locator == "merchant"+sti(pchar.GenQuest.Device.Shipyarder.Chance1))
			{
				dialog.text = "Hmm... Oui, il y avait un gars étrange. Mais il ne m'a pas dit ce que c'était, il a juste essayé de me le vendre. Mais pourquoi en aurais-je besoin, si je n'avais aucune idée de ce que c'est ? Comment pourrais-je le revendre ? Alors, j'ai simplement refusé"+NPCharSexPhrase(npchar,"","")+", et il s'est enfui";
				link.l1 = "Et à quoi ressemblait-il et où est-il allé ? J'ai vraiment besoin de cet instrument.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "Non, rien de tel. Désolé, je ne peux pas vous aider. Demandez autour de vous.";
				link.l1 = "Je comprends. Eh bien, il est temps de se renseigner!";
				link.l1.go = "exit";
			}
		break;
		// <-- генератор Неудачливый вор
		
		// Мангароса
		case "mangarosa":
			// тут работает везение
			if (sti(pchar.questTemp.Mangarosa.m_count) == 5 || GetSummonSkillFromName(pchar, SKILL_FORTUNE) > 10+hrand(30)+hrand(40, "1"))
			{
				dialog.text = "Montrez-le moi... Oui, c'est une plante intéressante. Et une très, très rare. Elle s'appelle Manga Rosa. Je ne sais pas à quoi elle sert, mais il y avait un fait intéressant lié à elle...";
				link.l1 = "Que voulez-vous dire ?";
				link.l1.go = "mangarosa_1";
			}
			else
			{
				dialog.text = LinkRandPhrase("Montrez-le moi... Oui, c'est une plante intéressante. Mais, malheureusement, je ne peux pas vous en dire plus que ça. Si elle est effectivement utilisée à des fins quelconques, cela m'est inconnu.","Voyons voir... Hmm... On dirait une plante médicinale, mais je n'y connais rien. Désolé, je ne peux pas vous aider.","Où est-ce? Hmm... Non, je n'ai jamais vu celui-ci auparavant. Cela semble très intéressant, mais je n'ai aucune idée de à quoi cela sert...");
				link.l1 = "Je vois. Eh bien, je vais poser encore quelques questions. Désolé.";
				link.l1.go = "mangarosa_exit";
			}
		break;
		
		case "mangarosa_exit":
			DialogExit();
			pchar.questTemp.Mangarosa.m_count = sti(pchar.questTemp.Mangarosa.m_count)+1;
			npchar.quest.mangarosa = "true";
		break;
		
		case "mangarosa_1":
			dialog.text = "Des gitans nomades et des sauvages montrent un grand intérêt pour ces plantes. J'ai vu une fois un gitan payer une poignée d'or pour une simple tige comme celle-ci. Mais je n'ai aucune idée de pourquoi ils en auraient besoin.";
			link.l1 = "Je vois... Eh bien, c'est quelque chose au moins ! Maintenant, je sais où demander davantage. Merci beaucoup !";
			link.l1.go = "mangarosa_2";
		break;
		
		case "mangarosa_2":
			DialogExit();
			npchar.quest.mangarosa = "true";
			DeleteAttribute(pchar, "questTemp.Mangarosa.m_count");
			pchar.questTemp.Mangarosa = "gipsy";
			AddQuestRecord("Mangarosa", "2");
		break;
		
		//--> Украденное воспоминание
		case "UV_Lavochniki_1":
			dialog.text = "Hélas, "+GetAddress_Form(NPChar)+", je n'ai plus eu d'objets précieux depuis longtemps. La demande pour ce genre d'articles est, vous savez, bien faible de nos jours. Le peuple ne peut se permettre que des babioles bon marché, et les gens de qualité ne viennent presque jamais chez moi.";
			link.l1 = "D'accord...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.UV_Lavochniki");
			pchar.questTemp.UV_Lavochniki_2 = true;
			npchar.quest.UV_Vopros;
		break;

		case "UV_Lavochniki_2":
			dialog.text = "Hélas, capitaine, je ne vends plus ce genre de marchandises depuis longtemps. Les riches clients viennent rarement ici, et les simples gens n'achètent que ce qui est bon marché.";
			link.l1 = "D'accord...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.UV_Lavochniki_2");
			pchar.questTemp.UV_Lavochniki_3 = true;
			npchar.quest.UV_Vopros;
		break;

		case "UV_Lavochniki_3":
			dialog.text = "Capitaine, vous arrivez un peu trop tard... Il y a seulement quelques heures, j'ai vendu un magnifique collier à un capitaine fortuné. Il m'arrive souvent d'avoir des objets capables de faire fondre le cœur même de la dame la plus exigeante\nRevenez demain, peut-être que Giselle... enfin... mes fournisseurs... pourront vous trouver un bijou qui conquérra le cœur de n'importe quelle dame à jamais.";
			link.l1 = "Je n'ai pas le temps. Il me faut ce bijou immédiatement. Dis-moi, quel est le nom du capitaine à qui tu as vendu le collier ?";
			link.l1.go = "UV_Lavochniki_3_1";
		break;

		case "UV_Lavochniki_3_1":
			dialog.text = "Tristan Renier, capitaine de la 'Mouette d'Or'. Son navire est toujours au port. Mais je doute qu'il veuille se séparer de ce collier. S'il refuse, revenez demain. Je vous le promets, capitaine, vous ne le regretterez pas.";
			link.l1 = "...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.UV_Lavochniki_3");
			AddDialogExitQuestFunction("UV_GoldSeagull");
		break;
		//<-- Украденное воспоминание

// ======================== блок нод angry ===============>>>>>>>>>>>>>>>

////////////////////////////////////////////////////////////////////////////////////////////////
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok")
		break;

// <<<<<<<<<<<<============= блок нод angry =============================
	}
}
