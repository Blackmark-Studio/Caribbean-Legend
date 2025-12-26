// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Perguntas, "+GetAddress_Form(NPChar)+"?","Como posso ajudar você, "+GetAddress_Form(NPChar)+"?"),""+GetSexPhrase("Hm, qual é a grande ideia, "+GetAddress_Form(NPChar)+"? ","De novo com essas perguntas estranhas? Querido, vai tomar um rum ou algo assim...")+"","Durante todo este dia, essa já é a terceira vez que você faz essa pergunta..."+GetSexPhrase(" Isso são sinais de carinho?","")+"","Mais perguntas, imagino eu, "+GetAddress_Form(NPChar)+"?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia","Não tenho nada para conversar no momento."),"Não, não, linda...","De jeito nenhum, querido...","Não, que perguntas?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Старые счёты
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_2"))
			{
				link.l1 = "Preciso te fazer algumas perguntas. Você estava trabalhando na taverna no dia em que o barril de gim sumiu, não estava? O que pode me contar sobre o que aconteceu aqui naquele dia?";
				link.l1.go = "OS_Tavern2_1";
			}
			//<-- Старые счёты
		break;

		//--> Старые счёты
		case "OS_Tavern2_1":
			dialog.text = "Eu... Eu não sei o que dizer. Estava tudo normal, nada fora do comum.";
			link.l1 = "É mesmo? Nada de estranho? E aquele marinheiro do 'Fera do Mar' que estava te importunando? Parecia certo de que você ia aceitar a companhia dele esta noite.";
			link.l1.go = "OS_Tavern2_2";
			DelLandQuestMark(npchar);
		break;

		case "OS_Tavern2_2":
			dialog.text = "Ah, ele! Ele... só bebeu um pouco demais, só isso. Isso acontece bastante por aqui, sabe. Eu com certeza não incentivei, mas ele começou a se engraçar. Então eu coloquei ele no lugar dele.";
			link.l1 = "Sem incentivo? Ele conta uma história diferente. Por que você causou tanta confusão desta vez, mas não nas outras ocasiões?";
			link.l1.go = "OS_Tavern2_3";
		break;

		case "OS_Tavern2_3":
			dialog.text = "Eu... eu não sei mais o que dizer! Juro que não sei de nada! Eu estava... estava à vista de todos a noite inteira! Não vi nada, não ouvi nada! E sobre o barril... não faço ideia do que aconteceu com ele! Por que esse interrogatório? Eu só estava... só fazendo meu trabalho, como sempre!";
			link.l1 = "Eu suspeito que você está escondendo algo. Uma noite no porão do navio, sem luz nem comida, faz milagres pela memória. Quer descobrir? Ou vamos conversar direito?";
			link.l1.go = "OS_Tavern2_4_HO";
			link.l2 = "Acredito que você sabe muito mais do que está dizendo. Agora você tem uma chance rara — conte-me tudo, e eu guardo seu papel nessa história só pra mim. Mas se ficar em silêncio — vai ser pior pra você. Vou descobrir a verdade com ou sem a sua ajuda.";
			link.l2.go = "OS_Tavern2_4_harizma";
		break;

		case "OS_Tavern2_4_HO":
			dialog.text = "Eu... eu... eu conto tudo! Foi tudo culpa do meu... pretendente, Jack. Jack Veils! Ele me convenceu a atrair qualquer marinheiro do 'Monstro do Mar'. E quando ele se aproximasse, era pra eu causar uma cena pra tirar o dono da taverna de trás do balcão. Quando a confusão começasse a acalmar, dois marinheiros iam começar uma briga pra manter ele ocupado no salão principal. Foi exatamente isso que aconteceu\nNesse momento, o capitão do 'Monstro do Mar' conseguiu roubar o barril. É... é tudo que eu sei, "+GetSexPhrase("senhor","senhora")+"! Por favor, não me entregue! Eu só... eu estava apenas... eu simplesmente... queria que o Jack finalmente me tratasse com um pouco de respeito! Eu ajudei ele, afinal...";
			link.l1 = "Você ajudou um homem enquanto jogava outro aos lobos sem hesitar por um segundo?! Ainda assim, mantenho minha palavra — não vou revelar seu envolvimento nisso. Mas você vai ter que conviver com o que fez! Sua imprudência poderia ter colocado o estalajadeiro em grande perigo. Onde posso encontrar esse tal Jack? E lembre-se: se mentir pra mim, eu volto. Acredite, você não vai gostar da minha volta.";
			link.l1.go = "OS_Tavern2_5";
			AddComplexSelfExpToScill(40, 40, 40, 0);
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
		break;

		case "OS_Tavern2_4_harizma":
			dialog.text = "Eu... eu... eu conto tudo! Foi tudo ideia do meu... pretendente, Jack. Jack Veils! Ele me convenceu a atrair qualquer marinheiro do 'Monstro do Mar'. E quando ele se aproximasse, era pra eu armar uma cena pra tirar o dono da taverna de trás do balcão. Quando a confusão começasse a se acalmar, dois marinheiros iam começar uma briga pra manter ele ocupado no salão principal. Foi exatamente isso que aconteceu\nNesse tempo, o capitão do 'Monstro do Mar' conseguiu roubar o barril. Isso... isso é tudo que eu sei, "+GetSexPhrase("senhor","senhora")+"! Por favor, não me entregue! Eu só... eu estava apenas... eu simplesmente... queria que o Jack finalmente me tratasse com um pouco de respeito! Afinal, eu ajudei ele...";
			link.l1 = "Você ajudou um homem enquanto jogava outro aos lobos sem hesitar por um segundo?! Ainda assim, mantenho minha palavra — não vou revelar seu envolvimento nisso. Mas você vai ter que conviver com o que fez! Sua imprudência poderia ter colocado o estalajadeiro em sério perigo. Onde posso encontrar esse tal Jack? E lembre-se: se mentir pra mim, eu volto. Pode acreditar, você não vai gostar da minha volta.";
			link.l1.go = "OS_Tavern2_5";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "OS_Tavern2_5":
			dialog.text = "Eu não sabia que era tão sério! É só um barril, afinal de contas... O Jack mora do outro lado da rua. Ele aluga aquela casa, eu... eu não sei de mais nada! Por favor, me perdoe! Capitão, eu juro que nunca mais vou fazer algo assim!";
			link.l1 = "Volte para suas tarefas, e nem pense em começar a chorar — o dono da taverna não pode suspeitar de nada.";
			link.l1.go = "OS_Tavern2_6";
		break;
		
		case "OS_Tavern2_6":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.OS_Tavern_2");
			AddQuestRecord("OS", "4");
			
			//
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.cask_gin = 1;
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.map_full = 1;
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.jewelry2 = 10;
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.GunPowder = 50;
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.bullet = 50;
			
			PChar.quest.OS_Zasada.win_condition.l1 = "item";
			PChar.quest.OS_Zasada.win_condition.l1.item = "cask_gin";
			PChar.quest.OS_Zasada.function = "OS_Zasada";
			
			SetFunctionLocationCondition("DWH_Close_House", "PuertoPrincipe_QuestHouse_1", false);
		break;
		//<-- Старые счёты
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
