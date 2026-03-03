// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Fale, estou ouvindo";
			link.l1 = "Eu estava enganado. Adeus.";
			link.l1.go = "Exit";
		break;
		
		case "tonzag_bail":
			NextDiag.TempNode = "First_officer";
		
			dialog.text = "Qual é o motivo da sua visita a Tortuga, Capitão?";
			link.l1 = "Eu imploro! Ajude meu camarada, e eu responderei a todas as suas perguntas!";
			link.l1.go = "tonzag_bail_a";
			link.l2 = "Você é uma pessoa tão importante, e veio aqui sem nenhum guarda, logo depois que a prisão inteira ouviu um tiro?!";
			link.l2.go = "tonzag_bail_b";
		break;
		
		case "tonzag_bail_a":
			dialog.text = "Enquanto você demora para responder, ele está sangrando até a morte. Repito a pergunta.";
			link.l1 = "";
			link.l1.go = "tonzag_bail_1";
		break;
		
		case "tonzag_bail_b":
			dialog.text = "Já sei o suficiente sobre o que aconteceu. Repito a pergunta.";
			link.l1 = "";
			link.l1.go = "tonzag_bail_1";
		break;
		
		case "tonzag_bail_1":
			dialog.text = "Última chance, Capitão.";
			link.l1 = "Estou cumprindo a tarefa que me foi designada pelo governador-geral!";
			link.l1.go = "tonzag_bail_truth";
			link.l2 = "Você sabe muito bem que sou o capitão do meu próprio navio, e trabalho por contrato. E visito sua bela ilha algumas vezes por ano!";
			link.l2.go = "tonzag_bail_lies";
		break;
		
		case "tonzag_bail_truth":
			dialog.text = "Eu tinha minhas suspeitas, mas não tinha certeza absoluta. Você teve sorte que, há poucos dias, aconteceu uma reunião importante em Capsterville. Algumas pessoas muito influentes conseguiram chegar a um acordo. Sendo assim, você não é mais meu inimigo.";
			link.l1 = "Você vai nos ajudar?";
			link.l1.go = "tonzag_bail_truth_1";
			
			AddDialogExitQuestFunction("Tonzag_GetOut");
		break;
		
		case "tonzag_bail_truth_1":
			dialog.text = "Vou libertar você imediatamente. Seu companheiro será transferido para o navio e receberá tratamento.";
			link.l1 = "Obrigado...";
			link.l1.go = "tonzag_bail_truth_2";
		break;
		
		case "tonzag_bail_truth_2":
			dialog.text = "Você quase encalhou, Charles! Vá embora e não volte para Tortuga por pelo menos um mês. Deixe a poeira baixar e os ânimos esfriarem.";
			link.l1 = "Vou fazer isso. Adeus!";
			link.l1.go = "exit";
			link.l2 = "Você não vai explicar nada? Nem um pouco? ...";
			link.l2.go = "tonzag_bail_truth_3";
		break;
		
		case "tonzag_bail_truth_3":
			dialog.text = "Alguém fez uma denúncia contra você. Dizem que é um católico fanático que veio à nossa bela ilha para assassinar maldosamente o nosso honrado governador.";
			link.l1 = "Eu não sou fanático!";
			link.l1.go = "tonzag_bail_truth_4";
		break;
		
		case "tonzag_bail_truth_4":
			dialog.text = "Está escrito com habilidade, pode acreditar. Sou bom nessas coisas – as melhores difamações são aquelas que têm pelo menos um grão de verdade nelas.";
			link.l1 = "Quem escreveu o relatório?";
			link.l1.go = "tonzag_bail_truth_a";
			link.l2 = "Quem deixou o assassino entrar na prisão?";
			link.l2.go = "tonzag_bail_truth_b";
		break;
		
		case "tonzag_bail_truth_a":
			dialog.text = "Alguém quis que você ficasse trancado na prisão por alguns dias, em vez de ser mandado direto para a mesa de tortura dos huguenotes no porão de La Roche.\nChega, Charles. Vá embora. Primeiro resolva o que está na sua frente, e depois... bem, você me entende!";
			link.l1 = "Sim. Eu vou. Adeus, Comandante.";
			link.l1.go = "exit";
		break;
		
		case "tonzag_bail_truth_b":
			dialog.text = "Eu fiz.";
			link.l1 = "É melhor você chamar outro antes que eu vá embora daqui.";
			link.l1.go = "tonzag_bail_truth_b_threat";
			link.l2 = "Estou ouvindo, comandante.";
			link.l2.go = "tonzag_bail_truth_b_charm";
		break;
		
		case "tonzag_bail_truth_b_threat":
			AddComplexSelfExpToScill(100, 100, 100, 100);
		
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 60) {
				dialog.text = "Não sou obrigado a te explicar nada, Charles. Dê-se por satisfeito de ter caído nas minhas mãos e não nas do meu superior direto. E agradeça que quem vai me compensar por toda essa confusão é o seu chefe, não você.";
				link.l1 = "Ceeeeeeerto... Você não conhece meu chefe como eu conheço. Até mais, comandante.";
				link.l1.go = "exit";
				
				Notification_Skill(false, 60, SKILL_LEADERSHIP);
				AddQuestRecord("Tonzag", "3.1");
			} else {
				dialog.text = "Sabe de uma coisa? Acho que vou te contar. Uma doação generosa, livre de impostos, foi feita ao fundo especial de pensão da guarnição. Como forma de agradecimento, o doador pôde contribuir para a rápida e legal execução de um criminoso notório!";
				link.l1 = "Meu oficial?";
				link.l1.go = "tonzag_bail_truth_b_1";
				link.l2 = "Meu amigo?";
				link.l2.go = "tonzag_bail_truth_b_1";
				
				Notification_Skill(true, 60, SKILL_LEADERSHIP);
			}
		break;
		
		case "tonzag_bail_truth_b_charm":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 60) {
				dialog.text = "Não sou obrigado a te explicar nada, Charles. Agradeça por ter caído nas minhas mãos e não nas do meu superior direto. E agradeça também porque quem vai me compensar por toda essa confusão é o seu chefe, e não você.";
				link.l1 = "Ceeeeerto... Você não conhece meu chefe como eu. Até mais, comandante.";
				link.l1.go = "exit";
				
				Notification_Skill(false, 60, SKILL_LEADERSHIP);
				AddQuestRecord("Tonzag", "3.1");
			} else {
				dialog.text = "Sabe de uma coisa? Acho que vou te contar. Uma doação generosa, livre de impostos, foi feita ao fundo especial de pensão da guarnição. Como forma de agradecimento, o doador pôde contribuir para a rápida e justa execução de um criminoso notório!";
				link.l1 = "Meu oficial?";
				link.l1.go = "tonzag_bail_truth_b_1";
				link.l2 = "Meu amigo?";
				link.l2.go = "tonzag_bail_truth_b_1";
				
				Notification_Skill(true, 60, SKILL_LEADERSHIP);
			}
		break;
		
		case "tonzag_bail_truth_b_1":
			dialog.text = "Vá embora, Charles. E leve essa escória com você. Sua escolha de companhia... é decepcionante.";
			link.l1 = "Pelo menos me diga onde posso encontrar seu... benfeitor?";
			link.l1.go = "tonzag_bail_truth_b_2";
		break;
		
		case "tonzag_bail_truth_b_2":
			dialog.text = "No continente. Adeus, Charles.";
			link.l1 = "";
			link.l1.go = "exit";
			
			pchar.questTemp.TonzagQuest.KnowMain = true;
			AddQuestRecord("Tonzag", "3.2");
		break;
		
		case "tonzag_bail_lies":
			dialog.text = "Fizeram uma denúncia contra você. Uma bem séria. Capitão, está claro que armaram pra você, mas... Tenho total autoridade pra mantê-lo aqui por mais algumas semanas e deixar seu amigo morrer. A não ser que...";
			link.l1 = "Quanto?";
			link.l1.go = "tonzag_bail_lies_a";
			link.l2 = "Quem me armou uma cilada? Foi você quem deixou o assassino entrar na prisão?";
			link.l2.go = "tonzag_bail_lies_b";
			
			AddDialogExitQuestFunction("Tonzag_Bailed");
		break;
		
		case "tonzag_bail_lies_a":
			pchar.questTemp.TonzagQuest.Bail = 500;
			dialog.text = "Por favor, deposite quinhentos dobrões no fundo de pensão da guarnição de Tortuga com o agiota local.";
			if (CheckAttribute(pchar, "questTemp.FMQT") && pchar.questTemp.FMQT == "end") {
				pchar.questTemp.TonzagQuest.Bail = 600;
				dialog.text = dialog.text+" E vamos acrescentar mais cem dobrões pelos velhos problemas que você causou ao se envolver com uma dama de alta posição nesta ilha.";
			}
			link.l1 = "Abre logo essa maldita porta!";
			link.l1.go = "exit";
			
			AddQuestRecord("Tonzag", "3.3");
		break;
		
		case "tonzag_bail_lies_b":
			pchar.questTemp.TonzagQuest.Bail = 500;
			dialog.text = "Você já tomou tempo demais do meu dia. Vá até o agiota e deposite quinhentos dobrões no fundo de pensão da guarnição de Tortuga.";
			if (CheckAttribute(pchar, "questTemp.FMQT") && pchar.questTemp.FMQT == "end") {
				pchar.questTemp.TonzagQuest.Bail = 600;
				dialog.text = dialog.text+" E vamos acrescentar mais cem dobrões pelo antigo problema que você causou ao se envolver com uma dama de alta posição nesta ilha.";
			}
			link.l1 = "Abre logo essa maldita porta!";
			link.l1.go = "exit";
			
			AddQuestRecord("Tonzag", "3.3");
		break;
		
		case "tonzag_bailed":
			dialog.text = "";
			link.l1 = "Os fundos foram depositados. Onde está Hercule?";
			link.l1.go = "tonzag_bailed_1";
		break;
		
		case "tonzag_bailed_1":
			dialog.text = "We gave him first aid and sent him to your ship. The scoundrel is tough; he'll most likely pull through. Farewell, Captain, and don't let me catch you on our island for a while!";
			link.l1 = "Bem, depois de uma recepção dessas, vou ficar bem longe daqui! Adeus, Comandante.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "First time";
			AddDialogExitQuestFunction("Tonzag_GetOut");
		break;
		
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
