// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Que tipo de perguntas, "+GetSexPhrase("meu filho","minha filha")+"?","Pode perguntar, estou ouvindo..."),"Estou ouvindo, pode falar. "+GetSexPhrase("meu filho","minha filha")+"...","Pela terceira vez, "+GetSexPhrase("meu filho","minha filha")+", peça o que precisar.","Um clérigo tem muito trabalho e você está me distraindo, "+GetSexPhrase("meu filho","minha filha")+"...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia...","Agora não, padre..."),"Não tenho nada a dizer, me desculpe.","Eu vou perguntar, mas depois. Me perdoe, padre.","Com licença, padre...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";		
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "utensil" && !CheckAttribute(npchar, "quest.utensil"))
			{
				link.l1 = "Venho até você por causa de um assunto incomum, padre. Um corsário chamado Guy Marchais trouxe recentemente um objeto muito valioso para a sua paróquia. Era um crucifixo peitoral de ouro com lazurita incrustada. Isso é verdade?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Oh sim, meu filho!  É o objeto mais precioso da nossa paróquia. Nunca vi tamanha magnificência em toda a minha vida! Mas por que pergunta, meu filho? Por que está interessado nesta cruz?";
			link.l1 = "Santo Padre, sei que isso não vai lhe agradar, mas esta cruz foi roubada de outra paróquia e o sacerdote foi assassinado durante o crime. O homem que lhe entregou este objeto é um assassino.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Todos nós pecamos, meu filho, e assassinar um clérigo é uma acusação grave. Você tem alguma prova? De qual paróquia essa cruz foi roubada?";
			link.l1 = "A minha palavra não basta como prova? Esta cruz foi roubada da paróquia em Santiago e precisa ser devolvida.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Santiago? Não é uma cidade espanhola? Meu filho, você me surpreende...";
			link.l1 = "Santo Padre, todos são iguais perante Deus. Os espanhóis são cristãos como nós, e desentendimentos entre nações não devem afetar os sentimentos dos fiéis. Peço que devolva esta cruz à paróquia de Santiago.";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Meu filho, você não entende que esta cruz é um presente dos fiéis cristãos para a nossa paróquia?! Não, meu filho, não posso fazer o que você me pede.";
			link.l1 = "Você não se importa que sangue foi derramado sobre essa cruz? Sangue de um clérigo, espanhol ou não, isso não faz diferença.";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "Meu filho, você não apresentou nenhuma prova e eu não posso simplesmente acreditar na sua palavra. A cruz vai permanecer em nossa paróquia. Esta é minha decisão final. Além disso, seu esforço em ajudar os espanhóis nessa questão me preocupa profundamente.";
			link.l1 = "Assim seja. Adeus então, padre...";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			DialogExit();
			npchar.quest.utensil = "true";
			pchar.questTemp.Guardoftruth.Baster_church = "seek";
			AddQuestRecord("Guardoftruth", "27");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
