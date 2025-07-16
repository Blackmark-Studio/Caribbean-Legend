// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Wszystkie plotki o "+GetCityName(npchar.city)+" do usług. Czego chciałbyś się dowiedzieć?"," Właśnie o tym rozmawialiśmy. Musiałeś zapomnieć... ","To już trzeci raz, kiedy mnie niepokoisz...","Powtarzasz wszystko jak papuga...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Wiesz, "+NPChar.name+"Może następnym razem.","Dobrze, z jakiegoś powodu zapomniałem...","Tak, to naprawdę jest trzeci raz...","Tak...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if(CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "cartahena" && !CheckAttribute(npchar, "quest.gonsales"))
			{
				link.l1 = "Szukam Enrique Gonzalesa. Czy możesz mi powiedzieć, jak go znaleźć?";
				link.l1.go = "saga";				
			}
		break;
			
		case "saga":
			dialog.text = "Wszyscy znają Senora Gonzalesa! Jego dom jest obok urzędu portowego.";
			link.l1 = "Ile on ma lat?";
			link.l1.go = "saga_1";
		break;
		
		case "saga_1":
			dialog.text = "Cóż, nie wiem na pewno, ale wygląda na co najmniej pięćdziesiąt lat. Mieszka w tym domu od dłuższego czasu. Lubi opowiadać przeróżne bajki o piratach, z którymi prawdopodobnie zetknął się tylko w swoich snach.";
			link.l1 = "Wygląda na to, że to człowiek, którego potrzebuję. Dziękuję, "+npchar.name+" , byłeś wielką pomocą!";
			link.l1.go = "saga_2";
		break;
		
		case "saga_2":
			DialogExit();
			npchar.quest.gonsales = "true";
			pchar.questTemp.Saga.Gonsales = "true";
			pchar.quest.Saga_Gonsales1.win_condition.l1 = "location";
			pchar.quest.Saga_Gonsales1.win_condition.l1.location = "Cartahena_houseF2";
			pchar.quest.Saga_Gonsales1.function = "Saga_CreateGonsalesA";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
