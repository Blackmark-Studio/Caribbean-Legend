// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Que tipo de perguntas?","O que você quer?");
			link.l1 = RandPhraseSimple("Mudei de ideia.'","Não tenho nada a dizer agora.");
		    link.l1.go = "exit";
			//Jason, суп из черепахи
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "baster" && !CheckAttribute(npchar, "quest.terrapin") && CheckAttribute(PChar, "questTemp.Terrapin.SJ_count"))
			{
				link.l1 = "Estou procurando o senhor Jones. Você o conhece?";
				link.l1.go = "terrapin";
			}
		break;
		
		case "terrapin":
			if (sti(pchar.questTemp.Terrapin.SJ_count) == 5 || rand(9) == 1) // 10% или числом
			{
				dialog.text = "Tem muitos Jones por aqui. O mais conhecido que eu sei é o Benjamin Jones, ajudante de ordens do Coronel Fox. Ele costuma receber os visitantes no quartel do regimento.";
				link.l1 = "Ele tem uma irmã chamada Molly?";
				link.l1.go = "terrapin_yes";
			}
			else
			{
				dialog.text = LinkRandPhrase("Qual Jones você procura? Eu conheço pelo menos umas duas dúzias deles...","Temos muitos Jones por aqui. Você precisa ser mais específico.","Tem muitos Jones por aqui, além de Johnsons e Jacksons. Você precisa ser mais específico, certo?");
				link.l1 = "Ele tem uma irmã adulta chamada Molly. Ouvi dizer que ela é uma beleza rara.";
				link.l1.go = "terrapin_no";
			}
			npchar.quest.terrapin = "true";
		break;
		
		case "terrapin_no":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Hum, receio que não posso te ajudar com isso.","Não, eu não conheço ele.","Phah! Se a Molly Jones que eu conheço é uma grande beleza, então o coronel Fox é um padre de paróquia."),LinkRandPhrase("Eu conheço algumas Molly Jones. Uma delas tem um irmão, mas... não é a que você procura. Só alguém que viveu entre macacos chamaria ela de 'uma beleza rara'.","Desculpe, mas todos os Jones que conheço não têm irmãs.","Desculpe, não posso te ajudar. Pergunte para outra pessoa."));
			link.l1 = "Entendi. Desculpe pelo incômodo.";
			link.l1.go = "exit";
			pchar.questTemp.Terrapin.SJ_count = sti(pchar.questTemp.Terrapin.SJ_count)+1;
		break;
		
		case "terrapin_yes":
			dialog.text = "Sim, mas ela estaria melhor se fosse o irmão dele. Essa moça forte provavelmente não vai arranjar marido por causa da cara feia.";
			link.l1 = "Meu agradecimento.";
			link.l1.go = "terrapin_yes_1";
		break;
		
		case "terrapin_yes_1":
			DialogExit();
			AddQuestRecord("Terrapin", "2");
			pchar.questTemp.Terrapin.Benjamin = true;
			DeleteAttribute(pchar, "questTemp.Terrapin.SJ_count");
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

            link.l1 = "Você é mesmo um cabeça de vento! Vai embora.";
			link.l1.go = "exit";
			link.l2 = "Mais alguma pergunta, então?";
			link.l2.go = "new question";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
