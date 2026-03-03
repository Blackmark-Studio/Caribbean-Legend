// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Que tipo de perguntas?","O que você quer?");
			link.l1 = RandPhraseSimple("Mudei de ideia.'","Não tenho nada a dizer agora.");
		    link.l1.go = "exit";
			// Rebbebion, квест "Путеводная звезда" ==>
			if (CheckAttribute(pchar, "questTemp.PZ_Beliz.AskForLatterAndSotta") && !CheckAttribute(npchar, "questTemp.PZ_Sotta") && !CheckAttribute(npchar, "questTemp.PZ_Lutter"))
			{
				if (rand(1) == 0)
				{
					link.l1 = "Por acaso você já cruzou com o capitão Edgardo Sotta? Pode nos contar algo sobre ele? Parece ser um homem interessante de se conhecer.";
					link.l1.go = "Sotta1";
					link.l2 = "Você não vai assistir à execução do Tagarela?";
					link.l2.go = "Lutter1";
				}
				else
				{
					link.l1 = "Me diga, você viu o herói do dia, o Capitão Edgardo Sotta? Eu perdi ele, infelizmente. Como ele é? Não acredito que um mercador pegou o infame Tagarela Matt!";
					link.l1.go = "Sotta1_1";
					link.l2 = "Vejo que a cidade inteira está comemorando a captura do Lutter, até mesmo quem nunca vai ao mar."link.l2.go ="Lutter1_1";
				}
			}
			// <== квест "Путеводная звезда"
			//--> Дикая Роза
			if(CheckAttribute(pchar, "questTemp.WildRose_Etap6_Beliz") && CheckAttribute(pchar, "questTemp.WildRose_Beliz_Citizen") && !CheckAttribute(npchar, "quest.WildRose_Vopros") && npchar.city == "Beliz")
			{
				link.l1 = "Há cerca de um mês e meio, um tal de Jerome Sauvernier chegou a Belize. Ele foi ferido numa briga no 'Olho de Vidro', mas sobreviveu. Você poderia me dizer onde posso encontrá-lo?";
				link.l1.go = "WildRose_Beliz_Citizen_1";
			}
			if(CheckAttribute(pchar, "questTemp.WildRose_Etap6_Beliz") && CheckAttribute(pchar, "questTemp.WildRose_Beliz_Citizen_2") && !CheckAttribute(npchar, "quest.WildRose_Vopros") && npchar.city == "Beliz")
			{
				link.l1 = "Há cerca de um mês e meio, mais ou menos, apareceu um cavalheiro em Belize. O nome dele era Jerome Sauvernier. Ele estava procurando por outro homem – então deve ter conversado com o pessoal da cidade. Depois, acabou se ferindo numa briga de taverna, mas felizmente sobreviveu. Você sabe me dizer onde posso encontrá-lo?";
				link.l1.go = "WildRose_Beliz_Citizen_2";
			}
			if(CheckAttribute(pchar, "questTemp.WildRose_Etap6_Beliz") && CheckAttribute(pchar, "questTemp.WildRose_Beliz_Citizen_3") && !CheckAttribute(npchar, "quest.WildRose_Vopros") && npchar.city == "Beliz")
			{
				link.l1 = "Estou tentando encontrar um homem que chegou a Belize há cerca de dois meses. O nome dele é Jerome Sauvernier. Ele estava procurando por um certo cavalheiro, e imagino que tenha conversado com o pessoal da cidade sobre isso...";
				link.l1.go = "WildRose_Beliz_Citizen_3";
			}
			//<-- Дикая Роза
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "Você acha que eu trabalho para o serviço secreto de "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "Bem... não. Então, até logo.";
			link.l1.go = "exit";
			link.l2 = "Mais alguma pergunta, então?";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "Por acaso eu pareço algum tipo de investigador? Eu não sei, não sei de nada.";

            link.l1 = "Você é tão cabeça de vento! Cai fora.";
			link.l1.go = "exit";
			link.l2 = "Mais alguma pergunta, então?";
			link.l2.go = "new question";
		break;
		
		// Квест "Путеводная звезда" ==>
		case "Sotta1":
			dialog.text = "Não cheguei a falar com ele, mas vi o navio dele – um galeão pesado. É perigoso navegar sozinho por essas águas, mas Sotta se vira sem escolta.";
			link.l1 = "Provavelmente correndo atrás de cada moeda de ouro e cortando custos onde pode. Bem, não vou te segurar. Tenha um bom dia.";
			link.l1.go = "Exit";
			
			npchar.questTemp.PZ_Sotta = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Sotta1_1":
			dialog.text = "É difícil de acreditar! Mas não confie em tudo que ouve, senhor. Eu vi ele, tão claramente quanto vejo você agora. Foi bom ele ter pego o Lutter, mas por que toda essa encenação de mercador? Ele se comporta como um soldado. Eu sempre percebo – um parente meu serviu por anos.";
			link.l1 = "Interessante. Bem, cada um tem seus segredos. É melhor eu ir. Obrigado pela informação.";
			link.l1.go = "Exit";
			
			npchar.questTemp.PZ_Sotta = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Lutter1":
			dialog.text = "Já vi esse homem. É difícil acreditar que esse é o mesmo pirata que aterrorizou nossos mercadores por anos. Como ele conseguiu um comando próprio, afinal? Vi os soldados escoltando ele – gritava, chorava, ria. Um louco.";
			link.l1 = "Talvez a derrota e a realidade da morte iminente tenham sido demais para ele. Mas isso não importa. Adeus!";
			link.l1.go = "Exit";
			
			npchar.questTemp.PZ_Lutter = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Lutter1_1":
			dialog.text = "Sim, e eu também estou comemorando – muitos dos meus compatriotas morreram pelas mãos dele. Os mais azarados perderam um pai, um irmão, um filho – você entende. Aquela barbárie durou tempo demais! Se quer saber, o Matt foi um dos piratas mais sortudos dos últimos anos.";
			link.l1 = "A sorte sempre acaba mais cedo ou mais tarde. Até logo.";
			link.l1.go = "Exit";
			
			npchar.questTemp.PZ_Lutter = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		// <== Квест "Путеводная звезда"
		
		//--> Дикая Роза
		case "WildRose_Beliz_Citizen_1":
    		dialog.text = "Não conheço esse homem, senhor. Brigas na taverna acontecem quase todo dia, e lembrar de cada sujeito que se machuca não é tarefa fácil.";
    		link.l1 = "Entendi, obrigado. Tudo de bom.";
    		link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.WildRose_Beliz_Citizen");
			pchar.questTemp.WildRose_Beliz_Citizen_2 = true;
			npchar.quest.WildRose_Vopros;
 		break;
		
		case "WildRose_Beliz_Citizen_2":
    		dialog.text = "Sauvernier? Um francês... Sim, havia um sujeito assim. Ele veio me pedir ajuda, mas não pude fazer nada por ele. Não o vi desde então, me perdoe.";
    		link.l1 = "Obrigado. Então, vou continuar perguntando por aí.";
    		link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.WildRose_Beliz_Citizen_2");
			pchar.questTemp.WildRose_Beliz_Citizen_3 = true;
			npchar.quest.WildRose_Vopros;
 		break;
		
		case "WildRose_Beliz_Citizen_3":
			dialog.text = "Senhor Jerome! Claro, claro, eu me lembro dele. Ele foi ferido numa briga de taverna. Desde então, mal sai de casa, cuidando da ferida na perna.";
			link.l1 = "E onde fica essa casa?";
    		link.l1.go = "WildRose_Beliz_Citizen_3_1";
 		break;
		
		case "WildRose_Beliz_Citizen_3_1":
    		dialog.text = "Fica bem aqui, pertinho, ao lado da capitania do porto. A casa com o telhado vermelho. É lá que você vai encontrá-lo.";
    		link.l1 = "Muito obrigado, você foi de grande ajuda! Tudo de melhor pra você!";
    		link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.WildRose_Beliz_Citizen_3");
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_3_citizen");
 		break;
		//<-- Дикая Роза
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
