// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Que perguntas você tem?","Como posso ajudar você, "+GetAddress_Form(NPChar)+"?"),"Você tentou me fazer uma pergunta há pouco tempo, "+GetAddress_Form(NPChar)+"...","Durante o dia de hoje, essa já é a terceira vez que você faz essa pergunta...","Mais perguntas, imagino?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia...","Não tenho nada para conversar no momento."),"Ah, onde foi parar minha memória...","Sim, é mesmo a terceira vez...","Não, que perguntas?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";			
			if (pchar.questTemp.Slavetrader == "FindRatPortobello")
            {
                link.l1 = "Escute, você viu um corsário chamado Francois Gontier? Ele esteve aqui na sua cidade recentemente.";
                link.l1.go = "Portobello_rat_1";
            }			
			// карибские нравы
			if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy" && !CheckAttribute(npchar, "quest.trial"))
            {
                link.l1 = "Escute, você poderia me dizer onde encontrar um comerciante chamado Jaime Silicio? Ele deveria ter vindo falar com você...";
                link.l1.go = "trial";
            }
			// Addon-2016 Jason ФМК-Гваделупа
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "headhunter_portobello" && !CheckAttribute(npchar, "quest.FMQG"))
            {
                link.l1 = "Olha, estou procurando um homem chamado Bertrand Pinette, já ouviu falar dele? Ele chegou em Portobello há pouco tempo. Um cavalheiro imponente, de peruca encaracolada. Comerciante. Talvez tenha passado por aqui...";
                link.l1.go = "FMQG";
            }
			//--> Письмо от покойника
			if (CheckAttribute(pchar, "questTemp.LFD_Tavern_1"))
            {
                link.l1 = "Você pode me dizer onde posso encontrar Marisa Caldera?";
                link.l1.go = "LFD_Tavern_1_1";
            }
			//<-- Письмо от покойника
		break;
		
		case "Portobello_rat_1":
			dialog.text = NPCStringReactionRepeat("Não, eu não sei. Ele não passou pela taverna e também não o vi na cidade.","Você já perguntou sobre isso e eu já te respondi.","Eu já te disse, 'você já perguntou sobre esse tal de Gontier.'","Escuta, vai embora e para de me incomodar! Você ficou maluco de vez?","block",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Então tá, vou continuar procurando.","Hum, acho que sim...","Sim, é isso mesmo, eu pedi isso...","Desculpe, "+npchar.name+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;		

		case "trial":
			DelLandQuestMark(npchar);
			npchar.quest.trial = true;
			
			dialog.text = "Me perdoe, senhor, mas só um traidor ou um bêbado falaria sobre esses assuntos com um estranho. Não quero confusão.";
			link.l1 = "Um bêbado, é isso? Até mais, camarada.";
			link.l1.go = "exit";
		break;
		
		// Addon-2016 Jason ФМК-Гваделупа
		case "FMQG":
			dialog.text = "Nunca ouvi falar dele, camarada.";
			link.l1 = "Ele é conhecido de Don Carlos de Milyar. Tem certeza de que nunca ouviu falar dele?";
			link.l1.go = "FMQG_1";
		break;
		
		case "FMQG_1":
			dialog.text = "Sou eu. Se ele é amigo do de Milyar, vá até o governador e peça pelo senhor Carlos. Ele vai te contar sobre esse comerciante seu.";
			link.l1 = "Vou fazer isso. Obrigado pelo conselho!";
			link.l1.go = "FMQG_2";
		break;
		
		case "FMQG_2":
			DialogExit();
			AddQuestRecord("FMQ_Guadeloupe", "9");
			npchar.quest.FMQG = true;
		break;
		
		//--> Письмо от покойника
		case "LFD_Tavern_1_1":
			dialog.text = "Marisa? Hm... Não a vejo faz tempo. Desde que soube da morte do marido, ela parou de aparecer pela cidade.";
			link.l1 = "Então ela é viúva?";
			link.l1.go = "LFD_Tavern_1_2";
			DelLandQuestMark(npchar);
		break;

		case "LFD_Tavern_1_2":
			dialog.text = "Sim. O marido dela era capitão da chalupa mercante 'Wavereaver'. Graças a uma licença da Companhia Holandesa das Índias Ocidentais, quase todos os portos do arquipélago estavam abertos para ele. Dizem que ele não sobreviveu a um ataque de piratas no caminho de Belize para Capsterville. Essas coisas não são raras por aqui, mas para ela, foi um golpe e tanto.";
			link.l1 = "Então ela simplesmente sumiu?";
			link.l1.go = "LFD_Tavern_1_3";
		break;

		case "LFD_Tavern_1_3":
			dialog.text = "Bem, 'desapareceu' talvez seja uma palavra forte demais. Mas desde então, ela quase não é vista na cidade. O curioso é que... de vez em quando, aparecem homens diferentes perguntando por ela. Como você, Capitão. Se ela não fosse tão devota, eu até pensaria que... se escondeu e está se virando como pode. Mas a Marisa, antes da morte do marido, nunca perdia uma missa – praticamente morava na igreja – então duvido que seja isso.";
			link.l1 = "É só isso? Não sabe de mais nada?";
			link.l1.go = "LFD_Tavern_1_4";
		break;

		case "LFD_Tavern_1_4":
			dialog.text = "Já contei tudo o que sei, Capitão.";
			link.l1 = "...";
			link.l1.go = "LFD_Tavern_1_5";
		break;

		case "LFD_Tavern_1_5":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Tavern_1");
		break;
		//<-- Письмо от покойника
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}