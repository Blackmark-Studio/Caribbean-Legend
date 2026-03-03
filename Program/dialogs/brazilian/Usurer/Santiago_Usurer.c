// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quais são suas dúvidas?","Como posso ajudar você?"),"Você tentou me perguntar isso não faz muito tempo...","É, deixa eu adivinhar... Dando voltas de novo?","Ouça, eu cuido das finanças aqui, não respondo perguntas...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia...","Não tenho nada para conversar no momento."),"Ah, onde foi parar minha memória...","Você adivinhou, me desculpe...","Entendo...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит, Голландия
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "SantiagoTripBegin")
			{
				link.l1 = "Senhor, eu sou o capitão "+GetFullName(pchar)+", e estou aqui a mando de Lucas Rodenburg. Tenho um pacote dele para você.";
				link.l1.go = "SantiagoTripBank";	
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "SantiagoTripReturn")
			{
				link.l1 = "Vim buscar a resposta do Señor Lucas Rodenburg.";
				link.l1.go = "SantiagoTripBank_3";	
			}
			//Голландский гамбит, Голландия
		break;
		
		case "SantiagoTripBank":
			if (GetCharacterItem(pchar, "Chest") >= 5)
			{
			dialog.text = "Imagine só... um pacote! Bem, entregue aqui, señor.";
			link.l1 = "Além disso, o senhor Rodenburg pediu para eu lhe entregar isto...";
			link.l1.go = "SantiagoTripBank_1";
			RemoveItems(PChar, "NPC_Letter", 1);
			RemoveItems(PChar, "Chest", 5);
			DelLandQuestMark(npchar);
			}
			else
			{
			dialog.text = "Pelo que eu sei, havia mais alguma coisa que eu deveria receber além do pacote, capitão. Então... onde está? Você entende do que estou falando?";
			link.l1 = "Mas é claro! Os baús estão sob vigilância segura no meu navio. Vou entregá-los a você imediatamente.";
			link.l1.go = "exit";
			}
		break;
		
		case "SantiagoTripBank_1":
			dialog.text = "Hm-m... interessante. Então ele 'manda suas desculpas'. Pois bem. Embora as desculpas do senhor Rodenburg sejam bastante convincentes, é difícil negar. Senhor, vai levar um tempo para preparar uma resposta adequada, poderia voltar amanhã ao meio-dia para buscá-la? Descanse em uma taverna, passeie pela cidade. Santiago tem muito a oferecer.";
			link.l1 = "Certo, voltarei amanhã por volta do meio-dia. Até lá, señor.";
			link.l1.go = "SantiagoTripBank_2";
		break;
		
		case "SantiagoTripBank_2":
			DialogExit();
			pchar.quest.SantiagoTripOver.over = "yes"; //снять таймер
			bDisableFastReload = true;
			pchar.quest.Santiago_Trip.win_condition.l1 = "location";
			pchar.quest.Santiago_Trip.win_condition.l1.location = "Santiago_town";
			pchar.quest.Santiago_Trip.function = "SantiagoTrip_Attack";
			pchar.questTemp.HWIC.Holl = "SantiagoTripAttack";
			LAi_LocationDisableOfficersGen("Santiago_town", true);//офицеров не пускать // 291112
		break;
		
		case "SantiagoTripBank_3":
			dialog.text = "Sim, claro... mas acredito que podemos resolver isso sem formalidades por escrito. Apenas diga a ele estas palavras: 'esse homem deve morrer.' Isso seria justo, e não teremos problemas considerando o 'valor' das desculpas recebidas. E o incidente será considerado totalmente resolvido.";
			link.l1 = "Certo, vou me lembrar disso, señor. Mais alguma coisa?";
			link.l1.go = "SantiagoTripBank_4";
			DelLandQuestMark(npchar);
		break;
		
		case "SantiagoTripBank_4":
			dialog.text = "Sim, é claro. O que eu disse é a vontade da família Giraldi. E pode, é claro, enviar meus melhores cumprimentos ao Senhor Lucas. Desejo-lhe bons ventos, capitão "+GetFullName(pchar)+".";
			link.l1 = "Entendi. Adeus, senhor "+npchar.name+".";
			link.l1.go = "SantiagoTripBank_5";
		break;
		
		case "SantiagoTripBank_5":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "SantiagoTripFinal";
			LAi_LocationDisableOfficersGen("Santiago_town", false);//офицеров пускать // 291112
			AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			AddMapQuestMarkCity("Villemstad", true);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
