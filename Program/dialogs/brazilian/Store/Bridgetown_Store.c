// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Pode falar, o que você quer?","Acabamos de falar sobre isso. Você deve ter esquecido...","Esta é a terceira vez hoje que você traz essa pergunta...","Olha, aqui é uma loja. As pessoas vêm comprar coisas. Não me atrapalhe!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sabe, "+NPChar.name+", talvez da próxima vez.","Certo, por algum motivo eu me esqueci...","Sim, realmente é a terceira vez...","Hm, eu não vou...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "Ouça, ouvi dizer que os preços de pau-brasil e cacau em Belize vão subir bastante em breve. Fechei um bom negócio recentemente e enchi minha bolsa de dobrões, he-he... Gostaria de adquirir um pouco dessa mercadoria. Posso contar com um desconto?";
                link.l1.go = "StoreDone";
            }
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "barbados1")
			{
				link.l1 = "Um galeão chamado 'Admirável' atracou recentemente na sua colônia sob o comando do Capitão Gaius Marchais. Diga-me, ele poderia ter comprado munição aqui, ou mercadorias para revender?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "StoreDone":
			dialog.text = "Bem, senhor, se o lote for realmente grande, então claro, podemos conversar sobre um desconto razoável.";
			link.l1 = "Maravilha! Ouvi dizer que um novo fluyt deve estar à venda no estaleiro a qualquer momento. Vou esperar e comprar esse navio. Mesmo tendo tirado todos os canhões do meu brigue, ainda não há espaço suficiente no porão para todas essas mercadorias! Passo aqui mais tarde!";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-11");
			DelLandQuestMark(npchar);
			if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7) 
			{
				AddQuestRecord("Holl_Gambit", "2-6");
				pchar.questTemp.HWIC.Eng = "SeekVanBerg";
				pchar.quest.GotoBridgetownOver.over = "yes";//снять таймер
				DelMapQuestMarkCity("Bridgetown");
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Ha! Eu me lembro daquele sujeito estranho! Ele acreditou numa fofoca boba de que Guadalupe precisaria desesperadamente de baunilha porque uma grande caravana de mercadores europeus pararia lá para comprar tantas especiarias quanto conseguissem carregar\nOuço esse tipo de bobagem todo mês, mas Marchais levou isso muito a sério. Ele ficou aqui uma semana, me pediu para juntar baunilha suficiente para encher os porões do navio dele\nParece que gastou até a última moeda nisso. Sinto pena dele, mas não posso impedir um homem de enlouquecer se é isso que ele quer.";
			link.l1 = "Então, ele pode estar em Guadalupe agora?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Muito provavelmente. Porque ele vai continuar esperando por esses 'mercadores' imaginários até o fim dos tempos, e só vai perder dinheiro vendendo baunilha. Se for esperto, vai ficar em Basse-Terre até a procura por baunilha disparar ou até descobrir com certeza outro lugar onde ela seja mais necessária.";
			link.l1 = "Sim. Obrigado, você me ajudou muito!";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			DialogExit();
			AddQuestRecord("Guardoftruth", "14");
			pchar.questTemp.Guardoftruth = "guadeloupe";
			pchar.quest.GuardOT_guadeloupe.win_condition.l1 = "location";
			pchar.quest.GuardOT_guadeloupe.win_condition.l1.location = "guadeloupe";
			pchar.quest.GuardOT_guadeloupe.function = "GuardOT_CreateTwoShips";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
