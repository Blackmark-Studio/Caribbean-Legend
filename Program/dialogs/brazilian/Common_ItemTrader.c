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
			dialog.text = NPCharSexPhrase(npchar,"Gostaria de comprar equipamentos para você ou para seus oficiais, capitão? Se for o caso, veio falar com a pessoa certa!","Oh, capitão, eu sabia que você viria até mim! Posso oferecer equipamentos para você e seus oficiais, além de muitas outras coisas úteis.");
			link.l1 = "Mostre o que você tem.";
			link.l1.go = "Trade_exit";
			
   			/*link.l2 = "Vim por outro motivo.";
			link.l2.go = "quests";*/
			// --> Мангароса
			if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "find" && npchar.Merchant.type == "potion" && !CheckAttribute(npchar, "quest.mangarosa"))
			{
				link.l4 = "Ei, encontrei uma planta interessante aqui perto. Você pode me dizer se ela serve para preparar poções ou infusões? Ela só chamou minha atenção. Pode dar uma olhada?";
				link.l4.go = "mangarosa";
			}
			// <-- Мангароса
			

			//Jason --> мини-квест Дефицитный товар
			if (CheckAttribute(pchar, "questTemp.Wine.bottle") && NPChar.location == pchar.questTemp.Wine.City + "_town" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
   				link.l4 = "Me diga, você pode me vender uma garrafa de vinho europeu de qualidade?";
				link.l4.go = "Wine_ItemTrader";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.bottles") && NPChar.location == pchar.questTemp.Wine.City + "_town" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
   				link.l4 = "Escute, eu sei que você está vendendo vinho europeu. Eu preciso de sessenta garrafas.";
				link.l4.go = "Wine_Bottles";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.Repeat1") && NPChar.location == pchar.questTemp.Wine.City + "_town" && npchar.id == pchar.questTemp.Wine.ItemTraderID && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
   				link.l4 = "Sou eu de novo. O que tudo isso significa, hein?";
				link.l4.go = "Wine_Repeat1";
			}
			// <-- мини-квест Дефицитный товар
			
			//Sinistra --> мини-квест "Знакомство с индейцами"
			if (CheckAttribute(pchar, "questTemp.ZsI_PokupaemPistolety") && npchar.Merchant.type == "armourer")
			{
   				link.l4 = "Preciso de duas pistolas, além de balas e pólvora para vinte tiros.";
				link.l4.go = "ZsI_PokupaemPistolety";
			}
			// <-- мини-квест "Знакомство с индейцами"
			
			// --> Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l4 = "Escuta, o nome 'Juan' te diz alguma coisa?";
				link.l4.go = "Consumption";
			}
			// <-- Цена чахотки
			
			//--> Украденное воспоминание
			if(CheckAttribute(pchar, "questTemp.UV_Lavochniki") && !CheckAttribute(npchar, "quest.UV_Vopros") && npchar.city == "PortPax")
			{
				link.l4 = "Bom mercador, procuro algo de qualidade excepcional. Não aquelas bugigangas comuns que satisfazem a maioria, mas uma peça de verdadeiro requinte—talvez um par de brincos finamente trabalhados ou um pingente elegante, digno do gosto de uma aristocrata. Preciso de um presente que agrade a uma dama de linhagem distinta.";
				link.l4.go = "UV_Lavochniki_1";
			}
			if(CheckAttribute(pchar, "questTemp.UV_Lavochniki_2") && !CheckAttribute(npchar, "quest.UV_Vopros") && npchar.city == "PortPax")
			{
				link.l4 = "Será que, entre seus pertences, você teria algo de valor realmente significativo? Procuro uma peça que agrade até o gosto mais exigente de uma dama da nobreza — algo distinto e refinado, muito além do que atrairia cidadãos comuns. Talvez um pingente de arte incomum ou uma pulseira de design sofisticado?";
				link.l4.go = "UV_Lavochniki_2";
			}
			if(CheckAttribute(pchar, "questTemp.UV_Lavochniki_3") && !CheckAttribute(npchar, "quest.UV_Vopros") && npchar.city == "PortPax")
			{
				link.l4 = "Me diga, bom mercador, você entende de joias finas? Procuro algo extraordinário para presentear uma dama de prestígio. Vou ser direto: não me interessam bugigangas comuns. O que preciso é de uma peça realmente magnífica — talvez um broche com pedras preciosas ou um anel de artesanato incomparável.";
				link.l4.go = "UV_Lavochniki_3";
			}
			//<-- Украденное воспоминание
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_town" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l5 = "Escuta, você negocia todo tipo de mercadoria... Ontem ou hoje - alguém tentou te vender  "+pchar.GenQuest.Device.Shipyarder.Type+"?";
				link.l5.go = "Device_ItemTrader";
			}
			//<-- генератор Неудачливый вор

			link.l9 = "Obrigado, não estou interessado.";
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
			dialog.text = "Claro. Setecentos pesos por garrafa.";
			if (makeint(Pchar.money) >= 700)
			{
				link.l1 = "Excelente. Pegue o dinheiro e entregue para mim.";
				link.l1.go = "Wine_ItemTrader_1";
			}
			link.l2 = "Excelente! Voltarei assim que decidir comprar algo.";
			link.l2.go = "exit";
		break;
		
		case "Wine_ItemTrader_1":
			dialog.text = "Por favor, pegue sua garrafa.";
			link.l1 = "Obrigado!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -700);
			TakeNItems(pchar, "potionwine", 1);
			PlaySound("interface\important_item.wav");
			DeleteAttribute(pchar, "questTemp.Wine.bottle");
			AddQuestRecord("Wine", "1_1");
			WineTraderQMDel();
		break;
		
		case "Wine_Bottles":
			dialog.text = "Ha! Eu sou só um comerciante, não um atacadista. Eu levaria mais de meio ano pra vender tantas garrafas – esse vinho é raro e caro, não é qualquer um que pode pagar, sabe. Não tenho tudo isso.";
			link.l1 = "Certo, você não tem - sem problema. Mas você consegue de algum lugar, não é? Talvez você possa me dizer o nome do seu fornecedor, e eu compro direto com ele. Ou o vinho vem da Europa para você?";
			link.l1.go = "Wine_Bottles_1";
		break;
		
		case "Wine_Bottles_1":
			dialog.text = "Não, não é isso. Eu entendo aqui. Mas não vou revelar meu fornecedor assim tão fácil. Mas por mil pesos... talvez eu até contasse...";
			if (makeint(Pchar.money) >= 1000)
            {
				link.l1 = "Certo. Aqui está o seu mil – agora me diga, quem é o seu fornecedor.";
				link.l1.go = "Wine_Bottles_2";
			}
			link.l2 = "Agora vocês, mercadores, ficaram ousados demais! Isso não seria bom demais pra vocês? Eu me viro muito bem sem o seu fornecedor, obrigado.";
			link.l2.go = "Wine_Bottles_fail";
		break;
		
		case "Wine_Bottles_free":
			dialog.text = "Suponho que... muito bem então. Aqui está sua nota, e espero que retribua o favor no futuro.";
			link.l1 = "...";
			link.l1.go = "Wine_Bottles_free_1";
		break;
		
		case "Wine_Bottles_free_1":
			pchar.questTemp.Wine.TraderID = pchar.questTemp.Wine.City +"_trader";
			sld = characterFromId(pchar.questTemp.Wine.TraderID);
			pchar.questTemp.Wine.Name = GetFullName(sld);
			pchar.questTemp.Wine.ItemTraderID = npchar.id;
			dialog.text = "O nome do meu fornecedor de vinho é "+pchar.questTemp.Wine.Name+", ele é dono da loja local.";
			link.l1 = "Entendi! Obrigado!";
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
			dialog.text = "O nome do meu fornecedor de vinho é "+pchar.questTemp.Wine.Name+", ele é dono da loja local.";
			link.l1 = "Entendi! Obrigado!";
			link.l1.go = "exit";
			pchar.questTemp.Wine.Trader = "true";
			DeleteAttribute(pchar, "questTemp.Wine.bottles");
			AddQuestRecord("Wine", "3");
			AddQuestUserData("Wine", "sName", pchar.questTemp.Wine.Name);
			WineTraderQMDel();
		break;
		
		case "Wine_Bottles_fail":
			dialog.text = "Como quiser, capitão. Tudo de bom pra você.";
			link.l1 = "Até mais.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Wine.bottles");
			AddQuestRecord("Wine", "4");
			WineTraderQMDel();
		break;
		
		case "Wine_Repeat1":
			DeleteAttribute(pchar, "questTemp.Wine.Repeat1");
			dialog.text = "O que você quer dizer com isso? Explique-se.";
			link.l1 = "Você me enganou, seu patife! Acabei de passar na loja, "+pchar.questTemp.Wine.Name+" nunca negocia com vinho, ele mesmo me disse isso! Me devolva meu dinheiro!";
			link.l1.go = "Wine_Repeat1_fail";
			link.l2 = "Houve um mal-entendido... Fui até o lojista, e "+pchar.questTemp.Wine.Name+" afirmou que nunca lidou com vinho. Como você explica isso?";
			link.l2.go = "Wine_Repeat1_1";
		break;
		
		case "Wine_Repeat1_1":
			dialog.text = "Heh! Ele negocia vinho, disso não tenho dúvida. Só que ele não vende vinho pra qualquer um – assim como faz com algumas outras mercadorias também. E tem vários motivos pra isso... Se quiser comprar vinho com ele, posso escrever um bilhete. Ele me conhece e reconhece minha letra, então depois que ler, vai te vender o vinho. Claro, esse favor também não sai de graça.";
			link.l1 = "Isso é um absurdo! Você acabou de tirar mil moedas de mim!";
			link.l1.go = "Wine_Repeat1_2";
		break;
		
		case "Wine_Repeat1_2":
			dialog.text = "Eu já peguei mil de você pela informação. E pela carta, vai ter que pagar dois mil pesos à parte, e de qualquer jeito, não menos que isso.";
			if (makeint(Pchar.money) >= 2000)
			{
				link.l1 = "Oh... Vocês mercadores são tão gananciosos. Não é à toa que ninguém gosta de vocês. Enfim, aqui está o seu dinheiro, então vá em frente e escreva o bilhete.";
				link.l1.go = "Wine_Bottles_3";
			}
			if(CheckCharacterPerk(pchar, "Trustworthy"))
			{
				Notification_Perk(true, "Trustworthy");
				link.l2 = "(Confiável) Vamos chegar a um acordo. Você me dá uma recomendação agora, de graça, e depois eu faço o mesmo por você, também sem cobrar nada. Este negócio do vinho é só o começo.";
				link.l2.go = "Wine_Bottles_free";
			}
			link.l3 = "Now that's completely out of line! I'd rather abandon the whole affair; I will not enrich such a cunning miser. And by that miser I mean you. Farewell.";
			link.l3.go = "Wine_Repeat1_goaway";
		break;
		case "Wine_Bottles_free":
			dialog.text = "Suponho que... muito bem então. Aqui está sua nota, e espero que um dia você retribua o favor.";
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
			dialog.text = "Você é uma figura, capitão! Olha, eu entendo que seu intendente cuida das finanças, mas de vez em quando você também devia pensar por si mesmo. Vai ter a chance de comprar um bom lote de vinhos no atacado, sem o meu acréscimo, e ainda lucrar bastante. Então, vamos deixar cada um ganhar o seu dinheiro, porque agora quem está parecendo ganancioso é você.\nCerto... (escrevendo) Aqui, pegue esta carta - "+pchar.questTemp.Wine.Name+"  vou te vender o vinho sem fazer perguntas.";
			link.l1 = "Espero que sim... Se algo der errado de novo, eu volto. Até mais!";
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
			dialog.text = "Como quiser, capitão. Adeus.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddQuestRecord("Wine", "4");
			DelLandQuestMark(npchar);
		break;
		
		case "Wine_Repeat1_fail":
			dialog.text = "Ah, então você veio aqui para me ameaçar e ser grosseiro? Vou chamar os guardas, então! Ei, guardas! Aqui!";
			link.l1 = "Ah, cale a boca! Você venceu, estou indo embora! Maldição sobre você "+NPCharSexPhrase(npchar,"","")+", corvo-marinho, que você seja arruinado!";
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
				dialog.text = "Ah, entendi. Fazendo acordos com os nativos? Ouvi dizer que esse aí já te custou uma boa grana, ha ha!";
			}
			else
			{
				dialog.text = "Esperando encrenca, capitão? Ou planejando uma aventura na selva? Ha-ha!";
			}
			link.l1 = "Então, podemos fazer um acordo?";
			link.l1.go = "ZsI_PokupaemPistolety_1";
			DelLandQuestMark(npchar);
		break;
		
		case "ZsI_PokupaemPistolety_1":
			dialog.text = "Claro! Clientes são sempre bem-vindos. Por três mil pesos, você leva pistolas confiáveis, balas e pólvora, como pediu.";
			if (sti(pchar.Money) > 2999)
			{
				link.l1 = "Caro, mas tudo bem. Eu vou levar.";
				link.l1.go = "ZsI_PokupaemPistolety_2";
			}
			if (sti(pchar.Money) > 2299)
			{
				link.l2 = "O preço parece injusto. Que tal um desconto para um amigo do Fadey, o Moscovita?";
				link.l2.go = "ZsI_Torg";
			}
			link.l3 = "Três mil? Isso é um roubo! Adeus, Monsieur!";
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
			dialog.text = "Boa sorte lá fora, Capitão!";
			link.l1 = "Adeus, Monsieur.";
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
				Notification_Skill(true, 19, SKILL_COMMERCE);
				dialog.text = "De fato, Capitão. Os amigos do Fadey são sempre bem-vindos aqui. Dois mil e trezentos pelo lote todo?";
				link.l1 = "Parece melhor. Eu fico com isso.";
				link.l1.go = "ZsI_Torg_2";
				AddCharacterExpToSkill(pchar, "Commerce", 30);
			}
			else
			{
				Notification_Skill(false, 19, SKILL_COMMERCE);
				dialog.text = "Os amigos do Monsieur Fadey são sempre bem-vindos, mas os preços não têm amigos. Vai custar três mil pesos, Capitão.";
				if (sti(pchar.Money) > 2999)
				{
					link.l1 = "Caro, mas tudo bem. Eu vou levar.";
					link.l1.go = "ZsI_PokupaemPistolety_2";
				}
				link.l2 = "Três mil? Isso é um roubo! Adeus, Monsieur!";
				link.l2.go = "ZsI_NetDeneg";
				//Log_info("Trading skill is not sufficient");
				AddCharacterExpToSkill(pchar, "Commerce", -30);
			}
		break;
		
		case "ZsI_Torg_2":
			dialog.text = "Boa sorte lá fora, Capitão!";
			link.l1 = "Adeus, Monsieur.";
			link.l1.go = "ZsI_PokupaemPistolety_3";
			AddMoneyToCharacter(pchar, -2300);
			Log_info("You have acquired the required pistols for Cocoa Leaf");
			PlaySound("Interface\important_item.wav");
		break;
		// <-- мини-квест "Знакомство с индейцами"
		
		// --> Цена чахотки
		case "Consumption":
			dialog.text = "Não, não tem nada a ver... Agora, por favor, não me incomode, estou bastante ocupado... Que pergunta idiota...";
			link.l1 = "Entendi. Desculpe por ter feito você perder tempo...";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
		// <-- Цена чахотки
		//Jason --> генератор Неудачливый вор
		case "Device_ItemTrader":
			dialog.text = "Hmm, "+pchar.GenQuest.Device.Shipyarder.Type+"? Nunca ouvi falar disso antes... O que é, afinal? Nunca ouvi falar de algo assim em todo o meu tempo"+NPCharSexPhrase(npchar,"","")+".";
			link.l1 = "Bem, é uma ferramenta de carpinteiro naval, "+pchar.GenQuest.Device.Shipyarder.Describe+". Alguém te ofereceu algo assim?";
			link.l1.go = "Device_ItemTrader_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_ItemTrader_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) > 0 && sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 4 && npchar.location.group == "merchant" && npchar.location.locator == "merchant"+sti(pchar.GenQuest.Device.Shipyarder.Chance1))
			{
				dialog.text = "Hum... É, apareceu um sujeito estranho. Mas ele não me disse o que era aquilo, só tentou me vender. Mas pra que eu ia querer aquilo, se nem sabia pra que servia? Como é que eu ia revender? Então, só recusei."+NPCharSexPhrase(npchar,"","")+", e ele foi embora";
				link.l1 = "E como ele era, e para onde foi? Eu preciso muito desse instrumento.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "Não, nada disso. Desculpe, não posso te ajudar. Pergunte por aí.";
				link.l1 = "Entendi. Bem, é hora de perguntar por aí!";
				link.l1.go = "exit";
			}
		break;
		// <-- генератор Неудачливый вор
		
		// Мангароса
		case "mangarosa":
			// тут работает везение
			if (sti(pchar.questTemp.Mangarosa.m_count) == 5 || GetSummonSkillFromName(pchar, SKILL_FORTUNE) > 10+hrand(30)+hrand(40, "1"))
			{
				dialog.text = "Mostre para mim... Sim, essa é uma planta interessante. E muito, muito rara. Chama-se Manga Rosa. Não sei para que serve, mas há um fato curioso sobre ela...";
				link.l1 = "O que você quer dizer?";
				link.l1.go = "mangarosa_1";
			}
			else
			{
				dialog.text = LinkRandPhrase("Mostre para mim... Sim, essa é uma planta interessante. Mas, infelizmente, não posso te dizer mais do que isso. Se ela realmente tem algum uso, eu não sei.","Deixe-me ver... Hmm... Parece uma planta medicinal, mas não entendo nada disso. Desculpe, não posso te ajudar.","Onde está? Hmm... Não, nunca vi este antes. Parece realmente muito interessante, mas não faço ideia para que serve...");
				link.l1 = "Entendi. Bem, vou perguntar mais um pouco. Desculpe.";
				link.l1.go = "mangarosa_exit";
			}
		break;
		
		case "mangarosa_exit":
			DialogExit();
			pchar.questTemp.Mangarosa.m_count = sti(pchar.questTemp.Mangarosa.m_count)+1;
			npchar.quest.mangarosa = "true";
		break;
		
		case "mangarosa_1":
			dialog.text = "Ciganos nômades e selvagens demonstram grande interesse por essas plantas. Uma vez vi um cigano pagar um punhado de ouro por apenas um caule desses. Mas não faço ideia do porquê eles precisariam disso.";
			link.l1 = "Entendi... Bem, já é alguma coisa! Agora sei onde perguntar em seguida. Muito obrigado!";
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
			dialog.text = "Lamentavelmente, "+GetAddress_Form(NPChar)+", meu estabelecimento não via mercadorias tão finas há muitos meses. O apetite por luxo diminuiu nesses tempos difíceis. O povo simples que frequenta minha loja só consegue comprar pequenos enfeites, enquanto a nobreza raramente se digna a olhar meus humildes produtos.";
			link.l1 = "Muito bem...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.UV_Lavochniki");
			pchar.questTemp.UV_Lavochniki_2 = true;
			npchar.quest.UV_Vopros;
		break;

		case "UV_Lavochniki_2":
			dialog.text = "Com muito pesar, Capitão, peças tão requintadas não aparecem no meu estabelecimento há bastante tempo. Os clientes abastados deste porto raramente honram minha modesta loja com sua presença, e meus fregueses habituais procuram apenas o que suas bolsas modestas podem pagar.";
			link.l1 = "Muito bem...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.UV_Lavochniki_2");
			pchar.questTemp.UV_Lavochniki_3 = true;
			npchar.quest.UV_Vopros;
		break;

		case "UV_Lavochniki_3":
			dialog.text = "Ah, Capitão, sua chegada não poderia ser mais infeliz... Poucas horas atrás, vendi um colar realmente magnífico — adquirido por outro capitão do mar, de consideráveis posses. Meu estabelecimento costuma receber peças capazes de derreter o coração até da dama mais exigente.  Quem sabe volte amanhã? Giselle... quer dizer... meus fornecedores... provavelmente conseguiriam um tesouro que faria com que você conquistasse de vez a pessoa que tanto admira.";
			link.l1 = "Time is a luxury I do not possess; I require such a piece without delay. Pray tell, what is the name of this fortunate captain who acquired the necklace you speak of?";
			link.l1.go = "UV_Lavochniki_3_1";
		break;

		case "UV_Lavochniki_3_1":
			dialog.text = "Tristan Renier, capitão do 'Golden Seagull'. O navio dele continua ancorado em nosso porto. Mas devo confessar que duvido que ele vá abrir mão de um prêmio desses. Se ele não quiser negociar, volte a me procurar amanhã. Dou minha palavra, Capitão, que você vai achar o acordo bem satisfatório.";
			link.l1 = "...";
			link.l1.go = "UV_Lavochniki_exit";
			DeleteAttribute(pchar, "questTemp.UV_Lavochniki_3");
			AddDialogExitQuestFunction("UV_GoldSeagull");
		break;
		
		case "UV_Lavochniki_exit":
			DialogExit();
			AddQuestRecord("UV", "3");
			/*AddQuestUserData("UV", "sSex", NPCharSexPhrase(NPChar,"ца","ки"));
			AddQuestUserData("UV", "sSex1", NPCharSexPhrase(NPChar,"ец","ка"));
			AddQuestUserData("UV", "sSex2", NPCharSexPhrase(NPChar,"","а"));*/
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
