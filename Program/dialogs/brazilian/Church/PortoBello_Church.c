// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Que tipo de perguntas, "+GetSexPhrase("meu filho","minha filha")+"?","Pode perguntar, estou ouvindo..."),"Estou ouvindo, pode falar. "+GetSexPhrase("meu filho","minha filha")+"...","Pela terceira vez, "+GetSexPhrase("meu filho","minha filha")+", peça o que precisar.","Um clérigo tem muito trabalho, e você está me distraindo. "+GetSexPhrase("meu filho","minha filha")+"...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia...","Agora não, padre..."),"Não tenho nada a dizer, me desculpe.","Vou perguntar, mas depois. Me perdoe, padre.","Com licença, padre...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Письмо от покойника
			if (CheckAttribute(pchar, "questTemp.LFD_Church_1"))
            {
                link.l1 = "Padre, estou procurando por Marisa Caldera. Ouvi dizer que ela é muito devota e costumava frequentar a igreja regularmente. O senhor pode me dizer como encontrá-la?";
                link.l1.go = "LFD_Church_1_1";
            }
			//<-- Письмо от покойника
		break;
		
		//--> Письмо от покойника
		case "LFD_Church_1_1":
			dialog.text = "Marisa era uma das nossas paroquianas mais devotas, realmente a alma da nossa igreja. Sua ausência é uma grande perda para a congregação. O que a fez desaparecer, eu não sei, mas tenho certeza: ela foi injustamente provada, não sem a mão do Diabo e de seus asseclas\nDe vez em quando, ouço rumores de que ela foi vista na cidade, mas nada além disso. Tudo o que podemos fazer é confiar na vontade do Senhor e esperar que um dia ela volte e encontre consolo novamente sob o teto da igreja.";
			link.l1 = "Talvez você conheça alguém que possa me contar mais sobre ela?";
			link.l1.go = "LFD_Church_1_2";
			DelLandQuestMark(npchar);
		break;

		case "LFD_Church_1_2":
			dialog.text = ""+GetSexPhrase("Meu filho","Minha filha")+", me diga, por que você está procurando a Marisa? Eu sei que de vez em quando as pessoas vêm atrás dela, e nem todas parecem ser homens de bem. O mundo está cheio de tentações, e nem todos que a procuram têm boas intenções. Antes de dizer qualquer coisa, preciso ter certeza de que você não pretende fazer mal a ela ou a quem está ao lado dela.";
			link.l1 = "Eu entendo sua preocupação, Padre, mas lhe asseguro: não tenho más intenções. Só quero entregar uma carta que demorou demais para chegar até ela. Vai saber—talvez tenha algo importante para ela aqui dentro. Veja, dê uma olhada.";
			link.l1.go = "LFD_Church_1_3";
			TakeItemFromCharacter(pchar, "LFD_letter");
			notification("Given: Letter for Marisa Caldera", "None");
		break;

		case "LFD_Church_1_3":
			dialog.text = "Sim, esta carta parece ter enfrentado muitas tempestades antes de chegar às suas mãos. Quem sabe o que ela contém, e quais serão as consequências depois de lida... Mas você age com honra, Capitão, ao devolvê-la ao seu verdadeiro destinatário. Se alguém sabe onde Marisa está agora, é sua amiga Dolores Monjo—a única em quem talvez ela tenha confiado\nA casa dela fica à esquerda da capitania do porto. Espero que esta carta não traga mais sofrimento para Marisa, pois ela já suportou mais do que o suficiente.";
			link.l1 = "Obrigado, padre. Que o Senhor cuide de você.";
			link.l1.go = "LFD_Church_1_4";
			GiveItem2Character(PChar, "LFD_letter");
		break;

		case "LFD_Church_1_4":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Church_1");
		break;
		//<-- Письмо от покойника
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
