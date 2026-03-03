// старпом Акулы - Лейтон Декстер
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Não me incomode, garoto. Fale com o Tubarão, ele é quem manda aqui.";
				link.l1 = "Posso ao menos te cumprimentar ou isso também é contra as regras?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				if (CheckAttribute(npchar, "quest.map"))
				{
					link.l2 = "Layton, o Shark me disse que você tem um mapa da ilha. Posso comprá-lo de você?";
					link.l2.go = "map";
				}
				dialog.text = "Ah, "+GetFullName(pchar)+"! Você tem algum assunto comigo ou só quer conversar? De qualquer forma, traga uma garrafa de rum da próxima vez, ha-ha!";
				link.l1 = "Não, só queria dizer oi. Da próxima vez, trago rum só pra você.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "Ha! Um brincalhão! Tudo bem... Meu nome é Layton Dexter. Eu era o imediato do Tubarão antes de vir parar aqui, e agora sou o braço direito dele nesta 'Cidade dos Navios Abandonados.' (cospe)\nPasso meus dias vendendo mantimentos para os moradores e tentando arrancar algum dinheiro daquele vagabundo do Fazio.";
			link.l1 = "Eu sou "+GetFullName(pchar)+". Prazer em conhecê-lo... Acho.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// Акула погиб по варианту N
		case "admiral":
			dialog.text = "Suponho que você já ouviu que o Steve morreu. Foram os Narvais que fizeram isso.";
			link.l1 = "Ouvi dizer... Então, você é o novo Almirante?";
			link.l1.go = "admiral_1";
			AddQuestRecord("SharkHunt", "28");
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour legendary edition	
		break;
		
		case "admiral_1":
			dialog.text = "Sou eu. Chad desertou para os Narvais, Steve morreu, então... eu sou o Almirante. Alguma objeção?";
			link.l1 = "Não... sem objeções.";
			link.l1.go = "admiral_2";
		break;
		
		case "admiral_2":
			dialog.text = "Bom.";
			link.l1 = "Você vai se vingar dos Narvais pela morte do Tubarão?";
			link.l1.go = "admiral_3";
		break;
		
		case "admiral_3":
			dialog.text = "Quer dizer, se eu vou declarar guerra contra eles? Não. Existem maneiras melhores de fazê-los pagar.\nPrimeiro, vou triplicar o preço que eles pagam pelos mantimentos. Se não gostarem e tentarem atacar o San Augustine, vão pagar com sangue.\nDepois, vou negociar uma trégua com os Rivados. Claro, mal dá pra confiar nesses malditos negros, especialmente depois da morte do feiticeiro deles, Chimiset, mas comida e rum podem amenizar qualquer pecado.";
			link.l1 = "Entendi. Bem... adeus, Layton...";
			link.l1.go = "admiral_4";
		break;
		
		// нода пересечения
		case "admiral_4":
			dialog.text = "Espere. O Steve me disse que você queria sair da ilha e voltar com um navio. Esse ainda é o seu plano?";
			link.l1 = "É.";
			link.l1.go = "admiral_5";
		break;
		
		case "admiral_5":
			dialog.text = "Pegue estes roteiros náuticos. Eles trazem instruções de navegação que vão te trazer de volta aqui inteiro — ou seja, você não vai naufragar nos recifes, não vai ser levado pela correnteza e não vai bater nos destroços ao redor da ilha.\nSem eles, ou você vai passar direto pela ilha... ou vai virar mais um naufrágio.\nLembre-se: você precisa usar uma embarcação pequena, de calado raso, para passar pelos recifes. Tartana, lugre, escuna, saveiro... nada maior que isso. Entendeu?";
			link.l1 = "Sim, eu sei. Obrigado.";
			link.l1.go = "admiral_6";
		break;
		
		case "admiral_6":
			GiveItem2Character(pchar, "LSC_navigation_map");
			dialog.text = "Don't forget to fill your cargo hold with provisions - I'll buy them from you for a good price. And never show this document to anyone; our base must remain secret. I'm only giving it to you because Steve himself was going to, and because you're a friend of Jan Svenson.";
			link.l1 = "Prometo que ninguém mais verá isso. Obrigado de novo, Layton.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Dexter_wait";
			AddQuestRecord("LSC", "5");
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour legendary edition
			// убираем квестовые предметы
			sld = ItemsFromID("key_capper");
			sld.price = 10;
			if (CheckCharacterItem(pchar, "letter_chad")) RemoveItems(pchar, "letter_chad", 1);
		break;
		
		case "Dexter_wait":
			dialog.text = "Já fez algum progresso planejando sua fuga, "+pchar.name+"?";
			link.l1 = "Ainda não, Layton, estou trabalhando nisso.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Dexter_wait";
		break;
		
		// Акула погиб по варианту M
		case "admiral_7":
			dialog.text = "Aí está você. Precisamos conversar.";
			link.l1 = "Então, agora você é o Almirante?";
			link.l1.go = "admiral_8";
		break;
		
		case "admiral_8":
			dialog.text = "Sim, eu sou o Almirante. Fui o braço direito do Steve em tudo, então assumi o comando quando ele morreu. Alguma objeção?";
			link.l1 = "Não... sem objeções. Você tem todo o direito.";
			link.l1.go = "admiral_9";
		break;
		
		case "admiral_9":
			dialog.text = "Fico feliz que nos entendemos. Me avise se precisar de alguma coisa.";
			link.l1 = "Você vai se vingar dos Narvais pela morte do Tubarão?";
			link.l1.go = "admiral_10";
		break;
		
		case "admiral_10":
			dialog.text = "Quer dizer, se eu vou declarar guerra a eles? Não. Existem maneiras melhores de fazê-los pagar.\nPrimeiro, vou triplicar o preço que eles pagam pelos mantimentos. Se não gostarem e tentarem atacar o San Augustine, vão pagar com sangue.\nAlém disso, agora temos uma boa relação com os Rivados, então os Narvais vão pensar duas vezes antes de tentar algo contra a gente de novo.";
			link.l1 = "Entendi. Mais alguma coisa, ou posso ir?";
			link.l1.go = "admiral_4";
		break;
		
		case "plan":
			PlaySound("Voice\English\LSC\Layton Dexter-07");
			dialog.text = "Yes. I see only one way we can get to the Narwhals. It's not perfect, but I don't see any alternative.\nWe will attack them from two directions. A group of cutthroats on longboats will board the Ceres while a second group, joined by the Rivados, will storm the Esmeralda.\nThis will either eliminate them completely, or prompt them to flee to the San Gabriel.\nThe second scenario is more likely; the San Gabriel is a very defensible position and besieging her would take a long time. Either way, we win.";
			link.l1 = "";
			link.l1.go = "plan_1";
		break;
		
		case "plan_1": // ноду Акуле
			DialogExit();
			npchar.greeting = "dexter_1";
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "whyskey_final_3";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_CharacterEnableDialog(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
			NextDiag.CurrentNode = "plan_2";
		break;
		
		case "plan_2":
			dialog.text = "Estou esperando pelo relatório da sua conversa com Donald Greenspan. Isso é crucial, então não perca tempo.";
			link.l1 = "Estou a caminho.";
			link.l1.go = "exit";
			NextDiag.TempNode = "plan_2";
		break;
		
		case "map":
			dialog.text = "Sim, eu tenho um mapa. Se quiser, ele pode ser seu por apenas duzentos doblões.";
			link.l1 = "Que tal pesos?";
			link.l1.go = "map_1";
		break;
		
		case "map_1":
			dialog.text = "No, I take gold - and haggling will get you nowhere; I know exactly what this map is worth, and that's two hundred doubloons.";
			if (PCharDublonsTotal() >= 200)
			{
				link.l1 = "Certo, eu concordo. Aqui está seu ouro.";
				link.l1.go = "map_2";
			}
			link.l2 = "Eu não tenho tanto ouro assim. Talvez mais tarde...";
			link.l2.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "map_2":
			RemoveDublonsFromPCharTotal(200);
			PlaySound("interface\important_item.wav");
			Log_Info("You have received a map of the City of Abandoned Ships");
			GiveItem2Character(pchar, "map_LSC");
			dialog.text = "Pegue seu mapa. Vale o preço – passei uma semana inteira rastejando pela cidade para desenhá-lo. Na verdade, acho até que te vendi barato.";
			link.l1 = "Barato?! Ha! Bem... obrigado.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			DeleteAttribute(npchar, "quest.map");
		break;
		
		// геймовер диким геймерам за издевательство над игрой
		case "LSC_GameOverPrison":
			dialog.text = "Pare aí mesmo, camarada! É, o Tubarão tinha razão, esse desgraçado enlouqueceu. Tanta gente morreu por culpa dele... Amarrem ele e joguem na cela!";
			link.l1 = "...";
			link.l1.go = "LSC_GameOverPrison_1";
		break;
		
		case "LSC_GameOverPrison_1":
			DialogExit();
			DoQuestReloadToLocation("TartarusPrison", "quest", "prison4", "LSC_GameOverInPrison");
		break;
		
		case "return":
			dialog.text = "Steve made me Admiral in his stead - I take it you and he are going back to the Caribbean together.\nI'll stay here and carry on business; me and Steve are loathe to lose such a great base. And you, of course, will always be a welcome guest, here.";
			link.l1 = "Obrigado, Layton. Fique de olho naquele horizonte, um dia eu volto.";
			link.l1.go = "return_1";
		break;
		
		case "return_A":
			dialog.text = "A-ha, "+GetFullName(pchar)+"! Você conseguiu! Encontrou a Ilha da Justiça usando as instruções de navegação do Steve, não foi? Seu maluco... bem-vindo de volta!";
			link.l1 = "Valeu, Layton. Te disse que um dia eu voltaria, ha-ha!";
			link.l1.go = "return_1";
		break;
		
		int iTrade = GetSquadronGoods(pchar, GOOD_FOOD)-GetCrewQuantity(pchar);
		int iMoney = 0;
		case "return_1":
			dialog.text = "Certo. Você tem alguma comida para vender? Estou disposto a pagar o dobro do preço de mercado.";
			if (iTrade > 0)
			{
				link.l1 = "Sim, tenho mantimentos para vender.";
				link.l1.go = "trade";
			}
			link.l2 = "Infelizmente, não tenho nada para te vender no momento.";
			link.l2.go = "return_2";
			npchar.quest.foodqty = 0; // предел затарки складов = 15 000
		break;
		
		case "return_2":
			dialog.text = "Pena. Não esqueça de trazer um pouco da próxima vez – pago bem.";
			link.l1 = "Vou tentar não esquecer.";
			link.l1.go = "exit";
			NextDiag.TempNode = "head";
		break;
		
		case "trade":
			dialog.text = "Quanto?";
			link.l1.edit = 4;
			link.l1 = "";	
			link.l1.go = "trade_1";
		break;
		
		case "trade_1":
			iTemp = dialogEditStrings[4];
			int iMax = GetSquadronGoods(pchar, GOOD_FOOD)-GetCrewQuantity(pchar);
			if (iTemp <= 0 || iTemp > GetSquadronGoods(pchar, GOOD_FOOD))
			{
				dialog.text = "O quê, você está bêbado, camarada? Volte quando estiver pronto para conversar sério.";
				link.l1 = "Hm...";
				link.l1.go = "exit";
			break;
			}
			if (iTemp <= 50)
			{
				dialog.text = "Isso é uma mixaria! Não vale meu tempo – traga mais!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
			break;
			}
			if (iTemp > iMax)
			{
				dialog.text = "E como você pretende navegar sem nenhum mantimento pra você mesmo, camarada? Quer que seus homens morram de fome? Guarde pelo menos "+FindRussianQtyString(GetCrewQuantity(pchar))+".";
				link.l1 = "É, você tem razão.";
				link.l1.go = "exit";
			break;
			}
			if (iTemp >= 15000) // лесник
			{
			 iTemp = (15000 - sti(npchar.quest.foodqty))	
             dialog.text = "Meu Deus do céu, isso é demais pra gente! Nunca conseguiríamos comer tudo antes de estragar. Agora mesmo não posso levar mais que "+iTemp+".";
			 link.l1 = "Tanto faz.";
			 link.l1.go = "trade_3";
			 break;
            }							  
			iMoney = (50+hrand(5, "&Slayer"))*iTemp;
			dialog.text = ""+FindRussianQtyString(iTemp)+"? Tudo bem, eu vou te pagar "+FindRussianMoneyString(iMoney)+". Fechado?";
			link.l1 = "Fechado! Foi um prazer fazer negócio com você!";
			link.l1.go = "trade_2";
			link.l2 = "Hum... não, mudei de ideia.";
			link.l2.go = "exit";
			NextDiag.TempNode = "head";
		break;
		case "trade_3": // лесник 
		    iTemp = (15000 - sti(npchar.quest.foodqty))	
		    iMoney = (50+hrand(5, "&Slayer"))*iTemp;
			dialog.text = "Fechado. Eu vou te pagar "+FindRussianMoneyString(iMoney)+" pelos produtos. Justo?";
			link.l1 = "Justo! Foi um prazer fazer negócio com você!";
			link.l1.go = "trade_4";
			link.l2 = "Hum... não, mudei de ideia.";
			link.l2.go = "exit";
			NextDiag.TempNode = "head";
		break;
		case "trade_4": // лесник 
		    iTemp = (15000 - sti(npchar.quest.foodqty))	
			iMoney = (50+hrand(5, "&Slayer"))*iTemp;
			AddMoneyToCharacter(pchar, iMoney);
			RemoveCharacterGoods(pchar, GOOD_FOOD, iTemp);
			npchar.quest.foodqty = sti(npchar.quest.foodqty)+iTemp;
			if(!CheckAttribute(pchar,"Achievment.LSCfood")) pchar.Achievment.LSCfood = iTemp;
			else pchar.Achievment.LSCfood = sti(pchar.Achievment.LSCfood) + iTemp;
			if(sti(pchar.Achievment.LSCfood) >= 20000) Achievment_Set("ach_CL_112");
			if (sti(npchar.quest.foodqty) >= 15000) // склады затарены на полгода
			{
				SetFunctionTimerCondition("LSC_ClearFoodStorage", 0, 0, 180, false);
				dialog.text = "Maldição, não acredito! Meu armazém está lotado! Não vou precisar comprar mantimentos pelos próximos seis meses.";
				link.l1 = "Ótimo. Então vou trazer o próximo carregamento de mantimentos para você em seis meses.";
				link.l1.go = "exit";
				AddQuestRecord("LSC", "25");
			}
			else
			{
				dialog.text = "Ótimo! Traga mais para mim da próxima vez.";
				link.l1 = "Claro!";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "head";
		break;
		case "trade_2":
			iTemp = dialogEditStrings[4];
			iMoney = (50+hrand(5, "&Slayer"))*iTemp;
			AddMoneyToCharacter(pchar, iMoney);
			RemoveCharacterGoods(pchar, GOOD_FOOD, iTemp);
			npchar.quest.foodqty = sti(npchar.quest.foodqty)+iTemp;
			if(!CheckAttribute(pchar,"Achievment.LSCfood")) pchar.Achievment.LSCfood = iTemp;
			else pchar.Achievment.LSCfood = sti(pchar.Achievment.LSCfood) + iTemp;
			if(sti(pchar.Achievment.LSCfood) >= 20000) Achievment_Set("ach_CL_112");
			if (sti(npchar.quest.foodqty) >= 15000) // склады затарены на полгода
			{
				SetFunctionTimerCondition("LSC_ClearFoodStorage", 0, 0, 180, false);
				dialog.text = "Excelente! Meu armazém está cheio agora. Não vou precisar comprar mantimentos pelo próximo semestre.";
				link.l1 = "Ótimo. Então eu trarei a próxima carga de mantimentos em seis meses.";
				link.l1.go = "exit";
				AddQuestRecord("LSC", "25");
			}
			else
			{
				dialog.text = "Ótimo! Traga mais para mim da próxima vez.";
				link.l1 = "Claro!";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "head";
		break;
		
		case "head": // стандартный диалог Декстера-адмирала
			dialog.text = "A-ah, "+GetFullName(pchar)+"! Que bom te ver! O que você quer?";
			if (iTrade > 0 && sti(npchar.quest.foodqty) < 15000)
			{
				link.l1 = "Quer comprar alguns mantimentos de mim?";
				link.l1.go = "trade";
			}
			link.l2 = "Não é nada, só queria saber como você está.";
			link.l2.go = "exit";
			NextDiag.TempNode = "head";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
