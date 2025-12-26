// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Fale, estou ouvindo";
			link.l1 = "Eu estava enganado. Adeus.";
			link.l1.go = "Exit";
			// Калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche.Bandos") && pchar.questTemp.Caleuche.Bandos == "start")
			{
				link.l1 = "Ouvi falar de uma quadrilha de ladrões e assaltantes agindo nas redondezas de Belize e até mesmo dentro da própria cidade.";
				link.l1.go = "caleuche";
				DelLandQuestMark(npchar);
				DelLandQuestMarkToPhantom();
			}
			if (CheckAttribute(pchar, "questTemp.Caleuche.Bandos") && pchar.questTemp.Caleuche.Bandos == "know" && CheckAttribute(pchar, "questTemp.Caleuche.belizbandos") && GetQuestPastDayParam("questTemp.Caleuche.belizbandos") < 3)
			{
				link.l1 = "Posso te dar informações sobre a gangue.";
				link.l1.go = "caleuche_3";
				DelLandQuestMark(npchar);
				DelLandQuestMarkToPhantom();
			}
			if (CheckAttribute(pchar, "questTemp.Caleuche.BelizRegard"))
			{
				link.l1 = "Alguma novidade sobre a quadrilha? Já os capturaram na caverna?";
				link.l1.go = "caleuche_7";
				DelLandQuestMark(npchar);
				DelLandQuestMarkToPhantom();
			}
			// Путеводная звезда ==>
			if (CheckAttribute(pchar, "questTemp.PZ_Beliz_Komendant"))
			{
				link.l1 = "A cidade inteira parece estar comemorando a captura de um pirata. Pode me contar mais sobre isso?";
				link.l1.go = "PZ_Beliz_Komendant_1";
				DeleteAttribute(pchar, "questTemp.PZ_Beliz_Komendant");
			}
			// <== Путеводная звезда
		break;
		
		// Путеводная звезда ==>
		case "PZ_Beliz_Komendant_1":
			dialog.text = "Com prazer! Este não é um pirata qualquer – é aquele canalha, Matthew Lutter.";
			link.l1 = "A sorte de todo mundo acaba uma hora ou outra.";
			link.l1.go = "PZ_Beliz_Komendant_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Beliz_Komendant_2":
			dialog.text = "Você não é inglês, e também não parece um comerciante, então entendo por que não está tão animado. Lutter aterrorizou essas águas por anos, atacando tanto a nós quanto os espanhóis, mas mais frequentemente a nós. Ele sempre conseguia escapar das nossas patrulhas costeiras, navegando em sua corveta, a Gaivota, que já foi o navio mais rápido do Arquipélago. Como ele conseguiu comandar um navio de guerra desses, só Deus sabe.";
			link.l1 = "Então é verdade que ele perdeu para um mercador? Num corveta? Parece inacreditável.";
			link.l1.go = "PZ_Beliz_Komendant_3";
		break;
		
		case "PZ_Beliz_Komendant_3":
			dialog.text = "Por mais estranho que pareça, é verdade. Um comerciante, e ainda por cima espanhol! Nossa marinha poderia aprender uma ou duas coisas com ele. O capitão Sotta, percebendo que não havia como escapar, preparou-se para a batalha...";
			link.l1 = "Figura bem peculiar, esse Sotta.";
			link.l1.go = "PZ_Beliz_Komendant_4";
		break;
		
		case "PZ_Beliz_Komendant_4":
			dialog.text = "Talvez. Ele mandou adaptar o navio para levar o máximo de carga possível, o que tornou a fuga impossível. Sabendo que os piratas estavam atrás da carga, fingiu estar à deriva. E então...";
			link.l1 = "...ele içou as velas no momento certo?";
			link.l1.go = "PZ_Beliz_Komendant_5";
			if (!CharacterIsHere("Longway"))
			{
				sld = CharacterFromID("Longway");
				ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
			}
		break;
		
		case "PZ_Beliz_Komendant_5":
			dialog.text = "Ha! Não, ele disparou uma saraivada de balins à queima-roupa quando Lutter se aproximou, e depois ele mesmo subiu a bordo do navio pirata! Quando descobriu quem era Lutter, entregou-o para nós. Um verdadeiro herói, um homem de honra!";
			link.l1 = "Não era só a honra que o movia – devia haver uma recompensa por capturar o Tagarela.";
			link.l1.go = "PZ_Beliz_Komendant_6";
		break;
		
		case "PZ_Beliz_Komendant_6":
			dialog.text = "Às vezes, o lucro anda junto com boas intenções. Mas sim, ele foi muito bem recompensado. Sua Graça o presenteou com mercadorias valiosas como sinal da gratidão da nossa cidade antes de ele partir.";
			link.l1 = "Gostaria de tê-lo conhecido – queria apertar sua mão. Me conte...";
			link.l1.go = "PZ_Beliz_Komendant_7";
		break;
		
		case "PZ_Beliz_Komendant_7":
			StartInstantDialog("Longway", "PZ_Beliz_Komendant_8", "Quest\CompanionQuests\Longway.c");
		break;
		// <== Путеводная звезда
		
		// Калеуче
		case "caleuche":
			dialog.text = "Seu informante estava dizendo a verdade. Esses bandidos têm sido um verdadeiro incômodo para nós. Quer nos contar algo sobre eles?";
			link.l1 = "Além disso, só levaram uma coisa importante de mim – nada mais. Eu esperava que você pudesse me contar algo sobre eles. Talvez algum deles tenha sido pego e esteja pronto para testemunhar...";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Desculpe desapontar você, capitão, mas não tenho informações sobre eles. Só sei que estão escondidos em algum lugar na selva, e que têm cúmplices na cidade, só isso. Agora, se souber de algo novo sobre eles, por favor me avise imediatamente.";
			link.l1 = "Certo, oficial. Vou fazer isso.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			DialogExit();
			AddQuestRecord("Caleuche", "10");
			pchar.questTemp.Caleuche.Bandos = "seek";
		break;
		
		case "caleuche_3":
			string sTime;
			if (GetQuestPastDayParam("questTemp.Caleuche.belizbandos") == 0) sTime = "in three days";
			if (GetQuestPastDayParam("questTemp.Caleuche.belizbandos") == 1) sTime = "on the day after tomorrow";
			if (GetQuestPastDayParam("questTemp.Caleuche.belizbandos") == 2) sTime = "tomorrow";
			dialog.text = "Está falando sério, capitão? Fale, estou ouvindo.";
			link.l1 = "Encontrei um dos informantes deles na cidade. Ele me contou que a gangue está se preparando para atacar um navio, que deve chegar à enseada de Chetumal. Os canalhas estão se reunindo "+sTime+" à noite, perto de uma caverna não muito longe de Belize. Para chegar lá, basta pegar o caminho da esquerda na bifurcação da selva.";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "Na caverna? Ótima notícia. Vou mandar preparar uma emboscada para esses canalhas. Se você estiver certo e seu informante falou a verdade, vamos pegar esses desgraçados, e então pedirei ao governador que te recompense.";
			link.l1 = "Obrigado! Vou te procurar quando tudo isso acabar.";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "Tudo bem. Sem problemas.";
			link.l1 = "Até logo, oficial.";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			DialogExit();
			AddDialogExitQuestFunction("Caleuche_BelizComendantPrison");
		break;
		
		case "caleuche_7":
			if (sti(pchar.questTemp.Caleuche.BelizChance) < 3)
			{
				dialog.text = "Preparamos uma recepção calorosa para os canalhas, ha-ha-ha! Se você tivesse visto a cara deles! Capturamos todos, até o chefe! Alguns tentaram resistir, mas nossos soldados valentes cuidaram deles.";
				link.l1 = "Ótima notícia, oficial! Agora os cidadãos de Belize finalmente podem dormir em paz.";
				link.l1.go = "caleuche_12";
			}
			else
			{
				dialog.text = "Hum... Meus soldados esperaram por eles na caverna a noite toda, mas ninguém apareceu. O sargento ficou furioso. Ainda bem que ele ainda não te pegou.";
				link.l1 = "Maldição! Isso não pode ser! Em qual caverna você preparou a emboscada? São duas!";
				link.l1.go = "caleuche_8";
			}
		break;
		
		case "caleuche_8":
			dialog.text = "Onde você me disse. Naquela à direita na bifurcação...";
			link.l1 = "É O DA ESQUERDA! À esquerda da bifurcação, seus imbecis!";
			link.l1.go = "caleuche_9";
		break;
		
		case "caleuche_9":
			dialog.text = "Mas eu me lembro claramente de você ter dito 'à direita'.";
			link.l1 = "Meu Deus! Para a esquerda! Eu disse, PARA! A! ESQUERDA! Você deixou eles escaparem, e a culpa foi sua!";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			AddQuestRecord("Caleuche", "16");
			dialog.text = "Então você deve ter resmungado alguma coisa. Eu ouço muito bem, sabia?";
			link.l1 = "Está bem, oficial, não vou discutir. Queria ajudar, mas não se pode ajudar quem não quer se ajudar. Adeus.";
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Caleuche.BelizChance");
			DeleteAttribute(pchar, "questTemp.Caleuche.BelizRegard");
		break;
		
		case "caleuche_12":
			dialog.text = "Informei ao governador sobre o seu papel na eliminação da quadrilha. Ele valorizou muito a sua contribuição e me autorizou a lhe entregar uma recompensa: um bônus em dinheiro e uma arcabuz de troféu.";
			link.l1 = "Obrigado!";
			link.l1.go = "caleuche_13";
		break;
		
		case "caleuche_13":
			Log_Info("You have received a chest with doubloons");
			Log_Info("You have received an arquebus");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Caleuche", "17");
			GiveItem2Character(pchar, "chest"); 
			GiveItem2Character(pchar, "mushket3"); 
			dialog.text = "Obrigado pelo seu serviço, capitão! Se todos os nossos cidadãos fossem tão dedicados quanto você, já teríamos acabado com o crime há muito tempo! Boa sorte para você!";
			link.l1 = "Até logo, oficial! Boa sorte no seu serviço!";
			link.l1.go = "caleuche_11";
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			OfficersReaction("good");
			ChangeCharacterNationReputation(pchar, ENGLAND, 8);
			AddCharacterExpToSkill(pchar, "Leadership", 300);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 200);//скрытность
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
